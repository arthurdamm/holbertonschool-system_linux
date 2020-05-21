
#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

/**
 * print_python_string - prints a Python string
 * @p: pointer to PyObject
 */
void print_python_string(PyObject *p)
{
	wprintf(L"[.] string object info\n");
	if (!p || p->ob_type != &PyUnicode_Type)
	{
		wprintf(L"  [ERROR] Invalid String Object\n");
		return;
	}
	if (((PyASCIIObject *)p)->state.ascii)
		wprintf(L"  type: compact ascii\n");
	else
		wprintf(L"  type: compact unicode object\n");
	wprintf(L"  length: %ld\n", ((PyASCIIObject *)p)->length);
	wprintf(L"  value: %ls\n", PyUnicode_AS_UNICODE(p));
}
