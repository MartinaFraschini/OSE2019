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

#include <mpi.h>


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 A simple implementation of the Box-Muller algorithm, used to 
generate gaussian random numbers; necessary for the Monte Carlo 
method below. */

double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance" 
  // is less than unity
  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a Asian vanilla call option with a Monte Carlo method

double monte_carlo_call_price(const int& num_sims, const int& num_per, const double& S, const double& K, const double& r, const double& v, const double& T, const int& nitnode) {
  double interv = T / num_per;
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<nitnode; i++) {
    double S_old = S;
    double S_sum = 0.0;
    for (int j=0; j<num_per; j++) {
      double gauss_bm = gaussian_box_muller();
      S_cur = S_old * exp((r-0.5*v*v)*interv + sqrt(v*v*interv)*gauss_bm);
      S_sum += S_cur;
      S_old = S_cur;
    }
    payoff_sum += std::max((S_sum / static_cast<double>(num_per)) - K, 0.0);
  }

  return payoff_sum;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a Asian vanilla put option with a Monte Carlo method

double monte_carlo_put_price(const int& num_sims, const int& num_per, const double& S, const double& K, const double& r, const double& v, const double& T,  const int& nitnode) {
  double interv = T / num_per;
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<nitnode; i++) {
    double S_old = S;
    double S_sum = 0.0;
    for (int j=0; j<num_per; j++) {
      double gauss_bm = gaussian_box_muller();
      S_cur = S_old * exp((r-0.5*v*v)*interv + sqrt(v*v*interv)*gauss_bm);
      S_sum += S_cur;
      S_old = S_cur;
    }
    payoff_sum += std::max(K - (S_sum / static_cast<double>(num_per)), 0.0);
  }

  return payoff_sum;
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
  double call_sum, put_sum;
  double time = 0.; 

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  time -= MPI_Wtime();

  int nitnode = niter/size;
  int rmd = niter % size;
  if (rank<rmd)
  {
      nitnode += 1;
  }

  //set seed
  srand((rank+1)*2);                                                                        

  // Then we calculate the call/put values via Monte Carlo                                                                          
  double call_partial = monte_carlo_call_price(num_sims, num_per, S, K, r, v, T, nitnode);
  double put_partial = monte_carlo_put_price(num_sims, num_per, S, K, r, v, T, nitnode);

  MPI_Reduce(&call_partial, &call_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&put_partial, &put_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  // Finally we output the parameters and prices
  if (rank == 0)
  {
    double call = (call_sum/ static_cast<double>(num_sims)) * exp(-r*T);
    double put = (put_sum / static_cast<double>(num_sims)) * exp(-r*T);
    time += MPI_Wtime();                                                                    
    std::cout << "Number of Paths:   " << num_sims << std::endl;
    std::cout << "Number of Periods: " << num_per << std::endl;
    std::cout << "Underlying:        " << S << std::endl;
    std::cout << "Strike:            " << K << std::endl;
    std::cout << "Risk-Free Rate:    " << r << std::endl;
    std::cout << "Volatility:        " << v << std::endl;
    std::cout << "Maturity:          " << T << std::endl;

    std::cout << "Call Price:        " << call << std::endl;
    std::cout << "Put Price:         " << put << std::endl;

    std::cout << "time : " << time << " seconds" << std::endl;
  }

  MPI_Finalize();

  return 0;
}
