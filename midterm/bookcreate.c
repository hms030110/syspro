#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "db.dat"
#define MAX_STUDENT_COUNT 100
  
int main(int argc, char *argv[]){
      int fd;
      struct student record;
      if(argc< 2){
          fprintf(stderr, "How to use: %s file\n", argv[0]);
          exit(1);
      }
 
      if((fd= open(argv[1],O_WRONLY| O_CREAT| O_EXCL, 0640))== -1){
          perror(argv[1]);
          exit(2);
      }
 
      printf("%-2s %-8s %-6s %-4s %-11s %-6s\n", "id", "bookname", "author", "year", "numofborrow", "borrw");
      while(scanf("%d %s %s %d %d %s", &record.id, record.bookname, &record.author, &record.year, &record.numofborrow, &record.borrow)==6){
          lseek(fd,(record.id - START_ID)*sizeof(record), SEEK_SET);
          write(fd, (char *)&record, sizeof(record));
     }
      close(fd);
      exit(0);
  }

