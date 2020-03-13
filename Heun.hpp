// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 4 - Implicit Solvers, p-norms, and 
//					Insulin/Glucose Dynamics
// Filename   : Heun.hpp

using namespace std;

template <typename T>
Heun<T>::Heun(T& i_state, double s_size, const std::function<T(T)>& callback_ode)
{
	if(s_size <= 0) throw(std::domain_error(to_string(s_size)));
	
	m_state = i_state;
	m_step_size = s_size;
	m_ODE = callback_ode;
}

template<typename T>
Heun<T>::Heun(const Heun<T>& rhs)
{
	m_state = rhs.m_state;
	m_predictor = rhs.m_predictor;
	m_step_size = rhs.m_step_size;
	m_ODE = rhs.m_ODE;
}

template <typename T>
Heun<T>& Heun<T>::operator=(const Heun<T>& rhs)
{
	m_state = rhs.m_state;
	m_predictor = rhs.m_predictor;
	m_step_size = rhs.m_step_size;
	m_ODE = rhs.m_ODE;
	return *this;
}

template <typename T>
T Heun<T>::operator()()
{
	m_predictor = m_state + m_step_size * m_ODE(m_state);
	m_state = m_state + (m_step_size/2) * (m_ODE(m_state) + m_ODE(m_predictor));
	return m_state;
}

template <typename T>
void Heun<T>::set_step(const double new_step)
{
	if(new_step <= 0) throw(std::domain_error(to_string(new_step)));
	m_step_size = new_step;
	return;
}