#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	_Bool hasRobot; // 1 (true) a robot is here; 0 (false) the space is clear
	int robHeading; // 0 (west), 1 (north), 2 (east), 3 (south)
	_Bool robAlive; // 1 (true) for running robot; (false) when crashed
} gridSquare;

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);

	// The 10 by 10 grid
	gridSquare grid[10][10];

	// initialize the grid using a nested loop so there are no robots
	for(int i=0; i<10; i++ ){
		for(int j=0; j<10; j++){
			grid[i][j].hasRobot = 0;
		}
	}


	int i;
	int row, column;

	// Add 10 robots to the grid
	for (i = 0; i < 10; i++) {

		// This makes sure that the grid space is currently empty
		do {
			row = rand() % 10;
			column = rand() % 10;
		} while (grid[row][column].hasRobot);

		// Randomly set the heading at (column,row), and make the robot alive
		grid[row][column].hasRobot = 1;
		grid[row][column].robHeading = rand() % 4;
		grid[row][column].robAlive	 = 1;
	}

	// Counts the number of live robots
	int liveCount = 10;

	// main loop of the game
	do {

		// Output the grid
		for(int i=0; i<10; i++ ){
			for(int j=0; j<10; j++){
				if(!grid[i][j].hasRobot)
					printf(".");
				else if(grid[i][j].hasRobot && grid[i][j].robAlive)
					printf("R");
				else
					printf("@");

			}
			printf("\n");
		}

		char cmd;

		// Obtain user input (move or rotate command)
		printf("\n alive robots: %i", liveCount);
		printf("\n input action and coordinates, please: ");
		scanf(" %c %i %i", &cmd, &row, &column);

		// Process user command
		if (grid[row][column].hasRobot && grid[row][column].robAlive) {

			if (cmd == 'L') {

				// Update the heading to the left
				grid[row][column].robHeading = (grid[row][column].robHeading + 4 - 1) % 4;

			} else if (cmd == 'R') {

				// Update the heading to the right
				grid[row][column].robHeading = (grid[row][column].robHeading + 4 + 1) % 4;

			} else if (cmd == 'F') {

				// This attempts to move the robot forward, depending on the
				// direction it is currently pointing
				switch (grid[row][column].robHeading) {

					case 0: // Pointing west
						if (column > 0) {
							// If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row][column-1].hasRobot){
								grid[row][column].robAlive = 0;
								liveCount -= 1;
								if(grid[row][column-1].robAlive){
									grid[row][column - 1].robAlive = 0;
									liveCount -= 1;
								}
							}
							else{
								grid[row][column-1].hasRobot = 1;
								grid[row][column-1].robHeading = grid[row][column].robHeading;
								grid[row][column-1].robAlive = grid[row][column].robAlive;
								grid[row][column].hasRobot = 0;
							}
						}
						break;

					case 1: // Pointing north
						if (row > 0) {
							// If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row - 1][column].hasRobot){
								grid[row][column].robAlive = 0;
								liveCount -= 1;
								if(grid[row - 1][column].robAlive){
									grid[row - 1][column].robAlive = 0;
									liveCount -= 1;
								}
							}
							else{
								grid[row - 1][column].hasRobot = 1;
								grid[row - 1][column].robHeading = grid[row][column].robHeading;
								grid[row - 1][column].robAlive = grid[row][column].robAlive;
								grid[row][column].hasRobot = 0;
							}
						}
						break;

					case 2: // Pointing east
						if (column < 9) {
							// If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row][column + 1].hasRobot){
								grid[row][column].robAlive = 0;
								liveCount -= 1;
								if(grid[row][column + 1].robAlive){
									grid[row][column + 1].robAlive = 0;
									liveCount -= 1;
								}
							}
							else{
								grid[row][column + 1].hasRobot = 1;
								grid[row][column + 1].robHeading = grid[row][column].robHeading;
								grid[row][column + 1].robAlive = grid[row][column].robAlive;
								grid[row][column].hasRobot = 0;
							}
						}
						break;

					case 3: // Pointing south
						if (row < 9) {
							// If a robot is in front of you, crash both;
							// otherwise move the robot forward
							if(grid[row + 1][column].hasRobot){
								grid[row][column].robAlive = 0;
								liveCount -= 1;

								if(grid[row + 1][column].robAlive){
									grid[row + 1][column].robAlive = 0;
									liveCount -= 1;
								}
							}
							else{
								grid[row + 1][column].hasRobot = 1;
								grid[row + 1][column].robHeading = grid[row][column].robHeading;
								grid[row + 1][column].robAlive = grid[row][column].robAlive;
								grid[row][column].hasRobot = 0;
							}
						}
						break;

					default: // Shouldn't happen
						break;
				}

			}

		}

	} while (liveCount > 0);

	for(int i=0; i<10; i++ ){
		for(int j=0; j<10; j++){
			if(!grid[i][j].hasRobot)
				printf(".");
			else if(grid[i][j].hasRobot && grid[i][j].robAlive)
				printf("R");
			else
				printf("@");

		}
		printf("\n");
	}
	printf("\n alive robots: %i", liveCount);
	printf("\n You are attaboy!!!");

	return 0;
}
