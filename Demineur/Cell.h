#pragma once

struct Cell
{
	bool mine;
	bool descover;
	bool flag;
	int MinesAdj;
};

void InitializeCell(Cell* p);

void PutFlag(Cell* p);

void PutMineAdj(Cell** cells, int CountMine, int rowMax, int colMax, int row, int col);