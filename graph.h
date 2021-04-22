struct edge{
	int id;//Edge id
	int vertex_u;//Endpoint of the edge(start)
	int vertex_v;//Endpoint of the edge(end)
	float weight;//Edge weight
};

struct list_entry{
	struct edge edge;//Edge in the graph
	struct list_entry *next;//Next pointer pointing to the next edge
};

void list_insert(struct list_entry**, int, struct edge);
void delete_list(struct list_entry**, int);
struct edge* find_edge(struct list_entry**, int, int, int);
int Dijkstra(struct vertex*, struct list_entry**, int, int, int, int);
