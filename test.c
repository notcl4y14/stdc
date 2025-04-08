#include <array.h>

#include <stdio.h>

int main ()
{
	array_t* array = array_newa(10, sizeof(int));

	int value = 10;
	array_add(array, &value);
	value += 10;
	array_add(array, &value);
	value += 10;
	array_add(array, &value);
	value += 10;
	array_add(array, &value);
	value += 10;
	array_add(array, &value);

	array_remf(array);
	array_reml(array);

	for (uint32_t i = 0; i < array->count; i++)
	{
		int* v = array_getp(array, i);
		printf("%d, ", *v);
	}

	array_freea(array);
}