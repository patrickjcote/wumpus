#include "wumpus.h"

void initWumpusGame(struct wmpCaveST wmpCavePR[], struct wmpHntrST *wmpHntrPR) {

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

        for (currentCave = 0; currentCave < DUODEC + 1; currentCave++){
                wmpCavePR[currentCave].wmpTunnlsSV[0] = 0;
                wmpCavePR[currentCave].wmpTunnlsSV[1] = 0;
                wmpCavePR[currentCave].wmpTunnlsSV[2] = 0;
                wmpCavePR[currentCave].wmpBatsSV = false;
                wmpCavePR[currentCave].wmpWmpHereSV = false;
                wmpCavePR[currentCave].wmpPitsSV = false;
        }//for init each cave

        for (currentCave = 1; currentCave < DUODEC + 1; currentCave++){
                for (currentTnl = 0; currentTnl < 3; currentTnl++){

                        nmbrTnlsTried = 0;
                        while (true){


                                //-------------------------- Avoiding Inf Loop Routine -------------
                                //
                                nmbrTnlsTried++;
                                if (nmbrTnlsTried > DUODEC * 2){	//No valid tunnels left
                                        goto rebuildWorld;				//Rebuild whole world
                                }//if nmbrTnlsTried is more than 2 times the number of caves
                                //-------------------------- Avoiding Inf Loop Routine -------------


                                if (wmpCavePR[currentCave].wmpTunnlsSV[currentTnl] != 0){
                                        break;
                                }//if currentTnl in currentCave has already been set

                                toCaveNdx = rand() % DUODEC + 1;

                                if (toCaveNdx == currentCave){
                                        continue;
                                }//if toCaveNdx is currentCave set new random cave

                                if (wmpCavePR[toCaveNdx].wmpTunnlsSV[0] == currentCave ||
                                                wmpCavePR[toCaveNdx].wmpTunnlsSV[1] == currentCave ||
                                                wmpCavePR[toCaveNdx].wmpTunnlsSV[2] == currentCave){
                                        continue;
                                }//if toCaveNdx already has a tunnel to the currentCave

                                //look for an empty tunnel in wmpCavePR[toCaveNdx]
                                for (toCaveTnlNdx = 0; toCaveTnlNdx < 3; toCaveTnlNdx++){
                                        if (wmpCavePR[toCaveNdx].wmpTunnlsSV[toCaveTnlNdx] == 0){
                                                wmpCavePR[toCaveNdx].wmpTunnlsSV[toCaveTnlNdx] = currentCave;
                                                wmpCavePR[currentCave].wmpTunnlsSV[currentTnl] = toCaveNdx;
                                                break;
                                        }//if toCaveNdx tunnel at toCaveTnlNdx is empty, set both ends of tunnel
                                }//for each tunnel in toCaveNdx
                        }//while currentTnl hasn't been set
                }//for each tunnel of currentCave
        }//for each cave

        wmpCavePR[rand() % DUODEC + 1].wmpWmpHereSV = true;

        for (hazardNdx = 0; hazardNdx < NUM_BATS; hazardNdx++){
                while (true){
                        hazardLoc = rand() % DUODEC + 1;
                        if(!wmpCavePR[hazardLoc].wmpBatsSV){
                                wmpCavePR[hazardLoc].wmpBatsSV = true;
                                break;
                        }//if a bat is not at hazardLoc
                }//while setting current bat
        }//for total number of bats

        for (hazardNdx = 0; hazardNdx < NUM_PITS; hazardNdx++){
                while (true){
                        hazardLoc = rand() % DUODEC + 1;
                        if (!wmpCavePR[hazardLoc].wmpPitsSV){
                                wmpCavePR[hazardLoc].wmpPitsSV = true;
                                break;
                        }//if Pit is not at hazardLoc
                }//while set current Pit
        }//for total number of Pits

        while (true){

                hnterLoc = rand() % DUODEC + 1;

                if (!wmpCavePR[hnterLoc].wmpPitsSV && 
                                !wmpCavePR[hnterLoc].wmpBatsSV &&
                                !wmpCavePR[hnterLoc].wmpWmpHereSV){
                        wmpHntrPR->hntrCaveSV = hnterLoc;
                        break;
                }//if no pits, bats or wumpus set hntrCave to hnterLoc
        }//while setting hnter cave

        wmpHntrPR->nmbrArrowsSV = NUM_ARROWS;

        return;

}//initWmpusGame()



