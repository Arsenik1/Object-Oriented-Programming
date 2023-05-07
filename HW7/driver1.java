package HW.HW7;


public class driver1 {
	public static void main(String[] args)
	{
		System.out.println("Welcome to Tetris game Test Driver.\n");
		System.out.println("Testing the Tetris game class.\n");
		Tetromino piece = new Tetromino('Z');
		Tetromino piece1 = new Tetromino('S');
		Tetromino piece2 = new Tetromino('L');
		Tetromino piece3 = new Tetromino('J');
		Tetromino piece4 = new Tetromino('O');
		Tetromino piece5 = new Tetromino('T');
		Tetromino piece6 = new Tetromino('I');
		piece.printPiece();
		System.out.println();
		piece1.printPiece();
		System.out.println();
		piece2.printPiece();
		System.out.println();
		piece3.printPiece();
		System.out.println();
		piece4.printPiece();
		System.out.println();
		piece5.printPiece();
		System.out.println();
		piece6.printPiece();
		System.out.println();
	}
}
