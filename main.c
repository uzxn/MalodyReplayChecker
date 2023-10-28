#include <stdio.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char **argv) {
	argc--, argv++;
	if (argc != 1) {
		log("crazy argument\n");
		return 0;
	}

	FILE *fp = fopen(argv[0], "rb");
	if (fp == NULL) {
		log("file not found\n");
		return 0;
	}
	
	printf("File Name \t| %s\n", argv[0]);
	printf("----------------+------------------------------------------------\n");
    
    MalodyReplayInfo mr;
    memset(&mr, 0, sizeof(MalodyReplayInfo));
    MalodyReplayInfo_read(fp, &mr);
    MalodyReplayInfo_print(&mr);
    printf("\n");
    fclose(fp);

	return 0;
}
