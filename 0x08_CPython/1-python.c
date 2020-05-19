#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_python_list - prints info about a python list
 * @p: pointer to python object struct
 */
void print_python_list(PyObject *p)
{
	ssize_t sz = ((PyVarObject *)p)->ob_size, i = 0;

	printf("%s", "[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", sz);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < sz; i++)
		printf("Element %ld: %s\n", i,
			((PyListObject *)p)->ob_item[i]->ob_type->tp_name);
}
