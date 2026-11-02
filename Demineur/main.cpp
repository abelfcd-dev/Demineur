#include <iostream>
#include "Cell.h"
#include "Grid.h"
#include <ctime>



void Difficulty(Grid* g)
{
	int difficulty;
	std::cout << "Choisis ta dificulte" << std::endl;
	std::cout << "1 : 9x9" << std::endl;
	std::cout << "2 : 16x16" << std::endl;
	std::cout << "3 : 16x30" << std::endl;
	std::cout << "4 : Niveau Personnalise\n" << std::endl;
	std::cin >> difficulty;
	g->CellReveal = 0;
	switch (difficulty)
	{
	case 1:
		g->rowCount = 9;
		g->colCount = 9;
		break;
	case 2:
		g->rowCount = 16;
		g->colCount = 16;
		break;
	case 3:
		g->rowCount = 16;
		g->colCount = 30;
		break;
	case 4:
		int row = 0;
		int col = 0;
		std::cout << "Quel dimension veux-tu ?" << std::endl;
		while (row < 5 || row > 55)
		{
			std::cout << "Nombre de lignes (entre 5 et 55)" << std::endl;
			std::cin >> row;
		}
		g->rowCount = row;
		while (col < 5 || col > 78)
		{
			std::cout << "Nombre de colonnes (entre 5 et 78)" << std::endl;
			std::cin >> col;
		}
		g->colCount = col;
		break;
	}
	Initialize(g, g->rowCount, g->colCount);
}


void PlayGame(Grid* g, Cell* c)
{
	Difficulty(g);
	DisplayGrid(g);
	FirstChooseCell(g);
	bool PlayAgain;
	while (g->CellReveal > -1 && g->CellReveal < ((g->colCount) * (g->rowCount) - g->CountMines))
		ChooseCell(g);

	if (g->CellReveal == -1)
	{
		DisplayGrid(g);
		std::cout << "You loose..." << std::endl;
		std::cout << "Veux tu rejouer ? (0 ou 1)" << std::endl;
		std::cin >> PlayAgain;
		if (PlayAgain)
		{
			system("cls");
			Free(g);
			PlayGame(g, c);
		}
		return;
	}
	system("cls");
	std::cout << R"(
    |--------------------------------|
    |  \\          // || ||\\   ||   |
    |   \\        //  || || \\  ||   |
    |    \\  /\  //   || ||  \\ ||   |
    |     \\//\\//    || ||   \\||   |
    |      \/  \/     || ||    \\|   |
    |--------------------------------|
)";
	std::cout << "Veux tu rejouer ?" << std::endl;
	std::cin >> PlayAgain;
	if (PlayAgain)
		PlayGame(g, c);
}



int main()
{
	srand(time(NULL));
	Grid g;
	Cell c;
	PlayGame(&g, &c);

	return 0;
}