void
printWorld(struct wmpCaveST wmpCavePR[]) {

        int ndx, tnl1, tnl2, tnl3, bat, wump, pit;
        printf("Cave\tTunnels\t\tB  W  P\n");
        printf("----------------------------------\n");
        for (ndx = 1; ndx < DUODEC + 1; ndx++){
                tnl1 = wmpCavePR[ndx].wmpTunnlsSV[0];
                tnl2 = wmpCavePR[ndx].wmpTunnlsSV[1];
                tnl3 = wmpCavePR[ndx].wmpTunnlsSV[2];
                bat = wmpCavePR[ndx].wmpBatsSV;
                wump = wmpCavePR[ndx].wmpWmpHereSV;
                pit = wmpCavePR[ndx].wmpPitsSV;
                printf("%02d\t%02d %02d %02d\t%d  %d  %d\n", ndx, tnl1, tnl2, tnl3, bat, wump, pit);
        }

        return;

}//printWorld()    


void wumpusDescription(void) {

        /*L01*/	printf("Description of \"Hunt The Wumpus \"\n\n");
        printf("The Wumpus lives in a labyrinth of 20 caves. \n");
        printf("Each cave has 3 tunnels that lead to other caves. \n");
        printf("(A dodecahedron is a model of the Wumpus' labyrinth.) \n");
        printf("The Wumpus occasionally ventures out of  his labyrinth \n");
        printf("and eats pets and children in a nearly village. \n");
        printf("Since you are a renowned hunter you have been commissioned \n");
        printf("to hunt and slay the Wumpus!\n\n");
        printf("Hazards!\n");
        printf("---------\n");
        printf("Two of the caves have bottomless pits in them. \n");
        printf("If you go into one of these caves you will fall into \n");
        printf("the pit and never be seen again!. But there is a clue. \n");
        printf("When you are in a cave that has a tunnel that connects \n");
        printf("to a cave with a bottomless pit you will feel a draft. \n\n");
        printf("The Wumpus shares his lair with giant bats.\n");
        printf("These bats only live in two of the caves, but if you\n");
        printf("so much as enter one of these room a giant bat will \n");
        printf("grab you and take you to some other room at random.\n");
        printf("This can possibly cost you your life!\n\n");
        printf("The WUMPUS\n");
        printf("-----------\n");
        printf("The Wumpus is not bothered by hazards. He has sucker feet \n");
        printf("that can grip the sides of the bottomless pits, and he is \n");
        printf("too big for a bat to lift. Usually he is asleep. Two things \n");
        printf("wake him up: (1) you shooting an arrow, or (2) you entering\n");
        printf("his cave. If he wakes he either moves to an adjacent cave \n");
        printf("(with probability 0.75) or stays where he is. If he ends up \n");
        printf("where you are, he eats you and the game is over.\n\n");
        printf("YOU\n");
        printf("---\n");
        printf("The game starts with you (and five magic arrows) in an empty cave \n");
        printf("(no Wumpus, bats, or pits). You have two choices: MOVE or SHOOT. \n");
        printf("You can use one of the tunnels from the cave your are in and \n");
        printf("move to an adjacent cave, OR \n");
        printf("you can shoot a magic arrow. To shoot an arrow you tell the \n");
        printf("computer which caves (up to 5) the arrow is to travel through. \n");
        printf("If a cave you listed is not a possible path for the arrow (from the \n");
        printf("arrow's current location (cave#) there is not a tunnel to the cave \n");
        printf("you listed next it selects a tunnel from its current position \n");
        printf("at random and continues to do so for as many caves as you listed. \n");
        printf("If your arrow hits the Wumpus you win and collect your handsome commission. \n");
        printf("If the arrow hits you, you die \n");
        printf("(and stay dead unless you choose to play again).\n\n");


        return;

}//wumpusDescription()


#define MAX_SALUTATION 50
void
progSalutatn(char strtEndPR, char progNamePR[]) {

	char	dashLine[MAX_SALUTATION] = { "-----------------------------------\n" };

	switch (strtEndPR) {

	case 'e':
	case 'E':
		printf("%s", dashLine);
		printf("%s%s%s\n", "-Ending ", progNamePR, "-");
		printf("%s", dashLine);
		printf("\n");
		return;

	case 's':
	case 'S':
		printf("\n");
		printf("%s", dashLine);
		printf("%s%s%s\n", "-Starting ", progNamePR, "-");
		printf("%s", dashLine);
		printf("\n");
		return;

	default:
		printf("default");
		return;
	}//switch

}//progSalutatn()

