#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

void print_file_info(const char *dir_path, struct dirent *d, int opt_i, int opt_p, int opt_Q) {
    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dir_path, d->d_name);

    struct stat st;
    if (lstat(fullpath, &st) < 0) {
        perror("lstat error");
        return;
    }

    printf("%4ld ", st.st_blocks / 2);

    if (opt_i) {
        printf("%10lu ", (unsigned long)st.st_ino);
    }

    printf("%c", S_ISDIR(st.st_mode) ? 'd' :
                 S_ISLNK(st.st_mode) ? 'l' :
                 S_ISCHR(st.st_mode) ? 'c' :
                 S_ISBLK(st.st_mode) ? 'b' :
                 S_ISFIFO(st.st_mode) ? 'p' :
                 S_ISSOCK(st.st_mode) ? 's' : '-');
    printf("%c", (st.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (st.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (st.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (st.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (st.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (st.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (st.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (st.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c ", (st.st_mode & S_IXOTH) ? 'x' : '-');

    struct passwd *pw = getpwuid(st.st_uid);
    struct group  *gr = getgrgid(st.st_gid);
    printf("%2ld %s %s %8ld ", (long)st.st_nlink,
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown",
           (long)st.st_size);

    struct tm *tm = localtime(&st.st_mtime);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm);
    printf("%s ", timebuf);

    if (opt_Q) {
        if (opt_p && S_ISDIR(st.st_mode)) {
            printf("\"%s/\"\n", d->d_name);
        } else {
            printf("\"%s\"\n", d->d_name);
        }
    } else {
        if (opt_p && S_ISDIR(st.st_mode)) {
            printf("%s/\n", d->d_name);
        } else {
            printf("%s\n", d->d_name);
        }
    }
}

int main(int argc, char *argv[]) {
    int opt_i = 0, opt_p = 0, opt_Q = 0;
    char *dir_path = ".";

    int opt;
    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
            case 'i': opt_i = 1; break;
            case 'p': opt_p = 1; break;
            case 'Q': opt_Q = 1; break;
            default:
                break;
        }
    }

    if (optind < argc) {
        dir_path = argv[optind];
    }

    DIR *dp = opendir(dir_path);
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }

    struct dirent *d;
    while ((d = readdir(dp)) != NULL) {
        print_file_info(dir_path, d, opt_i, opt_p, opt_Q);
    }

    closedir(dp);
    return 0;
}
