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

void show(list *addressOfObject){
    for (int i = 0; i < addressOfObject->used_size; i++)
    {
        printf("%d\t",addressOfObject->base_ptr[i]);
    }
    
}

void setValue(list *addressOfObject)
{
    for (int i = 0; i < addressOfObject->used_size; i++)
    {
        printf("Enter element %d\n", i);
        scanf("%d",&(addressOfObject->base_ptr[i]));
    }
    
}

int main()
{
    list marks;

    createList(&marks,20,5);
    setValue(&marks);
    show(&marks);

    return 0;
}
