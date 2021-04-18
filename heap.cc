int left(int i){
	return 2 * i + 1;
}

int right(int i){
	return 2 * i + 2;
}

int parent(int i){
	return (i - 1) / 2
}

void min_heapify(struct heap_entry *heap, int i, int size){
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
		struct heap_entry temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		min_heapify(heap, smallest, size);
	}
}

void build_min_heap(struct heap_entry *heap, int size){
	for (int i = parent(size - 1); i >= 0; i--)
		min_heapify(heap, i, size);
}

void heap_insert(struct heap_entry *heap, struct heap_entry node, int size){
	size++;
	int i = size - 1;
	while (i > 0 && heap[parent(i)].dist > node.dist){
		heap[i] = heap[parent(i)];
		i = parent(i);
	}
	heap[i] = node;
}

void decrease_key(struct heap_entry *heap, int pos, int dist){
	if (heap[pos].dist > dist){
		while (pos > 0 && heap[parent(pos)].dist > dist){
			heap[pos] = heap[parent(pos)];
			pos = parent(pos);
		}
		heap[pos].dist = dist;
	}
}


