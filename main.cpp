#include <iostream>
#include <fstream>
#include <cfloat>
#include <string> 

#include "main.h"
#include "binomial.h"
#include "black_scholes.h"
#include "critical_price.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Enter 2, 3 or 4 to pick which question to run." << endl;
    } else {
        if (argv[1][0] == '1') run_Q1();
        else if (argv[1][0] == '2') run_Q2();
        else if (argv[1][0] == '3') run_Q3();
        else if (argv[1][0] == '4') run_Q4();
        else {
            cout << "Enter 2, 3 or 4 to pick which question to run." << endl;
        }
    }

    return 0;
}

void run_Q1() {
    // Configure parameters here
    params_t params;
    params.option = CALL; 
    params.k = 100;
    params.t = 1.0;
    params.s0 = 100;
    params.sigma = 0.2; 
    params.r = 0.05; 
    params.q = 0.04; 
    params.exercise = EUROPEAN;
    params.do_CRR = true;

    bin_ret_t bin_result;
    
    params.n = 1000; 
    bin_result = binomial(params);
    cout << "N = " << params.n <<  ", Compute Time = " << bin_result.duration << "s" << endl;
    
    params.n = 5000; 
    bin_result = binomial(params);
    cout << "N = " << params.n <<  ", Compute Time = " << bin_result.duration << "s" << endl;
    
    params.n = 10000; 
    bin_result = binomial(params);
    cout << "N = " << params.n <<  ", Compute Time = " << bin_result.duration << "s" << endl;
}

/****** QUESTION 2 *****/
void run_Q2() {
    // Create/Open output file
    ofstream outfile;
    outfile.open("q2_output.csv");

    // Configure parameters here
    params_t params;
    params.option = CALL; 
    params.k = 100;
    params.t = 1.0;
    params.s0 = 100;
    params.sigma = 0.2; 
    params.r = 0.05; 
    params.q = 0.04; 
    params.n = 1000; // Variable
    params.exercise = EUROPEAN;
    
    // Set do_CRR to 'true' if we want to use sigma to find 'u' and 'd'
    params.do_CRR = true;
    // params.u = 1.05;
    // params.d = 0.95;

    double black_scholes_px = black_scholes(params);
    cout << "The Black-Scholes price of this European call is: " << black_scholes_px << endl;
    cout << "Working..." << endl;
    
    // Vary the value of N to see how the convergence resembles
    outfile << "N,Price" << endl;
    bin_ret_t bin_result;
    for (int N = 100; N <= 10000; N += 100) {
        params.n = N;
        bin_result = binomial(params);
        outfile << N << "," << bin_result.option_price << endl;
    }

    cout << "See q2_output.csv for prices using CRR model." << endl;
    // Close output file
    outfile.close();
}

/****** QUESTION 3 *****/
void run_Q3() {
    // Configure parameters here
    params_t params;
    params.option = PUT; 
    params.k = 100;
    params.s0 = 100; 
    params.sigma = 0.2; 
    params.r = 0.05; 
    params.n = 3000; // Variable
    params.exercise = AMERICAN;
    params.do_CRR = true;

    for (params.q = 0.0; params.q <= 0.04; params.q += 0.04) {
        /* Calculate and plot the price of a 12-month put as a function of s0 */
        params.t = 12.0/12.0;
        find_option_price(params);

        /* For varying time to maturity, find the critical stock price S*(i) */
        ofstream outfile;
        if (params.q == 0.04) outfile.open("q3_output_yield_4_crit_px.csv");
        else if (params.q == 0.0) outfile.open("q3_output_yield_0_crit_px.csv");
        outfile << "S_i,Crit_Price" << endl;

        cout << "q = " << params.q << endl;
        for (double t_month = 1; t_month <= 12; t_month += 1) {
            params.t = t_month/12.0;
            double crit_px = q3_find_crit(params, 50, 100);
            cout << "S*(" << (int) (params.t*12) << ") = " << crit_px << endl;
            outfile << (int) (params.t*12) << "," << crit_px << endl;
        }
        outfile.close();
    }
}

