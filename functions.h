#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "linkedlist.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

void displayRules(void);
void playGame(PlayerProfile<string>* player, CommandList<string>* gameCommands);
void addCommand(CommandList<string>* head);
void removeCommand(CommandList<string>* head);

#endif