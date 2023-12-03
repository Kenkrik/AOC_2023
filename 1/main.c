#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 101
#define MAX_LINES 1001

int main(){

  FILE* file = fopen("input", "r");

  if(file == NULL){
    fprintf(stderr,"Failed to open the file\n");
    return -1;
  }

  int first_num[MAX_LINES];
  int last_num[MAX_LINES]; 
  char line[MAX_LINES][MAX_LINE_LEN];


  int line_count = 0;
  char* num[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}; 
  bool first_found;

  while(fgets(line[line_count], MAX_LINE_LEN , file) && line_count < MAX_LINES-1){
    line_count++; 
  }
   for(int curr_line = 0; curr_line < line_count; curr_line++){
    // Find first digit
     for (int curr_line_char = 0; line[curr_line][curr_line_char] != '\n'; curr_line_char++) {
    // look for digit
        if(isdigit(line[curr_line][curr_line_char])){
          first_num[curr_line] = (line[curr_line][curr_line_char] - '0'); 
          break;
        } 
     // look for digit hidden as text 
      for(int curr_num = 0; (curr_num < 9) && !first_found; curr_num++){
        for(unsigned long curr_num_char = 0; curr_num_char < strlen(num[curr_num]); curr_num_char++){
          if(line[curr_line][curr_line_char+curr_num_char] == num[curr_num][curr_num_char]){
            if(curr_num_char+1 == strlen(num[curr_num])){
              first_num[curr_line] = curr_num+1;
              first_found = true;
              break;
              // do sth
            }
          }
          // jump out !if, check next number first char
          else{
            break;
          }
        }
      
      } 
      if(first_found){
        break;
      }
     }
      first_found = false;
  }
     for(int curr_line = 0; curr_line < line_count; curr_line++){
      // Find last digit
     for (int curr_line_char = 0; line[curr_line][curr_line_char] != '\n'; curr_line_char++) {
        // Look for digit
        if(isdigit(line[curr_line][curr_line_char])){
          last_num[curr_line] = (line[curr_line][curr_line_char] - '0'); 
        }
        // Look for digit hidden as text
     
        for(int curr_num = 0; (curr_num < 9); curr_num++){
          for(unsigned long curr_num_char = 0; curr_num_char < strlen(num[curr_num]); curr_num_char++){
            if(line[curr_line][curr_line_char+curr_num_char] == num[curr_num][curr_num_char]){
              if(curr_num_char+1 == strlen(num[curr_num])){
                last_num[curr_line] = curr_num+1;
                break;
                // do sth
              }
            }
            // jump out !if, check next number first char
            else{
              break;
            }
          }
        
        } 
    
      //end of for
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
