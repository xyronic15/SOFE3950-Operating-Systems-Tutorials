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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    // lookup the question and print if found
    for(int i = 0; i < 12; i++){
        if(strcmp(questions[i].category, category) && questions[i].value == value){
            printf("%s", questions[i].question);
            return;
        }
    }

    // Print not found
    printf("Question not found");
    return;
    
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // lookup the question and check the answer
    for(int i = 0; i < 12; i++){
        if(strcmp(questions[i].category, category) && questions[i].value == value){
            // Compare the answer
            if(strcasecmp(questions[i].answer, answer)){
                // Return true if correct
                return true;
            } else
            {
                return false;
            }
        }
    }

    // Return false if question not found at all
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for(int i = 0; i < 12; i++){
        if(strcmp(questions[i].category, category) && questions[i].value == value){
            if (questions[i].answered)
            {
                // Print already answered message if answered
                printf("This question is already answered!");
                return questions[i].answered;
            } else
            {
                // Just return if not answered yet
                return questions[i].answered;
            }
        }
    }

    // Print a message that says the question doesn't exist
    printf("Question does not exist");
    // Return true if question doesn't exist
    return true;
}
