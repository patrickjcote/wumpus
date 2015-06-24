/** *************************************************************
FILE:		  	wmpusGmeCheckCPJ.c

FUNCTION:		wmpusGameCheck

DESCRIPTION: 	Checks the integrity of the wumpus world constructed
				by initWmpGame.

REQUIREMENTS:
R01 Perform validation checks described below and return "false"
    if any fail; otherwise return "true"

R02 Produce a "Wumpus World Check Report" that consists of

        (1) A labeled list of caves and associated tunnels:

                Cave    Tunnels
                ----    -------
                01      a b c
                .
                .
                .
                20      d e f

        (2) A label list of tunnels and the caves they connect

                Tunnel  Caves
                ------  -----
                01      a b
                .
                .
                .
                30      c d

                where a < b, c < d, etc.

R03 In the list of caves:
        (a) a, b, c, d, e, f, ... , must only have values in [01,20],
        (b) For each cave the three tunnel values must be different.
        (c) Each cave number must appear twice and only three in the list.

R04 The tunnel configuration is sound iff the pair a, b occurs only once
    in the list.

HISTORY:
Date      	Author          Description
%=======	======          ===========
04/17/15	Frank Ackerman  Initial lab stub
04/21/15	Patrick Cote	Initial Code
04/22/15	Patrick Cote	Update algorithm


VARIABLES:
int bats,
	caveChk[DUODEC + 1],
	caveNdx,
	pits,
	tempTnl,
	wumpus;

ALGORITHM:
A01	Initialize variables
A02 For each cave
A03		increment caveChk[cave->tnl] for each tunnel in cave
A04		if cave has a bat, bat++
A05		if cave has a pit, pit++
A06		if cave has a wumpus, wumpus++
A07		Exchange sort the tunnels
A08	If (bats != 2) return false
A09	If (pits != 2) return false
A10 If (wumpus != 1) return false
A11 for each value of caveChk
A12		If(caveChk[caveNdx] !=) return false
A13	return true

SAMPLE INPUT/OUTPUT

*****************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"


bool
wumpusGameCheck(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {

		int bats,
			caveChk[DUODEC + 1],
			caveNdx,
			pits,
			tempTnl,
			wumpus;

/*L01*/	for (caveNdx = 0; caveNdx < DUODEC + 1; caveNdx++){
			caveChk[caveNdx] = 0;
		}//for init caveChk

		bats = 0;
		pits = 0;
		wumpus = 0;

/*L02*/	for (caveNdx = 1; caveNdx < DUODEC + 1; caveNdx++){
/*L03*/		caveChk[wmpCavePR[caveNdx].wmpTunnlsSV[0]]++;
			caveChk[wmpCavePR[caveNdx].wmpTunnlsSV[1]]++;
			caveChk[wmpCavePR[caveNdx].wmpTunnlsSV[2]]++;
/*L04*/		if (wmpCavePR[caveNdx].wmpBatsSV){
				bats++;
			}
/*L05*/		if (wmpCavePR[caveNdx].wmpPitsSV){
				pits++;
			}
/*L06*/		if (wmpCavePR[caveNdx].wmpWmpHereSV){
				wumpus++;
			}

/*L07*/		//exchange sort the tunnels [0]<[1]<[2]
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

/*L08*/	if (bats != NUM_BATS){
			return(false);
		}//if there aren't exactly two bats

/*L09*/	if (pits != NUM_PITS){
			return(false);
		}//if there aren't exactly two pits

/*L10*/	if (wumpus != 1){
			return(false);
		}//if there isn't exactly one wumpus

/*L11*/	for (caveNdx = 1; caveNdx < DUODEC + 1; caveNdx++){
/*L12*/		if (caveChk[caveNdx] != 3){
				return(false);
			}//if there are more than three tunnels
		}//for caveChk

/*L13*/	return(true);

}//wmpusGameCheck()

//end wmpusGmeCheckCPJF.c