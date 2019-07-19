// Day 2
// Homework 1 - Exercise 1: HPC basics
// Martina Fraschini

#include <iostream>

using namespace std;

// define function to compute the maximum speed-up (Amdahl's Law):
double AmdahlsLaw(double const s, double percent) 
{
    double speedup;
    double p;
    p = percent / double(100);
    speedup = 1 / (p + (1 / s) * (1 - p));

    return speedup;
}



int main()
{
    cout << "\nAmdahl's Law: S(p, s) = 1/(p + (1/s)*(1-p)), \nwhere S is the speed-up, p the proportion of the program that remains serial and s the number of processors. " << endl;
    cout << "In our case, with s = 100 CPUs and p = 0.4%, we have S(100, 0.004) = " << AmdahlsLaw(100, 0.4) << "\n" << endl;

    return 0;
}