#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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

    printf("File read success\n");
    printf("Total Line : %d\n", line_count);
    printf("You can choose 1 ~ %d Line\n", line_count);
    printf("Pls 'Enter' the line to select : ");

    char input[50];
    scanf("%s", input);

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < line_count; i++) {
            printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start - 1; i < end && i < line_count; i++) {
            printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int idx = atoi(token) - 1;
            if (idx >= 0 && idx < line_count) {
                printf("%s\n", savedText[idx]);
            }
            token = strtok(NULL, ",");
        }
    } 
    else {
        int idx = atoi(input) - 1;
        if (idx >= 0 && idx < line_count) {
            printf("%s\n", savedText[idx]);
        }
    }

    return 0;
}
