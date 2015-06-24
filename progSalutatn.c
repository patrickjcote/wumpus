/** ------------------------------------------------------
DESCRIPTION:  progSalutatn()
Displays a program salutation.

REQUIREMENTS:
R01 If strtEndPR is 'S' (or 's') and progNamePR is "ProgramName" on stdout
progSalutatn() displays:

<blank line>
--------------------------
-Starting ProgramName-
--------------------------
<blank line>

and returns;

R02	If strtEndPR is 'E' (or 'e') and progNamePR is "ProgramName" on stdout
progSalutatn() displays:

------------------------
-Ending ProgramName-
------------------------
<blank line>

and returns;

R03	If strtEndPR is any character other than 'S' (or's' ) or 'E' (or'e') and
progNamePR is "ProgramName" on stdout
progSalutatn() displays:

-------------
-ProgramName-
-------------

and returns;

VARIABLES:
char	dashLine[MAX_SALUTATION] = { "-----------------------------------\n" };

ALGORITHM:
A01 Switch (startEndPR) {

A02		Case 'e':
		Case 'E':
			Display dashLine;
			Display "-Ending <progNamePR>-";
			Display dashline;
			Display blank line;
			Return;

A03		Case 's':
		Case 'S':
			Display blank line;
			Display "-Starting <progNamePR>-';
			Display dashline;
			Display blank line;
			Return;

A04		Default:
			Display dashLine;
			Display "-<progNamePR>-";
			Display dashline;
			Return;

    }//Switch

SAMPLE INPUT/OUTPUT
Covered by above requirements
---------------------------------------------------------*/
#include "wumpus.h"

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

//end progSalutatn.c
