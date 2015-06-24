/** *************************************************************
PROJECT:      	Wumpus

FILE:		  	wumpus.h

DESCRIPTION: 	The only header file for this application

*****************************************************/
//----------
//C includes
//----------
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


//---------
//C defines
//---------
#define	DEBUG_MODE 0
#define DUODEC 20
#define NUM_ARROWS 5
#define NUM_BATS 2
#define NUM_PITS 2



//----------------
//Global constants
//----------------
//<none>

//------------
//Global Types
//------------
struct wmpCaveST {
	unsigned int	wmpTunnlsSV[3];
	bool			wmpBatsSV;
	bool			wmpPitsSV;
	bool			wmpWmpHereSV;

};

struct wmpHntrST {
	unsigned int hntrCaveSV;
	unsigned int nmbrArrowsSV;
};


//----------------
//Global variables
//----------------
//<none>


//-----------
//Prototyypes
//-----------
void
initWumpusGame(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR);

bool
pitNearby(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR);

void
printWorld(struct wmpCaveST wmpCavePR[]);

bool
processMove(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR);

bool
processShoot(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR);

void
progSalutatn(char strtEndPR, char progNamePR[]);

void
wumpusDescription(void);

bool
wumpusGameCheck(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR);

bool
wumpusMove(struct wmpCaveST wmpCavePR[], unsigned int hntrLocPR);

//end   wumpus.h
