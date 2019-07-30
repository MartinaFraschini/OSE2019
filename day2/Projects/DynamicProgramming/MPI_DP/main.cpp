/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
 * main.cpp
 * 
 * In this file, we perform and time Value Function Iterations. 
 * Furthermore, we store the results of certain 
 * iterations in text files. We end by computing the time it takes 
 * to write the results of a single iteration. 
 * 
 * Simon Scheidegger -- 06/18
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/ 

#include <iostream>
#include <fstream>
#include "param.hpp"
#include "econ.hpp"
#include <mpi.h>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[]) {
    
    // time variables
    double t1, t2;
    
    
    // Declare Old Value Function Matrix
    MatrixXd ValOld(nk, ntheta);
    
    
    // Declare Value Function Iteration Function
    MatrixXd ValIt(MatrixXd ValOld);
    
    // Unit for Printing Data to text files
    ofstream output;
    
    // Dummy Variable for the return value of scanf
    int dumm;
    
    MPI_Init(&argc, &argv);
    
    int my_rank, size;
    
    // Obtain number of proccesses and id's
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Declare Policy Function
    MatrixXd Policy=(my_rank==0) ? MatrixXd::Zero(nk, ntheta): MatrixXd::Zero(1,1);
    
    // Matrix for storing Data in desired format
    
    MatrixXd Display= (my_rank==0) ? MatrixXd::Zero(nk, nout) : MatrixXd::Zero(1,1);
    
    // Result is a (2nk x ntheta) matrix that will store the matrix returned by ValIt
    MatrixXd Result=(my_rank==0) ? MatrixXd::Zero(2*nk, ntheta) : MatrixXd::Zero(1,1);
    
    
    if (my_rank==0) {
        if (numstart==0) {
            ValOld=MatrixXd::Zero(nk, ntheta);
        }
        
        else {
            float f,g;
            FILE * pFile;
            
            for (int j=0; j<ntheta; j++) {
                char filename_dummy[100];
                sprintf(filename_dummy,"%s%.2f%s%d%s", "results/theta_" ,thetagrid(j),"_", numstart,".txt");
                pFile=fopen(filename_dummy, "r+");
                
                dumm=fscanf(pFile, "%*s %*s %*s");
                
                for (int i=0; i<nk; i++) {
                    dumm=fscanf (pFile, " %*f %f %f ", &f, &g);
                    ValOld(i,j)=f;
                    Policy(i,j)=g;
                }
                
                fclose(pFile);
            }
            
        }

        
    }
    
    MatrixXd ValNew=(my_rank==0) ? ValOld: MatrixXd::Zero(1,1);
    

    // We will now do Value Function Iteration Numits times and time it
    t1=MPI_Wtime();
    for (int i=numstart; i<Numits; i++) {
        if (my_rank==0) {
            ValOld=ValNew;
        }
        MPI_Bcast(ValOld.data(), nk*ntheta, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        
        // Extract Value Function and Policy Function and compute Final error
        
        Result=ValIt(ValOld);
        
        
        ValNew=(my_rank==0) ? Result.topLeftCorner(nk,ntheta) : Result;
        Policy=(my_rank==0) ? Result.bottomRightCorner(nk, ntheta) : Result;
        
        if (my_rank==0) {
            errmax=(ValNew-ValOld).array().abs().maxCoeff();
            printf("iteration %d max error %f \n", i+1, errmax);
            
            if (i % datafreq==0) {
                for (int j=0; j<ntheta; j++) {
                    // Create text file where we will store results
                    char filename_dummy[100];
                    sprintf(filename_dummy,"%s%.2f%s%d%s", "results/theta_" , thetagrid(j), "_", i+1, ".txt");
                    output.open(filename_dummy);
                    
                    // Store data as desired in Display and print results into the text file
                    Display<<kgrid, ValNew.col(j), Policy.col(j);
                    output<<" kgrid "<<" ValNew "<< " Policy " << endl;
                    output<<Display;
                    output.close();
                }
                
            }

            
        }
        
        
    }
    
    t2=MPI_Wtime();
    
    if (my_rank==0) {
        
        // Print Elapsed Time
        printf( "Iterations took %f seconds\n", t2 - t1 );
        
        // Perform Final Iteration and Store Both the Value Function Guess
        // and the Policy Function Guess
        
        ValOld=ValNew;
        
    }
    
    MPI_Bcast(ValOld.data(), nk*ntheta, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    
    Result=ValIt(ValOld);
    
    
    if (my_rank==0) {
        // Time Final Part (Writing Part)
        t1=MPI_Wtime();
        
        // Extract Value Function and Policy Function and compute Final error
        
        ValNew=Result.topLeftCorner(nk,ntheta);
        errmax=(ValNew-ValOld).array().abs().maxCoeff();
        Policy=Result.bottomRightCorner(nk, ntheta);
        
        // Print kgrid and the corresponding Values and Policies into a text file for each theta
        
        for (int i=0; i<ntheta; i++) {
            // Create text file where we will store results
            char filename_dummy[100];
            sprintf(filename_dummy,"%s%.2f%s", "results/theta_" ,thetagrid(i),"_testing.txt");
            output.open(filename_dummy);
            
            // Store data as desired in Display and print results into the text file
            Display<<kgrid, ValNew.col(i), Policy.col(i);
            output<<" kgrid "<<" ValNew "<< " Policy " << endl;
            output<<Display;
            output.close();
        }
        
        // End timing
        t2=MPI_Wtime();
        
        printf("Final Part (writing) took %f seconds\n", t2 - t1 );
    }
    
    
    MPI_Finalize();
    
    return 0;
    
 }
 
