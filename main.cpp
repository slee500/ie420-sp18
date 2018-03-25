#include <iostream>
#include <fstream>
#include <ctime>

#include "main.h"
#include "CRR_binomial.h"
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
    params.k = 100;
    params.t = 1;
    params.s0 = 100;
    params.sigma = 0.2;
    params.r = 0.05; 
    params.q = 0.04; 
    params.n = 1; 
    params.exercise = AMERICAN;

    // cout << "Black-Scholes Option Price: " << black_scholes(params) << endl;
    
    double option_price = CRR_binomial(params);
    cout << "CRR-Binomial Option Price: " << option_price << endl;
    cout << "Critical Stock Price: " << critical_price(params, option_price) << endl;

    // for (int i = 1; i <= 1000; i += 1) {
    //     params.n = i;
    //     outfile << "N = " << i << ", " << CRR_binomial(params) << endl;
    // }
    
    // Close the output file
    outfile.close();

    // End the timer
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Time taken: " << duration << endl;

    return 0;
}
