Q1 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void printFileInfo(const char *filename) {
    struct stat statBuf;

    // Get file information
    if (stat(filename, &statBuf) == -1) {
        perror("stat");
        return;
    }

    // Print file type and inode number
    printf("File: %s\n", filename);
    printf("File Type: ");
    
    switch (statBuf.st_mode & S_IFMT) {
        case S_IFREG:
            printf("Regular File\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFLNK:
            printf("Symbolic Link\n");
            break;
        default:
            printf("Other\n");
            break;
    }

    printf("Inode Number: %lu\n", (unsigned long)statBuf.st_ino);
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; ++i) {
        printFileInfo(argv[i]);
    }

    return 0;
}


Q1

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
File type: Regular file
Inode number: 8520972
*/


Q2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void child_handler(int signo) {
    if (signo == SIGCHLD) {
        printf("Child process terminated.\n");
        exit(EXIT_SUCCESS);
    }
}

void alarm_handler(int signo) {
    if (signo == SIGALRM) {
        printf("Timeout: Child process taking too long. Killing it.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        execvp(argv[1], &argv[1]); // Execute the command
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        signal(SIGCHLD, child_handler); // Set signal handler for child termination
        signal(SIGALRM, alarm_handler); // Set signal handler for alarm

        // Set an alarm for 5 seconds
        alarm(5);

        // Wait for the child process to terminate
        wait(NULL);

        // Disable the alarm
        alarm(0);

        printf("Parent process exiting.\n");
    }

    return 0;
}

