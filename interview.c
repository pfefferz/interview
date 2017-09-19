/** Directions
 *
 *  1. Implement strcpy, ARRAY_SIZE and atoi.
 *  2. Implement test cases that prove that each function works.
 *  3. Compile and run the code.
 *
 *  General comments on the solution
 *
 *  Being able to quickly and precisely implement each of these
 *  functions demonstrates that you understand:
 *      1. What a string is
 *      2. What a fundamental quality of a type is: its size in bytes
 *      3. How to implement a basic algorithm
 *
 *  The test also calls for you to test each function. Since its not
 *  asked for, the test cases can cover basic functionality.
 *
 *  Although not explicitly stated, the test also request that you
 *  implement the functions in an existing unit test rig. To do this
 *  you would have to review the file and quickly understand how to
 *  fit your implementation in.
 *
 *  The test also looks at the style of your code. Does it adhere to 80
 *  chars? Is the code easy to read? Have you removed all of the
 *  whitespace at the end of each line? Does it pass checkpatch? Do
 *  you know how to run checkpatch?
 *
 *  wget https://raw.githubusercontent.com/torvalds/linux/master/scripts/checkpatch.pl
 *  chmod +x checkpatch.pl
 *  checkpatch.pl --no-tree -f ../interview/interview.c
 *
 *  Note: This file has 4 checkpatch warnings and 1 checkpatch error
 *
 *  Finally, coderpad.io lets me follow along as you code. With this I
 *  can get a sense of your level of code craftsmanship. Can you use
 *  vim effectively? Can you get around code effectively. Writing code
 *  effectively using vim is an extremely important skills to master
 *  to efficiently and correctly write low level code.
 */

#include <stdio.h>

/** Copy a string
 *
 *  Return dst
 *
 *  Why do I consider this implementation correct?
 *
 *  In K&R C, a book on the original dialect of the C programming
 *  language, by Kernighan and Ritchie, they list the implementation
 *  given here.
 *
 *  Why do I use this question?
 *
 *  When someone lists the correct implementation and is able to
 *  explain it, they demonstrate that they understand what a string
 *  is: a sequence of non '\0' bytes terminated by a '\0'. Strings are
 *  fundamental to C, so understanding what a string is and is not, is
 *  crucial to working with the language.
 *
 *  This is important because so much of what we do is built in C.  By
 *  listing this implementation, the user demonstrates that they also
 *  understand how to copy data and how to copy the right amount of
 *  data.  Again, in C, users copy a great deal of data. Because of
 *  this, knowing how to copy the right amount of data is important so
 *  that programs are correct and do not contain errors, like
 *  off-by-one errors.
 */
char *strcpy(char *dst, char *src)
{

	char *ret = dst;

	while (*dst++ = *src++);

	return ret;
}

/** Return the number of elements in an array of any type
 *
 *  Why do I consider this implementation correct?
 *
 *  When 'a' is an array, sizeof(a) will return the number of bytes
 *  needed to store the array. sizeof(*a) returns the number of bytes
 *  needed to store the type of array. I prefer *a to a[0] for
 *  stylistic reasons, i.e. if you have a zero length array and list
 *  a[0], it seems to suggest that the implementation won't work,
 *  although it does work.
 *
 *  Why do I use this question?
 *
 *  Knowing one of the fundamental properties of a type, i.e. that the
 *  type has a size in bytes is important to keep in mind in low level
 *  programming because we tend to need to do things like malloc
 *  memory to hold types of data or we need to treat a type at a more
 *  fundamental level, e.g. as a stream of bytes.
 */
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*a))

/** Return the integer represented by the string
 *
 *  Why do I consider this implementation correct?
 *
 *  This implementation handles str's pointing to '\0' and it handles
 *  positive and negative values. It also handles these conditions
 *  without extra steps in a straight forward fashion, e.g. its very
 *  easy to read and understand.
 *
 *  Why do I use this question?
 *
 *  Its a way to assess how someone approaches an algorithm.
 */
