/** *************************************************************
FILE:		  	processMoveCPJ.c

FUNCTION:		processMove

DESCRIPTION: 	Perform all the operations and display any output
                associated with the hunter moving from his present
                cave location to another cave via a tunnel.

REQUIREMENTS:
R01 Begin by displaying the cave #s for which there is a connection
    tunnel.

R02 Obtain a valid cave# to move to from the user.

R03 Move the hunter to this cave# (movedToCave).

R04 If movedToCave is empty return true.

R05 If the wumpus is in movedToCave and wakes up,
    display appropiate message and return false.

R06 If movedToCave has bottomless pits display
    appropriate message and return false.

R06 If movedToCave has super bats select a random
    cave to which the hunter could be carried by a bat, batCave.

R07 If batCave is empty return true.

R08 If the wumpus is in batCave and wakes up
    display appropriate message and return false.

R09 If batCave has bottomless pits display
    appropriate message and return false.

R10 If batCave has super bats repeat above starting with R06.

HISTORY:
Date      	Author          Description
%=======	======          ===========
04/17/15	Frank Ackerman  Initial lab stub


VARIABLES:
unsigned int	batLoc,
				newCaveNdx,
				tnl1,
				tnl2,
				tnl3;

ALGORITHM:
A01	Load tunnels
A02	Display possible caves
A03	Display prompt for cave
A04	Get cave from user
A05	Move hunter to that cave
A06	If cave is empty, return true
A07	If cave has pit, display message, return false
A08	If cave has wumpus call wumpusMove()
		return result of wumpusMove()
A09	If cave has bat, display message
A10		while(true)
A11			set batLoc to random cave [1,20]
A12			if batloc is current cave, continue
A13			If batloc is pit, disp message, return false
A14			If batloc is wump, return result of wumpusMove()
A15			If batloc is a bat, disp message, continue
A16			if batloc is empty, disp message, return true
A17	Return ture

SAMPLE INPUT/OUTPUT

*****************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"

bool
processMove(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR) {
	

		unsigned int	batLoc,
						newCaveNdx,
						tnl1,
						tnl2,
						tnl3;

/*L01*/	tnl1 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[0];
		tnl2 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[1];
		tnl3 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[2];

/*L02*/	printf("You can move to caves %d %d %d\n", tnl1, tnl2, tnl3);

/*L03*/	printf("Enter the tunnel you want to travel through> ");
	
/*L04*/	while (true){
			scanf(" %d", &newCaveNdx);
			if (newCaveNdx == tnl1 || newCaveNdx == tnl2 || newCaveNdx == tnl3){
				break;
			}
			printf("Not a valid tunnel [%d %d %d] > ", tnl1, tnl2, tnl3);
		}//while valid cave check
	
/*L05*/	wmpHntrPR->hntrCaveSV = newCaveNdx;

/*L06*/	if (!(wmpCavePR[newCaveNdx].wmpPitsSV ||
			wmpCavePR[newCaveNdx].wmpWmpHereSV ||
			wmpCavePR[newCaveNdx].wmpBatsSV)){
			return(true);
		}//if the cave is empty

/*L07*/	if (wmpCavePR[newCaveNdx].wmpPitsSV){
			printf("\nOh no! You fell in a bottomless pit...\n");
			return(false);
		}//if a bottomless pit

/*L08*/	if (wmpCavePR[newCaveNdx].wmpWmpHereSV){
			if (!wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV)){
				return(false);
			}//if wumpus eats the hunter
		}//if wumpus is in the room

/*L09*/	if (wmpCavePR[newCaveNdx].wmpBatsSV){
			printf("Oh no! A super bat picked you up\n");
/*L10*/		while (true){
/*L11*/			batLoc = rand() % DUODEC + 1;
/*L12*/			if (batLoc == wmpHntrPR->hntrCaveSV){
					continue;
				}//if it's the current cave
/*L13*/			if (wmpCavePR[batLoc].wmpPitsSV){
					printf("and dropped you in a bottomless pit...\n");
					return(false);
				}//if bat takes you to room with pit
/*L15*/			if (wmpCavePR[batLoc].wmpWmpHereSV){
					printf("and dropped you into a new cave.\n");
					return(wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV));
				}//if the wumpus was there
/*L15*/			if (wmpCavePR[batLoc].wmpBatsSV){
					printf("and dragged you to cave with another bat.\n");
					printf("This bat picked you up\n");
					continue;
				}//if the new cave has a bat
/*L16*/			if (!wmpCavePR[batLoc].wmpBatsSV){
					printf("and dropped you into a new cave.\n");
					wmpHntrPR->hntrCaveSV = batLoc;
					return(true);
				}//the cave is empty
			}//while the bat has you
		}//if there's a bat in the room


/*L17*/	return(true);

}//processMoveAFF()

//end processMoveCPJ.c
