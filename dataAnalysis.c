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
 char word[20];
 words=0;
 int noOfChar=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allPosLines[i];
	 if(allPosLines[i]=='\n')
	{
		char *str = (char *)malloc(sizeof(char)*count);
		words++;
		for(noOfChar=0;noOfChar<count;noOfChar++)
			*(str+noOfChar)=word[noOfChar];
		*(str+count-1)='\0';
		posWordArray[words-1]=malloc(count);
		//write(0,posWordArray[words-1],count);
		strcpy(posWordArray[words-1],str);
		count = 0;
		posWordCount++;
	}
 }
}
void readNegFile(int fd)
{
  int i,n,count,words;
  count=0;
  char* allNegLines = malloc(500);
  memset(buf,0,512);
  while((n = read(fd, buf, sizeof(buf))) > 0){
      	strcpy(allNegLines,buf);	      
    }

 int len = strlen(allNegLines);
 char word[20];
 words=0;
 int noOfChar=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allNegLines[i];
	 if(allNegLines[i]=='\n')
	{	
		char*str = (char *)malloc(sizeof(char)*count);
		words++;
		for(noOfChar=0;noOfChar<count;noOfChar++)
			*(str+noOfChar)=word[noOfChar];
		*(str+count-1)='\0';
		negWordArray[words-1] = malloc(count);
		//write(0,negWordArray[words-1],count);
		strcpy(negWordArray[words-1],str);
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
 int noOfChars = 0;
 words=0;
 for(i=0;i<len;i++)
 {
	 word[count++]=allLines[i];
	 if(!((allLines[i] >= 'a' && allLines[i] <= 'z') || (allLines[i] >= 'A' && allLines[i] <= 'Z')))
	{
		char *str = (char *)malloc(sizeof(char)*count);
		words++;
		for(noOfChars = 0;noOfChars<count; noOfChars++)
			*(str+noOfChars)=word[noOfChars];
		*(str+count-1)='\0';
		reviewWordArray[words-1]=malloc(count);
		strcpy(reviewWordArray[words-1], str);
		//printf(1,"word : %s  %d\n",reviewWordArray[words-1],count+5);
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
  int j =0;
  int pos = 0;
  int neg = 0;
 /* for (j=0;j<reviewCount;j++)
	printf(1,"word :%s\n",reviewWordArray[j]);
  for(j=0;j<posWordCount;j++)
	printf(1,"pos :%s\n",posWordArray[j]);
*/
  for(j = 0;j<reviewCount;j++)
  {
	  //printf(1,"word : %s \n",reviewWordArray[j]);
	  for(pos=0;pos<posWordCount;pos++)
	  {	  
		  //printf(1,"word is _%s_",posWordArray[pos]);
		  //printf(1,"review is _%s_",reviewWordArray[j]);
		  if(strcmp(reviewWordArray[j],posWordArray[pos])==0)
		  {
				  finalPosCount++;
				  printf(1, "Pos Word _%s_\n",posWordArray[pos]);
		  }

	  }
	  for(neg=0;neg<negWordCount;neg++)
	  {
	  	if(strcmp(reviewWordArray[j],negWordArray[neg])==0)
		{
				finalNegCount++;
				printf(1,"Neg Word_%s_\n",negWordArray[neg]);
		}		
	  }
  }
  printf(1,"Pos word count %d \n",finalPosCount);
  printf(1,"Neg word count %d \n",finalNegCount);
  printf(1,"Review word count %d",reviewCount);
  exit();
}
