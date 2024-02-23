#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "common.h"

int main(int argc, char **argv) {
  argc--, argv++;
  if (argc == 0) {
    printf(HELP_INFO);
    return 0;
  }

  // csv 命令: 将回放信息写入 .csv 文件
  if (strcmp(argv[0], "csv") == 0) {
    if (argc < 3) {
      error("Crazy arguments\n");
      return 0;
    }
    FILE *fp_out = fopen(argv[1], "w");
    fprintf(fp_out,
        "=\"File Name\",=\"Song Name\",=\"Song Author\",=\"Difficulty\",=\"Score\","
        "=\"Accuracy\",=\"Judgement\",=\"Max Combo\",=\"Best\",=\"Cool\",=\"Good\",=\"Miss\","
        "=\"Mods\",=\"Chart md5\",=\"Time\",=\"Malody Ver\"\n");
    for (int i = 2; i < argc; i++) {
      FILE *fp_in = fopen(argv[i], "rb");
      if (fp_in == NULL) {
        error("File not found: %s\n", argv[i]);
        continue;
      }
      printf("Current file: %s\n", argv[i]);
      fprintf(fp_out, "=\"%s\",", argv[i]);
      MalodyReplayInfo mr;
      memset(&mr, 0, sizeof(mr));
      MalodyReplayInfo_read(fp_in, &mr);
      MalodyReplayInfo_write_csv(fp_out, &mr);
      fclose(fp_in);
    }
    printf("All finished\n");
    fclose(fp_out);
    return 0;
  }

  // name 命令: 输出回放文件的格式化文件名
  if (strcmp(argv[0], "name") == 0) {
    if (argc < 2) {
      error("Crazy arguments\n");
      return 0;
    }
    for (int i = 1; i < argc; i++) {
      FILE *fp = fopen(argv[i], "rb");
      if (fp == NULL) {
        error("File not found: %s\n", argv[i]);
        continue;
      }
      printf("Current file: %s\n", argv[i]);
      MalodyReplayInfo mr;
      memset(&mr, 0, sizeof(mr));
      MalodyReplayInfo_read(fp, &mr);
      fclose(fp);
      printf(" -> %s_%s_%c%.2lf.mr\n", mr.song, mr.diff, mr.judge, mr.acc);
    }
    return 0;
  }

  // rename 命令: 重命名回放文件
  if (strcmp(argv[0], "rename") == 0) {
    if (argc < 2) {
      error("Crazy arguments\n");
      return 0;
    }
    for (int i = 1; i < argc; i++) {
      FILE *fp = fopen(argv[i], "rb");
      if (fp == NULL) {
        error("File not found: %s\n", argv[i]);
        continue;
      }
      printf("Current file: %s\n", argv[i]);
      MalodyReplayInfo mr;
      memset(&mr, 0, sizeof(mr));
      MalodyReplayInfo_read(fp, &mr);
      fclose(fp);
      string new_name = {0};
      sprintf(new_name, "%s_%s_%c%.2lf.mr", mr.song, mr.diff, mr.judge, mr.acc);
      printf("  -> %s\n", new_name);
      if (rename(argv[i], new_name) != 0) {
        error("%s\n", strerror(errno));
      }
    }
    printf("All finished\n");
    return 0;
  }

  // 无命令: 输出回放信息
  for (int i = 0; i < argc; i++) {
    FILE *fp = fopen(argv[i], "rb");
    if (fp == NULL) {
      error("File not found: %s\n", argv[i]);
      continue;
    }
    printf("----------------+------------------------------------------------\n");
    printf(" File Name \t| %s\n", argv[i]);
    printf("----------------+------------------------------------------------\n");
    MalodyReplayInfo mr;
    memset(&mr, 0, sizeof(mr));
    MalodyReplayInfo_read(fp, &mr);
    MalodyReplayInfo_print(&mr);
    if (i+1 == argc) {
      printf("----------------+------------------------------------------------\n");
    }
    fclose(fp);
  }

  return 0;
}
