#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bench.h"

static const char *upper_case_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char *lower_case_alphabet = "abcdefghijklmnopqrstuvwxyz";

double tvgetf()
{
    struct timespec ts;
    double sec;

    clock_gettime(CLOCK_REALTIME, &ts);
    sec = ts.tv_nsec;
    sec /= 1e9;
    sec += ts.tv_sec;

    return sec;
}

int bench_test(const tst_node *root, char *out_file, const int max)
{
    char prefix[3];
    char **sgl;
    FILE *fp = fopen(out_file, "w");
    int idx = 0, sidx = 0;
    double t1, t2;

    if (!fp) {
        fprintf(stderr, "error: file open failed '%s'.\n", out_file);
        return 1;
    }

    sgl = (char **)malloc(sizeof(char *) * max);
    for (int i = 0; i < 26; i++) {
        prefix[0] = upper_case_alphabet[i];
        for (int j = 0; j < 26; j++) {
            prefix[1] = lower_case_alphabet[j];
            for (int k = 0; k < 26; k++) {
                prefix[2] = lower_case_alphabet[k];
                t1 = tvgetf();
                tst_search_prefix(root, prefix, sgl, &sidx, max);
                t2 = tvgetf();
                fprintf(fp, "%d %.6f sec\n", idx, t2 - t1);
                idx++;
            }
        }
    }
    fclose(fp);
    return 0;
}
