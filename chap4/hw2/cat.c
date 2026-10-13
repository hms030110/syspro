#include <stdio.h>
#include <string.h>

void file_cat(FILE *fp, int line_num_flag, int *line_count) {
    int c;

    if (line_num_flag && *line_count == 0) {
        printf("%6d  ", ++(*line_count));
    }

    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
        if (line_num_flag && c == '\n') {
            printf("%6d  ", ++(*line_count));
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    int i = 1;
    int line_num_flag = 0;
    int line_count = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        line_num_flag = 1;
        i = 2;
    }

    if (i >= argc) {
        file_cat(stdin, line_num_flag, &line_count);
        return 0;
    }

    for (; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
            continue;
        }
        file_cat(fp, line_num_flag, &line_count);
        fclose(fp);
    }

    return 0;
}
