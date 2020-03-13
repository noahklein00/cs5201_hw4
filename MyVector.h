/*! \file
 *
 * Definitions for the MyVector class. \n
 * Programmer: Noah Klein \n
 * Class: CS5201 \n
 * Assignment: Homework 4 \n
 */

#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <iterator>
#include <functional>
#include <cmath>

using namespace std;

//! MyVector class.
/*!
 * This class uses std::arrays to create a vector and 
 * dynamically allocate memory.
 */
template <typename T>
class MyVector
{
	private:
		T* m_arr; /*!< A std::array* that is used to simulate a dynamic array
				   */
		int m_size; /*!< Integer used to display the current number of 
					 * occupied elements in the array. 
					 */
		int m_available; /*!< Integer used to display the current maximum
						  * number of elements the array can store 
						  */
		
	public:
		// The Big 3 //
		
		/*! \brief Default constructor.
		 *	
		 * Description: Creates an empty vector of type T, sets m_size to 0 and
		 * m_available to 10.
		 * \post A MyVector object is created with nothing stored and a maximum
		 * of 10 spaces available.
		 */
		MyVector();
		
		/*! \brief Constructor.
		 *
		 * Description: Takes an integer size and initializes a MyVector with
		 * that size available. It initializes the space but fills it with
		 * nothing.
		 * \param size is the integer size of the vector to be created.
		 * \pre The array allocated is filled with zeroes.
		 * \post A MyVector object is created with zeroes stored and (size)
		 * elements available.
		 * \throw throws a std::length_error object if the size is negative.
		 */
		MyVector(const int size);
		
		/*! \brief constructor
		 *
		 * Description: Constructs a MyVector object based off of the 
		 * std::initializer_list passed to it.
		 * \param list is a std::initializer_list that stores the elements
		 * to be stored in the MyVector.
		 * \post A MyVector object is created with the data and size equal
		 * to the data and size of the std::initializer_list. 
		 */
		MyVector(const std::initializer_list<T> & list);
		
		/*! \brief copy constructor
		 *
		 * Description: Constructs a MyVector object with all member
		 * variables set equal to the MyVector passed.
		 * \param cpy_vec is a MyVector that has already been 
		 * initialized with data.
		 * \post The newly initialized MyVector is created and has all
		 * data set equal to the cpy_vec passed. 
		 */
		MyVector(const MyVector<T> & cpy_vec);
		
		/*! \brief = operator
		 *
		 * Description: Sets the calling object equal to the parameter.
		 * \param cpy_vec is a MyVector that has already been initialized
		 * with data.
		 * \return returns a MyVector through *this.
		 * \pre operator = needs to be defined for type T.
		 * \post The calling object is set equal to the parameter. 
		 */
		MyVector<T>& operator=(const MyVector<T> & cpy_vec);
		
		/*! \brief destructor
		 *
		 * Description: Properly deallocates memory for the MyVector class.
		 * \post The calling object has its memory properly deallocated. 
		 */
		~MyVector();
		
		// Mutators //
		
		/*! \brief Adds an element to the back of the vector
		 *
		 * Description: Adds the parameter passed to the "back" of the 
		 * calling MyVector object. This also increments the size and/or
		 * resizes the vector properly.
		 * \param item is the object to be added to the back of the vector.
		 * \post item is now stored at the "back" of the vector and 
		 * the appropriate m_size and m_available are set. 
		 */
		void push_back(const T & item);
		
		/*! \brief Sets a new size for the vector
		 *
		 * Description: Allows the user to override the data stored
		 * in the vector to set their own size.
		 * \param new_size should be an integer of 0 or greater.
		 * \post The calling object is resized appropriately and 
		 * any data that was trashed is deallocated.
		 * \throws Throws a std::domain_error object if new_size
		 * is negative. 
		 */
		void resize(const int new_size);
		
		/*! \brief Sets a new size for the vector and fills it
		 *
		 * Description: Allows the user to override the data stored
		 * in the vector to set their own size and fills any new 
		 * containers created with the "filler" parameter.
		 * \param new_size should be an integer of 0 or greater.
		 * \param filler can be any object of type T to fill the vector.
		 * \post The calling object is resized appropriately,
		 * any data that was trashed is deallocated and any new 
		 * containers are filled with the "filler" object.
		 * \throws Throws a std::domain_error object if new_size
		 * is negative. 
		 */
		void resize(const int new_size, const T& filler);
		
