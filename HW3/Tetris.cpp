#include "Tetris.hh"


TwoD &Tetris::getBoard()
{
	return _board;
}


void Tetris::setBoard(TwoD board)
{
	_board = board;
}

TwoD& Tetris::getPlaceBoard()
{
	return _placeBoard;
}

void Tetris::setPlaceBoard(TwoD& placeBoard)
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

void Tetris::placePieces(TwoD &piece, int col,int row, int where)
{
	int size1 = piece.getRow();
	if(where)
		for(int i = 0; i < size1; i++)
		{
			decltype(size1) size2 = piece.getCol();
			for(int j = 0; j < size2; j++)
				if(piece.at(i, j) != Shape::Empty )
					_board.at(row + i, col + j) = piece.at(i, j);
		}
	else
		for(int i = 0; i < size1; i++)
		{
			decltype(size1) size2 = piece.getCol();
			for(int j = 0; j < size2; j++)
				if(piece.at(i, j) != Shape::Empty )
					_placeBoard.at(row + i, col + j) = piece.at(i, j);
		}
}

bool Tetris::overlap()  			 //looks for overlap between _placeBoard and _board. placeBoard contains a piece in a spesific coordinate.
{							 		//and this function checks the same coordinates in the actual game table. it looks for piece overlap.
	int size1 = getHeight(), size2;
	for(int i = 0; i < size1; i++)
	{
		size2 = getWidth();
		for(int j = 0; j < size2; j++)
		{
			if(_board.at(i, j) != Shape::Empty && _placeBoard.at(i, j) != Shape::Empty)
				return true;
		}
	}
	return false;
}

bool Tetris::animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount) //burasını değiştirmen lazım animate ederken gelecek yerde overlap var mı kontrol edip devam edecek
{
	//fit gidecek
	int	height = getHeight() - piece.getPiece().getRow();				//setting the initial places, which means top middle in here.
	int	width = _board.getCol() / 2 - (piece.getPiece().getCol() / 2);

	_placeBoard += piece;
	if(overlap())	//initial overlap check
		return false;
	clearTable();

	while(rotateCount > 0)
	{
		if(rotateDir == 'L')
			piece.rotate("left");
		else if(rotateDir == 'R')
			piece.rotate("right");
		--rotateCount;
	}		//ROTATION COMPLETE
	// piece.printPiece();

	_placeBoard += piece;
	if(overlap())
		return false;
	clearTable();

	while(!overlap() && moveCount > 0 && width >= 0 && width < _board.getCol() - piece.getPiece().getCol())	//horizontal animation part
	{
		clearTable();
		placePieces(piece.getPiece(), width, height, 0);
		--moveCount;
		if(moveDir == 'L')
			--width;
		else if(moveDir == 'R')
			++width;
		cout << "\033[2J" << "\033[0;0f";
		if(assemble())
			draw(0);
		_placeBoard = backup;
		// cout << "\nleft-right\n";
		usleep(200000); //intcreased time from 50000 because it was too fast.
	}

	if(height < 0 || overlap())	//this is a check for vertical animation. when going horizontal, if height somehow becomes negative or especially when an overlap occurs, it means that there is not much space left.
	{							//returning false will cause the game to end.
		if(overlap())
		{
			if(moveDir == 'L')	//restoring to the place one step before by going in reverse direction for once.
			++width;
			else if(moveDir == 'R')
			--width;
			clearTable();
			placePieces(piece.getPiece(), width, height, 0);
			assemble();
			draw(0);		//drawing the last state of the board before the game ends.
			_placeBoard = backup;
			sleep(3);
		}
		clearTable();
		return false;
	}
	else //vertical animation part
	{
		while(!overlap() && height > 0) //overlapping here will not cause this function to return false because most probably game has still some room to play because it passed vertical animation part,
		{								//which means it has plenty of space.
			// cout << "\nANIMATE\n";
			clearTable();
			placePieces(piece.getPiece(), width, height, 0);
			cout << "\033[2J" << "\033[0;0f";
			if(assemble())	//if no overlapping occcurs when assembling _placeBoard and _board, the assembled board will be printed to the screen. this is used for the prevention of invalid draw() calls where two pieces overlap.
				draw(0);
			_placeBoard = backup;
			usleep(200000);
			--height;
		}
		if(overlap())
			height += 2;
		// cout << " \033[u";
		placePieces(piece.getPiece(), width, height);
		clearTable();
		return true;
	}
}

Tetris::Tetris(const int height,const int width) : _board(height, width) , _placeBoard(height, width), backup(height, width)
{
	_width = width;
	_height = height;
	_pieceCount = 0;
}

void Tetris::draw(int flag) //game plays in a horizontally reverse direction. so both pieces and the board are flipped horizontally. It has been done like this because it makes the code more readable and more versatile.
{
	if(flag)
	{
		for(int k = 0; k < _board.getCol() + 2; k++)
			cout << '#';
		cout << endl;
		for(int i = _board.getRow() - 1; i >= 0; i--)
		{
			cout << '#';
			for(int j = 0; j < _board.getCol(); j++)
				cout << static_cast<char>(_board.at(i, j));
			cout << '#';
			cout << endl;
		}
		for(int k = 0; k < _board.getCol() + 2; k++)
			cout << '#';
		cout << endl;
		cout << endl;
		return;
	}

	for(int k = 0; k < _placeBoard.getCol() + 2; k++)
		cout << '#';
	cout << endl;
	for(int i = _placeBoard.getRow() - 1; i >= 0; i--)
	{
		cout << '#';
		for(int j = 0; j < _placeBoard.getCol(); j++)
			cout << (char)_placeBoard.at(i, j);
		cout << '#';
		cout << endl;
	}
	for(int k = 0; k < _placeBoard.getCol() + 2; k++)
		cout << '#';
	cout << endl;
	return ;
}

void Tetris::clearTable() //clears the always used temporary _placeBoard vector.
{
	for(int i = 0; i < _placeBoard.getRow(); i++)
		for(int j = 0; j < _placeBoard.getCol(); j++)
			_placeBoard.at(i, j) = Shape::Empty;
}

bool Tetris::assemble() //makes union of _placeBoard and _board.
{
	backup = _placeBoard;
	for(int i = 0; i < getHeight(); i++)
		for(int j = 0; j < getWidth(); j++)
		{
			if(_placeBoard.at(i,j) == Shape::Empty && _board.at(i,j) != Shape::Empty)
				_placeBoard.at(i,j) = _board.at(i,j);
			else if(_placeBoard.at(i,j) != Shape::Empty && _board.at(i,j) != Shape::Empty)
				return false;
		}
	return true;
}