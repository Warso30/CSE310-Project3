#include <climits>
#include <iostream>
#include "graph.h"
#include "heap.h"

void list_insert(struct list_entry **list, int vertex, struct edge edge){
	int pos = vertex - 1;
	struct list_entry *old_head = list[pos];
	list[pos] = new list_entry;
	list[pos]->edge = edge;
	list[pos]->next = old_head;
}

void delete_list(struct list_entry **list, int size){
	for (int i = 0; i < size; i++){
		struct list_entry *temp = list[i];
		struct list_entry *curr = temp;
		while(temp != NULL){
			temp = temp->next;
			curr->next = NULL;
			delete curr;
			curr = temp;
		}
	}
	delete[] list;
}
/*
struct edge* find_edge(struct list_entry **graph, int vertex_u, int value){
	struct list_entry *temp = graph[vertex_u - 1];
	if (temp == NULL)
		return NULL;
	struct edge *edge = NULL;
	while (temp != NULL){
		if (temp->edge.vertex_v > value){
			edge = &temp->edge;
			temp = temp->next;
			break;
		}
		temp = temp->next;
	}

	while (temp != NULL){
		if (temp->edge.vertex_v > value && temp->edge.vertex_v < edge->vertex_v)
			edge = &temp->edge;
		temp = temp->next;
	}
	
	return edge;
}
*/
struct edge* find_edge(struct list_entry **graph, int vertex_u, int value, int id){
	struct list_entry *temp = graph[vertex_u - 1];
	if (temp == NULL)
		return NULL;
	struct edge *edge = NULL;
	if (value == 0)
		edge = &temp->edge;
	else{
		while (temp != NULL){
			if (temp->edge.vertex_v == value && temp->edge.id == id){
				temp = temp->next;
				break;
			}
			temp = temp->next;
		}
		if (temp != NULL)
			edge = &temp->edge;
	}
	return edge;
}
int Dijkstra(struct vertex *vertices, struct list_entry **graph, int num_vertices, int source, int destination, int flag){
	int heap_size = 0;
	struct vertex *heap = new vertex[num_vertices];
	for (int i = 0; i < num_vertices; i++){
		vertices[i].id = i + 1;
		vertices[i].pred = -1;
		vertices[i].dist = INT_MAX;
		vertices[i].inserted = 0;
		vertices[i].deleted = 0;
		vertices[i].determined = 0;
	}
	vertices[source - 1].dist = 0;
	vertices[source - 1].inserted = 1;
	heap_insert(heap, vertices[source - 1], heap_size, flag);
	heap_size++;
	while (heap_size != 0){
		struct vertex vertex_u = extract_min(heap, heap_size, flag);
		vertex_u.deleted = 1;
		vertex_u.determined = 1;
		heap_size--;
		vertices[vertex_u.id - 1] = vertex_u;
		if (vertex_u.id == destination)
			break;
		struct edge *adj = find_edge(graph, vertex_u.id, 0, 0);
		while (adj != NULL){
			struct vertex vertex_v = vertices[adj->vertex_v - 1];
			if (vertex_v.determined == 0){
				if (vertex_u.dist + adj->weight < vertex_v.dist){
					vertex_v.dist = vertex_u.dist + adj->weight;
					vertex_v.pred = vertex_u.id;
					if (vertex_v.inserted == 0){
						vertex_v.inserted = 1;
						heap_insert(heap, vertex_v, heap_size, flag);
						heap_size++;
					}
					else
						decrease_key(heap, vertex_v, heap_size, flag);
					vertices[adj->vertex_v - 1] = vertex_v;
				}
			}
			adj = find_edge(graph, vertex_u.id, adj->vertex_v, adj->id);
		}
	}
	delete[] heap;
	return heap_size;
}
