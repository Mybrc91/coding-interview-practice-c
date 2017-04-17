#include <stdio.h>
#include <stdlib.h>

#include "array.c"

void run_example();

// Implements a vector (called MArray) from a C array.

int main(int argc, char* argv[]) {
  run_all_tests();
  run_example();

  return EXIT_SUCCESS;
}

void run_example() {
  int capacity = 0;

  printf("Enter many numbers would you like to store: ");
  scanf("%d", &capacity);

  printf("You'll be storing %d numbers.\n", capacity);

  // make it so

  MArray* aptr = marray_new(capacity);

  for (int d = 1; d <= capacity; ++d) {
    marray_push(aptr, d);
  }

  int insert_value = 999;
  printf(" - Inserting %d at index %d.\n", insert_value, capacity - 1);
  marray_insert(aptr, capacity - 1, insert_value);

  printf(" - Prepending %d.\n", 12);
  marray_prepend(aptr, 12);

  printf(" - Popping an item: %d\n", marray_pop(aptr));

  marray_print(aptr);

  int index_to_remove = marray_size(aptr) - 3;
  printf(" - Deleting from index %d\n", index_to_remove);
  marray_delete(aptr, index_to_remove);

  marray_push(aptr, 12);
  marray_push(aptr, 12);

  marray_print(aptr);

  printf(" - Deleting 12s\n");

  marray_remove(aptr, 12);

  marray_print(aptr);

  marray_destory(aptr);
}







