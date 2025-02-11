/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U
 *
 * Copyright (C) 2025, Salum Khatib, Sufyan Mohammed, Viet Nguyen Bao, Danial Shaikh
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
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

void str_lower_case(char *str);

void display_instructions();

void bubble_sort(player *arr);

void swap(player *a, player *b);

int main()
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    display_instructions();
    initialize_game();

    // Prompt for players names and append them to an array of players
    for(int i = 0; i < NUM_PLAYERS; i++) {
        char *name = calloc(256, sizeof(char));
        player p;
        p.score = 0;
        printf("Enter player %d's name: ", i+1);
        scanf("%s", name);
        strcpy(p.name, name);
        players[i] = p;
        free(name);
    }
    
    // initialize each of the players in the array
    
    int counter = 0;
    // Perform an infinite loop getting command input from users until game ends
    while (true)
    {

        // initialize name and category and allocate memroy
        char *name = calloc(256, sizeof(char));
        char *category = calloc(256, sizeof(char));

        // get the player whos turn it is, validate it and display error message if appropriate
        while (true) {
            printf("Enter the current player: ");
            scanf("%s", name);
            if(player_exists(players, NUM_PLAYERS, name)) {
                break;
            }
            printf("There is no player named %s \n", name);
        }

        // display categories
        display_categories();

        int value;
        //Keeps asking for category and value till one that has not been chosen is picked
        ASK:
        while (true) {
            printf("What category do you want, %s?\n", name);
            scanf(" %s", category);
            str_lower_case(category);
            if (strstr(category, "sports") || strstr(category, "countries") ||strstr(category, "os")){
             break;
            }
        }

        while (true){
            char *v = calloc(BUFFER_LEN, sizeof(char));
            printf("What value do you want, %s?\n", name);
            scanf("%s", v);
            value = atoi(v);
            if(value == 100|| value == 200 || value == 300 || value == 400){
                break;
            }
            free(v);
        }
    
        // restarts the questions selection loop
        if(already_answered(category, value) == true)
        {
            printf("That question has been answered\n");
            goto ASK;
        }

        //shows question and checks for the answer
        display_question(category, value);

        char *answer = calloc(BUFFER_LEN, sizeof(char));
        char *cleaned_answer = calloc(BUFFER_LEN, sizeof(char));

        // reads in answer, tokenizes it and validates that it has who is or what is as well as yes or no
        while (true) {
            char **tokens = calloc(BUFFER_LEN, sizeof(char*));
            scanf("\n%[^\n]c", answer);
            str_lower_case(answer);
            tokenize(answer, tokens);
            if ((strstr(tokens[0], "who") || strstr(tokens[0], "what")) && strstr(tokens[1], "is")) {
                if(strstr(tokens[2], "yes") || strstr(tokens[2], "no")) {
                    cleaned_answer = tokens[2];
                    break;
                } else {
                    printf("Please answer using yes or no!\n");
                }
            } else {
                printf("Please answer using \"who is\" or \"what is\"!\n");
            }

            free(tokens);
        }

        // print if the answer is correct and display score. display answer if incorrect
        if (valid_answer(category, value, cleaned_answer))
        {
            update_score(players, NUM_PLAYERS, name, value);
            for(int i = 0; i < NUM_PLAYERS; i++) {
                player p = players[i];
                if(strstr(p.name, name)) {
                    printf("Correct! %s's score is now: %d \n", name, p.score);
                }
            }
        } else {
            for(int i = 0; i < NUM_PLAYERS; i++) {
                player p = players[i];
                if(strstr(p.name, name)) {
                    printf("%s's score is still: %d \n", name, p.score);
                }
            }
        }

        // free memory
        free(answer);
        free(name);
        free(category);

        counter++;

        // Display the final results and exit
        if(counter >= 12){
            show_results(players, NUM_PLAYERS);
            break;
        }

    }
    return EXIT_SUCCESS;
}

// displays instructions
void display_instructions() {
    printf("Instructions:\n");
    printf("Firstly, enter all 4 players names.\n\nThen enter the category and dollar amount of question.\n\n");
    printf("Next answer the question with \"who is yes\" or \"who is no\". \"What is\" is also accepted.");
    printf("\n\nWhen all questions have been answered the final results will be displayed.\n\n");
}

// converts a string to lower case
void str_lower_case(char *str) {
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

// splits input into tokens and appends them to an array
void tokenize(char *input, char **tokens) {
    char *token = strtok(input, " ");
    int c = 0;

    while(token != NULL) {
        tokens[c++] = token;
        token = strtok(NULL, " ");
    }
}

// displays final game results
void show_results(player *players, int num_players) {
    bubble_sort(players);

    for(int i = 0; i < num_players; i++) {
        printf("%d. %s - %d\n", i+1, players[i].name, players[i].score);
    }

    printf("%s wins!", players[0].name);
}

// swap for bubble sort
void swap(player *a, player *b) {
    player temp = *a;
    *a = *b;
    *b = temp;
}

// bubble sort implementation
void bubble_sort(player *arr) {
    for(int i = 0; i < NUM_PLAYERS; i++){
        for(int j = 0; j < NUM_PLAYERS - i - 1; j++) {
            if(arr[j].score < arr[j+1].score) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}