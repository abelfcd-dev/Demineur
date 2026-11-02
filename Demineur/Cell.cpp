#include <iostream>
#include "Cell.h"
#include "Grid.h"

int GenerateRandomNumber(int min, int max)
{
	return rand() % max;
}

void InitializeCell(Cell* p)
{
	p->descover = false;
	p->flag = false;
	p->mine = false;
	p->MinesAdj = 0;
}


void PutFlag(Cell* p)
{
	p->flag = !p->flag;
}

void PutMineAdj(Cell** p, int CountMine, int rowMax, int colMax, int row, int col)
{
	int randrow = GenerateRandomNumber(0, rowMax - 1);
	int randcol = GenerateRandomNumber(0, colMax - 1);
	int posrow = -1;
	int poscol = -1;

	while (CountMine > 0)
	{
		while (p[randrow][randcol].mine == true || ((randrow >= row - 1 && randrow <= row + 1) && (randcol >= col - 1 && randcol <= col + 1)))
		{
			randrow = GenerateRandomNumber(0, rowMax - 1);
			randcol = GenerateRandomNumber(0, colMax - 1);
		}
		p[randrow][randcol].mine = true;
		for (int decalrow = -1; decalrow <= 1; decalrow++)
		{
			for (int decalcol = -1; decalcol <= 1; decalcol++)
			{
				if (randrow + decalrow >= 0 && randcol + decalcol >= 0 && randrow + decalrow < rowMax && randcol + decalcol < colMax)
					p[randrow + decalrow][randcol + decalcol].MinesAdj += 1;
			}
		}
		CountMine--;
	}
}
