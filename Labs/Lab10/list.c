#include <stdio.h>
#include <stdlib.h>

typedef struct _LinkNode {
	
	int data;
	struct _LinkNode* next;

} LinkNode;

LinkNode* add(LinkNode* head, int value);
LinkNode* delete(LinkNode* head, int value);
void print(LinkNode* head);
void empty(LinkNode* head);

int main() {

	int command = 0;
	int value = 0;
	LinkNode* head = NULL;	

	while (command != 4) {

		printf("1. Add new element\n2. Delete element\n3. Print list\n4. Exit\n");
		scanf("%d", &command);
	
		if (command == 1) {
			scanf("%d", &value);
			head = add(head, value);
		}
		else if (command == 2) {
			scanf("%d", &value);			
			head = delete(head, value);
		}
		else if (command == 3) 
			print(head);
	}

	empty(head);
	
	return 0;
}

LinkNode* add(LinkNode* head, int value) {

	LinkNode* newNode = malloc(sizeof(LinkNode));
	newNode->data = value;

	newNode->next = head;
	head = newNode;
	
	return head;
	
}

LinkNode* delete(LinkNode* head, int value) {

	LinkNode* temp = head;
	LinkNode* ptr;

	if (head == NULL)
		return NULL;

	if (temp->data == value) {
		head = temp->next;
		free(temp);
		return head;
	}

	while (temp->next != NULL) {
		if (temp->next->data == value) {
			ptr = temp->next;
			temp->next = ptr->next;
			free(ptr);
			return head;
		}	
		temp = temp->next;	
	}

	return head;	
}

void print(LinkNode* head) {
	
	LinkNode* temp = head;

	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}

	printf("\n");
}

void empty(LinkNode* head) {

	LinkNode* temp;

	while (temp->next != NULL) {
		temp = head;
		head = temp->next;
		free(temp);
	}

}
