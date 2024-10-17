x, y = input("Enter 2 values separated by spaces:").split()
z = 55 - int(x)
# print(x,y,z)

if (z % 3 != 0):
    print(-1)
else:
    res = []
    z /= 3  # 每個人能分配到的資產總額
    for i in range(1, 10, 1):
        for j in range(2, 10, 1):
            if (i != int(x) and i != int(y) and j != int(x) and j != int(y) and i + j + int(y) == z):
                if not res:
                    res.append(i)
                    res.append(j)
                    res.append(int(y))
                    res.sort()
                else:
                    temp = [i, j, int(y)]
                    sorted(temp)
                    n1 = int(str(res[0]) + str(res[1]) + str(res[2]))
                    n2 = int(str(temp[0]) + str(temp[1]) + str(temp[2]))
                    if (n2 < n1):
                        res.append(i)
                        res.append(j)
                        res.append(int(y))
                        res.sort
    for e in res:
        print(e, end=' ')
