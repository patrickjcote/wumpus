/** *************************************************************
FILE:		  	wokenWumpusCPJ.c

FUNCTION:		wumpusMove

DESCRIPTION: 	Determines movement of a woken Wumpus

 *****************************************************/

//--------------------
//Includes
//--------------------
#include "wumpus.h"


bool
wumpusMove(struct wmpCaveST wmpCavePR[], unsigned int hntrLocPR) {

        unsigned int	caveNdx,
                        moveProbability,
                        newWumpusLoc,
                        randTnlNdx,
                        wmpStartLoc;

        for (caveNdx = 0; caveNdx < DUODEC + 1; caveNdx++){
                if (wmpCavePR[caveNdx].wmpWmpHereSV){
                        wmpStartLoc = caveNdx;
                        break;
                }//if wumpus is here
        }//for find wmpStartLoc

        moveProbability = rand() % 100 + 1;

        if (moveProbability < 75){
                randTnlNdx = rand() % 3;
                newWumpusLoc = wmpCavePR[wmpStartLoc].wmpTunnlsSV[randTnlNdx];
                if (newWumpusLoc == hntrLocPR){
                        printf("The Wumpus woke up and ate you!\n");
                        return(false);
                }//if the wumpus moved to a cave with you in it

                wmpCavePR[newWumpusLoc].wmpWmpHereSV = true;
                wmpCavePR[wmpStartLoc].wmpWmpHereSV = false;

                //------------ Debug: Display wumpus move --------------
#if DEBUG_MODE
                printf("DEBUG: Wumpus moved to cave: %d\n", newWumpusLoc);
#endif
                //------------------------------------------------------

                return(true);
        }//if 75% wumpus moves to an adjacent cave
        else if (wmpStartLoc == hntrLocPR){
                printf("The Wumpus woke up and ate you!\n");
                return(false);
        }//if 25% the wumpus doesn't move and you're in the same cave

        return(true);


}// wokenWumpus()
