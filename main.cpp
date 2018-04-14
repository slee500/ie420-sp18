#include <iostream>
#include <fstream>

#include "main.h"
#include "binomial.h"
#include "black_scholes.h"
#include "critical_price.h"

using namespace std;

int main(int argc, char** argv) {
    run_Q2();
    return 0;
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
    cout << "Working..."
    
    // Vary the value of N to see how the convergence resembles
    outfile << "N, Price" << endl;
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
    // TODO: Complete this function
}