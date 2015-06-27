/** *************************************************************
FILE:		  	processMoveCPJ.c

FUNCTION:		processMove

DESCRIPTION: 	Perform all the operations and display any output
associated with the hunter moving from his present
cave location to another cave via a tunnel.

 *****************************************************/

//--------------------
//Includes
//--------------------
#include "wumpus.h"

bool
processMove(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR) {


        unsigned int	batLoc,
                        newCaveNdx,
                        tnl1,
                        tnl2,
                        tnl3;

        tnl1 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[0];
        tnl2 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[1];
        tnl3 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[2];

        printf("You can move to caves %d %d %d\n", tnl1, tnl2, tnl3);

        printf("Enter the tunnel you want to travel through> ");

        while (true){
                scanf(" %d", &newCaveNdx);
                if (newCaveNdx == tnl1 || newCaveNdx == tnl2 || newCaveNdx == tnl3){
                        break;
                }
                printf("Not a valid tunnel [%d %d %d] > ", tnl1, tnl2, tnl3);
        }//while valid cave check

        wmpHntrPR->hntrCaveSV = newCaveNdx;

        if (!(wmpCavePR[newCaveNdx].wmpPitsSV ||
                                wmpCavePR[newCaveNdx].wmpWmpHereSV ||
                                wmpCavePR[newCaveNdx].wmpBatsSV)){
                return(true);
        }//if the cave is empty

        if (wmpCavePR[newCaveNdx].wmpPitsSV){
                printf("\nOh no! You fell in a bottomless pit...\n");
                return(false);
        }//if a bottomless pit

        if (wmpCavePR[newCaveNdx].wmpWmpHereSV){
                if (!wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV)){
                        return(false);
                }//if wumpus eats the hunter
        }//if wumpus is in the room

        if (wmpCavePR[newCaveNdx].wmpBatsSV){
                printf("Oh no! A super bat picked you up\n");
                while (true){
                        batLoc = rand() % DUODEC + 1;
                        if (batLoc == wmpHntrPR->hntrCaveSV){
                                continue;
                        }//if it's the current cave
                        if (wmpCavePR[batLoc].wmpPitsSV){
                                printf("and dropped you in a bottomless pit...\n");
                                return(false);
                        }//if bat takes you to room with pit
                        if (wmpCavePR[batLoc].wmpWmpHereSV){
                                printf("and dropped you into a new cave.\n");
                                return(wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV));
                        }//if the wumpus was there
                        if (wmpCavePR[batLoc].wmpBatsSV){
                                printf("and dragged you to cave with another bat.\n");
                                printf("This bat picked you up\n");
                                continue;
                        }//if the new cave has a bat
                        if (!wmpCavePR[batLoc].wmpBatsSV){
                                printf("and dropped you into a new cave.\n");
                                wmpHntrPR->hntrCaveSV = batLoc;
                                return(true);
                        }//the cave is empty
                }//while the bat has you
        }//if there's a bat in the room


        return(true);

}//processMoveAFF()

//end processMoveCPJ.c
