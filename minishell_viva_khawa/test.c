#include <stdio.h>

int main(int ac, char **av, char **envp) {
    int i;
    av = NULL;
    ac = 0;
    for (i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}