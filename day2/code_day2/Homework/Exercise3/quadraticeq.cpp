// Day 2
// Homework 1 - Exercise 3: Quadratic Equation
// Martina Fraschini

#include <iostream>
#include <math.h>

using namespace std;

// define function to solve the quadratic equation:
void quad_eq(int a, int b, int c, double& x1, double& x2) 
{
	x1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
	x2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
}



int main()
{
	int a=1, b=0, c=1;
	double x1, x2;

	while(b*b - 4*a*c < 0)
	{
		cout << "Enter the parameters to construct the quadratic equation ax^2 + bx + c = 0" << endl;
		cout << "Parameter a: ";
		cin >> a;
		cout << "Parameter b: ";
		cin >> b;
		cout << "Parameter c: ";
		cin >> c;
		if (b*b - 4*a*c < 0)
		{
			cout << "The delta is negative, please retry.\n" << endl;
		}
	}
	
	quad_eq(a,b,c,x1,x2);

	cout << "\nThe solution is x1 = " << x1 << " and x2 = " << x2 << endl;

	return 0;
}