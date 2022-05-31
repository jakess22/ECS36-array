#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <ostream>
#include <iostream>
#include <stdbool.h>

/**
 * Array of a fixed length.
 */
/**
 * std::size_t is a C++ alternative to the size_t type from C.
 * size_t is typically used when referring to anything that is a quantity
 * related to memory, such as the length of an array (which is in memory).
 * It is an unsigned integer type and is typically (but not always) a typedef
 * for something like unsigned or long unsigned.
 * (If you think this is complicated, then you should look up size_type.)
 */
template <typename T, std::size_t Length>
class Array
{
private:
	// TODO: Your member variables and helper methods go here.
	std::size_t array_size;
	T* array_ptr;
	//bool fill_check;
public:
    /**
     * TODO: Provide a static assertion here that will prohibit arrays
     * of length 0.
     */
		 static_assert(Length != 0, "Array size cannot have length 0.");

		Array();
    ~Array();
    Array(const Array& other);
    void operator=(const Array& other);


     // Returns the size of the array.
     //
    std::size_t size() const;


     // Returns the first or last element of the array.
     //
     // Ideally, there would be non-const overloads for these too.
     ///
    const T& front() const;
		T& front_assign() const;
    const T& back() const;
		T& back_assign() const;


     // Returns the element of the array that is at the given index.
     // Throws std::out_of_range if index is out of range.
     //
    T& at(std::size_t index) const; //lets you use = to assign
    const T& const_at(std::size_t index) const; //does not / just returns const value


    // * Equality checking, i.e. checking if two arrays contain the exact
    // * same elements.
     //*/
    bool operator==(const Array& other) const;
  	bool operator!=(const Array& other) const;
};

//Array()
template <typename T, std::size_t Length>
Array<T, Length>::Array() {
	this->array_size = Length;
	this->array_ptr = new T[Length];
}


//~Array()
template <typename T, std::size_t Length>
Array<T, Length>::~Array() {
	this->array_size = 0;
	delete [] array_ptr;
}


//Array(Array& other)
template <typename T, std::size_t Length>
Array<T, Length>::Array(const Array& other) {
	/*this();
	if (this->array_size != other.array_size) {
		std::cerr << "Array sizes must match" << std::endl;
		return;
	}
	*/

	this->array_size = other.size();
	this->array_ptr = new T[Length];

	for (unsigned i = 0; i < other.size(); i++) {
		this->array_ptr[i] = other.array_ptr[i];
	}
}

//operator=
template <typename T, std::size_t Length>
void Array<T, Length>::operator=(const Array& other) {
	static_assert((this->array_size == other.array_size), "Array sizes must match");
	for (unsigned i = 0; i < other.size(); i++) {
		this->array_ptr[i] = other.array_ptr[i];
	}
}

//size()
template <typename T, std::size_t Length>
std::size_t Array<T, Length>::size() const {
	return this->array_size;
}

//at(std::size_t index)
template <typename T, std::size_t Length>
T& Array<T, Length>::at(std::size_t index) const {
	try {
		if ((index < this->array_size) && (index >= 0)) {
			return this->array_ptr[index];
		} else {
			throw std::out_of_range ("Caught expected out_of_range exception.");
		}
	} catch (const std::out_of_range &e) {
		std::cerr << e.what() << std::endl;
		exit(-1);
	}
}

//const at()
template <typename T, std::size_t Length>
const T& Array<T, Length>::const_at(std::size_t index) const {
	try {
		if ((index < this->array_size) && (index >= 0)) {
			return this->array_ptr[index];
		} else {
			throw std::out_of_range ("Caught expected out_of_range exception.");
		}
	} catch (const std::out_of_range &e) {
		std::cerr << e.what() << std::endl;
		exit(-1);
	}
}

//const front()
template <typename T, std::size_t Length>
const T& Array<T, Length>::front() const {
	return this->array_ptr[0];
}

//front_assign()
template <typename T, std::size_t Length>
T& Array<T, Length>::front_assign() const {
	return this->array_ptr[0];
}

//const back()
template <typename T, std::size_t Length>
const T& Array<T, Length>::back() const {
	return this->array_ptr[this->array_size - 1];
}

//back_assign()
template <typename T, std::size_t Length>
T& Array<T, Length>::back_assign() const {
	return this->array_ptr[this->array_size - 1];
}


//operator==
template <typename T, std::size_t Length>
bool Array<T, Length>::operator==(const Array& other) const {
		if (this->array_size != other.size()) {
			return false;
		}
		for (unsigned i = 0; i < this->array_size; i++) {
			if (this->array_ptr[i] != other.at(i)) {
				return false;
			}
		}
		return true;
}

//operator!=
template <typename T, std::size_t Length>
bool Array<T, Length>::operator!=(const Array& other) const {
	return !(this->operator==(other));
}





 // Returns the element of the array that is at the given index.
 // Causes compilation to fail (with a static assertion) if index is out
 // of range.
 //

template <std::size_t Index, typename T, std::size_t Length>
T& get(Array<T, Length>& array) {
	static_assert(((Index >= 0) && (Index < Length)), "Index must be between 0 and array length - 1");
	return array.at(Index);
}



template <std::size_t Index, typename T, std::size_t Length>
const T& get(const Array<T, Length>& array) {
	static_assert(((Index >= 0) && (Index < Length)), "Index must be between 0 and array length - 1");
	return array.at(Index);
}


 // Prints each element of the array.
template <typename T, std::size_t Length>
std::ostream& operator<<(std::ostream& os, const Array<T, Length>& array) {
	for (unsigned i = 0; i < Length; i++) {
		os << array.at(i) << " ";
	}
	os << "\n";
	return os;
}



#endif  // ARRAY_HPP
