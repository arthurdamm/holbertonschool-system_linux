#include <Python.h>

int long_to_decimal_string_internal(PyObject *aa, char **bytes_str)
{
    PyLongObject *a;
    char *str = NULL;
    Py_ssize_t size, strlen, size_a, i, j;
    digit *pout, *pin, rem, tenpow;
    int negative;
    int d;

    a = (PyLongObject *)aa;
    size_a = Py_SIZE(a) < 0 ? -Py_SIZE(a) : Py_SIZE(a);
    negative = Py_SIZE(a) < 0;

    d = (33 * _PyLong_DECIMAL_SHIFT) /
        (10 * PyLong_SHIFT - 33 * _PyLong_DECIMAL_SHIFT);
    /* assert(size_a < PY_SSIZE_T_MAX/2); */
    size = 1 + size_a + size_a / d;
	pout = calloc(sizeof(digit), size);
    if (!pout)
		return (-1);

    /* convert array of base _PyLong_BASE digits in pin to an array of
       base _PyLong_DECIMAL_BASE digits in pout, following Knuth (TAOCP,
       Volume 2 (3rd edn), section 4.4, Method 1b). */
    pin = a->ob_digit;
    size = 0;
    for (i = size_a; --i >= 0; ) {
        digit hi = pin[i];
        for (j = 0; j < size; j++) {
            twodigits z = (twodigits)pout[j] << PyLong_SHIFT | hi;
            hi = (digit)(z / _PyLong_DECIMAL_BASE);
            pout[j] = (digit)(z - (twodigits)hi *
                              _PyLong_DECIMAL_BASE);
        }
        while (hi) {
            pout[size++] = hi % _PyLong_DECIMAL_BASE;
            hi /= _PyLong_DECIMAL_BASE;
        }
    }
    /* pout should have at least one digit, so that the case when a = 0
       works correctly */
    if (size == 0)
        pout[size++] = 0;

    /* calculate exact length of output string, and allocate */
    strlen = negative + 1 + (size - 1) * _PyLong_DECIMAL_SHIFT;
    tenpow = 10;
    rem = pout[size-1];
    while (rem >= tenpow) {
        tenpow *= 10;
        strlen++;
    }

	str = calloc(1, strlen + 1);
	if (!str)
		return -1;

#define WRITE_DIGITS(p)                                               \
    do {                                                              \
        /* pout[0] through pout[size-2] contribute exactly            \
           _PyLong_DECIMAL_SHIFT digits each */                       \
        for (i=0; i < size - 1; i++) {                                \
            rem = pout[i];                                            \
            for (j = 0; j < _PyLong_DECIMAL_SHIFT; j++) {             \
                *--p = '0' + rem % 10;                                \
                rem /= 10;                                            \
            }                                                         \
        }                                                             \
        /* pout[size-1]: always produce at least one decimal digit */ \
        rem = pout[i];                                                \
        do {                                                          \
            *--p = '0' + rem % 10;                                    \
            rem /= 10;                                                \
        } while (rem != 0);                                           \
                                                                      \
        /* and sign */                                                \
        if (negative)                                                 \
            *--p = '-';                                               \
    } while (0)

#define WRITE_UNICODE_DIGITS                                    \
    do {                                                              \
        p = str + strlen;                  \
        WRITE_DIGITS(p);                                              \
    } while (0)

    /* fill the string right-to-left */

        char *p;
        WRITE_UNICODE_DIGITS;

#undef WRITE_DIGITS
#undef WRITE_UNICODE_DIGITS

	printf("%s\n", str);
    return 0;
	(void)bytes_str;
}

void print_python_int(PyObject *aa)
{
    if (long_to_decimal_string_internal(aa, NULL) == -1)
        return;
	// wprintf(L"%ls\n", PyUnicode_AS_UNICODE(v));
    return;
}
