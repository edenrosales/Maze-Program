//MADE BY EDEN ROSALES
//ID: 900796598
#pragma once
#include "Stack.h"
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std; 


class Maze {
public:
	int isAlive[5] = { 1,1,1,1,1 }; //this an array that tracks the status of the mice (1 means they are alive or not placed yet, 0 means dead)
	int catSurroundings[4];
	//XLOC and YLOC determine the coordinates that the maze is going to be printed at. Also is used for locations to print
	//mice and cats
	int XLOC=12;
	int YLOC=6; 
	void hideCursor(); //hides the cursor in the window 
	const int MAZEROWS = 16; //determines the amount of rows in the maze 
	const int MAZECOLS = 95; //determines the amount of columns in the maze 
	Stack mouse[5];//stack that saves the locatoins of the mice (the 5 of them) 
	//for the below array. it has three dimensions. the last two dimensions are the standard mazses for each individual mouse, 
	//the reason i made 5, is because it is one differnet board for each mouse, then a final one to control all the cats. The mice 
	//have different boards because i want them to act independently, because their move functions alter the map, which i want to 
	//only have an effect on the current mouse that is calling that move function 
	int board[6][16][95]; //array that saves the information about the mazes. 
	int xMouse[5], yMouse[5];//the x and y values of the mice (modifies with XLOC and YLOC for printing, but works with board[][][]
	void display();//displays board with the header and instructions (the active, moving map)
	Maze() { xMouse[0] = 1; yMouse[0] = 1;}//constructor for the maze. makes one mouse with the locaton (1,1) on the maze 
	void showMouse(int mouseNumber);//displays the mouse whos index is input through the function 
	void hideMouse(int mouseNumber);//hides the mouse whos index is input through the function
	void moveMouse(int mouseNumber);//moves the mouse whos index is input through the function
	void gotoxy(int, int); //goes to the (x,y) coordinate on the screen
	void loadMaze(string mazePathway1);//loads the maze into the board[][][] array 
	void setColor(int); //sets the color to the value passed into the function
	int finishGame = 0;//variable the determine if the mouse has touched the end of the maze 
	//Stack cat[10]; //unused 
	int xCat[10], yCat[10]; //the x and y vlues of the mive (each cat has its own index) (works in same was as mMouse yMouse)
	void showCat(int catNumber);//showMouse but for cats 
	void hideCat(int catNumber);//hideMouse but for cats 
	//the move function works differently than the move mouse function. 
	void moveCat(int catNumber);//moveMouse but for cats
	int catsEating(int catNumber);//method for when the cats eat mice 
	//void fillSpace(int catNumber);//unused 
	void startingScreen();//displays starting screen. Instructions 
	Stack placingCats(string mazePathway1); //occurs after startingScreen. allows user to manually input cats onto the maze, and set a custom path to place cats 
	void changeColor(int color); //changes the color to the int value input to the method 
	int catDefaultx = 1; //the default cat spawn locaton. can be modified in placingCats() method (x value)
	int catDefaulty = 1;//the default cat spawn locaton. can be modified in placingCats() method (y value)
	int catColor=15;//set cats color when they are displayed
	int miceColor=15;//set the mice color for when they are displayed
	int mapColor=15;//sets the maps color for when its displayed
	int colorMenu();//opens a menu for the user to select a color of choce, returns an int according to that value they chose
	void exitSequence();//method that allows user to exit program once escape is hit twice 
	void displayMap();//displays only the map, without the added instructions (for use with methods that display only the map) 
	void gameOver(int howManyLeft);//the game over sequence, just a text screen 
	bool mouseDeath = false;//determines if a mouse has been killed in this iteration. for use with the lives counter 
	void printMouseLives(int miceNum); //printing out the lives counter at the bottom right of the screen, updates when something of significance takes place 
	int mouseLivesScanner();//scans the isAlive array to determine how many mice are currently alive. Used to determine a game over. 
	string mazePathway="sosososososo dumb";
};