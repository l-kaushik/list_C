#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#define AOF address_of_object
#define NULL_CHECK(ptr) do { \
    if ((ptr) == NULL) { \
        printf("Null pointer detected at %s:%d\n", __FILE__, __LINE__); \
    } \
} while (0)

typedef struct myArray
{
    int total_size;
    int used_size;
    int *base_ptr; 
} list;

void createList(list *AOF, int tSize)
{
    AOF->total_size = tSize;
    AOF->used_size = 0;
    AOF->base_ptr = (int *)malloc(tSize * sizeof(int));
    NULL_CHECK(AOF->base_ptr);
}

void show(list *AOF)
{

    assert(AOF->used_size > 0);

    if(AOF->used_size > 0){
        printf("Error: No values are present in the list\n");
        return;
    }

    for (int i = 0; i < AOF->used_size; i++)
    {
        printf("%d\t", AOF->base_ptr[i]);
    }
}

void setValue(list *AOF, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Enter element %d\n", i);
        scanf("%d", &(AOF->base_ptr[i]));
    }

    AOF->used_size += count;
}

void setValues(list *AOF, int count, ...)
{
    va_list args;
    va_start(args, count);
    int availSize = AOF->total_size - AOF->used_size;

    if (count > availSize)
    {
        AOF->base_ptr = (int *)realloc(AOF->base_ptr, (AOF->total_size + count - availSize)*sizeof(int));
        NULL_CHECK(AOF->base_ptr);   
    }

    int startIndex = AOF->used_size;

    for (int i = 0; i < count; ++i)
    {
        AOF->base_ptr[startIndex + i] = va_arg(args, int);

    }
    printf("value in used_size is %d\t",AOF->used_size);
    AOF->used_size += count;

    va_end(args);
}

int main()
{
    list marks;
    createList(&marks, 10);

    setValue(&marks, 3);
    setValues(&marks, 5, 1,2,3,4,5);
    setValues(&marks, 5, 6,7,8,9,10);
    setValues(&marks, 5, 11,12,13,14,15);

    show(&marks);

    free(marks.base_ptr);

    return 0;
}
