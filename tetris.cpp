/*
Игра "Тетрис"
Учебный проект консольной версии игры "Тетрис"
(c) Карыгин Роман, Санжаровский Дмитрий, Фролов Дмитрий, Китавина Наталья, Бардин Валентин,
Брянцев Всеволод, Проценко Михаил, Проценко Вячеслов, Ивутин Антон, Старинин Андрей.
(с) Компьютерная академия ШАГ. Воронеж
Версия 0.1 (07.03.2019)
*/

#include "pch.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>
#include "windows.h"

using namespace std;

const int ROW = 20;				// Кол-во строк
const int COL = 10;				// Кол-во столбцов

int game_place[ROW][COL]{};		// Объявляем массив размером 20x10 (игровое поле) и инициализировали его 0

/*
	Типы фигур
	1 - I (Палка)
	2 - J
	3 - L
	4 - O (Квадрат)
	5 - S
	6 - Z
	7 - T
*/


int score = 0;					// Подсчет очков
int temp;						// Переменная, для подсчета заполненности строки
int check = 0;
int StepY = 0;
int *pcheck = &check;
int *pStepY = &StepY;
//char Step = _getch();

void InitFig_I(int position);
void InitFig_J(int position);
void InitFig_L(int position);
void InitFig_O();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);
void StartFig(int type, int position); // Описываем фигуры


void Fig_I_Pos1(int x, int y);
void Fig_I_Pos2(int x, int y);

void Fig_J_Pos1(int x, int y);
void Fig_J_Pos2(int x, int y);
void Fig_J_Pos3(int x, int y);
void Fig_J_Pos4(int x, int y);

void Fig_L_Pos1(int x, int y);
void Fig_L_Pos2(int x, int y);
void Fig_L_Pos3(int x, int y);
void Fig_L_Pos4(int x, int y);

void Fig_O_Pos(int x, int y);

void Fig_Z_Pos1(int x, int y);
void Fig_Z_Pos2(int x, int y);

void Fig_S_Pos1(int x, int y);
void Fig_S_Pos2(int x, int y);

void Fig_T_Pos1(int x, int y);
void Fig_T_Pos2(int x, int y);
void Fig_T_Pos3(int x, int y);
void Fig_T_Pos4(int x, int y);


bool RowFull(int row);			// Определение заполненности строки
int  GameScore();				// Определение очков
void DeleteRow();				// Удаление заполенной строки

void Fig_Step(int type, int pos);
bool GameOver();				// Определение проигрыша
bool CheckStep(int x, int y, int check);
void PrintGame();

void Game();

int main()
{
	setlocale(LC_ALL, "866");
	srand(time(NULL));
	int type = 1;
	int pos = 1;
	/*Fig_Step(type, 1);
	Fig_Step(type, 3);
	Fig_Step(type, 4);
	Fig_Step(type, 5);
	Fig_Step(type, 6);
	Fig_Step(type, 7);
	Fig_Step(type, 7);
	Fig_Step(type, 8);*/

	do 
	{
		type = rand() % 7 + 1;
		pos = rand() % 4 + 1;
		Fig_Step(3, 4);
	} while (GameOver() !=true);
	



	PrintGame();
}

