#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "cycledetection.h"

/*
 * Prints the usage to the console.
 */
void show_usage() {
	printf("===================================\n");
	printf("=======     Usage      ============\n");
	printf("===================================\n");
	printf(" ./program graph-file \n");
	printf("===================================\n");
}

// First command line parameter - input file
int main(int argc, char *argv[]) {

	linked_list *list = init_linked_list();


	add_element(list, 1);
	add_element(list, 2);
	add_element(list, 3);
	add_element(list, 4);

	void* removed = remove_first(list);

	int code = remove_element(list, 3);

	printf("%i\n", code);
	printf("%i\n", list->next->data);
	printf("%i\n", list->next->next->data);



	// Error checking
	if( argc != 2) {
		show_usage();
		return 0;
	}

	// Build a graph from the input
	graph *g = read_graph(argv[1]);

	// Run cycle detection algorithm and output result
	cycle_detection(g);
}
