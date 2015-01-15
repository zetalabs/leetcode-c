/*
 * There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

int min(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}

int find_kth(int A[], int m, int B[], int n, int k)
{
	int ia, ib;

	/* iteration finished */
	if (m > n) return find_kth(B, n, A, m, k);
	if (m == 0) return B[k - 1];
	if (k == 1) return min (A[0], B[0]);

	ia = min (k/2, m);
	ib = k - ia;
	if (A[ia - 1] < B[ib - 1])
		return find_kth(A+ia, m-ia, B, n, k-ia);
	else if (A[ia - 1] > B[ib - 1])
		return find_kth(A, m, B+ib, n-ib, k-ib);
	else
		return A[ia - 1];

}

/*
 * input
 *   A : sorted array
 *   m : number of the elements in array A
 *   B : sorted array
 *   n : number of the elements in array B
 * return
 *   on success if target is in A, return true;
 *   otherwise return false
 * time complexity: O(n)
 * space complexity: O(1)
 */
double findMedianSortedArrays(int A[], int m, int B[], int n) {
	int total = m + n;
	if (total & 0x1)
		return find_kth(A, m, B, n, total / 2 + 1);
	else
		return (find_kth(A, m, B, n, total / 2)
			+ find_kth(A, m, B, n, total / 2 + 1)) / 2.0;
}

#if 1
#define DBG(fmt, args...) do { printf(fmt, ##args); } while(0)
#else
#define DBG(fmt, args...)
#endif

/*
 * input
 *   fp : file pointer pointing to read file
 *   a : sorted array
 *   n : array length
 * return
 *   on success return number of elements in array a;
 *   otherwise return -1;
 */
int read_array(FILE *fp, int a[], int b[], int n, int *target, int *target2)
{
	char buf[2048];
	char *p, *start;
	int i, num, count, positive;

	if (fgets(buf, sizeof(buf), fp) == NULL) {
		DBG("%s(%d)\n", __func__, __LINE__);
		return -1;
	}

	p = buf;

	while((*p != '[') && (*p != '\0'))
		p++;

	if (*p == '\0') {
		DBG("%s(%d)\n", __func__, __LINE__);
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
			DBG("%s(%d)\n", __func__, __LINE__);
			return -1;
		}

		while (start != p) {
			i = (*start - '0');

			if ((i < 0) || (i > 9)) {
				DBG("%s(%d)\n", __func__, __LINE__);
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
			DBG("%s(%d)\n", __func__, __LINE__);
			return -1;
		}

		a[count] = num;
		count++;

		if (*p == ']')
			break;

		p++;
	}

	if (*p == '\0') {
		DBG("%s(%d)\n", __func__, __LINE__);
		return -1;
	}

	/* get target */
	p++;
	if (*p != ',') {
		DBG("%s(%d)\n", __func__, __LINE__);
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
		DBG("%s(%d)\n", __func__, __LINE__);
		return -1;
	}

	start = p;
	num = 0;

	while ((*start != ' ') && (*start != ',')) {
		i = (*start - '0');

		if ((i < 0) || (i > 9)) {
			DBG("%s(%d)\n", __func__, __LINE__);
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
	DBG("%s(%d) target=[%d]\n", __func__, __LINE__, *target);
	DBG("%s(%d) p=[%p]\n", __func__, __LINE__, p);

	while((*p != '[') && (*p != '\0'))
		p++;

	DBG("%s(%d) p=[%p]\n", __func__, __LINE__, p);
	if (*p == '\0') {
		DBG("%s(%d)\n", __func__, __LINE__);
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
			DBG("%s(%d)\n", __func__, __LINE__);
			return -1;
		}

		while (start != p) {
			i = (*start - '0');

			if ((i < 0) || (i > 9)) {
				DBG("%s(%d)\n", __func__, __LINE__);
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
			DBG("%s(%d)\n", __func__, __LINE__);
			return -1;
		}

		b[count] = num;
		count++;

		if (*p == ']')
			break;

		p++;
	}

	if (*p == '\0') {
		DBG("%s(%d)\n", __func__, __LINE__);
		return -1;
	}

	/* get target */
	p++;
	if (*p != ',') {
		DBG("%s(%d)\n", __func__, __LINE__);
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
		DBG("%s(%d)\n", __func__, __LINE__);
		return -1;
	}

	start = p;
	num = 0;

	while ((*start != '\0') && (*start != '\n') && (*start != ' ')) {
		i = (*start - '0');

		if ((i < 0) || (i > 9)) {
			DBG("%s(%d)\n", __func__, __LINE__);
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

	*target2 = num;

	return num;
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
	int b[1024];
	int n, target, target2;
	double b_result;

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

	n = read_array(fp_in, a, b, sizeof(a), &target, &target2);
	DBG("%s(%d)\n", __func__, __LINE__);
	while (n >= 0) {
		write_array(fp_out, a, target);
		fprintf(fp_out, ", %d,", target);
		write_array(fp_out, b, target2);
		fprintf(fp_out, ", %d", target2);
		fprintf(fp_out, " -> ");

		b_result = findMedianSortedArrays(a, target, b, target2);
		fprintf(fp_out, "%f", b_result);
		fprintf(fp_out, "\n");

		n = read_array(fp_in, a, b, sizeof(a), &target, &target2);
	}

func_out:
	if (fp_in != NULL)
		fclose(fp_in);

	if (fp_out != NULL)
		fclose(fp_out);

	return ret;
}
