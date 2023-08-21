#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define N 9
#define OK 12138
int usedNum[3][(int)(N*1.5)+1][10];//����������ʹ�ù������� 0:б��Ϊ0�ķ��� 1:б��Ϊ������3�ķ��� 2:б��Ϊ������3�ķ���
int extremal[3][(int)(N * 1.5) + 1][2];//���������ϵļ�ֵ 0:б��Ϊ0�ķ��� 1:б��Ϊ������3�ķ��� 2:б��Ϊ������3�ķ���

//int inputNum[ ( 3 * N * N + 1 )/ 4 + 1];//��ʼ����
int map[N + 1][(int)(N * 1.5) + 1];//���ѵ�ͼ
int count_solution = 0, count_test = 0;
char t;
FILE* fp = NULL;
void Initialize();
void PrintMap();
void MyGetchar(int line, int column);
int GetNext_x(int x, int y);
int GetNext_y(int x, int y);
bool CanSetNum(int x, int y,int(f_extremal)[3][(int)(N * 1.5) + 1][2]);
void RemoveNum(int x, int y);
int SetNum(int x, int y, int(f_extremal)[3][(int)(N * 1.5) + 1][2]);
int SetNextNum(int x, int y, int(f_extremal)[3][(int)(N * 1.5) + 1][2]);
bool InputNum();

