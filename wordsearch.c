#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Own personal using C++ structures
// #include <LinkedList.h>
#include "HashTable.c"
////////////////////////////////////

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

int compareString(char* stringOne, char* stringTwo);

void horizontalLeftSweep(char** arr, char** list , char* currentLine, int row,int listSize);
// int horizontalLeftSweep(char** list, char* target, int size);
// int verticalUpSweep(char** list, char* target, int size);
void verticalDownSweep(char** arr, char** list, int row, int col, int listSize);



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
	int i;
	
	int j;

	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%c ", *(*(arr + i) + j));
		}
		printf("\n");
	}


}

void searchPuzzle(char** arr, int n, char** list, int listSize) {
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
	long i;
	long j;
	long k;
	long o;

	char **listOfWordsFound = (char **)malloc(listSize * sizeof(char)); 
	// printf("List size: %d\n", listSize);
	for(o = 0; o < n; o++){
		for(i = 0; i < n; i++){
			// char* temp = (char *)malloc ((n-i) * sizeof(char));
			char* temp;
			temp = (*(arr + o) + i);
			// printf("Result of temp with lengh(%ld): %s\n", strlen(temp),temp);
			char *tempTwo;
			horizontalLeftSweep(arr, list, temp,o,listSize);
			verticalDownSweep(arr, list, o, i, listSize);
			

		}
	}
	// verticalDownSweep(arr, list, 0, 0, listSize);



}


int compareString(char* stringOne, char* stringTwo){
    // printf("String One of length(%ld): %s\n", strlen(stringOne),stringOne);
    // printf("String Two of length(%ld): %s\n", strlen(stringTwo),stringTwo);

	
	int equalToEachOther = 1;			// true = 1; false = 0;
    if(strlen(stringOne) == strlen(stringTwo)){
        for(int i = 0; i <= strlen(stringTwo); i++){
			char a = *(stringOne + i);
			char b = *(stringTwo + i);
			if(a >= 'a' && a <= 'z'){				//checks if the current char for stringOne is lowercase
				a = a+ ('A'-'a');				// 'A' = 65; 'Z' = 90;, 'a' = '97';
			}
			if(b >= 'a' && b <= 'z'){				//checks if the current char for stringTwo is lowercase
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
	char *tempTwo;
	for(j = 0; j < strlen(currentLine); j++){
		// char *tempTwo;
		long size = strlen(currentLine) - j;
		tempTwo = (char*)malloc(size * sizeof(char));
		// tempTwo = (char*)malloc((size-1) * sizeof(char));


		for(k = 0; k < size; k++){
			*(tempTwo + k) = *(currentLine + k);
		}
		*(tempTwo + k) = '\0';
		// printf("String of second temp: %s\n", (tempTwo));
			
		int p;
		for(p = 0; p < listSize; p++){
			if(compareString(tempTwo,*(list + p))){
				printf("Word found: %s\n", tempTwo);
			}
		}
				
		// printf("Size of second temp: %ld\n", strlen(tempTwo));

	}

}

void verticalDownSweep(char** arr, char** list, int row, int col, int listSize){

	
	char* temp;
	long n = strlen(*(arr + 0));
	// printf("Dimension: %ldx%ld\n", n,n);
	long j;
	long k;
	// printf("(Row, Col): (%d, %d)\n", row, col);

	for(j = row; j < n; j++){
		long size = n - j;
		temp = (char *)malloc(size * sizeof(char));
		// printf("Size vertically: %ld\n", size);
		for(k = row; k < size; k++){
			*(temp + k) = *(*(arr + k) + col);
		}
		*(temp + k) = '\0';
		// printf("Vertical string of (%ld, %d): %s\n", j, col, temp);

		int p;
		for(p = 0; p < listSize; p++){
			if(compareString(temp,*(list + p))){
				printf("Word found: %s\n", temp);
			}
		}

	}

	// for(j = row;)



}
