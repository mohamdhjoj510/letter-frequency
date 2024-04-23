#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>


//THREADS ARRAY
pthread_t th[4];
//ARRAYS TO COUNT LETTERS IN EACH FILE ( EACH THREAD HANDLE ON FILE AND ONE ARRAY) 
int lettersInFile1[26];
int lettersInFile2[26];
int lettersInFile3[26];
int lettersInFile4[26];
//THREADS INDEX
int threadIndex[4] = {0, 1, 2, 3};

//FUNCTION FOR COUNTING LETTERS IN FILES
void *CountLettersInFile(void *arg) {
	//THE FUNCTION TAKES THE THREAD INDEX
	int* currentThread = (int*)arg;
        FILE *file;
	int c;
	//FIRST THREAD HANDLING file1.txt AND COUNTING IN THE  lettersInFile1 ARRAY
	if((*currentThread)==0){
		//CHECK IF THE FILE IS ACCESSABLE OR NOT 
	   if (access("file1.txt", F_OK) == -1) {
		   perror("file 1 access blocked");
		   exit(1);
	   }
	   file = fopen("file1.txt","r");
	   //FAILED TO OPEN FILE
	   if(file==NULL){
		   perror("Error to open the file");
		   //END PROGRAM
		   exit(1);
	   }
	   //COUNT EACH LETTER IN THE FILE
	   while((c=fgetc(file))!=EOF){
		   c = tolower(c);
          	   if(c>='a' && c<='z'){
			   lettersInFile1[c-'a']++;
		   }
	   }
	   fclose(file);
	}
        //SECOND THREAD HANDLING file2.txt AND COUNTING IN THE  lettersInFile2 ARRAY
	if((*currentThread)==1){
		 if (access("file2.txt", F_OK) == -1) {
                   perror("file 2 access blocked");
                   exit(0);
           }
           file = fopen("file2.txt","r");
           if(file==NULL){
                   perror("Error to open the file");
                   exit(1);
           }
           while((c=fgetc(file))!=EOF){
                   c = tolower(c);
                   if(c>='a' && c<='z'){
                           lettersInFile2[c-'a']++;
                   }
           }
	   fclose(file);
	}
	//THIRD THREAD HANDLING file3.txt AND COUNTING IN THE  lettersInFile3 ARRAY
	if((*currentThread)==2){
		 if (access("file3.txt", F_OK) == -1) {
                   perror("file 3 access blocked");
                   exit(0);
           }
           file = fopen("file3.txt","r");
           if(file==NULL){
                   perror("Error to open the file");
                   exit(1);
           }
           while((c=fgetc(file))!=EOF){
                   c = tolower(c);
                   if(c>='a' && c<='z'){
                           lettersInFile3[c-'a']++;
                   }
           }
	   fclose(file);
	}
	//FOURTH THREAD HANDLING file4.txt AND COUNTING IN THE  lettersInFile4 ARRAY
	if((*currentThread)==3){
		 if (access("file4.txt", F_OK) == -1) {
                   perror("file 4 access blocked");
                   exit(0);
           }
           file = fopen("file4.txt","r");
           if(file==NULL){
                   perror("Error to open the file");
                   exit(1);
           }
           while((c=fgetc(file))!=EOF){
                   c = tolower(c);
                   if(c>='a' && c<='z'){
                           lettersInFile4[c-'a']++;
                   }
           }
	   fclose(file);
	}
	              return ((void *)0);
}
int main(void) {
    //MAIN THREAD 
    int i, retcode;
    //ARRAY TO COLLECT ALL THE RESULTS
    int lettersInAllFiles[26];
          //INITIALIZING ALL THE ARRAYS BY 0 
          for(i = 0; i < 26; i++)  {
                     lettersInFile1[i]=0;
                     lettersInFile2[i]=0;
                     lettersInFile3[i]=0;
                     lettersInFile4[i]=0;
	  }
	  //THE MAIN THREAD CREATING 4 THREADS TO HANDLE THE FILES COUNTING LETTERS FUNCTION
	  for(int i=0;i<4;i++){
		  retcode = pthread_create(&th[i], NULL, CountLettersInFile , (void *)&threadIndex[i] );
		  //AFTER CREATING EACH THREAD CHECK IF THE CREATING SUCCEED
		  if(retcode!=0){
			  printf("create thread failed");
			  exit(0);
		  }
		 }
	         //MAIN THREAD IS WAITING FOR THE 4 THREADS TO EXIT
		  for(i = 0; i < 4; i++) {
		       	  pthread_join(th[i], NULL);
		  }
		  //COLLECTING RESULTS IN ONE ARRAY
		  for(int i =0 ; i<26 ; i++){
			  lettersInAllFiles[i] =  (lettersInFile1[i]+lettersInFile2[i]+lettersInFile3[i]+lettersInFile4[i]);

		  }
		  //PRINTING FINAL RESULT
		  printf("Letter frequencies in all files :\n");
		  for(i=0;i<26;i++){
                      printf("%c: %d\n",(i+'a'), lettersInAllFiles[i]);
		  }
               return 0;
	  }
