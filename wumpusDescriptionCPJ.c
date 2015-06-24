/** *************************************************************
PROJECT:     	Wumpus

FILE:		  	wumpusDescription.c

DESCRIPTION:  	When called, displays a description of this version
				of "Hunt The Wumpus"

REQUIREMENTS:
R01	Display the instructions for playing "Hunt The Wumpus" on stdout.

HISTORY:
Date      	Author          Description
========	======          ===========
04/05/15	Frank Ackerman  A version of orignal game instructions
	
VARIABLES:
"None"

ALGORITHM:
A01	Use printf to display the instructions for playing this version of
	"Hunt The Wumpus" on stdout;
A02	Return;

CALLS:
"None"

SAMPLE RUNS:
"Not supplied"

*************************************************************************/

//--------------------
//Application includes
//--------------------
#include "wumpus.h"

void
wumpusDescription(void) {

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


/*L02*/	return;

}//wumpusDescription()

//end  wumpusDescription.c