#include <stdio.h>

int my_power(int x, int n) {
    int answer = 1;
    for(int i = 0; i < n; i++) {
        answer = answer * x;
    }
    return answer;
}

int my_power_rec(int x, int n) {
    if (n == 0) {
        return 1;
    } else {
        return x * my_power_rec(x, n - 1);
    }
}

int main()
{
    printf("%d\n", my_power(2, 4));
    printf("%d\n", my_power_rec(2, 4));
    return 0;
}