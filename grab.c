#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main(int argc, char *argv[]) {
  const char *file = NULL;
  const char *pattern = ""; // Default pattern

  if (argc < 2) {
    fprintf(stdout, "Usage: %s [file] [pattern]\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  file = argv[1];
  if (argc >= 3) {
    pattern = argv[2];
  }

  FILE *stream = fopen(file, "r");
  if (!stream) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t size = 0;
  ssize_t nread;

  while ((nread = getline(&line, &size, stream)) != -1) {
    if (strlen(pattern) == 0) {
      fputs(line, stdout);
    } else {
      char *cursor = line;
      char *match;
      size_t pattern_len = strlen(pattern);

      while ((match = strstr(cursor, pattern)) != NULL) {
        fwrite(cursor, 1, match - cursor, stdout);
        printf(ANSI_COLOR_RED);
        fwrite(match, 1, pattern_len, stdout);
        printf(ANSI_COLOR_RESET);
        cursor = match + pattern_len;
      }

      fputs(cursor, stdout); // print the rest of the line
    }
  }

  free(line);
  fclose(stream);
  return 0;
}
