#include <stdio.h>
#include "ft_printf.h"

// #include "../libftprintf"

// must handle
// any of conversion [cspdiuxX%]
// precision [.]
// any combination of [# +0] (including redundant combinations like %-0.0f)

/*
The overall syntax of a conversion specification is:
		%[argument$][flags][width][.precision][length modifier]conversion

	Conversion
		[cspdiuxX%]

	Precision
		An optional precision, in the form of a period ('.')  followed by
		an optional decimal digit string.

	Flag characters
       The character % is followed by zero or more of the following
       flags:

       #      The value should be converted to an "alternate form".  For
              o conversions, the first character of the output string is
              made zero (by prefixing a 0 if it was not zero already).
              For x and X conversions, a nonzero result has the string
              "0x" (or "0X" for X conversions) prepended to it.  For a,
              A, e, E, f, F, g, and G conversions, the result will always
              contain a decimal point, even if no digits follow it
              (normally, a decimal point appears in the results of those
              conversions only if a digit follows).  For g and G
              conversions, trailing zeros are not removed from the result
              as they would otherwise be.  For m, if errno contains a
              valid error code, the output of strerrorname_np(errno) is
              printed; otherwise, the value stored in errno is printed as
              a decimal number.  For other conversions, the result is
              undefined.

       0      The value should be zero padded.  For d, i, o, u, x, X, a,
              A, e, E, f, F, g, and G conversions, the converted value is
              padded on the left with zeros rather than blanks.  If the 0
              and - flags both appear, the 0 flag is ignored.  If a
              precision is given with an integer conversion (d, i, o, u,
              x, and X), the 0 flag is ignored.  For other conversions,
              the behavior is undefined.

       -      The converted value is to be left adjusted on the field
              boundary.  (The default is right justification.)  The
              converted value is padded on the right with blanks, rather
              than on the left with blanks or zeros.  A - overrides a 0
              if both are given.

       ' '    (a space) A blank should be left before a positive number
              (or empty string) produced by a signed conversion.

       +      A sign (+ or -) should always be placed before a number
              produced by a signed conversion.  By default, a sign is
              used only for negative numbers.  A + overrides a space if
              both are used.
*/

#include <stdio.h>
#include <unistd.h>
#include "libft.h"

void		ft_printf_tester(char const *str, ...)
// compare my printf code against actual
{
	va_list	arg;
	va_list arg_cpy;
	int		done1;
	int		done2;
	char	ref[46];

	va_start(arg, str);
	va_copy(arg_cpy, arg);
	done1 = vsnprintf(ref, 45, str, arg);
	if (done1 > 45)
		ft_strlcpy(ref + 42, "...", 4);
	printf("\e[30m%-45s (%03d) \e[0m", ref, done1);
	done2 = ft_vfprintf(stdout, str, arg_cpy);
	printf("\t(%03d)\t", done2);
	if (done1 == done2)
		printf("\e[1;32mOk ✓\e[0m\n");
		
	else
		printf("\e[1;31mFailed ✗\e[0m\n");
	va_end(arg_cpy);
	va_end(arg);
}

void	ft_printf_header(char *s)
{
	printf("\n%-104s\n", s);
	for (int x = 0; x < 104; x++)
		printf("-");
	printf("\n");
}

int main(void) {
    int i = 2147483647;
    int neg = -2147483648;
    unsigned int u = 4294967295;
    char c = 'A';
    char *s = "hello";
    void *p = &i;

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("%-52s%-52s\n", "printf", "ftprintf");
	for (int x = 0; x < 104; x++)
		printf("-");
	printf("\n");
	// No Specifiers
	ft_printf_tester("raw: This is the most basic test");

	ft_printf_header("CHARACTERS");
	ft_printf_tester("char:    [%c]", c);
	ft_printf_tester("char left:    [%-5c]", c);
	ft_printf_tester("char right:   [%5c]", c);
	ft_printf_tester("multiple char: [%3c%3c%3c%3c]", 'a' , 'b', 'c', 'd');

	// precision truncates
	ft_printf_header("STRINGS");
    ft_printf_tester("string:       [%s]", s);
    ft_printf_tester("string left:  [%-10s]", s);
	ft_printf_tester("string right:  [%10s]", s);
    ft_printf_tester("string prec:  [%.3s]", s);
    ft_printf_tester("string wide:  [%10.3s]", s);
	ft_printf_tester("string narrow: [%3s]", s);

	// pointer doesnt accept .
    ft_printf_header("POINTERS");
	ft_printf_tester("pointer: [%p]", p);
	ft_printf_tester("pointer wide: [%20p]", &c);
	ft_printf_tester("pointer prec: [%.3p]", &s);

	// precision pads 0 (only adds, doesn't override existing digits)
	// %.0p where p=0 is ""
    ft_printf_header("INT");
    ft_printf_tester("int d,i,u:    [%d, %i, %u]", i, neg, u);
    ft_printf_tester("int plus:     [%+d] [%+i] [%+u]", i, 0, i);
    ft_printf_tester("int space:    [% d] [% i] [% u]", i, neg, neg);
    ft_printf_tester("int 0-pad:    [%013d]", i);
	ft_printf_tester("int neg:      [%+d]", neg);
    ft_printf_tester("int .prec:    [%.5d]", 42);
	ft_printf_tester("int .prec:    [%10.0d]", 42);
	ft_printf_tester("int .prec:    [%+2.5d]", 0);
	ft_printf_tester("int .prec:    [%.0d]", 0);
	ft_printf_tester("int .prec:    [%+2.0d]", 0);
	ft_printf_tester("int .prec:    [% 5.0d]", 0);

	// Redundant combinations (Comment out if -Werror)
    // ft_printf_tester("int - +0:     [%-+05d]", i);
    // ft_printf_tester("int 0 .prec:  [%05.3d]", i);

    ft_printf_header("UINT");
    ft_printf_tester("unsigned:     [%u]", u);
    ft_printf_tester("unsigned 0:   [%010u]", u);
    ft_printf_tester("unsigned .3:  [%.3u]", u);
    ft_printf_tester("unsigned -#10.prec4:   [%-#10.4u]", 42);
	ft_printf_tester("unsigned .prec5:    [%.5u]", u);
	ft_printf_tester("unsigned 10.prec0:    [%10.0u]", u);
	ft_printf_tester("unsigned +2.prec5:    [%+2.5u]", 0);
	ft_printf_tester("unsigned .prec0:    [%.0u]", 0);
	ft_printf_tester("unsigned +2.prec0:    [%+2.0u]", 0);
	ft_printf_tester("unsigned 5.prec0:    [% 5.0u]", 0);

    ft_printf_header("HEX");
    ft_printf_tester("HEX:          [%X]", u); 
    ft_printf_tester("hex:          [%x]", u);
    ft_printf_tester("hex #:        [%#x]", u);
    ft_printf_tester("hex #0:       [%#08x]", u);
    ft_printf_tester("hex -#10.prec4:   [%-#10.4x]", 42);
	ft_printf_tester("hex .prec5:    [%.5x]", u);
	ft_printf_tester("hex 10.prec0:    [%10.0x]", u);
	ft_printf_tester("hex +2.prec5:    [%+2.5x]", 0);
	ft_printf_tester("hex .prec0:    [%.0x]", 0);
	ft_printf_tester("hex +2.prec0:    [%+2.0x]", 0);
	ft_printf_tester("hex 5.prec0:    [% 5.0x]", 0);

    ft_printf_header("LITERALS");
    ft_printf_tester("percent:      [100%%]");
    return 0;
}
