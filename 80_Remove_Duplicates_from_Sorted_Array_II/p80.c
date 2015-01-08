#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * input
 *   a : sorted array
 *   n : number of the elements in array a
 *   d : maximum duplicated times in array
 * return
 *   on success return merged number of elements in array a
 *   otherwise return -1;
 */
int remove_duplicates2(int a[], int n, int d)
{
	int i, j;
	int existed;

	if (a == NULL)
		return -1;

	if (n < 0)
		return -1;

	if (d < 1)
		return -1;

	if ((n == 0) || (n == 1))
		return n;

	i = 0;
	existed = 1;

	for (j = 1; j < n; j++) {
		if (a[i] != a[j]) {
			i++;
			a[i] = a[j];
			existed = 1;
		}
		else if (existed < d) {
			i++;
			a[i] = a[j];
			existed++;
		}
	}

	return i+1;
}

/*
 * input
 *   fp : file pointer pointing to read file
 *   a : sorted array
 *   n : array length
 * return
 *   on success return number of elements in array a;
 *   otherwise return -1;
 */
int read_array(FILE *fp, int a[], int n)
{
	char buf[2048];
	char *p, *start;
	int i, num, count, positive;

	if (fgets(buf, sizeof(buf), fp) == NULL)
		return -1;

	p = buf;
	while((*p != '[') && (*p != '\0'))
		p++;

	if (*p == '\0')
		return -1;

	p++;
	count = 0;

	while ((*p != ']') && (*p != '\0'))
	{
		/* check negative/positive sign */
		positive = 1;
		if (*p == '+') {
			p++;
		}
		else if (*p == '-') {
			p++;
			positive = 0;
		}

		start = p;
		num = 0;
		while ((*p != ']') && (*p != '\0') && (*p != ','))
			p++;

		if (*p == '\0')
			return -1;

		while (start != p) {
			i = (*start - '0');

			if ((i < 0) || (i > 9))
				return -1;

			if (positive) {
				num = (num * 10) + i;
			}
			else {
				num = (num * 10) - i;
			}
			start++;
		}

		if (count >= n)
			return -1;

		a[count] = num;
		count++;

		if (*p == ']')
			break;

		p++;
	}

	if (*p == '\0')
		return -1;

	return count;
}

/*
 * input
 *   fp : file pointer pointing to read file
 *   a : sorted array
 *   n : array length
 * return
 *   on success return 0;
 *   otherwise return -1;
 */
int write_array(FILE *fp, int a[], int n)
{
	int i;
	fprintf(fp, "[");
	for (i = 0; i < n; i++) {
		if (i == (n-1))
			fprintf(fp, "%d", a[i]);
		else
			fprintf(fp, "%d,", a[i]);
	}
	fprintf(fp, "]");
	return 0;
}

#define TEST_CASES_FILE  	"test_cases.txt"
#define TEST_RESULTS_FILE	"results.txt"

int main(int argc, char **argv)
{
	FILE *fp_in, *fp_out;
	int ret = -1;
	int a[1024];
	int n;

	fp_in = fopen(TEST_CASES_FILE, "r");
	fp_out = fopen(TEST_RESULTS_FILE, "w");

	if (fp_in == NULL) {
		printf("Can't open %s!\n", TEST_CASES_FILE);
		goto func_out;
	}

	if (fp_out == NULL) {
		printf("Can't open %s!\n", TEST_RESULTS_FILE);
		goto func_out;
	}

	n = read_array(fp_in, a, sizeof(a));
	while (n >= 0) {
		write_array(fp_out, a, n);
		fprintf(fp_out, "->");

		n = remove_duplicates2(a, n, 2);
		if (n >= 0) {
			write_array(fp_out, a, n);
			fprintf(fp_out, " n=%d", n);
		}
		else {
			fprintf(fp_out, "???");
		}
		fprintf(fp_out, "\n");

		n = read_array(fp_in, a, sizeof(a));
	}

func_out:
	if (fp_in != NULL)
		fclose(fp_in);

	if (fp_out != NULL)
		fclose(fp_out);

	return ret;
}
