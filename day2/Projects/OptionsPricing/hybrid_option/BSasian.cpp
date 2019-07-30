/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
 * 
 * This file contains routines to serially compute the call and 
 * put price of an European option.
 * 
 * Simon Scheidegger
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/ 

#include <algorithm>    // Needed for the "max" function
#include <cmath>
#include <iostream>
#include <omp.h>

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 A simple implementation of the Box-Muller algorithm, used to 
generate gaussian random numbers; necessary for the Monte Carlo 
method below. */

double gaussian_box_muller(unsigned int *myseed) {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance" 
  // is less than unity
  do {
    x = 2.0 * rand_r(myseed) / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand_r(myseed) / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a Asian vanilla call option with a Monte Carlo method

double monte_carlo_call_price(const int& num_sims, const int& num_per, const double& S, const double& K, const double& r, const double& v, const double& T) {
  double interv = T / num_per;
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  #pragma omp parallel reduction(+:payoff_sum)
  {
    unsigned int myseed = 25234 + 17 * omp_get_thread_num();
    #pragma omp for
    for (int i=0; i<num_sims; i++) {
      double S_old = S;
      double S_sum = 0.0;
      for (int j=0; j<num_per; j++) {
        double gauss_bm = gaussian_box_muller(&myseed);
        S_cur = S_old * exp((r-0.5*v*v)*interv + sqrt(v*v*interv)*gauss_bm);
        S_sum += S_cur;
        S_old = S_cur;
      }
      payoff_sum += std::max((S_sum / static_cast<double>(num_per)) - K, 0.0);
    }
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a Asian vanilla put option with a Monte Carlo method

double monte_carlo_put_price(const int& num_sims, const int& num_per, const double& S, const double& K, const double& r, const double& v, const double& T) {
  double interv = T / num_per;
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  #pragma omp parallel reduction(+:payoff_sum)
  {
    unsigned int myseed = 25234 + 17 * omp_get_thread_num();
    #pragma omp for
    for (int i=0; i<num_sims; i++) {
      double S_old = S;
      double S_sum = 0.0;
      for (int j=0; j<num_per; j++) {
        double gauss_bm = gaussian_box_muller(&myseed);
        S_cur = S_old * exp((r-0.5*v*v)*interv + sqrt(v*v*interv)*gauss_bm);
        S_sum += S_cur;
        S_old = S_cur;
      }
      payoff_sum += std::max(K - (S_sum / static_cast<double>(num_per)), 0.0);
    }
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc, char **argv) {

  // Parameters                                                                             
  int num_sims = 10000000;   // Number of simulated asset paths
  int num_per = 100;   // Number of periods for each simulated path
  double S = 100.0;  // Option price                                                                                  
  double K = 100.0;  // Strike price                                                                                  
  double r = 0.05;   // Risk-free rate (5%)                                                                           
  double v = 0.2;    // Volatility of the underlying (20%)                                                            
  double T = 1.0;    // One year until expiry
  double stime = -omp_get_wtime();                                                                   

  // Then we calculate the call/put values via Monte Carlo                                                                          
  double call = monte_carlo_call_price(num_sims, num_per, S, K, r, v, T);
  double put = monte_carlo_put_price(num_sims, num_per, S, K, r, v, T);

  stime += omp_get_wtime();

  // Finally we output the parameters and prices                                                                      
  std::cout << "Number of Paths:   " << num_sims << std::endl;
  std::cout << "Number of Periods: " << num_per << std::endl;
  std::cout << "Underlying:        " << S << std::endl;
  std::cout << "Strike:            " << K << std::endl;
  std::cout << "Risk-Free Rate:    " << r << std::endl;
  std::cout << "Volatility:        " << v << std::endl;
  std::cout << "Maturity:          " << T << std::endl;

  std::cout << "Call Price:        " << call << std::endl;
  std::cout << "Put Price:         " << put << std::endl;

  std::cout << "Execution time: " << stime << std::endl;

  return 0;
}
