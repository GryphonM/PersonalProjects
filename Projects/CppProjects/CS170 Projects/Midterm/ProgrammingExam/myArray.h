#pragma once
#include <iostream>

class myArray
{
public:
    myArray(void);
    myArray(const myArray& other);
    ~myArray(void);

    int get_capacity(void) const;
    int get_size(void) const;
    void push(int value_);
    void pop();
    myArray& operator=(const myArray& other);
    myArray& operator+(const myArray& other) const;

    friend std::ostream& operator<<(std::ostream& os, const myArray& a_);

private:
    int *numbers;
    int size;
    int capacity;
};
