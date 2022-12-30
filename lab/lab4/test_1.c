#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define SIZE 20

void mutate(char* input){                 // write random uint8 data to random position
  int length = strlen(input);
  for(int i = 0; i < length * 2; ++i){
    int pos = rand() % length;                          // generate the position to be changed
    input[pos] = (char)(33 + rand() % (126 - 33 + 1));  // generate char data randomly
  }
}

int main(){
  srand(time(0));
  while(1){
    char input[SIZE] = "test on fuzz lab!";  //crash_sample_input: t?}ldt€   dt on iuat on iua|!0
    mutate(input);
    FILE *mutation_save = fopen("mutation_normal_1", "w");
    fwrite(input, sizeof(char), sizeof(input), mutation_save);
    fclose(mutation_save);

    FILE *mutation_read = fopen("mutation_normal_1", "r");
    printf("INPUT IS: ");
    while(1){
      int c = fgetc(mutation_read);
      if(feof(mutation_read)){
        break;
      }
      printf("%c", c);
    }
    printf("\n");
    fclose(mutation_read);

    char output[SIZE];
    FILE *read_fp = popen("./base64_encode mutation_normal_1", "r");
    if(read_fp != NULL){
      if(fgets(output, sizeof(output), read_fp) == NULL){
        printf("CRASHED!\n");
        break;
      }
      printf("OUTPUT IS :");
      do{
        if(output[strlen(output) - 1] == '\n'){
          output[strlen(output) - 1] = '\0';
        }
        printf("%s", output);
      }while(fgets(output, sizeof(output), read_fp) != NULL);
      printf("\n");
      int retval = pclose(read_fp);
      printf("RETURN IS: %d\n", WIFEXITED(retval));
    }
  }

  return 0;
}
