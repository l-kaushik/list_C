#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct myArray
{
    int total_size;
    int used_size;
    int *base_ptr; 
} list;

void createList(list *addressOfObject, int tSize)
{
    addressOfObject->total_size = tSize;
    addressOfObject->used_size = 0;
    addressOfObject->base_ptr = (int *)malloc(tSize * sizeof(int));
}

void show(list *addressOfObject)
{
    for (int i = 0; i < addressOfObject->used_size; i++)
    {
        printf("%d\t", addressOfObject->base_ptr[i]);
    }
}

void setValue(list *addressOfObject, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Enter element %d\n", i);
        scanf("%d", &(addressOfObject->base_ptr[i]));
    }

    addressOfObject->used_size += count;
}

void setValues(list *addressOfObject, int count, ...)
{
    va_list args;
    va_start(args, count);

    int startIndex = addressOfObject->used_size;

    for (int i = 0; i < count; ++i)
    {
        addressOfObject->base_ptr[startIndex + i] = va_arg(args, int);
    }
    printf("value in used_size is %d\t",addressOfObject->used_size);
    addressOfObject->used_size += count;

    va_end(args);
}

int main()
{
    list marks;

    createList(&marks, 10);

    setValue(&marks, 3);
    setValues(&marks, 5, 3,4,3,2,90);

    show(&marks);

    free(marks.base_ptr);

    return 0;
}
