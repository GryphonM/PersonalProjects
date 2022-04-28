//---------------------------------------------------------------------------
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//---------------------------------------------------------------------------

namespace CS170
{
    template <typename T> T* copy(const T* startFirst, const T* end, T* startSecond);
    template <typename T> int count(const T* start, const T* end, const T& item);
    template <typename T> void display(const T* start, const T* end);
    template <typename T1, typename T2> bool equal(const T1* startFirst, const T1* end, const T2* startSecond);
    template <typename T> void fill(T* start, T* end, T value);
    template <typename T1, typename T2> T1* find(T1* start, T1* end, const T2& item);
    template <typename T> T* max_element(T* start, T* end);
    template <typename T> T* min_element(T* start, T* end);
    template <typename T> T* remove(T* start, T* end, const T& item);
    template <typename T> void replace(T* start, T* end, T oldVal, T newVal);
    template <typename T> T sum(const T* start, const T* end);
    template <typename T> void swap(T &left, T &right);
    template <typename T> void swap_ranges(T* startFirst, T* end, T* startSecond);
  
  /* 
   *  Other template function declarations for count, remove, replace, etc.
   *  go here. Make sure all of your declarations are sorted in alphabetical
   *  order. This includes putting the swap function above in the proper
   *  position.
   *
   */ 
   
   
}

#include "Functions.cpp"

#endif
//---------------------------------------------------------------------------
