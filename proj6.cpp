/**

*File Name: proj6.cpp

*Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. See Academic Integrity Procedural Guidelines (Links to an external site.) at:  https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines (Links to an external site.)

*Assisted by and Assisted line numbers:


*Your Name: Cory Drangel

*Your PSU user ID:  cjd209

*Course title: CMPSC465 Summer 2022 

*Due Time: 11:59 pm, Sunday, July 17, 2022

*Time of Last Modification:  1:00 pm, Friday , July 15, 2022

*Description: takes a matrix and determines the size of the largest square of all 1's inside
the matrix that is continuous
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

void square(int n, int m, int numArray[][100]);
int count(int numArray[][100], int i, int j, string direction);

int main() {
	fstream inFile;
	string str;
	int numArray[100][100], n, m;

  //opens the file to be read
	inFile.open("input.txt");

  //if statement to ensure the file opens properly
	if (inFile) {
    //reads the first input as a string and converts to a number
		inFile >> str;
		n = stoi(str);

    //while statement for as long as the n value isn't zero
		while (n != 0) {
      //reads the next value converts to a string and assigns it to m value
			inFile >> str;
			m = stoi(str);

      //gets the input from the file and turns it into a n X m matrix
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					inFile >> str;
					numArray[i][j] = stoi(str);
				}
			}

      //runs the square function to determine the largest square in the matrix
			square(n, m, numArray);

      //gets the next n value in the file
			inFile >> str;
			n = stoi(str);
		}
	}
	else {
		cout << "Error opening file.";
	}

	inFile.close();
}

//function to determine the largest square in the array
void square(int n, int m, int numArray[][100]) {
	int square[100][100], maxSquare = 1;

  //assigns the value 1 to any value that is 1 along the first column
	for (int i = 0; i < n; i++) {
		if (numArray[i][0] == 1) {
			square[i][0] = 1;
		}
	}

  //assigns the value 1 to any value that is 1 along the first row
	for (int j = 0; j < m; j++) {
		if (numArray[0][j] == 1) {
			square[0][j] = 1;
		}
	}

  //for loop for the rest of matrix that isn't the first row or first column
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
      //if the value in the array is equal to 1
			if (numArray[i][j] == 1) {
        //if the value in the elements above, to the left, and diagonal up and to the left
        //are all equal to 1
				if (numArray[i - 1][j] == 1 && numArray[i][j - 1] == 1 && numArray[i - 1][j - 1] == 1) {
					int up, left;

          //gets the number of consecutive 1's in the row and column
					up = count(numArray, i, j, "up");
					left = count(numArray, i, j, "left");

          //calculates the value of the square using the min of up and left -1 + the value 
          //of the upper left diagonal
					square[i][j] = (min(up, left) * 2) - 1 + square[i - 1][j - 1];

          //determing if the square is the max
					if (square[i][j] > maxSquare) {
            //assigning to the max if it is greater than the current
						maxSquare = square[i][j];
					}
				}
        //at least one of the values to the left, up, and upper left diagonal is not 1
        //assigning the value to be 1 then
				else {
					square[i][j] = 1;
				}
			}
      //assigning the value of the square to be 0 otherwise
			else {
				square[i][j] = 0;
			}
		}
	}

  //printing the maxSquare
	cout << maxSquare << endl;
}

//function to determine the number of 1's in a row
int count(int numArray[][100], int i, int j, string direction) {
	int count = 0;

  //if the direction is up
	if (direction == "up") {
    //while the value in the array is not 0
		while (numArray[i][j] != 0 && i >= 0 && j >= 0) {
      //adding 1 to the count
			count++;
      //decreasing i to go up
			i--;
		}
	}
  //else if the direction is to the left
	else if (direction == "left") {
    //while the value in the array is not 0
		while (numArray[i][j] != 0 && i >= 0 && j >= 0) {
      //adding 1 to the count
			count++;
      //decreaseing j to go to the left
			j--;
		}
	}

	return count;
}
