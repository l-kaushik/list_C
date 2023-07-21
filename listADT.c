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
#define LIST(name,initialSize)\
    list name;\
    createList(&name, initialSize);\

#define LIST_VAL(name,count,...)\
    list name;\
    createList(&name, count);\
    setValues(&name,count,__VA_ARGS__)

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
    void *self;
    bool isAllocated;
    bool _CLEAR_;

    void (*show)();
    void (*setValues)();
    void (*insert)();
    void (*append)();
    void (*pop)();
    void (*destroy)();
    void(*clear)();
    int(*count)();

    // void(*copy)();
    // void(*extend)();
    // void(*index)();
    // void(*insert)();
    // void(*remove)();
    // void(*reverse)();
    // void(*sort)();
} list;

void createList(list *, int);
void show(list *);
void setValues(list *, int, ...);
void insert(list *, int, int);
void append(list *, int);
void popItem(list *, int);
void destroyList(list *);
void clear(list *);
int count(list *, int);

void createList(list *AOF, int tSize)
{
    AOF->self = (list *)AOF;
    AOF->total_size = tSize;
    AOF->used_size = 0;
    AOF->base_ptr = (int *)calloc(tSize, sizeof(int));
    NULL_CHECK(AOF->base_ptr);
    AOF->isAllocated = true;
    AOF->_CLEAR_ = false;

    AOF->show = show;
    AOF->setValues = (void *)setValues;
    AOF->insert = insert;
    AOF->append = append;
    AOF->pop = popItem;
    AOF->destroy = destroyList;
    AOF->clear = clear;
    AOF->count = count;
}

void show(list *AOF)
{
    if (AOF->isAllocated != true)
    {
        printf("Error: Memory is not allocated for list");
        exit(EXIT_FAILURE);
    }

    if(AOF->_CLEAR_ == true)
    {
        printf("List items: []");
        return ;
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

    if (count > availSize)
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

    AOF->_CLEAR_ = false;
}

void insert(list *AOF, int index, int element)
{

    if (index > AOF->used_size)
    {
        printf("Error: index out of range, %d is the last index", AOF->used_size);
        exit(EXIT_FAILURE);
    }

    if (AOF->used_size <= AOF->total_size)
    {
        AOF->base_ptr = (int *)realloc(AOF->base_ptr, (AOF->total_size + 1) * sizeof(int));
        AOF->total_size += 1;
        NULL_CHECK(AOF->base_ptr);
    }

    for (int i = AOF->used_size - 1; i >= index; i--)
    {
        AOF->base_ptr[i + 1] = AOF->base_ptr[i];
    }

    AOF->base_ptr[index] = element;
    AOF->used_size += 1;

    AOF->_CLEAR_ = false;
}

void append(list *AOF, int element)
{
    insert(AOF, AOF->used_size, element);
    AOF->_CLEAR_ = false;
}

void popItem(list *AOF, int index)
{
    if (index > AOF->used_size)
    {
        printf("Error: index out of range, %d is the last index", AOF->used_size);
        exit(EXIT_FAILURE);
    }

    for(int i = index; i < AOF->used_size-1; i++)
    {
        AOF->base_ptr[i] = AOF->base_ptr[i + 1];
    }

    AOF->used_size -= 1;
}

void clear(list *AOF)
{

    AOF->base_ptr = (int *)realloc(AOF->base_ptr, 1 * sizeof(int));
    AOF->_CLEAR_ = true;
    AOF->total_size = 1;
    AOF->used_size = 0;

}

int count(list *AOF, int num)
{
    int count = 0;
    for(int i = 0; i < AOF->used_size; i++)
    {
        if(num == AOF->base_ptr[i])
            count++;
    }
    return count;
}

void destroyList(list *AOF)
{
    free(AOF->base_ptr);
    AOF->base_ptr = NULL; // Reset the pointer to NULL
    AOF->self = NULL;     // Reset the self pointer to NULL
    AOF->isAllocated = false;
    AOF->_CLEAR_ = false;
    AOF->total_size = 0;
    AOF->used_size = 0;

    AOF->show = NULL;
    AOF->setValues = NULL;
    AOF->insert = NULL;
    AOF->append = NULL;
    AOF->pop = NULL;
    AOF->destroy = NULL;
}

int main()
{
    // list marks;
    // createList(&marks, 5);
    // marks.setValues(marks.self, 5, 1, 2, 3, 4, 5);
    LIST_VAL(marks,5,1,2,3,4,5);
    marks.insert(marks.self, 2, 25);
    marks.append(marks.self, 30);
    marks.show(marks.self);
    printf("\n");
    marks.setValues(marks.self,5,1,2,3,4,5);
    printf("\n");
    marks.show(marks.self);
    printf("%d",marks.count(marks.self,5));
    marks.destroy(marks.self);

    return 0;
}
