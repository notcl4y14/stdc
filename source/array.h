#ifndef STDC_ARRAY_H
#define STDC_ARRAY_H

// #define __STDC_PTR_AT(base, index, stride) ((char*)base + (index * stride))

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Declarations
 */

typedef struct array_t
{
	void*    data;
	uint32_t size;
	uint32_t stride;
	uint32_t capacity;

	uint32_t count;
} array_t;

array_t  array_new  (uint32_t size, uint32_t unit_size); // Creates a new array_t
array_t* array_newa (uint32_t size, uint32_t unit_size); // Allocates and creates a new array_t
void    array_free  (array_t* arr); // Frees array_t
void    array_freea (array_t* arr); // Frees array_t and its allocation

void    array_clear (array_t* arr); // Clears array_t
void    array_fill  (array_t* arr, void* from); // Fills array_t with a value from a pointer

void*   array_data (array_t* arr); // Returns a pointer to array_t data

void    array_mset  (array_t* arr, uint32_t loc, uint32_t value);
void    array_mcopy (array_t* arr, uint32_t loc, void* from);

void*   array_getp (array_t* arr, uint32_t loc); // Returns a pointer to array_t value
void    array_get  (array_t* arr, void* to, uint32_t loc); // Sets a value from array_t value
void    array_set  (array_t* arr, void* from, uint32_t loc); // Sets a value to array_t value

void    array_add    (array_t* arr, void* from); // Adds an element to an array
void    array_append (array_t* arr, void* from); // Alias for array_add
void    array_push   (array_t* arr, void* from); // Alias for array_add

void    array_rem  (array_t* arr, uint32_t loc); // Removes an element at given location
void    array_reme (array_t* arr, void* from); // Search and remove an element
void    array_remf (array_t* arr); // Removes first element
void    array_reml (array_t* arr); // Removes last element
void    array_pop  (array_t* arr); // Alias for array_reml

void    array_shift (array_t* arr, uint32_t begin);

/* Defines
 */

array_t array_new (uint32_t size, uint32_t unit_size)
{
	array_t arr;

	arr.data = malloc(size * unit_size);
	arr.size = size * unit_size;
	arr.stride = unit_size;
	arr.capacity = size;
	arr.count = 0;

	return arr;
}

array_t* array_newa (uint32_t size, uint32_t unit_size)
{
	array_t* arr = malloc(sizeof(array_t));

	arr->data = malloc(size * unit_size);
	arr->size = size * unit_size;
	arr->stride = unit_size;
	arr->capacity = size;
	arr->count = 0;

	return arr;
}

// 

void array_free (array_t* arr)
{
	free(arr->data);
}

void array_freea (array_t* arr)
{
	array_free(arr);

	free(arr);
}

// 

void array_clear (array_t* arr)
{
	memset(arr->data, 0, arr->size);
}

void array_fill (array_t* arr, void* from)
{
	uint32_t loop_idx = -1;
	uint32_t loop_end = arr->capacity;

	while (++loop_idx != loop_end)
	{
		memcpy(array_getp(arr, loop_idx), from, arr->stride);
		// memcpy((uint8_t*)(arr->data) + (loop_idx * arr->stride), from, arr->stride);
		// memcpy(__STDC_PTR_AT(arr->data, loop_idx, arr->stride), from, arr->stride);
	}
}

// 

void* array_data (array_t* arr)
{
	return arr->data;
}

// 

void array_mset (array_t* arr, uint32_t loc, uint32_t value)
{
	memset(array_getp(arr, loc), value, arr->stride);
}

void array_mcopy (array_t* arr, uint32_t loc, void* from)
{
	memcpy(array_getp(arr, loc), from, arr->stride);
}

// 

void* array_getp (array_t* arr, uint32_t loc)
{
	return (uint8_t*)(arr->data) + (loc * arr->stride);
}

void array_get (array_t* arr, void* to, uint32_t loc)
{
	memcpy(to, array_getp(arr, loc), arr->stride);
}

void array_set (array_t* arr, void* from, uint32_t loc)
{
	memcpy(array_getp(arr, loc), from, arr->stride);
}

// 

void array_add (array_t* arr, void* from)
{
	// memcpy((uint8_t*)(arr->data) + (arr->count * arr->stride), from, arr->stride);
	// memcpy(array_getp(arr, arr->count), from, arr->stride);
	array_mcopy(arr, arr->count, from);
	arr->count++;
}

// 

void array_rem (array_t* arr, uint32_t loc)
{
	// memset((uint8_t*)(arr->data) + (arr->count * arr->stride), 0, arr->stride);
	// memset(array_getp(arr, arr->count), 0, arr->stride);
	array_mset(arr, loc, 0);
	array_shift(arr, loc);
	arr->count--;
}

void array_remf (array_t* arr)
{
	array_rem(arr, 0);
}

void array_reml (array_t* arr)
{
	arr->count--;
	// memset((uint8_t*)(arr->data) + (arr->count * arr->stride), 0, arr->stride);
	array_mset(arr, arr->count, 0);
}

// 

void array_shift (array_t* arr, uint32_t begin)
{
	uint32_t loop_idx = begin - 1;
	uint32_t loop_end = arr->capacity;

	while (++loop_idx != loop_end)
	{
		if (loop_idx == loop_end - 1)
		{
			memset((uint8_t*)(arr->data) + (loop_idx * arr->stride), 0, arr->stride);
			break;
		}

		memcpy(
			(uint8_t*)(arr->data) + (loop_idx * arr->stride),
			(uint8_t*)(arr->data) + ((loop_idx + 1) * arr->stride),
			arr->stride
		);
	}
}

#endif