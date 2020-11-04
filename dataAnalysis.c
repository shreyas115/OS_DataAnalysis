#include "types.h"
#include "stat.h"
#include "user.h"
#include<stddef.h>
#include "fcntl.h"

// temp buffer variable used across file reads
char buf[512];
// global variables to store words in an array. Defined global so that it can be
// accessed through out this program
char* posWordArray[500]; 
char* negWordArray[500];
char* reviewWordArray[500];
// global variables which stores the word count, similar to above
int posWordCount = 0;
int negWordCount = 0;
int reviewCount = 0;
int finalPosCount = 0;
int finalNegCount = 0;

/*
Function 	: readPosFile 
Input 		: Takes the connection to file stream
Output		: Stores positive word list in an array
Return		: None
Algorithm	: This method reads the content of the file and stores each word in an array	
			  The content is stored in a temp buffer and then read char by char. Once it hits a \n char,
			  the word is assumed to be terminated and stored in the permanent array. The count of 
			  number of words read from the file is also stored for future use.
*/
void readPosFile(int fd)
{
	int i,n,count,words;
	count=0;
	char* allPosLines = malloc(500);
	memset(buf, 0,512);
	// reads all the file content and stores in a char array
	while((n = read(fd, buf, sizeof(buf))) > 0)
	{
		strcpy(allPosLines,buf);	      
	}

	int len= strlen(allPosLines);
	char word[20]; // size of the word is assumed to be no more than 20 chars
	words=0;
	int noOfChar=0;
	// loops through every char in the file content array to get the words in it
	for(i=0;i<len;i++)
	{
		word[count++]=allPosLines[i]; // check the number of chars in the word
		if(allPosLines[i]=='\n') // here it decides that the word has ended (one word per line in the file), so we copy the content to array
		{
			char *str = (char *)malloc(sizeof(char)*count); // reset so that previous value is doesnt overlap with current
			words++;
			// copy chars in contiguous memory address
			for(noOfChar=0;noOfChar<count;noOfChar++)
				*(str+noOfChar)=word[noOfChar];
			*(str+count-1)='\0'; // word termination char
			posWordArray[words-1]=malloc(count);
			strcpy(posWordArray[words-1],str); // copy the word to array
			count = 0;
			posWordCount++; // increment the word count
		}
	}
}
/*
Function 	: readNegFile 
Input 		: Takes the connection to file stream
Output		: Stores negative word list in an array
Return		: None
Algorithm	: This method is similar to the readPosFile but stores the negative words in a different array
			  Note : The reason for using seperate function instead of a common function is becase of the pointer issues
			  faced and memory corruption that created some issues
*/
void readNegFile(int fd)
{
	int i,n,count,words;
	count=0;
	char* allNegLines = malloc(500);
	memset(buf,0,512);
	// reads all the file content and stores in a char array
	while((n = read(fd, buf, sizeof(buf))) > 0)
	{
		strcpy(allNegLines,buf);	      
	}

	int len = strlen(allNegLines);
	char word[20];// size of the word is assumed to be no more than 20 chars
	words=0;
	int noOfChar=0;
	// loops through every char in the file content array to get the words in it
	for(i=0;i<len;i++)
	{
		word[count++]=allNegLines[i];// check the number of chars in the word
		if(allNegLines[i]=='\n')// here it decides that the word has ended (one word per line in the file), so we copy the content to array
		{	
			char*str = (char *)malloc(sizeof(char)*count);// reset so that previous value is doesnt overlap with current
			words++;
			// copy chars in contiguous memory address
			for(noOfChar=0;noOfChar<count;noOfChar++)
				*(str+noOfChar)=word[noOfChar];
			*(str+count-1)='\0';// word termination char
			negWordArray[words-1] = malloc(count);
			strcpy(negWordArray[words-1],str);
			count = 0;
			negWordCount++;// increment the word count
		}
	}
}
/*
Function 	: readReviewFile 
Input 		: Takes the connection to file stream
Output		: Stores all the word in the files in an array list, processes them and calculates the positive and negative counts.
Return		: None
Algorithm	: This method takes the review file stream as input and reads the file as set of 500 chars. 
			  When the current char is not an alphabet, it assumes that the word is complete and its stored
			  in an array. Once the all the words in the buffer is identified, the next process of finding 
			  the number of positive and negative words takes place. The loop continues till all the words 
			  in the review file are compared with the positive and negative words.
*/
void readReviewFile(int fd)
{
	int i,n,count,words;
	count=0;
	char* allLines = malloc(500);
	int j =0;
	int pos = 0;
	int neg = 0;
	// Loop through the entire file data, in chunks of 500 chars at a time
	while((n = read(fd, buf, sizeof(buf))) > 0)
	{
		strcpy(allLines,buf);	      
		int len = strlen(allLines);
		char word[20];
		int noOfChars = 0;
		words=0;
		for(i=0;i<len;i++)
		{
			word[count++]=allLines[i];
			// check if the char is anything other than alphabets. That means, the word has terminated. 
			// since this is sentence, this method is used. 
			if(!((allLines[i] >= 'a' && allLines[i] <= 'z') || (allLines[i] >= 'A' && allLines[i] <= 'Z')))
			{
				char *str = (char *)malloc(sizeof(char)*count);// reset so that previous value is doesnt overlap with current
				words++;
				// copy chars in contiguous memory address
				for(noOfChars = 0;noOfChars<count; noOfChars++)
					*(str+noOfChars)=word[noOfChars];
				*(str+count-1)='\0';// word termination char
				reviewWordArray[words-1]=malloc(count);
				strcpy(reviewWordArray[words-1], str);
				count = 0;
				reviewCount++;// increment the word count
			}
		}
		// loop through every word in review file
		for(j = 0;j<reviewCount;j++)
		{
			// check if the word in review file matches with positive or negative word
			for(pos=0;pos<posWordCount;pos++)
			{	
				// checking if the word is a positive word
				if(strcmp(reviewWordArray[j],posWordArray[pos])==0 && strcmp(posWordArray[pos],"")!=0)
				{
					finalPosCount++; // increase count if word matches
					printf(1, "Pos Word _%s_\n",posWordArray[pos]); // temporary print to see what word matched
				}
			}
			for(neg=0;neg<negWordCount;neg++)
			{
				// checking if the word is a negative word
				if(strcmp(reviewWordArray[j],negWordArray[neg])==0)
				{
					finalNegCount++;// increase count if word matches
					printf(1,"Neg Word_%s_\n",negWordArray[neg]);// temporary print to see what word matched
				}		
			}
		}
		// reset all chars to prevent previous text overlap with current
		memset(allLines,0,500);
		memset(buf,0,512);
		reviewCount = 0;
	}
}
/*
Function 	: main 
Input 		: argv and argc
Output		: Produces the sentiment data
Return		: Tells the OS that it has exited
Algorithm	: Check if all the input files are valid and readable. Else throws an error to the user	
			  Calls the respective read methods for reading and getting the word/word count
			  Calls the review file read method to read the words and find out how many positive and negative
			  Based on the word count, does the calculation for sentiment analysis
*/