		/*! \brief clears the object
		 *
		 * Description: wipes the objects, sets m_size and m_available
		 * to 0 and makes m_arr NULL.
		 * \post All data stored in the vector is deleted and all
		 * variables are set to a base state of 0/NULL. 
		 */
		void clear();
		
		/*! \brief [] operator reference
		 *
		 * Description: Allows the user to access an index in the array.
		 * \param index is the space in the vector to be accessed.
		 * \return Returns the value at the index in the vector.
		 * \pre 0 <= index < m_size
		 * \throws Throws a std::domain_error object is the index is
		 * out of bounds. 
		 */
		T& operator[](const int index);
		
		/*! \brief - operator (binary)
		 *
		 * Description: Used to subtract one vector from another. Allows
		 * for vectors of different (or similar) sizes to be added through
		 * vector subtraction.
		 * \param rhs is the vector to be subtracted from the calling 
		 * object.
		 * \return Returns a newly created vector where each container now
		 * holds the difference of the two vectors passed at that index.
		 * \pre -= operator needs to be defined for type T.
		 * \post Creates a new vector that gets returned. 
		 */
		MyVector<T> operator-(const MyVector<T> & rhs);
		
		/*! \brief unary minus
		 *
		 * Description: Negates a calling vector.
		 * \return Returns a newly created vector that is equal to 
		 * the negative of the calling object.
		 * \pre *= operator needs to be defined for type T.
		 * \post Creates a new vector that gets returned. 
		 */
		MyVector<T> operator-();
		
		/*! \brief apply function
		 *
		 * Description: Allows the user to pass a function that
		 * takes a type T and returns a type T. apply applies the 
		 * function to each container.
		 * \param func is a function that takes a type T and returns
		 * a type T.
		 * \return Returns a new vector based off of the calling object
		 * with func applied to each container.
		 * \post Creates a new vector that gets returned. 
		 */
		MyVector<T> apply(T func (T)) const;
		
		// Accessors //
		
		/*! \brief get function
		 *
		 * Description: Returns a reference to the data stored in the container
		 * at position index in the array.
		 * \param index is the index in the vector to be accessed.
		 * \return Returns a reference to the element at the index in the
		 * vector.
		 * \pre 0 <= index < m_size
		 * \throws Throws a std::domain_error object if index is out of bounds.
		 */
		T& get(const int index);
		
		/*! \brief size of the vector
		 *
		 * Description: Returns the number of elements in the vector.
		 * \return Returns an int equal to the size of the vector. 
		 */
		int size() const;
		
		/*! \brief [] operator const
		 *
		 * Description: Allows for safe accessing of the data at the
		 * certain index in the vector.
		 * \param index is the index in the vector to be accessed.
		 * \return Returns a const reference to the data stored at that index.
		 * \pre 0 <= index < m_size
		 * \throws Throws a std::domain_error if index is out of bounds. 
		 */
		const T& operator[](const int index) const;
		
		/*! \brief Vector multiplication
		 *
		 * Description: Calculates the dot product of the parameter and 
		 * calling object vectors and returns the scalar.
		 * \param rhs is the vector to be dotted with the calling object.
		 * \return Returns a scalar representing the dot product of the 
		 * vectors.
		 * \pre * and += operators need to be defined for type T. 
		 */
		T operator*(const MyVector<T> & rhs) const;
		
		/*! \brief P-norm calculator
		 *
		 * Description: Calculates the p-norm for a given MyVector object
		 * \param norm is the p value for the p-norm.
		 * \return Returns the p-norm that was calculated for the vector as
		 * a double object.
		 * \pre operator += needs to be defined for type T.
		 */
		double operator^(const int norm) const;
		
		
		// Friend //
		
		/*! \brief + operator
		 *
		 * Description: Used to add two vectors together. Allows for vectors
		 * of different (or similar) sizes to be added through vector addition.
		 * \param lhs is the MyVector to be added to.
		 * \param rhs is the MyVector to be added to the calling object.
		 * \return Returns a newly created vector where each container now
		 * holds the sum of the two vectors passed at that index.
		 * \pre += operator needs to be defined for type T.
		 * \post Creates a new vector that gets returned. 
		 */
		template <typename U>
		friend MyVector<U> operator+(const MyVector<U> & lhs, const MyVector<U> & rhs);
		
