#include <iostream>
#include <cmath>

#include "main.h"
#include "helper.h"
#include "CRR_binomial.h"

using namespace std;

double update_s_star(op_t option, double s_star,  double stk_px, double op_px, double intr_val) {
    double s_star_ret = s_star;
    if (abs(op_px - intr_val) < 0.005) {
        if (option == PUT) {
            s_star_ret = (stk_px > s_star) ? stk_px : s_star;
        } 
        else if (option == CALL) {
            s_star_ret = (stk_px < s_star) ? stk_px : s_star;
        }
    } 
    return s_star_ret;
}

double critical_price(params_t &p, double option_price) {
    if (p.exercise == EUROPEAN) {
        cout << "ERROR: We only find critical price for American options." << endl;
        return -1;
    }

    // We want to compare the option price with the option intrinsic value
    double st, intrinsic_value;
    
    // TODO: What about the number of time steps when calculating st?
    st = 0; // ??;
    intrinsic_value = calc_payoff(p.option, st, p.k);
        
    // For a put, S*(i) is the largest stock price at which the difference between the option price and intrinsic value is less than 0.005
    // TODO: Complete this

    // For a call, S*(i) is the smallest stock price at which the difference between the option price and intrinsic value is less than 0.005
    // TODO: Complete this

    return 0;
}

