#include "types.h"
#include "stat.h"
#include "user.h"
#include<stddef.h>
#include "fcntl.h"

char buf[512];
char* posWordArray[500];
char* negWordArray[500];
char* reviewWordArray[500];
int posWordCount = 0;
int negWordCount = 0;
int reviewCount = 0;
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
		posWordCount++;
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
		negWordCount++;
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
		reviewCount++;
	}
 }
}

int main(int argc, char *argv[])
{
  int fd;
  if(argc <= 1){
	  printf(1,"Please provide three files",40);
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
 	printf(1, "cannot open %s", argv[3]);
     	exit();
  }
  readPosFile(fd);
  close(fd);

  //char length[2];
  //sprintf(length,"%d\n",len);
  printf(1,"Pos word count %d",posWordCount);
  printf(1,"Neg word count %d",negWordCount);
  printf(1,"Review word count %d",reviewCount);
  exit();
}
