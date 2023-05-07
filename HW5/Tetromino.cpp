#include "Tetromino.hh"

void Tetromino::printPiece() const
{
	for(int i = _piece.size() - 1; i >= 0; i--)
	{
		for(int j = 0; j < _piece[i].size(); j++)
			cout << (char)_piece[i][j];
		cout << endl;
	}
}

void Tetromino::rotate(string dir)
{
	if(_type == Shape::O)
		return;

	int loopCount = 1;
	int height = _piece.size();
	decltype(height) width = _piece.at(0).size();

	if(dir == "left")
		loopCount = 3;

	_piece.resize(4, vector<Shape>(4, Shape::Empty));
	for(int i = 0; i < _piece.size(); i++)
		_piece.at(i).resize(4, Shape::Empty);
	vector<vector<Shape>> rotationTemp(_piece.size(), vector<Shape>(_piece.size(), Shape::Empty));	//when rotating, used for temporary storage. it is static because I need no other instances.

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
	_piece.resize(width);
	for(int i = 0; i < _piece.size(); i++)
		_piece.at(i).resize(height, Shape::Empty);
}

Tetromino::Tetromino() //default constructor
{
	_type = Shape::Empty;
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
			{Shape::I},
			{Shape::I},
			{Shape::I},
			{Shape::I}
		};
	}
	else if(shape == Shape::O)
	{
		_piece = 
		{
			{Shape::O,Shape::O},
			{Shape::O,Shape::O}
		};
	}
	else if(shape == Shape::T)
	{
		_piece = 
		{
			{Shape::T,Shape::Empty},
			{Shape::T,Shape::T},
			{Shape::T,Shape::Empty}
		};
	}
	else if(shape == Shape::J)
	{
		_piece = 
		{
			{Shape::J,Shape::J},
			{Shape::Empty,Shape::J},
			{Shape::Empty,Shape::J}
		};
	}
	else if(shape == Shape::L)
	{
		_piece = 
		{
			{Shape::L,Shape::L},
			{Shape::L,Shape::Empty},
			{Shape::L,Shape::Empty}
		};
	}
	else if(shape == Shape::S)
	{
		_piece = 
		{
			{Shape::S,Shape::Empty},
			{Shape::S,Shape::S},
			{Shape::Empty,Shape::S}
		};
	}
	else if(shape == Shape::Z)
	{
		_piece = 
		{
			{Shape::Empty,Shape::Z},
			{Shape::Z,Shape::Z},
			{Shape::Z,Shape::S}
		};
	}
}

vector<vector<Shape>> &Tetromino::getPiece()
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

vector<Shape> &Tetromino::operator[](int index)	//returns the piece in the given index
{
	return _piece[index];
}

int Tetromino::height() const	//returns the height of the piece
{
	return _piece.size();
}

int Tetromino::width() const	//returns the width of the piece
{
	return _piece.at(0).size();
}