#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#ifdef _WIN32
  #include <direct.h>
  #define getcwd _getcwd
  #define access _access
#elif
  #include <unistd.h>
#endif

int main(int argc, char * argv[]){
  //Get current directory
  char * currentDirectory = (char *)malloc(sizeof(char) * 100);
  char * filename = (char *)malloc(sizeof(char)*30);
  char * fullfilename = (char *)malloc(sizeof(char) * 140);
  getcwd(currentDirectory, 200);

  if(argc < 2) {
    puts("Going to default file name....");
    //Check if file name of main exists.
    sprintf(fullfilename, "%s\\%s", currentDirectory, "main.c");
    if(access(fullfilename, 0) != 0){
      puts("No C input files found. Please make sure you provide an input file.");
      free(fullfilename);
      return -1;
    }
  }else{
    if(strlen(argv[1]) >= 30) {
      puts("File name too long.");
      return -1;
    }
    strcpy(filename, argv[1]);
    strcat(filename, ".c");
    sprintf(fullfilename, "%s\\%s", currentDirectory, filename);
    if(access(fullfilename, 0) != 0){
      puts("Provided input file name is not found. Please check if it exists.");
      free(fullfilename);
      return -1;
    }
  }

  char * fullcommand = (char *)malloc(sizeof(char) * 200);
  puts(fullfilename);
  sprintf(fullcommand, "gcc \"%s\" -o output && output.exe", fullfilename);
  system(fullcommand);
  free(fullcommand);

  return 0;
}