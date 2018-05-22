#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void load(unsigned int entries[], FILE *fp) {
  unsigned int patient_ID;
  unsigned int patient_age;
  char HUstatus[5];
  char FHstatus[5];
  char SCstatus[5];
  char TSstatus[5];
  char CFstatus[5];
  char entry_line[200];
  //scan line by line until not more entries to scan
  while (fscanf(fp, "%lu", &patient_ID) == 1) {

    // scan the space
    fgetc(fp);
    // scan the query
    fscanf(fp, "%[^\n]\n", query);

    // put in the appropriate query, weight pair
    strcpy(queries[i], query);
    weights[i] = weight;
    i++;
  }

  //grab the line with fgets
  //sscanf it to get the patient ID, age, and 5 statuses
  //make sure it's not a duplicate patient ID, if it is, break and move on to the next line
  //else, convert each disease status to an integer
  //bitwise shift each integer to the right location
  //put all the bits together with XOR and put this 32 bit integer in the entries[] array

}

int main(int argc, const char* argv[]) {

  //Store the filepath command-line argument
  char *filepath;
  if (argc == 2) {
    filepath = malloc(strlen(argv[1])+1);
    strcpy(filepath, argv[1]);
  } else {
    printf("Error: Not the right number of input arguments. Specify path to database.\n");
    return -1;
  }

  //Open a file pointer for the database file into an arrays
  FILE *fp = fopen(filepath, "r");

  // scan number of entries in the database file
  int num_entries;
  fscanf(fp, "%d", &num_entries);

  // declare the array of ints for the patients
  unsigned int entries[num_entries];

  // read the data into the array
  load(entries, fp);

  // always remember to close file pointers!
  fclose(fp);



  char user_menu_input[20];
  char user_input = 'a';
  while (user_input != 'q') {
    print_menu();
    scanf("%s", user_menu_input);
    printf("user inputted %s\n", user_menu_input);
    user_input = user_menu_input[0];
    if (user_input == 'q') {
      // do nothing
    } else if (strlen(user_menu_input) != 1 || (user_input != 'n' && user_input != 'd' && user_input != 'e' && user_input != 'c' && user_input != 'l' && user_input != 's' && user_input != 'q')) {
      bad_menu_option(user_input);
    } else {
      printf("execute program");
      //execute program

    }

  }
  free(filepath);
  return 0;
}
