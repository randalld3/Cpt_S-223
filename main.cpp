/*
* Author:     Randall Dickinson
* Class:      Cpt_S 223
* Date:       9/13/22
* Assignment: PA1
* 
* ADVANTAGES/DISADVANTAGES LINKED LIST:
* Advantage: In this assignment, an insertAtFront() function is required. A linked list
* has a large advantage over an array for this. In an array, every item in the list would
* have to be shifted to make room for the new object. This is computationally expensive.
* In a linked list, the new item can be inserted and its pointer set to the previous head
* of the list. This has a constant runtime complexity, which is very efficient.
* Disadvantage: 
* One disadvantage to a linked list is its complexity. In order to easily run my code, I 
* had to make the CommandList class and include a lot of functions in order to navigate 
* the linked list to accomplish tasks such as searching the linked list in order to ensure
* a command is or is not present for the add and remove command functions. Even once the 
* correct command was found with the search function, it would pass back an index, and the 
* list would have to be navigated again by the delete command function to that index before
* it could delete the command.
* ADVANTAGES/DISADVANTAGES ARRAY:
* Advantage:
* One advantage to an array is its simplicity. For this assignment, the deletion of players
* is not required, nor is it required to insert players at the front of the array. As such, 
* it is very easy to code and all processes done with the array in this assignment are 
* computationally cheap, with the exception of reallocating new memory if needed.
* Disadvantage:
* A major disadvantage to an array involves its memory usage. In a traditional array, I would
* set the size of the array before compilation. If the number of players was to exceed the 
* size of the array, I would not be able to store them. I was able to account for this by 
* utilizing a vector, which has the ability to reallocate new memory space as needed once the
* vector is full. However, this involves copying every data element to the new storage location,
* which is very computationally expensive
*/

#include "linkedlist.h"
#include "functions.h"
#include <fstream>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	ifstream commandFile;
	ifstream playerFile;
	commandFile.open("commands.csv");
	playerFile.open("profiles.csv");
	CommandList<string>* gameCommands = new CommandList<string>;
	string newCommand;
	string commandDescription;
	vector<PlayerProfile<string>> playerList;
	PlayerProfile<string> currentPlayer;
	string playerName;
	int playerScore;

	while (!commandFile.eof()) // reading in commands from file
	{
		getline(commandFile, newCommand, ',');
		if (newCommand == "")
			break;
		getline(commandFile, commandDescription);
		gameCommands->insertAtFront(newCommand, commandDescription);
	}
	while (!playerFile.eof()) // reading in profiles from file
	{
		getline(playerFile, playerName, ',');
		if (playerName == "")
			break;
		playerFile >> playerScore;
		currentPlayer.name = playerName;
		currentPlayer.score = playerScore;
		playerList.insert(playerList.begin(), currentPlayer);
		getline(playerFile, playerName);
	}
	commandFile.close();
	playerFile.close();


	playerName = "";
	currentPlayer.name = "";
	currentPlayer.score = 0;
	int menuOption = 0;
	bool valid = false;
	bool exit = false;

	while (menuOption != 6) // entering main menu and game loop
	{
		cout << "Welcome to the Linux Command Matching Game!" << endl << endl << "Main Menu" << endl << endl;
		cout << "Please select an option listed below:" << endl;
		cout << "1. Game Rules" << endl << "2. Play Game" << endl << "3. Load Previous Game" << endl;
		cout << "4. Add Command" << endl << "5. Remove Command" << endl << "6. Exit" << endl;
		cin >> menuOption;
		valid = false;

		switch (menuOption)
		{
		case 1: displayRules();
			break;
		case 2:
			while (!valid) // will continue to loop until game is played, or player enters 'r' to return to main menu
			{
				cout << endl;
				currentPlayer.name = "";
				cout << "Please enter your name, or enter 'r' to return to main menu" << endl;
				cin >> ws;
				getline(cin, currentPlayer.name);
				valid = true;

				if (currentPlayer.name == "") // will prevent problems in reading/writing to files
				{
					cout << "Invalid Entry" << endl;
					valid = false;
				}
				for (int i = 0; i < playerList.size(); ++i) // ensures a player does not input a name already in use
				{
					if (playerList[i].name == currentPlayer.name)
					{
						cout << "Player already exists." << endl;
						valid = false;
					}
				}
			}
			if (currentPlayer.name != "r") // will enter game loop
			{
				playGame(&currentPlayer, gameCommands);
				playerList.insert(playerList.begin(), currentPlayer);
			}
			cout << endl;
			break;
		case 3:while (!exit) // will loop until player loads previous game, or enters 'r' to return to the main menu.
		{
			cout << endl;
			cout << "Please enter the name of a player to be loaded, or" << endl;
			cout << "enter 'r' to return to main menu" << endl;
			cin >> ws;
			getline(cin, playerName);
			if (playerName == "r")
				break;

			for (int i = 0; i < playerList.size(); ++i) // searches vector for previous player
			{
				if (playerList[i].name == playerName) // enters game loop with previous player
				{
					playGame(&playerList[i], gameCommands);
					exit = true;
				}
			}
			if (!exit)
			{
				cout << "Player not found" << endl;
			}
		}
			  cout << endl;
			  break;
		case 4: addCommand(gameCommands);
			break;
		case 5: removeCommand(gameCommands);
			break;
		case 6: cout << "Sad to see you go!" << endl;
			break;
		default: cout << "Invalid entry, please try again" << endl << endl; // ensures only valid choices
			break;
		}
	}
		ofstream outCommandFile;
		ofstream outPlayerFile;
		outCommandFile.open("commands.csv", ios::trunc); // deletes previous contents
		outPlayerFile.open("profiles.csv", ios::trunc); // deletes previous contents

		for (int i = 0; i < gameCommands->size(); ++i) // writes commands to file
		{
			outCommandFile << gameCommands->at(i, true) << ",";
			outCommandFile << gameCommands->at(i, false) << endl;
		}

		for (int i = 0; i < playerList.size(); ++i) // writes players to file
		{
			outPlayerFile << playerList[i].name << ", " << playerList[i].score << endl;
		}
		outCommandFile.close();
		outPlayerFile.close();
		delete gameCommands; // deallocate memory, confirmed by cout statements in removeNode function in CommandList object
	
	return 0;
}
