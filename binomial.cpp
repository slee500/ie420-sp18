#include <iostream>
#include <vector>
#include <cmath> 

#include "main.h"
#include "helper.h"
#include "binomial.h"

using namespace std;

double binomial(params_t &p) {
    /* Calcualte u, d, p_star */
    double delta, u, d, p_star;
    delta = p.t/(double) p.n; // Ensure correct typecasting
    if (p.do_CRR == true) {
        u = exp(p.sigma * sqrt(delta));
        d = exp(-p.sigma * sqrt(delta));
    } else {
        u = p.u;
        d = p.d;
    }     
    p_star = (exp((p.r - p.q) * delta) - d) / (u - d);

    /* Calculate payoffs at maturity */
    vector<double> payoffs;
    double st;
    for (int i = 0; i <= p.n; i++) {
        // i represents to the number of "down" moves
        st = pow(u, p.n - i) * pow(d, i) * p.s0;
        payoffs.push_back(calc_payoff(p.option, st, p.k));
    }

    /* Backward Induction to find option price f0 */
    double p_fu, p_fd, max1, max2;
    int j_limit;
    while (payoffs.size() > 1) {
        j_limit = payoffs.size()-1;
        for (int j = 0; j < j_limit; j++) {
            // Calculate the payoff using the risk-neutral probability
            p_fu = p_star * payoffs[j];
            p_fd = (1-p_star) * payoffs[j+1];

            if (p.exercise == EUROPEAN) {
                payoffs[j] = exp(-p.r * delta) * (p_fu + p_fd);
            }
            else if (p.exercise == AMERICAN) {
                // Need additional calculations for American options 
                max1 = exp(-p.r * delta) * (p_fu + p_fd); 

                // Here, j represents the number of "down" moves
                st = pow(u, j_limit-1-j) * pow(d, j) * p.s0;
                max2 = calc_payoff(p.option, st, p.k);
                payoffs[j] = max(max1, max2);
            }
        }
        // Remove last element from "payoffs" since we no longer need it
        payoffs.pop_back(); 
    }
    // When we have finished iterating, the "payoffs" vector will be size 1 and containing the option price f0
    return payoffs[0];
}
