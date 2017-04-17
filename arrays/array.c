#include "array.h"

MArray * marray_new(int capaticy){
    int true_capacity = marray_determine_capaticy(capaticy);

    MArray *array = malloc(sizeof(MArray));
    check_address(array);

    array->size = 0;
    array->capacity = true_capacity;
    array->data = (int *)malloc(sizeof(int) * true_capacity);
    check_address(array->data);

    return array;
}
void marray_destory(MArray *arrptr){
    free(arrptr->data);
    free(arrptr);
}

void marray_resize_for_size(MArray *arrptr, int condidate_size){
    if (arrptr->size < condidate_size)
    {
        if (arrptr->size == arrptr->capacity)
        {
            marray_upsize(arrptr);
        }
    }else if(arrptr->size > condidate_size){
        if (arrptr->size < arrptr->capacity / kShrinkFactor)
        {
            marray_downsize(arrptr);
        }
    }
}

int marray_determine_capaticy(int capacity){
    const int kMinInitCapacity = 1;
    int true_capacity = kMinCapacity;
    if(capacity < kMinInitCapacity){
        exit(EXIT_FAILURE);
    }

    while(capacity > true_capacity /kGrowthFactor){
        true_capacity *= kGrowthFactor;
    }
    return true_capacity;
}

void marray_upsize(MArray *arrptr){
    int old_capacity = arrptr->capacity;
    int new_capacity = marray_determine_capaticy(old_capacity);

    int *new_data = (int *)malloc(sizeof(int) * new_capacity);
    check_address(new_data);

    for (int i = 0; i < old_capacity; ++i)
    {
        *(new_data +i) = *(arrptr->data +i);
    }

    free(arrptr->data);
    arrptr->data = new_data;
    arrptr->capacity = new_capacity;
}

void marray_downsize(MArray *arrptr){
    int old_capacity = arrptr->capacity;
    int new_capacity = arrptr->capacity / kGrowthFactor;

    if (new_capacity < kMinCapacity)
    {
        new_capacity = kMinCapacity;
    }

    if (new_capacity != old_capacity)
    {
        int *new_data = (int *)malloc(sizeof(int) * new_capacity);
        check_address(new_data);
        for (int i = 0; i < arrptr->size; ++i) {
            *(new_data + i) = *(arrptr->data + i);
        }

        free(arrptr->data);

        arrptr->data = new_data;
        arrptr->capacity = new_capacity;
    }
}

int marray_size(MArray *arrptr){
    return arrptr->size;
}

void marray_push(MArray *arrptr, int item){
    marray_resize_for_size(arrptr , arrptr->size + 1);

    *(arrptr->data + arrptr->size) = item;
    ++(arrptr->size);
}

void marray_print(MArray *arrptr){
    printf("Size: %d\n", arrptr->size);
    printf("Capacity: %d\n", arrptr->capacity);

    printf("Items:\n");
    for (int i = 0; i < arrptr->size; ++i) {
        printf("%d: %d\n", i, *(arrptr->data + i));
    }

    printf("---------\n");
}

int marray_capacity(MArray *arrptr){
    return arrptr->capacity;
}

int marray_at(MArray *arrptr, int index){
    if (index< 0 || index >= arrptr->size)
    {
        exit(EXIT_FAILURE);
    }
    return *(arrptr->data + index);
}

bool marray_is_empty(MArray *arrptr){
    int is_empty = 0;
    if (arrptr->size == 0)
    {
        is_empty = 1;
    }
    return is_empty;
}

void marray_insert(MArray * arrptr,int index, int value){
    if (index< 0 || index >= arrptr->size)
    {
        exit(EXIT_FAILURE);
    }

    marray_resize_for_size(arrptr , arrptr->size +1);

    int end_index = arrptr->size-1;

    for (int i = end_index +1; i > index; --i)
    {
        *(arrptr->data + i) = *(arrptr->data + i -1);
    }

    *(arrptr->data + index) = value;

    arrptr->size += 1;
}

void marray_prepend(MArray *arrptr , int value){
    marray_insert(arrptr ,0 , value);
}

int marray_pop(MArray *arrptr){
    if (arrptr->size == 0)
    {
        exit(EXIT_FAILURE);
    }
    marray_resize_for_size(arrptr, arrptr->size -1);

    int pop_value = *(arrptr->data + arrptr->size -1);
    arrptr->size -= 1;
    return pop_value;
}

void marray_delete(MArray *arrptr, int index){
     if (index< 0 || index >= arrptr->size)
    {
        exit(EXIT_FAILURE);
    }

    marray_resize_for_size(arrptr ,arrptr->size -1);

    int end_index = arrptr->size -1;
    for (int i = index; i <end_index; ++i)
    {
        *(arrptr->data + i) = *(arrptr->data + i +1);
    }
    arrptr->size -= 1;

}

