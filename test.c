#include <array.h>

#include <stdio.h>

void print_arr (array_t* array)
{
	uint32_t loop_idx = -1;
	uint32_t loop_end = array->count;

	while (++loop_idx != loop_end)
	{
		const uint32_t value = *(uint32_t*)array_getp(array, loop_idx);
		printf("%d", value);

		if (loop_idx != loop_end - 1)
		{
			printf(", ");
		}
	}
}

int main ()
{
	array_t* array1 = malloc(sizeof(array_t));
	array_t* array2 = malloc(sizeof(array_t));

	array_init(array1, 10, sizeof(uint32_t));

	{
		uint32_t value = 10;
		array_add(array1, &value);

		value = value * 2;
		array_add(array1, &value);
		
		value = value * 2;
		array_add(array1, &value);
		
		value = value * 2;
		array_add(array1, &value);
		
		value = value * 2;
		array_add(array1, &value);
	}

	array_copy(array2, array1);

	array_remf(array2);
	array_reml(array2);

	print_arr(array1); printf("\n");
	print_arr(array2); printf("\n");

	array_freea(array1);
}