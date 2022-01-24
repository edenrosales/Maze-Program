//MADE BY EDEN ROSALES
//ID: 900796598
#pragma once
#include <iostream>
#include "Stack.h"
#include <string> 
#include <Windows.h>
#include "Cursor.h"
using namespace std; 
class Stack {
public: 
	int STACKSIZE = 1000; //I am aware that this is not controlling the size of the stack, but i use this to make the
	//functions for stack easily changed and debugged if i need to change the size of the stack 
	int current=-1;//tracking variable 
	Cursor theStack[1000];
	void push(Cursor);
	Cursor pop();//returns the top of the stack, and deletes it 
	Cursor peek();//retursn the top of the stack, without deleting it 
	bool isEmpty();//checks if the stack is empty or not 
	bool isFull();//checks if the stack if full or not 
	
};