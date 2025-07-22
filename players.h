#ifndef PLAYERS_H
#define PLAYERS_H

//Player data
typedef struct{
	char name[50];
	int age;
	int season;
	char team[50];
	int jerseyNumber;
	float height;
	float weight;
	float ppg; //Points Per Game
	float rpg; //Rebounds Per Game
	float apg; //Assists Per Game
	float spg; //Steals Per Game
	float bpg; //Blocks Per Game
}Player;

FILE* openPlayerFile(const char* mode); //Open the player file

//Feature function declarations (including CRUD)
void addPlayer(); //CREATE
void displayPlayers(); //READ
void searchPlayer();
void updatePlayer(); //UPDATE
void deletePlayer(); //DELETE

#endif