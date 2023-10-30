#ifndef _FUNC_H
#define _FUNC_H

#define STR_SIZE 256

typedef char byte, string[STR_SIZE];
typedef struct MalodyReplayInfo {
    int ver[3];
    string md5;
    string diff;
    string song;
    string author;
    int score;
    int combo;
    int best;
    int cool;
    int good;
    int miss;
    int mods;
    char judge;
    string time;
} MalodyReplayInfo;

void read_int(FILE *fp, int *var);
void read_str(FILE *fp, char *str);
void MalodyReplayInfo_read(FILE *fp, MalodyReplayInfo *mr);
void MalodyReplayInfo_print(MalodyReplayInfo *mr);
void MalodyReplayInfo_csv(FILE *fp, MalodyReplayInfo *mr);

#endif /* func.h */
