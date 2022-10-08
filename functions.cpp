#include "functions.h"

#define MIN_ROUNDS 5
#define MAX_ROUNDS 30
#define POSSIBLE_OPTIONS 3

/*Name: displayRules
* Description: Will display the rules for the Linux Command Matching Game before returning.
* History: Created 9-7-22
* Inputs: None
* Outputs: The rules of the game printed to the screen.
* Returns: None
* Precondition: None
* Postcondition: None
*/
void displayRules(void) 
{
	cout << endl;
	cout << "The rules of the game are as follows:" << endl;
	cout << "At the start of the game, the player will choose how many questions they wish to be asked." << endl;
	cout << "With each round, the player will be given the description of a linux command." << endl;
	cout << "Three commands will be presented to the player." << endl;
	cout << "The player should enter the letter that is adjacent to the correct command, and press \"enter\"" << endl;
	cout << "The correct command will then be presented, along with the description." << endl;
	cout << "If the player has chosen the correct command, the player gains one point." << endl;
	cout << "If the player has chosen the incorrect command, the player loses one point" << endl;
	cout << "At the end of the game, the points are tallied and the player is given a score" << endl;
	cout << "Scores are recorded and saved to the player's profile." << endl << endl;
	cout << "A player may choose to load their profile from a previous game by choosing \"Load Previous Game\" from the main menu" << endl << endl;
}

/*Name: playGame
* Description: Will run the game loop for the Linux Command Matching Game. This function will prompt
*              the player for a number of rounds (5-30) to play. Then, it will randomly pick commands
*              chosen from an input linked list of commands. It ensures commands are not used twice.
*              It will then choose one of three positions to place the correct description. Incorrect
*              descriptions will be shown in the other two positions. The player chooses their option,
*              and either gains or loses a point based on whether their choiuce is right. The players'
*              score is updated by pointer, and a vector keeps track of used and unused commands. This
*              continues until all rounds have been played, at which point the while loop completes
*              and the function ends.
* History: Created 9-9-22
* Inputs: A pointer to linked list of game commands, which require two string data elements. A pointer
*         to a vector of player profiles, witha string and an integer data elements.
* Outputs: Multiple messages to screen for the game play. Updates player vector by pointer.
* Returns: None
* Precondition: None
* Postcondition: Player profile will have updated score.
*/
void playGame(PlayerProfile<string>* player, CommandList<string>* gameCommands)
{
	cout << endl;
	int totalCommands = gameCommands->size();
	int roundCount = 0;
	vector<bool> commandUsage; // this will keep track of which commands have already been used in game play.
	for (int i = 0; i < totalCommands; ++i) // setting all commands to value of not used. 
		commandUsage.push_back(false);

	if (gameCommands->size() < MIN_ROUNDS) // Prevents infinite loop that will search for unused commands.
	{
		cout << "Commands List is too small for the game" << endl << endl;
		return;
	}

	while (roundCount < MIN_ROUNDS || roundCount > MAX_ROUNDS) // loop to verify valid round count.
	{
		cout << "Enter the number of rounds (5-30) you would like to play:" << endl;
		cin >> roundCount;
		if (roundCount < MIN_ROUNDS || roundCount > MAX_ROUNDS)
			cout << "Invalid entry. Round number must be between five and thirty" << endl;
	}
	cout << endl;

	for (int roundIndex = 0, positionIndex, commandChoice, tempCommand, commandIndex;
		roundIndex < roundCount; ++roundIndex) // loops until all rounds have been played.
	{

		commandIndex = rand() % totalCommands; // chooses random command
		cout << "Round " << roundIndex + 1 << endl << endl;
		while (commandUsage[commandIndex] == true) // will repeat until unused command is found
			commandIndex = rand() % totalCommands;
		commandUsage[commandIndex] = true;
		
		cout << gameCommands->at(commandIndex, true) << endl << endl;
		positionIndex = rand() % POSSIBLE_OPTIONS; // picks location for correct description

		for (int i = 0; i < POSSIBLE_OPTIONS; ++i) // shows 2 incorrect and 1 correct command description
		{
			tempCommand = rand() % totalCommands;
			while (tempCommand == commandIndex) // ensure the incorrect command description does not match the correct one
				tempCommand = rand() % totalCommands;

			cout << i + 1 << ". "; // show the choice number
			if (i == positionIndex) // show the correct description
				cout << gameCommands->at(commandIndex, false) << endl;
			else // show an incorrect description
				cout << gameCommands->at(tempCommand, false) << endl;
		}

		do // obtains a valid command description choice from player
		{
			cin >> commandChoice;
			if (commandChoice < 1 || commandChoice > 3)
				cout << "Please enter a valid option (1-3)" << endl;

		} while (commandChoice < 1 || commandChoice > 3);

		if (commandChoice == positionIndex + 1) // correct choice
		{
			cout << endl << "Correct! - ";
			++player->score;
		}
		else // incorrect choice
		{
			cout << endl << "Incorrect! - ";
			--player->score;
		}
		cout << gameCommands->at(commandIndex, true) << ": ";
		cout << gameCommands->at(commandIndex, false) << endl << endl;

		cout << "Your current score is " << player->score << endl;
		cout << endl;
	}
}

/*Name: addCommand
* Description: Will continually prompt player for commands and descriptions until 'r' is given to 
*              return to menu. Commands require verification from CommandList class insertAtFront 
*              function to ensure a command is not put in twice.
* History: Created 9-7-22
* Inputs: A pointer to a CommandList object
* Outputs: Prompts for commands, adds commands to linked list using CommandList insertAtFront function.
* Returns: None
* Precondition: None
* Postcondition: CommandList will have new nodes as they are inserted.
*/
void addCommand(CommandList<string>* head)
{
	cout << endl;

	while (1)
	{
		string command;
		string description;
		
		cout << "Enter the command you would like to add, or enter \"r\" to return to the main menu" << endl;
		cin >> ws;
		getline(cin, command);

		if (command == "r")
		{
			cout << endl;
			break;
		}
			
		cout << "Enter a description for your command" << endl;
		getline(cin, description);

		head->insertAtFront(command, description);
	} 
}

/*Name: removeCommand
* Description: Will continually prompt player for commands until 'r' is given to return to menu.
*              Commands require verification from CommandList class removeNode function to 
*              ensure a command is present in the list so that it may be removed.
* History: Created 9-7-22
* Inputs: A pointer to a CommandList object
* Outputs: Prompts for commands, removes commands from linked list using CommandList removeNode 
*          function.
* Returns: None
* Precondition: None
* Postcondition: CommandList will have less nodes as they are removed.
*/
void removeCommand(CommandList<string>* head)
{
	cout << endl;

	while (1)
	{
		string command;
		
		cout << "Enter the command you would like removed, or enter \"r\" to return to the main menu" << endl;
		cin >> ws;
		getline(cin, command);

		if (command == "r")
		{
			cout << endl;
			break;
		}

		head->removeNode(command);
	}
}