#ifndef GENERIC_H
#define GENERIC_H

#include <iostream>

// Generic Base Class
// Must be a pointer for poly to work properly
// Generic does not actually store the value
// this is to avoid that template recursion thing for anytype containers
class Generic
{
public:
    // Type of Generic
    enum Type
    {
        kNumber,
        kString,
        kArray,
        kDict
    };

    // Contructor with type
    Generic(Type _type) : type(_type), good(true)
    {}
    virtual ~Generic()
    {}

    // Type to be set on inheritance
    const Type type;

    // good determines if the stream read the data with no errors
    bool good;

    // make a Generic of type T with value U
    template <typename T, typename U>
    static T *make(U value)
    {
        return new T(value);
    }

    // make a Generic of type T with default
    template <typename T>
    static T *make()
    {
        return new T();
    }

    // free memory
    void free();

    // returns the casted generic to type T
    template <typename T>
    T *as()
    {
        return dynamic_cast<T *>(this);
    }

    bool is(Type t);

    // gets the value of generic T to type U
    template <typename U, typename T>
    static U getValue(T *obj)
    {
        return obj->value;
    }

    // overload to do printing to a stream
    virtual std::ostream& print(std::ostream& os) = 0;
    // overload to do reading from a stream
    virtual std::istream& read(std::istream& is) = 0;

    // << overload
    template <typename T>
    friend std::ostream& operator<<(std::ostream& os, T *obj)
    {
        return obj->print(os);
    }

    // << overload
    template <typename T>
    friend std::istream& operator>>(std::istream& is, T *obj)
    {
        return obj->read(is);
    }
};

#endif // GENERIC_H
