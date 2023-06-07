#include <stdio.h>
#include <tchar.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include<fstream>
using namespace std;
FILE* fp1, * fp2;
errno_t err1 = fopen_s(&fp1, "shudu.txt", "w");//shudu.txt ��������վ�
errno_t err2 = fopen_s(&fp2, "solve.txt", "w");//solve.txt ��������Ľ�
int shudu_solve[9][9];
int Displacement[9] = { 3,6,1,4,7,2,5,8 };//λ����
struct NODE1
{
	int n, m;
}node1[4] = { { 0,0 },{ 2,3 },{ 2,4 },{ 3,4 } };//�����������м����е�λ��
struct NODE2
{
	int n, m;
}node2[4] = { { 0,0 },{ 5,6 },{ 5,7 },{ 6,7 } };//�������������е�λ��
//������ģ��1�Ļ����϶�������������֮��Ľ�����4~6,7~9��֮���������еĽ�����
int exchange(char shudu_1[10][10], int Count, int N)
{
	int x, y;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 6; x++)
		{
			if (!x && !y);
			else if (Count < N)
			{
				swap(Displacement[node1[x].n], Displacement[node1[x].m]);
				swap(Displacement[node2[y].n], Displacement[node1[y].m]);
				int k = 0;
				for (int i = 0; i < 9; i++)
				{
					if (k)
					{
						for (int j = 0; j < 9; j++)
						{
							shudu_1[k][(j + Displacement[i - 1]) % 9] = shudu_1[0][j];
						}
					}
					for (int z = 0; z < 9; z++)
					{
						if (z) fputc(' ', fp1);
						fputc(shudu_1[k][z], fp1);
					}
					fputc('\n', fp1);
					k++;
				}
				fputc('\n', fp1);
				swap(Displacement[node1[x].n], Displacement[node1[x].m]);
				swap(Displacement[node2[y].n], Displacement[node1[y].m]);
				Count++;
			}
		}
	}
	return Count;
}
//��������һ�н���ȫ���У�����8���֣���������ģ��1
void permutation(int* a, int k, int m, int* Count, int N)
{
	char shudu[10][10];
	memset(shudu, 0, sizeof(shudu));
	int b[8], i, j;
	if (k == m)
	{
		if (*Count < N)
		{
			for (i = 0; i <= m; i++)
			{
				b[i] = a[i];
			}
			*Count += 1;
			int k = 0, l = 0;
			shudu[0][0] = '3';
			for (i = 0; i < 8; i++)
			{
				shudu[0][i + 1] = b[i] + '0';
			}
			//�ֱ�������һ������3��6��1��4��7��2��5��8�еõ��ڶ�������
			for (i = 0; i < 9; i++)
			{
				if (k)
				{
					for (l = 0; l < 9; l++)
					{
						shudu[k][(l + Displacement[i - 1]) % 9] = shudu[0][l];
					}
				}
				for (j = 0; j < 9; j++)
				{
					if (j) fputc(' ', fp1);
					fputc(shudu[k][j], fp1);
				}
				fputc('\n', fp1);
				k++;
			}
			fputc('\n', fp1);
			char shudu_1[10][10];
			strncpy_s(shudu_1[0], sizeof(shudu_1), shudu[0], sizeof(shudu));
			*Count = exchange(shudu_1, *Count, N);
		}
	}
	else
	{
		for (j = k; j <= m; j++)
		{
			swap(a[j], a[k]);
			permutation(a, k + 1, m, Count, N);
			swap(a[j], a[k]);
		}
	}
}
//���������վֵĺ���shudu_create��NΪ���������վ���
void shudu_create(int N)
{
	int a[] = { 1,2,3,4,6,7,8,9 }, len = 8;
	int Count = 0;
	permutation(a, 0, len - 1, &Count, N);
	fclose(fp1);
}

