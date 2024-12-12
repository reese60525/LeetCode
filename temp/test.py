import cv2
import numpy as np
from ultralytics import YOLO

# 初始化 YOLO 模型
model = YOLO("yolov8n.pt")

# 設定安全距離閾值（單位：像素）
SAFE_DISTANCE = 50  # 根據實際情況調整
IOU_THRESHOLD = 0.3  # IoU 閾值
CENTER_APPROACH_THRESHOLD = 10  # 判斷是否靠近中心的速度閾值

# 載入並調整警告圖標大小
warning_icon = cv2.imread('./warning.png', cv2.IMREAD_UNCHANGED)
if warning_icon is None:
    raise FileNotFoundError("警告圖片加載失敗，請檢查圖片路徑是否正確。")
warning_icon = cv2.resize(warning_icon, (50, 50))


# 計算框框的面積大小
def calculate_area(box):
    return (box[2] - box[0]) * (box[3] - box[1])


# 計算兩個邊界框中心點之間的歐幾里得距離
def calculate_distance(box1, box2):
    x1, y1 = (box1[0] + box1[2]) / 2, (box1[1] + box1[3]) / 2
    x2, y2 = (box2[0] + box2[2]) / 2, (box2[1] + box2[3]) / 2
    pixel_distance = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    return pixel_distance


# 計算框框在畫面中的佔比
def calculate_box_ratio(box, frame_width, frame_height):
    box_width = box[2] - box[0]  # 框框寬度
    box_height = box[3] - box[1]  # 框框高度
    box_area = box_width * box_height  # 框框面積
    frame_area = frame_width * frame_height  # 畫面總面積
    return box_area / frame_area  # 返回佔比


# 計算 IoU（框框交集與聯集比值）
def calculate_iou(box1, box2):
    x1 = max(box1[0], box2[0])
    y1 = max(box1[1], box2[1])
    x2 = min(box1[2], box2[2])
    y2 = min(box1[3], box2[3])

    # 計算交集面積
    intersection_area = max(0, x2 - x1) * max(0, y2 - y1)

    # 計算聯集面積
    box1_area = (box1[2] - box1[0]) * (box1[3] - box1[1])
    box2_area = (box2[2] - box2[0]) * (box2[3] - box2[1])
    union_area = box1_area + box2_area - intersection_area

    # 如果聯集面積大於零，返回 IoU 值，否則返回零
    return intersection_area / union_area if union_area > 0 else 0


# 判斷是否朝向中心點靠近
def is_approaching_center(box, frame_center, previous_center):
    current_center = ((box[0] + box[2]) / 2, (box[1] + box[3]) / 2)
    previous_distance = np.sqrt((previous_center[0] - frame_center[0])**2 + (previous_center[1] - frame_center[1])**2)
    current_distance = np.sqrt((current_center[0] - frame_center[0])**2 + (current_center[1] - frame_center[1])**2)
    return previous_distance - current_distance > CENTER_APPROACH_THRESHOLD, current_center


# 判斷x軸是否從左右朝向中間靠近
def is_x_approaching_center(box, frame_center, previous_center):
    current_x = (box[0] + box[2]) / 2
    previous_x = previous_center[0]
    current_distance = abs(current_x - frame_center[0])
    previous_distance = abs(previous_x - frame_center[0])
    print(f'previous_center:{previous_center[0]}, current_center:{current_x}')
    # print(f'previous_distance:{previous_distance}, current_distance:{current_distance}')
    return current_distance < previous_distance


# 在疊加警告圖標函數中增加可調整圖標
def overlay_warning_icon(frame, position, icon):
    icon_h, icon_w = icon.shape[:2]
    x, y = position
    # 確保圖標不超出影像邊界
    if x + icon_w > frame.shape[1]:
        x = frame.shape[1] - icon_w
    if y + icon_h > frame.shape[0]:
        y = frame.shape[0] - icon_h

    # 提取圖標的 alpha 通道作為遮罩
    if icon.shape[2] == 4:  # 如果是 PNG 圖片，帶有透明通道
        alpha_s = icon[:, :, 3] / 255.0
        alpha_l = 1.0 - alpha_s
        for c in range(0, 3):
            frame[y:y + icon_h, x:x + icon_w,
                  c] = (alpha_s * icon[:, :, c] + alpha_l * frame[y:y + icon_h, x:x + icon_w, c])
    else:  # 如果是 JPG 或無透明通道的圖片
        frame[y:y + icon_h, x:x + icon_w] = icon
    return frame


# 處理影片
cap = cv2.VideoCapture('./data/input/video8.mp4')
if not cap.isOpened():
    raise FileNotFoundError("無法開啟影片，請檢查路徑是否正確。")

