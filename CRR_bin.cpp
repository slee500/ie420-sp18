#include <iostream>
#include <vector>
#include <cmath> 

#include "project.h"
#include "helper.h"

using namespace std;

double CRR_binomial(params_t &p) {
    /* Calcualte u, d, p_star */
    double delta, u, d, p_star;
    delta = p.t/double(p.n); // Ensure correct typecasting
    u = exp(p.sigma * sqrt(delta));
    d = exp(-p.sigma * sqrt(delta));
    // u = 2;
    // d = 0.5;
    p_star = (exp((p.r - p.q) * delta) - d) / (u - d);
    cout << "P-star: " << p_star << endl;

    /* Calculate payoffs at maturity */
    vector<double> payoffs;
    double st;
    for (int i = 0; i <= p.n; i++) {
        st = pow(u, p.n-i) * pow(d, i) * p.s0;
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
                st = pow(u, j_limit-1-j) * pow(d, j) * p.s0;
                max2 = calc_payoff(p.option, st, p.k);
                payoffs[j] = max(max1, max2);
            }
        }
        // Remove last element from "payoffs" since we no longer need it
        payoffs.pop_back(); 
    }
    return payoffs[0];
}