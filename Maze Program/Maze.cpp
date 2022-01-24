//MADE BY EDEN ROSALES
//ID: 900796598
#include "Maze.h"
void Maze::hideCursor()//the method to hide the cursor. taken from other projects 
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void Maze::display()//displays the main screen of the program. displays the maze, with its header, and instructions for commands below 

{//below is the header of the maze, showing its title 
	string bubbles = R"(
			   /' _ ` _ `\ /'_` )(_  ,) /'__`\    /'_ `\ /'_` )/' _ ` _ `\ /'__`\
			   | ( ) ( ) |( (_| | /'/_ (  ___/   ( (_) |( (_| || ( ) ( ) |(  ___/
			   (_) (_) (_)`\__,_)(____)`\____)   `\__  |`\__,_)(_) (_) (_)`\____)
						             ( )_) |                         
   )";
	gotoxy(15, 0);
	cout << bubbles;//printing header
	changeColor(mapColor);//method changes the map color to the variable mapColor, so that it can be changed at will 
	for (int i = 0; i < MAZEROWS; i++) {//printing the maze by reading from the board array, which must be loaded before this method can be used by using loadMaze function
		for (int j = 0; j < MAZECOLS; j++) {
			if (board[5][i][j] == 1)//this is for printing the walls of the maze 
			{
				gotoxy(XLOC + j, YLOC + i);
				cout << char(219);
			}
			else if (board[5][i][j] == 0) {//this is for printing spaces for locations that objects can move to 
				gotoxy(XLOC + j, YLOC + i);
				cout << " ";
			}
			else if (board[5][i][j] == 2) {//this is going to be the code for the dead end cells, is not a movable space, but will not print as a wall 
				gotoxy(XLOC + j, YLOC + i);
				cout << " ";
			}
			else {}
		}
		cout << endl;
	}
	changeColor(15);//if a custom color is used to print the maze, this method returns it to its default value 
	//following cout statements print out the statements the display the commands that the user can use while the program is running
	gotoxy(15, 23);
	cout << "f1: Map Color Menu";
	gotoxy(40, 23);
	cout << "f2: Cat Color Menu";
	gotoxy(27, 25);
	cout << "f3: Mice Color Menu";
	gotoxy(53, 26);
	cout << "Enter: Pause";
	gotoxy(65, 23);
	cout << "Spc: Adds a Mouse";
	gotoxy(90, 23);
	cout << "C or c: adds a Cat";
	gotoxy(70, 25);
	cout << "Esc: exit the program";
}

void Maze::displayMap()//method that just displays the map, without the header and the user command instructions
{
	for (int i = 0; i < MAZEROWS; i++) {//the loops that print out the map on the screen from the board array, loadMaze function must be called before this method can be used 
		for (int j = 0; j < MAZECOLS; j++) {
			if (board[5][i][j] == 1)//this is for printing the walls of the maze 
			{
				gotoxy(XLOC + j, YLOC + i);
				cout << char(219);
			}
			else if (board[5][i][j] == 0) {//this is for printing locatoins in which objects can move to 
				gotoxy(XLOC + j, YLOC + i);
				cout << " ";
			}
			//this was meant as a way to be able to reprint the maze, without the cells that the mouse determines as unmovable to show up as walls, which would make the maze look like it was changing over time 
			else if (board[5][i][j] == 2) {//this is going to be the code for the dead end cells, (NOTE: was going to use this, but it went unused) 
				gotoxy(XLOC + j, YLOC + i);
				cout << " ";
			}
			else {}
		}
		cout << endl;
	}
	//changeColor(15);
	//gotoxy(15, 23);
	//cout << "f1: Map Color Menu";
	//gotoxy(40, 23);
	//cout << "f2: Cat Color Menu";
	//gotoxy(27, 25);
	//cout << "f3: Mice Color Menu";
	//gotoxy(65, 23);
	//cout << "Spc: Adds a Mouse";
	//gotoxy(90, 23);
	//cout << "C or c: adds a Cat";
	//gotoxy(70, 25);
	//cout << "Esc: exit the program";
}

void Maze::gameOver(int howManyLeft)//method for the game over screen. Since this method is called after the main loop in main, it must
//take into account the two situations. Winning, or losing. This is determined by the variable howManyLeft. Which is a variable that holds the 
//value given to it by mouseLivesScanner, which tracks the amount of mice that are alive. if there are 0 mice alive, we know that the user lost the game
//if there are more than 1 mice alive, that means that at least one of the mice reached the end of the maze without being eaten. 
//the correct screen will be displayed accordingly 
//will also play a sound according to a loss or a victory
{
	if (howManyLeft > 0) {//game over screen for winning, when there is more than one mouse alive 
		system("cls");//clears screen of the maze 
		//the ascii art for the gameover screen
		string gameover = R"(
			          ___   ___         ___         ___         ___   ___  
			         |     |   | |\ /| |           |   | |  /  |     |   | 
		                 | +-  |-+-| | + | |-+-        |   | | +   |-+-  |-+-  
 			         |   | |   | |   | |           |   | |/    |     |  \  
 			          ---               ---         ---         ---        
)";
		gotoxy(10, 8);
		cout << gameover;
		gotoxy(56, 14);
		setColor(10);//sets the color to green for the next line of text 
		cout << "You win";//text that allows user to see that they have won the game 
		setColor(15);//resets color to default
		PlaySound(TEXT("victorytheme"), NULL, SND_SYNC);//play the victory sound
	}
	else if (howManyLeft == 0) {//game over screen for losing, when there is no mice alive
		system("cls");//clears the screen of the maze 
		//ascii art for the gameover screen
		string gameover = R"(
			          ___   ___         ___         ___         ___   ___  
			         |     |   | |\ /| |           |   | |  /  |     |   | 
		                 | +-  |-+-| | + | |-+-        |   | | +   |-+-  |-+-  
 			         |   | |   | |   | |           |   | |/    |     |  \  
 			          ---               ---         ---         ---        
)";
		gotoxy(10, 8);
		cout << gameover;
		gotoxy(56, 14);
		setColor(12);//sets the color to red for the next line of text 
		cout << "You LOSE";//text that allows the user to see that they have lost the game 
		PlaySound(TEXT("crybabyloser"), NULL, SND_SYNC);//plays the game over tune 
		setColor(15);//resets color to default 
	}
}

void Maze::printMouseLives(int miceNum)//the lives counter for the maze game 
{
	//the function has this tracker, and increments it by 3 each time, so that each X (which represents a mice's life), is spaces out for 
	//aesthetic purposes. A green X shows that the mouse is alive, a red one shows that it is now dead 
	//the function takes in the miceNum, the varible for the amount of mice that are currently alive in the maze, so that the functoin
	//will only be tracking the lives of the mice that have already been created, will not display mice that have not been added yet to game.
	int counter=85; //for tracking the x locatoin that gotoxy moves to for printing the lives counter 

	for (int i = 0; i <= miceNum-1; i++) {//loops to display the current amount of mice that have been spawned in the game 
		if (isAlive[i] == 0) {//if the mouse is dead
			setColor(12);//sets color to red
			gotoxy(counter, 27);//goes to the location (counter,27) on the screen.
			cout <<"X\t";//prints the red 'X'
			setColor(15);//sets the color back to default 
			counter += 3;//increments the x coordinate 
		}
		else if (isAlive[i] == 1) {//if the mouse is alive 
			setColor(10);//sets the color to green
			gotoxy(counter, 27);//goes to the location (counter, 27) on the screen
			cout << "X\t";//prints the rex 'X'
			setColor(15);//sets the color back to default		
			counter += 3;//increments the x coordinate 
		}
	}
}

int Maze::mouseLivesScanner()//scans the isAlive array to determine how many mice are alive 
{
	int counter = 0;//counter variable is initialized to 0 
	for (int i = 0; i < 5; i++) {//loops through the isAlive array
		if (isAlive[i] == 1) {//if any given mouse is alive
			counter++;//increments the counter variable 
		}
	}
	return counter;//returns the amount of mice that are alive 
}

void Maze::showMouse(int mouseNumber)//displays the mouse on the screen 
{
	changeColor(miceColor);//allows for customized colors to be printed 
	gotoxy(xMouse[mouseNumber]+XLOC , yMouse[mouseNumber]+YLOC);//locatoin is adjusted with the XLOC and YLOC of the maze, so that it displays properly inside of it 
	cout << "*";//displays a * for the mouse 
	changeColor(15);//resets the color to its default value 
}

void Maze::hideMouse(int mouseNumber)//method to hide the mouse 
{
	gotoxy(xMouse[mouseNumber]+XLOC, yMouse[mouseNumber]+YLOC);//goes to the location of the mouse 
	cout << " ";//prints a space there to make it look like it is not there
}

void Maze::moveMouse(int mouseNumber)//the move mouse function
//the logic of the function is as follows: 
//the mouse will first check the right, up, left, and down directions (in that order) to see if it is availible to move into 
//if it is, the mouse will move into that location. However it will also check if this locatoin is a locatoin in which the mouse
//has previously moved to in the last movement. If all the paths are closed or been traveled to in the last movement, it will then backtrack to the previous
//location that it was at in the stack, and make the location that it was at (which had not been added to the stack yet), a location that cannot be traveled by this mouse again.
//after the movement, it will input the previous location that it was in, to the stack. Unless it is making sure that a coordinate is to not be moved to 
//also checks if the mouse is one unit away from the finish like (denoted by a 4 in the board array) and will move there if it is 
{
	//checks on the up, left, right, and down directions if the finish line is adjacent to the mouse, if so, it will move it there
	if (board[mouseNumber][yMouse[mouseNumber]][xMouse[mouseNumber] + 1] == 4) {
	finishGame = 1;
	}
	else if (board[mouseNumber][yMouse[mouseNumber]][xMouse[mouseNumber] - 1] == 4) {
	finishGame = 1;
	}
	else if (board[mouseNumber][yMouse[mouseNumber] + 1][xMouse[mouseNumber]] == 4) {
	finishGame = 1;
	}
	else if (board[mouseNumber][yMouse[mouseNumber] - 1][xMouse[mouseNumber]] == 4) {
	finishGame = 1;
	}
	//checks if the mouse is either next to an availible locatoin, will not move to a location that it has just been to previously 
	//checks the right side 
	else if (board[mouseNumber][yMouse[mouseNumber]][xMouse[mouseNumber] + 1] == 0 && ((mouse[mouseNumber].peek().x != xMouse[mouseNumber] + 1) || (mouse[mouseNumber].peek().y != yMouse[mouseNumber]))) {
		//if it passes, and the mouse is able to move, will add the current location to the stack before moving 
		Cursor x;//creates cursor to hold this locatoin
		x.x = xMouse[mouseNumber];//adds the x value 
		x.y = yMouse[mouseNumber];//ads the y value 
		mouse[mouseNumber].push(x);//pushes coodinates to the stack 
		//moves the mouse to the right 
		xMouse[mouseNumber]++;
	}
	//checks above the mouse 
	else if (board[mouseNumber][yMouse[mouseNumber] - 1][xMouse[mouseNumber]] == 0 && ((mouse[mouseNumber].peek().x != xMouse[mouseNumber]) || (mouse[mouseNumber].peek().y != yMouse[mouseNumber] - 1))) {
		//if it passes, and the mouse is able to move, will add the current location to the stack before moving 
		Cursor x;//creates cursor to hold this locatoin
		x.x = xMouse[mouseNumber];//adds the x value 
		x.y = yMouse[mouseNumber];//ads the y value 
		mouse[mouseNumber].push(x);//pushes coodinates to the stack 
		//moves the mouse up
		yMouse[mouseNumber]--;
	}
	//checks to the left of the mouse 
	else if (board[mouseNumber][yMouse[mouseNumber]][xMouse[mouseNumber] - 1] == 0 && ((mouse[mouseNumber].peek().x != xMouse[mouseNumber] - 1) || (mouse[mouseNumber].peek().y != yMouse[mouseNumber]))) {
		//if it passes, and the mouse is able to move, will add the current location to the stack before moving 
		Cursor x;//creates cursor to hold this locatoin
		x.x = xMouse[mouseNumber];//adds the x value
		x.y = yMouse[mouseNumber];//ads the y value 
		mouse[mouseNumber].push(x);//pushes coodinates to the stack 
		xMouse[mouseNumber]--; //moves the mouse to the left 
	}
	//checks below the current mouse location 
	else if (board[mouseNumber][yMouse[mouseNumber] + 1][xMouse[mouseNumber]] == 0 && ((mouse[mouseNumber].peek().x != xMouse[mouseNumber]) || (mouse[mouseNumber].peek().y != yMouse[mouseNumber] + 1))) {
		//if it passes, and the mouse is able to move, will add the current location to the stack before moving 
		Cursor x;//creates cursor to hold this locatoin
		x.x = xMouse[mouseNumber];//adds the x value
		x.y = yMouse[mouseNumber];//ads the y value 
		mouse[mouseNumber].push(x);//pushes coodinates to the stack .
		//moves the mouse down 
		yMouse[mouseNumber]++;
	}
	else {//if all these fail, that means that all sides are either a wall, or the mouse has been there as its previous location
		//will proceed to make the current locatoin, a location that cannot be reachec by this mouse, then it will move the mouse to its prevoius location
		board[mouseNumber][yMouse[mouseNumber]][xMouse[mouseNumber]] = 1;//will set the mouses' current location to a 1, so taht it cannot be moved to again
		Cursor next;//makes a new cusor object 
		next = mouse[mouseNumber].pop();//pops the previous locatoin of the mouse (before its current one) 
		//moes the mouse to the previous location 
		xMouse[mouseNumber] = next.x;
		yMouse[mouseNumber] = next.y;

	}
}

void Maze::gotoxy(int x , int y )//places the cursor at the (x,y) coordinate 
{
		COORD pos = { x, y };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
}

void Maze::loadMaze(string mazePathway1)//loads the maze into the board[][][] array
{
	char c; 
	for (int n = 0; n < 6; n++) { //we are going to read the file 6 times over
		ifstream infile(mazePathway1);//takes the file that is at this location and opens it 
		for (int i = 0; i <= MAZEROWS - 1; i++) {//the loop for the rows 
			for (int j = 0; j <= MAZECOLS - 1; j++) {//the loop for the columns 
				infile >> c;
				if (c == '1') {//reads ones and inputs the integer value into the array (the mouse will not be able to move here)
					board[n][i][j] = 1;
				}
				else if (c == '0') {//reads 0's and inputs the integer value in the array (the mouse can move here)
					board[n][i][j] = 0;
				}
				else if (c == '4')//reads 4's and intputs the integer value in the array (the mouse will not be able to move here, but when adjacent, finishes the game) 
					board[n][i][j] = 4;
				else//if it is none of these values, it will input a 2 integer value (mouse cannot move here)
					board[n][i][j] = 2;
			}
		}
		infile.close();//closes the file 
	}
}

void Maze::setColor(int color)//sets the color of the text that proceeds this method 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Maze::showCat(int catNumber)//shows the cat, works in the same way as the showMouse function
{
	changeColor(catColor);//sets color
	gotoxy(xCat[catNumber] + XLOC, yCat[catNumber] + YLOC);//goes to the location where the cat is meant to be 
	cout << "@";//prints the symbol for the cat 
	changeColor(15);//resets the color 
}

void Maze::hideCat(int catNumber)//hides the cat, works in the same way as th showMouse function
{
	gotoxy(xCat[catNumber] + XLOC, yCat[catNumber] + YLOC);//moves to the locatoin where the cat is meant to be 
	cout << " ";//"hides" the cat by printing a space there
}

void Maze::moveCat(int catNumber)//the movement function for the cat, works differnt from the mouse moving function
//unlike the mouse, the cat will move in a random direction (adjacent to the cat). I have made it so that the cat will not try to move into a random location
//that cannot be moved into, but it will instead move to a random VALID location.

//this was done becuase i did not want the cats the move in the same way that the mice did, or else, if the cats were ever spawned at the same location right after each other
//the cat would never be able to catch up (or have a 100% chance to catch up with the mouse, if the mouse ran into a corner)
//, and it would look weird as a function...i felt that doing this made the program more balanced 
{
	int counter = 0; //this is the counter that determines if the cat has moved yet or not. 0 if the cat has not yet moved, 1 if that cat has moved 
	//		if (board[5][yCat[catNumber] + 1][xCat[catNumber]] == 0) { //to go down
	//			yCat[catNumber]++;
	//			//counter++;
	//		}
	int random;//variable for a random number
	while (counter<=0) {//while the cat has not moved yet
		random = (rand() % 4) + 1;//generates a random number 
		if ((random == 1) && (board[5][yCat[catNumber]][xCat[catNumber] + 1] == 0)) {//if the random locatoin (adjacent to cat) given is open or it 
			if (board[5][yCat[catNumber]][xCat[catNumber] + 1] == 0) { //to go to the right 
				xCat[catNumber]++;//move the cat to the random locaton
				counter++;//increment coutner, breaking out of the look
			}
		}
		else if ((random == 2) && (board[5][yCat[catNumber]][xCat[catNumber] - 1] == 0)) {//if the random locatoin (adjacent to cat) given is open or it 
			if (board[5][yCat[catNumber]][xCat[catNumber] - 1] == 0) { //to go to the left
				xCat[catNumber]--;//move the cat to the random locaton
				counter++;//increment coutner, breaking out of the look
			}
		}
		else if ((random == 3) && (board[5][yCat[catNumber] - 1][xCat[catNumber]] == 0)) {//if the random locatoin (adjacent to cat) given is open or it 
			if (board[5][yCat[catNumber] - 1][xCat[catNumber]] == 0) { //to go up
				yCat[catNumber]--;//move the cat to the random locaton
				counter++;//increment coutner, breaking out of the look
			}
		}
		else if ((random == 4) && (board[5][yCat[catNumber] + 1][xCat[catNumber]] == 0)) {//if the random locatoin (adjacent to cat) given is open or it 
			if (board[5][yCat[catNumber] + 1][xCat[catNumber]] == 0) { //to go down
				yCat[catNumber]++;//move the cat to the random locaton
				counter++;//increment coutner, breaking out of the look
			}
		}
	}
}

int Maze::catsEating(int catNumber)//the eating function for the cats 
{ 
	for (int i = 0; i <5; i++) {//goes through all the 5 mice that might be alive or not 
		if ((xCat[catNumber] == xMouse[i]) && (yCat[catNumber] == yMouse[i])) {//checks the current cat, and sees if any of the 5 mice (that might be alive or not) are at the same coodinate as the cat 
			if (isAlive[i] == 1) {//if the mouse is at the location of the cat, and if the mouse is alive
				isAlive[i] = 0;//make the mouse die, by setting its variable to 0 in the isAlive array
				hideMouse(i);//hide the mouse 
				showCat(catNumber);//show the cat ontop of the mouse, after the hideMouse function is called 
				mouseDeath = !mouseDeath;//flip the mouseDeath variable to its opposite (to true) 
				return -1;//return a -1, which is a way in which the programm is able to readjust the Sleep function to account for the mouse's death 
			}
		}
	}
 	return 0; //return 0 if nothing is killed, so that the sleep function is not readjusted 
}

//void Maze::fillSpace(int catNumber)//dead function
//{
//	catSurroundings[0] = board[catNumber][yCat[catNumber]][xCat[catNumber]+1]; 
//	catSurroundings[1] = board[catNumber][yCat[catNumber]][xCat[catNumber]-1];
//	catSurroundings[2] = board[catNumber][yCat[catNumber]+1][xCat[catNumber]];
//	catSurroundings[3] = board[catNumber][yCat[catNumber] - 1][xCat[catNumber]];
//}

void Maze::startingScreen()//the starting screen method, displays the instructions and lets the user switch between both using the 
//spacebar, and continue to the next screen by pressing enter 
{
	cout << R"( 




		 	            Press spacebar to change to the next page 
		   +--------------+--------+--------------------------------------------------+
		   | Keystroke    | ASCII  |                   Function                       |
		   |              |        |                                                  |
		   +--------------------------------------------------------------------------+
		   |  C or c      |   67   |  When pressed adds a Cat to the program          |
		   |              |        |                                                  |
		   |  Space       |   32   |  When pressed adds a Mouse to the program        |
		   |              |        |                                                  |
		   |  Enter       |   13   |  Pauses the program when pressed                 |
		   |              |        |                                                  |
		   |  Escape      |   27   |  Exits the program early                         |
		   |              |        |                                                  |
		   | Function keys|   0    |                                                  |
	   	   |    f2        |   60   |  Color menu for the Cats                         |
		   |    f3        |   61   |  Color menu for the Mice                         |
		   |    f1        |   59   |  Color menu for the map                 Page 1/2 |
		   +--------------+--------+----^---------------------------------------------+

  )";
	bool pageSwap = false;	//sets variable for the switch of the page 
	while (1) {
		if (_kbhit()) {	//if the keyboard was pressed 
			char c = _getch();//initializes the variable and sets it to the users input 
			if (c == 32) {	//if spacebar was pressed 
				pageSwap = !pageSwap;//switch the variable for switching between page one and two 
				if (!pageSwap) {//if variable has been switched to false, switch the page to page one 
					system("cls");
					//printPageOne();
					cout << R"( 




		 	            Press spacebar to change to the next page 
		   +--------------+--------+--------------------------------------------------+
		   | Keystroke    | ASCII  |                   Function                       |
		   |              |        |                                                  |
		   +--------------------------------------------------------------------------+
		   |  C or c      |   67   |  When pressed adds a Cat to the program          |
		   |              |        |                                                  |
		   |  Space       |   32   |  When pressed adds a Mouse to the program        |
		   |              |        |                                                  |
		   |  Enter       |   13   |  Pauses the program when pressed                 |
		   |              |        |                                                  |
		   |  Escape      |   27   |  Exits the program early                         |
		   |              |        |                                                  |
		   | Function keys|   0    |                                                  |
	   	   |    f2        |   60   |  Color menu for the Cats                         |
		   |    f3        |   61   |  Color menu for the Mice                         |
		   |    f1        |   59   |  Color menu for the map                 Page 1/2 |
		   +--------------+--------+----^---------------------------------------------+

  )";
				}
				if (pageSwap) {//if varaible has been switched to true, switch the page to page two 
					system("cls");
					//printPageTwo();
					cout << R"( 





	        +--------------------------------------------------------------------------+
		|                              Other notes:                                |
		|          Press space to return to Page 1. Or enter to proceed            |
		+--------------------------------------------------------------------------+
		|                                                                          |
		|      The next page will ask you if you would like to manually add        |
		|      Cats to the map at the start of the game. This is the only          |
		|      opportunity to manually add cats during the game.                   |
		|                                                                          |
		|      Inputting an invalid coordinate to place the Cats will display      |
		|      an "ERROR" message, and this Cat will not be placed on the          |
		|      screen. We can also input a default location that cats will be      |
		|      loaded at when 'c' is pressed (default x=1, y=1). Additionally      |
		|      The max amount of Mice is 5, and the max amount of Cats is 10!      |
		|                                                                Page 2/2  |
		+--------------------------------------------------------------------------+


)";
				}
			}
			else if (c == 13) {//if enter was pressed exit the loop
				system("cls");
				break;
			}
		}
	}
	gotoxy(5, 12);//goes to roughly the middle of the screen 
	cout << "Add a custom pathway for the maze? Press enter to skip this, press spacebar to enter a custom pathway" << endl;
	while (1) {//this loop looks for either a spacebar to input a custom pathway, if enter is pressed, will exit the method 
		if (_kbhit()) {	//if the keyboard was pressed 
			char chare = _getch();//initializes the variable and sets it to the users input 
			if (chare == 32) {	//if spacebar was pressed 
				gotoxy(40, 13);
				cout << "Enter the pathway:";//prompts the user for input 
				gotoxy(20, 14);
				getline(cin, mazePathway);//user input for the pathway to the file containing the maze 
				system("cls");
				break;
			}
			else if (chare == 13) { //if enter was pressed

				system("cls");//clears the window to prepare for the next method 
				break;
			}
		}
	}
}
//
//	system("cls"); //clears the screen of the instruction menus 
//	gotoxy(30, 12);//goes to roughly the middle of the screen 
//	cout << "Add a custom pathway for the maze? Press enter to skip this, press spacebar to enter a custom pathway" << endl;
//	char userinput;
//	cin >> userinput;
//	if (userinput == 10) {
//	}
//	else if (userinput == 32) {
//		cout << "Enter the custom pathway for the maze";
//	}
//}

Stack Maze::placingCats(string mazePathway1)//method for allowing the user to input custom cats into the maze before the game starts 
{
	//variables for tracking where the text is going to be printed 
	int gotoxtracker = 0;
	int gotoytracker = 20;
	//variable for user input on how many cats they want 
	int howManyCats;
	Stack initialCats;//makes a stack of the cats taht are 
	gotoxy(30, 12);//goes to roughly the middle of the screen 
	cout << "Would you like to add custom cats? (Type 'yes' or 'no')"<<endl;
	gotoxy(59, 13);//also roughly the middle, adjusted for text length
	string userInput;//variable for user input 
	cin >> userInput;//gets user input 
	//if they type in "no", the program will continue without this method, if "yes" they will enter the next screen. if neither, the program will exit 
	if (userInput == "no") {//exits the method 
		system("cls");
		return initialCats;
	}
	else if (userInput == "yes") {//continues the method 
		system("cls");//clears screen 
		gotoxy(30, 12);
		cout << "how many cats would you like to add? (no more than 10)"<<endl;//prompts user to input the amount of cats they would like to add
		gotoxy(55, 13);
		cin >> howManyCats;//gets uset input 
		if (howManyCats > 10 || howManyCats < 1)//if the user input is not 1-10. If not, the program will exit 
		{
			cout << "invalid intput, restart program";
			exit(0);
		}
		system("cls");
	}
	else {//if the user does not type in "yes" or "no" the program will exit
		cout << "this was an invalid input, restart program.";
		exit(0);
	}			
	//the string variables holding the numbers that will appear for the coordinates, aiding the user with adding cats, and also the arrows for the numbers 
	string topArrows = R"(|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |)";
	string topNumbers =R"(0    5    10   15   20   25   30   35   40   45   50   55   60   65   70   75   80   85   90   95)";
	Maze w;//new maze variable 
	w.YLOC = 2;//sets the location of this maze to print at y=2 
	//w.hideCursor();
	w.loadMaze(mazePathway1);//loads maze 
	w.displayMap();//prints just the maze part of the maze 
	w.YLOC = 6;//resets the ylocatoin back to 6 
	//this section prints out the top numbers for the coodinates and also the arrows for the top numbers 
	gotoxy(12, 1);
	cout << topArrows;
	gotoxy(12, 0);
	cout << topNumbers;
	//prints out the arrows for the left side arrows for the coordinates/numbers
	gotoxy(11, 2);
	cout << "_";
	gotoxy(11, 7);
	cout << "_";
	gotoxy(11, 12);
	cout << "_";
	gotoxy(11, 17);
	cout << "_";
	//prints out the numbers for the left side coordintes/numbers
	gotoxy(10, 2);
	cout << "0";
	gotoxy(10, 7);
	cout << "5";
	gotoxy(9, 12);
	cout << "10";
	gotoxy(9, 17);
	cout << "15";
	gotoxy(30, 19);
	//prompts user to input the x and y coodinates of the cats taht they want to add
	cout << "Input the x,y coordinates of the cats that you want to add." << endl;
	//will loop through as many times as the user input how many cats they wanted (so if they input 2, this will iterate twice)
	for (int i = 0; i <= howManyCats - 1; i++) {
		gotoxy(gotoxtracker, gotoytracker);
		cout << "Cat " << i + 1 << ":" << endl;//text along with formatting 
		int xvalue;//variable for the user input x value for custom cat
		int yvalue;//varaible for user input y value for custom cat 
		gotoxy(gotoxtracker, gotoytracker +1);//prints text under the previous line 
		cout << "X Value: ";//prompts user
		cin >> xvalue;//user input 

		gotoxy(gotoxtracker, gotoytracker +2);//prints text right uner the prevoius line 
		cout << "Y Value: ";//text prompt for user

		cin >> yvalue;//user input 
		if (w.board[4][yvalue][xvalue] == 0) {//checks if the user input is a valid locatoin that a can can be placed into 
			gotoxtracker += 15;//incremens the x value for the gotoxy function, so that next lines can be printed adjacently, in the horizonal directoin
			//makes a new cursor variable, adds the user input and then pushes it to a stack, that will be used later to initialize the cats in the maze 
			Cursor newCursor;
			newCursor.x = xvalue;
			newCursor.y = yvalue;
			initialCats.push(newCursor);
		}
		else {//otherwise, if the user input is not a valid location  that a cat can be pushed into
			//prints text that displays that the information was invalid 
			gotoxy(gotoxtracker, gotoytracker + 3);
			changeColor(12);
			cout << "ERROR!";
			changeColor(15);
			//still increments the x value for the gotoxy function so that the next input prompt can be formatted properly 
			gotoxtracker += 15;
		}
		/*gotoxtracker += 15;
		Cursor newCursor;
		newCursor.x = xvalue;
		newCursor.y = yvalue;
		initialCats.push(newCursor);*/
		//this only gets called when we are calling for the addition of more than 8 cats (i think)
		if (gotoxtracker > 105) {//once the prompts have reached the end of the line in the window, it will reformat so the rest of the prompts look aesthetically pleasing 
			gotoxtracker =0;
			gotoytracker = 24;
		}


	}
	system("cls");//after the input of the custom cats, clears the screen 
	//sets the map to be displayed at y=2 again
	w.YLOC = 2;
	//displays jsut the maze..also all the coodinates ahd the arrows like it was like in the previous window 
	w.displayMap();
	gotoxy(12, 1);
	cout << topArrows;
	gotoxy(12, 0);
	cout << topNumbers;
	gotoxy(11, 2);
	cout << "_";
	gotoxy(11, 7);
	cout << "_";
	gotoxy(11, 12);
	cout << "_";
	gotoxy(11, 17);
	cout << "_";
	//displaying the coodinates and arrows like it was in the previous window 
	gotoxy(10, 2);
	cout << "0";
	gotoxy(10, 7);
	cout << "5";
	gotoxy(9, 12);
	cout << "10";
	gotoxy(9, 17);
	cout << "15";
	gotoxy(15, 19);
	//new text, prompting the user to input custom x and y values to set a spawn locatoin for the cats that can be added during the program
	cout << "Input the x,y coordinatates of the location that new Cats will be placed in (Default: 1,1)" << endl;
	gotoxy(55, 21);
	cout << "X Value: ";//prompt for x value 
	cin >> catDefaultx;//user input 
	gotoxy(55, 22);
	cout << "Y Value: ";//prompst for y value 
	cin >> catDefaulty;//user input 
	while (w.board[5][catDefaulty][catDefaultx] != 0) {//if the user does not input a good value, will clear screen, and redisplay the entire screen with error text 
		//until the user inputs a valid coordinate for the newspawn point of the cats 
		//not going to comment all the lines, because it the exact same as the code above 
		//clears screen first 
		system("cls");
		//displays jsut the maze..also all the coodinates ahd the arrows like it was like in the previous window 
		w.displayMap();
		gotoxy(12, 1);
		cout << topArrows;
		gotoxy(12, 0);
		cout << topNumbers;
		gotoxy(11, 2);
		cout << "_";
		gotoxy(11, 7);
		cout << "_";
		gotoxy(11, 12);
		cout << "_";
		gotoxy(11, 17);
		cout << "_";
		w.displayMap();
		gotoxy(42, 20);
		changeColor(12);//changes the color to red 
		cout << "ERROR, input a valid coordinate";//prints out error message 
		changeColor(15);//resest color back to white 
		//displaying the coodinates and arrows like it was in the previous window 
		gotoxy(10, 2);
		cout << "0";
		gotoxy(10, 7);
		cout << "5";
		gotoxy(9, 12);
		cout << "10";
		gotoxy(9, 17);
		cout << "15";
		gotoxy(15, 19);
		cout << "Input the x,y coordinatates of the location that new Cats will be placed in (Default: 1,1)" << endl;
		gotoxy(55, 21);
		cout << "X Value: ";
		cin >> catDefaultx;//user input 
		gotoxy(55, 22);
		cout << "Y Value: ";
		cin >> catDefaulty;//user input 
	}

	system("cls");//at the end of the functoin, either if the user inputs a correct value for the custom spawnpoint for the cats the first time, or after an amount 
	//of tries, will exit the program, returning the stack holding the coordinates of the custom cats that are going to be added to the maze 
	return initialCats;


	/*while (1) {
		if (_kbhit()) {
			char input = _getch();
			if (input == 'w') {
				system("cls");
				break;
			}
		}
	}*/

}

void Maze::changeColor(int color)// this is another setColor function, i dont know why I have two of them, but im not deleting this one because it might be used in another locatoin 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
}

int Maze::colorMenu()//is the menu that is going to prompt users to unput a number cooresponding to a color 
//will then return the value that they choose, and the cooresponding color variables will be changed, so that these differnet 
//aspects of the program can have their color changed 
{
	while (1) {
		int random = 0;
		random = (rand() % 10) + 1;
		char ch = NULL;
		system("cls");
		//shows "color menu!" with randomizing colors 
		gotoxy(45, 5);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), random);
		cout << "Color menu!!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 1 
		gotoxy(45, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << "1. This one?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 2
		gotoxy(45, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "2. This one!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 3
		gotoxy(45, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		cout << "3. This one?!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 4
		gotoxy(45, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "4. THIS ONE?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 5
		gotoxy(45, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		cout << "5. this one?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 6
		gotoxy(45, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "6. thisone?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 7
		gotoxy(45, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "7. ThiS oNe?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 8
		gotoxy(45, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		cout << "8. eno siht?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 9
		gotoxy(45, 14);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << "9. th1s on3?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 10, which is the default option
		gotoxy(45, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Enter. Default?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (_kbhit()) {
			ch = _getch();
			if (ch == 49) {//when number 1 is pressed, cooresponding with option 1, will return 1, which can be stored in a variable 
				system("cls");
				return 1;
				break;
			}
			else if (ch == 50) { //when number 2 is pressed, cooresponding with option 2, will return 2, which caan be stored in a variable 
				system("cls");
				return 2;
				break;
			}
			else if (ch == 51) {//when number 3 is pressed, cooresponding with option 3, will return 3, which can be stored in a variable
				system("cls");
				return 3;
				break;
			}
			else if (ch == 52) {//when number 4 is pressed, cooresponding with option 4, will return 4, which can be stored in a variable
				system("cls");
				return 4;
				break;
			}
			else if (ch == 53) {//when number 5 is pressed, cooresponding with option 5, will return 5, which can be stored in a variable
				system("cls");
				return 5;
				break;
			}
			else if (ch == 54) {//when number 6 is pressed, cooresponding with option 6, will return 6, which can be stored in a variable
				system("cls");
				return 6;
				break;
			}
			else if (ch == 55) {//when number 7 is pressed, cooresponding with option 7, will return 7, which can be stored in a variable
				system("cls");
				return 7;
				break;
			}
			else if (ch == 56) {//when number 8 is pressed, cooresponding with option 8, will return 8, which can be stored in a variable
				system("cls");
				return 8;
				break;
			}
			else if (ch == 57) {//when number 9 is pressed, cooresponding with option 9, will return 9, which can be stored in a variable
				system("cls");
				return 9;
				break;
			}
			else if (ch == 13) {//when enter is pressed, cooresponding with the enter option, will return 15 as its value (default color), which can be stored in a variable 
				system("cls");
				return 15;
				break;
			}
		}

	}

}

void Maze::exitSequence()//this is the exit sequence of the program
//when the user presses escape they are prompted to press escape again to exit, or enter to goo back 
{
	system("cls");
	gotoxy(25,13);		//setting location to print message (bottom right of screen)
	cout << "Press esc key again to end the program, any other buttom to resume";//instructions printed after escape is pressed
	char exitProgram = NULL; //variable for user input 
	exitProgram = _getch();	//grabbing user input
	if (exitProgram == 27) {	//when escape is pressed here, will exit the program
		exit(0);
	}
	system("cls");
}