		/*! \brief Scalar multiplication
		 *
		 * Description: Allows for scalar multiplication of a calling vector.
		 * \param lhs is the MyVector that the scalar will be multiplied on.
		 * \param rhs is a scalar of type T to be multiplied through the
		 * vector.
		 * \return Returns a newly created vector where the data in each 
		 * container has been multiplied by the scalar.
		 * \pre *= operator needs to be defined for type T.
		 * \post Creates a new vector that gets returned. 
		 */
		template <typename U>
		friend MyVector<U> operator*(const MyVector<U> & lhs, const U & rhs);
		
		/*! \brief Scalar multiplication
		 *
		 * Description: Allows for scalar multiplication of a calling vector.
		 * \param lhs is a scalar of type T to be multiplied through the
		 * vector.
		 * \param rhs is the MyVector that the scalar will be multiplied on.
		 * \return Returns a newly created vector where the data in each 
		 * container has been multiplied by the scalar.
		 * \pre *= operator needs to be defined for type T.
		 * \post Creates a new vector that gets returned. 
		 */
		template <typename U>
		friend MyVector<U> operator*(const U & lhs, const MyVector<U> & rhs);
		
		/*! \brief << operator
		 *
		 * Description: Allows for proper outputting of MyVector objects.
		 * \param out is the ostream passed.
		 * \param rhs is the MyVector to be output.
		 * \return Returns the ostream
		 * \pre << operator must be defined for type T.
		 * \post Outputs the object to the stream. 
		 */
		template <typename U>
		friend ostream& operator << (ostream& out, const MyVector<U>& rhs);
		
		/*! \brief >> operator
		 *
		 * Description: Allows the user to insert any amount of data into 
		 * a MyVector object.
		 * \param in is the istream passed.
		 * \param rhs is the MyVector to store input.
		 * \return Returns the istream.
		 * \post Inputted data is stored in the rhs MyVector. 
		 */
		template <typename U>
		friend istream& operator >> (istream & in, const MyVector<U>& rhs);
	
	//! iterator class.
	/*!
	 * This class allows for iterating over the MyVector
	 * object containers.
	 */
	class iterator
    {
	
		private:
			MyVector<T>* m_array; /*!< a MyVector<T> pointer that allows for
				* iterating over the containers. 
				*/
			unsigned int m_idx; /*!< Integer used to display the current 
				* index of the pointer.
				*/
			
		public:
		
			/*! \brief constructor
			 *
			 * Description: Constructs an iterator over a certain MyVector 
			 * object starting at a specified integer.
			 * \param a is the pointer to a MyVector to be copied.
			 * \param idx is the index position of the pointer.
			 * \post Creates a new iterator object with the specified data. 
			 */
			iterator(MyVector<T>* a, unsigned int idx): 
				m_array(a), m_idx(idx) {}
			
			/*! \brief * operator
			 *
			 * Description: Accesses the data at the position the pointer 
			 * is pointing to.
			 * \return Returns a reference to the data in the object pointed
			 * to by m_array at the index m_idx. 
			 */
			T& operator*() { return (*m_array)[m_idx]; }

			/*! \brief -> operator
			 *
			 * Description: Allows the user to use -> syntax instead of 
			 * the * operator.
			 * \return Returns a reference to the data in the object pointed
			 * to by m_array at the index m_idx.
			 */
			T& operator->() { return (*m_array)[m_idx]; }

			/*! \brief operator ++ (postfix)
			 *
			 * Description: Increments the index in stored in the iterator.
			 * \return Returns the calling object with an incremented iterator.
			 */
			iterator& operator++()
			{
			  m_idx++;
			  return *this;
			}

			/*! \brief operator ++ (prefix)
			 *
			 * Description: Increments the index in stored in the iterator.
			 * \return Returns a new iterator object with an incremented
			 * iterator.
			 */
			iterator operator++(int)
			{
			  iterator temp = *this;
			  m_idx++;
			  return temp;
			}

			/*! \brief += operator
			 *
			 * Description: Allows for jumping the iterator's index by a 
			 * specified amount.
			 * \param inc only allows for forward iterating.
			 * \return Returns the calling object with an adjusted iterator.
			 */
			iterator& operator+=(const unsigned int inc)
			{
			  m_idx += inc;
			  return *this;
			}

			/*! \brief operator -- (postfix)
			 *
			 * Description: Decrements the index stored in the iterator.
			 * \return Returns the calling object with a decremented index.
			 */
			iterator& operator--()
			{
			  m_idx--;
			  return *this;
			}

