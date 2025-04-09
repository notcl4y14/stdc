#ifndef STDC_ARRAY_H
#define STDC_ARRAY_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* ================
 * Declarations
 * ================
 */

typedef struct array_t
{
	void*    data;
	uint32_t size;
	uint32_t stride;
	uint32_t capacity;

	uint32_t count;
} array_t;

/**
 * Creates a new Array instance.
 * @param int capacity n of elements an array can store
 * @param int unit_size size of an element
 * @return array_t
 */
array_t  array_new  (uint32_t capacity, uint32_t unit_size);

/**
 * Allocates space for a new Array instance (creates it too).
 * @param int capacity n of elements an array can store
 * @param int unit_size size of an element
 * @return array_t*
 */
array_t* array_newa (uint32_t capacity, uint32_t unit_size); // Allocates and creates a new array_t

/**
 * Initializes an Array instance.
 * @param array_t* arr array pointer
 * @param int capacity n of elements an array can store
 * @param int unit_size size of an element
 * @return array_t
 */
void     array_init  (array_t* arr, uint32_t capacity, uint32_t unit_size);


/**
 * Frees Array instance.
 * @param array_t* arr array pointer
 * @return void
 */
void    array_free  (array_t* arr); // Frees array_t

/**
 * Frees allocated Array instance.
 * @param array_t* arr array pointer
 * @return void
 */
void    array_freea (array_t* arr); // Frees array_t and its allocation


/**
 * Copies an array to another array.
 * @param array_t* arr_to detination array pointer
 * @param array_t* arr_from source array pointer
 * @return void
 */
void    array_copy (array_t* arr_to, array_t* arr_from);


/**
 * Clears data in array.
 * @param array_t* arr array pointer
 * @return void
 */
void    array_clear (array_t* arr); // Clears array_t

/**
 * Fills array data with a specific value.
 * @param array_t* arr array pointer
 * @param void* from value pointer
 * @return void
 */
void    array_fill  (array_t* arr, void* from); // Fills array_t with a value from a pointer


/**
 * memset()-s an array value.
 * @param array_t* arr array pointer
 * @param int loc element index
 * @param int value element value
 * @return void
 */
void    array_mset  (array_t* arr, uint32_t loc, uint32_t value);

/**
 * memcpy()-s an array value.
 * @param array_t* arr array pointer
 * @param int loc element index
 * @param void* from value pointer
 * @return void
 */
void    array_mcopy (array_t* arr, uint32_t loc, void* from);


/**
 * Returns a pointer to an array element.
 * @param array_t* arr array pointer
 * @param int loc element index
 * @return void*
 */
void*   array_getp (array_t* arr, uint32_t loc); // Returns a pointer to array_t value

/**
 * Returns a value of an array element.
 * @param array_t* arr array pointer
 * @param void* to return variable
 * @param int loc element index
 * @return void
 */
void    array_get  (array_t* arr, void* to, uint32_t loc); // Sets a value from array_t value

/**
 * Sets a value of an array element.
 * @param array_t* arr array pointer
 * @param void* from value pointer
 * @param int loc element index
 * @return void
 */
void    array_set  (array_t* arr, void* from, uint32_t loc); // Sets a value to array_t value


/**
 * Adds an element to an array.
 * @param array_t* arr array pointer
 * @param void* from value pointer
 * @return void
 */
void    array_add    (array_t* arr, void* from); // Adds an element to an array
void    array_append (array_t* arr, void* from); // Alias for array_add
void    array_push   (array_t* arr, void* from); // Alias for array_add


/**
 * Removes an element from an array.
 * @param array_t* arr array pointer
 * @param int loc element index
 * @return void
 */
void    array_rem  (array_t* arr, uint32_t loc); // Removes an element at given location

/**
 * Removes an element from an array by searching it.
 * @param array_t* arr array pointer
 * @param void* from element instance
 * @return void
 */
void    array_reme (array_t* arr, void* from); // Search and remove an element

/**
 * Removes first element from an array.
 * @param array_t* arr array pointer
 * @return void
 */
void    array_remf (array_t* arr); // Removes first element

/**
 * Removes last element from an array.
 * @param array_t* arr array pointer
 * @return void
 */
void    array_reml (array_t* arr); // Removes last element
void    array_pop  (array_t* arr); // Alias for array_reml


/**
 * Shifts the array. Moves all the values after `begin` index to the left side.
 * @param array_t* arr array pointer
 * @param int begin element index
 * @return void
 */
void    array_shift (array_t* arr, uint32_t begin);

/* ================
 * Defines
 * ================
 */

array_t array_new (uint32_t capacity, uint32_t unit_size)
{
	array_t arr;
	array_init(&arr, capacity, unit_size);

	return arr;
}

array_t* array_newa (uint32_t capacity, uint32_t unit_size)
{
	array_t* arr = malloc(sizeof(array_t));
	array_init(arr, capacity, unit_size);

	return arr;
}

void array_init (array_t* arr, uint32_t capacity, uint32_t unit_size)
{
	arr->data = malloc(capacity * unit_size);
	arr->size = capacity * unit_size;
	arr->stride = unit_size;
	arr->capacity = capacity;
	arr->count = 0;
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

void array_copy (array_t* arr_to, array_t* arr_from)
{
	memcpy(arr_to, arr_from, sizeof(array_t));

	// Copying arr_from data to arr_to data
	const uint32_t copy_size = arr_to->size;
	arr_to->data = malloc(copy_size);
	memcpy(arr_to->data, arr_from->data, copy_size);
}

// 

void array_clear (array_t* arr)
{
	memset(arr->data, 0, arr->size);
	arr->count = 0;
}

void array_fill (array_t* arr, void* from)
{
	uint32_t loop_idx = -1;
	uint32_t loop_end = arr->capacity;

	while (++loop_idx != loop_end)
	{
		array_mcopy(arr, loop_idx, from);
	}
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
	array_mcopy(arr, arr->count, from);
	arr->count++;
}

// 

void array_rem (array_t* arr, uint32_t loc)
{
	array_mset(arr, loc, 0);
	array_shift(arr, loc);
	arr->count--;
}

void array_remf (array_t* arr)
{
	// Compared to array_reml, array_remf don't decrease count,
	// because array_rem already does this
	array_rem(arr, 0);
}

void array_reml (array_t* arr)
{
	// Decreasing count because array_mset doesn't
	// (And also before calling array_mset because it depends on count)
	arr->count--;
	array_mset(arr, arr->count, 0);
}

// 

void array_shift (array_t* arr, uint32_t begin)
{
	const void* src = array_getp(arr, begin);
	const void* dest = (uint8_t*)(src) - (arr->stride); // No need to get the pointer twice
	const uint32_t size = (arr->capacity - begin) * arr->stride;
	memcpy((void*)dest, src, size); // TODO: Remove const from src if it's not needed
	array_mset(arr, arr->capacity - 1, 0);
}

#endif