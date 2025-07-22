#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "players.h"

//Opening the player file
FILE* openPlayerFile(const char* mode){
    FILE* fp;

    fp = fopen("players.txt", mode);
    if(fp == NULL){
        printf("File could not be opened...\n");
        return NULL;
    }

    return fp;
}

//Adding a new player
void addPlayer(){
    Player player;
    FILE* fp = openPlayerFile("a");

    if(fp == NULL){
        printf("Could not add player...\n");
        return;
    }

    while(getchar() != '\n'); //Remove newline character before fgets, or else NAME gets skipped

    printf("NAME: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = 0; //Don't include newline character into entry

    printf("AGE: ");
    scanf("%d", &player.age);

    printf("SEASON: ");
    scanf("%d", &player.season);

    while(getchar() != '\n'); //Remove newline character before fgets, or else TEAM gets skipped

    printf("TEAM: ");
    fgets(player.team, sizeof(player.team), stdin);
    player.name[strcspn(player.name, "\n")] = 0; //Don't include newline character into entry

    printf("JERSEY #: ");
    scanf("%d", &player.jerseyNumber);

    printf("HEIGHT: "); //Need to add metric conversion
    scanf("%f", &player.height);

    printf("WEIGHT: "); //Need to add metric conversion
    scanf("%f", &player.weight);

    printf("POINTS PER GAME: ");
    scanf("%f", &player.ppg);

    printf("REBOUNDS PER GAME: ");
    scanf("%f", &player.rpg);

    printf("ASSISTS PER GAME: ");
    scanf("%f", &player.apg);

    printf("STEALS PER GAME: ");
    scanf("%f", &player.spg);

    printf("BLOCKS PER GAME: ");
    scanf("%f", &player.bpg);

    fprintf(fp, "%s,%d,%d,%s,%d,%.2f,%.2f,%.1f,%.1f,%.1f,%.1f,%.1f\n",
            player.name, player.age, player.season, player.team, player.jerseyNumber,
            player.height, player.weight, player.ppg, player.rpg, player.apg, player.spg, player.bpg);

    fclose(fp);
}

//Displaying all players from the file
void displayPlayers(){
    Player player;
    FILE* fp = openPlayerFile("r");

    if (fp == NULL){
        printf("Could not display players...\n");
        return; 
    }

    printf("\n---NBA PLAYERS---\n");

    while(fscanf(fp, "%49[^,],%d,%d,%49[^,],%d,%f,%f,%f,%f,%f,%f,%f\n",
                  player.name, &player.age, &player.season, player.team,
                  &player.jerseyNumber, &player.height, &player.weight,
                  &player.ppg, &player.rpg, &player.apg, &player.spg, &player.bpg) == 12){
        printf("NAME: %s | AGE: %d | SEASON: %d | TEAM: %s | #: %d | HEIGHT: %.2f | WEIGHT: %.2f | PPG: %.1f | RPG: %.1f | APG: %.1f | SPG: %.1f | BPG: %.1f\n",
               player.name, player.age, player.season, player.team, player.jerseyNumber,
               player.height, player.weight, player.ppg, player.rpg, player.apg, player.spg, player.bpg);
    }

    fclose(fp);
}