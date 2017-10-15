#include "TnStatistic.h"
#include "spline.h"
#include <algorithm>
#include <cmath>
using namespace std;

double mean(const vector<double> &y)
{
    double sum = 0;
    for (unsigned i = 0; i < y.size(); ++i)
        sum += y[i];

    return sum / (double)y.size();
}

double standard_deviation(const vector<double> &y)
{
    double mu = mean(y);
    double sum = 0;
    for (unsigned i = 0; i < y.size(); ++i)
        sum += pow(y[i] - mu, 2.0);

    return sqrt(sum / ((double)y.size() - 1.0));
}

double standard_error(const vector<double> &y)
{
    return 1.96 * standard_deviation(y) / sqrt((double) y.size());
}

double upper_percentage_point(const double alpha)
{
    /* The data for upper percentage points were calculated previously on the Mathematica notebooks provided.
       This function interpolates those results, defined in the ConfidenceIntervals header. */
    vector<double> alphas({ 0.001, 0.005, 0.01, 0.025, 0.05, 0.1, 0.15, 0.25, 0.5 });
    vector<double> qs({ 7.803, 5.768, 4.909, 3.798, 2.983, 2.200, 1.768, 1.258, 0.659 });
    tk::spline s;
    s.set_points(alphas, qs);
    return s(alpha);
}

double tn_zero(const vector<double> &y)
{
    unsigned n = (unsigned) y.size();
    double loglik = 0;
    double kx, fnleft, fnright, op1, op2;
    
    vector<double> x = y;
    sort(x.begin(), x.end());
    
    for (unsigned i = 0; i < n; ++i)
    {
        kx = fabs(x[i]);
        fnleft = 0;
        fnright = 0;

        /* We can guarantee that to stop at the condition x[j] >= kx and x[j] > -kx because
           of the previously done sorting. */
        for (unsigned j = 0; (j < n) && (x[j] < kx); ++j)
            ++fnleft;

        for (unsigned j = 0; (j < n) && (x[j] <= -kx); ++j)
            ++fnright;
        
        op1 = n - fnleft;
        op2 = fnright + op1;
        if (fnright > 0)
            loglik += fnright * log(op2 / (2 * fnright));
        
        if (fnleft < n)
            loglik += op1 * log(op2 / (2 * op1));
    }
    
    return -(2 * loglik) / n;
}

double tn(vector<double> y, const double c)
{
    // Shift every entry.
    for (unsigned i = 0; i < y.size(); ++i)
        y[i] = y[i] - c;
        
    return tn_zero(y);
}

vector< Coord<double> > ranged_tn(const std::vector<double> &y, const double cmin, const double cmax, const double deltac)
{
    vector< Coord<double> > out;
    for (double c = cmin; c <= cmax; c += deltac)
        out.push_back(Coord<double>(c, tn(y, c)));
    
    return out;
}