void Initialize()//��ʼ��
{
	count_solution = 0;
	for (int direction = 0; direction < 3; direction++)
	{
		for (int line = 1; line < (int)(N * 1.5) + 1; line++)
		{
			for (int num = 0; num <= 9; num++)
			{
				usedNum[direction][line][num] = 0;//0:�ڵ�direction�������ϵĵ�line��δʹ�ù�num
			}
			(extremal)[direction][line][0] = 10;//�ڵ�direction�������ϵĵ�line�е���Сֵ��ʼΪ10
			(extremal)[direction][line][1] = -2;//�ڵ�direction�������ϵĵ�line�е����ֵ��ʼΪ-2
		}
	}

	for (int i = 0; i < N + 1; i++)
	{
		for (int j = 0; j < (int)(N * 1.5) + 1; j++)
		{
			map[i][j] = -1;//-1:�߽� 0:δ�� 1~9:�������Ӧ����
		}
	}
}
void PrintMap()
{
	count_solution++;
	printf("��%d���� : " , count_solution);
	for (int line = 1; line <= N; line++)
	{
		for (int column = 1; column <= (int)N * 1.5; column++)
		{
			if (map[line][column] != -1)
			{
				printf("%d", map[line][column]);
			}
		}
	}
	printf("\n");
}
void MyGetchar(int x , int y)//getchar��ȡ��������
{
	fscanf(fp, "%c", &t);
	map[x][y] = (int)t - '0';
}
int GetNext_x(int x, int y)
{
	if (x == N && y == N / 2 + 1)return -1;//������
	y++;
	if (y == (int)(N * 1.5) + 1)//������ĩβ
	{
		x++;
	}
	return x;
}
int GetNext_y(int x, int y)
{
	if (x == N&& y == N / 2 + 1)return -1;//������
	y++;
	if (y == (int)(N * 1.5) + 1)//������ĩβ
	{
		y = 1;
	}
	return y;
}
bool CanSetNum(int x, int y , int(f_extremal)[3][(int)(N * 1.5) + 1][2])//�ж����������Ƿ����ظ�����,�ܷ�������ҷ���TRUE,or�����ҷ���FALSE
{
	if (map[x][y] == 0)return true;
	int direction[3] = { x,y,x + y - 1 };//��map�е�����x,y ת��Ϊ���������ϵ������
	for (int dir = 0; dir < 3; dir++)
	{
		if (usedNum[dir][direction[dir]][map[x][y]])
		{
			return false;
		}
	}
	for (int dir = 0; dir < 3; dir++)
	{
		usedNum[dir][direction[dir]][map[x][y]] = 1;
		usedNum[dir][direction[dir]][0]++;
		if (map[x][y] < (f_extremal)[dir][direction[dir]][0])
		{
			(f_extremal)[dir][direction[dir]][0] = map[x][y];
		}
		if (map[x][y] > (f_extremal)[dir][direction[dir]][1])
		{
			(f_extremal)[dir][direction[dir]][1] = map[x][y];
		}
	}
	for (int dir = 0; dir < 3; dir++)
	{
		int shortest = N / 2 + 1;
		int delta_max = 0;
		if (dir != 2)
		{
			if (direction[dir] <= shortest)
			{
				delta_max = direction[dir] + shortest - 2;
			}
			else
			{
				delta_max = N - direction[dir] + shortest - 1;
			}
		}
		else
		{
			if (direction[dir] <= N)
			{
				delta_max = direction[dir] - 1;
			}
			else
			{
				delta_max = 2 * N - 1 - direction[dir];
			}
		}

		//int line_min = 10, line_max = 0, delta = 0, count_used = 0;

		/*for (int candidate = 1; candidate <= 9; candidate++)
		{
			
			if (usedNum[dir][direction[dir]][candidate] != 0)
			{
				count_used++;
				if (candidate < line_min)
				{
					line_min = candidate;
				}
				if (candidate > line_max)
				{
					line_max = candidate;
				}
			}
		}*/

		
		if (usedNum[dir][direction[dir]][0] >= 2)
		{
			//delta = line_max - line_min;
			int delta = f_extremal[dir][direction[dir]][1] - f_extremal[dir][direction[dir]][0];
			if (delta > delta_max)
			{
				for (int dir2 = 0; dir2 < 3; dir2++)
				{
					usedNum[dir2][direction[dir2]][map[x][y]] = 0;
					usedNum[dir2][direction[dir2]][0]--;
				}
				return false;
			}
		}
	}
	
	return true;
}
void RemoveNum(int x, int y)
{
	if (map[x][y] == -1)
		return;
	int direction[3] = { x,y,x + y - 1 };//��map�е�����x,y ת��Ϊ���������ϵ������
	for (int dir = 0; dir < 3; dir++)
	{
		usedNum[dir][direction[dir]][map[x][y]] = 0;
	}
	
	map[x][y] = 0;
}
int SetNum(int x, int y, int(f_extremal)[3][(int)(N * 1.5) + 1][2])
{
	int state = -1;
	
	if (map[x][y] != 0)
	{
		state = SetNextNum(x, y, f_extremal);
		//if (state == OK) return OK;
		//RemoveNum(x, y);
		return 0;
	}
	if (x == -1)
	{
		PrintMap();
		return 0;
		//return OK;
	}
	for (int candidate = 1; candidate <= 9; candidate++)
	{
		map[x][y] = candidate;
		int direction[3] = { x,y,x + y - 1 };//��map�е�����x,y ת��Ϊ���������ϵ������
		int t_extremal[3][2];
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 2; k++)
			{
				t_extremal[i][k] = f_extremal[i][direction[i]][k];
			}
		}
		if (!CanSetNum(x, y, f_extremal))
		{
			for (int dir = 0; dir < 3; dir++)
			{
				f_extremal[dir][direction[dir]][0] = t_extremal[dir][0];
				f_extremal[dir][direction[dir]][1] = t_extremal[dir][1];
			}
			map[x][y] = 0;
			continue;
		}
		state = SetNextNum(x, y, f_extremal);
		//if (state == OK) return OK;
		RemoveNum(x, y);

		
		for (int dir = 0; dir < 3; dir++)
		{
			f_extremal[dir][direction[dir]][0] = t_extremal[dir][0];
			f_extremal[dir][direction[dir]][1] = t_extremal[dir][1];
		}
		/*
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < (int)(N * 1.5) + 1; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					f_extremal[i][j][k] = t_extremal[i][j][k];
				}
			}
		}*/
	}
	return 0;
}
int SetNextNum(int x, int y, int(f_extremal)[3][(int)(N * 1.5) + 1][2])
{
	int next[2];
	next[0] = GetNext_x(x, y);
	next[1] = GetNext_y(x, y);
	return SetNum(next[0], next[1], f_extremal);
}
bool InputNum()//forѭ����ȡ��������
{
	int shortest = N / 2 + 1;//��̱ߵĳ��� N = 9  =>  shortest = 5
	for (int line = 1; line <= N; line++)
	{
		int column = 1;
		if (line <= shortest)
		{
			column = shortest - line + 1;
			for (;column <= N; column++)
			{
				MyGetchar(line, column);
				if (!CanSetNum(line, column,extremal))
				{
					printf("ERROR �������־����ظ�\n");
					return false;
				}
			}
			continue;
		}
		for (; column <= N - (line - shortest); column++)
		{
			MyGetchar(line, column); 
			if (!CanSetNum(line, column, extremal))
			{
				printf("ERROR �������־����ظ�\n");
				return false;
			}
		}
	}
	return true;
}


int main()
{
	
	char* position = "D:\\SAVE\\code\\c\\Haniddoku\\Project_Haniddoku\\easy_hanidoku.txt";
	fp = fopen(position, "r");
	while (1)
	{
		count_test++;
		printf("_____________________\n��%d�β��� : \n", count_test);
		for (int i = 0; i < 5; i++)
		{
			fscanf(fp, "%c", &t);
		}
		Initialize();
		if (InputNum())
		{
			SetNum(1, 1, extremal);
		}
		fscanf(fp, "%c",&t);
	}
	fclose(fp);
	
	return 0;
}