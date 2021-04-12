#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
	string file = argv[1];
	string direction = argv[2];
	ifstream in;
	in.open(file);
	if (!in){
		cout << "File doesn't exist!";
		return -1;
	}
	int num_vertices;
	int num_edges;
	in >> num_vertices >> num_edges;
	struct list_entry **graph = new list_entry *[vertices];
	struct 
	for (int i = 0; i < num_edges; i++){
			
	}
	in.close();
	
		
	return 0;
}
