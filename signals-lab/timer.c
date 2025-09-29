// timer.c
// Emits a SIGALRM every second and counts how many have fired.
// On Ctrl-C (SIGINT), prints the total execution time in seconds and exits.
//
// Build:  gcc -Wall -Wextra -std=c11 -o timer timer.c
//
// Usage:  ./timer   (press Ctrl-C to exit)
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdatomic.h>

static volatile sig_atomic_t tick_count = 0;
static volatile sig_atomic_t should_quit = 0;
static time_t start_time;

void handle_alarm(int sig) {
    (void)sig;
    ++tick_count;
    const char dot[] = ".";
    // Provide a heartbeat without newline each second (optional)
    ssize_t _ = write(STDOUT_FILENO, dot, sizeof dot - 1);
    (void)_;
    alarm(1); // re-arm for the next second
}

void handle_int(int sig) {
    (void)sig;
    const char msg[] = "\nSIGINT received, preparing to exit...\n";
    ssize_t _ = write(STDOUT_FILENO, msg, sizeof msg - 1);
    (void)_;
    should_quit = 1;
}

int main(void) {
    start_time = time(NULL);

    if (signal(SIGALRM, handle_alarm) == SIG_ERR) {
        perror("signal SIGALRM");
        return 1;
    }
    if (signal(SIGINT, handle_int) == SIG_ERR) {
        perror("signal SIGINT");
        return 1;
    }

    alarm(1); // first tick in 1s
    while (!should_quit) {
        pause(); // wait for signals
    }

    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);
    printf("Total SIGALRM ticks observed: %d\n", (int)tick_count);
    printf("Total execution time (seconds): %.0f\n", elapsed);
    return 0;
}
