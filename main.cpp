// Description: This program demonstrates the use of the move constructor and move assignment operator.
//The class also has a copy constructor and a copy assignment operator,
// which allow instances of the class to be copied. They create a new array of
// integers of the same size as the source object's array, and then copy the
// data from the source object's array to the new array. The move constructor
// and move assignment operator are also implemented to provide efficient transfer
// of resources between objects.

#include <algorithm>
#include <iostream>
#include <vector>

class A {
private:
    size_t mLength;// The length of the resource.
    int *mData;    // The resource.

public:
    // Simple constructor that initializes the resource.
    explicit A(size_t length) : mLength(length), mData(new int[length]) {
        std::cout << " A(size_t). length = " << mLength << "." << std::endl;
    }

    // Destructor,
    ~A() {
        std::cout << " ~A(). length = " << mLength << ".";

        if (mData != NULL) {
            std::cout << " Deleting resource.";
            delete[] mData;// Delete the resource.
        }
        std::cout << std::endl;
    }

    // Copy constructor. const
    A(A& other) : mLength(other.mLength), mData(new int[other.mLength]) {
        std::cout << "A(const A&). length = " << other.mLength << ". Copying resource." << std::endl;
        std::copy(other.mData, other.mData + mLength, mData);
    }

    // Copy assignment operator.
    A &operator=(const A &other) {
        std::cout << "operator=(const A&). length = " << other.mLength << ". Copying resource." << std::endl;

        if (this != &other) {
            delete[] mData;// Free the existing resource.
            mLength = other.mLength;
            mData = new int[mLength];
            std::copy(other.mData, other.mData + mLength, mData);
        }
        return *this;
    }

    // Move constructoor
    A(A &&other) : mData(NULL), mLength(0) {// Initialize via member initializer list to avoid dangling pointer
        std::cout << "A(A&&). length = " << other.mLength << ". Moving resource.\n";

        // Copy the data pointer and its length from the
        // source object.
        mData = other.mData;
        mLength = other.mLength;

        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.mData = NULL;
        other.mLength = 0;
    }

    // Move assignment operator.
    A &operator=(A &&other) {
        std::cout << "operator=(A&&). length = "
                  << other.mLength << "." << std::endl;

        if (this != &other) {
            // Free the existing resource.
            delete[] mData;

            // Copy the data pointer and its length from the
            // source object.
            mData = other.mData;
            mLength = other.mLength;

            // Release the data pointer from the source object so that
            // the destructor does not free the memory multiple times.
            other.mData = NULL;
            other.mLength = 0;
        }
        return *this;
    }

    // Retrieves the length of the data resource.
    size_t Length() const {
        return mLength;
    }
};


int main() {
    // Create a vector object and add a few elements to it.
//    std::vector<A> v;
//    v.push_back(A(25)); // A(size_t). length = 25. that takes rvalue reference && 25
//    v.push_back(A(75)); // A(size_t). length = 75. that takes rvalue reference && 75
//
//    // Insert a new element into the second position of the vector.
//    // add a new element to the vector between the first and second existing elements.
//    v.insert(v.begin() + 1, A(50));

    // Declare a new vector object and an A object with length 25.
    /*aObj is an lvalue because it is a named variable with a storage location.

In the statement A aObj(25), a new A object is created with a length of 25 using the constructor that takes a size_t parameter. The constructor
     initializes the mLength member variable with the given length and allocates a
     new integer array of that length using the new operator. The constructor then initializes the integer array with default values of 0.

                             Since aObj is a named variable, it has a storage location in memory, and we can refer to it by its identifier.
                             We can take its address using the address-of operator &, and we can pass it as an
                             argument to functions or assign it to other variables. All of these operations are characteristic of lvalues.*/
    std::vector<A> v2;
    A aObj(25); // lvalue ?

    // Push the A object into the vector, which invokes the copy constructor to create a copy of the A object.
//    v2.push_back(static_cast<A&&>(aObj)); // A(const A&). length = 25. Copying resource.
    v2.push_back(std::move(aObj));

    return 0;
}