#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define READ 0
#define WRITE 1

char* cap(char* s, int size){
  int h;
  for(int i=0;i<size;i++){
    h=s[i];
    if(isalpha(s[i])){
      if(h>96){h=h-32;}else{h=h+32;}
    }
    s[i]=h;
  }
  return s;
}

int main(){
  char s[50];
  int fds[2];
  int fds2[2];
  pipe(fds);
  pipe(fds2);
  int f=fork();
  if(f){
    while(1){
      close(fds[READ]);
      close(fds2[WRITE]);
      printf("Enter a string:");
      fgets(s, 50, stdin);
      write(fds[WRITE], s, sizeof(s));
      read(fds2[READ], s, sizeof(s));
      printf("Edited String: %s\n",s);
    }
  }else{
    while(1){
      close(fds[WRITE]);
      close(fds2[READ]);
      read(fds[READ], s, sizeof(s));
      write(fds2[WRITE], cap(s, sizeof(s)), sizeof(s));
    }
  }
  return 0;
}
