// signal2.c
// Prints "Hello World!" from the SIGALRM handler every 5 seconds,
// followed by "Turing was right!" from main(), indefinitely.
//
// Build:  gcc -Wall -Wextra -std=c11 -o signal2 signal2.c
//
// Usage:  ./signal2   (press Ctrl-C to terminate)
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdatomic.h>

static volatile sig_atomic_t fired = 0;

void handle_alarm(int sig) {
    (void)sig;
    const char msg[] = "Hello World!\n";
    ssize_t _ = write(STDOUT_FILENO, msg, sizeof msg - 1);
    (void)_;
    fired = 1;
    alarm(5); // schedule the next alarm
}

int main(void) {
    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    alarm(5); // first alarm in 5 seconds

    for (;;) {
        while (!fired) {
            pause(); // sleep until SIGALRM fires
        }
        fired = 0;
        printf("Turing was right!\n");
        fflush(stdout);
    }
}
