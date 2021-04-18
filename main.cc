#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
	string file = read_command(1, argv);
	string direction = read_command(2, argv);
	ifstream in;
	in.open(file);
	if (!in){
		cout << "File doesn't exist!";
		return -1;
	}
	int num_vertices;
	int num_edges;
	in >> num_vertices >> num_edges;
	struct list_entry **graph = new list_entry *[num_vertices];
	struct edge *edge = new edge[num_edges];
	for (int i = 0; i < num_edges; i++){
		in >> edge[i].id >> edge[i].vertex_u >> edge[i].vertex_v >> edge[i].weight;
		list_insert(graph, edge[i].vertex_u, edge[i]);
		if (direction == "undirected"){
			int temp = edge[i].vertex_v;
			edge[i].vertex_v = edge[i].vertex_u;
			edge[i].vertex_u = temp;
			list_insert(graph, edge[i].vertex_u, edge[i]);
		}
	}

	in.close();
	
	string query_data[4];
	struct vertex *path = new vertex[num_vertices];
	struct vertex *heap;
	int valid = 0;
	do{
		int source, s;
		int dest, d;
		for (int i = 0; i < 4; i++)
			query_data[i] = "";
		string token;
		string str;
		getline(cin, str);
		cout << str << endl;
		size_t pos = 0;
		int i = 0;
		while ((pos = str.find(" ") != string::npos){
			token = str.substr(0, pos);
			query_data[i] = token;
			str.erase(0, pos + 1);
			i++;
		}
		query_data[i] = str;

		if (query_data[0] == "find"){
			source = stoi(query_data[1]);
			dest = stoi(query_data[2]);
			int flag = stoi(query_data[3]);			
			if ((1 <= source && source <= num_vertices) && dest != source && (flag == 0 || flag == 1)){
				heap = Dijkstra(path, graph, num_vertices, source, dest, flag);
				valid = 1;	
			}
			else
				cout << "Error: invalid find query" << endl;
		}
		else if (query_data[0] == "write"){
			s = stoi(query_data[2]);
			d = stoi(query_data[3]);
			if (valid == 0)
				cout << "Error: no path computation done" << endl;
			else if (s != source || ((d < 1 || d > num_vertices) || d == s))
				cout << "Error: invalid source destination pair" << endl;
			else{
				
			}
		}
	}
	while (query_data[0] != "stop");
	
		
	return 0;
}
