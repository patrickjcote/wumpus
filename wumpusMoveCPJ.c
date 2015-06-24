/** *************************************************************
FILE:		  	wokenWumpusCPJ.c

FUNCTION:		wumpusMove

DESCRIPTION: 	Determines movement of a woken Wumpus

REQUIREMENTS:
R01 
HISTORY:
Date      	Author          Description
%=======	======          ===========
04/17/15	Frank Ackerman  Initial lab stub
04/22/15	Patrick Cote	Initial Code


VARIABLES:
unsigned int	caveNdx,
				moveProbability,
				newWumpusLoc,
				randTnlNdx,
				wmpStartLoc;

ALGORITHM:
A01	Find wmpStartLoc
A02	Set moveProbability to rand [1,100]
A03	If moveProbability < 75
A04		Move to a random, adjacent cave
A05		Check if wumpus ended up in hnter cave,
A06	Else Check if wumpus and hunter in same cave
A07 return

SAMPLE INPUT/OUTPUT

*****************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"


bool
wumpusMove(struct wmpCaveST wmpCavePR[], unsigned int hntrLocPR) {

		unsigned int	caveNdx,
						moveProbability,
						newWumpusLoc,
						randTnlNdx,
						wmpStartLoc;

/*L01*/	for (caveNdx = 0; caveNdx < DUODEC + 1; caveNdx++){
			if (wmpCavePR[caveNdx].wmpWmpHereSV){
				wmpStartLoc = caveNdx;
				break;
			}//if wumpus is here
		}//for find wmpStartLoc
	
/*L02*/	moveProbability = rand() % 100 + 1;
	
/*L03*/	if (moveProbability < 75){
			randTnlNdx = rand() % 3;
/*L04*/		newWumpusLoc = wmpCavePR[wmpStartLoc].wmpTunnlsSV[randTnlNdx];
			if (newWumpusLoc == hntrLocPR){
/*L05*/			printf("The Wumpus woke up and ate you!\n");
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
/*L06*/	else if (wmpStartLoc == hntrLocPR){
			printf("The Wumpus woke up and ate you!\n");
			return(false);
		}//if 25% the wumpus doesn't move and you're in the same cave
	
/*L07*/	return(true);


}// wokenWumpus()