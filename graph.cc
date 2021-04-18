#include <iostream>
#include "graph.h"

void list_insert(struct list_entry **list, int pos, struct edge edge){
	struct list_entry *old_head = list[pos];
	list_entry[pos] = new list_entry;
	list_entry[pos]->edge = edge;
	list_entry[pos]->next = old_head;
}

struct edge find_min(struct list_entry **graph, int vertex_u, int value){
	struct list_entry *temp = graph[vertex_u];
	if (temp == NULL)
		return NULL;
	struct edge min = temp->edge;
	while (temp != null){
		if (temp->edge.vertex_v != value && temp->edge.vertex_v < min.vertex_v)
			min = temp->edge;
		temp = temp->next;
	}
	
}

void Dijkstra(struct vertex *path, struct list_entry **graph, int num_vertices, int source, int destination, int flag){
	int heap_size = 0;
	int path_size = 0;
	struct vertex *heap = new vertex[num_vertices];
	struct vertex *vertices = new vertex[num_vertices];
	for (int i = 0; i < num_vertices; i++){
		vertices[i].id = i;
		vertices[i].pred = -1;
		vertices[i].dist = INT_MAX;
	}
	vertices[source].dist = 0;
	heap_insert(heap, vertices[source], heap_size);
	heap_size++;
	if (flag == 1)
		cout << "Insert vertex %d, key=%12.4f\n";
	for (int i = 0; i < num_vertices  - 1; i++){
		if (size == 0)
			break;
		else{
			struct vertex vertex_u = extract_min(heap, size);
			path[i] = vertex_u;
			path_size++;
			struct edge min = find_min(graph, vertex_u.id, 0);
			while (min != NULL){
				int j;
				for (j = 0; j < path_size; j++){
					if (min.vertex_v == path[j].id)
						break;
				}
				if (j == path_size){
					if (vertex_u.dist + min.weight < vertices[min.vertex_v].dist){
						vertices[min.vertex_v].dist = vertex_u.dist + min.weight;
						vertices[min.vertex_v].pred = vetex_u.id;
						heap_insert(heap, vertices[min.vertex_v], heap_size);
						heap_size++;
					}
				}
				min = find_min(graph, vertex_u.id, min.vertex_v);
			}
		}
	}
	
}

