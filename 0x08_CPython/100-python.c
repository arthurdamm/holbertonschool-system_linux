#include <Python.h>

void print_python_int(PyObject *p);
int long_to_str(PyObject *o, char **bytes_str);
char *decimal_digits_to_str(digit *pout, ssize_t size, int negative);

/**
 * print_python_int - prints a long python integer
 * @p: pointer to python int
 */
void print_python_int(PyObject *p)
{
	char *str = NULL;

	if (long_to_str(p, &str) == -1)
		return;
	printf("%s\n", str);
	free(str);
}

/**
 * long_to_str - renders a python long int as a string
 * @o: pointer to python int
 * @str: address of char pointer which will be assiged
 * Return: -1 on error else 0
 */
int long_to_str(PyObject *o, char **str)
{
	PyLongObject *a;
	ssize_t size, size_a, i, j;
	digit *pout, *pin;
	int negative, d;

	a = (PyLongObject *)o;
	size_a = Py_SIZE(a) < 0 ? -Py_SIZE(a) : Py_SIZE(a);
	negative = Py_SIZE(a) < 0;

	d = (33 * _PyLong_DECIMAL_SHIFT) /
		(10 * PyLong_SHIFT - 33 * _PyLong_DECIMAL_SHIFT);
	size = 1 + size_a + size_a / d;
	pout = calloc(sizeof(digit), size);
	if (!pout)
		return (-1);

	pin = a->ob_digit;
	size = 0;
	for (i = size_a; --i >= 0; )
	{
		digit hi = pin[i];

		for (j = 0; j < size; j++)
		{
			twodigits z = (twodigits)pout[j] << PyLong_SHIFT | hi;

			hi = (digit)(z / _PyLong_DECIMAL_BASE);
			pout[j] = (digit)(z - (twodigits)hi *
							  _PyLong_DECIMAL_BASE);
		}
		while (hi)
		{
			pout[size++] = hi % _PyLong_DECIMAL_BASE;
			hi /= _PyLong_DECIMAL_BASE;
		}
	}
	if (size == 0)
		pout[size++] = 0;

	*str = decimal_digits_to_str(pout, size, negative);
	return (0);
}

/**
 * decimal_digits_to_str - renders vector of decimal digits to string
 * @pout: vector of decimal digits
 * @size: the size of the vector
 * @negative: 1 if number is negative
 * Return: allocated string representation of digits
 */
char *decimal_digits_to_str(digit *pout, ssize_t size, int negative)
{
	digit rem, tenpow;
	char *str, *p;
	ssize_t strlen, i, j;

	strlen = negative + 1 + (size - 1) * _PyLong_DECIMAL_SHIFT;
	tenpow = 10;
	rem = pout[size - 1];
	while (rem >= tenpow)
	{
		tenpow *= 10;
		strlen++;
	}

	str = calloc(1, strlen + 1);
	if (!str)
		return (NULL);
	p = str + strlen;
	for (i = 0; i < size - 1; i++)
	{
		rem = pout[i];
		for (j = 0; j < _PyLong_DECIMAL_SHIFT; j++)
		{
			*--p = '0' + rem % 10;
			rem /= 10;
		}
	}
	rem = pout[i];
	do {
		*--p = '0' + rem % 10;
		rem /= 10;
	} while (rem != 0);

	if (negative)
		*--p = '-';
	return (str);
}
