#include "Tetris.hh"


void Tetris::setPieceCount(int pieceCount)
{
	if(pieceCount > 0)
		_pieceCount = pieceCount;
}

int Tetris::getPieceCount() const
{
	return _pieceCount;
}

vector<vector<Shape>> Tetris::getBoard() const
{
	return _board;
}


void Tetris::setBoard(vector<vector<Shape>> board)
{
	_board = board;
}

vector<vector<Shape>> Tetris::getPlaceBoard() const
{
	return _placeBoard;
}

void Tetris::setPlaceBoard(vector<vector<Shape>> placeBoard)
{
	_placeBoard = placeBoard;
}

int Tetris::getHeight() const
{
	return _height;
}

int Tetris::getWidth() const
{
	return _width;
}

void Tetris::placePieces(vector<vector<Shape>> piece, int col,int row, int where)
{
	int size1 = piece.size();
	if(where)
		for(int i = 0; i < size1; i++)
		{
			decltype(size1) size2 = piece.at(0).size();
			for(int j = 0; j < size2; j++)
				if(piece[i][j] != Shape::Empty )
					_board[row + i][col + j] = piece[i][j];
		}
	else
		for(int i = 0; i < size1; i++)
		{
			decltype(size1) size2 = piece.at(0).size();
			for(int j = 0; j < size2; j++)
				if(piece[i][j] != Shape::Empty )
					_placeBoard[row + i][col + j] = piece[i][j];
		}
}

bool Tetris::overlap()  const //looks for overlap between _placeBoard and _board. placeBoard contains a piece in a spesific coordinate.
{							 		//and this function checks the same coordinates in the actual game table. it looks for piece overlap.
	int size1 = _board.size(), size2;
	for(int i = 0; i < size1; i++)
	{
		size2 = _board.at(0).size();
		for(int j = 0; j < size2; j++)
		{
			if(_board.at(i).at(j) != Shape::Empty && _placeBoard.at(i).at(j) != Shape::Empty)
				return true;
		}
	}
	return false;
}

vector<int> Tetris::fit(Tetromino &piece)
{
	int rotateFlag = 0;
	//this is used for the cases like the shape I has to come to the end vertically bu the program does not try it because it only tries for "total length minus size"
	//boxes. I has a length of 4 horizontally so it won't try the last 3 columns. this flag will let the program try the remaining valid ones at least for once.
	//the program initially will try for both vertical and horicontal versions of all pieces.

	for(int i = 0; i < _board.size() - piece.getPiece().size(); i++)
	{
		int rotationCount = 0;
		rotateFlag = 0;
		for(int j = 0; j < _board.at(0).size() - piece.getPiece().at(0).size() + 1 && rotateFlag == 0; j++) //the +1 in "_board.at(0).size() - piece.getPiece().at(0).size() + 1" if there because placepiece function
		{																				 					//places the piece at the j'th index. without the +1, it will not put any shape to the last availeble space.
			clearTable();
			placePieces(piece.getPiece(), j, i, 0); //sending 4th parameter which means "place piece at _placeBoard"
			// for(int i = _board.size() - 1; i >= 0; i--)
			// {
			// 	for(int j = 0; j < _placeBoard[0].size(); j++)
			// 		cout << (char)_placeBoard[i][j];
			// 	cout << endl;
			// }
			// cout << endl;
			if(overlap() == false)
				return {i, j}; //returning positive values whicch means return value is "true" and also returning the best fitable coordinates as vector.
			else
			{
				if(rotationCount < 5)	//it tries to place to a coordinate 4 times, each in a different rotation.
				{
					rotationCount++;
					if(piece.getType() == Shape::J || piece.getType() == Shape::Z)
						piece.rotate("left");
					else
						piece.rotate();
					j--;	//to stay in the position we are
					if(j + 1 >= _board.at(0).size() - piece.getPiece().at(0).size() + 1) //if next index is available, it will try the narrowest rotation for once.
						if(piece.getType() == Shape::J || piece.getType() == Shape::Z)
						piece.rotate("left");
					else
						piece.rotate();
					continue;
				}
				else	//after enough tries it gives up and moves the coordinate
				{
					if(j + 1 >= _board.at(0).size() - piece.getPiece().at(0).size() + 1)
					if(piece.getType() == Shape::J || piece.getType() == Shape::Z)
						piece.rotate("left");
					else
						piece.rotate();
					rotateFlag = 0;
					rotationCount = 0;
				}
			}
		}
	}
	return {-1, -1};
}
bool Tetris::add(Tetromino piece)
{
	vector<int> heightWidth = fit(piece); //getting the fitable coordinates of the board
	if(heightWidth.at(0) == -1)	//if the vector which the fit() function has returned contains negative value, it means "false" so no operation has been made.
		return false;
	else
	{
		cout << "\033[2J" << "\033[0;0f";
		for(int i = _board.size() - piece.getPiece().size() - 1; i >= heightWidth.at(0); i--)
		{
			clearTable();
			_placeBoard = _board;
			placePieces(piece.getPiece(), heightWidth.at(1), i, 0);			

			cout << "\033[" << heightWidth.at(0) << ";" << 0 << "f";

			for(int k = 0; k < _placeBoard.at(0).size() + 2; k++)
				cout << '#';
			cout << endl;
			for(int i = _placeBoard.size() - 1; i >= 0; i--)
			{
				cout << '#';
				for(int j = 0; j < _placeBoard[0].size(); j++)
					cout << (char)_placeBoard[i][j];
				cout << '#';
				cout << endl;
			}
			for(int k = 0; k < _placeBoard.at(0).size() + 2; k++)
				cout << '#';

			cout << endl;
			usleep(50000);
		}
		
		cout << " \033[u";
		//ANIMATING PART WILL BE HERE
		placePieces(piece.getPiece(), heightWidth.at(1), heightWidth.at(0)); //placing the piece at the coordinates which fit() function returned.
		return true;
	}
}

Tetris::Tetris(int height, int width)
{
	_width = width;
	_height = height;
	_pieceCount = 0;
	_board.resize(height, vector<Shape>(width, Shape::Empty));
	_placeBoard.resize(height, vector<Shape>(width, Shape::Empty));
}

void Tetris::draw() const//game plays in a horizontally reverse direction. so both pieces and the board are flipped horizontally.
{
	for(int k = 0; k < _board.at(0).size() + 2; k++)
		cout << '#';
	cout << endl;
	for(int i = _board.size() - 1; i >= 0; i--)
	{
		cout << '#';
		for(int j = 0; j < _board[0].size(); j++)
			cout << (char)_board[i][j];
		cout << '#';
		cout << endl;
	}
	for(int k = 0; k < _board.at(0).size() + 2; k++)
		cout << '#';
	cout << endl;
}

void Tetris::clearTable() //clears the always used temporary _placeBoard vector.
{
	for(int i = 0; i < _placeBoard.size(); i++)
		for(int j = 0; j < _placeBoard.at(i).size(); j++)
			_placeBoard.at(i).at(j) = Shape::Empty;
}

