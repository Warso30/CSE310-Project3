#include <stdio.h>
#include "heap.h"

int left(int i){
	return 2 * i + 1;
}

int right(int i){
	return 2 * i + 2;
}

int parent(int i){
	return (i - 1) / 2;
}

void min_heapify(struct vertex *heap, int i, int size){
	int l = left(i);
	int r = right(i);
	int smallest;
	
	if (l < size && heap[l].dist < heap[i].dist)
		smallest = l;
	else
		smallest = i;
	if (r < size && heap[r].dist < heap[smallest].dist)
		smallest = r;

	if (smallest != i){
		struct vertex temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		min_heapify(heap, smallest, size);
	}
}

void build_min_heap(struct vertex *heap, int size){
	for (int i = parent(size - 1); i >= 0; i--)
		min_heapify(heap, i, size);
}

void heap_insert(struct vertex *heap, struct vertex node, int size, int flag){
	if (flag == 1)
		printf("Insert vertex %d, key=%12.4f\n", node.id, node.dist);
	size++;
	int i = size - 1;
	while (i > 0 && heap[parent(i)].dist > node.dist){
		heap[i] = heap[parent(i)];
		i = parent(i);
	}
	heap[i] = node;
}

void decrease_key(struct vertex *heap, int vertex, float dist, int flag){
	if (flag == 1)
		printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", vertex, heap[vertex - 1].dist, dist);
	int pos = vertex - 1;
	if (heap[pos].dist > dist){
		while (pos > 0 && heap[parent(pos)].dist > dist){
			heap[pos] = heap[parent(pos)];
			pos = parent(pos);
		}
		heap[pos].dist = dist;
	}
}

struct vertex extract_min(struct vertex *heap, int size, int flag){
	struct vertex min = heap[0];
	if (flag == 1)
		printf("Delete vertex %d, key=%12.4f\n", min.id, min.dist);
	heap[0] = heap[size - 1];
	size--;
	min_heapify(heap, 0, size);
	return min;
}
