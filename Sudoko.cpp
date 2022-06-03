#include <bits/stdc++.h>
using namespace std;
class Sudoko
{
private:
    bool flag = false;
    int a[82];
    int getRow(int);                              // OVER
    int getColumn(int);                           // OVER
    unordered_set<int> getRowElements(int);       // OVER
    unordered_set<int> getColElements(int);       // OVER
    unordered_set<int> getGridElements(int, int); // OVER
    vector<int> getUnfilledElements(int);         // OVER
    void fill(int);                               // OVER
public:
    Sudoko(vector<string> &A);       // OVER
    void convert(vector<string> &A); // OVER
};

class Solution
{
private:
    vector<string> A;

public:
    void readSudoko_CustomInput();
    void readSudoko_SampleInput();
    void display();
    void solveSudoku();
};

int main()
{
    Solution obj = Solution();
    obj.readSudoko_SampleInput();
    obj.solveSudoku();
    obj.display();
    return 0;
}

Sudoko::Sudoko(vector<string> &A)
{
    int p = 1;
    for (auto x : A)
    {
        for (auto y : x)
        {
            if (y != '.')
                a[p] = y - '0';
            else
                a[p] = -1;
            ++p;
        }
    }
}
int Sudoko::getRow(int N)
{
    return (N % 9 == 0) ? (N / 9) : (N / 9 + 1);
}
int Sudoko::getColumn(int N)
{
    return (N % 9 == 0) ? 9 : (N % 9);
}
unordered_set<int> Sudoko::getRowElements(int row)
{
    unordered_set<int> s;
    for (int i = 1; i <= 9; i++)
        s.insert(i);
    for (int i = (row - 1) * 9 + 1; i <= row * 9; i++)
    {
        if (a[i] > 0)
            s.erase(a[i]);
    }
    return s;
}
unordered_set<int> Sudoko::getColElements(int col)
{
    unordered_set<int> s;
    for (int i = 1; i <= 9; i++)
        s.insert(i);
    for (int i = col; i <= 81; i += 9)
    {
        if (a[i] > 0)
            s.erase(a[i]);
    }
    return s;
}
unordered_set<int> Sudoko::getGridElements(int row, int col)
{
    unordered_set<int> s;
    int row1, row2, col1, col2;
    row1 = (row % 3 == 0) ? (row - 2) : (row / 3 * 3 + 1);
    row2 = (row % 3 == 0) ? row : ((row / 3 + 1) * 3);
    col1 = (col % 3 == 0) ? (col - 2) : (col / 3 * 3 + 1);
    col2 = (col % 3 == 0) ? col : ((col / 3 + 1) * 3);

    for (int i = 1; i <= 9; i++)
        s.insert(i);
    for (int i = row1; i <= row2; i++)
    {
        for (int j = col1; j <= col2; j++)
        {
            int idx = (i - 1) * 9 + j;
            if (a[idx] > 0)
                s.erase(a[idx]);
        }
    }
    return s;
}
vector<int> Sudoko::getUnfilledElements(int N)
{
    int row, col;
    row = getRow(N);
    col = getColumn(N);
    unordered_set<int> ROW = getRowElements(row);
    unordered_set<int> COL = getColElements(col);
    unordered_set<int> GRID = getGridElements(row, col);
    vector<int> res;
    for (int x : ROW)
    {
        if (COL.count(x) && GRID.count(x))
            res.push_back(x);
    }
    return res;
}
void Sudoko::fill(int idx)
{
    if (idx == 82)
    {
        flag = true;
        return;
    }
    if (a[idx] > 0)
    {
        fill(idx + 1);
        return;
    }

    vector<int> v = getUnfilledElements(idx);
    if (v.size() == 0)
        return;
    for (int x : v)
    {
        a[idx] = x;
        fill(idx + 1);
        if (flag)
            return;
        a[idx] = -1;
    }
}
void Sudoko::convert(vector<string> &A)
{
    fill(0);
    int p = 1;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < 9; j++)
        {
            A[i][j] = a[p++] + '0';
        }
    }
}

void Solution::readSudoko_SampleInput()
{
    A = {"53..7....", "6..195...", ".98....6.", "8...6...3", "4..8.3..1", "7...2...6", ".6....28.", "...419..5", "....8..79"};
}

void Solution::solveSudoku()
{
    Sudoko s(A);
    s.convert(A);
}

void Solution::display()
{
    for (auto s : A)
    {
        for (char c : s)
            cout << c << setw(3);
        cout << "\n";
    }
}