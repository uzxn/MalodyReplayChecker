#ifndef _COMMON_H
#define _COMMON_H

#define STR_SIZE      (1024)
#define GET_BIT(x,n)  (((x) & (1<<n)) >> n)
#define error(...)    fprintf(stderr, "[ERROR] "__VA_ARGS__)
#define HELP_INFO\
  "mr - MalodyReplayChecker v0.2.0\n"\
  "Usage: mr [command] [output-file.csv] <replay-file(s).mr ...>\n"\
  "Command: \n"\
  "    (none)    output the replay information to the screen\n"\
  "    rename    rename the replay files to the formatted name\n"\
  "    name      output the formatted file name to the screen\n"\
  "    csv       write the replay information to output-file.csv\n"\
  "              in CSV format that can be opened with Excel\n"\
  "See github.com/uzxn/MalodyReplayChecker for more information\n"

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
  double acc; // 非文件内容, 由程序计算得出
  int miss;
  int mods;
  char judge;
  string time;
} MalodyReplayInfo;

// 从 fp 指向的 .mr 文件中读取一个整数
void read_int(FILE *fp, int *var);
// 从 fp 指向的 .mr 文件中读取一个字符串
void read_str(FILE *fp, char *str);
// 从 fp 指向的 .mr 文件中读取数据并保存到 mr 中
void MalodyReplayInfo_read(FILE *fp, MalodyReplayInfo *mr);
// 将 mr 中的数据格式化输出到命令行
void MalodyReplayInfo_print(MalodyReplayInfo *mr);
// 将 mr 中的数据写入到 fp 指向的 .csv 表格文件中
void MalodyReplayInfo_write_csv(FILE *fp, MalodyReplayInfo *mr);

#endif /* common.h */
