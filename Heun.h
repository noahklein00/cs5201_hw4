/*! \file
 *
 * Definitions for the Heun class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 4 \n
 */

#ifndef HEUN_H
#define HEUN_H

using namespace std;

//! Heun class.
/*!
 * This class uses std::function to simulate the Heun
 * methed of solving ODEs.
 */
template <typename T>
class Heun
{
	private:
		T m_state; /*!< A T object that is used to store the current state of
				   the ODE system. */
		T m_predictor; /*!< A T object used to store the predictor step used
						in Heun's method. */
		double m_step_size; /*!< A double used to represent the step size of 
							 the iterator method. */
		std::function<T (T)> m_ODE; /*!< A std::function that takes a type T&
									 and returns a type T. This is used to 
									 hold the ODE. */
		
	public:
	
		/*! \brief constructor
		 *
		 * Description: A parameterized constructor for a Heun object.
		 * \param i_state is the initial state of the ODE system.
		 * \param s_size is the step size used in the Heun method.
		 * \param callback_ode is the ODE that the Heun method will be 
		 * evaluated on.
		 * \post A new Heun object is initialized with the values passed.
		 * \throw Throws a std::domain_error object if the step size <= 0.
		 */
		Heun(T& i_state, double s_size, 
			const std::function<T(T)>& callback_ode);
		
		/*! \brief constructor
		 *
		 * Description: Constructs a barebones Heun object that can't really
		 * be used for anything except to be initialized.
		 * \post A Heun object is initialized with only a default step size.
		 */
		Heun(): m_step_size(.15) {}
		
		/*! \brief copy constructor
		 *
		 * Description: Initializes a new Heun object with the same parameters
		 * as the one passed.
		 * \param rhs is an already initialized Heun object to be copied.
		 * \pre = operator needs to be defined for type T.
		 * \post Creates a new Heun object initialized with the values of
		 * the object passed.
		 */
		Heun(const Heun<T>& rhs);
		
		/*! \brief operator =
		 *
		 * Description: Operator = overload for the Heun object that sets the
		 * calling object equal to the parameter.
		 * \param rhs is an already initialized Heun object to be copied.
		 * \return Returns *this with data identical to the parameter.
		 * \pre = operator needs to be defined for type T.
		 * \post Creates a new Heun object initialized with the values of
		 * the object passed.
		 */
		Heun<T>& operator=(const Heun<T>& rhs);
		
		/*! \brief step overload
		 *
		 * Description: Allows the step size to be overloaded with a new value.
		 * \param new_step is the new step size to be stored in the Heun
		 * object.
		 * \post The step size stored in the Heun object is overwritten.
		 * \throw Throws a std::domain_error object if new_step <= 0.
		 */
		void set_step(const double new_step);
		
		/*! \brief operator ()
		 *
		 * Description: Steps the Heun object forward by one time step.
		 * \return Returns the new state calculated by the Heun method.
		 * \pre = operator needs to be defined for type T.
		 * \post The next step is calculated by the Heun method.
		 */
		T operator()();
};


#include "Heun.hpp"
#endif