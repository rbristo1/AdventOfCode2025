#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>
char **map;
uint64_t total = 0;
int mapSize = 0;
int mapLen = 0;
void solveMap() {
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapLen; j++) {
            int adj = 0;
            if (map[i][j] == '@') {
                if (i != mapLen-1 && (map[i+1][j] == '@' || map[i+1][j] == 'x')) {
                    adj++;
                }
                if (i != 0 && (map[i-1][j] == '@' || map[i-1][j] == 'x')) {
                    adj++;
                }
                if (j != mapSize-1 && (map[i][j+1] == '@' || map[i][j+1] == 'x')) {
                    adj++;
                }
                if (j != 0 && (map[i][j-1] == '@' || map[i][j-1] == 'x')) {
                    adj++;
                }
                if (j != mapSize-1 && i != mapLen-1 && (map[i+1][j+1] == '@' || map[i+1][j+1] == 'x')) {
                    adj++;
                }
                if (j != mapSize-1 && i != 0 && (map[i-1][j+1] == '@' || map[i-1][j+1] == 'x')) {
                    adj++;
                }
                if (j != 0 && i != mapLen-1 && (map[i+1][j-1] == '@' || map[i+1][j-1] == 'x')) {
                    adj++;
                }
                if (j != 0 && i != 0 && (map[i-1][j-1] == '@' || map[i-1][j-1] == 'x')) {
                    adj++;
                }
                if (adj < 4) {
                    total++;
                    map[i][j] = 'x';
                }
            }
            else {
                continue;
            }
        }
    }
}
//part 1
/*void sighandler(int sig) {
    if (SIGINT == sig) {
        solveMap();
        for (int i = 0; i < mapSize; i++) {
            free(map[i]);
        }
        free(map);
        printf("%lu\n", total);

        exit(0);
    }
}*/

//part 2
void sighandler(int sig) {
    if (SIGINT == sig) {
        int old = 0;
        while (true) {
            old = total;
            solveMap();
            if (total == old) {
                break;
            }
            for (int i = 0; i < mapSize; i++) {
                for (int j = 0; j < mapLen; j++) {
                    if (map[i][j] == 'x') {
                        map[i][j] = '.';
                    }
                }
            }
        }
        
        for (int i = 0; i < mapSize; i++) {
            free(map[i]);
        }
        free(map);
        printf("%lu\n", total);

        exit(0);
    }
}
int main() {
    signal(SIGINT, sighandler);
    char buf[256];
    map = malloc(sizeof(char *));
    while (scanf("%s", buf) == 1) {
        mapLen = strlen(buf);
        map[mapSize] = malloc(256);
        strcpy(map[mapSize], buf);

        mapSize++;
        map = realloc(map, (mapSize+1)*sizeof(char*));
    }
    for (int i = 0; i < mapSize; i++) {
        free(map[i]);
    }
    free(map);
    return 0;
}