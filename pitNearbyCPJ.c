/** *************************************************************
FILE:		  	pitNearbyCPJ.c

FUNCTION:		pitNearby

DESCRIPTION: 	Lets the user know if there is a pit nearby

 *****************************************************/

//--------------------
//Includes
//--------------------
#include "wumpus.h"

bool
pitNearby(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {

        unsigned int	pitChkNdx,
                        tnlNdx;

        for (tnlNdx = 0; tnlNdx < 3; tnlNdx++){
                pitChkNdx = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[tnlNdx];
                if (wmpCavePR[pitChkNdx].wmpPitsSV){
                        return(true);
                }//if that cave has a pit
        }//for each tunnel
        return(false);

}//pitNearby()

//end pitNearbyCPJ.c
