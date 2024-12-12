import os
import cv2
import random
from ultralytics import YOLO
from tracker import Tracker


# 初始化影片輸入與輸出
def initialize_video(video_path, output_path):
    # 加載輸入影片
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        raise FileNotFoundError(f"Error: Unable to open video at {video_path}")

    # 讀取影片第一幀，ret 表示影片讀取成功與否，frame 為影片幀的數據
    ret, frame = cap.read()
    if not ret:
        raise RuntimeError("Error: Unable to read the first frame from the video.")

    # 設置輸出影片
    fps = cap.get(cv2.CAP_PROP_FPS) or 30
    frame_size = (frame.shape[1], frame.shape[0])
    out = cv2.VideoWriter(output_path, cv2.VideoWriter_fourcc(*'mp4v'), fps, frame_size)
    if not out.isOpened():
        raise RuntimeError("Error: Unable to initialize VideoWriter.")

    return cap, out, frame


# 使用 YOLO 模型偵測物件並過濾低於 threshold 的結果
def detect_objects(model, frame, threshold):
    results = model(frame)  # results 是一個列表，每個 element 對應於一個偵測結果，包含多個偵測框的資訊
    detections = [
        info[:5]  # 提取 [x1, y1, x2, y2, score]
        for result in results for info in result.boxes.data.tolist() if info[4] > threshold  # 置信度過濾
    ]

    return detections


# 生成指定數量的隨機顏色，用於區分追蹤物件
def generate_colors(num_colors):
    return [(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)) for _ in range(num_colors)]


# 主程式：處理影片並進行物件偵測與追蹤
def main(video_path, video_out_path):
    #  初始化
    capture, capture_out, frame = initialize_video(video_path, video_out_path)
    detection_threshold = 0.3
    model = YOLO("yolov8n.pt")
    tracker = Tracker()
    colors = generate_colors(100)

    # 處理影片
    while True:
        # 物件偵測與追蹤更新
        detections = detect_objects(model, frame, detection_threshold)
        tracker.update(frame, detections)

        # 在每幀上繪製追蹤框
        for track in tracker.tracks:
            bbox = track.bbox
            x1, y1, x2, y2 = bbox
            track_id = track.track_id
            cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), colors[track_id % len(colors)], 3)

        # 顯示處理後的影片
        cv2.imshow('frame', frame)
        if cv2.waitKey(200) & 0xFF == ord('q'):  # 按 'q' 會退出
            break

        # 輸出處理後的影片
        capture_out.write(frame)

        # 讀取下一幀
        ret, frame = capture.read()
        if not ret:
            break

    # 釋放資源
    capture.release()
    capture_out.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    video_path = './data/input/video5.mp4'
    video_out_path = './data/output/out5.mp4'
    main(video_path, video_out_path)
