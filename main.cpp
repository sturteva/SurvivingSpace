/********************************************************
** Program: main.cpp
** Description: A text adventure game. 
********************************************************/
using namespace std;
//  .___________. __________   ___ .___________.        ___       _______  ____    ____  _______ .__   __. .___________. __    __  .______       _______ 
//  |           ||   ____\  \ /  / |           |       /   \     |       \ \   \  /   / |   ____||  \ |  | |           ||  |  |  | |   _  \     |   ____|
//  `---|  |----`|  |__   \  V  /  `---|  |----`      /  ^  \    |  .--.  | \   \/   /  |  |__   |   \|  | `---|  |----`|  |  |  | |  |_)  |    |  |__   
//      |  |     |   __|   >   <       |  |          /  /_\  \   |  |  |  |  \      /   |   __|  |  . `  |     |  |     |  |  |  | |      /     |   __|  
//      |  |     |  |____ /  .  \      |  |         /  _____  \  |  '--'  |   \    /    |  |____ |  |\   |     |  |     |  `--'  | |  |\  \----.|  |____ 
//      |__|     |_______/__/ \__\     |__|        /__/     \__\ |_______/     \__/     |_______||__| \__|     |__|      \______/  | _| `._____||_______|
//                                                                                                                                                                                                                                                                                                                                     
#include <iostream>
#include "game.hpp"

int main()
{
	// Variable Declaration
	int playerChoice;
    game gameState; 

	// create rooms
	room exitRoom("exit", NULL);
	room entrance("entrance", &exitRoom);

    // initilize gameState
    gameState.initlize(&entrance);

    cout << "======================== Text Adventure ========================" << endl;
	cout << "(1.) Start Text Adventure" << endl;
	cout << "(2.) Exit" << endl;
	cout << "Type 1 or 2 to make your selection: ";
	cin >> playerChoice;

	// Makes sure that there is a valid input
	while(cin.fail() || playerChoice <= 0 || playerChoice >= 3) 
	{
		cout << "Error, Selection:" << endl;
		cin.clear();
		cin.ignore(256,'\n');
		cin >> playerChoice;
	}
	
	// Clear the buffer
	cin.clear();
	cin.ignore(256,'\n');
	
	// Process choice
	switch (playerChoice)
	{
		case 1:
			//system("clear"); // clear the screen

			cout << "  .___________. __________   ___ .___________.        ___       _______  ____    ____  _______ .__   __. .___________. __    __  .______       _______ " << endl;
			cout << "  |           ||   ____\\  \\ /  / |           |       /   \\     |       \\ \\   \\  /   / |   ____||  \\ |  | |           ||  |  |  | |   _  \\     |   ____|" << endl;
			cout << "  `---|  |----`|  |__   \\  V  /  `---|  |----`      /  ^  \\    |  .--.  | \\   \\/   /  |  |__   |   \\|  | `---|  |----`|  |  |  | |  |_)  |    |  |__   " << endl;
			cout << "      |  |     |   __|   >   <       |  |          /  /_\\  \\   |  |  |  |  \\      /   |   __|  |  . `  |     |  |     |  |  |  | |      /     |   __|  " << endl;
			cout << "      |  |     |  |____ /  .  \\      |  |         /  _____  \\  |  '--'  |   \\    /    |  |____ |  |\\   |     |  |     |  `--'  | |  |\\  \\----.|  |____ " << endl;
			cout << "      |__|     |_______/__/ \\__\\     |__|        /__/     \\__\\ |_______/     \\__/     |_______||__| \\__|     |__|      \\______/  | _| `._____||_______|" << endl;

			cout << "\nPress ENTER to begin adventure";
			cin.get();
			cout << endl << endl;

			// initlize game
			//gameState.initlize();

			// start game loop
			gameState.start();
			
			break;
		case 2:
			cout << "Thanks for Playing!" << endl;
			return 0;
	}



	return 0;
}