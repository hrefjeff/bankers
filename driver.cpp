/****************************************************
    Names       : Geoffrey Morris & Jeffrey Allen
    Date        : CS420 Spring 2014
    Assignment  : Banker's Algorithm
    Description : The Banker's Algorithm is a deadlock avoidance algorithm.
    			  In this implementation, it is done by taking a snapshot of
    			  the current state of the system, and testing to see if in fact
    			  deadlock has occured.
    			  
    			  The Resource-Request Algorithm implemented here allows a
    			  user to send a resource request to the system and give
    			  feed-back on whether or not deadlock will occur.

    			  Default values from "Operating Systems Concepts" PG340, Question 7.3 are used.
    Due Date    : November 20, 2014
*****************************************************/

#include "Globals.h"
#include "Snapshot.h"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	bool safeState = false; //Does what it says on the tin; state is safe or unsafe
	Snapshot currentState; //Declare a snapshot object of the current system state
	int command = 0;
	string file;
	int requestVector[resources] = { 0, 4, 2, 0 }; //default request for resources

	do{
		system("cls");
		cout << "1. Take snapshot of current state" << endl;
		cout << "2. Print snapshot of current state" << endl;
		cout << "3. Test for safe state" << endl;
		cout << "4. Request resources (0,4,2,0)" << endl;
		cout << "5. Quit" << endl;
		cout << "Choose an option: ";
		cin >> command;

		switch (command){

			case 1:{
				cout << endl << "Type file name: ";
				cin >> file;
				currentState.InputFile(file); //Build the current state from an input file
				break;
			}

			case 2:{
				if (!currentState.IsEmpty()){
					currentState.PrintState(); //Print the current state to the console
				}
				else{
					cout << "Please take a snapshot of the current state first!" << endl << endl;
				}
				system("pause");
				break;
			}

			case 3:{
				if (!currentState.IsEmpty()){
					safeState = currentState.testSafeState();
					if (safeState){
						cout << endl << "State is SAFE" << endl << endl;
						system("pause");
						break;
					}
					else{
						cout << endl << "State is UNSAFE" << endl << endl;
						system("pause");
						break;
					}
				}
				else{
					cout << "Please take a snapshot of the current state first!" << endl << endl;
					system("pause");
					break;
				}
			}

			case 4:{
				if (!currentState.IsEmpty()){
					currentState.resourceRequest(1, requestVector);
					system("pause");
					break;
				}
				else{
					cout << "Please take a snapshot of the current state first!" << endl << endl;
					system("pause");
					break;
				}
			}
		}
	}while (command != 5);

	return 0;	
}