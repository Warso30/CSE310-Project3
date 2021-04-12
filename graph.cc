#include <iostream>
#include "graph.h"

void list_insert(struct list_entry **list, int pos, struct vertex){
	struct list_entry *old_head = list[pos];
	list_entry[pos] = new list_entry;
	list_entry[pos]->vertex = vertex;
	list_entry[pos]->next = old_head;
}