int atoi(char *str)
{
	int val = 0;
	int neg = 1;

	if (!str)
		return val;

	if (*str == '-') {
		neg = -1;
		str++;
	}

	while (*str) {
		switch (*str) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			val *= 10;
			val += *str - '0';
		break;
		}
		str++;
	}

	return neg*val;
}

/** Test strcpy
 *
 *  Return 1 on success and 0 on failure
 *
 *  Why do I consider this implementation correct?
 *
 *  It tests copying empty strings, non-empty stings and tests copying
 *  to 0 and non-zero'd memory.
 *
 *
 *  The C standard [1] doesn't say what happens when you pass an
 *  invalid pointer to strcpy so I don't test for it.
 *
 *  Reference
 *
 *  [1] C Standard (C11)
 *  http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1570.pdf
 */
static const char test_strcpy_desc[] = "Test strcpy";
int test_strcpy(void)
{
	struct test {
		char test_str_in[16];
		char test_str_out[16];
	} tests[] = {
		{
			"",		/* Case 1: an empty str */
			"xxxxxxx"       /* Copy to non-zeroed memory*/
		},
		{
			"123",		/* Case 2: a non empty str */
			"xxxxxxx"       /* Copy to non-zeroed memory */
		},
		{
			"",		/* Case 1: an empty str */
			""              /* Copy to zeroed memory */
		},
		{
			"123",		/* Case 2: a non empty str */
			""              /* Copy to zeroed memory */
		},
	};

	int i;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		char *str;

		str = strcpy(tests[i].test_str_out, tests[i].test_str_in);
		if (str != tests[i].test_str_out)
			return 0;

		int j = 0;

		while (tests[i].test_str_in[j] != '\0' &&
		tests[i].test_str_out[j] == tests[i].test_str_in[j])
			j++;

		if (tests[i].test_str_out[j] != '\0')
			return 0;
	}

	return 1;
}


/** Test ARRAY_SIZE()
 *
 *  Return 1 on success and 0 on failure
 *
 *  Why do I consider this implementation correct?
 *
 *  I test 0 and more than 0, two typical inputs.
 */
static const char test_array_size_desc[] = "Test ARRAY_SIZE";
int test_array_size(void)
{
	int a[] = {};
	int b[] = {0, 1, 2};

	if (ARRAY_SIZE(a) != 0)
		return 0;

	if (ARRAY_SIZE(b) != 3)
		return 0;

	return 1;
}

/** Test atoi
 *
 *  Return 1 on success and 0 on failure
 *
 *  Why do I consider this implementation correct?
 *
 *  I test 0, positive and negative values.
 *
 *  I don't test invalid input since the implementation doesn't
 *  require handling bad numbers. In general, I would handle input
 *  validation using a separate function.
 */
static const char test_atoi_desc[] = "Test atoi";
int test_atoi(void)
{
	struct test {
		char num_str[16];
		int num;
	} tests[] = {
		{
			"",
			0
		},
		{
			"3",
			3
		},
		{
			"-30",
			-30
		}
	};

	if (atoi(0) != 0)
		return 0;

	int i;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		if (atoi(tests[i].num_str) != tests[i].num)
			return 0;
	}

	return 1;
}

struct test {
	int (*test_func)(void);
	const char *test_desc;
} tests[] = {
	{test_strcpy, test_strcpy_desc},
	{test_array_size, test_array_size_desc},
	{test_atoi, test_atoi_desc},
};

int main(int argc, char *argv[])
{
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		ret = tests[i].test_func();
		switch (ret) {
		case 0:
			printf("%s: ", "FAILED");
			break;
		case 1:
			printf("%s: ", "PASSED");
			break;
		default:
			printf("%s: ", "UNEXPE");
			break;
		}
		printf("%s", tests[i].test_desc);
		printf("\n");
	}

	return 0;
}
