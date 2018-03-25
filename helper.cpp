#include "project.h"
#include "helper.h"

const double max(const double &a, const double &b) {
  return (a < b) ? b : a;
}

double calc_payoff(op_t option, double st, double k) {
    if (option == CALL) return max(0, st-k);
    else if (option == PUT) return max(0, k-st);
}
