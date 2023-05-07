#ifndef __TETRIS_ADAPTER_HH__
#define __TETRIS_ADAPTER_HH__

#include "AbstractTetris.hh"

template <typename T>
class TetrisAdapter : public AbstractTetris
{
public:
	TetrisAdapter(const int height,const int width);
	TetrisAdapter(const TetrisAdapter& other);
	TetrisAdapter& operator=(const TetrisAdapter& other);

	void readFromFile(const std::string& filename) override;
	void writeToFile(const std::string& filename) override;
	TetrominoMove lastMove() const override;
	int numberOfMoves() const override;

	T& getBoard();
	void setBoard(const T board);
	T& getPlaceBoard();
	void setPlaceBoard(T& placeBoard) override;
	int getHeight() const override;
	int getWidth() const override;
	void placePieces(T &piece,int col, int row = 0, int where = 1);	//places a Tetromino to the board.
	bool overlap(); //checks overlap between _placeBoard and _board.
	void draw(int flag = 1) override;
	void clearTable() override; //clears placeBoard.
	bool animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount) override; //after adding, it animates and places the piece.
	bool assemble() override; //assembles board and placeboard into placeboard. returns true when no overlap happens
	void operator+=(Tetromino&) override; //adds the piece to the top middle
	const int getPieceCount() const;
	TetrominoMove getLastMove() const;
	void setLastMove(TetrominoMove lastMove);
	void setNumberOfMoves(int numberOfMoves);
	void syncBoard() override;
	void del_line() override;

private:
	int _width;
	int _height;
	int _pieceCount;
	int _numberOfMoves;
	TetrominoMove _lastMove;
	T _board;
	T _placeBoard;
	T backup; //it is used for the assemble() function. when _placeBoard and _board are assembled to _placeBoard, the old version of _placeBoard is backed up in this variable.
};


template <typename T>
void TetrisAdapter<T>::syncBoard()
{
	setPlaceBoard(getBoard());
}


template <typename T>
TetrisAdapter<T>::TetrisAdapter(const int height,const int width) :_board(height, vector<Shape>(width, Shape::Empty)) , _placeBoard(height, vector<Shape>(width, Shape::Empty)),
							 backup(height, vector<Shape>(width, Shape::Empty)), _height(height), _width(width), _pieceCount(0), _numberOfMoves(0), _lastMove({Shape::Empty, 0, 0})
{
}

template <typename T>
TetrisAdapter<T>::TetrisAdapter(const TetrisAdapter& other) : _height(other.getHeight()), _width(other.getWidth()), _pieceCount(other.getPieceCount()), _numberOfMoves(other.numberOfMoves()), _lastMove(other.getLastMove())
{
	_board = other._board;
	_placeBoard = other._placeBoard;
	backup = other.backup;
}

template <typename T>
TetrisAdapter<T>& TetrisAdapter<T>::operator=(const TetrisAdapter& other)
{
	if (this != &other)
	{
		_board = other._board;
		_placeBoard = other._placeBoard;
		backup = other.backup;
		_height = other.getHeight();
		_width = other.getWidth();
		_pieceCount = other.getPieceCount();
		_numberOfMoves = other.numberOfMoves();
		_lastMove = other.getLastMove();
	}
	return *this;
}

template <typename T>
T &TetrisAdapter<T>::getBoard()
{
	return _board;
}


template <typename T>
void TetrisAdapter<T>::setBoard(T board)
{
	_board = board;
}

template <typename T>
T& TetrisAdapter<T>::getPlaceBoard()
{
	return _placeBoard;
}

template <typename T>
void TetrisAdapter<T>::setPlaceBoard(T& placeBoard)
{
	_placeBoard = placeBoard;
}

template <typename T>
int TetrisAdapter<T>::getHeight() const
{
	return _height;
}

template <typename T>
int TetrisAdapter<T>::getWidth() const
{
	return _width;
}

template <typename T>
const int TetrisAdapter<T>::getPieceCount() const
{
	return _pieceCount;
}

