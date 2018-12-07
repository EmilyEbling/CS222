
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Student.h"
#include "tree.c"

//prototypes 
void help();
void load(char* fileName, Student* houses[5]);
void save(char* fileName, Student* houses[5]);
void clear();
void printStudent(Student* root);
void fPrintStudent(Student* root, FILE* file);
int getHouse(char* house);
void inorder(Student* root);
void preorder(Student* root);
void savePreorder(Student* root, FILE* file);
void postorder(Student* root);
void add(Student* root, char *first, char* last, int points, int year, char* house, Student* houses[5]);
Student* kill(Student* root, char* first, char* last, Student* houses[5]);
Student* find(Student* root, char* first, char* last);
void addPoints(Student* root, int number);
int score(Student* root);

int main() {

	char command[10];
	char fileName[100];

	char first[100];
	char last[100];
	int points;
	int year;
	char house[100];

	int number;
	int i;

	Student* houses[5] = {NULL, NULL, NULL, NULL, NULL}; //array holding the four houses & deceased list

	while (strcmp(command, "quit") != 0) { //while the user entered command does not equal quit
		printf("Enter command: ");
		scanf("%s", command); //read in the command

		if (strcmp(command, "help") == 0) //display the help menu
			help();

		else if (strcmp(command, "load") == 0) { //load the roster
			scanf("%s", fileName);
			load(fileName, houses);
		}

		else if (strcmp(command, "save") == 0) { //save roster to a file
			scanf("%s", fileName);
			save(fileName, houses);
		}

		else if (strcmp(command, "clear") == 0) { //clears roster for all houses 
			int i;			
			for (i = 0; i < 5; i++)
				clear(houses[i]);
			printf("All data cleared.\n");
		}

		else if (strcmp(command, "inorder") == 0) { //prints inorder traversal for all houses
			printf("Inorder print-out of roster:\n\n");		
			printf("Gryffindor House\n\n");			
			inorder(houses[0]);
			printf("\n");
			printf("Ravenclaw House\n\n");
			inorder(houses[1]);
			printf("\n");
			printf("Hufflepuff House\n\n");			
			inorder(houses[2]);
			printf("\n");
			printf("Slytherin House\n\n");			
			inorder(houses[3]);
			printf("\n");
			printf("Deceased\n\n");
			inorder(houses[4]);
			printf("\n");		
		}

		else if (strcmp(command, "preorder") == 0) { //prints preorder traversal for all houses
			printf("Preorder print-out of roster:\n\n");
			printf("Gryffindor House\n\n");			
			preorder(houses[0]);
			printf("\n");
			printf("Ravenclaw House\n\n");
			preorder(houses[1]);
			printf("\n");
			printf("Hufflepuff House\n\n");			
			preorder(houses[2]);
			printf("\n");
			printf("Slytherin House\n\n");			
			preorder(houses[3]);
			printf("\n");
			printf("Deceased\n\n");
			preorder(houses[4]);
			printf("\n");
		}

		else if (strcmp(command, "postorder") == 0) { //print postorder traversal for all houses
			printf("Postorder print-out of roster:\n\n");
			printf("Gryffindor House\n\n");			
			postorder(houses[0]);
			printf("\n");
			printf("Ravenclaw House\n\n");
			postorder(houses[1]);
			printf("\n");
			printf("Hufflepuff House\n\n");			
			postorder(houses[2]);
			printf("\n");
			printf("Slytherin House\n\n");			
			postorder(houses[3]);
			printf("\n");
			printf("Deceased\n\n");
			postorder(houses[4]);
			printf("\n");
		}

		else if (strcmp(command, "add") == 0) { //adds a student to roster
			scanf("%s", first);
			scanf("%s", last);
			scanf("%d", &points);
			scanf("%d", &year);
			scanf("%s", house);
			
			if (strcmp(house, "Gryffindor") != 0 && strcmp(house, "Ravenclaw") != 0 && strcmp(house, "Hufflepuff") != 0 && strcmp(house, "Slytherin") != 0) //if user enters invalid house
				printf("Add failed. Invalid house: %s\n", house);
			
			else { 
				Student* student = malloc(sizeof(Student));
			
				if ((student = find(houses[getHouse(house)], first, last)) == NULL) //if the student doesn't already exist in the tree add him/her
					add(student, first, last, points, year, house, houses);
			
				else
					printf("Add failed. Student %s %s already present in roster.\n", first, last); //otherwise print error message	
			}
		}

		else if (strcmp(command, "kill") == 0) { //kills a student R.I.P.
			scanf("%s", first);
			scanf("%s", last);
			scanf("%s", house);

			if (strcmp(house, "Gryffindor") != 0 && strcmp(house, "Ravenclaw") != 0 && strcmp(house, "Hufflepuff") != 0 && strcmp(house, "Slytherin") != 0) //if user enters invalid house
				printf("Kill failed. Invalid house: %s\n", house);
			
			else {
				Student* student;

				if ((student = find(houses[getHouse(house)], first, last)) != NULL) { //if the student exists then kill him/her
					student = kill(student, first, last, houses);
					printf("Moved %s %s to list of deceased students.\n", first, last);
					insert(&houses[4], student); //move student to deceased tree
				}
				else
					printf("Kill failed. %s %s was not found in %s House.\n", first, last, house); //otherwise print error message
			}
			
		}

		else if (strcmp(command, "find") == 0) { //finds student in tree
			scanf("%s", first);
			scanf("%s", last);
			scanf("%s", house);
			
			if (strcmp(house, "Gryffindor") != 0 && strcmp(house, "Ravenclaw") != 0 && strcmp(house, "Hufflepuff") != 0 && strcmp(house, "Slytherin") != 0) //if user enters invalid house
				printf("Find failed. Invalid house: %s\n", house);

			else {
				Student* student;
			
				if ((student = find(houses[getHouse(house)], first, last)) != NULL) //if student is found print the student's information
					printStudent(student);
				else
					printf("Find failed. %s %s was not found in the %s House.\n", first, last, house); //otherwise print error message
			}
		}

		else if (strcmp(command, "points") == 0) { //adds x amount of points to student
			scanf("%s", first);
			scanf("%s", last);
			scanf("%s", house);
			scanf("%d", &number);
			
			if (strcmp(house, "Gryffindor") != 0 && strcmp(house, "Ravenclaw") != 0 && strcmp(house, "Hufflepuff") != 0 && strcmp(house, "Slytherin") != 0) //if user enters invalid house
				printf("Points change failed. Invalid house: %s\n", house);
			
			else {
				Student* student;
			
				if ((student = find(houses[getHouse(house)], first, last)) != NULL) { //if the student is found update his/her points
					addPoints(student, number);
					printf("Points for %s %s changed to %d\n", first, last, number);
				}
				else
					printf("Point changed failed. %s %s was not found in house %s\n", first, last, house); //otherwise print error message
			}    
		}

		else if (strcmp(command, "score") == 0) { //print total score for all houses
			int i;
	
			printf("Point totals:\n\n");

			printf("Gryffindor House:\t%d\n", score(houses[0]));
			printf("Ravenclaw House:\t%d\n", score(houses[1]));
			printf("Hufflepuff House:\t%d\n", score(houses[2]));
			printf("Slytherin House:\t%d\n", score(houses[3]));

		}

		else
			if (strcmp(command, "quit") != 0) //invalid command error 
				printf("Unknown command: %s\n", command);		
	} 
	
	for (i = 0; i < 5; i++) //clear all memory
		clear(houses[i]);
	
	printf("All data cleared\n");

	return 0;
}

