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
int finalPosCount = 0;
int finalNegCount = 0;

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
		//write(0,posWordArray[words-1],count);
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
		//write(0,negWordArray[words-1],count);
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
 char word[20];
 char filteredWord[20];
 int noOfChars = 0;
 words=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allLines[i];
	 if(allLines[i]==' ')
	{
		words++;
		for(noOfChars = 0;noOfChars<count; noOfChars++)
			filteredWord[noOfChars]=word[noOfChars];
		reviewWordArray[words-1]=malloc(20);
		strcpy(reviewWordArray[words-1], filteredWord);
		//printf(1,"word : %s  %d\n",reviewWordArray[words-1],count+5);
		count = 0;
		reviewCount++;
		memset(filteredWord,' ',20);
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
  int j =0;
  int pos = 0;
  int neg = 0;
  for (j=0;j<reviewCount;j++)
	printf(1,"word _%s\n_",reviewWordArray[j]);
  for(j=0;j<posWordCount;j++)
	printf(1,"pos _%s\n_",posWordArray[j]);

			
  for(j = 0;j<reviewCount;j++)
  {
	  //printf(1,"word : %s \n",reviewWordArray[j]);
	  for(pos=0;pos<posWordCount;pos++)
	  {
		  if(strcmp(reviewWordArray[j],posWordArray[pos])==0)
				  finalPosCount++;

	  }
	  for(neg=0;neg<negWordCount;neg++)
	  {
	  	if(strcmp(reviewWordArray[j],negWordArray[neg])==0)
				finalNegCount++;
	  }
  }
  printf(1,"Pos word count %d \n",finalPosCount);
  printf(1,"Neg word count %d \n",finalNegCount);
  printf(1,"Review word count %d",reviewCount);
  exit();
}
