/** *************************************************************
FILE:		  	initWumpusGameCPJ.c

FUNCTION:		initWmpusGame

DESCRIPTION: 	Establishes all starting conditions for a game of
				"Hunt The Wumpus".

REQUIREMENTS:
R01 wmpCave[0] is not used.

R02 Tunnels between caves are random.

R03 Two caves selected at random are inhabited by bats.

R04 Two caves selected at random have bottomless pits.

R05 The wumpus is in a cave selected at random.

R06 The hunter starts in an emtyp cave (selected at random).

HISTORY:
Date      	Author          Description
%=======	======          ===========
04/17/15	Frank Ackerman  Initial lab stub
04/21/15	Patrick Cote	Initial code
04/22/15	Patrick Cote	Update algorithm

VARIABLES:
unsigned int	currentCave,
				currentTnl,
				hazardNdx,
				hazardLoc,
				hnterLoc,
				nmbrTnlsTried,
				toCaveNdx,
				toCaveTnlNdx;

ALGORITHM:

A01	Initialize Caves
A02	For(each cave)
A03		for(each tunnel)
A04			While(true)
A04a			if stuck in loop goto A01
A05				if tunnel has alread been set: break
A06				set toCaveNdx randomly [1,20]
A07				if(toCaveNdx == currentCave)
					continue;
A08				if(toCaveNdx has a tunnel to currentCave)
					continue;
A09				for(each tunnel at toCaveNdx)
A10					if there is an empty tunnel set at both ends
				//for
		//for
	//for
A11	set wumpus location randomly in [1,20]
A12	Set bats, check they aren't in same room
A13	Set pits, check they are in same room
A14	Set hunterLoc, check he is in empty room
A15	Set number of arrows
A16	Return

SAMPLE INPUT/OUTPUT


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

/*L01*/	for (currentCave = 0; currentCave < DUODEC + 1; currentCave++){
			wmpCavePR[currentCave].wmpTunnlsSV[0] = 0;
			wmpCavePR[currentCave].wmpTunnlsSV[1] = 0;
			wmpCavePR[currentCave].wmpTunnlsSV[2] = 0;
			wmpCavePR[currentCave].wmpBatsSV = false;
			wmpCavePR[currentCave].wmpWmpHereSV = false;
			wmpCavePR[currentCave].wmpPitsSV = false;
		}//for init each cave

/*L02*/	for (currentCave = 1; currentCave < DUODEC + 1; currentCave++){
/*L03*/		for (currentTnl = 0; currentTnl < 3; currentTnl++){

				nmbrTnlsTried = 0;
/*L04*/			while (true){


/*L04a*/		//-------------------------- Avoiding Inf Loop Routine -------------
				//
					nmbrTnlsTried++;
					if (nmbrTnlsTried > DUODEC * 2){	//No valid tunnels left
						goto rebuildWorld;				//Rebuild whole world
					}//if nmbrTnlsTried is more than 2 times the number of caves
				//-------------------------- Avoiding Inf Loop Routine -------------


/*L05*/				if (wmpCavePR[currentCave].wmpTunnlsSV[currentTnl] != 0){
						break;
					}//if currentTnl in currentCave has already been set

/*L06*/				toCaveNdx = rand() % DUODEC + 1;

/*L07*/				if (toCaveNdx == currentCave){
						continue;
					}//if toCaveNdx is currentCave set new random cave

/*L08*/				if (wmpCavePR[toCaveNdx].wmpTunnlsSV[0] == currentCave ||
						wmpCavePR[toCaveNdx].wmpTunnlsSV[1] == currentCave ||
						wmpCavePR[toCaveNdx].wmpTunnlsSV[2] == currentCave){
						continue;
					}//if toCaveNdx already has a tunnel to the currentCave

					//look for an empty tunnel in wmpCavePR[toCaveNdx]
/*L09*/				for (toCaveTnlNdx = 0; toCaveTnlNdx < 3; toCaveTnlNdx++){
/*L10*/					if (wmpCavePR[toCaveNdx].wmpTunnlsSV[toCaveTnlNdx] == 0){
							wmpCavePR[toCaveNdx].wmpTunnlsSV[toCaveTnlNdx] = currentCave;
							wmpCavePR[currentCave].wmpTunnlsSV[currentTnl] = toCaveNdx;
							break;
						}//if toCaveNdx tunnel at toCaveTnlNdx is empty, set both ends of tunnel
					}//for each tunnel in toCaveNdx
				}//while currentTnl hasn't been set
			}//for each tunnel of currentCave
		}//for each cave

/*L11*/	wmpCavePR[rand() % DUODEC + 1].wmpWmpHereSV = true;

/*L12*/	for (hazardNdx = 0; hazardNdx < NUM_BATS; hazardNdx++){
			while (true){
				hazardLoc = rand() % DUODEC + 1;
				if(!wmpCavePR[hazardLoc].wmpBatsSV){
					wmpCavePR[hazardLoc].wmpBatsSV = true;
					break;
				}//if a bat is not at hazardLoc
			}//while setting current bat
		}//for total number of bats

/*L13*/	for (hazardNdx = 0; hazardNdx < NUM_PITS; hazardNdx++){
			while (true){
				hazardLoc = rand() % DUODEC + 1;
				if (!wmpCavePR[hazardLoc].wmpPitsSV){
					wmpCavePR[hazardLoc].wmpPitsSV = true;
					break;
				}//if Pit is not at hazardLoc
			}//while set current Pit
		}//for total number of Pits

/*L14*/	while (true){

			hnterLoc = rand() % DUODEC + 1;

			if (!wmpCavePR[hnterLoc].wmpPitsSV && 
				!wmpCavePR[hnterLoc].wmpBatsSV &&
				!wmpCavePR[hnterLoc].wmpWmpHereSV){
				wmpHntrPR->hntrCaveSV = hnterLoc;
				break;
			}//if no pits, bats or wumpus set hntrCave to hnterLoc
		}//while setting hnter cave

/*L15*/	wmpHntrPR->nmbrArrowsSV = NUM_ARROWS;

/*L16*/	return;

}//initWmpusGame()



//end initWmpusGameCPJ.c
