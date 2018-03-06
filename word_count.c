#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{//struct with all relevant information about tokenized input file
  int letterCount, freq, repeatWords;
  char *word[50];
}wordInfo;

int strcascmp(char const *a, char const *b){//non-case sensitive strcmp()
    for (;; a++, b++) {
        int c = tolower(*a) - tolower(*b);
        if (c != 0 || !*a)
            return c;
    }
}

int freqSort(const void *a, const void *b){// sort based on frequency of words
  wordInfo *numA = (wordInfo *)a;
  wordInfo *numB = (wordInfo *)b;
  return(numA->freq < numB->freq);
}

int ascendingSort(const void *a, const void *b){//basic sort for rule 1
  wordInfo *numA = (wordInfo *)a;
  wordInfo *numB = (wordInfo *)b;
  return(numA->letterCount > numB->letterCount);
}

int wordSort(const void *a, const void *b){//sorts the word array in the struct alphanumerically
  char *wordA = (char *)a;
  char *wordB = (char *)b;
  if(strcmp(wordA,wordB) > 0 || strcmp(wordA,wordB) == 0){
    return 0;
  }
  return 1;
}

void removeE(char *arr[], int ind, int len){//removes an element from an array
   int i;
   for(i = ind; i < len - 1; i++){
		  arr[i] = arr[i + 1];
		}
}

int numWords(char a[]){//returns the number of words from the input file
  char* wordTok = strtok(a, " ,.;()\n");
  int arrSize = 0;
  while(wordTok != NULL){
    arrSize++;
		wordTok = strtok(NULL, " ,.;()\n");
	}
  return arrSize;
}

void printWords(wordInfo a[], int length){//prints unique words for Part 3
  for(int ab = 0; ab < length;ab++){
    for(int c = 0; c < a[ab].freq - a[ab].repeatWords; c++){
      for(int d = c + 1; d < a[ab].freq - a[ab].repeatWords;d++){
        if(strcascmp(a[ab].word[c],a[ab].word[d]) == 0){
          removeE(a[ab].word, d, a[ab].freq - a[ab].repeatWords);
          a[ab].repeatWords++;
          d--;
        }
      }
    }
    qsort(a[ab].word, a[ab].freq - a[ab].repeatWords, sizeof(char*), wordSort);
  }
  for(int z = 0;z < length;z++){
    if(a[z].freq - a[z].repeatWords == 1){
      printf("Count[0%d]=0%d; (words: \"%s\")\n", a[z].letterCount, a[z].freq, a[z].word[0]);
      z++;
      if(z == length){
        exit(0);
      }
    }
    printf("Count[0%d]=0%d; (words: ", a[z].letterCount, a[z].freq);
    for(int y = 0;y < a[z].freq - a[z].repeatWords;y++){
      if(y == a[z].freq){
      }
      if(y == a[z].freq - a[z].repeatWords - 1){
        printf("and \"%s\"", a[z].word[y]);
        break;
      }
      if(y == (a[z].freq - a[z].repeatWords - 2)){
        printf("\"%s\" ", a[z].word[y]);
      }
      else{
        printf("\"%s\", ", a[z].word[y]);
      }
    }
    printf(")\n");
  }
}

void wordCount(char a[], int argc, char* argv[]){//handles part 1 and 2 of assignment and prints sorted list (using rules 1 and 2)
  char* str1 = "--sort";
  char* str2 = "--print-words";
	char* wordTok = strtok(a, " ,.;()\n");
  int arrSize = 0;
  char* words[750];
  while(wordTok != NULL){
    words[arrSize] = wordTok;
    arrSize++;
		wordTok = strtok(NULL, " ,.;()\n");
	}
  wordInfo arr[arrSize];
  for(int b = 0;b < arrSize;b++){
    arr[b].repeatWords = 0;
    arr[b].freq = 1;
    arr[b].letterCount = strlen(words[b]);
    arr[b].word[0] = words[b];
    for(int d = b + 1;d < arrSize; d++){
      if(arr[b].letterCount == strlen(words[d])){
          arr[b].word[arr[b].freq] = words[d];
          arr[b].freq++;
          removeE(words, d, arrSize);
          arrSize--;
          d--;
      }
    }
  }
  qsort(arr, arrSize, sizeof(wordInfo), ascendingSort);
  for(int abc = 1; abc < argc; abc++){
    if(strcmp(argv[abc],str1) == 0){
      qsort(arr, arrSize, sizeof(wordInfo), freqSort);
    }
  }
  for(int y = 0;y < argc; y++){
    if(strcmp(argv[y],str2) == 0){
      printWords(arr, arrSize);
      exit(0);
    }
  }
  for(int z = 0;z < arrSize; z++){
    printf("Count[0%d]=0%d;\n", arr[z].letterCount, arr[z].freq);
  }
}

int main(int argc, char* argv[]){//handle input file and determines if valid
	char *str1 = "--infile";
	if(argc < 2){
		fprintf(stderr, "Invalid filename\n");
		exit(1);
	}
	FILE *inf;
	char word[750];
	for(int a = 1; a < 5; a++){
		if(strcmp(argv[a],str1) == 0){
			inf = fopen(argv[a+1], "r");
			if(inf == NULL){
				fprintf(stderr, "Can't open %s\n", argv[a+1]);
				exit(1);
			}
			fgets(word,10000,inf);
      wordCount(word, argc, argv);
			fclose(inf);
			break;
		}
	}
}
