/*
 * linked_list.c
 *
 *  Created on: Dec 24, 2013
 *      Author: jacob
 */
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

linked_list *init_linked_list()
{
	//creating a 'root' node with no data.
	//the root's data field will always be NULL
	linked_list *root = (linked_list *)malloc(sizeof(linked_list));
	root->data = NULL;
	root->next = NULL;
	root->previous = NULL;
	return root;
}

void add_element(linked_list *list, void *element)
{
	//creating new listnode to add to the list
	linked_list *newNode = init_linked_list();

	//iterating through the list to get to the end
	while (list->next != NULL)
	{
		list = list->next;
	}

	//allocating memory for data
	newNode->data = (void *)malloc(sizeof(int));

	//assigning values to all fields once the end is found
	newNode->data = element;
	newNode->next = NULL;
	newNode->previous = list;
	list->next = newNode;
}

int linked_list_size(linked_list *list)
{
	int count = 0;

	//iterating through the list to get to the end 
	//and counting up each step
	while (list->next != NULL)
	{
		list = list->next;
		count++;
	}
	return count;
}

void *remove_first(linked_list *list)
{
	//saving the first element
	//and making the 'root' point to the second element, 
	//making that the new first element
	void *element = list->next->data;
	list->next = list->next->next;

	return element;
}

int remove_element(linked_list *list, void *element)
{
	//iterating through the list
	while (list->next != NULL)
	{
		//comparing the data of each listnode with the element
		if (list->next->data == element)
		{
			//removing element if found as in remove_first
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
