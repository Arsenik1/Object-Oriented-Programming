#include "Tetris.hh"

int main()
{
	char inputShape;
	int height = 0, width = 0;
	char temp;
	string area;
	string shapeType;
	srand(time(0));	//random seed

	while(height < 4 || width < 4) 
	{
		int i = 0;
		cout << "PLEASE USE CAPS LOCK THROUGHOUT THE GAME.\n\nEnter size (syntax: heightXwidth): ";
		cin >> area;
		cin.clear();
		for(i = 0; i < area.length() && (area.at(i) > '9' || area.at(i) < '0'); i++);
		while(i < area.length() && area.at(i) <= '9' && area.at(i) >= '0')
		{
			height = (10 * height) + area.at(i) - '0';
			i++;
		}
		for(; i < area.length() && (area.at(i) > '9' || area.at(i) < '0'); i++);
		while(i < area.length() && area.at(i) <= '9' && area.at(i) >= '0')
		{
			width = (10 * width) + area.at(i) - '0';
			i++;
		}
		area = "";
		// cout << endl << height << " " << width << " " << i << endl;
		if(height < 4 || width < 4)
		{
			height = 0;
			width = 0;
		}
    }

	Tetris game(height, width); //creating the game
	cout << "\033[2J" << "\033[0;0f";
	game.draw();
	cout <<" \033[s";

	while(true)
	{
		cout << "\033[2J" << "\033[0;0f";
		game.draw();
		cout << " \033[u";
		cout << "\nEnter shape: ";
		cin >> shapeType;
		cin.clear();
		inputShape = shapeType.at(0);
		if(inputShape == 'Q')
		{
			cout << "\033[2J";
			return 0;
		}
		if(inputShape == 'R')
			while(Tetromino::returnShape(inputShape) == Shape::Empty)
				inputShape = rand() % 100;
		if(Tetromino::returnShape(inputShape) == Shape::Empty && inputShape != 'R')	//input handling
		{
			cout << "\033[2J" << "\033[0;0f";
			cout << "\nInvalid input\n";
			sleep(3);
			shapeType = "";
			continue;
		}
		else
		{
			Tetromino inputPiece(inputPiece.returnShape(inputShape));	//creating the inputted piece
			if(game.add(inputPiece) == false)	//playing the game and getting the success
			{
				cout << "\033[2J" << "\033[0;0f" << "THE GAME HAS ENDED.\n";
				return 0;
			}
		}
	}
	return 0;
}