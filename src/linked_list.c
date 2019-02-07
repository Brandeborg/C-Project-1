/*
 * linked_list.c
 *
 *  Created on: Dec 24, 2013
 *      Author: jacob
 */
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

linked_list *init_linked_list() {
	linked_list *root = (linked_list*)malloc(sizeof(linked_list)); 
	root -> data = NULL;
	root -> next = NULL;
	root -> previous = NULL;
	return root;
}

void add_element(linked_list *list, void *element) {
	linked_list *newNode = init_linked_list();

	while (list->next != NULL){
		list = list->next;
	}

	newNode->data = (void*)malloc(sizeof(int)); 

	newNode->data = element;
	newNode->next = NULL;
	newNode->previous = list;
	list->next = newNode;
}

int linked_list_size(linked_list *list) {
	int count = 0;

	while (list->next != NULL){
		list = list->next;
		count++;
	}
	return count;
}

void *remove_first(linked_list *list) {
	void* element = list->next->data;

	free(list->next);	//may be wrong					
	list->next = list->next->next;

	return element;
}

int remove_element(linked_list *list, void *element) {
	while (list->next != NULL){
		if (list->next->data == element){
			free(list->next);		//may be wrong				
			list->next = list->next->next;
			return 0;
		}
		else
		{
			list = list->next;
		}
	}

	return -1;
}
