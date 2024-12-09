
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "heap.h"

#define KEY_NOT_PRESENT -1

    heap->capacity = capacity; //establish a relationship. Capacity is how much the array can hold
// constructor. I am establishing the relationship between both structs. Why? Because if i dont then whats the point of putting two structs.
heap_t *heap_create(int capacity)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (heap_node_t *)malloc(sizeof(heap_node_t) * capacity);
    heap->capacity = capacity; // establish a relationship. Capacity is how much the array can hold
    heap->size = 0;            // This is used to determine what level a individual node is on.

    return heap;
}

void heap_free(heap_t *heap)
{
    if (heap != NULL)
    {
        if (heap->data != NULL)
        {
            free(heap->data);
        }
        free(heap);
    }
}

unsigned int heap_size(heap_t *heap) { return heap->size; }

unsigned int heap_parent(unsigned int index)
{
    if (index == 0)
    {
        return 0;
    }
    return (index - 1) / 2;
}

unsigned int heap_left_child(unsigned int index) { return 2 * index + 1; }

unsigned int heap_right_child(unsigned int index) { return 2 * index + 2; }

unsigned int heap_level(unsigned int index)
{
    if (index == 0)
    {
        return 0;
    }
    return (unsigned int)log2(index + 1);
}

void heap_print(heap_t *heap)
{
    for (int ix = 0; ix < heap_size(heap); ix++)
    {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    printf("\n");
}

void heap_swap(heap_t *heap, int index1, int index2)
{
    heap_node_t parent = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = parent;
}

void heap_bubble_up(heap_t *heap, int index)
{
    while (index > 0)
    {
        int parent = heap_parent(index);
        if (heap->data[index].key < heap->data[parent].key)
        {
            heap_swap(heap, index, parent);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void heap_bubble_down(heap_t *heap, int index)
{
    while (true)
    {
        int left = heap_left_child(index);
        int right = heap_right_child(index);
        int parent = heap_parent(index);

        if (heap->data[left].key < heap->data[parent].key)
        {
            heap_swap(heap, left, parent);
            if (left >= heap->size)
            {
                break;
            }
        }
        else if (heap->data[right].key < heap->data[parent].key)
        {
            heap_swap(heap, right, parent);
            if (right >= heap->size)
            {
                break;
            }
        }
    }
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data)
{
    if (heap_size(heap) == heap->capacity)
    {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

heap_value_t heap_remove_min(heap_t *heap)
{
    if (heap_size(heap) == 0)
    {
        return NULL;
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    // move last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}