void help() { //prints help menu

	printf("help\nPrints this display\n\n");

	printf("load <filename>\nAdds the contents of a file to the current roster\n\n");

	printf("save <filename>\nSaves the current roster to a file\n\n");
	
	printf("clear\nClear the current roster\n\n");
	
	printf("inorder\nPrint out an inorder traversal of the roster for each house\n\n");

	printf("preorder\nPrint out a preorder traversal of the roster for each house\n\n");

	printf("postorder\nPrint out a postorder traversal of the roster for each house\n\n");
	
	printf("add <firstname> <lastname> <points> <year> <house>\nAdds a student to the roster\n\n");

	printf("kill <firstname> <lastname> <house>\nMoves a student to the deceased list\n\n");

	printf("find <firstname> <lastname> <house> <points>\nSearches for a student in a house\n\n");

	printf("points <firstname> <lastname> <house> <points>\nChanges the points a student has earned by the specified amount\n\n");

	printf("score\nLists the point totals for all four houses\n\n");

	printf("quit\nQuits the program\n\n");

}

void load(char* fileName, Student* houses[5]) { //function that loads roster

	FILE* file = fopen(fileName, "r"); 

	if (file == NULL) //if file is invalid
		printf("Load failed. Invalid file: <%s>\n", fileName);

	else {
		printf("Successfully loaded data from file %s\n", fileName);

		char firstName[100];
		char lastName[100];
		int points;
		int year;
		char house[100];

		while (fscanf(file, "%s", firstName) == 1) { //read in all student data
			fscanf(file, "%s", lastName);
			fscanf(file, "%d", &points);
			fscanf(file, "%d", &year);
			fscanf(file, "%s", house);

			Student* student = malloc(sizeof(Student)); //create a new student 		

			student->first = strdup(firstName);
			student->last = strdup(lastName);
			student->points = points;
			student->year = year;
			student->house = getHouse(house);

			insert(&houses[student->house], student); //insert student to BST

		}

		fclose(file); //close the file
	}

}

