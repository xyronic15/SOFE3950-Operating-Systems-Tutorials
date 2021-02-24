/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Print the intro message
    printf("This is Jeopardy\n");
    
    // initialize each of the players in the array
    for(int i = 0; i < NUM_PLAYERS; i++){
        // prompt for player's name
        printf("Player%d name: ", (i + 1));
        scanf("%s", players[i].name);

        // Set the player's score to 0
        players[i].score = 0;
    }

    // Perform an infinite loop getting command input from users until game ends
    while (!all_answered())
    {

        // clear the command line
        system("clear");
        
        char chosenPlayer[MAX_LEN] = "";
        char chosenCategory[MAX_LEN] = "";
        int chosenValue = 0;

        do {
        if(strcmp(chosenPlayer, "") != 0)
        printf("The player %s was not found", chosenPlayer);

        printf("Enter first player's name: ");
        scanf("%s", (char *) &chosenPlayer);
        } while(!player_exists(players, 4, chosenPlayer));

        do {
        if(chosenValue != 0)
        printf("Invalid selection");

        printf("Enter category: ");
        getchar();
        fgets((char *) chosenCategory, MAX_LEN, stdin);
        strtok(chosenCategory, "\n");

        printf("Enter: ");
        scanf("%d", (int *) &chosenValue);
        } while(alreadyAnswered(chosenCategory, chosenValue));


        system("clear");
        display_question(chosenCategory, chosenValue);

        char *answer[MAX_LEN] = {0};
        getchar();
        fgets((char *) answer, MAX_LEN, stdin);

        char *tokenize_answer;
        tokenize((char *) answer, &tokenize_answer);

        if(tokenize_answer == NULL)
        printf("Try again");
        else if(valid_answer(chosenCategory, chosenValue, tokenize_answer)) {
        printf("Correct Answer!");
        printf("%s gains %d points \n", chosenPlayer, chosenValue);
        update_score(players, 4, chosenPlayer, chosenValue);
        } else {
        printf("Wrong Answer!");
        int num = get_question_number(chosenCategory, chosenValue);
        printf("Correct answer was: %s", questions[num].answer);
        }

        track_answered(chosenCategory, chosenValue);

        }

        show_results(players, 4);
        getchar();

    }
    return EXIT_SUCCESS;
}
