/*! \file
 *
 * Definitions for the PID class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 4 \n
 */
 
#ifndef PID_H
#define PID_H

using namespace std;

//! PID class.
/*!
 * This class acts as a PID controller with an adjustable step size
 * and target set point.
 */
class PID
{
	private:
		float m_step; /*!< A float the stores the step size for the
					   simulation. */
		float desired_value; /*!< A float the stores the target value
							  for the simulation. */
		MyVector<float> m_error; /*!< A MyVector that stores all of the 
								  error values. */
		float m_signal; /*!< A float that stores the signal to be sent
						 out of the controller. */
		
		float present = 0; /*!< A float that stores the first element of
							the signal function. */
		float past = 0; /*!< A float that stores the second element of the 
						 signal function. */
		float future = 0; /*!< A float that stores the third element of the 
						   signal function. */
						   
		MyVector<float> m_kstore; /*!< A MyVector that stores the k values for
								   the signal calculation. */

	public:
	
		/*! \brief constructor
		 *
		 * Description: Constructor for the PID class that takes and
		 * initializes the step size, target value, the error storage
		 * MyVector, and the signal to be sent out.
		 * \param step is the step size to be used by the PID object.
		 * \param d_value is the target value for the error to be 
		 * calculated with.
		 * \post Initializes a PID object with the desired values.
		 * \throw Throws a std::domain_error object if step <= 0.
		 */
		PID(const float step, const float d_value);
		
		/*! \brief constructor
		 *
		 * Description: Default constructor for the PID class that 
		 * initializes the step size, target value, the error storage
		 * MyVector, and the signal to be sent out.
		 * \post Initializes a PID object with the default values.
		 */
		PID(): m_step(.15), desired_value(0), m_error(MyVector<float>(0)),
			m_signal(0), m_kstore(MyVector<float>(3)) {}
			
		/*! \brief copy constructor
		 *
		 * Description: Copy constructor for the PID class. Sets the calling
		 * object equal to the object passed.
		 * \param rhs is the PID to be copied.
		 * \post Initializes a PID object with the same values as the 
		 * object passed.
		 */	
		PID(const PID& rhs);
		
		/*! \brief operator =
		 *
		 * Description: Copy assignment operator for the PID class.
		 * \param rhs is the object to set the calling object equal to.
		 * \post sets the values of the calling object equal to the values
		 * of the parameter.
		 */
		PID& operator=(const PID& rhs);
		
		/*! \brief operator ()
		 *
		 * Description: Calculates the signal to be sent out based on the
		 * current value that is passed to the object.
		 * \param curr_value is the current value of the system that the PID
		 * compares the target value against to calculate the error.
		 * \return Returns the signal that is calculated.
		 */
		float operator()(const float curr_value);
		
		/*! \brief operator []
		 *
		 * Description: Allows the user to access the k-values and change
		 * them.
		 * \param access is the space in the m_kstore MyVector to be accessed.
		 * [0] for Kp, [1] for Ki, and [2] for Kd.
		 * \return Returns a reference to the spot in the array.
		 */
		float& operator[](const int access);
		
		/*! \brief Target reset function
		 *
		 * Description: Sets a new target for the controller to output a signal
		 * to work towards.
		 * \param new_d is the new target.
		 * \post Sets the desired_value equal to new_d.
		 */
		void reset(const float new_d);
		
		/*! \brief step overload
		 *
		 * Description: Allows the step size to be overloaded with a new value.
		 * \param new_step is the new step size to be stored in the PID
		 * object.
		 * \post The step size stored in the PID object is overwritten.
		 * \throw Throws a std::domain_error object if new_step <= 0.
		 */
		void set_step(const float new_step);
};

#endif