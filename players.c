#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "players.h"
#include <ctype.h>

//Opening the player file
FILE* openPlayerFile(const char* mode){
    FILE* fp;

    fp = fopen("players.txt", mode);
    if(fp == NULL){
        printf("Unable to open file...\n");
        return NULL;
    }

    return fp;
}

//Adding a new player
void addPlayer(){
    Player player;

    FILE* fp = openPlayerFile("a");

    if(fp == NULL){
        printf("Unable to open file...\n");
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

    printf("HEIGHT (m): ");
    scanf("%f", &player.height);

    printf("WEIGHT (kg): ");
    scanf("%f", &player.weight);

    printf("POINTS PER GAME (PPG): ");
    scanf("%f", &player.ppg);

    printf("REBOUNDS PER GAME (RPG): ");
    scanf("%f", &player.rpg);

    printf("ASSISTS PER GAME (APG): ");
    scanf("%f", &player.apg);

    printf("STEALS PER GAME (SPG): ");
    scanf("%f", &player.spg);

    printf("BLOCKS PER GAME (BPG): ");
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
        printf("Unable to search player...\n");
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

//Comparison functions for sorting (declared outside of SortPlayers function)
int compareName(const void* a, const void* b){
    return strcmp(((Player*)a)->name, ((Player*)b)->name);
}

int compareAge(const void* a, const void* b){
    return ((Player*)b)->age - ((Player*)a)->age;
}

int compareSeason(const void* a, const void* b){
    return ((Player*)b)->season - ((Player*)a)->season;
}

int compareTeam(const void* a, const void* b){
    return strcmp(((Player*)a)->team, ((Player*)b)->team);
}

int compareJerseyNumber(const void*a, const void* b){
    return((Player*)b)->jerseyNumber - ((Player*)a)->jerseyNumber;
}

int compareHeight(const void* a, const void* b){
    return ((Player*)b)->height > ((Player*)a)->height ? 1 : -1;
}

int compareWeight(const void* a, const void* b){
    return ((Player*)b)->weight > ((Player*)a)->weight ? 1 : -1;
}

int comparePPG(const void* a, const void* b){
    return ((Player*)b)->ppg > ((Player*)a)->ppg ? 1 : -1;
}

int compareRPG(const void* a, const void* b) {
    return ((Player*)b)->rpg > ((Player*)a)->rpg ? 1 : -1;
}

int compareAPG(const void* a, const void* b) {
    return ((Player*)b)->apg > ((Player*)a)->apg ? 1 : -1;
}

int compareSPG(const void* a, const void* b) {
    return ((Player*)b)->apg > ((Player*)a)->apg ? 1 : -1;
}

int compareBPG(const void* a, const void* b) {
    return ((Player*)b)->bpg > ((Player*)a)->bpg ? 1 : -1;
}

void sortPlayers(){
    FILE* fp = openPlayerFile("r");

    if(fp == NULL){
        printf("Unable to sort players...\n");
        return;
    }

    Player players[450]; //Assuming that in each of the 30 NBA teams, there are max 15 players!
    int count = 0;
    int choice; //Local scope; won't affect choice variable of main program
    char saveOption;

    while(fscanf(fp, "%49[^,],%d,%d,%49[^,],%d,%f,%f,%f,%f,%f,%f,%f\n",
                 players[count].name, &players[count].age, &players[count].season, 
                 players[count].team, &players[count].jerseyNumber, 
                 &players[count].height, &players[count].weight, 
                 &players[count].ppg, &players[count].rpg, 
                 &players[count].apg, &players[count].spg, 
                 &players[count].bpg) == 12){
                    count++;
    }

    fclose(fp);

    //Prompt the user to sort players based on the selected option
    printf("1. NAME\n");
    printf("2. AGE\n");
    printf("3. SEASON\n");
    printf("4. TEAM\n");
    printf("5. JERSEY #\n");
    printf("6. HEIGHT\n");
    printf("7. WEIGHT\n");
    printf("8. POINTS PER GAME\n");
    printf("9. REBOUNDS PER GAME\n");
    printf("10. ASSISTS PER GAME\n");
    printf("11. STEALS PER GAME\n");
    printf("12. BLOCKS PER GAME\n");
    printf("Select how these players should be sorted: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            qsort(players, count, sizeof(Player), compareName);
            break;
        case 2:
            qsort(players, count, sizeof(Player), compareAge);
            break;
        case 3:
            qsort(players, count, sizeof(Player), compareSeason);
            break;
        case 4:
            qsort(players, count, sizeof(Player), compareTeam);
            break;
        case 5:
            qsort(players, count, sizeof(Player), compareJerseyNumber);
            break;
        case 6:
            qsort(players, count, sizeof(Player), compareHeight);
            break;
        case 7:
            qsort(players, count, sizeof(Player), compareWeight);
            break;
        case 8:
            qsort(players, count, sizeof(Player), comparePPG);
            break;
        case 9:
            qsort(players, count, sizeof(Player), compareRPG);
            break;
        case 10:
            qsort(players, count, sizeof(Player), compareAPG);
            break;
        case 11:
            qsort(players, count, sizeof(Player), compareSPG);
            break;
        case 12:
            qsort(players, count, sizeof(Player), compareBPG);
            break;
        default: 
            printf("Invalid choice.\n");
            break;
    }

    //Print out the sorted players list
    //printf("\n--- SORTED PLAYERS ---\n");
    for(int i = 0; i < count; i++){
        printf("NAME: %s | AGE: %d | SEASON: %d | TEAM: %s | #: %d | HEIGHT: %.2f | WEIGHT: %.2f | PPG: %.1f | RPG: %.1f | APG: %.1f | SPG: %.1f | BPG: %.1f\n",
               players[i].name, players[i].age, players[i].season, players[i].team,
               players[i].jerseyNumber, players[i].height, players[i].weight,
               players[i].ppg, players[i].rpg, players[i].apg, players[i].spg, players[i].bpg);
    }

    printf("Would you like to save this sorting to the file? (Enter Y for Yes and N for No) ");
    scanf(" %c", &saveOption);

    if(toupper(saveOption) == 'Y'){
        fp = openPlayerFile("w");
        if(fp == NULL){
            printf("Unable to open file to save sorted player data...\n");
            return;
        }
        
        for(int i = 0; i < count; i++){
            fprintf(fp, "%s,%d,%d,%s,%d,%.2f,%.2f,%.1f,%.1f,%.1f,%.1f,%.1f\n",
                    players[i].name, players[i].age, players[i].season, players[i].team,
                    players[i].jerseyNumber, players[i].height, players[i].weight,
                    players[i].ppg, players[i].rpg, players[i].apg, players[i].spg, players[i].bpg);
                }
                
        fclose(fp);
        
        printf("\nSorting has been saved!\n"); //Users can select "View Players" option to verify
    }
}