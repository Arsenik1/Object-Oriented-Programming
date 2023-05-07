#include "header.hh"

bool Tetromino::canFit(Tetromino &otherOne, string pos)
{
	int i = 0, j = 0;
	Tetromino temp(otherOne._type); //used for left direction rotation
	decltype(i) currentCol = 1;
	int counter = 0; //counts how many times it tried for a column (maximum 3 because 4 rotations is the same piece)
	vector<vector<Shape>> place(8, vector<Shape>(8)); //acts as a trying board
	int size = place.size();
	bool hasPlaced = false;

	if(pos == "left")
		return temp.canFit(*this, "right");

	for(i = 0; i < 8; i++)	//filling place with Shape::Empty
		for(j = 0; j < 8; j++)
			place[i][j] = Shape::Empty;

	for(i = 0; i < _piece.size(); i++)	//placing the first element to place
		for(j = 0; j < _piece.size(); j++)
			place[i][j] = _piece[i][j];

	while(currentCol < size && hasPlaced == false)
	{
		counter = 0;
		for(i = 0; i < otherOne._piece.size(); i++)
		{
			if(counter == 5)
			{
				if(place[0][currentCol] == Shape::Empty && currentCol != 0)
				{
					hasPlaced = false;
					currentCol = otherOne._piece.size();
					continue;
				}
				break;
			}

			if(otherOne._piece[0][0] == Shape::Empty && place[0][currentCol] == Shape::Empty) //OK
			{
				// cout << "111 " << currentCol << " " << counter << " 111\n";
				++counter;
				otherOne.rotate("right");
				i = -1;
				continue;
			}
			//first box fill check done
			// cout << "debug -> i:" << i << " col:" << currentCol << " leftIf:" << (place[i][currentCol] != Shape::Empty) << ", rightIf:" << (_piece[i][0] != Shape::Empty) << endl;
			if(place[i][currentCol] != Shape::Empty && _piece[i][0] != Shape::Empty) //other boxes check
			{
				++counter;
				i = -1;
				otherOne.rotate("right");
				// cout << currentCol << endl;
				continue;
			}
			if(i == otherOne._piece.size() - 1) //i only becomes size - 1 when all boxes are valid.
			{
				cout << currentCol << endl;
				for(int i = 0; i < otherOne._piece.size(); i++)
					for(int j = 0; j < otherOne._piece.size(); j++)
						if(otherOne._piece[i][j] != Shape::Empty)
							place[i][j + currentCol] = otherOne._piece[i][j];
				cout << "\n*******************************\n";
				for(int i = place.size() - 1; i >= 0; i--)
				{
					for(int j = 0; j < place.size(); j++)
						cout << (char)place[i][j];
					cout << endl;
				}
				cout << "*******************************\n" << endl;
				hasPlaced = true;
				i = otherOne._piece.size();
			}
		}
		++currentCol;
	}
	return hasPlaced;
}

void Tetromino::printPiece()
{
	for(int i = _piece.size() - 1; i >= 0; i--)
	{
		for(int j = 0; j < _piece.size(); j++)
			cout << (char)_piece[i][j];
		cout << endl;
	}
}

void Tetromino::rotate(string dir)
{
	int loopCount = 1;
	vector<vector<Shape>> rotationTemp(_piece.size(), vector<Shape>(_piece.size(), Shape::Empty));	//when rotating, used for temporary storage. it is static because I need no other instances.
	if(dir == "left")
		loopCount = 3;
	while(loopCount--)
	{
		for(int i = 0; i < _piece.size(); i++)
			for(int j = 0; j < _piece[i].size(); j++)
				rotationTemp[j][i] = _piece[i][j];

		int size = _piece.size();
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
				_piece[i][j] = rotationTemp[i][size - 1 - j];
		}
	}
	moveCorner();
}

Tetromino::Tetromino() //default constructor
{
	_type = Shape::I;
	_piece = {};
}

Tetromino::Tetromino(Shape shape)
{
	_type = shape; 
	setPiece(shape);
}

