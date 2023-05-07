#include "Tetris.hh"

using namespace std;

int main()
{
	cout << "\nPART I:\nPress enter to get to the next step AND ALWAYS USE CAPS LOCK. Please go till the end, I have wasted so mush time on this tester :)\nTetris class test\n";
	{
		int height;
		int width;
		bool what;
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nEnter height:";
		cin >> height;
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nEnter width:";
		cin >> width;
		Tetris testris(height, width);
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "Object height: " << testris.getHeight() << " width: " << testris.getWidth() << ".\n";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "Getting the board:\n";
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
				cout << (char)testris.getBoard().at(i, j);
			cout << endl;
		}
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nAdding piece to the board using Tetromino and operator+=. Also, to do this, using Tetromino constructor and draw function are used : \n";
		Tetromino testromino(Shape::S);
		testris.getBoard() += testromino;
		cout << endl;
		testris.draw();
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "PlaceBoard at the initial state:\n";
		testris.draw(0);
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "PlaceBoard after assemble(): \n";
		what = testris.assemble();
		testris.draw(0);
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nand also return value of assemble: " << what;
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "The overlap() function will be tested. Since we copied the placeBoard and board, they should overlap completely\n and the function should return true.\n Return value: " << testris.overlap();
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\n\nNow clearing the placeBoard using clearTable(): \n";
		testris.clearTable();
		testris.draw(0);
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "Let's play the game for just once and see: \n";
		{
			char inputShape;
			int height = 0, width = 0;
			char temp;
			string area;
			string shapeType;
			char rotateDir;
			unsigned int rotateCount;
			char moveDir;
			unsigned int moveCount;
			string Stemp;

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
			cout <<" \033[s";	//printing for once because I save the cursor's coordinates in here.

			while(true)
			{
				cout << "\033[2J" << "\033[0;0f";
				game.draw();
				cout << " \033[u";
				cout << "\nEnter shape: ";
				cout << "Examples:  (I, O, T, J, L, S, Z)\n:";
				cin >> shapeType;
				cin.clear();
				inputShape = shapeType.at(0);
				if(inputShape == 'Q')
				{
					cout << "\033[2J" << "-----EXIT-----";
					break;
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
					Tetromino inputPiece(Tetromino::returnShape(inputShape));	//creating the inputted piece
					// inputPiece.printPiece();
					// cout << endl << endl << endl << "\nafasdokaswndvjasndvjsaknvfjakdfvadfvodafgkdafglk\n" <<"_height" << "_width" << endl << endl;
					// sleep(2);
					
					// cout << "\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
					// sleep(2);
					cout << "\033[2J" << "\033[0;0f";
					while(true)
					{
						game.setPlaceBoard(game.getBoard());
						game.getPlaceBoard() += inputPiece;
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
							game.setPlaceBoard(game.getBoard());
							game.getPlaceBoard() += inputPiece;
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
							break;
						}
						cout << "\033[2J" << "\033[0;0f";
						cout << endl << "You have entered a wrong input or you are out of boundaries. Keep in mind that rotation count cannot be more than 4. Try again.\n";
						cin.clear();
					}
					if(game.animate(inputPiece, rotateDir, rotateCount, moveDir, moveCount))	//playing the game and getting the success
					{
						cout << "\033[2J" << "\033[0;0f" << "THE GAME HAS ENDED.\n";
						game.assemble();
						game.draw();
						break;
					}
				}
			}
		}
		sleep(2);
		cout << "\033[2J" << "Test successful.\n Last part, destructor call and after that you will test part II.";
	}
	{
		char inputShape;
		int input = 1;
		string dir;
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nPART II:\n\nTetromino class test\n";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "To call the shape constructor, what type of tetromino you want? \n(This also tests the static returnShape function.)\n:";
		cout << "Examples:  (I, O, T, J, L, S, Z)\n:";
		cin >> inputShape;
		Tetromino testromino(Tetromino::returnShape(inputShape));
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nAfter construction, your requested object is(using Tetromino::printPiece function):\n";
		testromino.printPiece();
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nand your shape type is(using Tetromino::getType): " << "Shape::" << (char)testromino.getType() << endl << endl;
		while(true)
		{
			cout << "Which way do you want to rotate the piece(this also tests Tetromino::moveCorner. if you see the piece correctly in a rectangular shape with minimum size after every rotation, it means that it works.)?\n enter '0' to stop rotating part:";
			cin >> dir;
			if(dir[0] == '0')
				break;
			testromino.rotate(dir);
			testromino.printPiece();
			dir = "";
			cin.clear();
		}
	}
	{
		char inputShape;
		int height, width;
		Shape shape;
		cout << "\033[2J";
		cout << "\nPART III:\n\nTwoD class test\n";
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "This is my own array class. It has vector-like properties. I added the specifications that I used the most.\n\n Constructor I test:\n Enter height: ";
		cin >> height;
		cout << "\nEnter width:";
		cin >> width;
		cout << "\nEnter default element you want to set to this piece. If the Tetromino shape type you enter is not valid, it will be filled with emptiness.\n:";
		cout << "Examples:  (I, O, T, J, L, S, Z)\n:";
		cin >> inputShape;
		cout << "Here's the TwoD you constructed(Height size,width size getters and the TwoD::at() are used while printing): ";
		TwoD test1(height, width, Tetromino::returnShape(inputShape));
		for(int i = 0; i < test1.getRow(); i++)
		{
				for(int j = 0; j < test1.getCol(); j++)
					cout << (char)test1.at(i,j);
			cout << endl;
		}
		cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		cout << "\nNow, let's resize it. It works even better than the vector implementation.\nPlease enter the new height:";
		cin >> height;
		cout << "\nPlease enter the new width: ";
		cin >> width;
		cout << "Lastly, enter what type of tetromino shape value you want to have as deafult(invalid enters will be treated as Empty.): ";
		cout << "Examples:  (I, O, T, J, L, S, Z)\n:";
		cin >> inputShape;
		test1.resize(height, width, Tetromino::returnShape(inputShape));
		cout << "Here's your new TwoD:\n";
		for(int i = 0; i < test1.getRow(); i++)
		{
				for(int j = 0; j < test1.getCol(); j++)
					cout << (char)test1.at(i,j);
			cout << endl;
		}
		cout << "\nLastly, Constructor II will be tested.";
		while(true)
		{
			cout << "The shape type you enter will be converted to the array. Know that this is not a tetromino class, it is TwoD class. \nEnter shape type(Q for quit):";
			cout << "Examples:  (I, O, T, J, L, S, Z)\n:";
			cin >> inputShape;
			if(inputShape == 'Q')
				break;
			TwoD test2(Tetromino::returnShape(inputShape));
			for(int i = 0; i < test1.getRow(); i++)
			{
					for(int j = 0; j < test1.getCol(); j++)
						cout << (char)test1.at(i,j);
				cout << endl;
			}
			inputShape = ' ';
			cin.clear();
			cout << "\033[2J" << "Test successful.\n Last part, destructor call and after that you will finish.";
			cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		}
	}

	return 0;
}