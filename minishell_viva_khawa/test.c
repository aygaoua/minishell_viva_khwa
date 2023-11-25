// #include <stdio.h>

// int main(int ac, char **av, char **envp) {
//     int i;
//     av = NULL;
//     ac = 0;
//     for (i = 0; envp[i] != NULL; i++) {
//         printf("%s\n", envp[i]);
//     }
//     return 0;
// }

#include <unistd.h>
#include <stdio.h>

int main() {
    // Write C code here
    //\r\n\v \f
    write(1, "\t", 1);
    // write(1, "\n", 1);
    write(1, "\r", 1);
    write(1, "\n", 1);
    write(1, "\v", 1);
    return 0;
}