void Tetromino::setPiece(Shape shape)
{
	if(shape == Shape::I)
	{
		_piece = 
		{
			{Shape::I,Shape::Empty,Shape::Empty,Shape::Empty},
			{Shape::I,Shape::Empty,Shape::Empty,Shape::Empty},
			{Shape::I,Shape::Empty,Shape::Empty,Shape::Empty},
			{Shape::I,Shape::Empty,Shape::Empty,Shape::Empty}
		};
	}
	else if(shape == Shape::O)
	{
		_piece = 
		{
			{Shape::O,Shape::O, Shape::Empty},
			{Shape::O,Shape::O, Shape::Empty},
			{Shape::Empty,Shape::Empty,Shape::Empty}
		};
	}
	else if(shape == Shape::T)
	{
		_piece = 
		{
			{Shape::Empty,Shape::T,Shape::Empty},
			{Shape::T,Shape::T,Shape::T},
			{Shape::Empty,Shape::Empty,Shape::Empty}
		};
	}
	else if(shape == Shape::J)
	{
		_piece = 
		{
			{Shape::J,Shape::J,Shape::Empty},
			{Shape::Empty,Shape::J,Shape::Empty},
			{Shape::Empty,Shape::J,Shape::Empty}
		};
	}
	else if(shape == Shape::L)
	{
		_piece = 
		{
			{Shape::L,Shape::L,Shape::Empty},
			{Shape::L,Shape::Empty,Shape::Empty},
			{Shape::L,Shape::Empty,Shape::Empty}
		};
	}
	else if(shape == Shape::S)
	{
		_piece = 
		{
			{Shape::S,Shape::S,Shape::Empty},
			{Shape::Empty,Shape::S,Shape::S},
			{Shape::Empty,Shape::Empty,Shape::Empty}
		};
	}
	else if(shape == Shape::Z)
	{
		_piece = 
		{
			{Shape::Empty,Shape::Z,Shape::Z},
			{Shape::Z,Shape::Z,Shape::Empty},
			{Shape::Empty,Shape::Empty,Shape::Empty}
		};
	}
}

vector<vector<Shape>> Tetromino::getPiece()
{
	return _piece;
}

const Shape Tetromino::getType()
{
	return _type;
}

void Tetromino::setType(Shape type)
{
	_type = type;
}

const Shape Tetromino::returnShape(char shape)
{
	switch(shape)
	{
		case 'I': return Shape::I;
		case 'O': return Shape::O;
		case 'J': return Shape::J;
		case 'L': return Shape::L;
		case 'S': return Shape::S;
		case 'Z': return Shape::Z;
		case 'T': return Shape::T;
		default: return Shape::Empty;
	}
	return Shape::I;
}

void Tetromino::moveCorner()
{
	int size = _piece.size();
	bool up = true, left = true;
	int i, j;

	while(up || left)
	{
		for(auto a : _piece[0])
			if(a != Shape::Empty)
				up = false;
		for(int a = 0; a < _piece.size(); a++)
			if(_piece[a][0] != Shape::Empty)
				left = false;

		for(i = 1; i < _piece.size() && up == true; i++)
			for(j = 0; j < _piece.size(); j++)
				_piece[i - 1][j] = _piece[i][j];
		if(up == true)
			for(i = 0; i < _piece.size() && up == true; i++)
				_piece[_piece.size() - 1][i] = Shape::Empty;

		for(i = 0; i < _piece.size() && left == true; i++)
			for(j = 1; j < _piece.size(); j++)
				_piece[i][j - 1] = _piece[i][j];
		if(left == true)
			for(i = 0; i < _piece.size(); i++)
				_piece[i][_piece.size() - 1] = Shape::Empty;
	}
}

void Board::setBoard(vector<vector<Shape>> board)
{
	_board = board;	
}

vector<vector<Shape>>& Board::getBoard()
{
	return _board;
}

void Board::placePieces(vector<vector<Shape>> piece, int col,int row)
{
	int size = piece.size();
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(piece[i][j] != Shape::Empty )
				_board[row + i][col + j] = piece[i][j];
}

const void Board::printBoard()
{
	for(int i = _board.size() - 1; i >= 0; i--)
	{
		for(int j = 0; j < _board.size(); j++)
			cout << (char)_board[i][j];
		cout << endl;
	}
}

vector<Tetromino> Board::getAllPieces()
{
	return _allPieces;
}

void Board::setAllPieces(vector<Tetromino> allPieces)
{
	_allPieces = allPieces;
}

vector<vector<Shape>> Board::placeBoard = {};	
//For now, this program will only have 1 board object
//but I might add multiple games at the same time and this placeBoard
//vector will be used as a temporary vector to put the Tetrominos on the table
//so I won't need more than one instance for it.

Board::Board(int pieceCount, vector<Tetromino> allPieces) //constructing the playground according to the input.
{
	_pieceCount = pieceCount;
	_allPieces = allPieces;
	_board = {};
	_board.resize(pieceCount * 4);	//reserving the least space needed 

	for(int i = 0; i < _board.size(); i++)
		_board[i].resize(pieceCount * 4, Shape::Empty);

	placeBoard.resize(pieceCount * 4);	//reserving the least space needed
	for(int i = 0; i < placeBoard.size(); i++)
		placeBoard[i].resize(pieceCount * 4, Shape::Empty);
}