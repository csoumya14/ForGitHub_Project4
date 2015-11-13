#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;
#include "include\armadillo"
using namespace arma;

int periodic(int entrance, int pm, int spins)
//Takes care of the periodic boundary condition of lattice
{
    return (entrance + pm + spins) % spins;
}

int initialize(int spins, mat spin_matrix, double &E, double &M)
{
    E=0; M=0;
    for (int i = 0; i < spins; i++)
    {
        for (int j = 0; j < spins; j++)
        {
            M += spin_matrix(i,j);
            E -= spin_matrix(i,j)
                    *(spin_matrix(i,periodic(j,-1,spins))
                      +spin_matrix(periodic(i,-1,spins),j));
        }
    }
}

int main()
{
    ofstream myfile ("IsingForE_L_10_zoom2.txt");
        if (myfile.is_open())
        {
    int n, mccycles, steady_state;
    //double T;
    cout << "Please enter number of spins in each direction:\n>";
    cin >> n;
    //cout << "Please enter value of T:\n>";
    //cin >> T;
    cout << "Please enter number of MC cycles:\n>";
    cin >> mccycles;
    //cout << "Please enter steady state:\n>";
    //cin >> steady_state;

    myfile << "Number of spins in each direction: " << n << endl;
    //myfile << "Temperature: "   << T    << endl;
    myfile << "Total number of MC cycles: " << mccycles << endl;
    //myfile << "Steady state: " << steady_state  << endl;
    myfile << "Initial spin configuration: random" << endl;
    myfile << "T" << setw(15) << "E" << setw(15) << "M" << setw(15) << "specific_heat" << setw(15) << "susceptibility" << endl;
    double T_initial, T_final, T_step;
    T_initial = 2.33;
    T_final = 2.40;
    T_step = 0.01;

    double E, M; //initialize energy and magnetization
    for (double T = T_initial; T<=T_final; T+=T_step)
    {
    double susceptibility, specific_heat;
    mat spin_matrix(n,n);
    spin_matrix.ones();
    //Spin matrix with random initialization:

    srand(time(NULL));
    int a[n], b[n];
    for (int i=0; i<n; i++)
    {
      for (int j=0; j<n; j++)
      {
    a[j] = (n-0.000001)*((double) rand() / (RAND_MAX));
    b[j] = pow(-1,a[j]);
    spin_matrix(i,j) = b[j];
    }
    }

    initialize(n,spin_matrix,E,M);
    double E_expectation = 0, M_expectation = 0, E_squared = 0, M_squared = 0;
    int accepted_moves = 0;

    int x[n], y[n];
    int microstates = 17;      //pow(2,n*n)+1;
    //Compute w before MC to use the fact that the change of energy only can take 5 different values
    double w[microstates];
    for (int i =0; i < microstates; i++){
        w[i] = 0;
    }
    for (int dE = -8; dE <= 8; dE+=4){
        w[dE+8] = exp(-dE/T);
    }
    int DE;
    srand(time(NULL));

    for (int cycles = 1; cycles <= mccycles; cycles++)
        {
    for (int k=0; k<n; k++)
    {
    for (int i=0; i<n; i++)
    {
    x[i] = (n-0.000001)*((double) rand() / (RAND_MAX));  //making sure that the row and column number is either 0 or 1 (randomly chosen - almost uniform)
    y[i] = (n-0.000001)*((double) rand() / (RAND_MAX));
    DE = 2*spin_matrix(x[i],y[i])
            *(spin_matrix(x[i],periodic(y[i],-1,n))+spin_matrix(x[i],periodic(y[i],1,n))
            + spin_matrix(periodic(x[i],-1,n),y[i]) + spin_matrix(periodic(x[i],1,n),y[i]));
    if (w[DE+8] >= ((double) rand() / (RAND_MAX)))
    {
        spin_matrix(x[i],y[i]) = -spin_matrix(x[i],y[i]);
        E += DE;
        M += 2*spin_matrix(x[i],y[i]);
        accepted_moves += 1;
    }
    }
    }
    //The computed energies are in the unit of E/J
    //The computed susectibilty is in the unit J*Chi
    //The computed specific heat is in the unit c_v / k_B
        E_expectation += E;
        M_expectation += fabs(M);
        E_squared += E*E;
        M_squared += M*M;   
    }

    susceptibility = 1/T * (M_squared/mccycles -(M_expectation/mccycles)*(M_expectation/mccycles));
    specific_heat = 1/(T*T)*(E_squared/mccycles -(E_expectation/mccycles)*(E_expectation/mccycles));
    cout << "Number of MC cycles:" << setw(10) << mccycles << endl;
    //cout << "Most likely state" << endl;
    //cout << spin_matrix << endl;
    //cout << "Number of accepted moves:" << accepted_moves << endl;
    //cout << "Expectation value of energy:" << setw(10) << E_expectation/mccycles << endl;
    //cout << "Expectation value of magnetization:" << setw(10) << M_expectation/mccycles << endl;
    //cout << "Specific heat:" << setw(10) << specific_heat << endl;
    //cout << "Susceptibilty:" << setw(10) << susceptibility << endl;

    myfile << T << setw(15) << E_expectation/mccycles << setw(15) << M_expectation/mccycles << setw(15) << specific_heat << setw(15) << susceptibility << endl;
    }   //Temp for loop ends
        } //myfile closes

        return 0;
    }
