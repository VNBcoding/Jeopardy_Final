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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    question s1;
    strcpy(s1.category, "sports");
    strcpy(s1.question, "Is soccer the most popular sport in the world?");
    strcpy(s1.answer, "yes");
    s1.value = 100;
    s1.answered = false;
    questions[0] = s1;

    question s2;
    strcpy(s2.category, "sports");
    strcpy(s2.question, "Is Michael Jordan the all time points leader in the NBA?");
    strcpy(s2.answer, "no");
    s2.value = 200;
    s2.answered = false;
    questions[3] = s2;

    question s3;
    strcpy(s3.category, "sports");
    strcpy(s3.question, "Has Bayern Munich won the second most Champion League Titles?");
    strcpy(s3.answer, "no");
    s3.value = 300;
    s3.answered = false;
    questions[6] = s3;

    question s4;
    strcpy(s4.category, "sports");
    strcpy(s4.question, "Did the Toronto Blue Jays win back-to-back World Series?");
    strcpy(s4.answer, "yes");
    s4.value = 400;
    s4.answered = false;
    questions[9] = s4;

    question c1;
    strcpy(c1.category, "countries");
    strcpy(c1.question, "Is Canada the second-largest country in the world by land area?");
    strcpy(c1.answer, "yes");
    c1.value = 100;
    c1.answered = false;
    questions[1] = c1;

    question c2;
    strcpy(c2.category, "countries");
    strcpy(c2.question, "Is Tokyo the capital of Japan?");
    strcpy(c2.answer, "yes");
    c2.value = 200;
    c2.answered = false;
    questions[4] = c2;

    question c3;
    strcpy(c3.category, "countries");
    strcpy(c3.question, "Is the Great Wall of China visible from space?");
    strcpy(c3.answer, "no");
    c3.value = 300;
    c3.answered = false;
    questions[7] = c3;

    question c4;
    strcpy(c4.category, "countries");
    strcpy(c4.question, "Is Nigeria the most populated country in Africa?");
    strcpy(c4.answer, "yes");
    c4.value = 400;
    c4.answered = false;
    questions[10] = c4;

    question o1;
    strcpy(o1.category, "os");
    strcpy(o1.question, "Is Linux an open-source operating system?");
    strcpy(o1.answer, "yes");
    o1.value = 100;
    o1.answered = false;
    questions[2] = o1;

    question o2;
    strcpy(o2.category, "os");
    strcpy(o2.question, "Is Windows developed by Apple?");
    strcpy(o2.answer, "no");
    o2.value = 200;
    o2.answered = false;
    questions[5] = o2;

    question o3;
    strcpy(o3.category, "os");
    strcpy(o3.question, "Does the fork() function create 2 child processes?");
    strcpy(o3.answer, "no");
    o3.value = 300;
    o3.answered = false;
    questions[8] = o3;

    question o4;
    strcpy(o4.category, "os");
    strcpy(o4.question, "Can a process in user mode directly modify the kernel memory in a modern operating system?");
    strcpy(o4.answer, "no");
    o4.value = 400;
    o4.answered = false;
    questions[11] = o4;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf("  Sports      Countries        OS\n");
    for(int i = 0; i < NUM_QUESTIONS; i += 3) {
        if(questions[i].answered) printf("   %s   ", "   ");
        else printf("   %d   ", questions[i].value);

        if(questions[i+1].answered) printf("        %s   ", "   ");
        else printf("        %d   ", questions[i+1].value);

        if(questions[i+2].answered) printf("        %s   \n", "   ");
        else printf("        %d   \n", questions[i+2].value);
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for(int i = 0; i < NUM_QUESTIONS; i++) {
        question q = questions[i];
        if(strstr(category, q.category) && q.value == value) {
            printf("%d: %s\n> ", q.value, q.question);
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for(int i = 0; i < NUM_QUESTIONS; i++) {
        question q = questions[i];
        if(strstr(category, q.category) && q.value == value) {
            q.answered = true;
            questions[i] = q;
            if(strstr(q.answer, answer)) {
                return true;
            } else {
                printf("Incorrect, the correct answer is: %s\n", q.answer);
            }
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for(int i = 0; i < NUM_QUESTIONS; i++) {
        question q = questions[i];
        if(strstr(category, q.category) && q.value == value) {
            return q.answered; 
        }
    }
    return false;
}