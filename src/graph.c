#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

graph *read_graph(char *filename)
{

	FILE *file = fopen(filename, "r");
	char *line = NULL;
	int size = 0;
	int charactersRead = 0;

	if (file == NULL)
	{
		printf("could not read file\n");
		exit(EXIT_FAILURE);
	}

	int count = -1;
	while ((charactersRead = getline(&line, &size, file) != -1))
	{
		if (count == -1)
		{
			graph *graph = malloc(sizeof(graph));
			graph->number_vertices = (int) line;
		}
		else
		{
			vertex *vertex = malloc(sizeof(vertex));
			vertex->id = count;
			vertex->out_neighbours = init_linked_list();

			for (int i = 0; strlen(line); i++)
			{
				if (line[i] == 1)
				{
					add_element(vertex->out_neighbours, i);
				}
			}
		}
		count++;

		printf("%i\n", charactersRead);
		printf("%s\n", line);
	};

	return NULL;
}

void print_graph(graph *g)
{
}
