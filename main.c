#include "interface.h"
#include <stdio.h>


int main() {
  char user_menu_input[50];
  print_menu();
  scanf("%s\n", user_menu_input);
  printf("%s\n", user_menu_input);
  return 0;
}
