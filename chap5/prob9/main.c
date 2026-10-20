#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 10
#define MAX_LEN 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("File open error");
        exit(1);
    }

    char savedText[MAX_LINES][MAX_LEN];
    int line_count = 0;
    int col = 0;
    char buf;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line_count][col] = '\0';
            line_count++;
            col = 0;
        } else {
            savedText[line_count][col++] = buf;
        }
    }
    close(fd);

    for (int i = line_count - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    return 0;
}
