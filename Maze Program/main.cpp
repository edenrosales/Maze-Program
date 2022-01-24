//MADE BY EDEN ROSALES
//ID: 900796598
#include "Stack.h"
#include "Maze.h"
#include <conio.h>
#include <mmsystem.h>
using namespace std;

int main() {
	string loadmap;
	int howManyLeft=1; //creates and initializes the variable to 1. In the main loop of program, determines how many mice are currently alive. if 0, program ends
	bool pause = false;//variable for the pause functionality of the program
	Stack initialCats;//Stack variable for the custom cats that can get added to program
	srand(time(0));//random number seed 
	int modifier = 0;//modifier that corrects the Sleep() function for how many objects are being displayed on the screen
	int miceNum = 1;//the initial mice number
	int catNum = 0;//the initial cat number (before custom cats)
	int firstCat = 0;//variable to track if the first cat has been added yet (ignores custom cats) 
	Maze m;
	m.startingScreen();//the instructions screen plays first 
	loadmap = m.mazePathway;
	{
		initialCats = m.placingCats(loadmap);//the placing cats function is called, which then returns the stack of the custom cats to this varaible 
		while (initialCats.isEmpty() == false) {//pops the custom cat coordinates out and places the custom cats on the maze, until they are all placed
			catNum++;//increases the catNum variable, because a new cat is being created 
			Cursor newCat = initialCats.pop();//places the pop cat coordinates into this Cursor variable ,which stores the coordintaes 
			m.xCat[catNum - 1] = newCat.x;//sets this new cat's x coordinate
			m.yCat[catNum - 1] = newCat.y;//sets this new cat's y coordinate 
			m.showCat(catNum - 1);//displays the cat on the screen
		}
	}
	m.hideCursor();//hides the cursor for the program
	m.loadMaze(loadmap);//loads the maze 
	m.display();//prints the maze (with the instruction text and header text)
	m.printMouseLives(miceNum);
	//m.showMouse(1);//toggled sometimes, for some reason running this here causes a visual bug. never figured out why exactly 
	while (m.finishGame == 0 && howManyLeft!=0) {//the main loop of the functoin runs until either a mouse hits the end of the maze. or all the mice are dead 
		howManyLeft = m.mouseLivesScanner();//tracks how many mice are alive, counted as alive if they are not added yet (because its like a life system, where the mice are given 5 lives to complete the maze)
		if (_kbhit()) {//if user hits keyboard 
			char c = _getch();//gets user input 
			if (c == 'c' || c == 'C') {//if user input is 'c' or 'C'
				if (catNum < 10) {//if the cat num is less than 10 (the max amount of cats)
					catNum++;//another cat will be added by incrementing the catNum varaible 
					m.xCat[catNum - 1] = m.catDefaultx;//the new cats x value will be input using the cutom spawnpoint for cats (or default one)
					m.yCat[catNum - 1] = m.catDefaulty;;//the new cats y value will be input using the cutom spawnpoint for cats (or default one)
					m.showCat(catNum - 1);//will show this cat on the map 
					/*firstCat++;*/
				}
			}
			else if (c == 32) {//if the spacebar is pressed 
				if (miceNum < 5) {//if less than 5 mice have been added/have lived  (the max amount of mice)
					miceNum++;//another mouse will be addedby incrementing 
					//sets mouse at the beginning of the maze (no customization allowed becaus they need to start at the beginning to get to the end 
					m.xMouse[miceNum - 1] = 1;//sets mouse at x=1 
					m.yMouse[miceNum - 1] = 1;//sets mout as y=1 
					m.showMouse(miceNum - 1);//displays the mouse 
					Cursor newMouse;//creates a new Cursor variable to store the current location of the mouse 
					newMouse.x = 1;//the x value of the current locatoin (1) 
					newMouse.y = 1;//the y value of the current location (1)
					m.mouse[miceNum - 1].push(newMouse);//pushes these coordinates to the stack
					m.printMouseLives(miceNum);//prints the lives counter (this is called here to update the counter, showing a new mouse has been added) 
				}
			}
			else if (c == 0) {//for the functoin keys 
				char next = _getch();//gets user input again for funciotn keys 
				if (next == 59) {//if f1 was pressed, opens color menu for the map
					m.mapColor = m.colorMenu();//opens up the color menu using the method and sets the mapColor variable according to the value returned 
					m.display();//redisplays the screen 
					m.printMouseLives(miceNum);//redisplays the mouse life counter 
				}
				if (next == 60) {//f2, opens color menu for the cats 
					m.catColor = m.colorMenu();//opens up the color menu using the method and sets the catColor variable according to the value returned 
					m.display();//redisplays the screen 
					m.printMouseLives(miceNum);//redisplays the mouse life counter 
				}
				if (next == 61) {//f3 opens color menu for the mice 
					m.miceColor = m.colorMenu();//opens up the color menu using the method and sets the miceColor variable according to the value returned 
					m.display();//redisplays the screen 
					m.printMouseLives(miceNum);//redisplays the mouse life counter 
				}
			}
			else if (c == 27) { //when user presses escape key, they will be instructed to either press escape again to exit program, or press any other key to continue 
				m.exitSequence();//calls function which asks user to press escpae again to exit 
				m.display();//redisplays the screen
				m.printMouseLives(miceNum);//redisplays the mouse life counter 
			}
			else if (c == 13) {//if enter is pressed, pauses the program by entereing a loop in which only the controls will work, with the logic for the movement of the mice and cats omitted 
				pause = !pause;//toggles the pause variable for the following loop 
				while (pause) {//while pause menu variable is turned so that pause is true 
					//all this logic is the EXACT same as above, for all the keyboard input commands, so i will not recomment all of this, it would be redundant. (except for the enter key, which controls pause, unapuse, because it is different here)
					if (_kbhit()) {
						char chare = _getch();
						if (chare == 'c' || chare == 'C') {
							if (catNum < 10) {
								catNum++;
								m.xCat[catNum - 1] = m.catDefaultx;
								m.yCat[catNum - 1] = m.catDefaulty;
								m.showCat(catNum - 1);
								/*firstCat++;*/
							}
						}
						else if (chare == 32) {
							if (miceNum < 5) {
								miceNum++;
								m.xMouse[miceNum - 1] = 1;
								m.yMouse[miceNum - 1] = 1;
								m.showMouse(miceNum - 1);
								Cursor newMouse;
								newMouse.x = 1;
								newMouse.y = 1;
								m.mouse[miceNum - 1].push(newMouse);
								m.printMouseLives(miceNum);
							}
						}
						else if (chare == 0) {
							char next = _getch();
							if (next == 59) {
								m.mapColor = m.colorMenu();
								m.display();
								m.printMouseLives(miceNum);
								for (int i = 0; i < catNum; i++) {
									m.showCat(i);
								}
								for (int i = 0; i < miceNum; i++) {
									m.showMouse(i);
								}
							}
							if (next == 60) {
								m.catColor = m.colorMenu();
								m.display();
								m.printMouseLives(miceNum);
								for (int i = 0; i < catNum; i++) {
									m.showCat(i);
								}
								for (int i = 0; i < miceNum; i++) {
									m.showMouse(i);
								}
							}
							if (next == 61) {
								m.miceColor = m.colorMenu();
								m.display();
								m.printMouseLives(miceNum);
								for (int i = 0; i < miceNum; i++) {
									m.showMouse(i);
								}
								for (int i = 0; i < catNum; i++) {
									m.showCat(i);
								}
							}
						}
						else if (chare == 27) { //when user presses escape key, they will be instructed to either press escape again to exit program, or press any other key to continue 
							m.exitSequence();
							m.display();
							m.printMouseLives(miceNum);
						}
						else if (chare == 13) {//pressing enter again will change the pause variable. when done here will unpause the program
							pause = !pause;
						}
						else {}
					}

				}
			}
			else if (c == 'i') {}//does nothing, added for debugging 
		}
			/*if (firstCat == 1) {
				m.showCat(1);
				firstCat++;
			}*/
			for (int i = 0; i < catNum; i++) {//this is the logic for moving each of the cats. plays sound on mouse death
				m.hideCat(i);//first hides the cat, to allowfor it to move 
				m.moveCat(i);//completes the logic for moving the cat
				m.showCat(i);//displays the cat after it has moved
				modifier = modifier + m.catsEating(i);//preforms the function to check if the cat can eat any mice, returns a -1 if it does. this is to modify the sleep function so that each loop of this function will completely iterate at the same speed every time 
				if (m.mouseDeath) {//the cats eating function will also toggle this boolean variable on, if a mouse has been killed in the catsEating function, this is used to update the mouse lives counter on the bottom right of the screen 
					m.printMouseLives(miceNum);//updates the mouse lives counter, to show that a mouse has died in this iteration of the loop
					PlaySound(TEXT("pacman_death"), NULL, SND_SYNC);//plays a death sound when a mouse is killed, and after the death counter has been updated 
					m.mouseDeath = !m.mouseDeath;//retoggles so that this does not become an infinite loop
				}
				Sleep(150 / (miceNum + catNum + modifier));//a contant is divided by the amount sum of the (cats created + mice created - amount of mice killed) to get (the amount of objects on the screen) this loop will sleep for 5 seconds before continuing 
			}
			if (firstCat <= 3) {//is used to get rid of visual glitches when initially printing all the mice and cats on the screen. only runs three times. someitmes adding cats manually would break the screen slightly, only causing a visual glitch, this fixes it 
				m.display();//redisplays screen
				m.printMouseLives(miceNum);//redisplays the mouse lives counter 
				firstCat++;
			}
			for (int i = 0; i < miceNum; i++) {//this is the logic for moving the mice. plays sound on mouse death
				if (m.isAlive[i] == 1) {//if a mouse if found to be alive (its index in the isAlive array is =1) 
					m.hideMouse(i);//first hides the mouse 
					m.moveMouse(i);//moves the mouse
					m.showMouse(i);//prints the mouse on the screen
					//will iterate per how many cats are on the maze, this is because the catsEating function is based off of the amount of cats alive (its parameter needs to loop through that many cats) so making this separate loop is necessary)
					for (int j = 0; j < catNum; j++) {//if the mouse moves into a cat, the catsEating method must be played to make sure that the mouse is eaten during this turn. ensures that it visually checks out, and also makes sure that the mice are eaten if moved into same space as a cat
						modifier = modifier + m.catsEating(j);//calls the catEating function for each cat that is in the maze 
						if (m.mouseDeath) {//the cats eating function will also toggle this boolean variable on, if a mouse has been killed in the catsEating function, this is used to update the mouse lives counter on the bottom right of the screen 
							m.printMouseLives(miceNum);//updates the mouse lives counter, to show that a mouse has died in this iteration of the loop
							PlaySound(TEXT("pacman_death"), NULL, SND_SYNC);//plays a death sound when a mouse is killed, and after the death counter has been updated 
							m.mouseDeath = !m.mouseDeath;//retoggles so that this does not become an infinite loop
						}
					}
					//NOTE: since this loop  will sleep for an amount of ticks, and the previous sleep function with the logic for the cat will also sleep for the same duration, the sum of the constsants between the two sleep functions will stay constant no matter
					//how many objects are on the screen. for example if i set sleep to be 20 ticks for both sleep functions. the first loop would iterate in 20 seconds, and the second one would too, for a total runtime between these two functions of 40 ticks.
					//this is done to make the movement of all the objects on the screen look fluid and aethetically pleasing 
					Sleep(150 / (catNum + miceNum + modifier));//a contant is divided by the amount sum of the (cats created + mice created - amount of mice killed) to get (the amount of objects on the screen) this loop will sleep for 5 seconds before continuing 

				}
				else if (m.isAlive[i] == 0) {//if the mouse if dead, it will do nothing because it is dead 

				}
			}
	}
	m.gameOver(howManyLeft);//display the  game over screen, the value determining how many mice are alive will be sent as a parameter, to let the function know what the outcome of the game was (win or loss)
};

	/*for (int i = 0; i <= 40; i++) {
		m.moveMouse();
		m.showMouse();
	}
	m.gotoxy(100, 100);

	cout << m.xMouse<<endl;
	cout << m.yMouse<<endl;
	Cursor jenna;
	jenna = m.mouse.peek();
	cout << jenna.x << endl;
	cout << jenna.y<<endl;
	cout << m.board[18][19] << endl;*/
