#ifndef _PARAMS_H
#define _PARAMS_H

/* Parameters start */
option_t option = PUT; 
double k        = 5; // Strike price
double t        = 2; // Time to maturity
double s0       = 4; // Initial Stock price
double sigma    = 0; // Volatility
double r        = 0.2231435; // cont. compounding risk-free i/r
double q        = 0; // cont. dividend yield
int n           = 2; // number of time steps 
exercise_t exercise = AMERICAN;
/* Parameters end */

#endif /* _PARAMS_H */