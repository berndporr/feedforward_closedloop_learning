#include "trace.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

int main (int, char **)
{
    double dampingCoeff = 0.51;
    double cutoff = 0.1;

    fprintf (stderr, "Using cufoff = %f.\n", cutoff);

    FCLTrace fclTrace;
    fclTrace.setParameters (cutoff, dampingCoeff);
    fclTrace.impulse("impulse.dat");
    fclTrace.filter(0);
    for(int i = 0; i < 100; i++) {
        fclTrace.filter(1);
    }
    double v = fclTrace.filter(0);
    if (0 == v) {
        fprintf(stderr,"fclTrace has zero output after step response");
        throw;
    }
    if (fabs(v) > 1) {
        fprintf(stderr,"fclTrace output is too large: %f\n",v);
        throw;
    }
}
