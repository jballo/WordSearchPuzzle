#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

int compareString(char* stringOne, char* stringTwo);

void horizontalLeftSweep(char** arr, char** list , char* currentLine, int row,int listSize);
void verticalDownSweep(char** arr, char** list, int row, int col, int listSize);
void diagTopLeftToBottom(char** arr, char** list, int row, int col, int listSize);


// Main function, DO NOT MODIFY (except line 52 if your output is not as expected -- see the comment there)!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");

	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i = 0; i < 50; i++) {
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i = 0; i < 49; i++) {
		*(*(words+i) + strlen(*(words+i))-2) = '\0'; // Change -2 to -1 if line 58 outputs words with the last character missing
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i = 0; i < 50; i++) {
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n) {
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here
	int row;
	int col;

	for(row = 0; row < n; row++){					//Will increment each time the start of the next array of char
		for(col = 0; col < n; col++){				// Will incremeent through every character of the string for the current row
			printf("%c ", *(*(arr + row) + col));
		}
		printf("\n");
	}


}

void searchPuzzle(char** arr, int n, char** list, int listSize) {
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
	long row;
	long col;

	char **listOfWordsFound = (char **)malloc(listSize * sizeof(char)); 
	// printf("List size: %d\n", listSize);
	for(row = 0; row < n; row++){
		for(col = 0; col < n; col++){
			char* temp;
			temp = (*(arr + row) + col);
			// printf("Result of temp with lengh(%ld): %s\n", strlen(temp),temp);
			char *tempTwo;

			//From the current (row,col) (or (x,y)) position, we can then start the search for letters in all five directions from the current place.
			horizontalLeftSweep(arr, list, temp,row,listSize);			// From (x,y) position, we look to the right
			verticalDownSweep(arr, list, row, col, listSize);			// From (x,y) position, we look down
			diagTopLeftToBottom(arr, list, row, col, listSize);			// From (x,y) position, we look diagonally from top left to bottom right
			

		}
	}



}


int compareString(char* stringOne, char* stringTwo){
	
	int equalToEachOther = 1;			// true = 1; false = 0;
    if(strlen(stringOne) == strlen(stringTwo)){
        for(int i = 0; i <= strlen(stringTwo); i++){
			char a = *(stringOne + i);					// saves our current character for string one into a temporary variable
			char b = *(stringTwo + i);					// save our current character for string two into a temporary variable
			if(a >= 'a' && a <= 'z'){					//checks if the current char for stringOne is lowercase
				a = a+ ('A'-'a');						// 'A' = 65; 'Z' = 90;, 'a' = '97';
			}
			if(b >= 'a' && b <= 'z'){					//checks if the current char for stringTwo is lowercase
				b = b+ ('A'-'a');
			}

            if(a != b){

                equalToEachOther = 0;
                break;
            }

        }
    }else{
        equalToEachOther = 0;
    }
    return equalToEachOther;

}



void horizontalLeftSweep(char** arr, char** list , char* currentLine, int row, int listSize){
	int j;
	int k;
	char *currentWord;									//This will hold the word the program creates after each loop to compare to a word in listgiven


	for(j = 0; j < strlen(currentLine); j++){			//This loop will let us know how much to decrement the string by for the next comparison
		long size = strlen(currentLine) - j;
		currentWord = (char*)malloc(size * sizeof(char));


		for(k = 0; k < size; k++){
			*(currentWord + k) = *(currentLine + k);	//Where I fill the word we created (aka currentWord)
		}
		*(currentWord + k) = '\0';							//Null character added to prevent weird output
			
		int listIndex;
		for(listIndex = 0; listIndex < listSize; listIndex++){
			if(compareString(currentWord,*(list + listIndex))){
				printf("Word found: %s\n", *(list + listIndex));
			}
		}

	}

}

void verticalDownSweep(char** arr, char** list, int row, int col, int listSize){

	
	char* currentWord;
	long n = strlen(*(arr + 0));						// Note: Dimension of 2D array of char is: n x n
	long j;
	long k;
	// printf("(Row, Col): (%d, %d)\n", row, col);

	for(j = row; j < n; j++){
		
		long size = n - j;								//calculates the size based on the size of the 2D array - vertical positon/row 
		currentWord = (char *)malloc(size * sizeof(char));

		for(k = 0; k < size; k++){
			*(currentWord + k) = *(*(arr + row + k) + col);	//Where I fill the word we created (aka currentWord)
		}
		*(currentWord + k) = '\0';						//Null character added to prevent weird output

		int listIndex;
		for(listIndex = 0; listIndex < listSize; listIndex++){
			if(compareString(currentWord,*(list + listIndex))){
				printf("Word found: %s\n", *(list + listIndex));
			}
		}
	}
}

void diagTopLeftToBottom(char** arr, char** list, int row, int col, int listSize){
	
	int rowPos = row;
	int colPos = col;

	int length = 0;

	while( rowPos != 15 && colPos != 15){		//Finds the length of the new string based on incrementing row and col until we hit the edge of the 2D array
		length++;
		rowPos++;
		colPos++;	
	}

	char* currentWord;									//Temporary string to compare to any words in the word bank
	int i;
	int k;

	for(i = length; i > 0; i--){
		currentWord = (char *)malloc(length * sizeof(char));
		for(k = 0; k < length; k++){
			*(currentWord + k) = *(*(arr + row + k) + col + k);	//Where I fill the word we created (aka currentWord)
		}
		*(currentWord +k) = '\0';						//Null character added to prevent weird output

		int listIndex;
		for(listIndex = 0; listIndex < listSize; listIndex++){					//Loops through the list of words to compare to our current word
			if(compareString(currentWord,*(list + listIndex))){
				printf("Word found: %s\n", *(list + listIndex));
			}
		}

		length--;										//Subtracts the length to make it smaller each repetition.
	}
}
