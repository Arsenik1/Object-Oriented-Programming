#include "TetrisVector.hh"
#include "TetrisAdapter.cpp"
#include "TetrisArray1D.hh"

bool fileExists(const string& filename)
{
	ifstream file(filename);
	return file.good();
}

int main()
{
	char inputShape;
	int height = 0, width = 0;
	char temp;
	char gameType;
	string area;
	string shapeType;
	char rotateDir;
	unsigned int rotateCount;
	char moveDir;
	unsigned int moveCount;
	string Stemp;

	srand(time(0));	//random seed

	cout << "Welcome to Tetris!\n\n";
	cout << "Please enter the type of game you would like to play:\n";
	while(gameType != 'V' && gameType != 'A' && gameType != 'T')
	{
		cout << "Please enter a valid game type (V, A, or T): ";
		cin >> gameType;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}

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

	TetrisVector game_v(height, width); //creating the game_v
	TetrisAdapter<vector<vector<Shape>>> game_a(height, width); //creating the game_v
	TetrisArray1D game_t(height, width); //creating the game_v
	AbstractTetris *gametype_pointer = &game_v;
	if(gameType == 'V')
	{
		cout << "\nYou have chosen to play the Vector version of Tetris.\n";
		gametype_pointer = &game_v;
	}
	else if(gameType == 'A')
	{
		cout << "\nYou have chosen to play the Array version of Tetris.\n";
		gametype_pointer = &game_a;
	}
	else if(gameType == 'T')
	{
		cout << "\nYou have chosen to play the Adapter version of Tetris.\n";
		gametype_pointer = &game_t;
	}
	// decltype(*gametype_pointer) game(height, width);
	AbstractTetris &game= *gametype_pointer;
	cout << "\033[2J" << "\033[0;0f";
	game.draw();
	cout <<" \033[s";	//printing for once because I save the cursor's coordinates in here.

	while(true)
	{
		cout << "\033[2J" << "\033[0;0f";
		game.draw();
		cout << " \033[u";
		cout << "\nEnter shape ";
		cout << "Examples:\nFor tetrominoes: (I, O, T, J, L, S, Z)\nTo save to \"save.txt\": (K)\nTo load from \"save.txt\": (Y)\nQUIT: (Q)\n:";
		cin >> shapeType;
		cin.clear();
		inputShape = shapeType.at(0);
		if(inputShape == 'Y')
		{
			try
			{
				if(fileExists("save.txt"))
					cout << "\nFile has been found.\n";
				else
					throw std::runtime_error("File does not exist");
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			cout << "\033[2J" << "\n-----LOADED-----\n";
			game.readFromFile("save.txt");
			sleep(3);
			continue;
		}
		else if(inputShape == 'K')
		{
			game.writeToFile("save.txt");
			cout << "\033[2J" << "\n-----SAVED-----\n";
			sleep(3);
			continue;
		}
		else if(inputShape == 'Q')
		{
			cout << "\033[2J" << "\n-----EXIT-----\n";
			return 0;
		}
		else if(inputShape == 'R')
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
			Tetromino inputPiece(Tetromino::returnShape(inputShape));	//creating the inputted piece
			// inputPiece.printPiece();
			// cout << endl << endl << endl << "\nafasdokaswndvjasndvjsaknvfjakdfvadfvodafgkdafglk\n" <<"_height" << "_width" << endl << endl;
			// sleep(2);
			
			// cout << "\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
			// sleep(2);
			cout << "\033[2J" << "\033[0;0f";
			while(true)
			{
				game.syncBoard();
				game += inputPiece;
				game.draw(0);
				cout << "\n(Image is for representation purposes only)\n";
				game.clearTable();
				cout << endl << "Please enter the rotation direction and rotation count.\nSyntax: DIRECTION ROTATIONCOUNT\nExample: LEFT 2\n:";
				cin >> rotateDir;
				cin >> Stemp;
				cin >> rotateCount;
				if((rotateDir == 'L' || rotateDir == 'R') && rotateCount <= 4 && rotateCount >= 0)
				{
					cout << "\033[2J" << "\033[0;0f";
					game.syncBoard();
					game += inputPiece;
					game.draw(0);
					game.clearTable();
					cout << "\n(Image is for representation purposes only)\n";
					cout << endl << "Please enter how you want to move the piece.\nSyntax: MOVEDIRECTION MOVECOUNT\nExample: RIGHT 2\n:";
					cin >> moveDir;
					cin >> Stemp;
					cin >> moveCount;
					if((moveDir == 'L' || moveDir == 'R') && moveCount < game.getWidth() && moveCount >= 0 && moveCount < game.getWidth() / 2)
						break;
				}
				if(rotateDir == 'Q' || moveDir == 'Q')
				{
					cout << "\033[2J" << "-----EXIT-----\n";
					game.assemble();
					game.draw();
					return 0;
				}
				cout << "\033[2J" << "\033[0;0f";
				cout << endl << "You have entered a wrong input or you are out of boundaries. Keep in mind that rotation count cannot be more than 4. Try again.\n";
				cin.clear();
			}
			if(game.animate(inputPiece, rotateDir, rotateCount, moveDir, moveCount) == false)	//playing the game and getting the success
			{
				cout << "\033[2J" << "\033[0;0f" << "THE GAME HAS ENDED.\n";
				game.assemble();
				game.draw();
				return 0;
			}
		}
	}

	return 0;
}