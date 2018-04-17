#ifndef _MAIN_H
#define _MAIN_H

enum ex_t {AMERICAN, EUROPEAN};
enum op_t {CALL, PUT};

struct bin_ret_t {
    double option_price;
    double duration;
};

struct params_t {
    op_t option;    // CALL or PUT
    double k;       // Strike price
    double t;       // Time to maturity
    double s0;      // Initial Stock price
    double sigma;   // Volatility
    double r;       // cont. compounding risk-free i/r
    double q;       // cont. dividend yield
    int n;          // number of time steps 
    ex_t exercise;  // AMERICAN or EUROPEAN
    
    bool do_CRR;    // 'false' to input values for u & d
    double u;       // Up movement in stock price
    double d;       // Down movement in stock price
};

void run_Q2();
void run_Q3();
void run_Q4();

void find_option_price(params_t &params);
double q3_find_crit(params_t &params, double lb, double hb);
double q4_find_crit(params_t &params, double lb, double hb);

#endif /* _MAIN_H */