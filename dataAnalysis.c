#include "types.h"
#include "stat.h"
#include "user.h"
#include<stddef.h>
#include "fcntl.h"

char buf[512];
char* posWordArray[500];
char* negWordArray[500];
char* reviewWordArray[500];
void readPosFile(int fd)
{
  int i,n,count,words;
  count=0;
  char* allPosLines = malloc(500);
  memset(buf, 0,512);
  while((n = read(fd, buf, sizeof(buf))) > 0){
      	strcpy(allPosLines,buf);	      
  }

 int len= strlen(allPosLines);
 char *word = malloc(500);
 words=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allPosLines[i];
	 if(allPosLines[i]=='\n')
	{
		words++;
		posWordArray[words-1] = word;
		write(0,posWordArray[words-1],count);
		count = 0;
	}
 }
}
void readNegFile(int fd)
{
  int i,n,count,words;
  count=0;
  char* allLines = malloc(500);
  while((n = read(fd, buf, sizeof(buf))) > 0){
      	strcpy(allLines,buf);	      
    }

 int len = strlen(allLines);
 char *word = malloc(500);
 words=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allLines[i];
	 if(allLines[i]=='\n')
	{
		words++;
		negWordArray[words-1] = word;
		write(0,negWordArray[words-1],count);
		count = 0;
	}
 }
}
void readReviewFile(int fd)
{
  int i,n,count,words;
  count=0;
  char* allLines = malloc(500);
  while((n = read(fd, buf, sizeof(buf))) > 0){
      	strcpy(allLines,buf);	      
    }

 int len = strlen(allLines);
 char *word = malloc(500);
 words=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allLines[i];
	 if(allLines[i]==' ')
	{
		words++;
		reviewWordArray[words-1] = word;
		write(0,reviewWordArray[words-1],count);
		count = 0;
	}
 }
}

int main(int argc, char *argv[])
{
  int fd, i;
  if(argc <= 1){
	  printf(1,"bye",4);
    	exit();
  }
if((fd = open(argv[1],0)) < 0){
 	printf(1, "cannot open %s", argv[1]);
     	exit();
  }
  readReviewFile(fd);
  close(fd);
if((fd = open(argv[2],0)) < 0){
 	printf(1, "cannot open %s", argv[2]);
     	exit();
  }
  readNegFile(fd);
  close(fd);

 if((fd = open(argv[3],0)) < 0){
 	printf(1, "cannot open %s", argv[i]);
     	exit();
  }
  readPosFile(fd);
  close(fd);
  int len = sizeof(posWordArray)/sizeof(posWordArray[0]);
  char length[2];
  sprintf(length,"%d\n",len);
  write(0,length,2);
  exit();
}
