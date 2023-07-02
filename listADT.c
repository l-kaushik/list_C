#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

// defining bool for older versions
#if __STDC_VERSION__ >= 19990L
#include <stdbool.h>
#else
typedef int bool;
#define true 1
#define false 0
#endif

#define AOF address_of_object
#define NULL_CHECK(ptr)                                                     \
    do                                                                      \
    {                                                                       \
        if ((ptr) == NULL)                                                  \
        {                                                                   \
            printf("Null pointer detected at %s:%d\n", __FILE__, __LINE__); \
            exit(EXIT_FAILURE);                                             \
        }                                                                   \
    } while (0)

typedef struct myArray
{
    int total_size;
    int used_size;
    int *base_ptr;
    bool isAllocated;
} list;

void createList(list *AOF, int tSize)
{
    AOF->total_size = tSize;
    AOF->used_size = 0;
    AOF->base_ptr = (int *)calloc(tSize, sizeof(int));
    NULL_CHECK(AOF->base_ptr);
    AOF->isAllocated = true;
}

void show(list *AOF)
{
    if (AOF->isAllocated != true)
    {
        printf("Error: Memory is not allocated for list");
        exit(EXIT_FAILURE);
    }
    assert(AOF->used_size > 0);

    printf("List items: [");
    for (int i = 0; i < AOF->used_size; i++)
    {
        printf("%d", AOF->base_ptr[i]);
        if (i < AOF->used_size - 1)
        {
            printf(", ");
        }
    }
    printf("]");
}

void setValues(list *AOF, int count, ...)
{
    va_list args;
    va_start(args, count);
    int availSize = AOF->total_size - AOF->used_size;
    int newSize = AOF->total_size + count - availSize;

    if (count >= availSize)
    {
        AOF->base_ptr = (int *)realloc(AOF->base_ptr, newSize * sizeof(int));
        AOF->total_size = newSize;
        NULL_CHECK(AOF->base_ptr);
    }

    int startIndex = AOF->used_size;

    for (int i = 0; i < count; ++i)
    {
        AOF->base_ptr[startIndex + i] = va_arg(args, int);
    }
    AOF->used_size += count;

    va_end(args);
}

void insert(list *AOF, int index, int element)
{
    if(index > AOF->used_size)
    {
        printf("Error: index out of range, %d is the last index",AOF->used_size);
        exit(EXIT_FAILURE);
    }

    if(AOF->used_size <= AOF->total_size)
    {
        AOF->base_ptr = (int *)realloc(AOF->base_ptr, (AOF->total_size + 1) * sizeof(int));
        AOF->total_size += 1;
        NULL_CHECK(AOF->base_ptr);
    }

    for (int i = AOF->used_size - 1; i >= index; i--)
    {
        AOF->base_ptr[i+1] = AOF->base_ptr[i];
    }

    AOF->base_ptr[index] = element;
    AOF->used_size += 1;

}

int main()
{
    list marks;
    createList(&marks, 10);
    setValues(&marks, 5, 1, 2, 3, 4, 5);
    show(&marks);
    insert(&marks, 5, 25);
    show(&marks);
    free(marks.base_ptr);

    return 0;
}
