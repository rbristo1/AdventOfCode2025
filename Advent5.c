#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
uint64_t total = 0;
typedef struct {
    uint64_t min;
    uint64_t max;
} Range;

void sighandler(int sig) {
    if (SIGINT == sig) {
        printf("total fresh: %lu\n", total);
        exit(0);
    }
}
bool isWithinRange(uint64_t * min, uint64_t * max, uint64_t check, int size) {
    for (int i = 0; i < size; i++) {
        if (check >= min[i] && check <= max[i]) {
            return true;
        }
    }
    return false;
}

int cmpRange(const void *a, const void *b) {
    const Range *ra = a;
    const Range *rb = b;
    return (ra->min > rb->min) - (ra->min < rb->min);
}

uint64_t sumMergedRanges(uint64_t *min, uint64_t *max, int size) {
    Range *r = malloc(size * sizeof(Range));
    for (int i = 0; i < size; i++) {
        r[i].min = min[i];
        r[i].max = max[i];
    }

    qsort(r, size, sizeof(Range), cmpRange);

    uint64_t total = 0;

    uint64_t tempMin = r[0].min;
    uint64_t tempMax = r[0].max;

    for (int i = 1; i < size; i++) {
        if (r[i].min <= tempMax + 1) {
            if (r[i].max > tempMax)  {
                tempMax = r[i].max;
            }
        } 
        else {
            total += tempMax - tempMin + 1;
            tempMin = r[i].min;
            tempMax = r[i].max;
        }
    }

    total += tempMax - tempMin + 1;

    free(r);
    return total;
}

int main() {
    signal(SIGINT, sighandler);
    char buf[256] = {0};
    uint64_t * min = malloc(sizeof(uint64_t));
    uint64_t * max = malloc(sizeof(uint64_t));
    int size = 0;
    while(fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = 0;
        if (strlen(buf) == 0) {
            break;
        }
        sscanf(buf, "%lu-%lu", &min[size], &max[size]);
        size++;
        min = realloc(min, sizeof(uint64_t)*(size+1));
        max = realloc(max, sizeof(uint64_t)*(size+1));
    }
    uint64_t check = 0;
    
    while(scanf("%lu", &check) == 1) {
        if (isWithinRange(min, max, check, size)) {
            total++;
        }
        printf("Summed Indices: %lu\n", sumMergedRanges(min,max,size));
    }
    return 1;
}