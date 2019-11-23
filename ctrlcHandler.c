#include <signal.h>

int keep_running = 1;

void handler(int signal) {
    keep_running = 0;
}

void activate_ctrlc_handler(){
    signal(SIGINT, handler);
}

void deactivate_ctrlc_handler(){
    signal(SIGINT, SIG_DFL);
}

int is_running(){
    return keep_running;
}