int getHouse(char* house) { //returns the number equivalent to the house's string 
   
	int i;

    for (i = 0; i < 5; i++)
        if (strcmp(house, HOUSE_NAMES[i]) == 0)
            return i;
        
    return -1;

}

void save(char* fileName, Student* houses[5]) { //saves roster to a new file
	
	FILE* file = fopen(fileName, "w");

	if (file == NULL) { //if file is invalid 
		printf("Save failed: Invalid file: <%s>\n", fileName);
		return;
	}

	else {

		printf("Successfully saved data to file <%s>\n", fileName); 		

		int i;
	
		for (i = 0; i < 5; i++) //write all student info to file
			savePreorder(houses[i], file);

		fclose(file); //close the file

	}

}

void clear(Student* root) { //clears the entire BST

	if (root != NULL) {
		clear(root->left);
		clear(root->right);
		free(root);
	}
}

void printStudent(Student* root) { //print student information all nicely

	char* temp = strdup(root->first); //combines first and last name
	temp = strcat(temp, " ");
	temp = strcat(temp, root->last);
	printf("%-25s", temp);

	printf("\tPoints: %d", root->points);
	printf("\tYear: %d ", root->year);

	if (root->house == 0)
		printf("House: Gryffindor");
	
	if (root->house == 1)
		printf("House: Ravenclaw");

	if (root->house == 2)
		printf("House: Hufflepuff");

	if (root->house == 3)
		printf("House: Slytherin");
	printf("\n");

}

void fPrintStudent(Student* root, FILE* file) { //used to print student data to a file instead of stdout

	char* temp = strdup(root->first); //combines first and last name 
	temp = strcat(temp, " ");
	temp = strcat(temp, root->last);
	fprintf(file, "%s ", temp);
 
	fprintf(file, "%d ", root->points);
	fprintf(file, "%d ", root->year);

	if (root->house == 0)
		fprintf(file, "Gryffindor");
	
	if (root->house == 1)
		fprintf(file, "Ravenclaw");

	if (root->house == 2)
		fprintf(file, "Hufflepuff");

	if (root->house == 3)
		fprintf(file, "Slytherin");
	fprintf(file, "\n");

}

void inorder(Student* root) { //inorder traversal

	if (root != NULL) {
		inorder(root->left);
		printStudent(root);
		inorder(root->right);
	}
	
}

void preorder(Student* root) { //preorder traversal

	if (root != NULL) {
		printStudent(root);
		preorder(root->left);
		preorder(root->right);
	}

}

void savePreorder(Student* root, FILE* file) { //preorder traversal for saving to a file

	if (root != NULL) {
		fPrintStudent(root, file);
		savePreorder(root->left, file);
		savePreorder(root->right, file);
	}

}

void postorder(Student* root) { //postorder traversal

	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printStudent(root);	
	}

}

void add(Student* root, char* first, char* last, int points, int year, char* house, Student* houses[5]) { //add student to roster
	
	if (year < 1 || year > 7) { //invalid year
		printf("Add failed. Invalid year: %d\n", year);
		return;
	}
		
	else {
		if (root == NULL) { //create new student
			root = malloc(sizeof(Student));
			root->first = strdup(first);
			root->last = strdup(last);
			root->points = points;
			root->year = year;
			root->house = getHouse(house);
			root->left = NULL;
			root->right = NULL;
		}

		insert(&houses[root->house], root); //add student to BST
		
		printf("Added %s %s to roster\n", first, last);
	}
}


Student* kill(Student* root, char* first, char* last, Student* houses[5]) { //kill a student/remove a student from the roster
	
	if (root == NULL)
		return NULL;

	return delete(&houses[root->house], first, last); //calls delete function 

}

Student* find(Student* root, char* first, char* last) { //finds a student in the BST

	if (root == NULL)
		return NULL;
	
	return search(root, first, last); //searches for student

}

void addPoints(Student* root, int number) { //add x points to a student's total

	if (root != NULL)
		root->points += number;

}

int score(Student* root) { //calculate total score for all houses
	
	if (root == NULL)
		return 0;

	
	return root->points + score(root->left) + score(root->right);

}






 




















