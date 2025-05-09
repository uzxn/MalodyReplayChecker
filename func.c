#include <stdio.h>
#include <string.h>
#include <time.h>

#include "common.h"

// 删除文件名中的限制字符 (如斜杠, 星号等)
void delete_forbidden_character(char *str) {
  char *p = str;
  while (*p) {
    if (*p == '\\' || *p == '/' || *p == ':' || *p == '*' || *p == '?' ||
        *p == '\"' || *p == '<' || *p == '>' || *p == '|') {
      *p = ' ';
    }
    p++;
  }
}

// 从 fp 指向的 .mr 文件中读取一个整数
void read_int(FILE *fp, int *ptr) { fread(ptr, sizeof(int), 1, fp); }

// 从 fp 指向的 .mr 文件中读取一个字符串
void read_str(FILE *fp, char *str) {
  int len = 0;
  read_int(fp, &len);
  fread(str, sizeof(char), len, fp);
}

// 从 fp 指向的 .mr 文件中读取数据并保存到 mr 中
void MalodyReplayInfo_read(FILE *fp, MalodyReplayInfo *mr) {
  int n = 0;
  string str = {0};

  read_str(fp, str);                        // "mr format head"
  fread(&mr->ver[2], sizeof(byte), 1, fp);  // Malody Ver '07'
  fread(&mr->ver[1], sizeof(byte), 1, fp);  // Malody Ver '03'
  fread(&mr->ver[0], sizeof(byte), 1, fp);  // Malody Ver '04'
  fread(&n, sizeof(byte), 1, fp);           // Malody Ver '00'

  read_str(fp, mr->md5);     // Chart MD5
  read_str(fp, mr->diff);    // Difficulty
  read_str(fp, mr->song);    // Song Name
  read_str(fp, mr->author);  // Song Author

  read_int(fp, &mr->score);  // Score
  read_int(fp, &mr->combo);  // Max Combo
  read_int(fp, &mr->best);   // Best
  read_int(fp, &mr->cool);   // Cool
  read_int(fp, &mr->good);   // Good
  read_int(fp, &mr->miss);   // Miss
  read_int(fp, &n);          // *unknown
  read_int(fp, &mr->mods);   // Mods
  read_int(fp, &n);          // Judgement
  mr->judge = "ABCDE"[n];

  memset(str, 0, STR_SIZE);
  read_str(fp, str);  // "mr data"

  fread(&n, sizeof(byte), 4, fp);  // Malody Ver (the same as above)
  read_int(fp, &mr->hit);          // The Number of Hits
  fread(&n, sizeof(byte), 1, fp);  // *unknown

  read_int(fp, &n);  // Playing Time
  time_t time_num = n;
  struct tm *time_struct = localtime(&time_num);
  mr->time.year = 1900 + time_struct->tm_year;  // tm_year 为从 1900 年起的年数
  mr->time.month = 1 + time_struct->tm_mon;     // tm_mon 范围为 0~11
  mr->time.date = time_struct->tm_mday;
  mr->time.hour = time_struct->tm_hour;
  mr->time.minute = time_struct->tm_min;
  mr->time.second = time_struct->tm_sec;

  mr->acc = (mr->best * 100 + mr->cool * 75 + mr->good * 40)  // Accuracy
            / (double)(mr->best + mr->cool + mr->good + mr->miss);
}

// 将 mr 中的数据格式化输出到命令行
void MalodyReplayInfo_print(MalodyReplayInfo *mr) {
  printf(" Song Name \t| %s\n", mr->song);
  printf(" Song Author \t| %s\n", mr->author);
  printf(" Difficulty \t| %s\n", mr->diff);
  printf(" Score \t\t| %d\n", mr->score);
  printf(" Accuracy \t| %g%%\n", mr->acc);
  printf(" Judgement \t| %c\n", mr->judge);
  printf(" Max Combo \t| %d\n", mr->combo);
  printf(" Best \t\t| %d\n", mr->best);
  printf(" Cool \t\t| %d\n", mr->cool);
  printf(" Good \t\t| %d\n", mr->good);
  printf(" Miss \t\t| %d\n", mr->miss);
  printf(" Total Hit \t| %d\n", mr->hit);

  printf(" Mods \t\t| ");
  if (GET_BIT(mr->mods, 0)) printf("Fair ");
  if (GET_BIT(mr->mods, 1)) printf("Luck ");
  if (GET_BIT(mr->mods, 2)) printf("Flip ");
  if (GET_BIT(mr->mods, 3)) printf("Const ");
  if (GET_BIT(mr->mods, 4)) printf("Dash ");
  if (GET_BIT(mr->mods, 5)) printf("Rush ");
  if (GET_BIT(mr->mods, 6)) printf("Hide ");
  if (GET_BIT(mr->mods, 7)) printf("Origin ");
  if (GET_BIT(mr->mods, 8)) printf("Slow ");
  if (GET_BIT(mr->mods, 9)) printf("Death ");
  printf("\n");

  printf(" Chart MD5 \t| %s\n", mr->md5);
  printf(" Time \t\t| %04d-%02d-%02d %02d:%02d:%02d\n", mr->time.year,
         mr->time.month, mr->time.date, mr->time.hour, mr->time.minute,
         mr->time.second);
  printf(" Malody Ver \t| %d.%d.%d\n", mr->ver[0], mr->ver[1], mr->ver[2]);
}

// 将 mr 中的数据写入到 fp 指向的 .csv 表格文件中
void MalodyReplayInfo_write_csv(FILE *fp, MalodyReplayInfo *mr) {
  fprintf(fp, "=\"%s\",", mr->song);
  fprintf(fp, "=\"%s\",", mr->author);
  fprintf(fp, "=\"%s\",", mr->diff);
  fprintf(fp, "%d,", mr->score);
  fprintf(fp, "%g%%,", mr->acc);
  fprintf(fp, "=\"%c\",", mr->judge);
  fprintf(fp, "%d,", mr->combo);
  fprintf(fp, "%d,", mr->best);
  fprintf(fp, "%d,", mr->cool);
  fprintf(fp, "%d,", mr->good);
  fprintf(fp, "%d,", mr->miss);
  fprintf(fp, "%d,", mr->hit);

  fprintf(fp, "=\"");
  if (GET_BIT(mr->mods, 0)) fprintf(fp, "Fair ");
  if (GET_BIT(mr->mods, 1)) fprintf(fp, "Luck ");
  if (GET_BIT(mr->mods, 2)) fprintf(fp, "Flip ");
  if (GET_BIT(mr->mods, 3)) fprintf(fp, "Const ");
  if (GET_BIT(mr->mods, 4)) fprintf(fp, "Dash ");
  if (GET_BIT(mr->mods, 5)) fprintf(fp, "Rush ");
  if (GET_BIT(mr->mods, 6)) fprintf(fp, "Hide ");
  if (GET_BIT(mr->mods, 7)) fprintf(fp, "Origin ");
  if (GET_BIT(mr->mods, 8)) fprintf(fp, "Slow ");
  if (GET_BIT(mr->mods, 9)) fprintf(fp, "Death ");
  fprintf(fp, "\",");

  fprintf(fp, "=\"%s\",", mr->md5);
  fprintf(fp, "=\"%04d-%02d-%02d %02d:%02d:%02d\",", mr->time.year,
          mr->time.month, mr->time.date, mr->time.hour, mr->time.minute,
          mr->time.second);
  fprintf(fp, "=\"%d.%d.%d\"", mr->ver[0], mr->ver[1], mr->ver[2]);
  fprintf(fp, "\n");
}