			/*! \brief operator -- (prefix)
			 *
			 * Description: Decrements the index stored in the iterator.
			 * \return Returns a new iterator object with a decremented 
			 * iterator.
			 */
			iterator operator--(int)
			{
			  iterator temp = *this;
			  m_idx--;
			  return temp;
			}

			/*! \brief -= operator
			 *
			 * Description: Allows for jumping the iterator's index by a 
			 * specified amount.
			 * \param dec only allows for reverse iterating.
			 * \return Returns the calling object with an adjusted index. 
			 */
			iterator& operator-=(const unsigned int dec)
			{
			  m_idx -= dec;
			  return *this;
			}

			/*! \brief == operator
			 *
			 * Description: Allows for logical comparison between two iterator
			 * objects.
			 * \param a is an iterator
			 * \param b is an iterator
			 * \return Returns a bool that reflects the equality of the 
			 * two iterators.
			 */
			friend bool operator==(const iterator& a, const iterator& b)
			{
			  return a.m_array == b.m_array && a.m_idx == b.m_idx;
			}

			/*! \brief !- operator
			*
			* Description: Allows for logical comparison between two iterator
			* objects.
			* \param a is an iterator
			* \param b is an iterator
			* \return Returns a bool that reflects the equality of the 
			* two iterators. 
			*/
			friend bool operator!=(const iterator& a, const iterator& b)
			{
			  return !(a == b);
			}
    };

	/*! \brief starting iterator
	 *
	 * Description: Returns an iterator pointing to the beginning of
	 * the MyVector object's array.
	 * \return Returns a new iterator object that points to the start
	 * of the MyVector array.
	 * \pre The first index in the vector that stores data needs to be
	 * m_arr[0].
	 */
    iterator begin() { return iterator(this, 0); }

	/*! \brief ending iterator
	 *
	 * Description: Returns an iterator pointing to the ending of
	 * the MyVector object's array.
	 * \return Returns a new iterator object that points to the end
	 * of the MyVector array.
	 */
    iterator end() { return iterator(this, m_size); }
};

/*! \brief + operator
 *
 * Description: Used to add two vectors together. Allows for vectors
 * of different (or similar) sizes to be added through vector addition.
 * \param lhs is the MyVector to be added to.
 * \param rhs is the MyVector to be added to the calling object.
 * \return Returns a newly created vector where each container now
 * holds the sum of the two vectors passed at that index.
 * \pre += operator needs to be defined for type T.
 * \post Creates a new vector that gets returned. 
 */
template <typename T>
MyVector<T> operator+(const MyVector<T> & lhs, const MyVector<T> & rhs);

/*! \brief Scalar multiplication
 *
 * Description: Allows for scalar multiplication of a calling vector.
 * \param lhs is the MyVector that the scalar will be multiplied through.
 * \param rhs is a scalar of type T to be multiplied through the
 * vector.
 * \return Returns a newly created vector where the data in each 
 * container has been multiplied by the scalar.
 * \pre *= operator needs to be defined for type T.
 * \post Creates a new vector that gets returned. 
 */
template <typename T>
MyVector<T> operator*(const MyVector<T> & lhs, const T & rhs);

/*! \brief Scalar multiplication
 *
 * Description: Allows for scalar multiplication of a calling vector.
 * \param lhs is a MyVector that the scalar will be muliplied through.
 * \param rhs is a scalar of type T to be multiplied through the
 * vector.
 * \return Returns a newly created vector where the data in each 
 * container has been multiplied by the scalar.
 * \pre *= operator needs to be defined for type T.
 * \post Creates a new vector that gets returned. 
 */
template <typename T>
MyVector<T> operator*(const T & lhs, const MyVector<T> & rhs);

/*! \brief << operator
 *
 * Description: Allows for proper outputting of MyVector objects.
 * \param out is the ostream passed.
 * \param rhs is the MyVector to be output.
 * \return Returns the ostream
 * \pre << operator must be defined for type T.
 * \post Outputs the object to the stream. 
 */
template <typename T>
std::ostream & operator << (ostream & out, const MyVector<T> & rhs);

/*! \brief >> operator
 *
 * Description: Allows the user to insert any amount of data into 
 * a MyVector object.
 * \param in is the istream passed.
 * \param rhs is the MyVector to store input.
 * \return Returns the istream.
 * \post Inputted data is stored in the rhs MyVector. 
 */
template <typename T>
std::istream & operator >> (istream & in, MyVector<T>& rhs);

#include "MyVector.hpp"
#endif


























