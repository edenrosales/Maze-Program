//MADE BY EDEN ROSALES
//ID: 900796598
#include "Stack.h"


void Stack::push(Cursor x)//adds a cursor to the stack...ERROR printed if the stack is full
{
	if (!isFull()) {//as long as the stack is not full, will add the cursor to the top of the stack
		current++;//increments the tracking vvariable 
		theStack[current] = x; //places the cursor in the stack
	}
	else {//error message if the stack is full 
		cout << "ERROR";
	}
}
Cursor Stack::pop() {//pops the top value from the stack, if it is empty, returns a cursor with error values 
	Cursor returning;//the return variable 
	if (!isEmpty()) {//while the stack is not empty 
		returning = theStack[current];//places the top of the stack into the return variable 
		current--; //decrements the tracking variable 
		return returning;//returns the return variable 
	}
	else {//if stack is empty, it will return a cursor with error values 
		Cursor x; 
		x.x = -1;
		x.y = -1;
		return x; //this is the value that will represent a failure of the function
	}
}
Cursor Stack::peek()//returns the top of the stack without deleting it 
{
	if (!isEmpty())//while the stakc is not empty 
		return theStack[current];//returns the top of the stack
	else {//if the stack is empty, returns a cursor with error values 
		Cursor x;
		x.x = -1;
		x.y = -1;
		return x;
	}
}

bool Stack::isEmpty() {//checks if the stack is empty or not 
	if (current <= -1) {//if the tracking variable is at the place -1, we know that the stack is empty
		return true;
	}
	else//if tracking variable is not at -1, we know that the stack is not empty 
	return false;
}
bool Stack::isFull() {//returns if the stack is full or not 
	if (current >= STACKSIZE-1) {//if the tracking varaible is not = to STACKSIZE-1, we know that it is not full, but if it is, we return true 
		return true; 
	}
	else//if the tracking variable is not = STACKSIZE -1, we know that the stack is not full, and we will return false 
	return false; 
}

