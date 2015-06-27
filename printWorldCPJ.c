/** *************************************************************
FILE:		  	printWorldCPJ.c

FUNCTION:		printWorldCPJ

DESCRIPTION: 	Prints the World

 *****************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"


void
printWorld(struct wmpCaveST wmpCavePR[]) {

        int ndx, tnl1, tnl2, tnl3, bat, wump, pit;
        printf("Cave\tTunnels\t\tB  W  P\n");
        printf("----------------------------------\n");
        for (ndx = 1; ndx < DUODEC + 1; ndx++){
                tnl1 = wmpCavePR[ndx].wmpTunnlsSV[0];
                tnl2 = wmpCavePR[ndx].wmpTunnlsSV[1];
                tnl3 = wmpCavePR[ndx].wmpTunnlsSV[2];
                bat = wmpCavePR[ndx].wmpBatsSV;
                wump = wmpCavePR[ndx].wmpWmpHereSV;
                pit = wmpCavePR[ndx].wmpPitsSV;
                printf("%02d\t%02d %02d %02d\t%d  %d  %d\n", ndx, tnl1, tnl2, tnl3, bat, wump, pit);
        }

        return;

}//wmpusGameCheck()

//end wmpusGmeCheckCPJF.c
