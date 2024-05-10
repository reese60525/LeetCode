#include <algorithm>
#include <iostream>
#include <string>

// 若num1<num2，sign則會為true，反之為false。
bool compare(const std::string &num1, const std::string &num2) {
    if (num1.length() > num2.length()) {
        return false;
    }
    else if (num1.length() < num2.length()) {
        return true;
    }
    else {
        for (int i = 0; i < num1.length(); ++i) { // 若是num1和num2長度相同則一一比較每個bit的值
            if (num1[i] < num2[i]) {
                return true;
            }
            else if (num1[i] > num2[i]) {
                return false;
            }
        }
    }
    return false; // num1 == num2的話就會到這邊，把sign設為false代表相減不為負
}

// 加法
std::string add(std::string num1, std::string num2) {
    if (compare(num1, num2)) // 比較num1和num2大小，讓num1>=num2，方便後面計算
        std::swap(num1, num2);
    int index1 = num1.length(), index2 = num2.length(), carry = 0; // carry代表進位，bit相加結果>9為1，反之carry為0
    std::string ans = "";

    while (index1 > 0 || index2 > 0) { // num1和num1都從尾端開始相加
        --index1, --index2;
        int n = num1[index1] - '0' + carry;
        if (index2 > -1) { // 由於在while()前呼叫compare()和std::swap，因此num1必>=num2，若num2加完了就不再加
            n += num2[index2] - '0';
        }
        carry = n / 10;
        n %= 10;
        ans += (n + '0');
    }
    if (carry > 0) // 處理 999 + 1 = "1"000 這種進位問題
        ans += '1';

    reverse(ans.begin(), ans.end()); // ans是最小bit先存入，所以答案要反序輸出
    return ans;
}

// 減法
std::string sub(std::string num1, std::string num2) {
    bool is_negative = compare(num1, num2); // 用以判斷相減是否為負
    if (is_negative)                        // 比較num1和num2大小，讓num1>=num2，方便後面計算
        std::swap(num1, num2);
    int index1 = num1.length(), index2 = num2.length(), carry = 0; // carry代表進位，bit相減結果<0為-1，反之carry為0
    std::string ans = "";

    while (index1 > 0 || index2 > 0) { // num1和num1都從尾端開始相減
        --index1, --index2;
        int n = num1[index1] - '0' + carry;
        if (index2 > -1) { // 由於在while()前呼叫compare()和std::swap，因此num1必>=num2，若num2減完了就不再減
            n -= num2[index2] - '0';
        }
        if (n < 0) { // 當前bit相減為負，要向前借位
            carry = -1;
            n += 10;
        }
        else {
            carry = 0; // 當前bit相減為正，不用借位
        }
        ans += (n + '0');
    }
    reverse(ans.begin(), ans.end());         // ans是最小bit先存入，所以答案要反序輸出
    for (int i = 0; i < ans.length(); ++i) { // 處理開頭的0，像是00021354要變成21354
        if (ans[i] != '0') {                 // 遇到不為0時，把前面的0全消除掉
            ans.erase(0, i);
            break;
        }
        else if (i == ans.length() - 1) // 若全部為0則輸出單個0，像是000000000要輸出0
            return "0";
    }
    if (is_negative) // 原本的num1-num2為負數，開頭加個負號
        ans = '-' + ans;
    return ans;
}

// 乘法，用長乘法計算，以多次呼叫add()完成
std::string mul(std::string num1, std::string num2) {
    std::string ans = "";
    for (int i = num2.length() - 1; i > -1; --i) { // 從除數(num2)的最後一bit開始，
        for (int j = 0; j < num2[i] - '0'; ++j) {  // 累加num2[i]次num1
            // 由於每次進入add()都會呼叫compare()和std::swap()，讓add()中的num1>=num2，為了不讓mul()中的num1被更改值，所以用temp來代替num1進入add()
            std::string temp = num1;
            ans = add(ans, temp);
        }
        num1 += "0"; // 每做完一輪相加後，被乘數要往左1bit，也就是乘以10
    }
    return ans; // 由於是透過多次呼叫add()來完成長乘法，add()返回的string已經有reverse了，所以這邊可以直接輸出ans
}

// 除法，用長除法計算，以多次呼叫sub()完成
std::string div(std::string num1, std::string num2) {
    if (compare(num1, num2)) // 若輸入的num1<num2直接return 0
        return "0";
    // index用以計算num1的index，假設num1 = 1234，num2 = 11，一開始now = ""，index = 0，
    // 接下來now累加num1[index]變成1，index + 1，拿去和num2比較，若比num2小則繼續累加num1[index]，
    // 此時now = 12，拿去後num2比較，傳回來的sign為false代表num1>=num2，就可以進行相減，12 - 11 = 1
    // ，now = 1，這時ans_count + 1，再拿now = 1去和num2 = 11比較，發現比除數小，因此把ans_count放
    // 入ans中，然後now累加num1[index]，以此一直重複到num1被累加完所有bit。
    int index = 0, ans_count = 0; // index是num1的index，一開始為0，隨著每次分配最左邊的bit給now，index會加1
    std::string ans = "", now = "";
    while (true) {
        if (compare(now, num2)) { // 進行比較，若sign為true代表now(被除數) < num2(除數)，要累加1個num1最左邊的bit給now
            ans += ans_count + '0'; // 把上次相減的次數(也就是商)加進ans中，由於一開始now為""，所以會有數個0開頭
            ans_count = 0;          // 重置ans_count
            if (index == num1.length()) // 若num1的bit都被累加完，則跳出while迴圈
                break;
            now += num1[index]; // 讓now累加num1最左邊的bit
            ++index;            // 累加後num1的index往右移
        }
        else {
            ++ans_count;          // 每次相減後都加1
            now = sub(now, num2); // now = 相減後的結果
            if (now == "0")       // 若是相減剛好為0，則把now設為""
                now = "";
        }
    }
    for (int i = 0; i < ans.length(); ++i) { // 消除開頭的0，例如:000123要變成123
        if (ans[i] != '0') {
            ans.erase(0, i);
            break;
        }
    }
    return ans; // 由於是透過多次呼叫sub()來完成長乘法，sub()返回的string已經有reverse了，所以這邊可以直接輸出ans
}

int main() {
    char op;
    std::string num1, num2;
    while (std::cin >> num1 >> op >> num2) {
        if (op == '+')
            std::cout << add(num1, num2) << '\n';
        else if (op == '-')
            std::cout << sub(num1, num2) << '\n';
        else if (op == '*')
            std::cout << mul(num1, num2) << '\n';
        else if (op == '/')
            std::cout << div(num1, num2) << '\n';
    }
    return 0;
}