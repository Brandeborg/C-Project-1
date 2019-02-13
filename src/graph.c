#include <stdlib.h>
#include <stdio.h>
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

	graph *graph = malloc(sizeof(graph));
	vertex *vert;
	
	size_t count = -1;
	while ((charactersRead = getline(&line, &size, file) != -1))
	{
		if (count == -1)
		{
			int numVert = atoi(line);
			graph->number_vertices = numVert;
			vert = malloc(numVert * sizeof(vertex));
		}
		else
		{
			(&vert[count])->id = count;
			(&vert[count])->out_neighbours = init_linked_list();
			(&vert[count])->in_neighbours = init_linked_list();

			for (int i = 0; i < strlen(line); i++)
			{
				if (line[i] == '1')
				{
					add_element((&vert[count])->out_neighbours, i);
				}
			}
		}
		count++;
	}

	//adding vertices to in_neighbors
	for (int i = 0; i < graph->number_vertices; i++)
	{
		linked_list *restore = (&vert[i])->out_neighbours;
		while ((&vert[i])->out_neighbours->next != NULL)
		{
			int j = (&vert[i])->out_neighbours->next->data;
			{
				add_element((&vert[j])->in_neighbours, i);
			}
			(&vert[i])->out_neighbours = (&vert[i])->out_neighbours->next;
		}
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
				printf("Node '%d' ", (&vert[i])->id);
				printf("peger på node %d", (&vert[i])->out_neighbours->next->data);
			}
			else
			{
				printf(",%d", (&vert[i])->out_neighbours->next->data);
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
				printf("Node '%d' ", (&vert[i])->id);
				printf("peges på af node %d", (&vert[i])->in_neighbours->next->data);
			}
			else
			{
				printf(",%d", (&vert[i])->in_neighbours->next->data);
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
