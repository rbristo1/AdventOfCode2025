#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>
uint64_t total = 0;
void sighandler(int sig) {
    if (SIGINT == sig) {
        printf("total: %d\n", total);
        exit(0);
    }
}
//part1
/*
int main() {
    signal(SIGINT, sighandler);
    int pos = 50;
    int dir = 0;
    int move = 0;
    char buf[256] = {0};
    while(scanf("%s", buf) == 1) {
        dir = 0;
        if (buf[0] == 'L') {
            dir = -1;
            sscanf(&buf[1], "%d", &move);

        }
        else {
            dir = 1;
            sscanf(&buf[1], "%d", &move);
        }
        pos += move*dir;
        if (pos%100 == 0) {
            total++;
        }

    }
}*/

//part 2
int main() {
    signal(SIGINT, sighandler);
    int pos = 50;
    int dir = 0;
    int move = 0;
    int old = 0;
    char buf[256] = {0};
    while(scanf("%s", buf) == 1) {
        old = pos;
        dir = 0;
        if (buf[0] == 'L') {
            dir = -1;
            sscanf(&buf[1], "%d", &move);

        }
        else {
            dir = 1;
            sscanf(&buf[1], "%d", &move);
        }
        pos += (move*dir)%100;
        if (pos < 0) {
            pos += 100;

        }
        if (pos > 0) {
            pos %= 100;
        }

        if (old + ((move*dir)%100) >= 100 && old != 0) {
            total++;
        }
        if (old + ((move*dir)%100) <= 0 && old != 0) {
            total++;
        }
        total += abs(move/100);
        

    }
}