#include "Tetris.hh"

using namespace std;

int main()
{
	int height = 10, width = 14;
	int test;
	Shape testShape = Shape::S;
	Tetris game(10, 14);
	Tetromino piece(testShape);
	Tetromino tempPiece(testShape);
	vector<vector<Shape>> testVect(4, vector<Shape>(4, Shape::Empty));

	cout << "\nTest 1:";
	if(game.getHeight() == height && game.getWidth() == width)
		cout << "OK\n";
	else
		cout << "KO\n";

	sleep(3);
	cout << "\nTest 2:";
	if(game.add(piece) == true) //this also tests the fit, placePieces, overlap and clearTable functions.
		cout << "OK";
	else
		cout << "KO";
	
	cout << "\033[2J" << "\033[0;0f";
	cout << "\nTest 3:";
	test = game.getPieceCount();
	if(test == 0)
		cout << "OK";
	else
		cout << "KO";
	
	cout << "\nTest 4:";
	game.setPieceCount(test);
	if(game.getPieceCount() == test)
		cout << "OK";
	else
		cout << "KO";
	
	cout << "\nTest 5:";
	if(testVect != game.getBoard())
		cout << "OK";
	else
		cout << "KO";

	cout << "\nTest 6:";
	game.setBoard(testVect);
	if(testVect == game.getBoard())
		cout << "OK";
	else
		cout << "KO";
	
	cout << endl;
	sleep(3);
	cout << "\033[2J" << "\033[0;0f";
	game.add(piece);
	cout << "\nTest 7:";
	testVect = game.getPlaceBoard();
	if(testVect == game.getPlaceBoard())
		cout << "OK";
	else
		cout << "KO";

	cout << "\nTest 8:";
	game.setPlaceBoard(testVect);
	if(testVect == game.getPlaceBoard())
		cout << "OK";
	else
		cout << "KO";

	cout << "\nTest 9:";
	game.clearTable();
	if(testVect != game.getPlaceBoard())
		cout << "OK";
	else
		cout << "KO";

	cout << "\n\nTetris class tests complete. Starting Tetromino tests...\n"; //only the used functions in hw2 will be tested.
	
	cout << "\nTest 1:";	//this also tests moveCorner.
	tempPiece = piece;
	piece.rotate("right");
	piece.rotate("left");
	if(tempPiece.getPiece() == piece.getPiece())
		cout << "OK";
	else
		cout << "KO";
	
	cout << "\nTest 2:";
	if(testShape == piece.getType())
		cout << "OK";
	else
		cout << "KO";

	cout << "\nTest 3:";
	piece.setType(Shape::Empty);
	if(testShape != piece.getType())
		cout << "OK";
	else
		cout << "KO";

	cout << endl << "All tests are completed." << endl; //draw and print functions havent printed because they dont do anything and there is no way that i can
	return 0;											//test whether the characters are being printed to the screen.
}