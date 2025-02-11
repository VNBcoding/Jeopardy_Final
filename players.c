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
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    for(int i = 0; i < num_players; i++) {
        player p = players[i];
        if(strstr(p.name, name)) {
            return true;
        }
    }
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score)//TODO
{
    for(int i = 0; i < num_players; i++) {
        player p = players[i];
        if(strstr(p.name, name)) {
            p.score += score;
            players[i] = p;
        }
    }
}
