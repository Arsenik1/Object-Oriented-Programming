#include "Tetris.hh"

void Tetromino::printPiece()
{
	for(int i = _piece.getRow() - 1; i >= 0; i--)
	{
		for(int j = 0; j < _piece.getCol(); j++)
			cout << (char)_piece.getVec()[i][j];
		cout << endl;
	}
}

void Tetromino::rotate(string dir)
{
	if(_type == Shape::O)
		return;

	int loopCount = 1;
	int height = _piece.getRow();
	decltype(height) width = _piece.getCol();
	if(dir == "left")
		loopCount = 3;

	_piece.resize(4, 4);
	TwoD rotationTemp(_piece.getRow(), _piece.getRow());	//when rotating, used for temporary storage. it is static because I need no other instances.
	// for(int i = 0; i < 4; i++)
	// {
	// 	for(int j = 0; j < 4; j++)
	// 		cout << (char)rotationTemp.at(i, j);
	// 	cout << endl;
	// }
	while(loopCount--)
	{
		for(int i = 0; i < _piece.getRow(); i++)
			for(int j = 0; j < _piece.getCol(); j++)
				rotationTemp.at(j,i) = _piece.getVec()[i][j];

		int size = _piece.getRow();
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
				_piece.at(i,j) = rotationTemp.at(i,size - 1 - j);
		}
	}
	moveCorner();
	// cout <<"\nROTATE\n";
	_piece.resize(width, height);
}

Tetromino::Tetromino() //default constructor
{
	TwoD piece;
	_type = Shape::Empty;
	_piece = piece;
}

Tetromino::Tetromino(Shape shape) : _piece(shape)
{
	// cout << endl << endl << _piece.getRow() << _piece.getCol() << endl << endl;
	_type = shape;
}

void Tetromino::setPiece(Shape shape)
{
	if(shape == Shape::I)
	{
		for(int i = 0; i < 4; i++)
			_piece.at(i,0) = Shape::I;
	}
	else if(shape == Shape::O)
	{
		_piece.at(0,0) = Shape::O;
		_piece.at(0,1) = Shape::O;
		_piece.at(1,0) = Shape::O;
		_piece.at(1,1) = Shape::O;
	}
	else if(shape == Shape::T)
	{
		for(int i = 0; i < 3; i++)
			_piece.at(0,i) = Shape::T;
		_piece.at(1,1) = Shape::T;
	}
	else if(shape == Shape::J)
	{
		_piece.at(0,0) = Shape::J;
		_piece.at(0,1) = Shape::J;
		_piece.at(1,1) = Shape::J;
		_piece.at(2,1) = Shape::J;
	}
	else if(shape == Shape::L)
	{
		for(int i = 0; i < 3; i++)
			_piece.at(i,0) = Shape::L;
		_piece.at(0,1) = Shape::L;
	}
	else if(shape == Shape::S)
	{
		_piece.at(0,0) = Shape::S;
		_piece.at(0,1) = Shape::S;
		_piece.at(1,1) = Shape::S;
		_piece.at(1,2) = Shape::S;
	}
	else if(shape == Shape::Z)
	{
		_piece.at(0,2) = Shape::S;
		_piece.at(0,1) = Shape::S;
		_piece.at(1,1) = Shape::S;
		_piece.at(1,0) = Shape::S;
	}
}

TwoD& Tetromino::getPiece()
{
	return _piece;
}

Shape Tetromino::getType() const
{
	return _type;
}

void Tetromino::setType(Shape type)
{
	_type = type;
}

Shape Tetromino::returnShape(char shape)
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

void Tetromino::moveCorner() //moves the shape to [0][0], corner of the vector
{
	int size = _piece.getRow();
	bool up = true, left = true;
	int i, j;
	while(up || left)
	{
		for(int a = 0; a < _piece.getCol(); a++)
			if(_piece.at(0,a) != Shape::Empty)
				up = false;
		for(int a = 0; a < _piece.getRow(); a++)
			if(_piece.at(a,0) != Shape::Empty)
				left = false;

		for(i = 1; i < _piece.getRow() && up == true; i++)
			for(j = 0; j < _piece.getRow(); j++)
				_piece.at(i - 1,j) = _piece.getVec()[i][j];
		if(up == true)
			for(i = 0; i < _piece.getRow() && up == true; i++)
				_piece.at(_piece.getRow() - 1,i) = Shape::Empty;

		for(i = 0; i < _piece.getRow() && left == true; i++)
			for(j = 1; j < _piece.getRow(); j++)
				_piece.at(i,j - 1) = _piece.getVec()[i][j];
		if(left == true)
			for(i = 0; i < _piece.getRow(); i++)
				_piece.at(i,_piece.getRow() - 1) = Shape::Empty;
	}
}