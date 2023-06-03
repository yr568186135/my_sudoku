#include <iostream>
#include <fstream>

bool check(int shudu[9][9], int n, int m)
{
    int row[9] = { 0 };
    int col[9] = { 0 };
    int block[9] = { 0 };

    for (int i = 0; i < 9; i++)
    {
        if (shudu[n][i] != 0 && row[shudu[n][i] - 1] == 0)
        {
            row[shudu[n][i] - 1] = 1;
        }
        else if (shudu[n][i] != 0 && row[shudu[n][i] - 1] == 1)
        {
            return false;
        }

        if (shudu[i][m] != 0 && col[shudu[i][m] - 1] == 0)
        {
            col[shudu[i][m] - 1] = 1;
        }
        else if (shudu[i][m] != 0 && col[shudu[i][m] - 1] == 1)
        {
            return false;
        }

        int start_row = (n / 3) * 3;
        int start_col = (m / 3) * 3;

        if (shudu[start_row + i / 3][start_col + i % 3] != 0 && block[shudu[start_row + i / 3][start_col + i % 3] - 1] == 0)
        {
            block[shudu[start_row + i / 3][start_col + i % 3] - 1] = 1;
        }
        else if (shudu[start_row + i / 3][start_col + i % 3] != 0 && block[shudu[start_row + i / 3][start_col + i % 3] - 1] == 1)
        {
            return false;
        }
    }

    return true;
}

bool backtrace(int shudu[9][9], int n, int m)
{
    if (n == 9)
    {
        return true; // 解数独完成
    }

    if (shudu[n][m] != 0)
    {
        if (m == 8)
        {
            if (backtrace(shudu, n + 1, 0))
            {
                return true;
            }
        }
        else
        {
            if (backtrace(shudu, n, m + 1))
            {
                return true;
            }
        }
    }
    else
    {
        for (int i = 1; i <= 9; i++)
        {
            shudu[n][m] = i;
            if (check(shudu, n, m))
            {
                if (m == 8)
                {
                    if (backtrace(shudu, n + 1, 0))
                    {
                        return true;
                    }
                }
                else
                {
                    if (backtrace(shudu, n, m + 1))
                    {
                        return true;
                    }
                }
            }
            shudu[n][m] = 0;
        }
    }

    return false;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    int shudu[9][9];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            inputFile >> shudu[i][j];
        }
    }

    inputFile.close();

    if (backtrace(shudu, 0, 0))
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                outputFile << shudu[i][j] << " ";
            }
            outputFile << std::endl;
        }
    }

    outputFile.close();

    return 0;
}
