#include<fstream>
#include<iostream> 
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<math.h> 
#include<cstring>
using namespace std;

int n = 0; //Ҫ���ɵ������վָ��� 
char a[10][10]; //�������� 
double list[10]; //�����������ɵ���������� 
int vis_code[10]; //����ʱ��ǵ�ǰ����Ƿ񱻱���� 
char move1[10][5] = { "036","063" }; //�ƶ����� 
char move2[10][5] = { "258","285","528","582","852","825" };
char move3[10][5] = { "147","174","417","471","714","741" };
char move_boss[10]; //������ϳ���һ������ 
int move_boss_int[10]; //������ϳ����е����Ͱ� 
const double low = -30, high = 30; //ά������������½�

char Print_Data[200000000];
char vis[3][10][10];
bool Found_Ans = false;
bool Is_First_Task = true;

ofstream OutputFile("shudu.txt");
ofstream OutputFileSolveSudoku("answer.txt");

double Rand(double lowwer, double upper) //��������� 
{

	return (rand() / (double)RAND_MAX) * ((upper)-(lowwer)) + (lowwer);
}

void transform(double* temp1)  //���� 
{
	memset(vis_code, 0, sizeof(vis_code));
	//ÿһ���ҵ�һ��ά���е���Сֵ������Сֵ��ʼ˳��ֵi 
	int min;
	for (int i = 1; i <= 9; i++)
	{
		min = -1;
		for (int j = 1; j <= 8; j++)//�ҵ���С��ά�� 
		{
			if ((min == -1 || temp1[j] < temp1[min]) && vis_code[j] == 0)
				min = j;
		}//minΪ��ǰ��Сά�� 
		if (i != 8)
			a[1][min + 1] = i + '0'; //����ǰ��Сά�ȵ�Ԫ����Ÿ�ֵΪi 
		else
			a[1][min + 1] = i + 1 + '0';
		vis_code[min] = 1;
	}
}

void Initial()  //��ʼ����һ�е����� 
{
	srand(time(NULL)); // ʹ�õ�ǰʱ����Ϊ����
	a[1][1] = (rand() % 9) + '1'; //���Ͻǵ�����Ϊ�����

	srand((unsigned)(time(NULL) + rand()));
	for (int j = 1; j <= 8; j++)
		list[j] = Rand(low, high); //���ɾŸ���������� 
	transform(list); //������һ�������վֵ�һ��������� 
}

void To_int() //��һ���ַ�����ת������������ 
{
	for (int i = 0; i < 9; i++)
		move_boss_int[i] = move_boss[i] - '0';
}

void Print_Sudoku(int tag)
{
	int pos = 0;
	if (tag == 1) //���������վֵ���� 
	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (j != 9)
				{
					Print_Data[pos++] = a[i][j];
					Print_Data[pos++] = ' ';//����ո�	
				}
				else
					Print_Data[pos++] = a[i][j];
			}
			Print_Data[pos++] = '\n';//���뻻�з�
		}
		Print_Data[pos++] = '\n';
		OutputFile << Print_Data; //һ�������վ��������ַ�������ʽ���
	}
	else if (tag == 2) //������������ 
	{
		if (Is_First_Task == false) //������ǵ�һ�����⣬�������֮ǰ���һ�п��� 
			OutputFileSolveSudoku << endl; //����ȥ 
		else
			Is_First_Task = false;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (j != 9)
				{
					Print_Data[pos++] = a[i][j];
					Print_Data[pos++] = ' ';//����ո�	
				}
				else
					Print_Data[pos++] = a[i][j];
			}
			Print_Data[pos++] = '\n';//���뻻�з�
		}
		OutputFileSolveSudoku << Print_Data; //һ�������վ��������ַ�������ʽ���
		cout << "�����Ľ��ѱ�����answer.txt�У�" << endl;
	}
}

void Produce_Sudoku(int DEMAND)
{
	int count = 0;
	for (int i = 0; i < 2; i++) //����������72�ֲ�ͬ������ʽ 
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 6; k++)
			{
				char s1[15], s2[15];
				strcpy_s(s1, sizeof(s1), move1[i]);
				strcpy_s(s2, sizeof(s2), move2[j]);
				strcpy_s(move_boss, sizeof(move_boss), strcat(strcat(s1, s2), move3[k]));
				To_int(); //���ַ�������ת��Ϊint�� 
				for (int q = 2; q <= 9; q++) //��������һ���������� 
				{
					for (int w = 1; w <= 9; w++)
					{
						int m = (w - move_boss_int[q - 1] + 9) % 9;
						if (m == 0) //��Ӧ���һ�е������Ҫ���⴦�� 
							m = 9;
						a[q][w] = a[1][m];
					}
				}
				++count;
				Print_Sudoku(1);
				if (count == DEMAND)//�����������һ�ֵ����󣬾��˳� 
					return;
			}
		}
	}
}

