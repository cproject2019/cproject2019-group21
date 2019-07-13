#include <windows.h>
#include <stdlib.h>//Only used to convert types
#include <string.h>
#include<string>
#include<iostream>
#include<stack>
#include<string.h>
#include<istream>
#include<math.h>
#include<sstream>

using namespace std;

/*the following linked lists are used to operate variables of statistics */
typedef struct _Node
{
	double value;
	struct _Node* pNext;
} Node;
typedef struct _Node2
{
	double x;
	double y;
	struct _Node2* next;
} Node2;

//some gloable variables
float res;
double avg = 0;
double s2 = 0;
double sigma = 0;
double barsigma = 0;
double avgx = 0;
double avgy = 0;
double s2x = 0;
double s2y = 0;
double sigmax = 0;
double sigmay = 0;
double barsigmax = 0;
double barsigmay = 0;
double sigmaA = 0;
double sigmaB = 0;
double r = 0;
double a1 = 0;
double b1 = 0;
int k;
#pragma once
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//make window process a life
													 //void OnShowNum(int iNum);
													 //HWND hOutputBox = NULL;
void TCHARTochar(const wchar_t *wchar, char *chr, int length);
HINSTANCE hInst;
int a = 0;
/*
TCHAR tcCur[300] = {0};
char ab = {'3'};
TCHAR D;
*/
TCHAR szInputBox1[300];
TCHAR szInputBox2[300];
TCHAR szInputBox3[300];
TCHAR szInputBox4[300];//Define buffer
TCHAR szOutputBox[300];
TCHAR Data[600];

string function, function1, function2,function3;
string value;
string down;
string up;