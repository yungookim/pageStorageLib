#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

typedef char Record[9];
/**
 * creates runs of length `run_length` in the `out_fp`.
 */
void mk_runs(FILE *in_fp, FILE *out_fp, long run_length); 