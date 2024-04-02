#include <iostream>
#include <map>
using namespace std;

int lengthOfLongestSubstring(string s)
{
    int count = 0, max = 0, j = 0;
    map<char, bool> m;
    for (int i = 0; i < s.length(); ++i)
    {
        if (m[s[j]] == true)
        {
            m[s[j]] = false;
            if (max < count)
                max = count;
        }
        else
        {
            m[s[j]] = true;
            ++count;
        }
    }
}

int main()
{
    // cin.sync_with_stdio(false); cin.tie(nullptr);

    return 0;
}