#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

graph *read_graph(char *filename)
{

	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("could not read file\n");
		exit(EXIT_FAILURE);
	}

	/*allocating memory for the graph.
	+8 for esktra stuff, that gave me an error otherwise*/
	graph *graph = malloc(sizeof(graph) + 8);
	vertex *vert;

	//defining variables needed for getline
	char *line = NULL;
	size_t buffersize = 0;
	size_t charactersRead = 0;

	size_t lineNum = -1;
	//save the read line in char pointer as long as there are lines
	while ((charactersRead = getline(&line, &buffersize, file) != -1))
	{
		/*the very first line number is set to -1, since that
		is not a node. The rest (nodes) are 0-indexed thereafter*/
		if (lineNum == -1)
		{
			/*allocating memory for all vertices in the graph
			according to the first line of the file, which is
			number of nodes*/
			int numVert = atoi(line);
			graph->number_vertices = numVert;
			vert = malloc(numVert * sizeof(vertex));
		}
		else
		{
			(&vert[lineNum])->id = lineNum;
			(&vert[lineNum])->out_neighbours = init_linked_list();
			(&vert[lineNum])->in_neighbours = init_linked_list();

			//reading every character in the current line
			for (size_t i = 0; i < strlen(line); i++)
			{
				/*adding the number of the pointees (current char)
				to the out_neighbours of the pointer*/
				if (line[i] == '1')
				{
					add_element((&vert[lineNum])->out_neighbours, (void *)i);
				}
			}
		}
		lineNum++;
	}
	fclose(file);

	//adding vertices to in_neighbours
	for (size_t i = 0; i < graph->number_vertices; i++)
	{
		//preparing a restoration point to the beginning of the list
		linked_list *restore = (&vert[i])->out_neighbours;

		/*if the current vertex has an out_neighbour,
		add current vertex to out_neighbours's in_neighbours*/
		while ((&vert[i])->out_neighbours->next != NULL)
		{
			size_t j = (size_t)(&vert[i])->out_neighbours->next->data;
			{
				add_element((&vert[j])->in_neighbours, (void *)i);
			}
			(&vert[i])->out_neighbours = (&vert[i])->out_neighbours->next;
		}
		/*restoring the beginning of out_neighbours,
		since the above process pushed the pointer
		to the end*/
		(&vert[i])->out_neighbours = restore;
	}
	graph->vertices = vert;

	return graph;
}

void print_graph(graph *g)
{
}
