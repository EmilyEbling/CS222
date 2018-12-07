#include "lab11.h"

int main() {	

	char name[NAME_LENGTH];
	char email[EMAIL_LENGTH];
	int age = 0;
	Contact* root = NULL;
	Contact* found = NULL;
	char choice = '\0';	

	do {
		choice = menu();
		switch( choice ) {
			case 'A': 
				printf("\tEnter name: ");
				readLine(name);
				printf("\tEnter e-mail: ");
				readLine(email);
				printf("\tEnter age: ");
				scanf("%d", &age);
				root = addContact(name, email, age, root);
				break;
			case 'F':
				printf("\tEnter name: ");
				readLine(name);
				found = findContact( name, root );
				if( found == NULL )
					printf("\"%s\" not found\n", name);
				else
					printContact( found );
				break;
			case 'P':
				printSortedContacts( root );
				break;
		}	
	} while( choice != 'Q' );
	
	cleanUp( root );
	root = NULL;

	return 0;

}

char menu() {  
	
	int choice;  // input

	// print menu  
	printf("A - Add a contact\n");
	printf("F - Find and display a contact\n");
	printf("P - Print contact list\n");
	printf("Q - Quit\n");
	printf("Your choice: ");

	// Get input
	while( isspace(choice = getchar()) );
	while( getchar() != '\n');

	return toupper(choice);

}

void readLine(char buffer[]) {
	
	int value = 0;
	int index = 0;
	
	value = getchar();
	while( value != '\n' && value != EOF ) {
		buffer[index++] = value;
		value = getchar();
	}
	
	buffer[index] = '\0';

}

void printContact(const Contact* contact) {

	printf("\t%s ", contact->name);
	printf("<%s> ", contact->email);
	printf("is %d years old.\n", contact->age);

}

Contact* addContact(char* name, char* email, int age, Contact* root) {

	if (root == NULL) {
		Contact* newContact = malloc(sizeof(Contact));
		newContact->name = strdup(name);
		newContact->email = strdup(email);
		newContact->age = age;
		root = newContact;
		return root;
	}	

	else if (strcmp(name, root->name) < 0) 
		root->left = addContact(name, email, age, root->left);
	
	else if (strcmp(name, root->name) > 0)
		root->right = addContact(name, email, age, root->right);

}

Contact* findContact(char* name, Contact* root) {

	if (root == NULL)
		return NULL;

	else if (strcmp(name, root->name) < 0)
		root = findContact(name, root->left);
	
	else if (strcmp(name, root->name) > 0)
		root = findContact(name, root->right);

	else if (strcmp(name, root->name) == 0)
		return root;

}

void printSortedContacts(Contact* root) {

	if (root != NULL) {
		printSortedContacts(root->left);
		printContact(root);
		printSortedContacts(root->right);	
	}

}

void cleanUp(Contact* root) {

	if (root != NULL) {
		cleanUp(root->left);
		free(root);
		cleanUp(root->right);
	}

}






















