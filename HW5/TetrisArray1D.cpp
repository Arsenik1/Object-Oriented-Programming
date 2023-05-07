#include "TetrisArray1D.hh"

TetrisArray1D::TetrisArray1D()
{
	_width = _height = 0;
}

TetrisArray1D::TetrisArray1D(const int height,const int width) :  _placeBoard(height, vector<Shape>(width, Shape::Empty)) , backup(height, vector<Shape>(width, Shape::Empty))
{
	_board = new Shape[height * width];
	for(int i = 0; i < height * width; ++i)
		_board[i] = Shape::Empty;
	_width = width;
	_height = height;
	_pieceCount = 0;
}

TetrisArray1D::~TetrisArray1D()
{
	delete _board; 
	// cout << "\nSELF DESTRUCTION\n"<< _height << endl;
}


bool TetrisArray1D::resize(int height, int width, Shape defaultVal) //even works in trivial cases where e.g: _height = 5 _width = 5 but the new height = 10 width = 3. You can compare it with vector::resize(), it has different output(i think it is a better output).
{
	Shape *temp;
	int resize_height = _height, resize_width = _width;

	if(_height > 0 && _width > 0)	//if we have allocated before, height and width becomes >0
	{
		temp = new Shape[size()];
		for(int i = 0; i < size(); i++)
			temp[i] = _board[i];
		delete _board;
	}

	_board = new Shape[height * width];
	if(height < _height)
		resize_height = height;
	if(width < _width)
		resize_width = width;
	
	for(int i = 0; i < resize_height; i++)		//the array sets itself according to the new size. It does this while losing the least possible data.
		for(int j = 0; j < resize_width; j++)
			this->at(i,j) = temp[i * _width + j];

	for(int i = _height; i < height; i++)
		for(int j = _width; j < width; j++)
			_board[i * _width + j] = defaultVal;
	if(height > _height)
		for(int i = _height; i < height; i++)
			for(int j = 0; j < width; j++)
				_board[i * _width + j] = defaultVal;
	if(width > _width)
		for(int i = 0; i < height; i++)
			for(int j = _width; j < width; j++)
				_board[i * _width + j] = defaultVal;

	// cout << height << width << (char)_board[0][1] << 3 << endl << endl;
	// cout << endl;
	// for(int i = _height; i < height; i++)
	// {
	// 	for(int j = _width; j < width; j++)
	// 		cout << (char)_board[i][j];
	// 	cout << endl;
	// }
	_height = height;
	_width = width;
	// sleep(1);
	return true;
}

Shape* TetrisArray1D::getBoard() const
{
	return _board;
}


const int TetrisArray1D::getRow() const
{
	return _height;
}

const int TetrisArray1D::getCol() const
{
	return _width;
}

void TetrisArray1D::setCol(int width)
{
	if(width > 0)
		_width = width;
}

void TetrisArray1D::setRow(int height)
{
	if(height > 0)
		_height = height;
}

void TetrisArray1D::operator+=(Tetromino& piece)
{
	int middle = _placeBoard.at(0).size() / 2 - (piece.getPiece().at(0).size() / 2);
	if(piece.getType() != Shape::Empty)
	{
		for(int i = 0; i < piece.getPiece().size(); i++)
			{
				for(int j = 0; j < piece.getPiece().at(0).size(); j++)
					if(piece.getPiece().at(i).at(j) != Shape::Empty )
						_placeBoard[_height - piece.getPiece().size() + i][middle + j] = piece.getPiece().at(i).at(j);
			}
	}
	// cout << piece.getPiece().getRow()<< endl;
	// for(int i = 0; i < _height; i++)
	// {
	// 	for(int j = 0; j < _width; j++)
	// 		cout << (char)_board[i][j];
	// 	cout << endl;
	// }
	// cout << piece.getPiece().getCol()<<endl;
	// cout << "\nOPERATOR +=\n";
}

TetrisArray1D& TetrisArray1D::operator=(TetrisArray1D& board) //deep copying
{
	delete _board;

	_board = new Shape[board.getRow()];

	for(int i = 0; i < board.size(); i++)
		_board[i] = board.at(i);
	_height = board._height;
	_width = board._width;
	_pieceCount = board._pieceCount;
	return *this;
}

Shape& TetrisArray1D::at(const int index) const
{
	if(index >= 0 && index < _height * _width)
		return _board[index * _width];
	return _board[0];
}

Shape& TetrisArray1D::at(const int row, const int col) const
{
	if(row >= 0 && col >= 0 && row < _height && col < _width)
		return _board[row * getCol() + col];
	return _board[0];
}

const int TetrisArray1D::size() const
{
	return _height * _width;
}


bool TetrisArray1D::assemble() //makes union of _placeBoard and _board.
{
	backup = _placeBoard;
	for(int i = 0; i < getRow(); i++)
		for(int j = 0; j < getCol(); j++)
		{
			if(_placeBoard.at(i).at(j) == Shape::Empty && this->at(i,j) != Shape::Empty)
				_placeBoard.at(i).at(j) = this->at(i,j);
			else if(_placeBoard.at(i).at(j) != Shape::Empty && this->at(i,j) != Shape::Empty)
			{
				clearTable();
				return false;
			}
		}
	return true;
}


void TetrisArray1D::clearTable() //clears the always used temporary _placeBoard vector.
{
	for(int i = 0; i < _placeBoard.size(); i++)
		for(int j = 0; j < _placeBoard.at(0).size(); j++)
			_placeBoard.at(i).at(j) = Shape::Empty;
}


