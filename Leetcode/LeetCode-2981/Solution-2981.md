# <center> [LeetCode - 2981. Find Longest Special Substring That Occurs Thrice I](https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412101114767.png)]((https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412101114767.png))

給一個只有小寫英文字母的字串 `s`，找出至少出現三次的最長 `special` substring 的長度，如果找不到則 return -1。

special substring 的定義：

- 字串中只包含同樣的字元，例如 "a"、"aaa"、"bbbbbbbb"。

e.g.

1. s = "aaaa"  
   - "a" 出現四次，長度為 1。
   - "aa" 出現三次，長度為 2。
   - "aaa" 出現兩次，長度為 3。
   - "aaaa" 出現一次，長度為 4。

    因此至少出現三次的最長 `special` substring 是 "aa"，長度為 2。

2. s = "abcd"  
   因為沒有任何 `special` substring 出現三次以上，所以 return -1。

3. s = "abcaba"  
   - "a" 出現三次，長度為 1。

   因此至少出現三次的最長 `special` substring 是 "a"，長度為 1。

## 解題思路

1. Sliding Window and Hash Map
