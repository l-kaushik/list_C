#include <stdio.h>
#include <stdlib.h>

typedef struct myArray
{
    int total_size;
    int used_size;
    int *base_ptr;
} list;

void createList(list *addressOfObject, int tSize, int uSize)
{
    addressOfObject->total_size = tSize;
    addressOfObject->used_size = uSize;
    addressOfObject->base_ptr = (int *) malloc(tSize*sizeof(int));

}

int main()
{
    list marks;

    createList(&marks,20,10);

    return 0;
}
