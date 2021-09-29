#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

//Defining true and false for bools
#ifndef _BOOL
typedef unsigned char bool;
static const bool false = 0;
static const bool true = 1;
#endif

//parsing it splitting a string of commands into smaller parts to be analyzed for issues usually
//Tokenization is splitting a sentence, or body of text into smaller units such as individual words or terms
//If I type "hi there" in the terminal it says "token was: hi" and "token was: there" so it splits up the phrase into two words
//A delimiter is a sequence of one or more character for specifying the boundary between parts of text. In this case it's space, which separates words
//strtok() is a function for string tokenization (like the word looks like "str" and "tok"). It takes 2 arguments, the string, and a character delimiter
void parse(char* s) {
  const char break_chars[] = " \t"; //2nd argument in "strtok()" which tells us that we separate tokens with a space. We could also change it to something like a comma.
  char* p;
  p = strtok(s, break_chars); //strtok(string, character delimiter)
  while (p != NULL) {
    printf("token was: %s\n", p); //%s means string, and p is previously defined as a char*, so that's just how we printf a char*
    p = strtok(NULL, break_chars);
  }
}


int main(int argc, const char * argv[]) {  
  char input[BUFSIZ]; //BUFSIZ is just a size that allows for a certain lenght of argument. Basically gives us certain amount of space for the input.
                      //Although input here is just an array of characters (or a string)
  char last_command[BUFSIZ]; 
  pid_t pid;
  
  memset(input, 0, BUFSIZ * sizeof(char)); //memset just fills a block of memory with a particular value
  memset(input, 0, BUFSIZ * sizeof(char)); //Syntax of memset: starting address of value to be filled, value to be filled, # of byte sto be filled
  bool finished = false;

  char *args[(BUFSIZ * sizeof(char)/2 + 1)];
  
  while (!finished) {
    printf("osh> ");
    fflush(stdout);

    if ((fgets(input, BUFSIZ, stdin)) == NULL) {   // or gets(input, BUFSIZ);
      fprintf(stderr, "no command entered\n");
      exit(1);
    }
    input[strlen(input) - 1] = '\0';          // wipe out newline at end of string
    printf("input was: \n'%s'\n", input);

    // check for history (!!) command
    if (strncmp(input, "!!", 2) == 0) { //strncmp returns positive, negative, or 0, depending on whether input is less than =to or greater than !!
      if (strlen(last_command) == 0) {
        fprintf(stderr, "no last command to execute\n");
      }
      printf("last command was: %s\n", last_command);
    } else if (strncmp(input, "exit", 4) == 0) {   // only compare first 4 letters
      finished = true;
    } else {
      strcpy(last_command, input); //strcpy is string copy. Copies 2nd argument into 1st
      printf("You entered: %s\n", input);   // you will call fork/exec

      pid = fork();
      if (pid < 0) { // error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
      }
      if (pid == 0) { // child process
        execvp(args[0], args);
      }
      /*
      else { // parent process
        wait(NULL); //parent will wait for child to complete
        printf("Waited for child to complete\n");
      }
      */

      parse(input);
			printf("after parse, what is input: %s\n", input);
      printf("\n");
    }
  }
  
  printf("osh exited\n");
  printf("program finished\n");
  
  return 0;
}
