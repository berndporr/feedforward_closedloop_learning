#include "fcl_util.h"
#include <math.h>

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * (C) 2017, Bernd Porr <bernd@glasgowneuro.tech>
 * (C) 2017, Paul Miller <paul@glasgowneuro.tech>
 **/

FeedforwardClosedloopLearningWithFilterbank::
    FeedforwardClosedloopLearningWithFilterbank (
        const int num_of_inputs,
        const std::vector<int> &num_of_neurons_per_layer,
        const int num_filtersInput, const double minT, const double maxT)
    : FeedforwardClosedloopLearning (num_of_inputs * num_filtersInput,
                                     num_of_neurons_per_layer)
{
#ifdef DEBUG
    fprintf (
        stderr,
        "Creating instance of FeedforwardClosedloopLearningWithFilterbank.\n");
#endif
    nFiltersPerInput = num_filtersInput;
    nInputs = num_of_inputs;
    assert ((nInputs * nFiltersPerInput) == getNumInputs ());
    fclTrace = new FCLTrace **[(unsigned)num_of_inputs];
    errors.resize ((unsigned)(num_of_inputs * num_filtersInput));
    filterbankOutputs.resize ((unsigned)(num_of_inputs * num_filtersInput));
    for (int i = 0; i < num_of_inputs; i++)
    {
        fclTrace[i] = new FCLTrace *[(unsigned)num_filtersInput];
        double fs = 1;
        double fmin = fs / maxT;
        double fmax = fs / minT;
        double df = (fmax - fmin) / ((double)(num_filtersInput - 1));
        double f = fmin;
#ifdef DEBUG
        fprintf (stderr, "fclTrace: fmin=%f,fmax=%f,df=%f\n", fmin, fmax, df);
#endif
        for (int j = 0; j < num_filtersInput; j++)
        {
            fclTrace[i][j] = new FCLTrace ();
#ifdef DEBUG
            fprintf (stderr, "fclTrace[%d][%d]->setParameters(%f,%f)\n", i, j,
                     f, dampingCoeff);
#endif
            fclTrace[i][j]->setParameters (f, dampingCoeff);
            f = f + df;
#ifdef DEBUG
            for (int k = 0; k < maxT; k++)
            {
                double a = 0;
                if (k == minT)
                {
                    a = 1;
                }
                double b = fclTrace[i][j]->filter (a);
                assert (b != NAN);
                assert (b != INFINITY);
            }
#endif
            fclTrace[i][j]->reset ();
            errors[(unsigned)(i * nFiltersPerInput + j)] = 0;
        }
    }
}

FeedforwardClosedloopLearningWithFilterbank::
    ~FeedforwardClosedloopLearningWithFilterbank ()
{
    for (int i = 0; i < nInputs; i++)
    {
        for (int j = 0; j < nFiltersPerInput; j++)
        {
            delete fclTrace[i][j];
        }
        delete[] fclTrace[i];
    }
    delete[] fclTrace;
}

void FeedforwardClosedloopLearningWithFilterbank::doStep (
    const std::vector<double> &input, const std::vector<double> &error)
{
    if (input.size () != (unsigned)nInputs)
    {
        char tmp[256];
        sprintf (tmp, "Input array dim mismatch: got: %ld, want: %d.",
                 input.size (), nInputs);
#ifdef DEBUG
        fprintf (stderr, "%s\n", tmp);
#endif
        throw tmp;
    }
    if (error.size () != (unsigned)nInputs)
    {
        char tmp[256];
        sprintf (tmp,
                 "Error array dim mismatch: got: %ld, want: %d "
                 "which is the number of inputs.",
                 error.size (), nInputs);
#ifdef DEBUG
        fprintf (stderr, "%s\n", tmp);
#endif
        throw tmp;
    }
    for (int i = 0; i < nInputs; i++)
    {
        for (int j = 0; j < nFiltersPerInput; j++)
        {
            filterbankOutputs[(unsigned)(i * nFiltersPerInput + j)]
                = fclTrace[i][j]->filter (input[(unsigned)i]);
            errors[(unsigned)(i * nFiltersPerInput + j)] = error[(unsigned)i];
        }
    }
    FeedforwardClosedloopLearning::doStep (filterbankOutputs, errors);
}
