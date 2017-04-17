#ifndef PROJECT_ARRAY_H
#define PROJECT_ARRAY_H


#include <assert.h>
#include <stdbool.h>

const int kMinCapacity = 16;
const int kGrowthFactor = 2;
const int kShrinkFactor = 4;

typedef struct FGImplementationArray {
    int size;
    int capacity;
    int *data;
} MArray;

MArray * marray_new(int capaticy);
void marray_destory(MArray *arrtpr);

void marray_resize_for_size(MArray *arrtpr, int condidate_size);

int marray_determine_capaticy(int capaticy);

void marray_upsize(MArray *arrptr);

void marray_downsize(MArray *arrptr);

int marray_size(MArray *arrptr);

void marray_push(MArray *arrptr, int item);

void marray_print(MArray *arrptr);

int marray_capacity(MArray *arrptr);

int marray_at(MArray *arrptr, int index);

bool marray_is_empty(MArray *attptr);

void marray_insert(MArray * arrptr,int index, int value);

void marray_prepend(MArray *arrptr , int value);

int marray_pop(MArray *arrptr);

void marray_delete(MArray *arrptr, int index);

void marray_remove(MArray *arrptr, int value);

int marray_find(MArray *arrptr, int value);

void check_address(void *p);

//test

void test_append();
void test_size_init();
void test_append_past_capacity();
void test_capacity();
void test_empty();
void test_resize();
void test_at();
void test_insert();
void test_prepend();
void test_pop();
void test_remove();
void test_find_exists();
void test_find_not_exists();

#endif // PROJECT_ARRAYS
