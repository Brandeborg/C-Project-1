#include <stdlib.h>
#include "graph.h"
#include "linked_list.h"

void cycle_detection(graph *g)
{

    linked_list *L = init_linked_list();
    linked_list *S = init_linked_list();

    vertex *vertG = g->vertices;

    for (int i = 0; i < g->number_vertices; i++)
    {
        if (linked_list_size((&vertG[i])->in_neighbours) == 0)
        {
            add_element(S, (&vertG[i]));
        }
    }

    while (linked_list_size(S) != 0)
    {
        vertex *vertS = remove_first(S);
        add_element(L, vertS->id);
        while (vertS->out_neighbours->next != NULL)
        {
            int id = vertS->out_neighbours->next->data;
            remove_element((&vertG[id])->in_neighbours, vertS->id);
            remove_element(vertS->out_neighbours, id);
            if ((&vertG[id])->in_neighbours->next == NULL)
            {
                add_element(S, (&vertG[id]));
            }
        }
    }

    for (int i = 0; i < g->number_vertices; i++)
    {
        if ((&vertG[i])->in_neighbours->next != NULL)
        {
            printf("CYCLE DETECTED!\n");
            break;
        }
        while (L->next != NULL)
        {
            printf("%i", remove_first(L));
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
