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
	graph->vertices = vert;

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
		for (int j = 0; j < graph->number_vertices; j++)
		{		
			while ((&vert[j])->out_neighbours->next != NULL)
			{
				if ((&vert[j])->out_neighbours->next->data == i)
				{
					add_element((&vert[i])->in_neighbours, j);
				}
				(&vert[j])->out_neighbours = (&vert[j])->out_neighbours->next;
			}
		}
	}

	return graph;
}

void print_graph(graph *g)
{
	vertex *vert = g->vertices;
	int count = 0;

	printf("Number of vertices: %d\n\n", g->number_vertices);

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
		printf("\n");
	}

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
		printf("\n");
	}
}
