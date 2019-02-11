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
	size_t count = -1;

	while ((charactersRead = getline(&line, &size, file) != -1))
	{
		if (count == -1)
		{
			graph->number_vertices = atoi(line);
		}
		else
		{
			vertex *vertex = malloc(sizeof(vertex));
			vertex->id = count;
			vertex->out_neighbours = init_linked_list();
			
			for (int i = 0; i<strlen(line); i++)
			{
				printf("%c \n", line[i]);

				if (line[i] == 1)
				{
					add_element(vertex->out_neighbours, i);
					graph->vertices = vertex;
				}
				
			}
			printf("%i\n", vertex->out_neighbours->next);
		}
		count++;

		//printf("%i\n", charactersRead);
		//printf("%s\n", line);
	};

	return NULL;
}

void print_graph(graph *g)
{
}
