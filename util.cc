#include <stdio.h>
#include <fstream>
#include <string>
#include "util.h"
using namespace std;

//This function reads the command line.
//It takes the the command arguments array and an index as parameters.
//It returns a command argument.
string read_command(int index, char *argv[]){
	return argv[index];
}

//This function prints the source-destination path.
//It takes a pointer to the path and an index as parameters.
void print_path(int *path, int index){
	printf("<");
	for (int i = index; i >= 0; i--){
		if (i != 0)
			printf("%d, ", path[i]);
		else
			printf("%d>\n", path[i]);
	}
}
