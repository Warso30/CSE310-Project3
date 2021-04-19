#include <stdio.h>
#include <fstream>
#include <string>

string read_command(int index, char *argv[]){
	return argv[index];
}

void print_path(int *path, int index){
	printf("<");
	for (int i = index; i >= 0; i--){
		if (i != 0)
			printf("%d, ", path[i]);
		else
			printf("%d>\n", path[i]);
	}
}

void print_dist(float *dist, int index){
	printf("weight(");
	for (int i = index; i >= 0; i--){
		if (i != 0)
			printf("%12.4f, ", dist[i]);
		else
			printf("%12.4f)\n", dist[i]);
	}
}
