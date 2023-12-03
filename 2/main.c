#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINES 100
#define MAX_LINE_LENGTH 300


int main(){

  bool is_valid[MAX_LINES]; 
  int blue[MAX_LINES]; 
  int red[MAX_LINES]; 
  int green[MAX_LINES]; 
  char line[MAX_LINES][MAX_LINE_LENGTH];
  FILE* file;
  bool is_id = true;

  // init to 0
  for(int curr_num = 0; curr_num < MAX_LINES; curr_num++){
    blue[curr_num] = 0;
    red[curr_num] = 0;
    green[curr_num] = 0;
    is_valid[curr_num] = true;
  }

  file = fopen("input", "r");
  
  if(file == NULL){
    fprintf(stderr, "Failed to open input");
    return -1;
  }

  int line_count = 0;

  while(fgets(line[line_count],MAX_LINE_LENGTH,file)){
    line_count++;
  }
 
  // Loop through lines
  for(int curr_line = 0; curr_line < line_count; curr_line++){
  // Loop through characters on lines
    for(unsigned long curr_char = 0; line[curr_line][curr_char] != '\n'; curr_char++){
      // skip loading id
      if(is_id){
        if(isdigit(line[curr_line][curr_char])){
          is_id = false;
        }
        
      }
      else{
        if(isdigit(line[curr_line][curr_char])){
          // count amount of digits in a number 
          int digit_count = 0;
          while(isdigit(line[curr_line][curr_char+digit_count])){
          digit_count++;
        }
          // get position where to check if blue, red, green
          int next_pos = 1+digit_count;
          
          // check that color is blue
          if(line[curr_line][curr_char+next_pos] == 'b'){
            if(blue[curr_line] < atoi(&(line[curr_line][curr_char]))){
              blue[curr_line] = atoi(&(line[curr_line][curr_char]));
            }
            if(atoi(&(line[curr_line][curr_char])) > 14){
              is_valid[curr_line] = false;
            }
            curr_char += strlen("blue");

          }
          // check that color is red
          if(line[curr_line][curr_char+next_pos] == 'r'){
            if(red[curr_line] < atoi(&(line[curr_line][curr_char]))){
              red[curr_line] = atoi(&(line[curr_line][curr_char]));
            }
            if(atoi(&(line[curr_line][curr_char])) > 12){
              is_valid[curr_line] = false;
            }
            curr_char += strlen("red");
          }
          // check that color is green
          if(line[curr_line][curr_char+next_pos] == 'g'){
            if(green[curr_line] < atoi(&(line[curr_line][curr_char]))){
              green[curr_line] = atoi(&(line[curr_line][curr_char]));
            }
            if((atoi(&line[curr_line][curr_char])) > 13){
              is_valid[curr_line] = false;
            }
            curr_char += strlen("green");
          }
        }

      }

    }
  }

  // Count result of first part
  int id_sum = 0;
  for(int curr_line = 0; curr_line < line_count; curr_line++){
    if(is_valid[curr_line]){
      id_sum += curr_line+1; 
    }
  }
  printf("ID sum: %d\n", id_sum);

  // Count result of second part
  int sum2 = 0;
  for(int curr_line = 0; curr_line < line_count; curr_line++){
    sum2 += blue[curr_line]*red[curr_line]*green[curr_line];
  }
  printf("Sum 2: %d\n", sum2);

  fclose(file);
  return 0;
}
