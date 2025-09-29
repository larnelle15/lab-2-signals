# Signals Lab (C / POSIX)

This repo contains three small programs demonstrating Unix signal handling with `signal()` and `alarm()`.

## Files
- `signal1.c` — Waits 5 seconds, prints **Hello World!** (from handler), then **Turing was right!** (from `main`) and exits.
- `signal2.c` — Every 5 seconds indefinitely prints **Hello World!** (from handler) then **Turing was right!** (from `main`).
- `timer.c` — Emits a SIGALRM once per second and counts ticks. On **Ctrl‑C** (SIGINT), prints total ticks and total wall time, then exits.
- `Makefile` — `make`, `make signals`, or `make all` builds all three. `make clean` removes binaries.

## Build
```bash
make
# or
make signals
```

## Run
```bash
./signal1   # wait ~5s
./signal2   # press Ctrl-C to stop
./timer     # prints a dot every second; press Ctrl-C for summary
```

### Notes
- The signal handlers use `write(2)` (async‑signal‑safe). Avoid `printf` inside handlers.
- `signal2.c` and `timer.c` re‑arm `alarm()` from inside the handler.
- Tested with `gcc -std=c11` on macOS/Linux.
```

