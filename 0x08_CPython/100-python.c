#include <Python.h>

int long_to_decimal_string_internal(PyObject *aa,
                                PyObject **p_output,
                                char **bytes_str)
{
    PyLongObject *scratch, *a;
    PyObject *str = NULL;
    Py_ssize_t size, strlen, size_a, i, j;
    digit *pout, *pin, rem, tenpow;
    int negative;
    int d;
    enum PyUnicode_Kind kind;

    a = (PyLongObject *)aa;
    size_a = Py_SIZE(a) < 0 ? -Py_SIZE(a) : Py_SIZE(a);
    negative = Py_SIZE(a) < 0;

    /* quick and dirty upper bound for the number of digits
       required to express a in base _PyLong_DECIMAL_BASE:
         #digits = 1 + floor(log2(a) / log2(_PyLong_DECIMAL_BASE))
       But log2(a) < size_a * PyLong_SHIFT, and
       log2(_PyLong_DECIMAL_BASE) = log2(10) * _PyLong_DECIMAL_SHIFT
                                  > 3.3 * _PyLong_DECIMAL_SHIFT
         size_a * PyLong_SHIFT / (3.3 * _PyLong_DECIMAL_SHIFT) =
             size_a + size_a / d < size_a + size_a / floor(d),
       where d = (3.3 * _PyLong_DECIMAL_SHIFT) /
                 (PyLong_SHIFT - 3.3 * _PyLong_DECIMAL_SHIFT)
    */
    d = (33 * _PyLong_DECIMAL_SHIFT) /
        (10 * PyLong_SHIFT - 33 * _PyLong_DECIMAL_SHIFT);
    /* assert(size_a < PY_SSIZE_T_MAX/2); */
    size = 1 + size_a + size_a / d;
    scratch = _PyLong_New(size);
    if (scratch == NULL)
        return -1;

    /* convert array of base _PyLong_BASE digits in pin to an array of
       base _PyLong_DECIMAL_BASE digits in pout, following Knuth (TAOCP,
       Volume 2 (3rd edn), section 4.4, Method 1b). */
    pin = a->ob_digit;
    pout = scratch->ob_digit;
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

    {
        str = PyUnicode_New(strlen, '9');
        if (str == NULL) {
            Py_DECREF(scratch);
            return -1;
        }
        kind = PyUnicode_KIND(str);
    }

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

#define WRITE_UNICODE_DIGITS(TYPE)                                    \
    do {                                                              \
        p = (TYPE*)PyUnicode_DATA(str) + strlen;                  \
                                                                      \
        WRITE_DIGITS(p);                                              \
                                                                      \
        /* check we've counted correctly */                           \
        assert(p == (TYPE*)PyUnicode_DATA(str));                  \
    } while (0)

    /* fill the string right-to-left */

    if (kind == PyUnicode_1BYTE_KIND) {
        Py_UCS1 *p;
        WRITE_UNICODE_DIGITS(Py_UCS1);
    }
    else if (kind == PyUnicode_2BYTE_KIND) {
        Py_UCS2 *p;
        WRITE_UNICODE_DIGITS(Py_UCS2);
    }
    else {
        Py_UCS4 *p;
        assert (kind == PyUnicode_4BYTE_KIND);
        WRITE_UNICODE_DIGITS(Py_UCS4);
    }
#undef WRITE_DIGITS
#undef WRITE_UNICODE_DIGITS

    Py_DECREF(scratch);
    {
        *p_output = (PyObject *)str;
    }
    return 0;
	(void)bytes_str;
}

PyObject *
print_python_int(PyObject *aa)
{
    PyObject *v;
    if (long_to_decimal_string_internal(aa, &v, NULL) == -1)
        return NULL;
	wprintf(L"%ls\n", PyUnicode_AS_UNICODE(v));
    return v;
}
