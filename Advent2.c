#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
uint64_t total = 0;
void sighandler(int sig) {
    if (SIGINT == sig) {
        printf("total: %lu\n", total);
        exit(0);
    }
}
int main() {
    signal(SIGINT, sighandler);
    uint64_t num1, num2;
    while(scanf("%lu-%lu,", &num1, &num2) == 2) {
        for (uint64_t i = num1; i <= num2; i++) {
            char str[256]= {0};
            char sstr[256] = {0};
            sprintf(str, "%lu", i);
            for (int j = 0; j < strlen(str)/2; j++) {
                bool fail = false;
                int k;
                for (k = 0; k <= j; k++) {
                    sstr[k] =  str[k];
                }
                sstr[k+1] = '\0';
                uint64_t subnum = 0;
                sscanf(sstr, "%lu", &subnum);
                
                if (subnum == 0) {
                    continue;
                }
                char derivedstr[256]= {0};
                uint64_t temp = i/subnum;

                sprintf(derivedstr, "%lu", temp);
                if (derivedstr[0] != '1' || derivedstr[strlen(derivedstr)-1] != '1') {
                    fail = true;
                }
                if (strlen(sstr) == strlen(str)) {
                    fail = true;
                }
                //uncomment for part 1
                /*for (k = 1; k < strlen(derivedstr)-1; k++) {
                   // printf("derstr: %s\n", derivedstr);
                    if (derivedstr[k] != '0') {
                        fail = true;
                        //printf("failed\n");
                        break;
                    }
                }*/
                if (!fail) {
                    bool noteq = false;
                    for (int k = 0; k < strlen(str); k++) {
                        if (str[k] != sstr[k%strlen(sstr)]) {
                            noteq = true;
                            break;
                        }
                    }
                    if (noteq) {
                        continue;
                    }
                    total += i;
                    break;
                }
                
            }
        }
    }
    

}