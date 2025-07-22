#include <stdio.h>

int main() {
    printf("Welcome to MyDB (SQLite-inspired)\n");
    printf("mydb > ");

    char input[1024];
    while (fgets(input, sizeof(input), stdin)) {
        printf("Received: %s", input);
        printf("mydb > ");
    }

    return 0;
}
