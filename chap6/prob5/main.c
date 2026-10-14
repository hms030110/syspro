#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

struct file_info {
    char name[NAME_MAX + 1];
    struct stat st;
};

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*);
int compare(const void *a, const void *b);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct dirent *d;
    char path[BUFSIZ+1];
    struct file_info *files = NULL;
    int count = 0;

    if (argc == 1)
        dir = ".";
    else dir = argv[1];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        files = realloc(files, sizeof(struct file_info) * (count + 1));
        strcpy(files[count].name, d->d_name);
        if (lstat(path, &files[count].st) < 0) {
            perror(path);
        } else {
            count++;
        }
    }
    closedir(dp);

    qsort(files, count, sizeof(struct file_info), compare);

    for (int i = 0; i < count; i++) {
        sprintf(path, "%s/%s", dir, files[i].name);
        printStat(path, files[i].name, &files[i].st);
    }
    free(files);

    exit(0);
}

int compare(const void *a, const void *b)
{
    const struct file_info *fa = (const struct file_info *)a;
    const struct file_info *fb = (const struct file_info *)b;
    if (fa->st.st_blocks < fb->st.st_blocks) return -1;
    if (fa->st.st_blocks > fb->st.st_blocks) return 1;
    return 0;
}

void printStat(char *pathname, char *file, struct stat *st) 
{
    printf("%5d ", (int)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3d ", (int)st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9d ", (int)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime)+4);
    printf("%s\n", file);
}

char type(mode_t mode) 
{
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
       return('s');
    return('?');
}

char* perm(mode_t mode) 
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i=0; i < 3; i++) {
        if (mode & (S_IRUSR >> i*3))
            perms[i*3] = 'r';
        if (mode & (S_IWUSR >> i*3))
           perms[i*3+1] = 'w';
        if (mode & (S_IXUSR >> i*3))
           perms[i*3+2] = 'x';
    }
    return(perms);
}
