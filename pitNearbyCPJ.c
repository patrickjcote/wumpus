/** *************************************************************
FILE:		  	pitNearbyCPJ.c

FUNCTION:		pitNearby

DESCRIPTION: 	Lets the user know if there is a pit nearby

REQUIREMENTS:
R01 Say the hunter is in cave A which has tunnels to caves B, C
    and D. If any of these caves has a bottomless pit, return true
    otherwise return false.

HISTORY:
Date      	Author          Description
%=======	======          ===========
04/17/15	Frank Ackerman  Initial lab stub
04/21/15	Patrick Cote	Initial Code
04/22/15	Patrick Cote	Update Algorithm


VARIABLES:
unsigned int	tnlNdx,
pitChkNdx;

ALGORITHM:
A01	For(each tunnel connected)
A02		if(tunnel is connected to a pit)
A03			return true;
A04	Return False;


SAMPLE INPUT/OUTPUT

*****************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"

bool
pitNearby(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {

		unsigned int	pitChkNdx,
						tnlNdx;

/*L01*/	for (tnlNdx = 0; tnlNdx < 3; tnlNdx++){
			pitChkNdx = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[tnlNdx];
/*L02*/			if (wmpCavePR[pitChkNdx].wmpPitsSV){
/*L03*/			return(true);
			}//if that cave has a pit
		}//for each tunnel
/*L04*/	return(false);

}//pitNearby()

//end pitNearbyCPJ.c