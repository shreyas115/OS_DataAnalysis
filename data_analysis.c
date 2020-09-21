#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void readFile(char* file_name,int *count, char wordArray[10][30])
{	
	FILE *fp;
	char word[30];
	char* localArray[30];
	int wordCount = 0, i;
	fp = fopen(file_name, "r");
	if(fp!=NULL) {
		while(fscanf(fp," %s ", word)!=EOF){
			wordCount++;
			strcpy(wordArray[wordCount],word);
		}
	}
	else 
		puts("Cannot read the file!");
	fclose(fp);
	*count = wordCount;
}
int main()
{	int i,j,count;
	char* file_name;
	char words[10][30];
	char words1[10][30];
	readFile("pos.txt",&count,words);
	for(i=0;i<=count;i++){
		printf("%s\n",words[i]);
	}	
	count=0;
	readFile("negative.txt",&count,words1);
	for(j=0;j<=count;j++){
		printf("%s\n",words1[j]);
	}
	return(0);		
}
