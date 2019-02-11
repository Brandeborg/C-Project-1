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

			for (int i = 0; i < strlen(line); i++)
			{
				if (line[i] == '1')
				{
					add_element((&vert[count])->out_neighbours, i);
				}
			}
		}
		count++;
	};

	return graph;
}

void print_graph(graph *g)
{
	vertex *vert = g->vertices;
	int count = 0;

	for (int i = 0; i < g->number_vertices; i++)
	{
		count = 0;
		while ((&vert[i])->out_neighbours->next != NULL)
		{
			if (count == 0)
			{
				printf("node '%d' ", (&vert[i])->id);
				printf("peger på %d", (&vert[i])->out_neighbours->next->data);
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
}
