#include "types.h"
#include "stat.h"
#include "user.h"
#include<stddef.h>
char buf[512];
char* posWordArray[100];
char* negWordArray[100];
char* reviewWordArray[10000];
void readFile(int fd, int type)
{
  int i,n,count,words;
  count=0;
  char* allLines = malloc(10000);
  while((n = read(fd, buf, sizeof(buf))) > 0){
      	strcpy(allLines,buf);	      
    }
 char* fileWords[10000];

 int len = strlen(allLines);
 char *word = malloc(100);
 words=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allLines[i];
	 if(allLines[i]=='\n')
	{
		words++;
		fileWords[words-1] = word;
		write(0,fileWords[words-1],count);
		count = 0;
	}
 }
 if(type == 1)
	 *reviewWordArray = *fileWords;
 else if(type ==2 )
	 *posWordArray = *fileWords;
 else if(type ==3)
	 *negWordArray = *fileWords;
}

int main(int argc, char *argv[])
{
  int fd, i;
  if(argc <= 1){
	  printf(1,"bye",4);
    	exit();
  }
  for(i = 1; i < argc; i++){
   	 if((fd = open(argv[i],0)) < 0){
     	 	printf(1, "cannot open %s", argv[i]);
     	 	exit();
	 }
    	readFile(fd,i);
   }
  close(fd);
  exit();
}
