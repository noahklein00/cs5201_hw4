// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 4 - Implicit Solvers, p-norms, and 
//					Insulin/Glucose Dynamics
// Filename   : driver.cpp

#include "MyVector.h"
#include "IGsolver.h"
#include "PID.h"
#include <iostream>

using namespace std;

int main()
{
	try
	{
		const short TIME_STEPS = 667;
		MyVector<float> initial({400,0,200});
		IGsolver<float> IG(.15, initial);
		PID controller(.15, 100);
		
		for(int i = 0; i < TIME_STEPS; i++)
		{
			IG(controller(IG.getGlucose()));
			IG.print();
		}
	}
	catch(std::domain_error& e)
	{
		std::cerr << "Exception caught, index out of range: " 
			<< e.what() << endl;
	}
	catch(std::length_error& e)
	{
		std::cerr << "Exception caught, incorrect vector length: " 
			<< e.what() << endl;
	}
	
	return 0;
}