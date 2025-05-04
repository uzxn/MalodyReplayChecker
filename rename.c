#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"

int main(int argc, char **argv) {
  argc--, argv++;
  printf(
      "Rename - MalodyReplayChecker v0.4.0\n"
      "\n");

  if (argc == 0) {
    printf(
        "Drag .mr files into this program to normalize their file names!\n"
        "\n"
        "Do not directly double-click to open this program!\n"
        "\n"
        "You can now press any key to exit.\n");
    system("pause > nul");
    return 0;
  }

  FILE *fp = NULL;
  MalodyReplayInfo mr;
  string new_name = {0};
  memset(&mr, 0, sizeof(mr));

  for (int i = 0; i < argc; i++) {
    fp = fopen(argv[i], "rb");
    if (fp == NULL) {
      error("Can not open this file: %s\n", argv[i]);
    }

    else if (strncmp(argv[i] + strlen(argv[i]) - 3, ".mr", 3) != 0) {
      error("This is not Malody replay file: %s\n", argv[i]);
    }

    else {
      printf("Renaming: %s\n", argv[i]);
      memset(&mr, 0, sizeof(mr));
      MalodyReplayInfo_read(fp, &mr);
      fclose(fp);

      memset(new_name, 0, sizeof(new_name));
      sprintf(new_name, "%04d-%02d-%02d_%s_%s_%c%.2lf.mr", mr.time.year,
              mr.time.month, mr.time.date, mr.song, mr.diff, mr.judge, mr.acc);
      delete_forbidden_character(new_name);

      if (rename(argv[i], new_name) != 0) {
        error("%s.\n", strerror(errno));
      } else {
        printf("  -> %s\n", new_name);
      }
    }

    printf("\n");
  }

  printf(
      "Done.\n"
      "\n"
      "You can now press any key to exit.\n");
  system("pause > nul");
  return 0;
}
