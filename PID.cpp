// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 4 - Implicit Solvers, p-norms, and 
//					Insulin/Glucose Dynamics
// Filename   : PID.cpp

#include "MyVector.h"
#include "PID.h"

using namespace std;

PID::PID(const float step, const float d_value)
{
	if(step <= 0) throw(std::domain_error(to_string(step)));
	
	m_step = step; 
	desired_value = d_value;
	m_error = MyVector<float>(0); 
	m_signal = 0;
	m_kstore = MyVector<float>(3);
	m_kstore[0] = 10;
	m_kstore[1] = .1;
	m_kstore[2] = .1;
}

PID::PID(const PID& rhs)
{
	m_step = rhs.m_step;
	desired_value = rhs.desired_value;
	m_error = rhs.m_error;
	m_signal = rhs.m_signal;
	m_kstore = rhs.m_kstore;
}
	
PID& PID::operator=(const PID& rhs)
{
	m_step = rhs.m_step;
	desired_value = rhs.desired_value;
	m_error = rhs.m_error;
	m_signal = rhs.m_signal;
	m_kstore = rhs.m_kstore;
	return *this;
}
	

float PID::operator()(const float curr_value)
{
	m_error.push_back(((curr_value - desired_value)/desired_value * 100));
	present = m_error[m_error.size() -1];
	if(m_error.size() > 1)
	{
		past += ((m_error[m_error.size() - 1] - (m_error[m_error.size() - 2])) / 2)  * m_step;
		future = ((m_error[m_error.size() - 1] - m_error[m_error.size() - 2]) / m_step);
	}
	m_signal = (m_kstore[0] * present) + (m_kstore[1] * past) + (m_kstore[2] * future);

	return m_signal;
}

float& PID::operator[](const int access)
{
	return m_kstore[access];
}

void PID::reset(const float new_d)
{
	desired_value = new_d;
	return;
}

void PID::set_step(const float new_step)
{
	m_step = new_step;
	return;
}