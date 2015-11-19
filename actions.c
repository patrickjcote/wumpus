#include "wumpus.h"

bool wumpusMove(struct wmpCaveST wmpCavePR[], unsigned int hntrLocPR) {

        unsigned int	caveNdx,
                        moveProbability,
                        newWumpusLoc,
                        randTnlNdx,
                        wmpStartLoc;

        for (caveNdx = 0; caveNdx < DUODEC + 1; caveNdx++){
                if (wmpCavePR[caveNdx].wmpWmpHereSV){
                        wmpStartLoc = caveNdx;
                        break;
                }//if wumpus is here
        }//for find wmpStartLoc

        moveProbability = rand() % 100 + 1;

        if (moveProbability < 75){
                randTnlNdx = rand() % 3;
                newWumpusLoc = wmpCavePR[wmpStartLoc].wmpTunnlsSV[randTnlNdx];
                if (newWumpusLoc == hntrLocPR){
                        printf("The Wumpus woke up and ate you!\n");
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
        else if (wmpStartLoc == hntrLocPR){
                printf("The Wumpus woke up and ate you!\n");
                return(false);
        }//if 25% the wumpus doesn't move and you're in the same cave

        return(true);


}// wumpusMove()

bool processMove(struct wmpCaveST wmpCavePR[], struct wmpHntrST* wmpHntrPR) {


        unsigned int	batLoc,
                        newCaveNdx,
                        tnl1,
                        tnl2,
                        tnl3;

        tnl1 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[0];
        tnl2 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[1];
        tnl3 = wmpCavePR[wmpHntrPR->hntrCaveSV].wmpTunnlsSV[2];

        printf("You can move to caves %d %d %d\n", tnl1, tnl2, tnl3);

        printf("Enter the tunnel you want to travel through> ");

        while (true){
                scanf(" %d", &newCaveNdx);
                if (newCaveNdx == tnl1 || newCaveNdx == tnl2 || newCaveNdx == tnl3){
                        break;
                }
                printf("Not a valid tunnel [%d %d %d] > ", tnl1, tnl2, tnl3);
        }//while valid cave check

        wmpHntrPR->hntrCaveSV = newCaveNdx;

        if (!(wmpCavePR[newCaveNdx].wmpPitsSV ||
                                wmpCavePR[newCaveNdx].wmpWmpHereSV ||
                                wmpCavePR[newCaveNdx].wmpBatsSV)){
                return(true);
        }//if the cave is empty

        if (wmpCavePR[newCaveNdx].wmpPitsSV){
                printf("\nOh no! You fell in a bottomless pit...\n");
                return(false);
        }//if a bottomless pit

        if (wmpCavePR[newCaveNdx].wmpWmpHereSV){
                if (!wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV)){
                        return(false);
                }//if wumpus eats the hunter
        }//if wumpus is in the room

        if (wmpCavePR[newCaveNdx].wmpBatsSV){
                printf("Oh no! A super bat picked you up\n");
                while (true){
                        batLoc = rand() % DUODEC + 1;
                        if (batLoc == wmpHntrPR->hntrCaveSV){
                                continue;
                        }//if it's the current cave
                        if (wmpCavePR[batLoc].wmpPitsSV){
                                printf("and dropped you in a bottomless pit...\n");
                                return(false);
                        }//if bat takes you to room with pit
                        if (wmpCavePR[batLoc].wmpWmpHereSV){
                                printf("and dropped you into a new cave.\n");
                                return(wumpusMove(wmpCavePR, wmpHntrPR->hntrCaveSV));
                        }//if the wumpus was there
                        if (wmpCavePR[batLoc].wmpBatsSV){
                                printf("and dragged you to cave with another bat.\n");
                                printf("This bat picked you up\n");
                                continue;
                        }//if the new cave has a bat
                        if (!wmpCavePR[batLoc].wmpBatsSV){
                                printf("and dropped you into a new cave.\n");
                                wmpHntrPR->hntrCaveSV = batLoc;
                                return(true);
                        }//the cave is empty
                }//while the bat has you
        }//if there's a bat in the room


        return(true);

}//processMove()

bool processShoot(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {


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

bool pitNearby(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {

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

