// signal1.c
// Registers a SIGALRM handler; after the handler runs, main prints
// "Turing was right!" before exiting.
//
// Build:  gcc -Wall -Wextra -std=c11 -o signal1 signal1.c
//
// Usage:  ./signal1   (wait ~5 seconds)
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
    // write() is async-signal-safe; avoid printf in signal handlers.
    ssize_t _ = write(STDOUT_FILENO, msg, sizeof msg - 1);
    (void)_; // suppress unused warning
    fired = 1;
}

int main(void) {
    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("signal");
        return 1;
    }
    alarm(5); // deliver SIGALRM in 5 seconds

    // Busy wait more politely by pausing until a signal arrives
    while (!fired) {
        pause();
    }

    printf("Turing was right!\n");
    return 0;
}
