#include <stdio.h>
#define size 10

void merge(int a[], int low, int mid, int high) {
    int i, j, k, s1, s2;
    s1 = mid - low + 1;
    s2 = high - mid;
    int left[s1], right[s2];

    for (i = 0; i < s1; i++)
        left[i] = a[low + i];
    for (j = 0; j < s2; j++)
        right[j] = a[mid + 1 + j];

    i = 0;
    j = 0;
    k = low;

    while (i < s1 && j < s2) {
        if (left[i] <= right[j]) {
            a[k] = left[i];
            i++;
        } else {
            a[k] = right[j];
            j++;
        }
        k++;
    }

    while (j < s2) {
        a[k] = right[j];
        j++;
        k++;
    }

    while (i < s1) {
        a[k] = left[i];
        i++;
        k++;
    }
}

void mergesort(int a[], int l, int r) {
    int m;
    if (l < r) {
        m = (l + r) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int main() {
    int a[30], n, i;
    printf("\nNo. of Elements: ");
    scanf("%d", &n);
    printf("Enter Array Elements: \n");
    i = 0;
    do {
        scanf("%d", &a[i]);
        i++;
    } while (getchar() != '\n' && i < n);

    mergesort(a, 0, n - 1);

    printf("\nSorted Array : ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}
