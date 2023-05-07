#include "Tetris.hh"

TwoD::TwoD()
{
	_width = _height = 0;
}

TwoD::TwoD(Shape piece)
{
	// cout << "\nShape constructor\n\n";
	_width = 0;
	_height = 0;
	int height, width;
	if(piece == Shape::S || piece == Shape::Z || piece == Shape::T)
	{
		height = 2;
		width = 3;
	}
	else if(piece == Shape::J || piece == Shape::L )
	{
		height = 3;
		width = 2;
	}
	else if(piece == Shape::I)
	{
		height = 4;
		width = 1;
	}
	else if(piece == Shape::O)
	{
		height = 2;
		width = 2;
	}
	else
	{
		height = 0;
		width = 0;
	}

	if(height == 0) //it means that constructor has been called because of an error. possibly piece == Shape::Empty in this condition.
		exit(1);

	resize(height, width);
	// cout << "\nsssssssssssssssss\n";
	// sleep(1);
	setPiece(piece);
	// cout << endl << endl << _height << _width << endl << endl;
}

TwoD::TwoD(int height, int width, Shape defaultVal) //creates a TwoD at with the expected size and default value.
{
	_height = _width = 0;
	resize(height, width);
	for(int i = 0; i < _height; i++)
		for(int j = 0;j < _width; j++)
			_vec[i][j] = defaultVal;

	// cout << "\nccccccccccccccccccccccccccccccccccc\n";
}

TwoD::~TwoD()
{
	for(int i = 0; i < _height; i++)
		delete _vec[i];
	delete _vec; 
	// cout << "\nSELF DESTRUCTION\n"<< _height << endl;
}


bool TwoD::resize(int height, int width, Shape defaultVal) //even works in trivial cases where e.g: _height = 5 _width = 5 but the new height = 10 width = 3. You can compare it with vector::resize(), it has different output(i think it is a better output).
{
	Shape **temp;
	int resize_height = _height, resize_width = _width;

	if(_height > 0 && _width > 0)	//if we have allocated before, height and width becomes >0
	{
		temp = new Shape*[_height];
		for(int i = 0; i < _height; i++)
			temp[i] = new Shape[_width];

		for(int i = 0; i < _height; i++)
			for(int j = 0; j < _width; j++)
				temp[i][j] = _vec[i][j];

		for(int i = 0; i < _height; i++)
			delete _vec[i];
		delete _vec;
	}

	_vec = new Shape*[height];
	for(int i = 0; i < height; i++)
		_vec[i] = new Shape[width];

	if(height < _height)
		resize_height = height;
	if(width < _width)
		resize_width = width;
	
	for(int i = 0; i < resize_height; i++)		//the array sets itself according to the new size. It does this while losing the least possible data.
		for(int j = 0; j < resize_width; j++)
			this->at(i,j) = temp[i][j];

	for(int i = _height; i < height; i++)
		for(int j = _width; j < width; j++)
			_vec[i][j] = defaultVal;
	if(height > _height)
		for(int i = _height; i < height; i++)
			for(int j = 0; j < width; j++)
				_vec[i][j] = defaultVal;
	if(width > _width)
		for(int i = 0; i < height; i++)
			for(int j = _width; j < width; j++)
				_vec[i][j] = defaultVal;

	// cout << height << width << (char)_vec[0][1] << 3 << endl << endl;
	// cout << endl;
	// for(int i = _height; i < height; i++)
	// {
	// 	for(int j = _width; j < width; j++)
	// 		cout << (char)_vec[i][j];
	// 	cout << endl;
	// }
	_height = height;
	_width = width;
	// sleep(1);
	return true;
}

void TwoD::setPiece(Shape shape)
{
	if(shape == Shape::I)
	{
		for(int i = 0; i < 4; i++)
			_vec[i][0] = Shape::I;
	}
	else if(shape == Shape::O)
	{
		_vec[0][0] = Shape::O;
		_vec[0][1] = Shape::O;
		_vec[1][0] = Shape::O;
		_vec[1][1] = Shape::O;
	}
	else if(shape == Shape::T)
	{
		for(int i = 0; i < 3; i++)
			_vec[0][i] = Shape::T;
		_vec[1][1] = Shape::T;
	}
	else if(shape == Shape::J)
	{
		_vec[0][0] = Shape::J;
		_vec[0][1] = Shape::J;
		_vec[1][1] = Shape::J;
		_vec[2][1] = Shape::J;
	}
	else if(shape == Shape::L)
	{
		for(int i = 0; i < 3; i++)
			_vec[i][0] = Shape::L;
		_vec[0][1] = Shape::L;
	}
	else if(shape == Shape::S)
	{
		_vec[0][0] = Shape::S;
		_vec[0][1] = Shape::S;
		_vec[1][1] = Shape::S;
		_vec[1][2] = Shape::S;
	}
	else if(shape == Shape::Z)
	{
		_vec[0][2] = Shape::S;
		_vec[0][1] = Shape::S;
		_vec[1][1] = Shape::S;
		_vec[1][0] = Shape::S;
	}
	// cout << endl;
	// for(int i = 0; i < _height; i++)
	// {
	// 	for(int j = 0; j < _width; j++)
	// 		cout << (char)_vec[i][j];
	// 	cout << endl;
	// }
	// sleep(3);
	// cout << endl << endl << _height << _width << endl << endl;
}

Shape** TwoD::getVec() const
{
	return _vec;
}


const int TwoD::getRow() const
{
	return _height;
}

const int TwoD::getCol() const
{
	return _width;
}

void TwoD::setCol(int width)
{
	if(width > 0)
		_width = width;
}

void TwoD::setRow(int height)
{
	if(height > 0)
		_height = height;
}

TwoD& TwoD::operator+=(Tetromino& piece)
{
	int middle = getCol() / 2 - (piece.getPiece().getCol() / 2);
	if(piece.getType() != Shape::Empty)
	{
		for(int i = 0; i < piece.getPiece().getRow(); i++)
			{
				for(int j = 0; j < piece.getPiece().getCol(); j++)
					if(piece.getPiece().at(i,j) != Shape::Empty )
						_vec[_height - piece.getPiece().getRow() + i][middle + j] = piece.getPiece().at(i,j);
			}
	}
	// cout << piece.getPiece().getRow()<< endl;
	// for(int i = 0; i < _height; i++)
	// {
	// 	for(int j = 0; j < _width; j++)
	// 		cout << (char)_vec[i][j];
	// 	cout << endl;
	// }
	// cout << piece.getPiece().getCol()<<endl;
	// cout << "\nOPERATOR +=\n";
	return *this;
}

TwoD& TwoD::operator=(TwoD& vec) //deep copying
{
	for(int i = 0; i < _height; i++)
		delete _vec[i];
	delete _vec;

	_vec = new Shape*[vec.getRow()];
	for(int i = 0; i < vec.getRow(); i++)
		_vec[i] = new Shape[vec.getRow()];

	for(int i = 0; i < vec.getRow(); i++)
		for(int j = 0; j < vec.getCol(); j++)
			_vec[i][j] = vec.getVec()[i][j];

	return *this;
}

Shape*& TwoD::at(const int index) const
{
	if(index >= 0 && index < _height)
		return _vec[index];
	return _vec[0];
}

Shape& TwoD::at(const int row, const int col) const
{
	if(row >= 0 && col >= 0 && row < _height && col < _width)
		return _vec[row][col];
	return _vec[0][0];
}