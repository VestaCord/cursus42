## printf fun facts
The actual printf is [turing complete](https://github.com/carlini/printf-tac-toe)

***

## Requirements

• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.

BONUS
Manage any combination of the following flags: ’-0.’ and the field minimum width
under all conversions.

Manage all the following flags: ’# +’ (Yes, one of them is a space)

## glibc printf implementation
In glibc,
[printf][1] calls [vfprintf][2], which is
[a variant that accepts a single va_list argument rather than a variable list of arguments][3].
The only rare language feature here is the use of varargs to get at arguments in a variable length argument list.

	28 int
	29 __printf (const char *format, ...)
	30 {
	31   va_list arg;
	32   int done;
	33 
	34   va_start (arg, format);
	35   done = vfprintf (stdout, format, arg);
	36   va_end (arg);
	37 
	38   return done;
	39 }
	40 

### vprintf implementation

	# declaration
	int	vfprintf (FILE *s, const char *format, va_list ap)

What is `char`? It is decided at compile time to be `wchar` if wide characters are needed (see `wprintf`), else it is `char`.

	#ifndef COMPILE_WPRINTF
	 #define char char
	#else
	 #define char wchar
	#endif

The implementation of `FILE` is from the [libio.h][4] implementation originally found in GNU libg++.
If moulinette prevents using the stdout macro, I will just use the fileno member instead.

	struct _IO_FILE {
		...
		int _fileno;
		...
	};

### jump table

glibc uses the below jump table to map the letter specifiers to different format classes.
Ecole42 doesn't allow switch cases or goto (gcc specific), so I will use a function ptr array called `g_dispatch_table`.

	static const uint8_t	jump_table[] =
	{
			/*' '*/	1,					0,					0,	/*'#'*/		4,
							0,	/*'%'*/	14,					0,	/*'\''*/	6,
							0,					0,	/*'*'*/	7,	/*'+'*/		2,
							0,	/*'-'*/	3,	/*'.'*/	9,						0,
			/*'0'*/	5,	/*'1'*/	8,	/*'2'*/	8,	/*'3'*/		8,
			/*'4'*/	8,	/*'5'*/	8,	/*'6'*/	8,	/*'7'*/		8,
			/*'8'*/	8,	/*'9'*/	8,					0,						0,
							0,					0,					0,						0,
							0,	/*'A'*/	26,					0,	/*'C'*/		25,
							0,	/*'E'*/	19, /*F*/	  19,	/*'G'*/		19,
							0,	/*'I'*/	29,					0,						0,
			/*'L'*/	12,					0,					0,						0,
							0,					0,					0,	/*'S'*/		21,
							0,					0,					0,						0,
			/*'X'*/	18,					0, 	/*'Z'*/	13,						0,
							0,					0,					0,						0,
							0,	/*'a'*/	26,					0,	/*'c'*/		20,
			/*'d'*/	15, /*'e'*/	19, /*'f'*/	19,	/*'g'*/		19,
			/*'h'*/	10, /*'i'*/	15, /*'j'*/	28,						0,
			/*'l'*/	11, /*'m'*/	24, /*'n'*/	23,	/*'o'*/		17,
			/*'p'*/	22, /*'q'*/	12,					0,	/*'s'*/		21,
			/*'t'*/	27, /*'u'*/	16,					0,						0,
			/*'x'*/	18,					0,	/*'z'*/	13
	};

### Handling arguements

In order for vfprintf to handle positional arguement specifiers, it needs to save
the va list into an array

args_type[cnt] tells us what type the cnt-th argument is (e.g., PA_INT, PA_DOUBLE, PA_STRING, etc.)

args_value[cnt] is a union holding the actual value for that argument.

We're using va_arg(ap_save, TYPE) to extract the value from the saved va_list (ap_save), and we store it into args_value[cnt].

Example:

	args_value[cnt].mem = va_arg (ap_save, type);   
	args_value[cnt].pa_double = va_arg (ap_save, double);
	args_value[cnt].pa_long_double = va_arg (ap_save, long double);
	args_value[cnt].pa_pointer = va_arg (ap_save, void *);

### Core logic
Initial scan with __find_specmb() to locate first %.

For each %, enter fast loop:

    Use jump tables to process flags/modifiers.

    Maintain state in local variables (like space, left, base, spec).

Call process_arg() to:

    Fetch next argument from va_list ap_save.

    Convert it to string form.

    Apply formatting.

Write the result to output.

Repeat with f = __find_specmb(...) to find next %.

<!-- REFERENCES -->
[1]: https://sourceware.org/git/?p=glibc.git;a=blob;f=stdio-common/printf.c;h=4c8f3a2a0c38ab27a2eed4d2ff3b804980aa8f9f;hb=3321010338384ecdc6633a8b032bb0ed6aa9b19a

[2]: https://sourceware.org/git/?p=glibc.git;a=blob;f=stdio-common/vfprintf.c;h=fc370e8cbc4e9652a2ed377b1c6f2324f15b1bf9;hb=3321010338384ecdc6633a8b032bb0ed6aa9b19a

[3]: https://en.wikipedia.org/wiki/Printf#Family

[4]: https://stackoverflow.com/questions/16424349/where-to-find-struct-io-file