void find_option_price(params_t &params) {
    // Create/Open output file
    ofstream outfile;
    // For Q3
    if (params.option == PUT) {
        if (params.q == 0.04)  outfile.open("q3_output_yield_4_option_px.csv"); 
        else if (params.q == 0.0) outfile.open("q3_output_yield_0_option_px.csv");
    }
    // For Q4
    else if (params.option == CALL) {
        if (params.q == 0.04)  outfile.open("q4_output_yield_4_option_px.csv"); 
        else if (params.q == 0.08) outfile.open("q4_output_yield_8_option_px.csv");
    }
    
    bin_ret_t bin_result;
    outfile << "S0,Option Price" << endl;
    for (int s0 = 50; s0 <= 150; s0 += 1) {
        params.s0 = s0;
        bin_result = binomial(params);
        outfile << s0 << "," << bin_result.option_price << endl;
    }

    // Close output file
    outfile.close();
}

double q3_find_crit(params_t &params, double lb, double hb) {
    bin_ret_t bin_result;
    double prev_crit_px, curr_crit_px;
    double lower_bound = 0, higher_bound = 0;
    
    for (double s0 = lb; s0 <= hb; s0 += 1) {
        params.s0 = s0;
        bin_result = binomial(params);
        prev_crit_px = curr_crit_px;
        curr_crit_px = critical_price(params, bin_result.option_price);
        
        if (curr_crit_px <= 0.01) {
            // curr_crit_px price is now zero
            lower_bound = s0-1;
            higher_bound = s0;
            break;
        } 
    }

    for (double s0 = lower_bound; s0 <= higher_bound+0.01; s0 += 0.01) {
        params.s0 = s0;
        bin_result = binomial(params);
        prev_crit_px = curr_crit_px;
        curr_crit_px = critical_price(params, bin_result.option_price);
        if (curr_crit_px <= 0.01) {
            // curr_crit_px is now zero
            return prev_crit_px;
        } 
    }
    return 0.0;
}

void run_Q4() {
    // Configure parameters here
    params_t params;
    params.option = CALL; 
    params.k = 100;
    params.s0 = 100; 
    params.sigma = 0.2; 
    params.r = 0.05; 
    params.n = 3000; // Variable
    params.exercise = AMERICAN;
    params.do_CRR = true;

    for (params.q = 0.04; params.q <= 0.08; params.q += 0.04) {
        /* Calculate and plot the price of a 12-month put as a function of s0 */
        params.t = 12.0/12.0;
        find_option_price(params);

        /* For varying time to maturity, find the critical stock price S*(i) */
        ofstream outfile;
        if (params.q == 0.04) outfile.open("q4_output_yield_4_crit_px.csv");
        else if (params.q == 0.08) outfile.open("q4_output_yield_8_crit_px.csv");
        outfile << "S_i,Crit_Price" << endl;

        cout << "q = " << params.q << endl;
        for (double t_month = 11.0; t_month <= 12; t_month += 1) {
            params.t = t_month/12.0;
            double crit_px = q4_find_crit(params, 100, 170);
            cout << "S*(" << (int) (params.t*12) << ") = " << crit_px << endl;
            outfile << (int) (params.t*12) << "," << crit_px << endl;
        }
        outfile.close();
    }
}

double q4_find_crit(params_t &params, double lb, double hb) {
    bin_ret_t bin_result;
    double prev_crit_px, curr_crit_px;
    double lower_bound = 0, higher_bound = 0;
    
    for (double s0 = hb; s0 >= lb; s0 -= 1) {
        params.s0 = s0;
        bin_result = binomial(params);
        prev_crit_px = curr_crit_px;
        curr_crit_px = critical_price(params, bin_result.option_price);
        
        if (curr_crit_px == DBL_MAX) {
            // curr_crit_px price is DBL_MAX
            lower_bound = s0;
            higher_bound = s0+1;
            break;
        } 
    }

    for (double s0 = higher_bound; s0 >= lower_bound-0.01; s0 -= 0.01) {
        params.s0 = s0;
        bin_result = binomial(params);
        prev_crit_px = curr_crit_px;
        curr_crit_px = critical_price(params, bin_result.option_price);
        if (curr_crit_px == DBL_MAX) {
            // curr_crit_px is DBL_MAX
            return prev_crit_px;
        } 
    }
    return 0.0;
}