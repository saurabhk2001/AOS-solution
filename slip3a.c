#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  struct stat sb;

  if(argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  if(stat(argv[1], &sb) == -1) {
    perror("stat");
    return 1;
  }

  printf("File type: ");

  switch(sb.st_mode & S_IFMT) {
    case S_IFBLK:  
      printf("Block device\n");           
      break;
    case S_IFCHR:  
       printf("Character device\n");
       break;
    case S_IFDIR:  
       printf("Directory\n");
       break;
    case S_IFIFO:  
       printf("FIFO/pipe\n");        
       break;
    case S_IFLNK:  
       printf("Symlink\n");         
       break;
    case S_IFREG:  
       printf("Regular file\n");             
       break;
    case S_IFSOCK:  
       printf("Socket\n");           
        break;
    default:        
       printf("Unknown?\n");              
       break;
  }

  printf("Inode number: %ld\n", (long) sb.st_ino);

  return 0;  
}

/*
lab4@lab4-HP-Desktop-Pro-G2:~/Desktop/AOS$ gcc slip3a.c
lab4@lab4-HP-Desktop-Pro-G2:~/Desktop/AOS$ ./a.out slip1a.c
File type: Regular file
Inode number: 8520972
*/
