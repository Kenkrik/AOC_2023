#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 101
#define MAX_LINES 1001

int main(){

  FILE* file = fopen("short_input", "r");

  if(file == NULL){
    fprintf(stderr,"Failed to open the file\n");
    return -1;
  }

  int first_num[MAX_LINES];
  int last_num[MAX_LINES]; 
  char line[MAX_LINES][MAX_LINE_LEN];


  int line_count = 0;
  
  while(fgets(line[line_count], MAX_LINE_LEN , file) && line_count < MAX_LINES-1){
    line_count++; 
  }
   for(int curr_line = 0; curr_line < line_count; curr_line++){
     for (int curr_char = 0; line[curr_line][curr_char] != '\n'; curr_char++) {
       if(isdigit(line[curr_line][curr_char])){
         first_num[curr_line] = (line[curr_line][curr_char] - '0'); 
         break;
       } 
     } 
     for (int curr_char = 0; line[curr_line][curr_char] != '\n'; curr_char++) {
       if(isdigit(line[curr_line][curr_char])){
         last_num[curr_line] = (line[curr_line][curr_char] - '0'); 
       } 
     } 
   }
  
   int sum = 0;
   for (int curr_line = 0; curr_line < line_count; curr_line++) {
     sum += (10*(first_num[curr_line])+last_num[curr_line]); 

      printf("F:%d, S:%d\n",first_num[curr_line],last_num[curr_line]);
   }
  
  printf("Sum is: %d", sum);
  
  fclose(file);

  return 0;
}
