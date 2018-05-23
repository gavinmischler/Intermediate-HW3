#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// fills the int array disease_profile with 5 integers
void fill_disease_profile(unsigned int entries[], int requested_loc, int disease_profile[]) {
  unsigned int entry = entries[requested_loc];
  disease_profile[0] = (entry>>8) & 3; // just take the two digits that matter
  disease_profile[1] = (entry>>6) & 3;
  disease_profile[2] = (entry>>4) & 3;
  disease_profile[3] = (entry>>2) & 3;
  disease_profile[4] = entry & 3;
}

// searches through the entries[] matrix to see if it is there
// returns the integer location of the patient, or -1 if not found
int find_ID(unsigned int entries[], int num_patients, unsigned int requested_ID) {
  for (int i = 0; i < num_patients; i++) {
    if ((entries[i]>>17) == (requested_ID)) {
      return i;
    }
  }
  return -1;
}

// searches through the patient_ID_array[] matrix to see if the ID is in it
bool is_duplicate(unsigned int patient_ID, unsigned int patient_ID_array[], int num_entered) {
  if (num_entered < 1) {
    return false;
  }
  // search through the patient ID's that have been entered to see if this is a duplicate
  for (int j = 0; j < num_entered; j++) {
    if (patient_ID == patient_ID_array[j]) {
      return true;
    }
  }
  return false;
}

// convert the disease status to its unsigned integer representation
unsigned int status_to_int(char status[]) {
  if (strcmp(status, "UN") == 0) {
    return 0;
  } else if (strcmp(status, "DF") == 0) {
    return 1;
  } else if (strcmp(status, "DN") == 0) {
    return 2;
  } else if (strcmp(status, "DT") == 0) {
    return 3;
  } else {
    printf("Error: status not equal to one of the options\n");
    return 5;
  }
}


// load the database into the entries[] array
// returns the number of unique patients in the database (since some might have been duplicates)
int load(unsigned int entries[], int num_entries, FILE *fp) {
  char entry_line[200];
  unsigned int patient_ID;
  unsigned int patient_age;
  char HUstatus[20];
  char FHstatus[20];
  char SCstatus[20];
  char TSstatus[20];
  char CFstatus[20];
  unsigned int patient_ID_array[num_entries];

  // get the first line which has the number of entries already, so that the buffer is on the next line
  if (fgets(entry_line, "%s", fp) != NULL) {
    //hooray
  } else {
    printf("Error: failed to pass the first line when reading from the database\n");
    exit(0);
  }
  int i = 0; // i is the index of the database file
  int e = 0; // e is the index of the entries array we are in
  // scan line by line until no more entries to scan
  while ((fgets(entry_line, 200, fp) != NULL) && (i < num_entries)) {
    printf("%s\n", entry_line);
    // pull out each piece of data from the line
    sscanf(entry_line, "%u %u %s %s %s %s %s", &patient_ID,
      &patient_age, HUstatus, FHstatus, SCstatus, TSstatus, CFstatus);
    // add the patient ID to the patient ID array
    patient_ID_array[i] = patient_ID;
    //printf("ID = %u, age = %u, HU status = %s\n", patient_ID_array[i], patient_age, HUstatus);

    // check if the patient_ID is a duplicate
    if (is_duplicate(patient_ID, patient_ID_array, i)) {
      duplicate_entry(patient_ID);
    } else {
      // convert strings of disease statuses to integers
      unsigned int HUstatus_int = status_to_int(HUstatus);
      unsigned int FHstatus_int = status_to_int(FHstatus);
      unsigned int SCstatus_int = status_to_int(SCstatus);
      unsigned int TSstatus_int = status_to_int(TSstatus);
      unsigned int CFstatus_int = status_to_int(CFstatus);
      //printf("got %u %u %u %u %u\n", HUstatus_int, FHstatus_int, SCstatus_int, TSstatus_int, CFstatus_int);

      // bit shift the variables to the proper location
      patient_ID = patient_ID<<17;
      patient_age = patient_age<<10;
      HUstatus_int = HUstatus_int<<8;
      FHstatus_int = FHstatus_int<<6;
      SCstatus_int = SCstatus_int<<4;
      TSstatus_int = TSstatus_int<<2;
      unsigned int full_entry = patient_ID | patient_age | HUstatus_int | FHstatus_int | SCstatus_int | TSstatus_int | CFstatus_int;
      //printf("now %u %u %u %u %u %u\n", HUstatus_int, FHstatus_int, SCstatus_int, TSstatus_int, CFstatus_int, full_entry);
      entries[e] = full_entry;
      printf("%u\n just put db[%i] into entries[%i]\n\n", full_entry, i, e);
      e++;
    }
    i++;
  }
  return e;
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
  int num_patients = load(entries, num_entries, fp);

  // close file pointer
  fclose(fp);

  char user_menu_input[20];
  char user_input = 'a';
  while (user_input != 'q') {
    print_menu();
    scanf("%s", user_menu_input);
    user_input = user_menu_input[0];
    if (user_input == 'q') {
      exit(0);
    } else if (strlen(user_menu_input) != 1 || (user_input != 'n' && user_input != 'd' && user_input != 'e' && user_input != 'c' && user_input != 'l' && user_input != 's' && user_input != 'q')) {
      bad_menu_option(user_input);
    } else {

      unsigned int requested_ID = 0;


      switch (user_input) {
        case 'n':
          output_n(num_patients);
          printf("\n");
          break;
        case 'd':
          prompt_d();
          scanf("%u", &requested_ID);
          // find location of that patient ID
          int requested_loc = find_ID(entries, num_patients, requested_ID);
          if (requested_loc == -1) { // Patient ID not found in database
            bad_patient_ID(requested_ID);
            printf("\n");
          } else {
            int disease_profile[5];
            fill_disease_profile(entries, requested_loc, disease_profile);
            output_disease_profile(disease_profile);
            printf("\n");
          }
          break;
      }

    }

  }
  free(filepath);
  return 0;
}
