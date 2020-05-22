#include <Python.h>
#include <stdio.h>

/**
 * print_python_int - prints a python integer
 * @p: pointer to python object
 */
void print_python_int(PyObject *p)
{
	ssize_t sz, i, neg;
	unsigned long num = 0;

	setbuf(stdout, NULL);
	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}
	sz = ((PyVarObject *)p)->ob_size;
	neg = sz < 0;
	sz = neg ? -sz : sz;
	if (sz > 3 || (sz == 3 && ((PyLongObject *)p)->ob_digit[2] > 0xf))
	{
		printf("C unsigned long int overflow\n");
		return;
	}
	for (i = 0; i < sz; i++)
	{
		int sh = PyLong_SHIFT * i;
		unsigned long sub =
			((unsigned long)((PyLongObject *)p)->ob_digit[i]) * (1UL << (sh));
		num += sub;
	}
	if (neg)
		printf("-");
	printf("%lu\n", num);
}
