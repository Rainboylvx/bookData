---
title: 「USACO_2014铜」Cow_art
date: 2019-07-29 16:55
update: 2019-07-29 16:55
author: Rainboy
cover: https://s2.ax1x.com/2019/07/29/e3XAg0.png
---

## 解析

这个问题涉及到运行一个$flood fill$算法来访问每个区域，将其标记为已访问，直到所有区域都被访问和计数。在下面的代码中，我使用递归的“深度优先”搜索来填充每个连续的区域。函数的作用是:将一个单元格标记为被访问的单元格，然后递归地访问属于同一区域的所有相邻单元格。

## 代码
```c
#include <iostream>
#include <fstream>
#include <string>
#define MAX_N 100
using namespace std;

string A[MAX_N];
int N;
bool valid[256][256];
bool visited[MAX_N][MAX_N];

void visit(int i, int j)
{
    if (visited[i][j]) return;
    visited[i][j] = true;
    if (i > 0   && valid[A[i-1][j]][A[i][j]]) visit(i-1, j);
    if (j > 0   && valid[A[i][j-1]][A[i][j]]) visit(i, j-1);
    if (i < N-1 && valid[A[i+1][j]][A[i][j]]) visit(i+1, j);
    if (j < N-1 && valid[A[i][j+1]][A[i][j]]) visit(i, j+1);
}

int solve(void)
{
    int count = 0;
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            visited[i][j] = false;
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            if (!visited[i][j]) {
	            count++;
	            visit(i,j);
            }
    return count;
}

int main(void)
{
    ifstream fin("cowart.in");
    fin >> N;
    for (int i=0; i<N; i++) fin >> A[i];
    fin.close();

    valid['R']['R'] = valid['G']['G'] = valid['B']['B'] = true;
    int regions_human = solve();
    valid['R']['G'] = valid['G']['R'] = true;
    int regions_cow = solve();

    ofstream fout("cowart.out");
    fout << regions_human << " " << regions_cow << "\n";
    fout.close();

    return 0;
}
```
