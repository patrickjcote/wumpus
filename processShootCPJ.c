/** *************************************************************
FILE:		  	processShoot.c

DESCRIPTION: 	Implements all game actions involved in the hunter's
decision to shoot.
 *****************************************************/

//--------------------
//Includes
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
        tnl1 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[0];
        tnl2 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[1];
        tnl3 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[2];

        printf("Number of caves to shoot at > ");

        while (true){
                scanf(" %d", &nmbrCavesToTrvl);
                if (nmbrCavesToTrvl < 6 && nmbrCavesToTrvl > 0){
                        break;
                }//if nmbrCavesToTrvl is in valid range of [1,5]
                printf("Not a valid number of caves [1,5]> ");
        }//while valid caves check

        printf("Enter the flight path of the arrow:\n");

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

        arrowLoc = wmpHntrPR->hntrCaveSV;
        rndmFlight = false;

        for (caveNdx = 0; caveNdx < nmbrCavesToTrvl; caveNdx++){
                if (!rndmFlight){
                        if (flightPath[caveNdx] == tnl1 || flightPath[caveNdx] == tnl2 || flightPath[caveNdx] == tnl3){
                                arrowLoc = flightPath[caveNdx];
                        }//if the cave is adjacent 
                        else{
                                arrowLoc = wmpCavePR[arrowLoc].wmpTunnlsSV[rand() % 3];
                                rndmFlight = true;
                        }//else needs to travel through other tunnels
                }
                else{
                        arrowLoc = wmpCavePR[arrowLoc].wmpTunnlsSV[rand() % 3];
                        rndmFlight = true;
                }//else needs to travel through other tunnels

                //------------ Debug: Display Flight Path --------------
#if DEBUG_MODE
                printf("DEBUG: CaveNdx: %d  |  ArrowLoc: %d\n", caveNdx, arrowLoc);
#endif
                //------------------------------------------------------

                if (wmpCavePR[arrowLoc].wmpWmpHereSV){
                        printf("You hit the Wumpus!\n");
                        return(false);
                }//if arrow hits the wumpus 

                if (arrowLoc == wmpHntrPR->hntrCaveSV){
                        printf("You shot yourself!\n");
                        return(false);
                }//if arrow is in same cave as hunter

                //load tunnels for new cave
                tnl1 = wmpCavePR[arrowLoc].wmpTunnlsSV[0];
                tnl2 = wmpCavePR[arrowLoc].wmpTunnlsSV[1];
                tnl3 = wmpCavePR[arrowLoc].wmpTunnlsSV[2];

        }//for number of caves to travel

        wmpHntrPR->nmbrArrowsSV--;

        wumpusAction = wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV);

        if (wumpusAction){
                printf("You missed");

                if (wmpHntrPR->nmbrArrowsSV == 0){
                        printf("!\nAnd now you are out of arrows. Bummer.\n");
                        return(false);
                }//If no arrows remain
                else{
                        /*L15*/			printf("!\nYou have %d arrows remaining.\n\n", wmpHntrPR->nmbrArrowsSV);
                }//else display arrows remaining
        }//if wumpus didn't kill hunter

        return(wumpusAction);

}//processShootAFF()

//end processShootCPJ.c
