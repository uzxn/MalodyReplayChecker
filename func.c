#include <stdio.h>
#include <string.h>
#include <time.h>
#include "func.h"

void read_int(FILE *fp, int *var) {
	fread(var, sizeof(int), 1, fp);
}

void read_str(FILE *fp, char *str) {
	int len = 0;
	read_int(fp, &len);
    fread(str, sizeof(char), len, fp);
}

void MalodyReplayInfo_read(FILE *fp, MalodyReplayInfo *mr) {
    int n = 0;
    string str = {0};
	read_str(fp, str); // "mr format head"
	memset(str, 0, STR_SIZE);
	fread(&mr->ver[2], sizeof(byte), 1, fp); // Malody Version
	fread(&mr->ver[1], sizeof(byte), 1, fp);
	fread(&mr->ver[0], sizeof(byte), 1, fp);
	fread(&n, sizeof(byte), 1, fp); // *unknown
	read_str(fp, mr->md5); // Chart md5
	read_str(fp, mr->diff); // Difficulty
	read_str(fp, mr->song); // Song Name
	read_str(fp, mr->author); // Song Author
	read_int(fp, &mr->score); // Score
	read_int(fp, &mr->combo); // Max Combo
	read_int(fp, &mr->best); // Best
	read_int(fp, &mr->cool); // Cool
	read_int(fp, &mr->good); // Good
	read_int(fp, &mr->miss); // Miss
	read_int(fp, &n); // *unknown
	read_int(fp, &mr->mods); // Mods
	read_int(fp, &n); // Judgement
    mr->judge = "ABCDE"[n];
	read_int(fp, &n); // *unknown
	read_int(fp, &n); // Time
    strcpy(str, ctime((time_t *)&n));
    str[strlen(str)-1] = 0; // ctime 返回的字符串自带换行符
    strcpy(mr->time, str);
}

void MalodyReplayInfo_print(MalodyReplayInfo *mr) {
	printf("Song Name \t| %s\n", mr->song);
	printf("Song Author \t| %s\n", mr->author);
	printf("Difficulty \t| %s\n", mr->diff);
	printf("Score \t\t| %d\n", mr->score);
	printf("Accuracy \t| %g%%\n", (mr->best*100+mr->cool*75+mr->good*40)/(double)(mr->best+mr->cool+mr->good+mr->miss));
	printf("Judgement \t| %c\n", mr->judge);
	printf("Max Combo \t| %d\n", mr->combo);
	printf("Best \t\t| %d\n", mr->best);
	printf("Cool \t\t| %d\n", mr->cool);
	printf("Good \t\t| %d\n", mr->good);
	printf("Miss \t\t| %d\n", mr->miss);
	printf("Mods \t\t| ");
	if (GET_BIT(mr->mods, 0)); // *unknown
	if (GET_BIT(mr->mods, 1)) printf("Luck ");
	if (GET_BIT(mr->mods, 2)) printf("Flip ");
	if (GET_BIT(mr->mods, 3)) printf("Const ");
	if (GET_BIT(mr->mods, 4)) printf("Dash ");
	if (GET_BIT(mr->mods, 5)) printf("Rush ");
	if (GET_BIT(mr->mods, 6)) printf("Hide ");
	if (GET_BIT(mr->mods, 7)); // *unknown
	if (GET_BIT(mr->mods, 8)) printf("Slow ");
	if (GET_BIT(mr->mods, 9)) printf("Death ");
	printf("\n");
	printf("Chart md5 \t| %s\n", mr->md5);
	printf("Time \t\t| %s\n", mr->time);
	printf("Malody Version \t| %d.%d.%d\n", mr->ver[0], mr->ver[1], mr->ver[2]);
}
