   #include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include <fcntl.h>
   #include "student.h"
  
   int main(int argc, char *argv[]){
       int fd, id;
       int d;
      struct student record;
 
      if(argc<2){
          fprintf(stderr, "How to use : %s file\n", argv[0]);
          exit(1);
      }
      if((fd= open(argv[1], O_RDONLY))==-1){
          perror(argv[1]);
          exit(2);
      }
      do{
          printf("\Enter StudentID to search:");
          if (scanf("%d", &id)==1){
              lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
              if((read(fd, (char *)&record, sizeof(record))>0)&&(record.id != 0))
                      printf("id bookname author year numofborrow borrow\n %d %s %d %s %s %d", record.id, record.bookname,record.author, record.year, record.numofborrow, record.borrow);
              else printf("Record %d Null\n", id);
          }else printf("Input Error");
          printf("0: list of all books, 1: list of available books");
          scanf(" %d", &d);
      }while(c== '1');
      close(fd);
   exit(0);
}

