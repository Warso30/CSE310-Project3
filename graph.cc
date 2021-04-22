#include <climits>
#include <iostream>
#include "graph.h"
#include "heap.h"

//This function inserts an edge into the adjacency list.
//It takes a pointer to the adjacency list, a vertex id, and an edge as parameters.
void list_insert(struct list_entry **list, int vertex, struct edge edge){
	int pos = vertex - 1;//Position in the adjacency list
	//Insert the edge at head.
	struct list_entry *old_head = list[pos];
	list[pos] = new list_entry;
	list[pos]->edge = edge;
	list[pos]->next = old_head;
}
//This function deletes the whole adjacency list.
//It takes a pointer to the adjacency list and its size as parameters.
void delete_list(struct list_entry **list, int size){
	//Delete the chain at each index.
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
	//Free the memory dynamically allocated for the adjacency list.
	delete[] list;
}
	
//This function finds the edge of a vertex which has not been used yet.
//It takes a pointer to the adjacency list, the vertex id, a value which indicates the other endpoint of the edge, and the edge id as parameters.
//It returns a pointer to an edge of the vertex.
struct edge* find_edge(struct list_entry **graph, int vertex_u, int value, int id){
	struct list_entry *temp = graph[vertex_u - 1];
	if (temp == NULL)//If the chain is empty, the vertex doesn't have any edges.
		return NULL;
	struct edge *edge = NULL;

	//Value and id are identifiers to check whether an edge has already been used.
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

//This function computes a single-source shortest path between a specified pair of vertices in the graph, or from a specified source vertex to all destinations(exclude the source itself) in the vertices set.
//It takes a pointer to the vertices set and the graph, the number of vertices, a source vertex, a destination vertex and a flag as parameters.
//It returns the current size of the min-heap.
int Dijkstra(struct vertex *vertices, struct list_entry **graph, int num_vertices, int source, int destination, int flag){
	int heap_size = 0;//Current size of the min-heap
	struct vertex *heap = new vertex[num_vertices];//A min-heap priority queue
	//Initialize the vertices.
	for (int i = 0; i < num_vertices; i++){
		vertices[i].id = i + 1;
		vertices[i].pred = -1;//Doesn't have a predecessor
		vertices[i].dist = INT_MAX;//The distance to the source is infinite.
		vertices[i].inserted = 0;
		vertices[i].deleted = 0;
		vertices[i].determined = 0;
	}
	//Add the source vertex to the min-heap.
	vertices[source - 1].dist = 0;
	vertices[source - 1].inserted = 1;
	heap_insert(heap, vertices[source - 1], heap_size, flag);
	heap_size++;
	//Compute the path until the min-heap is empty.
	while (heap_size != 0){
		//Extract the vertex with the shortest distance to the source.
		struct vertex vertex_u = extract_min(heap, heap_size, flag);
		vertex_u.deleted = 1;
		vertex_u.determined = 1;
		heap_size--;
		vertices[vertex_u.id - 1] = vertex_u;

		//Terminate the algorithm when the destination is extracted.
		if (vertex_u.id == destination)
			break;
		//Find the edge of the vertex_u.
		struct edge *adj = find_edge(graph, vertex_u.id, 0, 0);
		//For every vertex that is in the vertices set but not in the path set and adjacent to vertex_u.
		while (adj != NULL){
			struct vertex vertex_v = vertices[adj->vertex_v - 1];//The adjacent vertex
			//Check if the vertex is in the path set.
			if (vertex_v.determined == 0){
				//Perform relaxation
				if (vertex_u.dist + adj->weight < vertex_v.dist){
					vertex_v.dist = vertex_u.dist + adj->weight;
					vertex_v.pred = vertex_u.id;

					//If the distance to the source of a vertex_v that is not in the heap is reduced from infinity to a real number, then the vertex_v is inserted into the heap.
					if (vertex_v.inserted == 0){
						vertex_v.inserted = 1;
						heap_insert(heap, vertex_v, heap_size, flag);
						heap_size++;
					}
					//Otherwise, simply decrease its distance to the source.
					else
						decrease_key(heap, vertex_v, heap_size, flag);
					vertices[adj->vertex_v - 1] = vertex_v;
				}
			}
			//Find the next edge of the vertex_u.
			adj = find_edge(graph, vertex_u.id, adj->vertex_v, adj->id);
		}
	}
	//Free the memory dynamically allocated for the heap.
	delete[] heap;
	return heap_size;
}
