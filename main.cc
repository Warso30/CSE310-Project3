#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "util.h"
#include "heap.h"
#include "graph.h"
using namespace std;

int main(int argc, char *argv[]){
	string file = read_command(1, argv);//Name of the graph file
	string direction = read_command(2, argv);//A string denoting the graph is directed or undirected
	ifstream in;//Input file
	in.open(file);
	//Test if the file exist.
	if (!in){
		cout << "File doesn't exist!";
		return -1;
	}

	int num_vertices;//Number of vertices in the graph
	int num_edges;//Number of edges in the graph
	in >> num_vertices >> num_edges;

	struct list_entry **graph = new list_entry *[num_vertices];//An adjacency list representing the graph
	for (int i = 0; i < num_vertices; i++)
		graph[i] = NULL;

	struct edge *edge = new struct edge[num_edges];//An array of edges in the graph
	//Keep reading in the data, and add the edges to the adjacency list representing the graph.
	for (int i = 0; i < num_edges; i++){
		in >> edge[i].id >> edge[i].vertex_u >> edge[i].vertex_v >> edge[i].weight;
		list_insert(graph, edge[i].vertex_u, edge[i]);
		//If the graph is undirected, add the edge to both vertices' adjacency list.
		if (direction == "undirected"){
			int temp = edge[i].vertex_v;
			edge[i].vertex_v = edge[i].vertex_u;
			edge[i].vertex_u = temp;
			list_insert(graph, edge[i].vertex_u, edge[i]);
		}
	}

	in.close();
	
	string query_data[4];//An array of query data
	struct vertex *vertices = new vertex[num_vertices];//An array of vertices in the graph
	int *path = new int[num_vertices];//An array representing the path from a source to a destination
	int heap_size;//Current size of the heap
	int valid = 0;//A value used to check whether last find command is valid
	do{
		int source, s;//Source vertex
		int dest, d;//Destination vertex
		for (int i = 0; i < 4; i++)
			query_data[i] = "";
		string token;
		string str;
		getline(cin, str);
		//Echo each query
		cout << "Query: "<< str << endl;
		//Parse the query and save the data into the query_data array.
		size_t pos = 0;
		int i = 0;
		while ((pos = str.find(" ")) != string::npos){
			token = str.substr(0, pos);
			query_data[i] = token;
			str.erase(0, pos + 1);
			i++;
		}
		query_data[i] = str;
		//Perform find command.
		if (query_data[0] == "find"){
			source = stoi(query_data[1]);
			dest = stoi(query_data[2]);
			int flag = stoi(query_data[3]);
			//The query is valid if the source is in the vertices set, the destination is an integer no equal to source, and the flag is 0 or 1.
			if ((1 <= source && source <= num_vertices) && dest != source && (flag == 0 || flag == 1)){
				//Perform a variant of Dijkstra's Algorithm.
				heap_size = Dijkstra(vertices, graph, num_vertices, source, dest, flag);
				valid = 1;//The query is valid.
			}
			else
				cout << "Error: invalid find query" << endl;
		}
		//Perform write path command.
		else if (query_data[0] == "write"){
			s = stoi(query_data[2]);
			d = stoi(query_data[3]);
			
			if (valid == 0)//No valid find query available.
				cout << "Error: no path computation done" << endl;
			//The source vertices don't match or the destination is not in the vertices set or the destination is the same as the source.
			else if (s != source || ((d < 1 || d > num_vertices) || d == s))
				cout << "Error: invalid source destination pair" << endl;
			else{
				struct vertex vertex = vertices[d - 1];//The destination vertex
				if (vertex.inserted == 1){//The distance between source and destination is non-infinite.
					//Obtain the source-destination path.
					int j = 0;
					while (vertex.pred != -1){
						path[j] = vertex.id;
						j++;
						vertex = vertices[vertex.pred - 1];
					}
					path[j] = vertex.id;
					vertex = vertices[d - 1];
					
					if (vertex.deleted == 1)//The destination has been extracted from the heap.
						cout << "Shortest path: ";
					else//The destination has not been extracted from the heap.
						cout << "Path not known to be shortest: ";
					//Print path and path weight.
					print_path(path, j);
					printf("The path weight is: %12.4f\n", vertex.dist);
				}
				else if (heap_size == 0)//The distance between source and destination is infinite and the heap is empty.
					cout << "No " << s << "-" << d << " path exists." << endl;
				else//The distance between source and destination is infinite and the heap is not empty.
					cout << "No " << s << "-" << d << " path has been computed." << endl;
			}
		}
	}
	while (query_data[0] != "stop");//The stop command exits the program
	
	//Free all memory dynamically allocated.
	delete_list(graph, num_vertices);
	delete[] edge;
	delete[] vertices;
	delete[] path;
		
	return 0;
}
