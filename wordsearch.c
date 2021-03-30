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

int horizontalRightSweep(char** list, char* target, int size);
int horizontalLeftSweep(char** list, char* target, int size);
int verticalUpSweep(char** list, char* target, int size);
int verticalDownSweep(char** list, char* target, int size);



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

	char **listOfWordsFound = (char **)malloc(listSize * sizeof(char)); 

	for(i = 0; i < n; i++){
		// char* temp = (char *)malloc ((n-i) * sizeof(char));
		char* temp;
		temp = (*(arr + 14) + i);
		printf("Result of temp with lengh(%ld): %s\n", strlen(temp),temp);

		for(j = 0; j < strlen(temp); j++){
			char *tempTwo;
			long size = strlen(temp) - j;

			tempTwo = (char*)malloc(size * sizeof(char));
			// tempTwo = (char*)malloc((size-1) * sizeof(char));


			for(k = 0; k < size; k++){
				*(tempTwo + k) = *(temp + k);
			}
			*(tempTwo + k) = '\0';
			compareString(tempTwo,"florida");
			// for(i = 0; i < (long)(listSize); i++){
			// 	if(compareString(tempTwo,*(list + i))){
			// 		// printf("Word found: %s", tempTwo);
			// 	}
			// }
			
			printf("String of second temp: %s\n", (tempTwo));
			// printf("Size of second temp: %ld\n", strlen(tempTwo));

		}

	}



}


int compareString(char* stringOne, char* stringTwo){
    // printf("String One of length(%ld): %s\n", strlen(stringOne),stringOne);
    // printf("String Two of length(%ld): %s\n", strlen(stringTwo),stringTwo);

	
	int test = 1;
    if(strlen(stringOne) == strlen(stringTwo)){
        for(int i = 0; i <= strlen(stringTwo); i++){
			char a = *(stringOne + i);
			char b = *(stringTwo + i);
			if

            if(*(stringOne + i) != *(stringTwo + i)){
                test = 0;
                break;
            }

        }
    }else{
        test = 0;
    }

    if (test){
        printf("Complex true\n");
    }else{
        printf("Complex false\n");
    }
    return test;

}