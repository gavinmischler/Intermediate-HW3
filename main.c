#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
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

  return 0;
}
