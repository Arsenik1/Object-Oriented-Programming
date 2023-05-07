#include "TetrisVector.hh"
#include "TetrisAdapter.cpp"
#include "TetrisArray1D.hh"

using namespace std;

int main()
{
	//TetrisVector testing driver code
	sleep(1);
	cout << "TetrisVector testing driver code" << endl << endl;
	TetrisVector tetrisVector(10, 10);
	sleep(1);
	tetrisVector.draw();
	sleep(1);
	cout << "Creating a Tetromino of type \"S\"" << endl;
	Tetromino tetromino(Shape::S);
	sleep(1);
	cout << "\nTesting one-step animation of a Tetromino:" << endl;
	sleep(2);
	tetrisVector.animate(tetromino, 'R', 1, 'L', 1);
	sleep(1);
	cout << "\033[2J\033[1;1H" << endl;
	tetromino.printPiece();
	sleep(1);
	cout << "Adding the Tetromino to the TetrisVector:" << endl;
	tetrisVector += tetromino;
	sleep(1);
	tetrisVector.draw(0);
	sleep(1);
	cout << "Writing to file \"test.txt\":" << endl;
	sleep(1);
	tetrisVector.draw();
	tetrisVector.writeToFile("test.txt");
	cout << "Reading from file \"test.txt\":" << endl;
	tetrisVector.readFromFile("test.txt");
	sleep(1);
	sleep(1);
	cout << "Number of moves: " << endl;
	sleep(1);
	cout << tetrisVector.numberOfMoves() << endl << endl;
	//VECTOR TEST

	//TetrisArray1D testing driver code
	sleep(1);
	cout << "TetrisArray1D testing driver code" << endl << endl;
	TetrisArray1D tetrisArray1D(20, 10);
	sleep(1);
	tetrisArray1D.draw();
	sleep(1);
	cout << "Creating a Tetromino of type \"S\"" << endl;
	Tetromino tetromino_ar(Shape::S);
	sleep(1);
	cout << "\nTesting one-step animation of a Tetromino:" << endl;
	sleep(2);
	tetrisArray1D.animate(tetromino_ar, 'R', 1, 'L', 1);
	sleep(1);
	cout << "\033[2J\033[1;1H" << endl;
	sleep(1);
	cout << "Adding the Tetromino to the TetrisArray1D:" << endl;
	tetrisArray1D += tetromino_ar;
	sleep(1);
	tetrisArray1D.draw(0);
	sleep(1);
	cout << "Writing to file \"test.txt\":" << endl;
	sleep(1);
	tetrisArray1D.draw();
	tetrisArray1D.writeToFile("test.txt");
	cout << "Reading from file \"test.txt\":" << endl;
	tetrisArray1D.readFromFile("test.txt");
	sleep(1);
	//ARRAY1D TEST

	//TetrisAdapter<vector<vector<Shape>>> testing driver code
	cout << "TetrisAdapter<vector<vector<Shape>>> testing driver code" << endl << endl;
	TetrisAdapter<vector<vector<Shape>>> tetrisAdapterVector(10, 10);
	sleep(1);
	tetrisAdapterVector.draw();
	cout << "Creating a Tetromino of type \"L\"" << endl;
	Tetromino tetromino_vec(Shape::L);
	cout << "\nTesting one-step animation of a Tetromino:" << endl;
	cout << "\033[2J\033[1;1H" << endl;
	tetrisAdapterVector.animate(tetromino_vec, 'R', 1, 'L', 1);
	sleep(2);
	cout << "\033[2J\033[1;1H" << endl;
	sleep(1);
	tetrisAdapterVector.draw();
	cout << "Adding the Tetromino to the TetrisAdapterVector:" << endl;
	tetrisAdapterVector += tetromino_vec;
	sleep(1);
	tetrisAdapterVector.draw(0);
	sleep(1);
	cout << "Writing to file \"test.txt\":" << endl;
	tetrisAdapterVector.writeToFile("test.txt");
	sleep(1);
	tetrisAdapterVector.draw();
	cout << "Reading from file \"test.txt\":" << endl;
	tetrisAdapterVector.readFromFile("test.txt");
	tetrisAdapterVector.draw();
	//ADAPTER VECTOR TEST

	return 0;
}