void TetrisArray1D::draw(int flag) //game plays in a horizontally reverse direction. so both pieces and the board are flipped horizontally. It has been done like this because it makes the code more readable and more versatile.
{
	if(flag)
	{
		for(int k = 0; k < this->getCol() + 2; k++)
			cout << '#';
		cout << endl;
		for(int i = this->getRow() - 1; i >= 0; i--)
		{
			cout << '#';
			for(int j = 0; j < this->getCol(); j++)
				cout << static_cast<char>(this->at(i, j));
			cout << '#';
			cout << endl;
		}
		for(int k = 0; k < this->getCol() + 2; k++)
			cout << '#';
		cout << endl;
		cout << endl;
		cout << "Number of moves played: "<< numberOfMoves() << endl << endl;
		return;
	}

	for(int k = 0; k < _placeBoard.at(0).size() + 2; k++)
		cout << '#';
	cout << endl;
	for(int i = _placeBoard.size() - 1; i >= 0; i--)
	{
		cout << '#';
		for(int j = 0; j < _placeBoard.at(0).size(); j++)
			cout << (char)_placeBoard.at(i).at(j);
		cout << '#';
		cout << endl;
	}
	for(int k = 0; k < _placeBoard.at(0).size() + 2; k++)
		cout << '#';
	cout << endl;
	return ;
}

bool TetrisArray1D::animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount) //burasını değiştirmen lazım animate ederken gelecek yerde overlap var mı kontrol edip devam edecek
{
	//fit gidecek
	int	height = getRow() - piece.getPiece().size();				//setting the initial places, which means top middle in here.
	int	width = getCol() / 2 - (piece.getPiece().at(0).size() / 2);

	*this += piece;
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

	*this += piece;
	if(overlap())
		return false;
	clearTable();

	while(moveCount > 0 && width >= 0 && width < getCol() - piece.getPiece().at(0).size() && !overlap())	//horizontal animation part
	{
		clearTable();
		placePieces(piece, width, height, 0);
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
	if(width < 0)
		width = 0;

	if(height < 0 || overlap())	//this is a check for vertical animation. when going horizontal, if height somehow becomes negative or especially when an overlap occurs, it means that there is not much space left.
	{							//returning false will cause the game to end.
		if(overlap())
		{
			if(moveDir == 'L')	//restoring to the place one step before by going in reverse direction for once.
			++width;
			else if(moveDir == 'R')
			--width;
			clearTable();
			placePieces(piece, width, height, 0);
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
			placePieces(piece, width, height, 0);
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
		placePieces(piece, width, height);
		clearTable();
		del_line();
		return true;
	}
}

bool TetrisArray1D::overlap()  			 //looks for overlap between _placeBoard and _board. placeBoard contains a piece in a spesific coordinate.
{							 		//and this function checks the same coordinates in the actual game table. it looks for piece overlap.
	int size1 = getRow(), size2;
	for(int i = 0; i < size1; i++)
	{
		size2 = getCol();
		for(int j = 0; j < size2; j++)
		{
			if(this->at(i, j) != Shape::Empty && _placeBoard.at(i).at(j) != Shape::Empty)
				return true;
		}
	}
	return false;
}

void TetrisArray1D::placePieces(Tetromino &piece, int col,int row, int where)
{
	int size1 = piece.getPiece().size();
	if(where)
		for(int i = 0; i < size1; i++)
		{
			// cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
			decltype(size1) size2 = piece.getPiece().at(0).size();
			for(int j = 0; j < size2; j++)
				if(piece.getPiece().at(i).at(j) != Shape::Empty )
					this->at(row + i, col + j) = piece.getPiece().at(i).at(j);
		}
	else
		for(int i = 0; i < size1; i++)
		{
			decltype(size1) size2 = piece.getPiece().at(0).size();
			for(int j = 0; j < size2; j++)
				if(piece.getPiece().at(i).at(j) != Shape::Empty )
					_placeBoard.at(row + i).at(col + j) = piece.getPiece().at(i).at(j);
		}
}

void TetrisArray1D::readFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if(!file.is_open())
	{
		std::cerr << "File could not be opened!\n";
		exit(1);
	}
	std::string line;
	int row = 0;
	
	int width, height;
	file >> width >> height;
	this->resize(height,_width);
	getline(file, line); //to get rid of the line that y
	while(getline(file, line))
	{
		for(int i = 0; i < line.size(); i++)
			this->at(row, i) = Tetromino::returnShape(line.at(i));
		++row;
	}
	file.close();
}
void TetrisArray1D::writeToFile(const std::string& filename)
{
	std::ofstream file(filename);
	if(!file.is_open())
	{
		std::cerr << "File could not be opened!\n";
		exit(1);
	}
	file << _width << " " << _height << endl;
	for(int i = 0; i < getRow(); i++)
	{
		for(int j = 0; j < getCol(); j++)
			file << (char)this->at(i, j);
		file << std::endl;
	}
	file.close();	
}
TetrominoMove TetrisArray1D::lastMove() const
{
	return _lastMove;
}

int TetrisArray1D::numberOfMoves() const
{
	return _numberOfMoves;
}

void TetrisArray1D::syncBoard()
{
	for(int i = 0; i < getRow(); i++)
		for(int j = 0; j < getCol(); j++)
			_placeBoard.at(i).at(j) = this->at(i, j);
}


void TetrisArray1D::del_line()
{
	int counter = 0;
	for(int i = 0; i < this->getHeight(); i++)
	{
		counter = 0;
		for(int j = 0; j < this->getWidth(); j++)
			if(this->at(i, j) != Shape::Empty)
				counter++;
		if(counter == this->getWidth())
		{
			for(int a = i; a < this->getHeight() - 1; a++)
			{
				for(int b = 0; b < this->getWidth(); b++)
					this->at(a, b) = this->at(a + 1, b);
			}
		}
	}
}