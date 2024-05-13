#include <stdio.h>

int combination(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
    return combination(n - 1, k - 1) + combination(n - 1, k);
}

void PascalTriangleIterative(int n) {
    if (n <= 0) {
        printf("1\n");
        return;
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", combination(i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void PascalTriangleRecursive(int n, int arr[]) {
    if (n == 0) {
        arr[0] = 1;
        printf("%d\n", arr[0]);
        return;
    }

    PascalTriangleRecursive(n - 1, arr);

    for (int i = n; i >= 0; i--) {
        arr[i] = combination(n, i);
    }

    for (int i = 0; i <= n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Pascal Triangle\n");

    printf("Enter n: ");
    scanf("%d", &n);

    PascalTriangleIterative(n);

    int arr[n + 1];
    for (int i = 0; i <= n; i++) {
        arr[i] = 0;
    }

    PascalTriangleRecursive(n, arr);

    return 0;
}