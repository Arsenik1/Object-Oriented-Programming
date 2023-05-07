#include "header.hh"

int main()
{
	int pieceCount = 0;
	char shapeType = ' ';
	vector<Tetromino> tetrominos;
	cout << "How many tetrominos?" << endl;
	cin >> pieceCount;
	tetrominos.resize(pieceCount);
	cin.clear();
	cout << "What are the types?" << endl;
	for(int i = 0; i < pieceCount; i++)
	{
		cin >> shapeType;
		Tetromino piece(piece.returnShape(shapeType));
		if(piece.getType() == Shape::Empty)
		{
			cout << endl << "Invalid input." << endl;
			--i;
			continue;	//resetting loop if an invalid input is given.
		}
		tetrominos.at(i) = piece;
		cin.clear();
	}
	Board board(pieceCount, tetrominos);
	cout << endl<< endl <<"Your tetrominos" << endl;
	for(auto i : tetrominos)
	{
		i.printPiece();
		cout << endl;
	}
	cout << endl << "--------------------------" << endl;
	board.placePieces(tetrominos[0].getPiece(), 0);
	int i = 1;
	int j;
	while(i < pieceCount)
	{
		if(tetrominos[i - 1].canFit(tetrominos[i], "right"))
		{
			for(j = 1; board.getBoard()[0][j] != Shape::Empty; j++);
				board.placePieces(tetrominos[i].getPiece(), j, 0);
		}
		else
		{
			cout << "\nFit error in incoming tetromino \"";
			cout << (char)tetrominos[i].getType();
			cout <<"\", cannot fit the rest of the pieces\n";
			i = pieceCount;
		}
		i++;
	}
	board.printBoard();
	return 0;
}