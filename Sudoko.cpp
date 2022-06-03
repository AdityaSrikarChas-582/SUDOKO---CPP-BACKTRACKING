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
    bool isValid();                  // OVER
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
    cout << "-------------------------------------------------------\n";
    cout << "\t1. Sample Input\n";
    cout << "\t2. Custom Input\n";
    cout << "Choose an Option : ";
    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
        obj.readSudoko_SampleInput();
        break;
    case 2:
        obj.readSudoko_CustomInput();
        break;
    }
    obj.solveSudoku();
    obj.display();
    cout << "-------------------------------------------------------\n";
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

bool Sudoko::isValid()
{
    // check rows
    for (int i = 1; i < 82; i += 9)
    {
        unordered_set<int> s;
        for (int j = i; j < i + 9; j++)
        {
            if (!s.count(a[j]))
                s.insert(a[j]);
            else
                return false;
        }
    }

    // check columns
    for (int i = 1; i < 10; i++)
    {
        unordered_set<int> s;
        for (int j = 0; i + j < 82; j += 9)
        {
            if (!s.count(a[i + j]))
                s.insert(a[i + j]);
            else
                return false;
        }
    }

    // check grid-1
    unordered_map<int, int> mp;
    mp[a[1]]++;
    mp[a[2]]++;
    mp[a[3]]++;
    mp[a[10]]++;
    mp[a[11]]++;
    mp[a[12]]++;
    mp[a[19]]++;
    mp[a[20]]++;
    mp[a[21]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-2
    mp[a[4]]++;
    mp[a[5]]++;
    mp[a[6]]++;
    mp[a[13]]++;
    mp[a[14]]++;
    mp[a[15]]++;
    mp[a[22]]++;
    mp[a[23]]++;
    mp[a[24]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-3
    mp[a[7]]++;
    mp[a[8]]++;
    mp[a[9]]++;
    mp[a[16]]++;
    mp[a[17]]++;
    mp[a[18]]++;
    mp[a[25]]++;
    mp[a[26]]++;
    mp[a[27]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-4
    mp[a[28]]++;
    mp[a[29]]++;
    mp[a[30]]++;
    mp[a[37]]++;
    mp[a[38]]++;
    mp[a[39]]++;
    mp[a[46]]++;
    mp[a[47]]++;
    mp[a[48]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-5
    mp[a[31]]++;
    mp[a[32]]++;
    mp[a[33]]++;
    mp[a[40]]++;
    mp[a[41]]++;
    mp[a[42]]++;
    mp[a[49]]++;
    mp[a[50]]++;
    mp[a[51]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-6
    mp[a[34]]++;
    mp[a[35]]++;
    mp[a[36]]++;
    mp[a[43]]++;
    mp[a[44]]++;
    mp[a[45]]++;
    mp[a[52]]++;
    mp[a[53]]++;
    mp[a[54]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-7
    mp[a[55]]++;
    mp[a[56]]++;
    mp[a[57]]++;
    mp[a[64]]++;
    mp[a[65]]++;
    mp[a[66]]++;
    mp[a[73]]++;
    mp[a[74]]++;
    mp[a[75]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-8
    mp[a[58]]++;
    mp[a[59]]++;
    mp[a[60]]++;
    mp[a[67]]++;
    mp[a[68]]++;
    mp[a[69]]++;
    mp[a[76]]++;
    mp[a[77]]++;
    mp[a[78]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    // check grid-9
    mp[a[61]]++;
    mp[a[62]]++;
    mp[a[63]]++;
    mp[a[70]]++;
    mp[a[71]]++;
    mp[a[72]]++;
    mp[a[79]]++;
    mp[a[80]]++;
    mp[a[81]]++;
    for (auto p : mp)
        if (p.second > 1)
            return false;
    mp.clear();

    return true;
}

void Solution::readSudoko_SampleInput()
{
    A = {"53..7....", "6..195...", ".98....6.", "8...6...3", "4..8.3..1", "7...2...6", ".6....28.", "...419..5", "....8..79"};
}

void Solution::readSudoko_CustomInput()
{
    cout << "Enter Sudoko Configuration as string\n";
    cout << "Each string represents a line\n";
    cout << "If that position is not filled, place a dot\n";
    cout << "If that position if filled, place the digit\n";
    cin.ignore();
    for (int i = 0; i < 9; i++)
    {
        string str;
        getline(cin, str);
        A.push_back(str);
    }
}

void Solution::solveSudoku()
{
    Sudoko s(A);
    s.convert(A);
    if (!s.isValid())
    {
        cout << "Sudoko not Valid\n";
        cout << "Solution not feasible..!";
    }
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