template <typename T>
int TetrisAdapter<T>::numberOfMoves() const
{
	return _numberOfMoves;
}
template <typename T>
TetrominoMove TetrisAdapter<T>::getLastMove() const
{
	return _lastMove;
}
template <typename T>
void TetrisAdapter<T>::setLastMove(TetrominoMove lastMove)
{
	if(lastMove.piece.getType() != Shape::Empty && lastMove.moveCount >= 0 && lastMove.rotateCount >= 0 && lastMove.rotateDir != ' ' && lastMove.moveDir != ' ')
		_lastMove = lastMove;
}
template <typename T>
void TetrisAdapter<T>::setNumberOfMoves(int numberOfMoves)
{
	if(numberOfMoves >= 0)
		_numberOfMoves = numberOfMoves;
}

template <typename T>
void TetrisAdapter<T>::placePieces(T &piece, int col,int row, int where)
{
	int size1 = piece.size();
	// cout << col << " " << row << endl;
	if(where)
		for(int i = 0; i < size1; i++)
		{
			decltype(size1) size2 = piece.at(i).size();
			for(int j = 0; j < size2; j++)
				if(piece.at(i).at(j) != Shape::Empty )
					_board.at(row + i).at(col + j) = piece.at(i).at(j);
		}
	else
		for(int i = 0; i < size1; i++)
		{
			decltype(size1) size2 = piece.at(i).size();
			for(int j = 0; j < size2; j++)
				if(piece.at(i).at(j) != Shape::Empty )
					_placeBoard.at(row + i).at(col + j) = piece.at(i).at(j);
		}
}

template <typename T>
bool TetrisAdapter<T>::overlap()  			 //looks for overlap between _placeBoard and _board. placeBoard contains a piece in a spesific coordinate.
{							 		//and this function checks the same coordinates in the actual game table. it looks for piece overlap.
	int size1 = getHeight(), size2;
	for(int i = 0; i < size1; i++)
	{
		size2 = getWidth();
		for(int j = 0; j < size2; j++)
		{
			if(_board.at(i).at(j) != Shape::Empty && _placeBoard.at(i).at(j) != Shape::Empty)
				return true;
		}
	}
	return false;
}

template <typename T>
bool TetrisAdapter<T>::animate(Tetromino &piece, char rotateDir, int rotateCount, char moveDir, int moveCount) //burasını değiştirmen lazım animate ederken gelecek yerde overlap var mı kontrol edip devam edecek
{

	*this += piece;
	if(overlap())	//initial overlap check
		return false;
	clearTable();
	_lastMove.piece = piece;
	_lastMove.moveDir = moveDir;
	_lastMove.rotateDir = moveCount;
	_lastMove.rotateCount = rotateCount % 4;
	_lastMove.moveCount = moveCount;
	++_numberOfMoves;
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

	int	height = getHeight() - piece.getPiece().size();				//setting the initial places, which means top middle in here.
	int	width = _board.at(0).size() / 2 - (piece.getPiece().at(0).size() / 2);

	while(moveCount > 0 && width >= 0 && width < _board.at(0).size() - piece.getPiece().at(0).size() && !overlap() )	//horizontal animation part
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
		if(height < 0)
			height = 0;
		if(overlap())
			height += 2;
		// cout << " \033[u";
		placePieces(piece.getPiece(), width, height);
		clearTable();
		del_line();
		return true;
	}
}

