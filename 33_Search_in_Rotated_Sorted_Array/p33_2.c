/*
 * Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 * You are given a target value to search. If found in the array return its index, otherwise return -1.
 * You may assume no duplicate exists in the array.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

/*
 * input
 *   A : sorted array
 *   n : number of the elements in array a
 * return
 *   on success if target is in A, return the index, otherwise return -1;
 *   or return -2 for some errors;
 * time complexity: O(log(n))
 * space complexity: O(1)
 */
int search(int A[], int n, int target)
{
	int first, last, mid;

	if (A == NULL)
		return -2;

	if (n < 0)
		return -2;

	if (n == 0)
		return -1;

	first = 0;
	last = n;
	while (first != last) {
		mid = first + (last - first) / 2;
		if (A[mid] == target)
			return mid;
		if (A[first] <= A[mid]) {
			if (A[first] <= target && target < A[mid])
				last = mid;
			else
				first = mid + 1;
		} else {
			if (A[mid] < target && target <= A[last-1])
				first = mid + 1;
			else
				last = mid;
		}
	}

	return -1;
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
int read_array(FILE *fp, int a[], int n, int *target)
{
	char buf[2048];
	char *p, *start;
	int i, num, count, positive;

	if (fgets(buf, sizeof(buf), fp) == NULL) {
		return -1;
	}

	p = buf;

	while((*p != '[') && (*p != '\0'))
		p++;

	if (*p == '\0') {
		return -1;
	}

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

		if (*p == '\0') {
			return -1;
		}

		while (start != p) {
			i = (*start - '0');

			if ((i < 0) || (i > 9)) {
				return -1;
			}

			if (positive) {
				num = (num * 10) + i;
			}
			else {
				num = (num * 10) - i;
			}
			start++;
		}

		if (count >= n) {
			return -1;
		}

		a[count] = num;
		count++;

		if (*p == ']')
			break;

		p++;
	}

	if (*p == '\0') {
		return -1;
	}

	/* get target */
	p++;
	if (*p != ',') {
		return -1;
	}
	p++;
	while (*p == ' ')
		p++;

	/* check negative/positive sign */
	positive = 1;
	if (*p == '+') {
		p++;
	}
	else if (*p == '-') {
		p++;
		positive = 0;
	}

	if (!isdigit(*p)) {
		return -1;
	}

	start = p;
	num = 0;

	while ((*start != '\0') && (*start != '\n')) {
		i = (*start - '0');

		if ((i < 0) || (i > 9)) {
			return -1;
		}

		if (positive) {
			num = (num * 10) + i;
		}
		else {
			num = (num * 10) - i;
		}
		start++;
	}

	*target = num;

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
	int n, target;

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

	n = read_array(fp_in, a, sizeof(a), &target);
	while (n >= 0) {
		write_array(fp_out, a, n);
		fprintf(fp_out, ", %d", target);
		fprintf(fp_out, " -> ");

		n = search(a, n, target);
		if (n >= -1) {
			fprintf(fp_out, "index=%d", n);
		}
		else {
			fprintf(fp_out, "???");
		}
		fprintf(fp_out, "\n");

		n = read_array(fp_in, a, sizeof(a), &target);
	}

func_out:
	if (fp_in != NULL)
		fclose(fp_in);

	if (fp_out != NULL)
		fclose(fp_out);

	return ret;
}
