#pragma once
#include "Cell.h"

struct Grid
{
	Cell** cells;
	int rowCount;
	int colCount;
	int CountMines;
	int CellReveal;
};

void Initialize(Grid* g, int rowCount, int colCount);

void DisplayGrid(Grid* g);

char DisplayCell(Grid* g, const Cell* cell);

void FirstChooseCell(Grid* g);

void ChooseCell(Grid* g);

void Discover(Grid* g, Cell** p, int row, int col, int rowMax, int colMax);

void Free(Grid* g);