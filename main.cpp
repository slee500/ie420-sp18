#include <iostream>
#include <fstream>
#include <ctime>


#include "main.h"
#include "binomial.h"
#include "black_scholes.h"
#include "critical_price.h"

using namespace std;

int main(int argc, char** argv) {
    // Start the timer
    clock_t start;
    double duration;
    start = clock();

    // Create output file
    ofstream outfile;
    outfile.open("output.csv");

    // Configure parameters here
    params_t params;
    params.option = PUT; 
    params.k = 1.26;
    params.t = 2;
    params.s0 = 1.26;
    params.sigma = 0.2; 
    params.r = 0.02; 
    params.q = 0.005; 
    params.n = 2; 
    params.exercise = AMERICAN;
    
    // If we don't want to use sigma to find 'u' and 'd'
    params.do_CRR = false;
    params.u = 1.05;
    params.d = 0.95;

    cout << "Put price: " << binomial(params) << endl;

    // double crr_option_price = binomial(params);
    // cout << "CRR-Binomial Option Price: " << crr_option_price << endl;
    // double options_price = black_scholes(params);
    // cout << "Black-Scholes Option Price: " << options_price << endl;
    
    // cout << "Critical Stock Price: " << critical_price(params, crr_option_price) << endl;

    // for (int i = 1; i <= 1000; i += 1) {
    //     params.n = i;
    //     outfile << "N = " << i << ", " << binomial(params) << endl;
    // }
    
    // Close the output file
    outfile.close();

    // End the timer
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time taken: " << duration << "s" << endl;

    return 0;
}
