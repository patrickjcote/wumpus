/** *************************************************************
FILE:		  	processShoot.c

DESCRIPTION: 	Implements all game actions involved in the hunter's
				decision to shoot.

REQUIREMENTS:
R01 Obtain the number of caves, arrowFlghtNum, for the arrow's flight.

R02 Obtain arrowFlightNum of legitimate cave numbers (must be in
    [1,20] from the user.

R03 Fly the arrow.

R04 If the arrow first goes through a cave inhabited by the wumpus
    display an appropiate message and return false;

R05 If the arrow does not hit the wumpus but enters the hunter's
    cave, display an appriate message and return false.

R06 If the wumpus wakes up and moves to the cave the hunter
    is in display an appropiate message and return false;

R07 If neither R04, R05, or R06 hold, return true.

HISTORY:
Date      	Author          Description
%=======	======          ===========
04/17/15	Frank Ackerman  Initial lab stub
04/21/15	Patrick Cote	Initial Code


VARIABLES:
unsigned int	arrowLoc,
				caveNdx,
				flightNdx,
				flightPath[5],
				nmbrCavesToTrvl,
				tnl1,
				tnl2,
				tnl3;

bool			rndmFlight,
				wumpusAction;

ALGORITHM:

A01	Load tunnels for the current cave
A02	Get number of caves for user
A03	Get the flightpath
A04	Set arrowLoc to hunterLoc and rndmFlight to false
A05	For (number of caves)
A06		if(rndmFlight is false)
			If(next cave is adjacent)
A07				Update arrowLoc
A08		Else set arrowLoc to random location
			set rndmFlight to true
A09		Check if arrow hit wumpus or hunter
A10			Display message, return false
A11		Load tunnels for updated arrowLoc
A12	Decrement Arrows
A13	Display "Missed!"
A14	If last arrow, display message, return false
A15	Else display remaining arrows
A16	Return result of wumpusMove()


SAMPLE INPUT/OUTPUT

*****************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"

bool
processShoot(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {


		unsigned int	arrowLoc,
						caveNdx,
						flightNdx,
						flightPath[5],
						nmbrCavesToTrvl,
						tnl1,
						tnl2,
						tnl3;

		bool			rndmFlight,
						wumpusAction;
	
		//load tunnels for current cave
/*L01*/	tnl1 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[0];
		tnl2 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[1];
		tnl3 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[2];

		printf("Number of caves to shoot at > ");

/*L02*/	while (true){
			scanf(" %d", &nmbrCavesToTrvl);
			if (nmbrCavesToTrvl < 6 && nmbrCavesToTrvl > 0){
				break;
			}//if nmbrCavesToTrvl is in valid range of [1,5]
			printf("Not a valid number of caves [1,5]> ");
		}//while valid caves check

/*L03*/	printf("Enter the flight path of the arrow:\n");

		for (flightNdx = 0; flightNdx < nmbrCavesToTrvl; flightNdx++){
			printf("Cave #%d > ", flightNdx+1);
			while (true){
				scanf(" %d", &flightPath[flightNdx]);
				if (flightPath[flightNdx] < DUODEC+1 && flightPath[flightNdx] > 0){
					break;
				}//cave is a valid cave from [1,20]
				printf("Not a valid cave [1,%d]> ", DUODEC);
			}//while is valid cave check
		}//for each nmbrCavesToTrvl

		printf("\n");

/*L04*/	arrowLoc = wmpHntrPR->hntrCaveSV;
		rndmFlight = false;

/*L05*/	for (caveNdx = 0; caveNdx < nmbrCavesToTrvl; caveNdx++){
/*L06*/		if (!rndmFlight){
				if (flightPath[caveNdx] == tnl1 || flightPath[caveNdx] == tnl2 || flightPath[caveNdx] == tnl3){
/*L07*/				arrowLoc = flightPath[caveNdx];
				}//if the cave is adjacent 
				else{
					arrowLoc = wmpCavePR[arrowLoc].wmpTunnlsSV[rand() % 3];
					rndmFlight = true;
				}//else needs to travel through other tunnels
			}
/*L08*/		else{
				arrowLoc = wmpCavePR[arrowLoc].wmpTunnlsSV[rand() % 3];
				rndmFlight = true;
			}//else needs to travel through other tunnels

			//------------ Debug: Display Flight Path --------------
			#if DEBUG_MODE
			printf("DEBUG: CaveNdx: %d  |  ArrowLoc: %d\n", caveNdx, arrowLoc);
			#endif
			//------------------------------------------------------

/*L09*/		if (wmpCavePR[arrowLoc].wmpWmpHereSV){
/*L10*/			printf("You hit the Wumpus!\n");
				return(false);
			}//if arrow hits the wumpus 

/*L09*/		if (arrowLoc == wmpHntrPR->hntrCaveSV){
/*L10*/			printf("You shot yourself!\n");
				return(false);
			}//if arrow is in same cave as hunter

			//load tunnels for new cave
/*L11*/		tnl1 = wmpCavePR[arrowLoc].wmpTunnlsSV[0];
			tnl2 = wmpCavePR[arrowLoc].wmpTunnlsSV[1];
			tnl3 = wmpCavePR[arrowLoc].wmpTunnlsSV[2];

		}//for number of caves to travel

/*L12*/	wmpHntrPR->nmbrArrowsSV--;
		
		wumpusAction = wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV);
		
		if (wumpusAction){
/*L13*/		printf("You missed");

/*L14*/		if (wmpHntrPR->nmbrArrowsSV == 0){
				printf("!\nAnd now you are out of arrows. Bummer.\n");
				return(false);
			}//If no arrows remain
			else{
				/*L15*/			printf("!\nYou have %d arrows remaining.\n\n", wmpHntrPR->nmbrArrowsSV);
			}//else display arrows remaining
		}//if wumpus didn't kill hunter

/*L16*/	return(wumpusAction);

}//processShootAFF()

//end processShootCPJ.c
