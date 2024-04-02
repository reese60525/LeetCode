#include <iostream>
#include <vector>
using namespace std;

int fun(vector<int> input_number, vector<char> input_operator)
{
    bool check[2] = {true, true};

    // // 測試
    // cout << "*******************TEST 1*******************";
    // cout << "\r\nnumber:\r\n";
    // for (int i = 0; i < input_number.size(); ++i)
    //     cout << input_number[i] << ", ";
    // cout << "\r\noperator:\r\n";
    // for (int i = 0; i < input_operator.size(); ++i)
    //     cout << input_operator[i] << ", ";
    // cout << "\r\nnum.size= " << input_number.size() << endl;
    // cout << "op.size= " << input_operator.size() << endl;
    // cout << "*******************TEST 1*******************" << endl;
    // // 測試

    // 處理括號
    while (check[0] && input_operator.size() > 0 && input_number.size() > 0)
    {
        int count_num = -1, count_op = -1;
        for (int i = 0; i < input_operator.size(); ++i)
        {
            if (input_operator[i] == ')')
            {
                if (input_operator[count_op] == '+')
                    input_number[count_num] += input_number[count_num + 1];
                else if (input_operator[count_op] == '-')
                    input_number[count_num] -= input_number[count_num + 1];
                else if (input_operator[count_op] == '*')
                    input_number[count_num] *= input_number[count_num + 1];
                else if (input_operator[count_op] == '/')
                    input_number[count_num] /= input_number[count_num + 1];
                input_number.erase(input_number.begin() + count_num + 1);
                input_operator.erase(input_operator.begin() + count_op - 1);
                input_operator.erase(input_operator.begin() + count_op - 1);
                input_operator.erase(input_operator.begin() + count_op - 1);
                break;
            }
            else if (input_operator[i] == '+' || input_operator[i] == '-' || input_operator[i] == '*' || input_operator[i] == '/')
            {
                ++count_num;
                ++count_op;
            }
            else if (input_operator[i] == '(')
                ++count_op;
            if (i == input_operator.size() - 1)
                check[0] = false;
        }
    }

    // // 測試
    // cout << "*******************TEST 2*******************";
    // cout << "\r\nnumber:\r\n";
    // for (int i = 0; i < input_number.size(); ++i)
    //     cout << input_number[i] << ", ";
    // cout << "\r\noperator:\r\n";
    // for (int i = 0; i < input_operator.size(); ++i)
    //     cout << input_operator[i] << ", ";
    // cout << "\r\nnum.size= " << input_number.size() << endl;
    // cout << "op.size= " << input_operator.size() << endl;
    // cout << "*******************TEST 2*******************" << endl;
    // // 測試

    // 處理 */
    while (check[1] && input_operator.size() > 0 && input_number.size() > 0)
    {
        int count_num = 0, count_op = 0;
        for (int i = 0; i < input_operator.size(); ++i)
        {
            if (input_operator[i] == '*' || input_operator[i] == '/')
            {
                // cout << "\r\nTEST2:i= " << i << ", count_num= " << count_num << ", count_op= " << count_op << endl;
                // cout << input_number[count_num] << input_operator[i] << input_number[count_num + 1] << endl;

                if (input_operator[i] == '*')
                    input_number[count_num] *= input_number[count_num + 1];
                else if (input_operator[i] == '/')
                    input_number[count_num] /= input_number[count_num + 1];

                input_number.erase(input_number.begin() + count_num + 1);
                input_operator.erase(input_operator.begin() + count_op);

                // cout << "\r\nTEST3:i= " << i << ", count_num= " << count_num << ", count_op= " << count_op << endl;
                // cout << "num.size= " << input_number.size() << endl;
                // cout << "op.size= " << input_operator.size() << endl;

                break;
            }
            else if (input_operator[i] == '+' || input_operator[i] == '-')
            {
                ++count_num;
                ++count_op;
            }
            if (i == input_operator.size() - 1)
                check[1] = false;
        }
    }

    // // 測試
    // cout << "*******************TEST 3*******************";
    // cout << "\r\nnumber:\r\n";
    // for (int i = 0; i < input_number.size(); ++i)
    //     cout << input_number[i] << ", ";
    // cout << "\r\noperator:\r\n";
    // for (int i = 0; i < input_operator.size(); ++i)
    //     cout << input_operator[i] << ", ";
    // cout << "\r\nnum.size= " << input_number.size() << endl;
    // cout << "op.size= " << input_operator.size() << endl;
    // cout << "*******************TEST 3*******************" << endl;
    // // 測試

    // 處理+-

    // Segmentation Fault.
    // cout << "1. op.size= " << input_operator.size() << endl;
    // while (input_operator.size() > 0 && input_number.size() > 0)
    // {
    //     cout << "2. op.size= " << input_operator.size() << endl;
    //     if (input_operator[0] == '+')
    //         input_number[0] += input_number[1];
    //     else if (input_operator[0] == '-')
    //         input_number[0] -= input_number[1];
    //     input_number.erase(input_number.begin() + 1);
    //     input_operator.erase(input_operator.begin());
    //     cout << "3. op.size= " << input_operator.size() << endl;

    //     if (input_operator.size() == 0)
    //         break;
    //     cout << "break; 後" << endl;
    // }
    // cout << "4. op.size= " << input_operator.size() << endl;

    for (int i = 0; i < input_operator.size(); ++i)
    {
        if (input_operator[0] == '+')
            input_number[0] += input_number[1];
        else if (input_operator[0] == '-')
            input_number[0] -= input_number[1];
        input_number.erase(input_number.begin() + 1);
        input_operator.erase(input_operator.begin());
    }

    // // 測試
    // cout << "*******************TEST 4*******************";
    // cout << "\r\nnumber:\r\n";
    // for (int i = 0; i < input_number.size(); ++i)
    //     cout << input_number[i] << ", ";
    // cout << "\r\noperator:\r\n";
    // for (int i = 0; i < input_operator.size(); ++i)
    //     cout << input_operator[i] << ", ";
    // cout << "\r\nnum.size= " << input_number.size() << endl;
    // cout << "op.size= " << input_operator.size() << endl;
    // cout << "*******************TEST 4*******************" << endl;
    // // 測試

    return input_number[0];
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);
    string input;
    while (getline(cin, input))
    {
        vector<char> input_operator;
        vector<int> input_number;
        int num = 0;
        bool check = false;
        for (int i = 0; i < input.length(); ++i)
        {
            if (input[i] - 48 >= 0 && input[i] - 48 <= 9)
            {
                num = num * 10 + (input[i] - 48);
                check = true;
                if (i == input.length() - 1)
                    input_number.push_back(num);
            }
            else if (check)
            {
                input_number.push_back(num);
                num = 0;
                check = false;
            }
            if (input[i] != ' ' && input[i] < '0' || input[i] > '9')
                input_operator.push_back(input[i]);
        }
        cout << fun(input_number, input_operator) << endl;
    }
    return 0;
}