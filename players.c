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
        printf("Unable to add player...\n");
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
    player.team[strcspn(player.team, "\n")] = 0; //Don't include newline character into entry

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

    if(fp == NULL){
        printf("Unable to display players...\n");
        return; 
    }

    printf("\n---NBA PLAYERS---\n");

    while(fscanf(fp, "%49[^,],%d,%d,%49[^,],%d,%f,%f,%f,%f,%f,%f,%f\n", //%49[^,] gets at most 49 characters and except the \n and comma added in players.txt
                  player.name, &player.age, &player.season, player.team,
                  &player.jerseyNumber, &player.height, &player.weight,
                  &player.ppg, &player.rpg, &player.apg, &player.spg, &player.bpg) == 12){
        printf("NAME: %s | AGE: %d | SEASON: %d | TEAM: %s | #: %d | HEIGHT: %.2f | WEIGHT: %.2f | PPG: %.1f | RPG: %.1f | APG: %.1f | SPG: %.1f | BPG: %.1f\n",
               player.name, player.age, player.season, player.team, player.jerseyNumber,
               player.height, player.weight, player.ppg, player.rpg, player.apg, player.spg, player.bpg);
    }

    fclose(fp);
}

void searchPlayer(){
    char searchName[50];
    char line[256]; //Length can vary (ex. Shai Gilgeous-Alexander has a lot of characters just for name)
    Player player;

    FILE* fp = openPlayerFile("r");
    if(fp == NULL){
        printf("Unable to search players...\n");
        return;
    }

    while(getchar() != '\n');

    printf("SEARCH PLAYER: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0; //Do NOT include the newline

    int found = 0;

    while(fgets(line, sizeof(line), fp)){
        sscanf(line, "%49[^,],%d,%d,%49[^,],%d,%f,%f,%f,%f,%f,%f,%f",
               player.name, &player.age, &player.season, player.team,
               &player.jerseyNumber, &player.height, &player.weight,
               &player.ppg, &player.rpg, &player.apg, &player.spg, &player.bpg);

        if(strcmp(player.name, searchName) == 0){
            printf("\nPlayer found:\n");
            printf("NAME: %s | AGE: %d | SEASON: %d | TEAM: %s | #: %d | HEIGHT: %.2f | WEIGHT: %.2f | PPG: %.1f | RPG: %.1f | APG: %.1f | SPG: %.1f | BPG: %.1f\n",
                   player.name, player.age, player.season, player.team, player.jerseyNumber,
                   player.height, player.weight, player.ppg, player.rpg, player.apg, player.spg, player.bpg);
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Player not found.\n");
    }

    fclose(fp);
}

//Updating a player's information
void updatePlayer(){
    char searchName[50];
    Player player;
    int found = 0;

    FILE *fp = openPlayerFile("r");
    FILE *temp = fopen("temp.txt", "w"); //To write new version/updated file

    if(fp == NULL || temp == NULL){
        printf("Unable to update player...\n");
        return;
    }

    while(getchar() != '\n');

    printf("NAME: "); //Search by name
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    while(fscanf(fp, "%49[^,],%d,%d,%49[^,],%d,%f,%f,%f,%f,%f,%f,%f\n",
                  player.name, &player.age, &player.season, player.team,
                  &player.jerseyNumber, &player.height, &player.weight,
                  &player.ppg, &player.rpg, &player.apg, &player.spg, &player.bpg) == 12){

        if(strcmp(player.name, searchName) == 0){
            printf("Player found! Enter new details:\n");

            printf("AGE: ");
            scanf("%d", &player.age);

            printf("SEASON: ");
            scanf("%d", &player.season);

            while(getchar() != '\n');

            printf("TEAM: ");
            fgets(player.team, sizeof(player.team), stdin);
            player.team[strcspn(player.team, "\n")] = 0;

            printf("JERSEY #: ");
            scanf("%d", &player.jerseyNumber);

            printf("HEIGHT: ");
            scanf("%f", &player.height);

            printf("WEIGHT: ");
            scanf("%f", &player.weight);

            printf("PPG: ");
            scanf("%f", &player.ppg);

            printf("RPG: ");
            scanf("%f", &player.rpg);

            printf("APG: ");
            scanf("%f", &player.apg);

            printf("SPG: ");
            scanf("%f", &player.spg);

            printf("BPG: ");
            scanf("%f", &player.bpg);

            found = 1;
        }

        fprintf(temp, "%s,%d,%d,%s,%d,%.2f,%.2f,%.1f,%.1f,%.1f,%.1f,%.1f\n",
                player.name, player.age, player.season, player.team, player.jerseyNumber,
                player.height, player.weight, player.ppg, player.rpg, player.apg, player.spg, player.bpg);
    }

    fclose(fp);
    fclose(temp);

    remove("players.txt");
    rename("temp.txt", "players.txt");

    if(found){
        printf("Player updated successfully!\n");
    }
    else{
        printf("Player not found.\n");
    }
}

//Deleting a player from the .txt file
void deletePlayer(){
    char searchName[50];
    Player player;
    int found = 0;

    FILE *fp = openPlayerFile("r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL || temp == NULL){
        printf("Unable to open file to delete player...\n");
        return;
    }

    while(getchar() != '\n');

    printf("NAME: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;

    while(fscanf(fp, "%49[^,],%d,%d,%49[^,],%d,%f,%f,%f,%f,%f,%f,%f\n",
                  player.name, &player.age, &player.season, player.team,
                  &player.jerseyNumber, &player.height, &player.weight,
                  &player.ppg, &player.rpg, &player.apg, &player.spg, &player.bpg) == 12){

        if(strcmp(player.name, searchName) == 0){
            found = 1;
            continue; //Skip the named player onto temp.txt; won't be included in the updated players.txt
        }

        fprintf(temp, "%s,%d,%d,%s,%d,%.2f,%.2f,%.1f,%.1f,%.1f,%.1f,%.1f\n",
                player.name, player.age, player.season, player.team, player.jerseyNumber,
                player.height, player.weight, player.ppg, player.rpg, player.apg, player.spg, player.bpg);
    }

    fclose(fp);
    fclose(temp);

    remove("players.txt");
    rename("temp.txt", "players.txt");

    if(found){
        printf("Player deleted successfully!\n");
    }
    else{
        printf("Player not found.\n");
    }
}