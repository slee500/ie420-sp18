#!/bin/bash
g++ helper.cpp black_scholes.cpp CRR_binomial.cpp project.cpp -std=c++11 -o project_out
./project_out