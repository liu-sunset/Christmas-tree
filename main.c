#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<windows.h>
#include <time.h>
#include<string.h>
#define PI 3.14159265359

char love[][1024] =
{
	 "001000000000010000000001000000000000000000010000",
	"000110000000010000000001000000000111011100100100",
	"000010010010010000000001000001000101010101111110",
	"111111111010010011111111111111100101010101000100",
	"000000100010010000000001000000000101010101010100",
	"010000100010010000000001000000000111011101000100",
	"001000100010010000000001000100000101010101010100",
	"000101000010010000111111111110000101010101001000",
	"000101000010010000000000000000000101010101000000",
	"000010000010010000000010000000000111011101111110",
	"000010000010010000010001100000000101010100000010",
	"000101000010010001010000100001000101010100001010",
	"001000100000010001010000000100100101010111111110",
	"010000110000010010010000000100100101010100000010",
	"100000010001010000001111111100001000101100001010",
	"000000000000100000000000000000000000000000000100",


};
void gotoxy(int x, int y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼������ľ��
	COORD pos = { x,y };//���ù������
	SetConsoleCursorPosition(hout, pos);
}
void SetColor(int color)
{
	if (color == 0)
		color = 0x04;//�������������ɫ��0����ɫ����ת����4��
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼������ľ��
		SetConsoleTextAttribute(hCon,color);//�����ı���ɫ����
}


void showsnow()
{
	SetColor(rand() % 16); //���������ɫ��
	int x = rand() % 120;
	int y = rand() % 40; //�����������
	gotoxy(x,y); //�������
	putchar('*');
}
float sx, sy;//Բ�ĵ�����
float sdcircle(float px, float py, float r)//�����������Բ�İ뾶
{
	float dx = px - sx, dy = py - sy; 
	return sqrtf(dx * dx + dy * dy) - r;//����ĳ�㵽Բ�߽���з��ž���
}


float opUnion(float d1, float d2)
{
	return d1 < d2 ? d1 : d2;
}


#define T px+scale*r*cosf(theta),py+scale*r*sin(theta)
int ribbon()
{
	float x = (fmodf(sy, 0.1f) / 0.1f - 0.5f) * 0.5f;
	return sx >= x - 0.05f && sx <= x + 0.05f;
}


float f(float px, float py, float theta, float scale, int n)
{
	float d = 0.0f; 
	for(float r = 0.0f; r < 0.8f; r += 0.02f)
		d = opUnion(d, sdcircle(T, 0.05f * scale * (0.95 - r)));
	if (n > 0)
	{
		for (int t = -1; t <= 1; t += 2)
		{
			float tt = theta + t * 1.8f;
				float ss = scale * 0.9f; 
				for (float r = 0.2f; r < 0.8f; r += 0.1f)
				{
					d = opUnion(d, f(T, tt, ss * 0.5f, n - 1));
					ss *= 0.8f;
				}
		}
	}
	return d;
}


int main(int argc, char* argv[])//argc�����ܿ���̨�Ĳ���������argv�����ܿ���̨�Ĳ���
{
	system("mode con cols=120 lines=42");//���ÿ���̨���
	srand((unsigned int)time(NULL)); 
	SetConsoleCP(437);//���ÿ���̨������ַ����뷽ʽ
	SetConsoleOutputCP(437);//���ÿ���̨����ַ��ı��뷽ʽ
	int n = argc > 1 ? atoi(argv[1]) : 3;
	float zoom = argc > 2 ? atof(argv[2]) : 1.0f; 
	for (sy = 0.8f; sy > 0.0f; sy -= 0.02f / zoom, putchar('\n'))
	{
		for (sx = -0.35f; sx < 0.35f; sx += 0.01f / zoom)
		{
			if (f(0, 0, PI * 0.5f, 1.0f, n) < 0.0f)
			{
				if (sy < 0.1f)
				{
					SetColor(rand() % 16);
					putchar('\3');
				}
				else {
					if (ribbon())
						putchar('=');
					else
					{
						SetColor(rand() % 16);
						putchar('\3');
					}
				}
			}
			else
				putchar(' ');
		}
	}
	int i, j;
	int x, y = 3;
	for (i = 0; i < 19; i++, y++)
	{
		x = 60;
		for (j = 0; j < strlen(love[i]); j++, x++)
		{
			gotoxy(x,y);
			if (love[i][j] == '1')
			{
				putchar(' ');
			}
			else {
				SetColor(0x06);
				putchar('*');
			}
		}
	}
	for (n = 0; n++ < 365;)
		showsnow();
	gotoxy(8,40);
	getchar();
	return 0;
}

