#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define LINE_LENGTH 200
#define LINES 200

#define FILENAME "input"

bool is_special_char(char c){
  if(isdigit(c)){
    return false;
  }
  if(c == '.'){
    return false;
  }
  printf("The char check: %c\n", c);
  return true;
  // return (c == '*' || c == '#' || c == '+' || c == '$');
}

int check_neighbor(int curr_line, unsigned long curr_char, char line[LINES][LINE_LENGTH], bool is_special[LINES][LINE_LENGTH], int line_amount){

  // if(isdigit(line[curr_line][curr_char+1] || curr_char != 0)){
  //   is_special[curr_line][curr_char] = true; 
  // }
  
  // Right
  if(is_special_char(line[curr_line][curr_char+1]) && (curr_char != (strlen(line[curr_line])-2))){
    printf("Right\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }
  // Left
  if(is_special_char(line[curr_line][curr_char-1]) && (curr_char != 0)){
    printf("Left\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }
  // Bottom
  if(is_special_char(line[curr_line+1][curr_char]) && (curr_line != line_amount -  1)){
    printf("Bottom\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }
  // Top
  if(is_special_char(line[curr_line-1][curr_char]) && curr_line != 0){
    printf("Top\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }
  // Bottom right
  if(is_special_char(line[curr_line+1][curr_char+1]) && (curr_line != line_amount - 1) && (curr_char != (strlen(line[curr_line])-2))){
    printf("Bottom right\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }
  // Top right
  if(is_special_char(line[curr_line-1][curr_char+1]) && (curr_line != 0) && (curr_char != (strlen(line[curr_line])-2))){
    printf("Top right\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }
  // Top left
  if(is_special_char(line[curr_line-1][curr_char-1]) && (curr_line != 0) && (curr_char != 0)){
    printf("Top left\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }
  // Bottom left
  if(is_special_char(line[curr_line+1][curr_char-1]) && (curr_line != line_amount - 1) && (curr_char != 0)){
    printf("Bottom left\n");
    is_special[curr_line][curr_char] = true;
    return 0;
  }

  printf("Not special: [%d][%lu]\n", curr_line+1,curr_char+1);
  return -1;
}



int main(){

  FILE* file;
  file = fopen(FILENAME, "r");
  if(file == NULL){
    fprintf(stderr, "Failed to open file");
    return -1;
  }

  char line[LINES][LINE_LENGTH]; 
  bool is_special[LINES][LINE_LENGTH];

  // Loop through lines
  int line_amount = 0;
  while((fgets(line[line_amount], sizeof(line), file))!=NULL){
    if((strlen(line[line_amount]) == LINE_LENGTH-1) && (line[line_amount][LINE_LENGTH-2] != '\n') ){
      fprintf(stderr, "Line too long, increase LINE_LENGTH");
      return -1;
    }
    line_amount++; 
  }

// printf("Line amount: %d\n", line_amount);

int sum = 0;
int sum140 = 0;
 // Check is neighbor is special 
  for(int curr_line = 0; curr_line < line_amount; curr_line++){
    for(int curr_char = 0; line[curr_line][curr_char] != '\n'; curr_char++){
      // printf("Line: %d, char: %d\n", curr_line+1, curr_char+1);
      // printf("Char: %c\n", line[curr_line][curr_char]);
      if(isdigit(line[curr_line][curr_char])){
        int num_count = 0;
        bool had_neighbour = false;
        while(isdigit(line[curr_line][curr_char])){
          num_count += 1;   
          // printf("Digit: %c\n", line[curr_line][curr_char]);
          if(check_neighbor(curr_line, curr_char, line, is_special, line_amount) == 0){
            had_neighbour = true;
          }
           curr_char++;
           if(line[curr_line][curr_char+1] == '\n'){
            break;
           }
        }
        // printf("End of digit\n");
        // set all digits to have a neighbor
        if(had_neighbour == true){
          int curr_char_temp;
          for(curr_char_temp = 0; curr_char_temp < num_count; curr_char_temp++){
            is_special[curr_line][curr_char - curr_char_temp] = true;
            if(curr_char_temp == num_count-1){
           printf("Special set:[%d][%d]\n", curr_line+1, curr_char - curr_char_temp );
            }
          }
          
          // printf("Temp: %d\n", curr_char - curr_char_temp); 
          sum += atoi(&line[curr_line][curr_char - curr_char_temp]);
          if(curr_line == 139){
          sum140 += atoi(&line[curr_line][curr_char - curr_char_temp]);
          }
          // printf("Sum %d\n", sum);
        }

      }
    }
  }


  // Sum up all the corresponding manual part numbers
  // for(int curr_line = 0; curr_line < line_amount; curr_line++){
  //   for(int curr_char = 0; line[curr_line][curr_char] != '\n'; curr_char++){
  //     if(is_special[curr_line][curr_char]){
  //       while(is_special[curr_line][curr_char]){
  //         // printf("S:[%d][%d]\n", curr_line+1, curr_char+1);
  //         printf("Special: %d\n", atoi(&line[curr_line][curr_char]));
  //         if(line[curr_line][curr_char+1] != '\n'){
  //           curr_char++;
  //         }
  //         else{
  //           break;
  //         }
  //       }
  //     }
  //
  //   }
  // }
  printf("The SUM of all part numbers is: %d\n", sum);
  printf("The SUM of 140 numbers is: %d\n", sum140);

        // while(isdigit(line[curr_line][curr_char])){
        //   curr_char++; 
        // }

  fclose(file);
  return 0;
}
