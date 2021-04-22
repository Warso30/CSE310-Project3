struct vertex{
	int id;//Name of the vertex
	int pred;//Predecessor of the vertex
	float dist;//Current distance from source
	int inserted;//Used to check if the vertex has been inserted into the min-heap
	int deleted;//Used to check if the vertex has been deleted from the min-heap
	int determined;//Used to check if the vertex has been added to the source-destination path set
};

int left(int);
int right(int);
int parent(int);
void min_heapify(struct vertex*, int, int);
void heap_insert(struct vertex*, struct vertex, int, int);
void decrease_key(struct vertex*, struct vertex, int, int);
struct vertex extract_min(struct vertex*, int, int);
