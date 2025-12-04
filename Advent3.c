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
        printf("total: %lu\n", total);
        exit(0);
    }
}

//part1
/*int main() {
    signal(SIGINT, sighandler);
    char buf[256];

    while(scanf("%s", buf) == 1) {
        int max = 0;
        int maxPos = 0;
        int max2 = 0;
        int max2Pos = 0;
        for (int i = 0; i < strlen(buf)-1; i++) {
            if ((int)buf[i]-48 > max) {
                max = (int)buf[i]-48;
                maxPos = i;
                if (max == 9) {
                    break;
                }
            }
        }
        for (int i = maxPos+1; i < strlen(buf); i++) {
            if ((int)buf[i]-48 > max2) {
                max2 = (int)buf[i]-48;
                max2Pos = i;
                if (max2 == 9) {
                    break;
                }
            }
        }
        total += max*10+max2;
    }
}*/

int main() {
    signal(SIGINT, sighandler);
    char buf[256];

    while(scanf("%s", buf) == 1) {
        int maxPos = -1;
        int max2Pos = 0;
        uint64_t max[12] = {0};
        for (int i = 0; i < 12; i++) {
            for (int j = maxPos+1; j < strlen(buf)-(11-i); j++) {
                if ((int)buf[j]-48 > max[i]) {
                    max[i] = (uint64_t)buf[j]-48;
                    max2Pos = j;
                    if (max[i] == 9) {
                        break;
                    }
                }
            }
            maxPos = max2Pos;
        }
        uint64_t temp = 0;
        for (int i = 0; i < 12; i++) {
            total += max[i]*(pow(10, 11-i));
            temp += max[i]*(pow(10, 11-i));
        }
        
    }
}