// Programmer : Noah Klein
// Instructor : Price
// Class      : CS5201 Spring 2020
// Assignment : Homework 3 - Euler's Method for ODEs and SIR(D) Model
// Filename   : MyVector.hpp

using namespace std;

//
//----------------- The Big 3 ------------------//
//

template <typename T>
MyVector<T>::MyVector()
{
	m_arr = new T[10]; //default size of 10
	m_size = 0;
	m_available = 10; 
}

/* template <typename T>
MyVector<T>::MyVector(const int size)
{
	m_arr = new T[size];
	m_size = 0;
	m_available = size;
} */

template <typename T>
MyVector<T>::MyVector(const std::initializer_list<T> & list)
{
	m_available = list.size(); 
	m_size = 0;
	m_arr = new T[m_available];
	for(auto itr = list.begin(); itr != list.end(); itr++)
	{
		this -> push_back(*itr);	
	}
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> & cpy_vec)
{
	m_size = 0;
	m_available = cpy_vec.m_available;
	if(m_available > 0)
	{
		m_arr = new T[m_available];
		for(int i = 0; i < cpy_vec.m_size; i++)
		{
			this -> push_back(cpy_vec.m_arr[i]);
		}
	}
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> & cpy_vec)
{
	this -> clear();
	m_available = cpy_vec.m_available;
	if(m_available > 0)
	{
		m_arr = new T[m_available];
		for(int i = 0; i < cpy_vec.m_size; i++)
		{
			this -> push_back(cpy_vec.m_arr[i]);
		}
	}
	return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
	delete[] m_arr;
}

//
//----------------- Mutator ------------------//
//

template <typename T>
void MyVector<T>::push_back(const T & item)
{
	T* temp_arr;
	if(m_available == 0)
	{
		m_arr = new T[1];
		m_arr[0] = item;
		m_size = 1;
		m_available = 1;
	}
	if(m_size >= m_available)
	{
		temp_arr = new T[m_available * 2];
		for(int i = 0; i < m_size; i++)
		{
			temp_arr[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = temp_arr;
		m_available = m_available * 2;
	}	
		
	m_arr[m_size] = item;
	m_size++;
	return;
}

template <typename T>
void MyVector<T>::resize(const int new_size)
{
	T* temp_arr;
	if(new_size < 0) throw(std::domain_error(to_string(new_size)));
	
	if(new_size > m_available)
	{
		temp_arr = new T[new_size];
		for(int i = 0; i < m_size; i++)
		{
			temp_arr[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = temp_arr;
		m_available = new_size;
	}
	else if(new_size < m_available)
	{
		temp_arr = new T[new_size];
		for(int i = 0; i < new_size; i++)
		{
			temp_arr[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = temp_arr;
		m_size = new_size;
		m_available = new_size;
	}
	return;
}
		
template <typename T>		
void MyVector<T>::resize(const int new_size, const T& filler)
{
	T* temp_arr;
	if(new_size < 0) throw(std::domain_error(to_string(new_size)));
	
	if(new_size > m_available)
	{
		temp_arr = new T[new_size];
		for(int i = 0; i < m_size; i++)
		{
			temp_arr[i] = m_arr[i];
		}
		for(int i = m_size; i < new_size; i++)
		{
			temp_arr[i] = filler;
		}
		delete[] m_arr;
		m_arr = temp_arr;
		m_available = new_size;
		m_size = new_size;
	}
	else if(new_size < m_available)
	{
		temp_arr = new T[new_size];
		for(int i = 0; i < new_size; i++)
		{
			temp_arr[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = temp_arr;
		m_size = new_size;
		m_available = new_size;
	}
	return;
}

template <typename T>
void MyVector<T>::clear()
{
	delete[] m_arr;
	m_arr = NULL;
	m_size = 0;
	m_available = 0;
}

template <typename T>
T& MyVector<T>::operator[](const int index)
{
	if(index < 0 || index >= m_size) 
		throw(std::domain_error(to_string(index)));
	return m_arr[index];
}

template <typename T>
MyVector<T> MyVector<T>::operator-(const MyVector<T> & rhs)
{
	MyVector<T> copy;
	if(m_size >= rhs.m_size)
	{
		copy = *this;
		for(int i = 0; i < rhs.m_size; i++)
			copy.m_arr[i] -= rhs.m_arr[i];
	}	
	else
	{
		copy = rhs;
		for(int i = 0; i < rhs.m_size; i++)
		{
			if(i < m_size)
				copy.m_arr[i] = m_arr[i] - rhs.m_arr[i];
			else
				copy.m_arr[i] = -rhs.m_arr[i];
		}
	}
	return copy;
}	

template <typename T>
MyVector<T> MyVector<T>::operator-()
{
	MyVector<T> copy(*this);
	for(int i = 0; i < m_size; i++)
	{
		copy.m_arr[i] *= -1;
	}
	return copy;
}

template <typename T>
MyVector<T> MyVector<T>::apply(T func (T)) const
{
	MyVector<T> new_vec;
	for(int i = 0; i < m_size; i++)
	{
		new_vec.push_back(func(m_arr[i]));
	}
	return new_vec;
}
	
//
//----------------- Accessor ------------------//
//

template <typename T>
T& MyVector<T>::get(const int index)
{
	if(index >= m_size || index < 0) 
		throw(std::domain_error(to_string(index)));
	return m_arr[index];
}

template <typename T>
int MyVector<T>::size() const
{
	return m_size;
}

template <typename T>
const T& MyVector<T>::operator[](const int index) const
{
	if(index < 0 || index >= m_size)
		throw(std::domain_error(to_string(index)));
	return m_arr[index];
}

template <typename T>
T MyVector<T>::operator*(const MyVector<T> & rhs) const
{
	T magnitude = 0;
	if(m_size <= rhs.m_size)
	{
		for(int i = 0; i < m_size; i++)
		{
			magnitude += (m_arr[i] * rhs.m_arr[i]);
		}
	}
	else
	{
		for(int i = 0; i < rhs.m_size; i++)
		{
			magnitude += (m_arr[i] * rhs.m_arr[i]);
		}
	}
	return magnitude;
}

//
//----------------- Friend ------------------//
//

template <typename T>
MyVector<T> operator+(const MyVector<T> & lhs, const MyVector<T> & rhs)
{
	MyVector<T> copy;
	if(lhs.m_size >= rhs.m_size)
	{
		copy = lhs;
		for(int i = 0; i < rhs.m_size; i++)
		{
			copy.m_arr[i] += rhs.m_arr[i];
		}
	}
	else
	{
		copy = rhs;
		for(int i = 0; i < lhs.m_size; i++)
		{
			copy.m_arr[i] += lhs.m_arr[i];
		}
	}
	return copy;
}	

template <typename T>
MyVector<T> operator*(const MyVector<T> & lhs, const T & rhs)
{
	MyVector<T> copy(lhs);
	for(int i = 0; i < copy.m_size; i++)
	{
		copy[i] *= rhs;
	}
	return copy;
}

template <typename T>
MyVector<T> operator*(const T & lhs, const MyVector<T> & rhs)
{
	return rhs * lhs;
}

template <typename T>
std::ostream & operator << (ostream & out, MyVector<T> & rhs)
{	
	for(auto t: rhs)
	{
		out << t << " ";
	}
	return out;
}

template <typename T>
std::istream & operator >> (istream & in, MyVector<T>& rhs)
{
	istream_iterator<T> in_it(in);
	istream_iterator<T> eos;
	
	rhs.clear();
	
	for(;in_it != eos; ++in_it)
	{
		rhs.push_back(*in_it);
	}
	return in;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	