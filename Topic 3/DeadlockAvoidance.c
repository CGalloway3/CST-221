#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

typedef int semaphore;
  semaphore memory;
  semaphore disk;
  semaphore printer;

void forkProcessOne(){
  if ( fork() == 0 ){
    printf("Process one starting");
    down(&memory);
    printf("Memory locked");
    up(&memory);
  }
  else {
    printf("_____I am the parent");
  }
}

void forkProcessTwo(){
  if ( fork() == 0 ){
    printf("Process Two starting");
    down(&memory);
    printf("Disk locked");
    up(&memory);
  }
  else {
    printf("_____I am the parent");
  }
}

void forkProcessThree(){
  if ( fork() == 0 ){
    printf("Process Three starting");
    down(&memory);
    printf("Printer locked");
    up(&memory);
  }
  else {
    printf("_____I am the parent");
  }
}

int main(){
  forkProcessOne();
  forkProcessTwo();
  ForkProcessthree();
}
