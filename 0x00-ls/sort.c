#include "hls.h"

/**
 * compare - compares 2 file structs
 * @param: the parameter struct
 * @a: the first file
 * @b: the second file
 *
 * Return: -1, 0, or 1 depending if <, =, or >
 */
int compare(Param *param, File *a, File *b)
{
	ssize_t d;

	if (param->options & OPTION_S)
	{
		d = b->stat.st_size - a->stat.st_size;
		if (!d)
			return (_strcmp(a->name, b->name));
		return (d);
	}
	if (param->options & OPTION_t)
	{
		if (b->stat.st_mtim.tv_sec == a->stat.st_mtim.tv_sec)
		{
			if (b->stat.st_mtim.tv_nsec == a->stat.st_mtim.tv_nsec)
				return (_strcmp(a->name, b->name));
			return (b->stat.st_mtim.tv_nsec - a->stat.st_mtim.tv_nsec);
		}
		return (b->stat.st_mtim.tv_sec - a->stat.st_mtim.tv_sec);
	}
	return (_strcmp(a->name, b->name));
}

/**
 * swap - swaps 2 int values
 * @array: the integer array to sort
 * @size: the size of the array
 * @a: address of first value
 * @b: address of second value
 *
 * Return: void
 */
void swap(File **array, size_t size, File **a, File **b)
{
	File *temp;

	(void)size;
	(void)array;
	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * lomuto_partition - partitions the array
 * @param: the parameter struct
 * @array: the integer array to sort
 * @size: the size of the array
 * @lo: the low index of the sort range
 * @hi: the high index of the sort range
 *
 * Return: void
 */
size_t lomuto_partition(Param *param, File **array, size_t size, ssize_t lo,
	ssize_t hi)
{
	int i, j;
	File *pivot = array[hi];

	for (i = j = lo; j < hi; j++)
		if (compare(param, array[j], pivot) <= 0)
			swap(array, size, &array[j], &array[i++]);
	swap(array, size, &array[i], &array[hi]);

	return (i);
}

/**
 * quicksort - quicksorts via Lomuto partitioning scheme
 * @param: the parameter struct
 * @array: the integer array to sort
 * @size: the size of the array
 * @lo: the low index of the sort range
 * @hi: the high index of the sort range
 *
 * Return: void
 */
void quicksort(Param *param, File **array, size_t size, ssize_t lo, ssize_t hi)
{
	if (lo < hi)
	{
		size_t p = lomuto_partition(param, array, size, lo, hi);

		quicksort(param, array, size, lo, p - 1);
		quicksort(param, array, size, p + 1, hi);
	}
}

/**
 * quick_sort - calls quicksort
 * @param: the parameter struct
 * @array: the integer array to sort
 * @size: the size of the array
 *
 * Return: void
 */
void quick_sort(Param *param, File **array, size_t size)
{
	if (!array || !size)
		return;
	quicksort(param, array, size, 0, size - 1);
}
