#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"

int main(int argc, char **argv) {
  argc--, argv++;
  printf(
      "Export to Excel - MalodyReplayChecker v0.4.0\n"
      "\n");

  if (argc == 0) {
    printf(
        "Drag .mr files into this program to export their info as .csv file!\n"
        "\n"
        "Do not directly double-click to open this program!\n"
        "\n"
        "You can now press any key to exit.\n");
    system("pause > nul");
    return 0;
  }

  MalodyReplayInfo mr;
  FILE *fp_in = NULL, *fp_out = NULL;
  memset(&mr, 0, sizeof(mr));

  if (fopen("export.csv", "r") != NULL) {
    error(
        "The file 'export.csv' already exists.\n"
        "\n");
  }

  else {
    fp_out = fopen("export.csv", "w");
    fprintf(fp_out,
            "=\"File\",=\"Song Name\",=\"Song "
            "Author\",=\"Difficulty\",=\"Score\",=\"Accuracy\",=\"Judgement\",="
            "\"Max Combo\",=\"Best\",=\"Cool\",=\"Good\",=\"Miss\",=\"Total "
            "Hit\",=\"Mods\",=\"Chart MD5\",=\"Time\",=\"Malody Ver\"\n");

    for (int i = 0; i < argc; i++) {
      fp_in = fopen(argv[i], "rb");
      if (fp_in == NULL) {
        error("Can not open this file: %s\n", argv[i]);
      }

      else if (strncmp(argv[i] + strlen(argv[i]) - 3, ".mr", 3) != 0) {
        error("This is not Malody replay file: %s\n", argv[i]);
      }

      else {
        printf("Processing: %s\n", argv[i]);
        fprintf(fp_out, "=\"%s\",", argv[i]);
        memset(&mr, 0, sizeof(mr));
        MalodyReplayInfo_read(fp_in, &mr);
        MalodyReplayInfo_write_csv(fp_out, &mr);
        fclose(fp_in);
      }

      printf("\n");
    }

    fclose(fp_out);
    printf(
        "Done.\n"
        "\n");
  }

  printf("You can now press any key to exit.\n");
  system("pause > nul");
  return 0;
}
