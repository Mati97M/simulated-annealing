// symulowane wyrzażanie.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
//#include <vector>
#define M_PI 3.14159265358979323846
////////////////functions

double given_function(double x);
double random_on_try(double x);
std::pair<double, double> getRange(double x);
/////////////algorythm settings
double T = 1.0;
double frozing_factor = 0.8;

const int steps_number = 10;
const int tries = 5;
/////////////////////////////////////////////////
int main()
{
    srand(time(NULL));

    //initializing x & F(x)
    double x = static_cast<double>((rand() % 10001)) / 1000 ;
    double Fx { given_function(x) };
    std::cout << std::setprecision(3) <<"initial x = " << x << "\t initial F(x) = " << Fx << std::endl;

    //maksimum funkcji f(x) = 3sin(πx / 5) + sin(πx)
   
    for (int i = 0; i < steps_number; i++)
    {
        std::cout << "Current tempterature:\t" << T << std::endl;
        for (int j = 0; j < tries; j++)
        {
            double temp_x = random_on_try(x);
            double temp_Fx = given_function(temp_x);
            if (temp_Fx > Fx)   //dla maksymalizacji
            {
                x = temp_x;
                Fx = temp_Fx;
                std::cout << "better solution found in step: " << i << "\t| try: " << j << std::endl
                    << "x = " << x << "\tF(x) = "<< Fx << std::endl;
            }
            else 
            {
                double offer_to_accept = exp((temp_Fx - Fx) / T);
                double level_of_accepting = static_cast<double>(rand() % 1001) / 1000;
                if (offer_to_accept > level_of_accepting)   //update x F(x)
                {
                    x = temp_x;
                    Fx = temp_Fx;
                    std::cout << "Worse solution excepeted in step: " << i << "\t| try: " << j << std::endl
                        << "x = " << x << "\tF(x) = " << Fx << std::endl <<
                        "level_of_accepting: " << level_of_accepting << "\toffer_to_accept was: " << offer_to_accept << std::endl;
                }
            }
        }
        T *= frozing_factor; // updating temperature
    }
    std::cout << "solution: \n" << "x = " << x << "\tF(x) = " << Fx << std::endl;

    return 0;
}

///////////////////////////////////////functions definitions

double given_function(double x)
{
    return 3 * sin(M_PI * x / 5) + sin(M_PI * x); //3sin(πx / 5) + sin(πx);
}

double random_on_try(double x)
{
    double result{};
    auto range = getRange(x);
    int a = (range.first * 1000);
    int b = (range.second * 1000);
    if (a > b) std::cout << "Warning begin is bigger than end!" << std::endl;
    else {
        int b_minus_a = b - a;
        int x = (rand() % (a + 1)) + b_minus_a;
        result = static_cast<double>(x) / 1000;
    }
 
    return result;
}

std::pair<double, double> getRange(double x)
{
    //[0, 10]           //[x-2T, x+2T]
    if (x < 0) std::cout << "Warning! x < 0 !!!" << std::endl;
    double a, b;
     a = x - 2 * T;
     b = x + 2 * T;
     if (a < 0) a = 0.0;
    
     return std::pair<double, double>(a,b);
}
