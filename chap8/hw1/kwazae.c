#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "사용법: %s [-e [환경변수이름] | -u | -g | -i | -p]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            char **ptr;
            for (ptr = environ; *ptr != NULL; ptr++) {
                printf("%s\n", *ptr);
            }
        } else {
            char *val = getenv(argv[2]);
            if (val != NULL) {
                printf("%s=%s\n", argv[2], val);
            } else {
                printf("%s: 해당 환경변수가 존재하지 않습니다.\n", argv[2]);
            }
        }
    }
    else if (strncmp(argv[1], "-e", 2) == 0 && strlen(argv[1]) > 2) {
        char *env_name = argv[1] + 2;
        char *val = getenv(env_name);
        if (val != NULL) {
            printf("%s=%s\n", env_name, val);
        } else {
            printf("%s: 해당 환경변수가 존재하지 않습니다.\n", env_name);
        }
    }
    else if (strcmp(argv[1], "-u") == 0) {
        uid_t ruid = getuid();
        uid_t euid = geteuid();
        struct passwd *rpw = getpwuid(ruid);
        struct passwd *epw = getpwuid(euid);

        printf("My Realistic User ID : %d(%s)\n", ruid, rpw ? rpw->pw_name : "unknown");
        printf("My Valid User ID : %d(%s)\n", euid, epw ? epw->pw_name : "unknown");
    }
    else if (strcmp(argv[1], "-g") == 0) {
        gid_t rgid = getgid();
        gid_t egid = getegid();
        struct group *rgr = getgrgid(rgid);
        struct group *egr = getgrgid(egid);

        printf("My Realistic Group ID : %d(%s)\n", rgid, rgr ? rgr->gr_name : "unknown");
        printf("My Valid Group ID : %d(%s)\n", egid, egr ? egr->gr_name : "unknown");
    }
    else if (strcmp(argv[1], "-i") == 0) {
        printf("my process number : [%d]\n", getpid());
    }
    else if (strcmp(argv[1], "-p") == 0) {
        printf("my parent's process number : [%d]\n", getppid());
    }
    else {
        fprintf(stderr, "지원하지 않는 옵션입니다: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
