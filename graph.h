struct edge{
	int id;
	int vertex_u;
	int vertex_v;
	float weight;
};

struct list_entry{
	struct edge edge;
	struct list_entry *next;
};

void list_insert(struct list_entry**, int, struct edge);
void delete_list(struct list_entry**, int);
struct edge* find_edge(struct list_entry**, int, int, int);
int Dijkstra(struct vertex*, struct list_entry**, int, int, int, int);