void marray_remove(MArray *arrptr, int value){
    for (int i = 0; i < arrptr->size; ++i)
    {
        int check_value = *(arrptr->data +i);

        if (check_value == value)
        {
            marray_delete(arrptr , i);
            --i;
        }
    }
}

int marray_find(MArray *arrptr, int value){
    int found_index = -1;
    for (int i = 0; i < arrptr->size; ++i)
    {
        int check_value = *(arrptr->data +i);
        if (check_value == value)
        {
            found_index = i;
            break;
        }
    }
    return found_index;
}

void check_address(void *p){
    if (p == NULL)
    {
        printf("Unable to allocate memory.\n");
        exit(EXIT_FAILURE);
    }


}

//test

void run_all_tests() {
  test_size_init();
  test_append();
  test_empty();
  test_resize();
  test_at();
  test_insert();
  test_prepend();
  test_pop();
  test_remove();
  test_find_exists();
  test_find_not_exists();
}

void test_size_init() {
  MArray *aptr = marray_new(5);
  int initial_size = marray_size(aptr);
  assert(initial_size == 0);
  marray_destory(aptr);
}

void test_append() {
  MArray *aptr = marray_new(2);
  marray_push(aptr, 2);
  marray_push(aptr, 12);
  int new_size = marray_size(aptr);
  assert(new_size == 2);
  marray_destory(aptr);
}

void test_resize() {
  MArray *aptr = marray_new(2);

  int old_capacity = marray_capacity(aptr);
  assert(old_capacity == 16);

  // forces a resize up
  for (int i = 0; i < 18; ++i) {
    marray_push(aptr, i + 1);
  }

  assert(marray_capacity(aptr) == 32);

  // forces a resize down
  for (int j = 0; j < 15; ++j) {
    marray_pop(aptr);
  }

  assert(marray_capacity(aptr) == 16);

  marray_destory(aptr);
}

void test_empty() {
  MArray *aptr = marray_new(2);
  bool empty = marray_is_empty(aptr);
  assert(empty == 1);
  marray_push(aptr, 1);
  empty = marray_is_empty(aptr);
  assert(empty == 0);
  marray_destory(aptr);
}

void test_at() {
  MArray *aptr = marray_new(12);
  for (int i = 0; i < 12; ++i) {
    marray_push(aptr, i + 3);
  }
  assert(marray_at(aptr, 6) == 9);
  marray_destory(aptr);
}

void test_insert() {
  MArray *aptr = marray_new(5);
  for (int i = 0; i < 5; ++i) {
    marray_push(aptr, i + 5);
  }
  marray_insert(aptr, 2, 47);
  assert(marray_at(aptr, 2) == 47);
  assert(marray_at(aptr, 3) == 7);
  marray_destory(aptr);
}

void test_prepend() {
  MArray *aptr = marray_new(5);
  for (int i = 0; i < 3; ++i) {
    marray_push(aptr, i + 1);
  }
  marray_prepend(aptr, 15);
  assert(marray_at(aptr, 0) == 15);
  assert(marray_at(aptr, 1) == 1);
  marray_destory(aptr);
}

void test_pop() {
  MArray *aptr = marray_new(5);
  for (int i = 0; i < 3; ++i) {
    marray_push(aptr, i + 1);
  }
  assert(aptr->size == 3);
  for (int j = 0; j < 3; ++j) {
    marray_pop(aptr);
  }
  assert(marray_is_empty(aptr) == 1);
  marray_destory(aptr);
}

void test_remove() {
  MArray *aptr = marray_new(5);
  marray_push(aptr, 12);
  marray_push(aptr, 3);
  marray_push(aptr, 41);
  marray_push(aptr, 12);
  marray_push(aptr, 12);
  marray_remove(aptr, 12);
  assert(marray_size(aptr) == 2);
  marray_destory(aptr);
}

void test_find_exists() {
  MArray *aptr = marray_new(5);
  marray_push(aptr, 1);
  marray_push(aptr, 2);
  marray_push(aptr, 3);
  marray_push(aptr, 4);
  marray_push(aptr, 5);
  assert(marray_find(aptr, 1) == 0);
  assert(marray_find(aptr, 4) == 3);
  assert(marray_find(aptr, 5) == 4);
  marray_destory(aptr);
}

void test_find_not_exists() {
  MArray *aptr = marray_new(3);
  marray_push(aptr, 1);
  marray_push(aptr, 2);
  marray_push(aptr, 3);
  assert(marray_find(aptr, 7) == -1);
  marray_destory(aptr);
}
