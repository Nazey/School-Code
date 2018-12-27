#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkMark(int *counter);

int main(void) {
	int counter;
	int markLoc = checkMark(&counter);
	double totalTimeEntrance = (double)counter * 1.5;
	printf("Mark's appearance: %.1lf\n", 1.5 * (double)markLoc);
	int peopleInParty = 0;
	double timer = -1.5;
	double timeForExit = 0;
	int i;

	do {
		timer += 1.5;
		if (i < counter) {
			peopleInParty += 1;
			i++;
		}
		if (i == 49) {
			timeForExit = timer;
			timer = 0;
		}
		if (timeForExit > 0){
			if ((int)timer % 15 == 0) {
				peopleInParty -= 5;
			}
			if ((int)timer % 30 == 0) {
				peopleInParty -= 6;
			}
			if ((int)timer % 60 == 0) {
				peopleInParty -= 4;
			}
			if ((int)timer % 120 == 0) {
				peopleInParty -= 20;
			}
			if (peopleInParty < 0) {
				peopleInParty = 0;
			}
		} 
		// if (peopleInParty < 1 && i == counter) {
		// 	printf("0! %d %d\n", i, counter);
		// }

	} while (i < counter || peopleInParty > 0);
	printf("Total time: %.1lf\n",timer+timeForExit);

	return 0;
}

int checkMark(int *counter) {
	*counter = 0;
	char tempChar[40];
	char mark[19] = "Mark;Zuckerberg";
	FILE* f = fopen("ptcp.csv", "r");
	char *cp;
	int check = 0;

	while (fgets(tempChar, 40, f)) {
		if (check == 0) {
			cp = tempChar;
			while (*cp != '\n') {
				cp++;
			}
			*cp = '\0';
			if (strcmp(tempChar, mark) == 0) {
				check = (*counter);
			}
		}
		(*counter)++;
	}
	fclose(f);
	return check;
}