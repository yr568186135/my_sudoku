#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <ctime>

std::ofstream fp1, fp2;
int shudu_solve[9][9];  // ������
int shudu_template[9][9];  // ����ģ��
int Displacement[8] = { 1,2,3,4,5,6,7,9 };  // ����ģ��1���б任

// ����������Ƿ�Ψһ
bool isUniqueSolution()
{
    int count = 0;
    int row = 0, col = 0;

    // ����������
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (shudu_solve[row][col] == 0) {
                count++;
            }
        }
    }

    return (count == 81);  // ��������û�пո�Ψһ��
}

// ����ģ��任
int exchange(char shudu[][10], int Count, int N)
{
    int i, j, k, l;
    int random_row, random_col, random_num;
    int temp;
    char shudu_1[10][10];

    memcpy(shudu_1, shudu, sizeof(shudu_1));

    for (i = 0; i < N; i++)
    {
        random_row = rand() % 9;
        random_col = rand() % 9;
        random_num = rand() % 9 + 1;
        temp = shudu_1[random_row][random_col];
        shudu_1[random_row][random_col] = shudu_1[random_row][random_num];
        shudu_1[random_row][random_num] = temp;
    }

    for (i = 0; i < N; i++)
    {
        random_row = rand() % 9;
        random_col = rand() % 9;
        random_num = rand() % 9 + 1;
        temp = shudu_1[random_row][random_col];
        shudu_1[random_row][random_col] = shudu_1[random_num][random_col];
        shudu_1[random_num][random_col] = temp;
    }

    Count++;
    k = Count % 9;
    l = (Count + Count / 9) % 9;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            shudu[i][j] = shudu_1[(i + k) % 9][(j + l) % 9];
        }
    }
    return Count;
}

// ȫ������������ģ��1
void permutation(int* a, int k, int m, int* Count, int N)
{
    int i, j;

    if (k > m)
    {
        char shudu[10][10] = { {0} };
        for (i = 0; i < 9; i++)
        {
            shudu[i][i] = a[i] + '0';
        }

        for (i = 0; i < 720; i++)
        {
            for (j = 0; j < 9; j++)
            {
                shudu[(j + i) % 9][j] = a[j] + '0';
            }
            *Count = exchange(shudu, *Count, N);
        }

        return;
    }

    for (i = k; i <= m; i++)
    {
        std::swap(a[k], a[i]);
        permutation(a, k + 1, m, Count, N);
        std::swap(a[k], a[i]);
    }
}

// ��������ģ��1
void generateTemplate1(int N)
{
    int Count = 0;
    int a[9] = { 1,2,3,4,5,6,7,8,9 };

    permutation(a, 0, 8, &Count, N);
}

// ��������ģ��2
void generateTemplate2()
{
    srand(time(NULL));

    // ��������б任
    for (int i = 0; i < 8; i++) {
        std::swap(Displacement[i], Displacement[rand() % (i + 1)]);
    }

    // �����б任��������ģ��2
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            shudu_template[i][j] = shudu_template[Displacement[i] - 1][j];
        }
    }
}

// �����������������num�Ƿ�Ϸ�
bool isValid(int row, int col, int num)
{
    // ������Ƿ�Ϸ�
    for (int i = 0; i < 9; i++) {
        if (shudu_solve[row][i] == num)
            return false;
    }

    // ������Ƿ�Ϸ�
    for (int i = 0; i < 9; i++) {
        if (shudu_solve[i][col] == num)
            return false;
    }

    // ���С�Ź����Ƿ�Ϸ�
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (shudu_solve[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// �������
bool solveSudoku(int row, int col)
{
    if (col == 9) {
        col = 0;
        row++;
    }

    if (row == 9) {
        return true;  // ������ĩβ��������
    }

    if (shudu_solve[row][col] != 0) {
        return solveSudoku(row, col + 1);  // ��ǰλ���������֣�������һ��λ��
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            shudu_solve[row][col] = num;  // ��������
            if (solveSudoku(row, col + 1)) {
                return true;  // ���������һ��λ��
            }
            shudu_solve[row][col] = 0;  // ���ݣ���յ�ǰλ�õ�����
        }
    }

    return false;  // �޽�
}

// ��ӡ�������⵽�ļ�
void printPuzzleToFile(const char* filename)
{
    fp1.open(filename);

    if (fp1.is_open())
    {
        // ��ӡ��������
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                fp1 << shudu_template[i][j] << " ";
            }
            fp1 << std::endl;
        }

        fp1.close();
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }
}

// ��ӡ�����⵽�ļ�
void printSolutionToFile(const char* filename)
{
    fp2.open(filename);

    if (fp2.is_open())
    {
        // ��ӡ������
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                fp2 << shudu_solve[i][j] << " ";
            }
            fp2 << std::endl;
        }

        fp2.close();
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }
}

int main()
{
    srand(time(NULL));

    // ��������ģ��1
    generateTemplate1(10000);

    // ��������ģ��2
    generateTemplate2();

    // �������
    if (solveSudoku(0, 0))
    {
        // ��ӡ�������⵽�ļ�
        printPuzzleToFile("puzzle.txt");

        // ��ӡ�����⵽�ļ�
        printSolutionToFile("solution.txt");
    }
    else
    {
        std::cout << "No solution exists." << std::endl;
    }

    return 0;
}
