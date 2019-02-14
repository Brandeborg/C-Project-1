#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "linked_list.h"

void cycle_detection(graph *g)
{

    linked_list *L = init_linked_list();
    linked_list *S = init_linked_list();

    vertex *vertG = g->vertices;

    //adding vertices with no in_neighbours to S
    for (size_t i = 0; i < g->number_vertices; i++)
    {
        if (linked_list_size((&vertG[i])->in_neighbours) == 0)
        {
            add_element(S, (&vertG[i]));
        }
    }

    while (linked_list_size(S) != 0)
    {
        //removing an element from S and adding it to L
        vertex *vertS = remove_first(S);
        add_element(L, (void*) (size_t) vertS->id);

        //if the removed element has an out_neighbour
        //remove that edge from the graph
        //both from the pointee's in_neighbours
        //and the pointer's out_neighbours
        while (vertS->out_neighbours->next != NULL)
        {
            size_t id = (size_t) vertS->out_neighbours->next->data;
            remove_element((&vertG[id])->in_neighbours, (void*) (size_t) vertS->id);
            remove_element(vertS->out_neighbours, (void*) id);

            //add the pointee to S, if it has no other in_neighbors
            if ((&vertG[id])->in_neighbours->next == NULL)
            {
                add_element(S, (&vertG[id]));
            }
        }
    }

    //printing L if the graph has no more edges
    for (size_t i = 0; i < g->number_vertices; i++)
    {
        if ((&vertG[i])->in_neighbours->next != NULL)
        {
            printf("CYCLE DETECTED!\n");
            break;
        }
        while (L->next != NULL)
        {
            printf("%li", (size_t) remove_first(L));
            if (L->next != NULL)
            {
                printf(", ");
            }
            else
            {
                printf("\n");
            }
        }
    }
}
