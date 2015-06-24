/** *************************************************************
FILE:		  	printWorldCPJ.c

FUNCTION:		printWorldCPJ

DESCRIPTION: 	Prints the World

HISTORY:
Date      	Author          Description
%=======	======          ===========
04/21/15	Patrick Cote	Initial code

REQUIREMENTS:
R01 Prints the layout of the world

ALGORITHM
A01 For each cave
A02		print all info
A03 return

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
/*L01*/	for (ndx = 1; ndx < DUODEC + 1; ndx++){
			tnl1 = wmpCavePR[ndx].wmpTunnlsSV[0];
			tnl2 = wmpCavePR[ndx].wmpTunnlsSV[1];
			tnl3 = wmpCavePR[ndx].wmpTunnlsSV[2];
			bat = wmpCavePR[ndx].wmpBatsSV;
			wump = wmpCavePR[ndx].wmpWmpHereSV;
			pit = wmpCavePR[ndx].wmpPitsSV;
/*L02*/		printf("%02d\t%02d %02d %02d\t%d  %d  %d\n", ndx, tnl1, tnl2, tnl3, bat, wump, pit);
		}

/*L03*/	return;

}//wmpusGameCheck()

//end wmpusGmeCheckCPJF.c