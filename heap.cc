#include <stdio.h>
#include "heap.h"

//This function calculates the index of the left child.
//It takes the index of the parent as a parameter.
//It returns the index of the left child.
int left(int i){
	return 2 * i + 1;
}

//This function calculates the index of the right child.
//It takes the index of the parent as a parameter.
//It returns the index of the right child.
int right(int i){
	return 2 * i + 2;
}

//This function calculates the index of the parent.
//It takes the index of the child as a parameter.
//It returns the index of the parent.
int parent(int i){
	return (i - 1) / 2;
}

//This function makes a tree into a min-heap.
//It takes a pointer to the array of the heap, the index of the node violating the min heap property and size of the heap as parameters.
void min_heapify(struct vertex *heap, int i, int size){
	int l = left(i);//Index of the left child
	int r = right(i);//Index of the right child
	int smallest;//Index of the node with the smallest value
	//If the left child exists and its value is smaller than that of its parent, set the smallest to it.
	if (l < size && heap[l].dist < heap[i].dist)
		smallest = l;
	//Else, set the parent to be the smallest.
	else
		smallest = i;
	
	//If the right child exists and its value is smaller than current smallest value, set the smallest to it.
	if (r < size && heap[r].dist < heap[smallest].dist)
		smallest = r;
	//If the value of the parent is not the smallest, swap it with the smallest one and call the function again to maintain the min-heap property of the subtree.
	if (smallest != i){
		struct vertex temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		min_heapify(heap, smallest, size);
	}
}

//This function inserts a node into the min-heap.
//It takes a pointer to the heap, its size, the vertex node and the flag as parameters.
void heap_insert(struct vertex *heap, struct vertex node, int size, int flag){	
	if (flag == 1)//Print information about insertion if flag is 1.
		printf("Insert vertex %d, key=%12.4f\n", node.id, node.dist);
	size++;
	int i = size - 1;
	//Keep swapping with the parent until the proper position is found.
	while (i > 0 && heap[parent(i)].dist > node.dist){
		heap[i] = heap[parent(i)];
		i = parent(i);
	}
	heap[i] = node;
}

//This function decreases the distance to the source of a vertex and maintains the min-heap property.
//It takes a pointer to the heap, its size, a vertex node and the flag as parameters.
void decrease_key(struct vertex *heap, struct vertex vertex, int size, int flag){
	int i;
	//Find the vertex node.
	for (i = 0; i < size; i++){
		if (heap[i].id == vertex.id)
			break;		
	}

	if (flag == 1)//Print the information about the decrease-key operation if flag is 1.
		printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", vertex.id, heap[i].dist, vertex.dist);
	if (heap[i].dist > vertex.dist){
		//Keep swapping with the parent until the proper position is found.
		while (i > 0 && heap[parent(i)].dist > vertex.dist){
			heap[i] = heap[parent(i)];
			i = parent(i);
		}
		heap[i] = vertex;
	}
}

//This function extracts the vertex with minimum distance to the source from the min-heap.
//It takes a pointer to the heap, its size and the flag as parameters.
//It returns the vertex with minimum distance to the source.
struct vertex extract_min(struct vertex *heap, int size, int flag){
	//The root of the min-heap is the vertex with minimum distance to the source.
	struct vertex min = heap[0];
	if (flag == 1)//Print the information about the deletion if flag is 1.
		printf("Delete vertex %d, key=%12.4f\n", min.id, min.dist);
	//Replace the root with the last node in the heap and perform min-heapify at the root to maintain min-heap property.
	heap[0] = heap[size - 1];
	size--;//The heap size decreases by 1.
	min_heapify(heap, 0, size);
	return min;
}
