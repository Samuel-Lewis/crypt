//
//  Singleton.hpp
//  Crypt
//
//  Created by Jacob Gonzalez on 6/10/2015.
//  Copyright © 2015 Jacob Gonzalez. All rights reserved.
//

// Generic SingleTon Class

#ifndef Singleton_hpp
#define Singleton_hpp

template <class SingletonClass>
class Singleton
{
public:
    static SingletonClass& getInstance()
    {
        if(_instance == nullptr)
        {
            _instance = new SingletonClass;
        }
        return *_instance;
    }

protected:
    static SingletonClass* _instance;
    Singleton(){}
    Singleton(Singleton const &);
    Singleton& operator = (Singleton const &);
};

template <class T>
T* Singleton<T>::_instance = nullptr;

#endif /* Singleton_hpp */
