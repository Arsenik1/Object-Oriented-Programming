package HW.HW7;

import java.util.*;

public class driver2 {
	public static void main(String[] args)
	{
		char inputShape;
		int height = 0, width = 0;
		char temp;
		String area = "";
		String shapeType = "";
		char rotateDir = 'L';
		int rotateCount = 'R';
		char moveDir = 'L';
		int moveCount = 1;
		String Stemp = "";
		String[] SSTemp; 
		Random rand = new Random();
		Scanner sc = new Scanner(System.in);

		while(height < 4 || width < 4) 
		{
			int i = 0;
			System.out.print("PLEASE USE CAPS LOCK THROUGHOUT THE GAME.\n\nEnter size (syntax: heightXwidth): ");
			area = sc.nextLine();
			for(i = 0; i < area.length() && (area.charAt(i) > '9' || area.charAt(i) < '0'); i++);
			while(i < area.length() && area.charAt(i) <= '9' && area.charAt(i) >= '0')
			{
				height = (10 * height) + area.charAt(i) - '0';
				i++;
			}
			for(; i < area.length() && (area.charAt(i) > '9' || area.charAt(i) < '0'); i++);
			while(i < area.length() && area.charAt(i) <= '9' && area.charAt(i) >= '0')
			{
				width = (10 * width) + area.charAt(i) - '0';
				i++;
			}
			area = "";
			// System.out.print('\n' + height + " " + width + " " + i + '\n');
			if(height < 4 || width < 4)
			{
				height = 0;
				width = 0;
			}
		}
		Tetris game = new Tetris(height, width); //creating the game
		System.out.print("\033[2J" + "\033[0;0f");
		game.draw(1);
		System.out.print(" \033[s");	//printing for once because I save the cursor's coordinates in here.

		while(true)
		{
			System.out.print("\033[2J" + "\033[0;0f");
			game.draw(1);
			System.out.print(" \033[u");
			System.out.print("\nEnter shape: ");
			shapeType = sc.nextLine();
			inputShape = shapeType.charAt(0);
			if(inputShape == 'Q')
			{
				System.out.print("\033[2J" + "-----EXIT-----");
				sc.close();
				return ;
			}
			if(inputShape == 'R')
				while(Tetromino.returnShape(inputShape) == '*')
					inputShape = (char)(rand.nextInt(999999) % 100);
			if(Tetromino.returnShape(inputShape) == '*' && inputShape != 'R')	//input handling
			{
				System.out.print("\033[2J" + "\033[0;0f");
				System.out.print("\nInvalid input\n");
				try{Thread.sleep(300);}catch(InterruptedException e){}
				shapeType = "";
				continue;
			}
			else
			{
				Tetromino inputPiece = new Tetromino(Tetromino.returnShape(inputShape));	//creating the inputted piece
				// inputPiece.printPiece();
				// System.out.print('\n' + '\n' + '\n' + "\nafasdokaswndvjasndvjsaknvfjakdfvadfvodafgkdafglk\n" +"_height" + "_width" + '\n' + '\n');
				// sleep(2);
				
				// System.out.print("\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
				// sleep(2);
				System.out.print("\033[2J" + "\033[0;0f");
				while(true)
				{
					game.setPlaceBoard(game.getBoard());
					game.addMiddle(inputPiece, game.getPlaceBoard());
					game.draw(0);
					System.out.print("\n(Image is for representation purposes only)\n");
					game.clearTable();
					System.out.print('\n' + "Please enter the rotation direction and rotation count.\nSyntax: DIRECTION ROTATIONCOUNT\nExample: LEFT 2\n:");
					Stemp = sc.nextLine();
					SSTemp = Stemp.split(" ");
					rotateDir = SSTemp[0].charAt(0);
					Stemp = SSTemp[1];
					rotateCount = Integer.parseInt(Stemp);
					if((rotateDir == 'L' || rotateDir == 'R') && rotateCount <= 4 && rotateCount >= 0)
					{
						System.out.print("\033[2J" + "\033[0;0f");
						game.setPlaceBoard(game.getBoard());
						game.addMiddle(inputPiece, game.getPlaceBoard());
						game.draw(0);
						game.clearTable();
						System.out.print("\n(Image is for representation purposes only)\n");
						System.out.print('\n' + "Please enter how you want to move the piece.\nSyntax: MOVEDIRECTION MOVECOUNT\nExample: RIGHT 2\n:");
						SSTemp = sc.nextLine().split(" ");
						moveDir = SSTemp[0].charAt(0);
						moveCount = Integer.parseInt(Stemp);
						if((moveDir == 'L' || moveDir == 'R') && moveCount < game.getWidth() && moveCount >= 0 && moveCount < game.getWidth() / 2)
							break;
					}
					if(rotateDir == 'Q' || moveDir == 'Q')
					{
						System.out.print("\033[2J" + "-----EXIT-----\n");
						game.assemble();
						game.draw(1);
						sc.close();
						return ;
					}
					System.out.print("\033[2J" + "\033[0;0f");
					System.out.print('\n' + "You have entered a wrong input or you are out of boundaries. Keep in mind that rotation count cannot be more than 4. Try again.\n");
				}
				if(game.animate(inputPiece, rotateDir, rotateCount, moveDir, moveCount) == false)	//playing the game and getting the success
				{
					System.out.print("\033[2J" + "\033[0;0f" + "THE GAME HAS ENDED.\n");
					game.assemble();
					game.draw(1);
					sc.close();
					return ;
				}

			}
		}
	}
}
