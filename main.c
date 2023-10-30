#include <stdio.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char **argv) {
    argc--, argv++;
    if (argc == 0) {
        printf("HELP\n");
        return 0;
    }

    if (strcmp(argv[0], "csv") == 0) {
        if (argc < 3) {
            printf("crazy arguments\n");
            return 0;
        }
        FILE *fp_out = fopen(argv[1], "w");
        fprintf(fp_out,
                "File Name,Song Name,Song Author,Difficulty,"
                "Score,Accuracy,Judgement,Max Combo,Best,Cool,Good,Miss,Mods,"
                "Chart md5,Time,Malody Ver\n");
        for (int i = 2; i < argc; i++) {
            FILE *fp_in = fopen(argv[i], "rb");
            if (fp_in == NULL) {
                printf("file not found\n");
                fclose(fp_out);
                return 0;
            }
            printf("current file: %s\n", argv[i]);
            fprintf(fp_out, "%s,", argv[i]);
            MalodyReplayInfo mr;
            memset(&mr, 0, sizeof(MalodyReplayInfo));
            MalodyReplayInfo_read(fp_in, &mr);
            MalodyReplayInfo_csv(fp_out, &mr);
            fclose(fp_in);
        }
        printf("success\n");
        fclose(fp_out);
        return 0;
    }

    for (int i = 0; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            printf("file not found\n");
            return 0;
        }
        printf("----------------+------------------------------------------------\n");
        printf(" File Name \t| %s\n", argv[i]);
        printf("----------------+------------------------------------------------\n");
        MalodyReplayInfo mr;
        memset(&mr, 0, sizeof(MalodyReplayInfo));
        MalodyReplayInfo_read(fp, &mr);
        MalodyReplayInfo_print(&mr);
        if (i+1 == argc) {
            printf("----------------+------------------------------------------------\n");
        }
        fclose(fp);
    }
    return 0;
}
