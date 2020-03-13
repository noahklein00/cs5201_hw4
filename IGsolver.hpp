// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 4 - Implicit Solvers, p-norms, and 
//					Insulin/Glucose Dynamics
// Filename   : IGsolver.hpp

using namespace std;

template <typename T>
IGsolver<T>::IGsolver(const float h, const MyVector<T>& initial)
{
	if(h <= 0) throw(std::domain_error(to_string(h)));
	m_step = h;
	m_GXI = initial;
	m_new_state = MyVector<T>(3);
	
	m_glucose = Heun<T>(m_GXI[0], m_step, [&] (const T & G) 
			{return -(.05 + m_GXI[1]) * G + .05 * 300 + 
			-maxFunc(0.0,m_control_signal);});  
	m_helper = Heun<T>(m_GXI[1], m_step, [&] (const T & X) 
			{return -(.5 * X) + .0001 * (m_GXI[2] - 40);});
	m_insulin = Heun<T>(m_GXI[2], m_step, [&] (const T & I) 
			{return .00001 * maxFunc(0.0, (m_GXI[0] - 150)) - 
			.05 * (I - 40) + maxFunc2(0.0,m_control_signal);});
}

template <typename T>
IGsolver<T>::IGsolver(const IGsolver<T>& rhs)
{
	m_step = rhs.m_step;
	m_GXI = rhs.m_GXI;
	m_new_state = rhs.m_new_state;
	
	m_glucose = Heun<T>(m_GXI[0], m_step, [&] (const T & G) 
			{return -(.05 + m_GXI[1]) * G + .05 * 300 + 
			-maxFunc(0.0,m_control_signal);});  
	m_helper = Heun<T>(m_GXI[1], m_step, [&] (const T & X) 
			{return -(.5 * X) + .0001 * (m_GXI[2] - 40);});
	m_insulin = Heun<T>(m_GXI[2], m_step, [&] (const T & I) 
			{return .00001 * maxFunc(0.0, (m_GXI[0] - 150)) - 
			.05 * (I - 40) + maxFunc2(0.0,m_control_signal);});
}
	
template <typename T>
IGsolver<T>& IGsolver<T>::operator=(const IGsolver<T>& rhs)
{
	m_step = rhs.m_step;
	m_GXI = rhs.m_GXI;
	m_new_state = rhs.m_new_state;
	
	m_glucose = Heun<T>(m_GXI[0], m_step, [&] (const T & G) 
			{return -(.05 + m_GXI[1]) * G + .05 * 300 + 
			-maxFunc(0.0,m_control_signal);});  
	m_helper = Heun<T>(m_GXI[1], m_step, [&] (const T & X) 
			{return -(.5 * X) + .0001 * (m_GXI[2] - 40);});
	m_insulin = Heun<T>(m_GXI[2], m_step, [&] (const T & I) 
			{return .00001 * maxFunc(0.0, (m_GXI[0] - 150)) - 
			.05 * (I - 40) + maxFunc2(0.0,m_control_signal);});
	return *this;
}

template <typename T>
void IGsolver<T>::operator()(const float control_signal)
{
	m_control_signal = control_signal;
	//advances each object by one time step and stores it 
	//in another vector so it doesn't overwrite the data
	//that the other functions need.
	
	m_new_state[0] = m_glucose();
	m_new_state[1] = m_helper();
	m_new_state[2] = m_insulin();
	
	m_GXI = m_new_state;
	return;
}

template <typename T>
T IGsolver<T>::getGlucose()
{
	return m_GXI[0];
}

template <typename T>
void IGsolver<T>::print()
{
	cout << "Glucose: " << m_GXI[0] << ", Insulin: " << m_GXI[2] << endl;
	return;
}

template <typename T>
void IGsolver<T>::set_step(const float new_step)
{
	m_step = new_step;
	m_glucose.set_step(new_step);
	m_helper.set_step(new_step);
	m_insulin.set_step(new_step);
	return;
}