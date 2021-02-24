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
#include <strings.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array

    // initialize the categories first
    // set answered to false
    // Assign a value for each question
    for (int i = 0; i < 12; i++)
    {
        strcpy(questions[i].category, categories[i % 3]);
        questions[i].answered = false;

        if (i > 8){
            // Set 800 value
            questions[i].value = 800;
        } else if (i > 5){
            // Set 600  value
            questions[i].value = 600;
        } else if (i > 2){
            // Set 400 value
            questions[i].value = 400;
        } else{
            // Set 200 value
            questions[i].value = 200;
        }        
    }

    // Programming questions
    questions[0].value = 200;
    strcpy(questions[0].question, " A piece of code containing a group of statements that is written once but can be executed multiple times");
    strcpy(questions[0].answer, "a loop");

    questions[3].value = 400;
    strcpy(questions[0].question, "Who invented C++?");
    strcpy(questions[0].answer, "Bjarne Stroustrup");

    questions[6].value = 600;
    strcpy(questions[0].question, "A set of instructions that can be performed with or without a computer");
    strcpy(questions[0].answer, "an algorithm");

    questions[9].value = 800;
    strcpy(questions[0].question, "Command on Linux that shows current directory");
    strcpy(questions[0].answer, "pwd");

    // Algorithm questions
    questions[1].value = 200;
    strcpy(questions[0].question, "The data structure used to perform breadth first search");
    strcpy(questions[0].answer, "a queue");

    questions[4].value = 400;
    strcpy(questions[0].question, "This search algorithm runs in O(logn) time");
    strcpy(questions[0].answer, "binary search");

    questions[7].value = 600;
    strcpy(questions[0].question, "This data structure is made up of nodes with at most 2 children nodes per node");
    strcpy(questions[0].answer, "a binary tree");

    questions[10].value = 800;
    strcpy(questions[0].question, "This complexity measures the amount of time an algorithm may take");
    strcpy(questions[0].answer, "time complexity");

    // Databases Questions
    questions[2].value = 200;
    strcpy(questions[0].question, "The present day “Database Management Systems” have evolved from a class of programs known as");
    strcpy(questions[0].answer, "a file management system");

    questions[5].value = 400;
    strcpy(questions[0].question, "These take applications to links or references which point towards the final data storage destination");
    strcpy(questions[0].answer, "a Navigational Database");

    questions[8].value = 600;
    strcpy(questions[0].question, "These store data in rows and columns allowing the applications to search for data instead of references. Edgar F. Codd, created the relational data base model and shared his invention in a paper entitled “A Relational Model for Large Shared Databanks”");
    strcpy(questions[0].answer, "a relational database");

    questions[11].value = 800;
    strcpy(questions[0].question, "Currently a buzzword, it is comprised of all the NoSQL DBMS such as MongoDB, HBase, Cassandra, Redis and CouchDB");
    strcpy(questions[0].answer, "a Post-relational Database");
    
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array

    // Assign a column width
    int col_width = 15;

    // Print all of the categories on the first line
    for(int i = 0; i < NUM_CATEGORIES; i++){
        printf("%-*s", col_width, categories[i]);
    }
    printf("\n");

    // Print values for each question or "---" for unanswered questions
    // Print three values then go to the next line
    for (int i = 0; i < 12; i++)
    {
        if (!questions[i].answered)
        {
            printf("%-*d", col_width, questions[i].value);
        } else
        {
            printf("%-*s", col_width, " --- ");
        }

        if (i % 3 == 0)
        {
            printf("\n");
        }
    }
    

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
                // change question to answered
                questions[i].answered = true;
                // return true if correct answer
                return true;
            } else
            {
                // change question to answered
                questions[i].answered = true;
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

// Returns true if all the questions are answered
bool all_answered(void){
    // iterate through each question and check if answered
    for(int i = 0; i < 12; i++){
        if (!questions[i].answered)
        {
            // return false if even one question is unanswered
            return false;
        }
    }

    return true;
}

// prints the answer of a question
void print_answer(char *category, int value){

    // lookup the question and print the answer
    for(int i = 0; i < 12; i++){
        if(strcmp(questions[i].category, category) && questions[i].value == value){
            printf("Correct answer was: %s", questions[i].answer);
        }
    }
}