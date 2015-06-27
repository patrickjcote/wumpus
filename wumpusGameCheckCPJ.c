/** *************************************************************
FILE:		  	wmpusGmeCheckCPJ.c

FUNCTION:		wmpusGameCheck

DESCRIPTION: 	Checks the integrity of the wumpus world constructed
by initWmpGame.

 *****************************************************/

//--------------------
//Includes
//--------------------
#include "wumpus.h"


bool wumpusGameCheck(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {

        int bats,
            caveChk[DUODEC + 1],
            caveNdx,
            pits,
            tempTnl,
            wumpus;

        for (caveNdx = 0; caveNdx < DUODEC + 1; caveNdx++){
                caveChk[caveNdx] = 0;
        }//for init caveChk

        bats = 0;
        pits = 0;
        wumpus = 0;

        for (caveNdx = 1; caveNdx < DUODEC + 1; caveNdx++){
                caveChk[wmpCavePR[caveNdx].wmpTunnlsSV[0]]++;
                caveChk[wmpCavePR[caveNdx].wmpTunnlsSV[1]]++;
                caveChk[wmpCavePR[caveNdx].wmpTunnlsSV[2]]++;
                if (wmpCavePR[caveNdx].wmpBatsSV){
                        bats++;
                }
                if (wmpCavePR[caveNdx].wmpPitsSV){
                        pits++;
                }
                if (wmpCavePR[caveNdx].wmpWmpHereSV){
                        wumpus++;
                }

                //exchange sort the tunnels [0]<[1]<[2]
                for (int i = 0; i < 2; i++){
                        for (int j = i + 1; j < 3; j++){
                                if (wmpCavePR[caveNdx].wmpTunnlsSV[i] > wmpCavePR[caveNdx].wmpTunnlsSV[j]){
                                        tempTnl = wmpCavePR[caveNdx].wmpTunnlsSV[j];
                                        wmpCavePR[caveNdx].wmpTunnlsSV[j] = wmpCavePR[caveNdx].wmpTunnlsSV[i];
                                        wmpCavePR[caveNdx].wmpTunnlsSV[i] = tempTnl;
                                }//if larger, swap
                        }//for inside loop
                }//for outside loop

        }//for each cave, sum total hazards, sort tunnels

        if (bats != NUM_BATS){
                return(false);
        }//if there aren't exactly two bats

        if (pits != NUM_PITS){
                return(false);
        }//if there aren't exactly two pits

        if (wumpus != 1){
                return(false);
        }//if there isn't exactly one wumpus

        for (caveNdx = 1; caveNdx < DUODEC + 1; caveNdx++){
                if (caveChk[caveNdx] != 3){
                        return(false);
                }//if there are more than three tunnels
        }//for caveChk

        return(true);

}//wmpusGameCheck()

//end wmpusGmeCheckCPJF.c
