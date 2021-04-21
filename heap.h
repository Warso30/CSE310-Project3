struct vertex{
	int id;
	int pred;
	float dist;
	int inserted;
	int deleted;
	int determined;
};

int left(int);
int right(int);
int parent(int);
void min_heapify(struct vertex*, int, int);
void build_min_heap(struct vertex*, int);
void heap_insert(struct vertex*, struct vertex, int, int);
void decrease_key(struct vertex*, struct vertex, int, int);
struct vertex extract_min(struct vertex*, int, int);
