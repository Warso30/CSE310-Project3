struct vertex{
	int id;
	int predecessor;
	int weight;
}

struct list_entry{
	struct vertex;
	struct list_entry *next;
}

