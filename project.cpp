#include <iostream>

#include "project.h"
#include "CRR_bin.h"
#include "black_scholes.h"

using namespace std;

int main(int argc, char** argv) {
    params_t params;
    params.option = PUT; 
    params.k = 1.5;
    params.t = 1;
    params.s0 = 1.5;
    params.sigma = 0.2;
    params.r = 0.05; 
    params.q = 0.04; 
    params.n = 1; 
    params.exercise = EUROPEAN;
    cout << "Option Price: " << black_scholes(params) << endl;

    return 0;
}