void Set_Vis(int r, int c, int num)
{
	vis[0][r][num] = 1;
	vis[1][c][num] = 1;
	vis[2][r / 3 * 3 + c / 3][num] = 1;
}

void Reset_Vis(int r, int c, int num)
{
	vis[0][r][num] = 0;
	vis[1][c][num] = 0;
	vis[2][r / 3 * 3 + c / 3][num] = 0;
}

bool Check_Vis(int r, int c, int num) //���ɲ����Է���
{
	if (vis[0][r][num] == 0
		&& vis[1][c][num] == 0
		&& vis[2][r / 3 * 3 + c / 3][num] == 0)
		return true;
	else
		return false;
}

void Solve_Sudoku(int r, int c)
{
	while (a[r][c] != '0') //�ҵ�һ���յ�����λ�� 
	{
		if (c < 8)
			c++;
		else //����һ�� 
		{
			c = 0;
			r++;
		}
		if (r == 9)	//�ҵ���һ���𰸼�9x9������û��0���Ǿ����ҵ���һ����� 
		{
			Found_Ans = true;
			return; //��� 
		}
	}

	bool Can_Search = false; //��ǻ����㷨�е�ǰ����Ƿ��������
	for (int i = 1; i <= 9; i++)
	{
		if (Check_Vis(r, c, i))
		{
			Can_Search = true; //��ǿ������� 
			Set_Vis(r, c, i); //��ǰ��������� 
			a[r][c] = i + '0';
			Solve_Sudoku(r, c);
			if (Found_Ans) //��֦ 
				return;
			Can_Search = false;
			Reset_Vis(r, c, i);
			a[r][c] = '0';
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "����ָ���������ڿ���̨ʹ����ȷ��ָ�������г���" << endl;
		cout << "����������shudu.exe -c N��������N�������վ��ļ���shudu.txt��" << endl;
		cout << "����������shudu.exe -s file_path�������ɶ������ļ�file_path�Ľ⵽solve.txt��" << endl;
		return 0;
	}
	FILE* fp1 = fopen(argv[2], "r");
	if (strcmp(argv[1], "-s") == 0 && fp1 == NULL)
	{
		cout << "����ָ���������ڿ���̨ʹ����ȷ��ָ�������г���" << endl;
		cout << "����������shudu.exe -c N��������N�������վ��ļ���shudu.txt��" << endl;
		cout << "����������shudu.exe -s file_path�������ɶ������ļ�file_path�Ľ⵽solve.txt��" << endl;
		return 0;
	}
	if (argc == 3 && strcmp(argv[1], "-c") == 0)
	{
		int len = strlen(argv[2]); //���������ַ���ת��Ϊ���� 
		for (int i = 0; i < len; i++)
		{
			if (argv[2][i] >= '0' && argv[2][i] <= '9')
			{
				int value = argv[2][i] - '0';
				for (int j = 1; j <= len - 1; j++)
					value *= 10;
				n += value;
			}
			else
			{
				cout << "���������������������1-1000000֮�������" << endl;
				return 0;
			}
		}
		if (n > 1000000 || n <= 0)
		{
			cout << "���������������������1-1000000֮�������" << endl;
			return 0;
		}
		int round; //��Ҫ���������վֵ�������һ������72��
		if (n <= 72)
			round = 1;
		else
			round = n / 72 + 1;
		while (round)
		{
			int demand; //ÿһ����Ҫ���ɵľ����� 
			Initial(); //��ʼ�������ĵ�һ�� 
			if (round != 1) //�������һ�� 
				demand = 72;
			else //�����һ�� 
				demand = n % 72;
			Produce_Sudoku(demand);
			--round;
		}
		cout << "�ѳɹ�����" << n << "�������վֱ�����shudu.txt��" << endl;
	}
	else if (argc == 3 && strcmp(argv[1], "-s") == 0)
	{
		char buf[110];
		int count = 0;
		while (fgets(buf, 20, fp1))
		{
			if (strcmp(buf, "\n") == 0) //���������� 
				continue;
			for (int i = 0; i <= 16; i++)
			{
				if (i % 2 == 0)
				{	
					if (buf[i] == '$') {
						buf[i] = '0';
					}
					a[count][i / 2] = buf[i];
					Set_Vis(count, i / 2, buf[i] - '0');
				}
			}
			count++;
			if (count == 9)
			{
				Found_Ans = false;
				Solve_Sudoku(0, 0); //���ݽ����� 
				Print_Sudoku(2);
				memset(vis, 0, sizeof(vis));
				count = 0;
			}
		}
	}
	else {
		cout << "����ָ���������ڿ���̨ʹ����ȷ��ָ�������г���" << endl;
		cout << "����������shudu.exe -c N��������N�������վ��ļ���shudu.txt��" << endl;
		cout << "����������shudu.exe -s file_path�������ɶ������ļ�file_path�Ľ⵽solve.txt��" << endl;
	}
	return 0;
}