template <typename T>
void TetrisAdapter<T>::draw(int flag) //game plays in a horizontally reverse direction. so both pieces and the board are flipped horizontally. It has been done like this because it makes the code more readable and more versatile.
{
	if(flag)
	{
		for(int k = 0; k < _board.at(0).size() + 2; k++) 
			cout << '#';
		cout << endl;
		for(int i = _board.size() - 1; i >= 0; i--)
		{
			cout << '#';
			for(int j = 0; j < _board.at(0).size(); j++)
				cout << static_cast<char>(_board.at(i).at(j));
			cout << '#';
			cout << endl;
		}
		for(int k = 0; k < _board.at(0).size() + 2; k++)
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

template <typename T>
void TetrisAdapter<T>::clearTable() //clears the always used temporary _placeBoard vector.
{
	for(int i = 0; i < _placeBoard.size(); i++)
		for(int j = 0; j < _placeBoard.at(0).size(); j++)
			_placeBoard.at(i).at(j) = Shape::Empty;
}

template <typename T>
bool TetrisAdapter<T>::assemble() //makes union of _placeBoard and _board.
{
	backup = _placeBoard;
	for(int i = 0; i < getHeight(); i++)
		for(int j = 0; j < getWidth(); j++)
		{
			if(_placeBoard.at(i).at(j) == Shape::Empty && _board.at(i).at(j) != Shape::Empty)
				_placeBoard.at(i).at(j) = _board.at(i).at(j);
			else if(_placeBoard.at(i).at(j) != Shape::Empty && _board.at(i).at(j) != Shape::Empty)
				return false;
		}
	return true;
}

template <typename T>
void TetrisAdapter<T>::operator+=(Tetromino& piece) //places the piece on the board.
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

	// int middle = getCol() / 2 - (piece.getPiece().getCol() / 2);
	// if(piece.getType() != Shape::Empty)
	// {
	// 	for(int i = 0; i < piece.getPiece().getRow(); i++)
	// 		{
	// 			for(int j = 0; j < piece.getPiece().getCol(); j++)
	// 				if(piece.getPiece().at(i,j) != Shape::Empty )
	// 					_vec[_height - piece.getPiece().getRow() + i][middle + j] = piece.getPiece().at(i,j);
	// 		}
	// }

	// cout << piece.getPiece().getRow()<< endl;
	// for(int i = 0; i < _height; i++)
	// {
	// 	for(int j = 0; j < _width; j++)
	// 		cout << (char)_vec[i][j];
	// 	cout << endl;
	// }
	// cout << piece.getPiece().getCol()<<endl;
	// cout << "\nOPERATOR +=\n";
}

template <typename T>
void TetrisAdapter<T>::readFromFile(const string& filename) //reads the board from a file.
{
	ifstream file;
	file.open(filename);
	char a;
	if(file.is_open())
	{
		file >> _width >> _height;
		_board.resize(_height);
		for(int i = 0; i < _height; i++)
			_board[i].resize(_width);
		for(int i = 0; i < _height; i++)
		{
			a = file.get(); //i dont'know why but it is necessary. it skips the newline character.
			for(int j = 0; j < _width; j++)
			{
				a = file.get();
				if(a != '\n')
					_board[i][j] = (Shape)a; 
			}
		}
	}
	else
		cerr << "File could not be opened." << endl;
	file.close();
}

template <typename T>
void TetrisAdapter<T>::writeToFile(const std::string& filename) //writes the current board to a file.
{
	ofstream file;
	file.open(filename);
	if(file.is_open())
	{
		file << _width << " " << _height << endl;
		for(int i = 0; i < _height; i++)
		{
			for(int j = 0; j < _width; j++)
				file << (char)_board[i][j];
			file << endl;
		}
	}
	else
		cerr << "File could not be opened." << endl;
	file.close();
}

template <typename T>
TetrominoMove TetrisAdapter<T>::lastMove() const //returns the last move.
{
	return _lastMove;
}

template <typename T>
void TetrisAdapter<T>::del_line()
{
	int counter = 0;
	for(int i = 0; i < this->getHeight(); i++)
	{
		counter = 0;
		for(int j = 0; j < this->getWidth(); j++)
			if(_board[i][j] != Shape::Empty)
				counter++;
		if(counter == this->getWidth())
		{
			for(int a = i; a < this->getHeight() - 1; a++)
			{
				for(int b = 0; b < this->getWidth(); b++)
					_board[a][b] = _board[a + 1][b];
			}
		}
	}
}

#endif