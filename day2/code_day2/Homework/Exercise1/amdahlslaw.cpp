// Day 2
// Homework 1 - Exercise 1: HPC basics
// Martina Fraschini

#include <iostream>

using namespace std;

// define function to compute the maximum speed-up (Amdahl's Law):
double AmdahlsLaw(double const p, double f_percent) 
{
    double speedup;
    double f;
    f = f_percent / double(100);
    speedup = 1 / (f + (1 - f)/p);

    return speedup;
}



int main()
{
    cout << "\nAmdahl's Law: S(p, N) = 1/(f + (1-f)/p), \nwhere S is the speed-up, f the proportion of the program that remains serial and p the number of processors. " << endl;
    cout << "In our case, with p = 100 CPUs and f = 0.4%, we have S = " << AmdahlsLaw(100, 0.4) << "\n" << endl;

    return 0;
}