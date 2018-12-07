#include "lab9.h"

int main() {
	
	char choice;

	ContactList list;
	
	list.size = 0;
	list.capacity = 5;
	list.contacts = malloc(sizeof(Contact) * list.capacity);
	
	char name[NAME_LENGTH];
	char email[EMAIL_LENGTH];
	int age;

	while (choice != 'Q') {
		choice = menu();
		if (choice == 'A') {
			printf("Enter name: ");
			getLine(name);
			printf("Enter e-mail: ");
			getLine(email);
			printf("Enter age: ");
			scanf("%d", &age);
			addContact(name, email, age, &list);
		}	
		else if (choice == 'F') {
			printf("Enter name: ");
			getLine(name);
			findContact(name, &list);
		}
		else if (choice == 'P')
			printAllContacts(&list);
	}

	return 0;

}

char menu() {  
	
	int choice; // input

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

void addContact (char* name, char* email, int age, ContactList* list) {

	if (list->size == list->capacity) {
		list->contacts = realloc(list->contacts, list->capacity * 2 * sizeof(Contact));
		list->capacity *= 2;
	}
	
	Contact* newContact;
	
	newContact->name = strdup(name);
	newContact->email = strdup(email);
	newContact->age = age;

	list->contacts[list->size] = *newContact;	
	
	list->size++; 

}

Contact* findContact (char* name, const ContactList* list) {

	int i;
	
	for (i = 0; i < list->size; i++)
		if (strcmp(list->contacts[i].name, name) == 0)
			return &(list->contacts[i]);

	return NULL;

}

void printAllContacts(const ContactList* list) {
	
int i = 0;

	if( list->size > 0 ) {
		// print everything
		for(i = 0; i < list->size; i++) {
		  printContact(&list->contacts[i]);
		  printf("\t----------------\n");
		}
	}
	else
		printf("\tContact list is empty!\n");

}

void printContact(const Contact* contact) {
	
	printf("\t%s ", contact->name);
	printf("<%s> ", contact->email);
	printf("is %d years old.\n", contact->age);

}

void getLine(char buffer[]) {
	
	int i = 0;
	char c;
	while( (c = getchar()) != '\n' && c != EOF )
		buffer[i++] = c;
	buffer[i] = '\0';

}