//�������ģ����������Լ��Ź����⣬�ж��Ƿ�Ϸ�
bool check(int Count)
{
	int x = Count / 9;//��ǰ��λ��
	int y = Count % 9;//��ǰ��λ��
	int i;
	//ÿ�ж�Ҫ��1~9��ÿһ������ֻ�ܴ���һ��
	for (i = 0; i < 9; i++)
	{
		if (shudu_solve[x][y] == shudu_solve[x][i] && i != y) return false;
	}
	//ÿ�ж�Ҫ��1~9��ÿһ������ֻ�ܴ���һ��
	for (i = 0; i < 9; i++)
	{
		if (shudu_solve[x][y] == shudu_solve[i][y] && i != x) return false;
	}
	//ÿ���Ź���Ҫ��1~9��ÿһ������ֻ�ܴ���һ��
	int xx = x / 3 * 3, yy = y / 3 * 3;
	for (i = xx; i < xx + 3; ++i)
	{
		for (int j = yy; j < yy + 3; ++j)
		{
			if (shudu_solve[i][j] == shudu_solve[x][y] && i != x && j != y) return false;
		}
	}
	return true;
}
//ͨ�����ݷ��������
void backtrace(int Count)
{
	if (Count == 81)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				fputc((char)(shudu_solve[i][j] + '0'), fp2);
				fputc(' ', fp2);
			}
			fputc('\n', fp2);
		}
		fputc('\n', fp2);
		return;
	}
	int x = Count / 9, y = Count % 9;
	if (shudu_solve[x][y] == 0)
	{
		for (int i = 1; i <= 9; i++)
		{
			shudu_solve[x][y] = i;
			if (check(Count))
				backtrace(Count + 1);
		}
		shudu_solve[x][y] = 0;
	}
	else
		backtrace(Count + 1);
}

void shudu_Solve(char* c)
{
	FILE* fp3;
	errno_t err3 = fopen_s(&fp3, c, "r");//����������
	if (fp3 == NULL)
		cout << "Path is error";
	else
	{
		int i, j;
		while (fscanf_s(fp3, "%d", &shudu_solve[0][0]) != EOF)
		{
			for (i = 0; i < 9; i++)
			{
				for (j = 0; j < 9; j++)
				{
					if (i == 0 && j == 0)
						continue;
					else
						fscanf_s(fp3, "%d", &shudu_solve[i][j]);
				}
			}
			backtrace(0);
			memset(shudu_solve, 0, sizeof(shudu_solve));
		}
	}
}
//�������
int ArgCheck(char* argv)
{
	int num = 0;
	int len = strlen(argv);
	for (int i = 0; i < len; i++)
	{
		if (!(argv[i] >= '0' && argv[i] <= '9'))
			return -1;
		else
			num = num * 10 + (int)(argv[i] - '0');
	}

	return num;
}

int main(int argc, char* argv[])
{

	char c[3] = { 0 }, s[3] = { 0 };
	c[0] = '-', c[1] = 'c';
	s[0] = '-', s[1] = 's';
	if (argc == 3)
	{
		if (!strcmp(argv[1], "-c"))
		{
			int num = ArgCheck(argv[2]);
			if (num == -1)
				cout << "����Ĳ�����Ϣ�������飡";
			else {
				shudu_create(num);
				cout << "�ѳɹ�����" << num << "�������վֵ�shudu.txt��" << endl;
			}
		}
		else if (!strcmp(argv[1], s)) {
			shudu_Solve(argv[2]);
			cout << "�ѳɹ��������Ľ������solve.txt��" << endl;
		}
	}
	else {
		cout << "����ָ���������ڿ���̨ʹ����ȷ��ָ�������г���" << endl;
		cout << "����������shudu.exe -c N��������N�������վ��ļ���shudu.txt��" << endl;
		cout << "����������shudu.exe -s file_path�������ɶ������ļ�file_path�Ľ⵽solve.txt��" << endl;
	}
	return 0;
}


