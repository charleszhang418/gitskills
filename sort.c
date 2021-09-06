#include <stdio.h>

int bubble_sort(int a[], int len) {
    int i, j, temp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main() {
    int a[] = {4, 2, 6, 7, 3, 10, 15};
    int len = (int) sizeof(a) / sizeof(*a);
    bubble_sort(a, len);
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}