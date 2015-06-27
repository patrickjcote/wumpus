/** *************************************************************
FILE:		  	initWumpusGameCPJ.c

FUNCTION:		initWmpusGame

DESCRIPTION: 	Establishes all starting conditions for a game of
"Hunt The Wumpus".

 *****************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"


void
initWumpusGame(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {

        unsigned int	currentCave,
                        currentTnl,
                        hazardNdx,
                        hazardLoc,
                        hnterLoc,
                        nmbrTnlsTried,
                        toCaveNdx,
                        toCaveTnlNdx;

        printf("Building the Wumpus' world...\n");

rebuildWorld:

        for (currentCave = 0; currentCave < DUODEC + 1; currentCave++){
                wmpCavePR[currentCave].wmpTunnlsSV[0] = 0;
                wmpCavePR[currentCave].wmpTunnlsSV[1] = 0;
                wmpCavePR[currentCave].wmpTunnlsSV[2] = 0;
                wmpCavePR[currentCave].wmpBatsSV = false;
                wmpCavePR[currentCave].wmpWmpHereSV = false;
                wmpCavePR[currentCave].wmpPitsSV = false;
        }//for init each cave

        for (currentCave = 1; currentCave < DUODEC + 1; currentCave++){
                for (currentTnl = 0; currentTnl < 3; currentTnl++){

                        nmbrTnlsTried = 0;
                        while (true){


                                //-------------------------- Avoiding Inf Loop Routine -------------
                                //
                                nmbrTnlsTried++;
                                if (nmbrTnlsTried > DUODEC * 2){	//No valid tunnels left
                                        goto rebuildWorld;				//Rebuild whole world
                                }//if nmbrTnlsTried is more than 2 times the number of caves
                                //-------------------------- Avoiding Inf Loop Routine -------------


                                if (wmpCavePR[currentCave].wmpTunnlsSV[currentTnl] != 0){
                                        break;
                                }//if currentTnl in currentCave has already been set

                                toCaveNdx = rand() % DUODEC + 1;

                                if (toCaveNdx == currentCave){
                                        continue;
                                }//if toCaveNdx is currentCave set new random cave

                                if (wmpCavePR[toCaveNdx].wmpTunnlsSV[0] == currentCave ||
                                                wmpCavePR[toCaveNdx].wmpTunnlsSV[1] == currentCave ||
                                                wmpCavePR[toCaveNdx].wmpTunnlsSV[2] == currentCave){
                                        continue;
                                }//if toCaveNdx already has a tunnel to the currentCave

                                //look for an empty tunnel in wmpCavePR[toCaveNdx]
                                for (toCaveTnlNdx = 0; toCaveTnlNdx < 3; toCaveTnlNdx++){
                                        if (wmpCavePR[toCaveNdx].wmpTunnlsSV[toCaveTnlNdx] == 0){
                                                wmpCavePR[toCaveNdx].wmpTunnlsSV[toCaveTnlNdx] = currentCave;
                                                wmpCavePR[currentCave].wmpTunnlsSV[currentTnl] = toCaveNdx;
                                                break;
                                        }//if toCaveNdx tunnel at toCaveTnlNdx is empty, set both ends of tunnel
                                }//for each tunnel in toCaveNdx
                        }//while currentTnl hasn't been set
                }//for each tunnel of currentCave
        }//for each cave

        wmpCavePR[rand() % DUODEC + 1].wmpWmpHereSV = true;

        for (hazardNdx = 0; hazardNdx < NUM_BATS; hazardNdx++){
                while (true){
                        hazardLoc = rand() % DUODEC + 1;
                        if(!wmpCavePR[hazardLoc].wmpBatsSV){
                                wmpCavePR[hazardLoc].wmpBatsSV = true;
                                break;
                        }//if a bat is not at hazardLoc
                }//while setting current bat
        }//for total number of bats

        for (hazardNdx = 0; hazardNdx < NUM_PITS; hazardNdx++){
                while (true){
                        hazardLoc = rand() % DUODEC + 1;
                        if (!wmpCavePR[hazardLoc].wmpPitsSV){
                                wmpCavePR[hazardLoc].wmpPitsSV = true;
                                break;
                        }//if Pit is not at hazardLoc
                }//while set current Pit
        }//for total number of Pits

        while (true){

                hnterLoc = rand() % DUODEC + 1;

                if (!wmpCavePR[hnterLoc].wmpPitsSV && 
                                !wmpCavePR[hnterLoc].wmpBatsSV &&
                                !wmpCavePR[hnterLoc].wmpWmpHereSV){
                        wmpHntrPR->hntrCaveSV = hnterLoc;
                        break;
                }//if no pits, bats or wumpus set hntrCave to hnterLoc
        }//while setting hnter cave

        wmpHntrPR->nmbrArrowsSV = NUM_ARROWS;

        return;

}//initWmpusGame()



//end initWmpusGameCPJ.c
