#include <iostream>
#include <cmath>

#include "main.h"
#include "helper.h"
#include "black_scholes.h"

using namespace std;

double normal(double x) {
    /* Sources: 
     * 1. https://stackoverflow.com/questions/12644745/c-normal-distribution
     * 2. https://stats.stackexchange.com/questions/187828/how-are-the-error-function-and-standard-normal-distribution-function-related
     *
     * CDF(x) = (1 + ERF(x / sqrt(2))) / 2
     */
    double CDF = 0.5 + 0.5 * erf(x / sqrt(2.0));
    return CDF;
}

double black_scholes(params_t &p) {
    if (p.exercise == AMERICAN) {
        cout << "ERROR: We only implement Black-Scholes for pricing European options." << endl;
        return -1;
    }

    // Calculate d1 and d2 as per the equations in the slides 
    double d1 = log(p.s0 / p.k) + p.t * (p.r - p.q + 0.5*pow(p.sigma, 2)) / (p.sigma * sqrt(p.t));
    double d2 = d1 - p.sigma * sqrt(p.t);

    if (p.option == CALL) {
        // c = s0 * exp(-qT) * N(d1) - k * exp(-rT) * N(d2)
        return (p.s0 * exp(-p.q * p.t) * normal(d1)) - (p.k * exp(-p.r * p.t) * normal(d2));
    } 
    else if (p.option == PUT) {
        // p = -s0 * exp(-qT) * N(-d1) + k * exp(-rT) * N(-d2)
        return (-p.s0 * exp(-p.q * p.t) * normal(-d1)) + (p.k * exp(-p.r * p.t) * normal(-d2));
    }
    return 0;
}