int main(int argc, char *argv[])
{
	int fd;
	//check if the user has provided three files as input else throw error to user
	if(argc <= 1){
		printf(1,"Please provide three files",40);
		exit();
	}
	// check if the second file (negative file) is readable, else throw error. Continue to process the file if its readable
	if((fd = open(argv[2],0)) < 0){
		printf(1, "cannot open %s", argv[2]);
		exit();
	}
	readNegFile(fd);
	close(fd);
	// check if the thrid file (positive file) is readable, else throw error. Continue to process the file if its readable
	if((fd = open(argv[3],0)) < 0){
		printf(1, "cannot open %s", argv[3]);
		exit();
	}
	readPosFile(fd);
	close(fd);
	// check if the first file (review file) is readable, else throw error. Continue to process the file if its readable
	if((fd = open(argv[1],0)) < 0){
		printf(1, "cannot open %s", argv[1]);
		exit();
	}
	readReviewFile(fd);
	close(fd);
	
	// once review file process is complete, we have the data. Apply % calculation logic to find the sentiment percentage 
	if(finalPosCount>finalNegCount)
		printf(1, "The review sentiment is %d percentage positive",(int)(finalPosCount*100/(finalPosCount+finalNegCount)));
	else if(finalPosCount<finalNegCount)
		printf(1,"The review sentiment is %d percentage negative",(int)(finalNegCount*100/(finalPosCount+finalNegCount)));
	else
		printf(1,"The review is neutral with equal amount of positive and negative sentiments");
	exit();
}
