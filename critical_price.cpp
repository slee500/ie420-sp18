#include <iostream>
#include <cmath>

#include "main.h"
#include "helper.h"
#include "binomial.h"

using namespace std;

void update_s_star(op_t option, double &s_star,  double stk_px, double op_px, double intr_val) {
    if (abs(op_px - intr_val) < 0.005) {
        if (option == PUT) {                
            // For a put, S*(i) is the largest stock price at which the difference between the option price and intrinsic value is less than 0.005
            s_star = (stk_px > s_star) ? stk_px : s_star;
        } 
        else if (option == CALL) {
            // For a call, S*(i) is the smallest stock price at which the difference between the option price and intrinsic value is less than 0.005
            s_star = (stk_px < s_star) ? stk_px : s_star;
        }
    } 
}

double critical_price(params_t &p, double option_price) {
    if (p.exercise == EUROPEAN) {
        cout << "ERROR: We only find critical price for American options." << endl;
        return -1;
    }

    // Calcualte u, d, p_star */
    double delta, u, d, p_star;
    delta = p.t/double(p.n); // Ensure correct typecasting
    if (p.do_CRR == true) {
        u = exp(p.sigma * sqrt(delta));
        d = exp(-p.sigma * sqrt(delta));
    } else {
        u = p.u;
        d = p.d;
    }

    // We want to compare the option price with the option intrinsic value
    double st, intrinsic_value, s_star;
    s_star = 0;
    // We are supposed to vary the number of time steps 'n' 
    for (int i=0; i<p.n; i++) {
        for (int j=0; j<=i; j++) {
            st = pow(u, i-j) * pow(d, j) * p.s0;
            intrinsic_value = calc_payoff(p.option, st, p.k);
            update_s_star(p.option, s_star, st, option_price, intrinsic_value);
        }
    }
    return s_star;
}

