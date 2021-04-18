struct vertex{
	int id;
	int pred;
}

struct edge{
	int id;
	struct vertex vertex_u;
	struct vertex vertex_v;
	int weight;
}

struct list_entry{
	struct edge edge;
	struct list_entry *next;
}

