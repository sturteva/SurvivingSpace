/*******************************************************************************
** Program: main.cpp
** Description: main function for Syrma's text adventure game: Surviving Space!
*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "game.hpp"
#include "room.hpp"


using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	// Variable Declaration
	int playerChoice;
    game gameState;
    string folder;
    
	// initilize dictionary for parser
	gameState.initializeDict();


    // DEBUG Room Vector
   /*
    vector<room*> newRooms = gameState.getRooms();
    for (int count = 0; count < (int)newRooms.size(); count++)
	{
		newRooms[count]->printRoomInfo();
	}
	*/
	
    system("clear");
	cout << "     _______. __    __  .______     ____    ____  __  ____    ____  __  .__   __.   _______         _______..______      ___       ______  _______  __  " << endl;
	cout << "    /       ||  |  |  | |   _  \\    \\   \\  /   / |  | \\   \\  /   / |  | |  \\ |  |  /  _____|       /       ||   _  \\    /   \\     /      ||   ____||  | " << endl;
	cout << "   |   (----`|  |  |  | |  |_)  |    \\   \\/   /  |  |  \\   \\/   /  |  | |   \\|  | |  |  __        |   (----`|  |_)  |  /  ^  \\   |  ,----'|  |__   |  | " << endl;
	cout << "    \\   \\    |  |  |  | |      /      \\      /   |  |   \\      /   |  | |  . `  | |  | |_ |        \\   \\    |   ___/  /  /_\\  \\  |  |     |   __|  |  | " << endl;
	cout << ".----)   |   |  `--'  | |  |\\  \\----.  \\    /    |  |    \\    /    |  | |  |\\   | |  |__| |    .----)   |   |  |     /  _____  \\ |  `----.|  |____ |__| " << endl;
	cout << "|_______/     \\______/  | _| `._____|   \\__/     |__|     \\__/     |__| |__| \\__|  \\______|    |_______/    | _|    /__/     \\__\\ \\______||_______|(__) " << endl;
	cout << "=======================================================================================================================================================" << endl << endl;
	cout << "(1.) Start New Adventure" << endl;
	cout << "(2.) Load Existing Adventure" << endl;
	cout << "(3.) Exit" << endl;
	cout << "Type 1, 2 or 3 to make your selection: ";
	cin >> playerChoice;

	// Makes sure that there is a valid input
	while(cin.fail() || playerChoice <= 0 || playerChoice > 3)
	{
		cout << "Error, Selection:";
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
			// initialize gameState
    		gameState.initializeRooms();

			// clear the screen
			system("clear");

			cout << "     _______. __    __  .______     ____    ____  __  ____    ____  __  .__   __.   _______         _______..______      ___       ______  _______  __  " << endl;
			cout << "    /       ||  |  |  | |   _  \\    \\   \\  /   / |  | \\   \\  /   / |  | |  \\ |  |  /  _____|       /       ||   _  \\    /   \\     /      ||   ____||  | " << endl;
			cout << "   |   (----`|  |  |  | |  |_)  |    \\   \\/   /  |  |  \\   \\/   /  |  | |   \\|  | |  |  __        |   (----`|  |_)  |  /  ^  \\   |  ,----'|  |__   |  | " << endl;
			cout << "    \\   \\    |  |  |  | |      /      \\      /   |  |   \\      /   |  | |  . `  | |  | |_ |        \\   \\    |   ___/  /  /_\\  \\  |  |     |   __|  |  | " << endl;
			cout << ".----)   |   |  `--'  | |  |\\  \\----.  \\    /    |  |    \\    /    |  | |  |\\   | |  |__| |    .----)   |   |  |     /  _____  \\ |  `----.|  |____ |__| " << endl;
			cout << "|_______/     \\______/  | _| `._____|   \\__/     |__|     \\__/     |__| |__| \\__|  \\______|    |_______/    | _|    /__/     \\__\\ \\______||_______|(__) " << endl;
			cout << "========================================================================================================================================================" << endl << endl;

			cout << "You, our intrepid hero, find yourself awakened upon the surface of a jungle planet." << endl << endl
				 << "You were on an exploratory mission for the International Space Federation," << endl
				 << "checking this planet out for rare minerals and to see if there was any intelligent life inhabiting the planet." << endl << endl
				 << "You aren’t exactly sure what happened, but something down on this planet shot at your ship, " << endl
				 << "forcing you to run to your escape pod..." << endl << endl
				 << "You find yourself at the base of a large tree, no esacpe pod in sight. " << endl
				 << "There is an animal path leading in two different directions, but the paths are completly blocked by a large thicket of bushes...."
				 << endl << endl;


			//cout << "Press ENTER to begin your journey...";
			//cin.get();
			//cout << endl << endl;


			// start game loop
			gameState.start();

			break;
		
		case 2:
			//load game
			

			cout << "Enter name of folder that contains gamestate files: ";
			cin >> folder;

			gameState.loadGameFromFolder(folder);
			cout << "Loading gamestate from files..." << endl;

			// start game loop
			gameState.start();


			break;


		case 3:
			cout << "Thanks for Playing!" << endl;

	}



	return 0;
}
