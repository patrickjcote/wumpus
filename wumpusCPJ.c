/** *************************************************************
FILE:		  	wumpusCPJ.c

FUNCTION:       main

DESCRIPTION: 	A slightly personalized version of the old classic
				keyboard single player game, "Hunt The Wumpus"
			
REQUIREMENTS:
R01 Satisfies all requirements that can be derived from the instructions
    and/or requirements in Hunt The Wumpus functions.


HISTORY:
Date      	Author          Description
%=======	======          ===========
04/17/15	Frank Ackerman  Initial lab stub

	
VARIABLES:
char	            mORs,
                    yesNo;
struct wmpCaveST    wmpCave[DUODEC+1];
struct wmpHntrST    wmpHntr;

ALGORITHM:
A01	Call progSalutatn('S', "Hunt The Wumpus (CPJ)") to display starting salutation;
A02 Display "welcome";
A03 Obtain "yes" or "no" from user re playing game;
A04 If (not "yes") {
        Display: Coward! ...
        Terminate normally;
    }//If

A05 While (true) { //user wants to play

A06     Obtain "yes" or "no" re displaying description;
A07     If ("yes") {
            Call wumpusDescription();
        }//If

A08     Call initWumpusGame() to set up wumpus world;
A09     Display: Start ...

A10         While (true) { //while game is in progress

A11             Display starting conditions;
A12             Obtain "move" or "shoot";

A13             If("move") {
A14                 If (processMove() does not end game) {
                        Continue;
                    }//If
A15                 Else {
                        Break;
                    }// hunter killed
                }//move
A15a			Debug: printWorld() with 'p'
A16             Else {
A17                 If (processShoot() does not end game) {
                        Continue;
                    }//If hunter and wumpus are still alive
A18                 Else {
                        Break;
                    }//Else either hunter or wumpus killed
                }//Else shoot

            }//While game is in progress

A19         Obtain "yes" or "no" to playing again;
A20         If (user wants to play again) {
                Continue;
            }//If
A21         Else {
                Break;
            }//Else user does not want to play again

    }//While user wants to play

A22 Call progSalutatn('E', "Hunt The Wumpus (CPJ)") to display ending salutation;
A23 Hold VS screen for user response;

SAMPLE RUN
<team supplies>

*****************************************************/
//--------------------
//Application includes
//--------------------
#include "wumpus.h"

//----
//main
//-----
int
main(void) {

		char                mORs, 
                            yesNo;

		struct wmpCaveST    wmpCave[DUODEC + 1];
		struct wmpHntrST    wmpHntr;


        system("clear");

/*L01*/	progSalutatn('S', "Hunt The Wumpus (CPJ)");

		srand((unsigned) time(NULL));
#if DEBUG_MODE
	printf("---------- DEBUG_MODE: ON ---------------\n\n");
#endif

/*L02*/	printf("Welcome to my lair!\n");
		printf("Would you like to play a game (y or n)? ");
		scanf(" %c", &yesNo);
/*L04*/	if (yesNo != 'y') {
			printf("Coward! Begone then.\n");
			goto leave;
		}//if

/*L05*/	while (true) { //user want to play

/*L06*/		printf("Would you like a game description (y or n)> ");
			scanf(" %c", &yesNo);
/*L07*/		if (yesNo == 'y') {
				wumpusDescription();
		}//if user wants instructions
			

/*L08*/		initWumpusGame(wmpCave, &wmpHntr);

/*L08a*/	if (wumpusGameCheck(wmpCave, &wmpHntr) != true) {
				printf("initWmpusGame has not constructed a\n");
				printf("world that meets our specifications. Aborting.");
				goto leave;
			}//if
/*L09*/		printf("\nStart new game.\n");
			printf("-----------------------------------------------\n");

/*L10*/		while (true) { //game is in progress

/*L11*/		    printf("You are in cave %d\n", wmpHntr.hntrCaveSV);

                printf("There are tunnels to caves %d %d %d\n",
	            wmpCave[wmpHntr.hntrCaveSV].wmpTunnlsSV[0],
	            wmpCave[wmpHntr.hntrCaveSV].wmpTunnlsSV[1],
	            wmpCave[wmpHntr.hntrCaveSV].wmpTunnlsSV[2]);

				if (pitNearby(wmpCave, &wmpHntr)) {
					printf("It's drafty here!\n");
				}//if

/*L12*/			printf("move (m) or shoot (s)> ");
				scanf(" %c", &mORs);

/*L13*/			if (mORs == 'm') {
/*L14*/				if (processMove(wmpCave, &wmpHntr)) {
						continue;
					}//if hunter did not die

/*L15*/              else {
	                    break;
                    }//else hunter killed
				}//if move

/*L15a*/		//------------ Debug: printWorld() on 'p' press --------
				#if DEBUG_MODE
				else if (mORs == 'p'){ printWorld(wmpCave); continue; }	
				#endif
				//------------------------------------------------------

/*L16*/			else {
/*L17*/				if (processShoot(wmpCave, &wmpHntr)) {
						continue;
					}//if hunter or wumpus did not die
/*L18*/             else {
	                    break;
                    }//else either hunter or wumpus died
				}//else shoot

			}//while game in progress

/*L19*/     printf("\n");
			printf("Would you like to play again? (y or n)> ");
            scanf(" %c", &yesNo);
/*L20*/		if (yesNo == 'y') {
				continue;
			}//if user want to play again
/*L21*/     else {
	            break;
            }//else user does not want to play again
		}//while user wants to play
leave:			
/*L22*/	printf("\n");
		progSalutatn('E', "\"Hunt The Wumpus\" (CPJ)");
/*L23*/	double anyNmbr;
		printf("Enter any number to exit> ");
		scanf("%lf", &anyNmbr);

        system("clear");


}//main()

//end   wumpusCPJ.c
