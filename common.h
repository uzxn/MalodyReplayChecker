#ifndef _COMMON_H
#define _COMMON_H

// 字符串最大长度
#define STR_SIZE (1024)
// 获取 x 的右起第 n 位二进制位
#define GET_BIT(x, n) (((x) >> (n)) & 1)
// 输出报错信息到 stderr 并在开头添加 "[ERROR] "
#define error(...) fprintf(stderr, "[ERROR] "__VA_ARGS__)

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
  double acc;  // 非从文件读取, 由程序计算得出
  int miss;
  int mods;
  char judge;
  int hit;
  struct {
    int year;    // 公历年份
    int month;   // 月份
    int date;    // 一月中的第几天 (日期)
    int hour;    // 小时
    int minute;  // 分钟
    int second;  // 秒
  } time;        // 游玩时间
} MalodyReplayInfo;

// 删除文件名中的限制字符 (如斜杠, 星号等)
void delete_forbidden_character(char *str);
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
