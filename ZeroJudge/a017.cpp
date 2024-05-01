#include <iostream>
#include <vector>
using namespace std;

void calculate(vector<int> &nums, char op) {
    if (op == '+')
        nums[nums.size() - 2] += nums[nums.size() - 1];
    if (op == '-')
        nums[nums.size() - 2] -= nums[nums.size() - 1];
    if (op == '*')
        nums[nums.size() - 2] *= nums[nums.size() - 1];
    if (op == '/')
        nums[nums.size() - 2] /= nums[nums.size() - 1];
    if (op == '%')
        nums[nums.size() - 2] %= nums[nums.size() - 1];
    nums.pop_back();
}

// 2 * ( ( 3 + 4 ) * 5 + 7 ) * 2

int main() {
    string input;
    while (getline(cin, input)) {
        vector<char> operators;
        vector<int> nums;
        int num = 0;
        bool check = false;
        for (int i = 0; i < input.length(); ++i) {
            // 數字處理
            if (input[i] - '0' >= 0 && input[i] - '0' <= 9) {
                check = true;
                num = num * 10 + (input[i] - '0');
                if (i == input.length() - 1)
                    nums.push_back(num);
            }
            else if (check) {
                nums.push_back(num);
                num = 0;
                check = false;
            }
            // 運算子處理
            if (input[i] == '(')
                operators.push_back('(');
            else if (input[i] == '*' || input[i] == '/' | input[i] == '%') {
                while (operators.size() > 0) {
                    char op = operators[operators.size() - 1];
                    if (op == '+' || op == '-' || op == '(')
                        break;
                    calculate(nums, op);
                    operators.pop_back();
                }
                operators.push_back(input[i]);
            }
            else if (input[i] == '+' || input[i] == '-' || input[i] == ')') {
                while (operators.size() > 0 && operators[operators.size() - 1] != '(') {
                    calculate(nums, operators[operators.size() - 1]);
                    operators.pop_back();
                }
                if (input[i] == ')')
                    operators.pop_back();
                else
                    operators.push_back(input[i]);
            }
        }
        // 2+3*4 會變成 : nums[2, 3, 4] , operators['+', '*']，要將剩下的處理完運算再輸出答案
        while (operators.size() > 0) {
            calculate(nums, operators[operators.size() - 1]);
            operators.pop_back();
        }
        cout << nums[0] << '\n';
    }
    return 0;
}