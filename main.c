#include <stdio.h>
#include <stdlib.h>
#include "players.h"

int main() {
    int choice;

    do{
        printf("\n---NBA PLAYERS---\n");
        printf("1. Add Player\n"); //CREATE
        printf("2. View Players\n"); //READ
        printf("3. Search Player\n");
        printf("4. Update Player\n"); //UPDATE
        printf("5. Delete Player\n"); //DELETE
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
            case 0:
                exit(0);
                break;
            default:
                printf("Invalid choice.\n");
        }

    }while(choice != 0);

    return 0;
}