frame_center = (cap.get(cv2.CAP_PROP_FRAME_WIDTH) / 2, cap.get(cv2.CAP_PROP_FRAME_HEIGHT) / 2)
previous_centers = {}  # 紀錄上一次的中心點
pause = False  # 用於切換暫停狀態

while cap.isOpened():
    if not pause:  # 若未暫停則讀取新幀
        ret, frame = cap.read()
        if not ret:
            break

        # 物體偵測
        results = model(frame)

        for result in results:
            boxes = result.boxes
            if boxes is not None:
                boxes_data = boxes.data.cpu().numpy()
                class_ids = boxes_data[:, 5].astype(int)
                scores = boxes_data[:, 4]  # 提取置信度
                xyxy_boxes = boxes_data[:, :4]  # 提取 [x1, y1, x2, y2]

                # 過濾置信度低於 0.2 的邊界框
                valid_indices = scores >= 0.2
                xyxy_boxes = xyxy_boxes[valid_indices]
                class_ids = class_ids[valid_indices]

                # 找出行人和車輛的邊界框
                person_boxes = xyxy_boxes[class_ids == 0]  # 類別 ID 0 通常為行人
                vehicle_boxes = xyxy_boxes[(class_ids == 2) | (class_ids == 3) | (class_ids == 5) |
                                           (class_ids == 7)]  # 車輛類別

                # 為行人繪製藍色框框
                for p_box in person_boxes:
                    x1, y1, x2, y2 = map(int, p_box)
                    cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 0), 2)

                # 為車輛繪製綠色框框
                for v_box in vehicle_boxes:
                    x1, y1, x2, y2 = map(int, v_box)
                    cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)

                # 檢查行人和車輛之間的條件
                for p_box in person_boxes:
                    for v_box in vehicle_boxes:
                        distance = calculate_distance(p_box, v_box)
                        iou = calculate_iou(p_box, v_box)
                        people_area = calculate_area(p_box)
                        vehicle_area = calculate_area(v_box)
                        # 判斷行人和車輛是否朝向中心點靠近
                        p_approaching, p_current_center = is_approaching_center(
                            p_box, frame_center, previous_centers.get(tuple(p_box), frame_center))
                        v_approaching, v_current_center = is_approaching_center(
                            v_box, frame_center, previous_centers.get(tuple(v_box), frame_center))
                        p_x_approaching = is_x_approaching_center(p_box, frame_center,
                                                                  previous_centers.get(tuple(p_box), frame_center))

                        # 自身和人的距離
                        p_box_ratio = calculate_box_ratio(p_box, frame.shape[1], frame.shape[0])
                        # print(f'比例:{p_box_ratio}')
                        rule1 = (p_box_ratio > 0.003) and (p_x_approaching)

                        # rule2 = people_area < vehicle_area and people_area > 0.05 * vehicle_area

                        # if distance < SAFE_DISTANCE or iou > IOU_THRESHOLD or (p_approaching and v_approaching):
                        if rule1:
                            # # 更新中心點紀錄
                            # previous_centers[tuple(p_box)] = p_current_center
                            # previous_centers[tuple(v_box)] = v_current_center

                            # 調整警告圖片大小為框框的 1/2
                            adjusted_icon = cv2.resize(warning_icon, (max(int(
                                (p_box[2] - p_box[0]) / 2), 1), max(int((p_box[3] - p_box[1]) / 2), 1)))

                            # 在行人位置顯示警告圖標
                            frame = overlay_warning_icon(frame, (int(p_box[0]), int(p_box[1])), adjusted_icon)

                            # # 在車輛位置顯示警告圖標
                            # adjusted_icon_vehicle = cv2.resize(warning_icon, (max(int(
                            #     (v_box[2] - v_box[0]) / 2), 1), max(int((v_box[3] - v_box[1]) / 2), 1)))
                            # frame = overlay_warning_icon(frame, (int(v_box[0]), int(v_box[1])), adjusted_icon_vehicle)

                            # # 繪製行人與車輛之間的紫色連線
                            # p_center = (int((p_box[0] + p_box[2]) / 2), int((p_box[1] + p_box[3]) / 2))
                            # v_center = (int((v_box[0] + v_box[2]) / 2), int((v_box[1] + v_box[3]) / 2))
                            # cv2.line(frame, p_center, v_center, (255, 0, 255), 2)  # 紫色連線

    # 顯示結果
    cv2.imshow('Frame', frame)
    key = cv2.waitKey(10)
    if key & 0xFF == ord('q'):  # 按 'q' 退出
        break
    elif key & 0xFF == ord(' '):  # 按空白鍵暫停
        pause = not pause

cap.release()
cv2.destroyAllWindows()
