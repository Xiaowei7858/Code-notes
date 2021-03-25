#include"proc.h"

void proc(){
  //清空
  char bar[NUM]; 
  memset(bar,'\0',sizeof(bar));

  //循环 
  int i = 0;
  // \有特殊用途
  const char *lable = "|/-\\";
  while(i < 100){
    fflush(stdout);
    bar[i++] = '#';
    usleep(100000);
    //默认的格式对齐是右对齐的
    //比率需要2个%%
    printf("[%-100s][%3d%%][%c]\r",bar,i,lable[i%4]);
  }
  printf("\n");
}

