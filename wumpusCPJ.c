/** *************************************************************
FILE:		  	wumpusCPJ.c

FUNCTION:       main

DESCRIPTION: 	A slightly personalized version of the old classic
keyboard single player game, "Hunt The Wumpus"

 *****************************************************/
//--------------------
//Includes
//--------------------
#include "wumpus.h"


int main(void) {

        char                mORs, 
                            yesNo;

        struct wmpCaveST    wmpCave[DUODEC + 1];
        struct wmpHntrST    wmpHntr;


        system("clear");

        progSalutatn('S', "Hunt The Wumpus (CPJ)");

        srand((unsigned) time(NULL));
#if DEBUG_MODE
        printf("---------- DEBUG_MODE: ON ---------------\n\n");
#endif

        printf("Welcome to my lair!\n");
        printf("Would you like to play a game (y or n)? ");
        scanf(" %c", &yesNo);
        if (yesNo != 'y') {
                printf("Coward! Begone then.\n");
                goto leave;
        }//if

        while (true) { //user want to play

                printf("Would you like a game description (y or n)> ");
                scanf(" %c", &yesNo);
                if (yesNo == 'y') {
                        wumpusDescription();
                }//if user wants instructions


                initWumpusGame(wmpCave, &wmpHntr);

                if (wumpusGameCheck(wmpCave, &wmpHntr) != true) {
                        printf("initWmpusGame has not constructed a\n");
                        printf("world that meets our specifications. Aborting.");
                        goto leave;
                }//if
                printf("\nStart new game.\n");
                printf("-----------------------------------------------\n");

                while (true) { //game is in progress

                        printf("You are in cave %d\n", wmpHntr.hntrCaveSV);

                        printf("There are tunnels to caves %d %d %d\n",
                                        wmpCave[wmpHntr.hntrCaveSV].wmpTunnlsSV[0],
                                        wmpCave[wmpHntr.hntrCaveSV].wmpTunnlsSV[1],
                                        wmpCave[wmpHntr.hntrCaveSV].wmpTunnlsSV[2]);

                        if (pitNearby(wmpCave, &wmpHntr)) {
                                printf("It's drafty here!\n");
                        }//if

                        printf("move (m) or shoot (s)> ");
                        scanf(" %c", &mORs);

                        if (mORs == 'm') {
                                if (processMove(wmpCave, &wmpHntr)) {
                                        continue;
                                }//if hunter did not die

                                else {
                                        break;
                                }//else hunter killed
                        }//if move

                        //------------ Debug: printWorld() on 'p' press --------
#if DEBUG_MODE
                        else if (mORs == 'p'){ printWorld(wmpCave); continue; }	
#endif
                        //------------------------------------------------------

                        else {
                                if (processShoot(wmpCave, &wmpHntr)) {
                                        continue;
                                }//if hunter or wumpus did not die
                                else {
                                        break;
                                }//else either hunter or wumpus died
                        }//else shoot

                }//while game in progress

                printf("\n");
                printf("Would you like to play again? (y or n)> ");
                scanf(" %c", &yesNo);
                if (yesNo == 'y') {
                        continue;
                }//if user want to play again
                else {
                        break;
                }//else user does not want to play again
        }//while user wants to play
leave:			
        printf("\n");
        progSalutatn('E', "\"Hunt The Wumpus\" (CPJ)");
        double anyNmbr;
        printf("Enter any number to exit> ");
        scanf("%lf", &anyNmbr);

        system("clear");


}//main()

//end   wumpusCPJ.c
