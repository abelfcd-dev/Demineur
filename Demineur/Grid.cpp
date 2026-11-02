#include <iostream>
#include "Grid.h"
#include "Cell.h"


void Initialize(Grid* g, int rowCount, int colCount)
{
	Cell** cells = (Cell**)malloc(sizeof(Cell*) * rowCount);

	for (int row = 0; row < rowCount; row++)
	{
		cells[row] = (Cell*)malloc(sizeof(Cell) * colCount);
		for (int col = 0; col < colCount; col++)
		{
			InitializeCell(&cells[row][col]);
		}
	}

	g->cells = cells;

	g->rowCount = rowCount;
	g->colCount = colCount;
}


void DisplayGrid(Grid* g)
{
	const char* RESET = "\033[0m";
	system("cls");
	std::cout << "  ";
	for (int col = 0; col < g->colCount; col++)
	{
		if (col < 10)
			std::cout << " " << col << " ";
		else
			std::cout << " " << col;
	}
	std::cout << std::endl;
	for (int row = 0; row < g->rowCount; row++)
	{
		if (row < 10)
			std::cout << row << " ";
		else
			std::cout << row;
		for (int col = 0; col < g->colCount; col++)
		{
			std::cout << "[";
			std::cout << DisplayCell(g, &g->cells[row][col]);
			std::cout << RESET << "]";
		}
		std::cout << std::endl;
	}

}


char DisplayCell(Grid* g, const Cell* cell)
{
	const char* GREEN = "\033[32m";
	const char* RED = "\033[31m";
	const char* BLUE = "\033[36m";
	const char* BACKWHITE = "\33[47m";
	if (cell->descover && cell->mine == false)
		if (cell->MinesAdj > 0)
		{
			if (cell->MinesAdj == 1)
			{
				std::cout << BLUE;
			}
			if (cell->MinesAdj == 2)
			{
				std::cout << GREEN;
			}
			if (cell->MinesAdj > 2)
			{
				std::cout << RED;
			}
			return cell->MinesAdj + '0';
		}
		else
		{
			return '.';
		}
	if (cell->flag)
		return 'F';
	if (g->CellReveal == -1)
		if (cell->mine)
		{
			std::cout << RED;
			return '*';
		}

	return ' ';
}



void FirstChooseCell(Grid* g)
{
	int row = 0;
	int col = 0;
	std::cout << "Tu joues ici au demineur !!" << std::endl;
	std::cout << "Choisis ta premiere case a reveler :)" << std::endl;
	std::cout << "Choisis ta ligne : " << std::endl;
	std::cin >> row;
	std::cout << "Choisis ta colonne : " << std::endl;
	std::cin >> col;
	g->CountMines = g->rowCount * g->colCount * 15 / 100;
	PutMineAdj(g->cells, g->CountMines, g->rowCount, g->colCount, row, col);
	Discover(g, g->cells, row, col, g->rowCount, g->colCount);
	DisplayGrid(g);
}



void ChooseCell(Grid* g)
{
	int row = 0;
	int col = 0;
	char flag;
	std::cout << "veux tu mettre un drapeau ? Si oui, marque 'F'! Sinon marque 'D'" << std::endl;
	std::cin >> flag;
	std::cout << "Choisis ta ligne : " << std::endl;
	std::cin >> row;
	std::cout << "Choisis ta colonne : " << std::endl;
	std::cin >> col;
	if (flag == 'f' || flag == 'F')
	{
		PutFlag(&g->cells[row][col]);
	}
	else
	{
		Discover(g, g->cells, row, col, g->rowCount, g->colCount);
	}
	DisplayGrid(g);
}





void Discover(Grid* g, Cell** p, int row, int col, int rowMax, int colMax)
{
	int compteur = 0;
	Cell* cell = &p[row][col];

	if (cell->descover)
		return;

	if (cell->flag)
		return;

	cell->descover = true;

	g->CellReveal += 1;

	if (cell->mine == true)
		g->CellReveal = -1;

	if (cell->MinesAdj > 0)
		return;

	for (int decalrow = -1; decalrow <= 1; decalrow++)
	{
		for (int decalcol = -1; decalcol <= 1; decalcol++)
		{
			if (row + decalrow < 0 || col + decalcol < 0)
				continue;

			if (row + decalrow >= rowMax || col + decalcol >= colMax)
				continue;

			Discover(g, p, row + decalrow, col + decalcol, rowMax, colMax);
		}
	}
}


void Free(Grid* g)
{
	for (int i = 0; i < g->rowCount; i++)
	{
		free(g->cells[i]);
	}
	free(g->cells);
}