/*! \file
 *
 * Definitions for the IGsolver class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 4 \n
 */

#ifndef IGSOLVER_H
#define IGSOLVER_H

#include "MyVector.h"
#include "Heun.h"

using namespace std;


/*! \brief max comparison
 *
 * Description: non-member function that is used in the ODE calculations
 * to complete the piecewise part of the signal calculation.
 * \param lhs is one of the values to be compared.
 * \param rhs is one of the values to be compared.
 * \post returns the value that follows the comparison.
 */
float maxFunc(const float lhs, const float rhs)
{
	return (rhs<lhs)?rhs:lhs;
}

/*! \brief max comparison
 *
 * Description: non-member function that is used in the ODE calculations
 * to complete the piecewise part of the signal calculation.
 * \param lhs is one of the values to be compared.
 * \param rhs is one of the values to be compared.
 * \post returns the value that follows the comparison.
 */
float maxFunc2(const float lhs, const float rhs)
{
	return (rhs<lhs)?lhs:rhs;
}

//! IGsolver class.
/*!
 * This class simulates an Insulin/Glucose dynamic system.
 */
template <typename T>
class IGsolver
{
	private:
		float m_step; /*!< A float to hold the step size for the
					   Insulin/Glucose model.*/
		MyVector<T> m_GXI; /*!< A MyVector that holds the state of 
							the simulation. */
		MyVector<T> m_new_state; /*!< A MyVector that temporarily stores
								  the new state of the simulation. */
		float m_control_signal; /*!< A float that holds the value of the 
								 control signal passed into the object. */
		
		Heun<T> m_glucose; /*!< A Heun object that stores the ODE for the 
							Glucose part of the simulation. */
		Heun<T> m_helper; /*!< A Heun object that stores the ODE for the 
						   Helper ODE part of the simulation. */
		Heun<T> m_insulin; /*!< A Heun object that stores the ODE for the 
							Insulin part of the simulation. */
		
	public:
	
		/*! \brief constructor
		 *
		 * Description: Constructor for the IGsolver object that initializes
		 * the step size and initial constants for the object.
		 * \param h is the step size to be initialized.
		 * \param initial is the the MyVector object that stores the initial 
		 * values for the initial state of the system.
		 * \post An IGsolver object is initialized with the proper values.
		 * \throw Throws a std::domain_error object if h <= 0.
		 */
		IGsolver(const float h, const MyVector<T>& initial);
		
		/*! \brief copy constructor
		 *
		 * Description: Copy constructor for the IGsolver object that
		 * initializes a new IGsolver object with the values passed through
		 * the parameter.
		 * \param rhs is the IGsolver object to be copied.
		 * \post A IGsolver object is initialized with the values of the
		 * object passed.
		 */
		IGsolver(const IGsolver<T>& rhs);
		
		/*! \brief operator =
		 *
		 * Description: Sets the values of the calling object equal to the 
		 * values of the object passed.
		 * \param rhs is the object to be copied.
		 * \return Returns *this with the copied values.
		 * \post A IGsolver object is initialized with the values of the
		 * object passed.
		 */
		IGsolver<T>& operator=(const IGsolver<T>& rhs);

		/*! \brief operator ()
		 *
		 * Description: Steps the simulation forward by one time step.
		 * \param control_signal is the signal passed by the PID class to 
		 * be used in the ODE calculations.
		 * \post The simulation is stepped forward by one time step and 
		 * m_GXI stores the new values of the simulation.
		 */		
		void operator()(float control_signal);
		
		/*! \brief Glucose accessor 
		 *
		 * Description: Allows the user to access the current value of the 
		 * glucose stored in the system.
		 * \return Returns the amount of glucose in the system.
		 */
		T getGlucose();
		
		/*! \brief print
		 *
		 * Description: Allows the user to print the state of the simulation
		 * in the proper format.
		 * \post The correct data is output to the user.
		 */
		void print();
		
		/*! \brief step overload
		 *
		 * Description: Allows the step size to be overloaded with a new value.
		 * \param new_step is the new step size to be stored in the IGsolver
		 * object.
		 * \post The step size stored in the IGsolver object is overwritten.
		 * This also overwrites the step size in each of the member Heun 
		 * objects.
		 * \throw Throws a std::domain_error object if new_step <= 0.
		 */
		void set_step(const float new_step);
};

#include "IGsolver.hpp"
#endif
		
	