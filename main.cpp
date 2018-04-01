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
    // ofstream outfile;
    // outfile.open("output.csv");

    // Configure parameters here
    params_t params;
    params.option = CALL; 
    params.k = 100;
    params.t = 10.0/12.0;
    params.sigma = 0.2; 
    params.r = 0.05; 
    params.q = 0.04; 
    params.n = 1000; // Variable
    params.exercise = AMERICAN;
    
    // Set do_CRR to 'true' if we want to use sigma to find 'u' and 'd'
    params.do_CRR = true;
    // params.u = 1.05;
    // params.d = 0.95;

    double option_price;
    for (double s0 = 149; s0 >= 148; s0 -= 0.01) {
        params.s0 = s0;
        option_price = binomial(params);
        cout << "S0 = " << params.s0;
        cout << ", Option Price = " << option_price; 
        cout << ", Critical Price = " << critical_price(params, option_price) << endl;
    }
    
    // Close the output file
    // outfile.close();

    // End the timer
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time taken: " << duration << "s" << endl;

    return 0;
}
