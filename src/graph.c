#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

graph *read_graph(char *filename)
{

	FILE *file = fopen(filename, "r");
	char *line = NULL;
	size_t size = 0;
	size_t charactersRead = 0;

	if (file == NULL)
	{
		printf("could not read file\n");
		exit(EXIT_FAILURE);
	}

	//allocating memory for the graph.
	//+8 for esktra stuff, that gave me an error otherwise
	graph *graph = malloc(sizeof(graph) + 8);
	vertex *vert;

	size_t count = -1;
	//save in line in char pinter as long as there are lines
	while ((charactersRead = getline(&line, &size, file) != -1))
	{
		if (count == -1)
		{
			//allocating memory for all vertices in the graph
			int numVert = atoi(line);
			graph->number_vertices = numVert;
			vert = malloc(numVert * sizeof(vertex));
		}
		else
		{
			(&vert[count])->id = count;
			(&vert[count])->out_neighbours = init_linked_list();
			(&vert[count])->in_neighbours = init_linked_list();

			//reading every character in the line
			for (size_t i = 0; i < strlen(line); i++)
			{
				//adding the number of the pointees (current char)
				//to the out_neighbours of the pointer
				if (line[i] == '1')
				{
					add_element((&vert[count])->out_neighbours, (void *)i);
				}
			}
		}
		count++;
	}

	

	//adding vertices to in_neighbours
	for (size_t i = 0; i < graph->number_vertices; i++)
	{
		linked_list *restore = (&vert[i])->out_neighbours;

		//if the current vertex has an out_neighbour,
		//add current vertex to out_neighbours's in_neighbours
		while ((&vert[i])->out_neighbours->next != NULL)
		{
			size_t j = (size_t)(&vert[i])->out_neighbours->next->data;
			{
				add_element((&vert[j])->in_neighbours, (void *)i);
			}
			(&vert[i])->out_neighbours = (&vert[i])->out_neighbours->next;
		}
		//restoring the beginning of out_neighbours,
		//since the above process pushed the pointer
		//to the end
		(&vert[i])->out_neighbours = restore;
	}

	graph->vertices = vert;
	return graph;
}

void print_graph(graph *g)
{

	vertex *vert = g->vertices;
	int count = 0;

	printf("Number of vertices: %d\n\n", g->number_vertices);

	printf("Out_neighbors: \n");
	for (int i = 0; i < g->number_vertices; i++)
	{
		count = 0;
		while ((&vert[i])->out_neighbours->next != NULL)
		{
			if (count == 0)
			{
				printf("Node '%i' ", (&vert[i])->id);
				printf("peger på node %li", (size_t)(&vert[i])->out_neighbours->next->data);
			}
			else
			{
				printf(",%li", (size_t)(&vert[i])->out_neighbours->next->data);
			}
			(&vert[i])->out_neighbours = (&vert[i])->out_neighbours->next;
			count++;
		}
		if ((&vert[i])->out_neighbours->previous != NULL)
		{
			printf("\n");
		}
	}

	printf("\nIn_neighbors: \n");
	for (int i = 0; i < g->number_vertices; i++)
	{
		count = 0;
		while ((&vert[i])->in_neighbours->next != NULL)
		{
			if (count == 0)
			{
				printf("Node '%i' ", (&vert[i])->id);
				printf("peges på af node %li", (size_t)(&vert[i])->in_neighbours->next->data);
			}
			else
			{
				printf(",%li", (size_t)(&vert[i])->in_neighbours->next->data);
			}
			(&vert[i])->in_neighbours = (&vert[i])->in_neighbours->next;
			count++;
		}
		if ((&vert[i])->in_neighbours->previous != NULL)
		{
			printf("\n");
		}
	}
}
