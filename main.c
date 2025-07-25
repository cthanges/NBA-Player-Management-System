#include <stdio.h>
#include <stdlib.h>
#include "players.h"

int main(){
    int choice;

    do{
        printf("\n---NBA PLAYERS---\n");
        printf("1. Add Player\n");
        printf("2. View Players\n");
        printf("3. Search Player\n");
        printf("4. Update Player\n");
        printf("5. Delete Player\n");
        printf("6. Sort Players\n"); //User gets prompted further in the sortPlayers() function on players.c
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                addPlayer();
                break;
            case 2:
                displayPlayers();
                break;
            case 3:
                searchPlayer();
                break;
            case 4:
                updatePlayer();
                break;
            case 5:
                deletePlayer();
                break;
            case 6:
                sortPlayers();
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

    }while(choice != 0);

    return 0;
}