bool CheckStep(int x, int y, int check) {

	switch (check)
	{
	case 1:   // проверка 1 координатного горизонтального элемента
		if (game_place[x + 1][y] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 2:   // проверка 2 координатного горизонтального элемента c координатой у - 1
		if (game_place[x + 1][y] != 1 && game_place[x + 1][y - 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 3:  // проверка 3 координатного горизонтального элемента
		if (game_place[x + 1][y] != 1 && game_place[x + 1][y + 1] != 1 && game_place[x + 1][y + 2] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 4:   // проверка 4 координатного горизонтального элемента
		if (game_place[x + 1][y] != 1 && game_place[x + 1][y + 1] != 1 && game_place[x + 1][y + 2] != 1 && game_place[x + 1][y + 3] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 5:   // проверка 1 координатного горизонтального элемента + (y + 1 && x - 1 )
		if (game_place[x + 1][y - 1] != 1 && game_place[x - 1][y] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 6:   // проверка 3 координатного горизонтального элемента (x + 1 & y - 1) , (x + 1 & y) , (x + 2 & y + 1)
		if (game_place[x + 1][y - 1] != 1 && game_place[x + 1][y] != 1 && game_place[x + 2][y + 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 7:   // проверка 2 координатного горизонтального элемента (x + 1 & y) , (x - 1 & y - 1 )
		if (game_place[x + 1][y] != 1 && game_place[x - 1][y - 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 8:   // проверка 3 координатного горизонтального элемента (x + 1 & y - 1) , (x + 1 & y) , (x + 2 & y - 1)
		if (game_place[x + 1][y] != 1 && game_place[x + 1][y + 1] != 1 && game_place[x + 2][y - 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 9:   // проверка 2 координатного горизонтального элемента с координатой у + 1
		if (game_place[x + 1][y] != 1 && game_place[x + 1][y + 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 10:   // проверка 3 координатного горизонтального элемента (x + 1 & y - 1) , (x + 1 & y) , (x & y + 1) S
		if (game_place[x + 1][y - 1] != 1 && game_place[x + 1][y] != 1 && game_place[x][y + 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 11:   // проверка 2 координатного горизонтального элемента с координатой x + 1 & y , x & y - 1
		if (game_place[x + 1][y] != 1 && game_place[x][y - 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 12:   // проверка 3 координатного горизонтального элемента (x + 1 & y) , (x + 1 & y + 1) , (x & y - 1) S
		if (game_place[x + 1][y] != 1 && game_place[x + 1][y + 1] != 1 && game_place[x][y - 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 13:   // проверка 2 координатного горизонтального элемента с координатой x + 1 & y , x & y - 1
		if (game_place[x + 1][y - 1] != 1 && game_place[x][y] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 14:   // проверка 3 координатного горизонтального элемента (x + 1 & y) , (x + 1 & y + 1) , (x & y - 1) T
		if (game_place[x + 1][y] != 1 && game_place[x][y + 1] != 1 && game_place[x][y - 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 15:   // проверка 2 координатного горизонтального элемента с координатой x + 1 & y , x & y - 1
		if (game_place[x + 1][y] != 1 && game_place[x][y - 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 16:   // проверка 2 координатного горизонтального элемента с координатой x + 1 & y , x & y + 1
		if (game_place[x + 1][y] != 1 && game_place[x][y + 1] != 1) 
		{
			return false;
		}
		else
		{
			return true;
		}
		break;

	default:
		break;
	}

}

void Fig_I_Pos1(int x, int y) // Фигура I , горизонтальное положение 
{
	if (x == 0) 
	{
		*pStepY = y;
	}

	if (x != 0) 
	{
		game_place[x - 1][*pStepY] = 0;
		game_place[x - 1][*pStepY + 1] = 0;
		game_place[x - 1][*pStepY + 2] = 0;
		game_place[x - 1][*pStepY + 3] = 0;
	}
	if (_kbhit()) {
		switch (_getch())
		{
			case (char)77:  // право
			if (game_place[x][*pStepY + 4] != 1 && *pStepY < 6)
			{
					*pStepY = *pStepY + 1;
			}
			break;
			case (char)75:  // лево
			if (game_place[x][*pStepY - 1] != 1 && *pStepY > 0) 
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
	game_place[x][*pStepY] = 1;
	game_place[x][*pStepY + 1] = 1;
	game_place[x][*pStepY + 2] = 1;
	game_place[x][*pStepY + 3] = 1;
	PrintGame();

	if (CheckStep(x, *pStepY, 4)) {
		*pcheck = 1;
	}
}
void Fig_I_Pos2(int x, int y) // Фигура I , вертикальное положение 
{
	if (x == 0) {
		*pStepY = y;
	}
	if (x != 0) {
		game_place[x - 1][*pStepY] = 0;
		game_place[x][*pStepY] = 0;
		game_place[x + 1][*pStepY] = 0;
		game_place[x + 2][*pStepY] = 0;
	}
	if (_kbhit()) {
		switch (_getch())
		{
		case (char)77: // право
			if (game_place[x][*pStepY + 1] != 1 && game_place[x + 1][*pStepY + 1] != 1 && game_place[x + 2][*pStepY + 1] != 1 && game_place[x + 3][*pStepY + 1] != 1 && *pStepY < 9) {
				*pStepY = *pStepY + 1;
			}
			break;
		case (char)75: // лево
			if (game_place[x][*pStepY - 1] != 1 && game_place[x + 1][*pStepY - 1] != 1 && game_place[x + 2][*pStepY - 1] != 1 && game_place[x + 3][*pStepY - 1] != 1 && *pStepY > 0) {
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
	game_place[x][*pStepY] = 1;
	game_place[x + 1][*pStepY] = 1;
	game_place[x + 2][*pStepY] = 1;
	game_place[x + 3][*pStepY] = 1;
	PrintGame();
	if (CheckStep(x + 3, *pStepY, 1)) {
		*pcheck = 1;
	}
}

void Fig_J_Pos1(int x, int y) // фигура J (0, 5) позиция № 1 
{
	if (x == 0) 
	{
		*pStepY = y;
	}
	if (x != 0) 
	{
		game_place[x - 1][*pStepY] = 0;
		game_place[x][*pStepY] = 0;
		game_place[x + 1][*pStepY - 1] = 0;
		game_place[x + 1][*pStepY] = 0;
	}
	if (_kbhit())
	{
		switch (_getch())
		{
			case (char)77: // право
			if (game_place[x][*pStepY + 1] != 1 && game_place[x + 1][*pStepY + 1] != 1 && game_place[x + 2][*pStepY + 1] != 1 && *pStepY < 9)
			{
				*pStepY = *pStepY + 1;
			}
			break;
			case (char)75:  // лево
			if (game_place[x][*pStepY - 1] != 1 && game_place[x - 2][*pStepY - 1] != 1 && *pStepY > 1) 
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
	game_place[x][*pStepY] = 1;
	game_place[x + 1][*pStepY] = 1;
	game_place[x + 2][*pStepY - 1] = 1;
	game_place[x + 2][*pStepY] = 1;
	PrintGame();
	if (CheckStep(x + 2, *pStepY, 2)) {
		*pcheck = 1;
	}
}

void Fig_J_Pos2(int x, int y) // фигура J (0, 5) позиция № 2 
{
	if (x == 0) 
	{
		*pStepY = y;
	}
	if (x != 0)
	{
		game_place[x - 1][*pStepY - 1] = 0;
		game_place[x][*pStepY - 1] = 0;
		game_place[x][*pStepY] = 0;
		game_place[x][*pStepY + 1] = 0;
	}
	if (_kbhit()) 
	{
		switch (_getch())
		{
		case (char)77: // право
			if (game_place[x + 1][*pStepY + 2] != 1 && game_place[x][*pStepY] != 1 && *pStepY < 8) 
			{
				*pStepY = *pStepY + 1;
			}
			break;
		case (char)75:  // лево
			if (game_place[x][*pStepY - 2] != 1 && game_place[x + 1][*pStepY - 2] != 1 && *pStepY > 1) 
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
	game_place[x][*pStepY - 1] = 1;
	game_place[x + 1][*pStepY - 1] = 1;
	game_place[x + 1][*pStepY] = 1;
	game_place[x + 1][*pStepY + 1] = 1;
	PrintGame();
	if (CheckStep(x + 1, *pStepY - 1, 3)) 
	{
		*pcheck = 1;
	}
}
void Fig_J_Pos3(int x, int y) // фигура J (0, 5) позиция № 3 
{
	if (x == 0) 
	{
		*pStepY = y;
	}
	if (x != 0) 
	{
		game_place[x - 1][*pStepY - 1] = 0;
		game_place[x - 1][*pStepY] = 0;
		game_place[x][*pStepY - 1] = 0;
		game_place[x + 1][*pStepY - 1] = 0;
	}
	if (_kbhit()) 
	{
		switch (_getch())
		{
		case (char)77: // право
			if (game_place[x][*pStepY + 1] != 1 && game_place[x + 1][*pStepY] != 1 && game_place[x + 2][*pStepY] != 1 && *pStepY < 9) 
			{
				*pStepY = *pStepY + 1;
			}
			break;
		case (char)75:  // лево
			if (game_place[x][*pStepY - 2] != 1 && game_place[x + 1][*pStepY - 2] != 1 && game_place[x + 2][*pStepY - 2] != 1 && *pStepY > 1) 
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
	game_place[x][*pStepY - 1] = 1;
	game_place[x][*pStepY] = 1;
	game_place[x + 1][*pStepY - 1] = 1;
	game_place[x + 2][*pStepY - 1] = 1;
	PrintGame();
	if (CheckStep(x + 2, *pStepY, 5)) 
	{
		*pcheck = 1;
	}
}

void Fig_J_Pos4(int x, int y) // фигура J (0, 5) позиция № 4 
{
	if (x == 0) 
	{
		*pStepY = y;
	}
	if (x != 0) 
	{
		game_place[x - 1][*pStepY - 1] = 0;
		game_place[x - 1][*pStepY] = 0;
		game_place[x - 1][*pStepY + 1] = 0;
		game_place[x][*pStepY + 1] = 0;
	}
	if (_kbhit()) 
	{
		switch (_getch())
		{
		case (char)77: // право
			if (game_place[x][*pStepY + 2] != 1 && game_place[x + 1][*pStepY + 2] != 1 && *pStepY < 8) 
			{
				*pStepY = *pStepY + 1;
			}
			break;
		case (char)75:  // лево
			if (game_place[x][*pStepY - 2] != 1 && game_place[x + 1][*pStepY] != 1 && *pStepY > 1) 
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
	game_place[x][*pStepY - 1] = 1;
	game_place[x][*pStepY] = 1;
	game_place[x][*pStepY + 1] = 1;
	game_place[x + 1][*pStepY + 1] = 1;
	PrintGame();
	if (CheckStep(x, *pStepY, 6)) 
	{
		*pcheck = 1;
	}
}

void Fig_L_Pos1(int x, int y) // фигура L (0, 5) позиция № 1 
{
	if (x == 0)
	{
		*pStepY = y;
	}
	if (x != 0) 
	{
		game_place[x - 1][*pStepY] = 0;
		game_place[x][*pStepY] = 0;
		game_place[x + 1][*pStepY] = 0;
		game_place[x + 1][*pStepY + 1] = 0;
	}
	if (_kbhit()) 
	{
		switch (_getch())
		{
		case (char)77:  // право
			if (game_place[x][*pStepY + 1] != 1 && game_place[x + 1][*pStepY + 1] != 1 && game_place[x + 2][*pStepY + 2] != 1 && *pStepY < 8)
			{
				*pStepY = *pStepY + 1;
			}
			break;
		case (char)75:  // лево
			if (game_place[x][*pStepY - 1] != 1 && game_place[x + 1][*pStepY - 1] != 1 && game_place[x + 2][*pStepY - 1] != 1 && *pStepY > 0)
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
		game_place[x][*pStepY] = 1;
		game_place[x + 1][*pStepY] = 1;
		game_place[x + 2][*pStepY] = 1;
		game_place[x + 2][*pStepY + 1] = 1;
		PrintGame();
	if (CheckStep(x + 2, *pStepY, 9))
	{
		*pcheck = 1;
	}
}
void Fig_L_Pos2(int x, int y) // фигура L (0, 5) позиция № 2
{
	if (x == 0)
	{
		*pStepY = y;
	}
	if (x != 0) 
	{
		game_place[x - 1][*pStepY + 1] = 0;
		game_place[x][*pStepY - 1] = 0;
		game_place[x][*pStepY] = 0;
		game_place[x][*pStepY + 1] = 0;
	}
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)77:  // право
			if (game_place[x][*pStepY + 2] != 1 && game_place[x + 1][*pStepY + 2] != 1 && *pStepY < 8)
			{
				*pStepY = *pStepY + 1;
			}
			break;
		case (char)75:  // лево
			if (game_place[x][*pStepY] != 1 && game_place[x + 1][*pStepY - 2] != 1  && *pStepY > 0)
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
		game_place[x][*pStepY + 1] = 1;
		game_place[x + 1][*pStepY - 1] = 1;
		game_place[x + 1][*pStepY] = 1;
		game_place[x + 1][*pStepY + 1] = 1;
		PrintGame();
	if (CheckStep(x + 1, *pStepY - 1, 3))
	{
		*pcheck = 1;
	}
}
void Fig_L_Pos3(int x, int y) // фигура L (0, 5) позиция № 3
{
	if (x == 0)
	{
		*pStepY = y;
	}
	if (x != 0) 
	{
		game_place[x - 1][*pStepY - 1] = 0;
		game_place[x - 1][*pStepY] = 0;
		game_place[x][*pStepY] = 0;
		game_place[x + 1][*pStepY] = 0;
	}
	if (_kbhit())
	{
		switch (_getch())
		{
			case (char)77:  // право
			if (game_place[x][*pStepY + 1] != 1 && game_place[x + 1][*pStepY + 1] != 1 && game_place[x + 2][*pStepY + 1] != 1 && *pStepY < 9)
			{
				*pStepY = *pStepY + 1;
			}
			break;
			case (char)75:  // лево
			if (game_place[x][*pStepY - 2] != 1 && game_place[x + 1][*pStepY - 1] != 1 && game_place[x + 2][*pStepY - 1] != 1 && *pStepY > 1)
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
		game_place[x][*pStepY - 1] = 1;
		game_place[x][*pStepY] = 1;
		game_place[x + 1][*pStepY] = 1;
		game_place[x + 2][*pStepY] = 1;
		PrintGame();
	if (CheckStep(x + 2, *pStepY, 7))
	{
		*pcheck = 1;
	}
}
void Fig_L_Pos4(int x, int y) // фигура L (0, 5) позиция № 4
{
	if (x == 0)
	{
		*pStepY = y;
	}
	if (x != 0) 
	{
		game_place[x - 1][*pStepY - 1] = 0;
		game_place[x - 1][*pStepY] = 0;
		game_place[x - 1][*pStepY + 1] = 0;
		game_place[x][*pStepY - 1] = 0;
	}
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)77:  // право
			if (game_place[x][*pStepY + 2] != 1 && game_place[x + 1][*pStepY] != 1 && *pStepY < 8)
			{
				*pStepY = *pStepY + 1;
			}
			break;
		case (char)75:  // лево
			if (game_place[x][*pStepY - 2] != 1 && game_place[x + 1][*pStepY - 2] != 1 && *pStepY > 1)
			{
				*pStepY = *pStepY - 1;
			}
			break;
		}
	}
		game_place[x][*pStepY - 1] = 1;
		game_place[x][*pStepY] = 1;
		game_place[x][*pStepY + 1] = 1;
		game_place[x + 1][*pStepY - 1] = 1;
		PrintGame();
	if (CheckStep(x, *pStepY, 8))
	{
		*pcheck = 1;
	}
}

void Fig_O_Pos(int x, int y)
{
	if (x != 0) 
	{
		game_place[x - 1][y + 1] = 0;
		game_place[x - 1][y] = 0;
		game_place[x][y + 1] = 0;
		game_place[x][y] = 0;
	}
		game_place[x][y + 1] = 1;
		game_place[x][y] = 1;
		game_place[x + 1][y + 1] = 1;
		game_place[x + 1][y] = 1;
		PrintGame();
	if (CheckStep(x + 1, y, 9)) 
	{
		*pcheck = 1;
	}
}

void Fig_S_Pos1(int x, int y) // фигура S (0, 5) позиция № 1
{
	if (x != 0) 
	{
		game_place[x - 1][y] = 0;
		game_place[x][y] = 0;
		game_place[x][y - 1] = 0;
		game_place[x - 1][y + 1] = 0;
	}
		game_place[x][y] = 1;
		game_place[x + 1][y] = 1;
		game_place[x + 1][y - 1] = 1;
		game_place[x][y + 1] = 1;
		PrintGame();
	if (CheckStep(x + 1, y, 10)) 
	{
		*pcheck = 1;
	}
}
void Fig_S_Pos2(int x, int y) // фигура S (0, 5) позиция № 2
{
	if (x != 0) {
		game_place[x - 1][y - 1] = 0;
		game_place[x][y - 1] = 0;
		game_place[x][y] = 0;
		game_place[x + 1][y] = 0;
	}
	game_place[x][y - 1] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	PrintGame();
	if (CheckStep(x + 2, y, 11)) {
		*pcheck = 1;
	}
}

void Fig_Z_Pos1(int x, int y) // фигура Z (0, 5) позиция № 1
{
	if (x != 0) 
	{
		game_place[x - 1][y - 1] = 0;
		game_place[x - 1][y] = 0;
		game_place[x][y] = 0;
		game_place[x][y + 1] = 0;
	}
		game_place[x][y - 1] = 1;
		game_place[x][y] = 1;
		game_place[x + 1][y] = 1;
		game_place[x + 1][y + 1] = 1;
		PrintGame();
	if (CheckStep(x + 1, y, 12)) 
	{
		*pcheck = 1;
	}
}
void Fig_Z_Pos2(int x, int y) // фигура Z (0, 5) позиция № 2
{
	if (x != 0) {
		game_place[x - 1][y] = 0;
		game_place[x][y] = 0;
		game_place[x][y - 1] = 0;
		game_place[x + 1][y - 1] = 0;
	}
		game_place[x][y] = 1;
		game_place[x + 1][y] = 1;
		game_place[x + 1][y - 1] = 1;
		game_place[x + 2][y - 1] = 1;
		PrintGame();
	if (CheckStep(x + 2, y, 13)) {
		*pcheck = 1;
	}
}

void Fig_T_Pos1(int x, int y) // фигура T (0, 5) позиция № 1
{
	if (x != 0) 
	{
		game_place[x - 1][y - 1] = 0;
		game_place[x - 1][y] = 0;
		game_place[x][y] = 0;
		game_place[x - 1][y + 1] = 0;
	}
		game_place[x][y - 1] = 1; 
		game_place[x][y] = 1;
		game_place[x + 1][y] = 1;
		game_place[x][y + 1] = 1;
		PrintGame();
	if (CheckStep(x + 1, y, 14)) 
	{
		*pcheck = 1;
	}
}
void Fig_T_Pos2(int x, int y) // фигура T (0, 5) позиция № 2
{
	if (x != 0) 
	{
		game_place[x - 1][y] = 0;
		game_place[x][y] = 0;
		game_place[x + 1][y] = 0;
		game_place[x][y - 1] = 0;
	}
		game_place[x][y] = 1;
		game_place[x + 1][y] = 1;
		game_place[x + 2][y] = 1;
		game_place[x + 1][y - 1] = 1;
		PrintGame();
	if (CheckStep(x + 2, y, 15)) 
	{
		*pcheck = 1;
	}
}
void Fig_T_Pos3(int x, int y) // фигура T (0, 5) позиция № 3
{
	if (x != 0) 
	{
		game_place[x - 1][y] = 0;
		game_place[x][y] = 0;
		game_place[x][y - 1] = 0;
		game_place[x][y + 1] = 0;
	}
		game_place[x][y] = 1;
		game_place[x + 1][y] = 1;
		game_place[x + 1][y - 1] = 1;
		game_place[x + 1][y + 1] = 1;
		PrintGame();
	if (CheckStep(x + 1, y - 1, 3)) 
	{
		*pcheck = 1;
	}
}
void Fig_T_Pos4(int x, int y) // фигура T (0, 5) позиция № 4
{
	if (x != 0) 
	{
		game_place[x - 1][y] = 0;
		game_place[x][y] = 0;
		game_place[x + 1][y] = 0;
		game_place[x][y + 1] = 0;
	}
		game_place[x][y] = 1;
		game_place[x + 1][y] = 1;
		game_place[x + 2][y] = 1;
		game_place[x + 1][y + 1] = 1;
		PrintGame();
	if (CheckStep(x + 2, y, 16)) 
	{
		*pcheck = 1;
	}
}

void InitFig_I(int position)
{
	switch (position)
	{
	case 1: Fig_I_Pos1(0, 3);
		break;
	case 2: Fig_I_Pos2(0, 5);
		break;
	}

}

void InitFig_J(int position)
{
	switch (position)
	{
	case 1:	Fig_J_Pos1(0, 5);
		break;
	case 2:	Fig_J_Pos2(0, 5);
		break;
	case 3:	Fig_J_Pos3(0, 5);
		break;
	case 4:	Fig_J_Pos4(0, 5);
		break;
	}
}

void InitFig_L(int position)
{
	switch (position)
	{
	case 1:	Fig_L_Pos1(0, 5);
		break;
	case 2:	Fig_L_Pos2(0, 5);
		break;
	case 3:	Fig_L_Pos3(0, 5);
		break;
	case 4:	Fig_L_Pos4(0, 5);
		break;
	}
}
void InitFig_O()
{
	Fig_O_Pos(0, 5);
}

void InitFig_S(int position)
{
	switch (position)
	{
	case 1:	Fig_S_Pos1(0, 5);
		break;
	case 2:	Fig_S_Pos2(0, 5);
		break;
	}
}

void InitFig_Z(int position)
{
	switch (position)
	{
	case 1:	Fig_Z_Pos1(0, 5);
		break;
	case 2:	Fig_Z_Pos2(0, 5);
		break;
	}
}

void InitFig_T(int position)
{
	switch (position)
	{
	case 1:	Fig_T_Pos1(0, 5);
		break;
	case 2:	Fig_T_Pos2(0, 5);
		break;
	case 3:	Fig_T_Pos3(0, 5);
		break;
	case 4:	Fig_T_Pos4(0, 5);
		break;
	}
}

void StartFig(int type, int position)
{
	switch (type)
	{
	case 1: InitFig_I(position);
		break;
	case 2: InitFig_J(position);
		break;
	case 3: InitFig_L(position);
		break;
	case 4: InitFig_O();
		break;
	case 5: InitFig_S(position);
		break;
	case 6: InitFig_Z(position);
		break;
	case 7: InitFig_T(position);
		break;
	}
}

void Fig_Step(int type, int pos)
{
	switch (type)
	{
	case 1:    //---------------------------------- Элемент I
	{
		if (pos == 3 || pos == 4)
		{
			pos = rand() % 2 + 1;
			switch (pos)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						Fig_I_Pos1(i, 3);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
				case 2:
				{
					for (int i = 0; i < ROW - 3; i++)
					{
						Fig_I_Pos2(i, 4);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
			}
		}
		else
		{
			switch (pos)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						Fig_I_Pos1(i, 3);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
				case 2:
				{
					for (int i = 0; i < ROW - 3; i++)
					{
						Fig_I_Pos2(i, 4);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}	
				break;
			}
		}
	}
	break;
	case 2:    //------------------------------------ Элемент  J
	{
		switch (pos)
		{
			case 1:
			{
				for (int i = 0; i < ROW - 2; i++)
				{
					Fig_J_Pos1(i, 5);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}

			}
			break;
			case 2:
			{
				for (int i = 0; i < ROW - 1; i++)
				{
					Fig_J_Pos2(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 3:
			{
				for (int i = 0; i < ROW - 2; i++)
				{
					Fig_J_Pos3(i, 5);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 4:
			{
				for (int i = 0; i < ROW - 1; i++)
				{
					Fig_J_Pos4(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
		}
		break;
	}
	case 3:  //---------------------------------- Элемент L
	{
		switch (pos)
		{
			case 1:
			{
				for (int i = 0; i < ROW - 2; i++)
				{
					Fig_L_Pos1(i, 5);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 2:
			{
				for (int i = 0; i < ROW - 1; i++)
				{
					Fig_L_Pos2(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 3:
			{
				for (int i = 0; i < ROW - 2; i++)
				{
					Fig_L_Pos3(i, 5);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 4:
			{
				for (int i = 0; i < ROW - 1; i++)
				{
					Fig_L_Pos4(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
		}
		break;
	}
	case 4:  //----------------------------------------- Элемент Z
	{
		if (pos == 3 || pos == 4)
		{
			pos = rand() % 2 + 1;
			switch (pos)
			{
				case 1:
				{
					for (int i = 0; i < ROW - 1; i++)
					{
						Fig_Z_Pos1(i, 4);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
				case 2:
				{
					for (int i = 0; i < ROW - 2; i++)
					{
						Fig_Z_Pos2(i, 5);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
			}
			break;
		}
		else
		{
			switch (pos)
			{
				case 1:
				{
					for (int i = 0; i < ROW - 1; i++)
					{
						Fig_Z_Pos1(i, 4);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
				case 2:
				{
					for (int i = 0; i < ROW - 2; i++)
					{
						Fig_Z_Pos2(i, 5);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
			}
			break;
		}
	}
	case 5:  //----------------------------------------- Элемент S
	{
		if (pos == 3 || pos == 4)
		{
			pos = rand() % 2 + 1;
			switch (pos)
			{
				case 1:
				{
					for (int i = 0; i < ROW - 1; i++)
					{
						Fig_S_Pos1(i, 4);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
				case 2:
				{
					for (int i = 0; i < ROW - 2; i++)
					{
						Fig_S_Pos2(i, 5);
						if (*pcheck == 1)
						{
							*pcheck = 0;
							break;
						}
					}
				}
				break;
			}
			break;
		}
		else
		{
			switch (pos)
			{
			case 1:
			{
				for (int i = 0; i < ROW - 1; i++)
				{
					Fig_S_Pos1(i, 4);
					if (*pcheck == 1)
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 2:
			{
				for (int i = 0; i < ROW - 2; i++)
				{
					Fig_S_Pos2(i, 5);
					if (*pcheck == 1)
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			}
			break;
		}
	}
	case 6:   //----------------------------------------- Элемент O
	{
		for (int i = 0; i < ROW - 1; i++)
		{
			Fig_O_Pos(i, 4);
			if (*pcheck == 1) 
			{
				*pcheck = 0;
				break;
			}
		}
	}
		break;
	
	case 7:  //----------------------------------------- Элемент T
	{
		switch (pos)
		{
			case 1:
			{
				for (int i = 0; i < ROW - 1; i++)
				{
					Fig_T_Pos1(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 2:
			{
				for (int i = 0; i < ROW - 2; i++)
				{
					Fig_T_Pos2(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 3:
			{
				for (int i = 0; i < ROW - 1; i++)
				{
					Fig_T_Pos3(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
			break;
			case 4:
			{
				for (int i = 0; i < ROW - 2; i++)
				{
					Fig_T_Pos4(i, 4);
					if (*pcheck == 1) 
					{
						*pcheck = 0;
						break;
					}
				}
			}
		break;
		}
	}
	break;  //-----------------------------------------
	default:
	break;
	}
}

bool RowFull(int row)
{
	temp = 0;
	for (int j = 0; j < COL; j++)
		temp += game_place[row][j];

	if (temp == 10)
		return true;
	else
		return false;
}

int GameScore()
{
	int k = 0;	// Переменная для подсчета заполненных строк
	for (int i = 0; i < ROW; i++)
	{
		if (RowFull(i))	// Если строка заполенная, то увеличиваем счетчик заполненых строк на 1
			k++;
	}
	// Добавление очков при полном заполнении строки 
	switch (k)
	{
	case 1:
		return 100;			// При заполнении 1 строки 100 очков
		break;
	case 2:
		return 300;			// При заполнении 2 строк 300 очков
		break;
	case 3:
		return 700;			// При заполнении 3 строк 700 очков
		break;
	case 4:
		return 1500;		// При заполнении 4 строк 1500 очков
		break;
	default:
		return 0;
		break;
	}
}

void DeleteRow()
{
	int m = 0;

	for (int i = 0; i < ROW; i++)
	{
		if (RowFull(i))
		{		// Если строка заполненная, то заменяем ее строкой выше
			m = i;
			do {
				for (int j = 0; j > COL; j++)
					game_place[m][j] == game_place[m - 1][j];
				m--;
			} while (m != 0);
		}
	}
}
	
bool GameOver() // Функция для проверки верхней строчки игрового поля на наличие в ней 1 (признак фигуры), если есть хоть одна то игра окончена
{
	for (int i = 0; i < COL; i++)
	{
		if (game_place[0][i] == 1)
			return true;	
	}
	cout << "Game over!" << endl;
	return false;
}

void PrintGame() {
	system("cls");
	for (int i = 0; i < COL + 2; i++)
	{
		cout << char(219);
	}
	cout << endl;
	for (int i = 0; i < ROW; i++)
	{
		cout << char(219);
		for (int j = 0; j < COL; j++)
		{
			if (game_place[i][j] == 0) {
				cout << " ";
			}
			else {
				cout << char(219);
			}
		}
		cout << char(219) << endl;
	}
	for (int i = 0; i < COL + 2; i++)
	{
		cout << char(219);
	}
	Sleep(500);
}
