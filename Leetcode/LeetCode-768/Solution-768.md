# <center> [LeetCode - 768. Max Chunks To Make Sorted II](https://leetcode.com/problems/max-chunks-to-make-sorted-ii/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412191435756.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412191435756.png)

給一個 integer array `arr`，將其進行以下操作:  

1. 將 `arr` 分割成一個或多個 subarray  
2. 對每個 subarray 進行排序  
3. 將每個 subarray 合併成一個 sorted array
4. 合併後的 sorted array 必須是**非遞減排序**  

請找出經過以上操作後，subarray 所能達到的最大數量。  

e.g.  

`arr` = {1, 2, 3, 1, 1, 2, 3, 4, 3}
    - 可以將 `arr` 分隔成 {{1}, {2, 3, 1, 1, 2}, {3}, {4, 3}}，排序後變成 {{1}, {1, 1, 2, 2, 3}, {3}, {3, 4}}，合併後為 {1, 1, 1, 2, 2, 3, 3, 3, 4}，subarray 數量為 4。  
    - 可以將 `arr` 分隔成 {{1, 2, 3, 1, 1, 2, 3}, {4, 3}}，排序後變成 {{1, 1, 1, 2, 2, 3, 3}, {3, 4}}，合併後為 {1, 1, 2, 2, 3, 3, 3, 4}，subarray 數量為 2。
    - 以此類推...可以得到 subarray 最大數量為 4。

## 解題思路

### Monotonic Stack
