#include <iostream> // cout, endl

namespace CS170
{
	// Copies the values of the first range to the second range
	//	Params:
	//		startFirst: the start of the first range
	//		end: the end of the first range
	//		startSecond: the start of the second range
	//	Returns:
	//		A pointer to the end of the second range after copying
	template <typename T> 
	T* copy(const T* startFirst, const T* end, T* startSecond)
	{
		const T* placeFirst = startFirst;
		T* placeSecond = startSecond;
		for (; placeFirst != end; placeFirst++, placeSecond++)
			*placeSecond = *placeFirst;

		return placeSecond;
	}

	// Counts how many time a given item appears.
	//	Params:
	//		start: pointer to the first object in the range
	//		end: pointer to the object after the last object to display
	//		item: what to look for
	//	Returns:
	//		the number of times the value was found
	template <typename T> 
	int count(const T* start, const T* end, const T& item)
	{
		int count = 0;
		for (const T* place = start; place != end; place++)
		{
			if (*place == item)
				count++;
		}
		return count;
	}

	// Displays the values from the starting point to the end point
	//	Params:
	//		start: pointer to the first object to display
	//		end: pointer to the object after the last object to display
	template <typename T> 
	void display(const T* start, const T* end)
	{
		for (const T* place = start; place != end; place++)
		{
			std::cout << *place;
			if (place + 1 != end)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}

	// Compares the values of two ranges
	//	Params:
	//		startFirst: pointer to the first object in the first range
	//		end: pointer to the object after the last object in the first range
	//		startSecond: pointer to the first object in the second range
	//	Returns:
	//		true if the values of the ranges are equal, false if any of the values are different
	template <typename T1, typename T2> 
	bool equal(const T1* startFirst, const T1* end, const T2* startSecond)
	{
		const T1* placeFirst = startFirst;
		const T2* placeSecond = startSecond;
		for (; placeFirst != end; placeFirst++, placeSecond++)
		{
			if (*placeFirst != *placeSecond)
				return false;
		}
		return true;
	}

	// Fills a range with the given values
	//	Params:
	//		start: pointer to the first object in the range
	//		end: pointer to the object after the last object in the range
	//		value: the value to set the range to
	template <typename T> 
	void fill(T* start, T* end, T value)
	{
		for (T* place = start; place != end; place++)
			*place = value;
	}

	// Returns the first occurence of the given item in a given range
	//	Params:
	//		start: pointer to the first object in the range
	//		end: pointer to the object after the last object of the range
	//		item: the item to look for
	//	Returns:
	//		Pointer to the location of the found item
	template <typename T1, typename T2> 
	T1* find(T1* start, T1* end, const T2& item)
	{
		for (T1* place = start; place != end; place++)
		{
			if (*place == item)
				return place;
		}
		return end;
	}

	// Finds and returns a pointer to the element with the highest value in the range
	//	Params:
	//		start: pointer to the first object in the range
	//		end: pointer to the object after the last object of the range
	//	Returns:
	//		Pointer to the maximum element of the range
	template <typename T>
	T* max_element(T* start, T* end)
	{
		T* minEl = start;
		for (T* place = start; place != end; place++)
		{
			if (*place > *minEl)
				minEl = place;
		}
		return minEl;
	}

	// Finds and returns a pointer to the element with the lowest value in the range
	//	Params:
	//		start: pointer to the first object in the range
	//		end: pointer to the object after the last object of the range
	//	Returns:
	//		Pointer to the minimum element of the range
	template <typename T> 
	T* min_element(T* start, T* end)
	{
		T* minEl = start;
		for (T* place = start; place != end; place++)
		{
			if (*place < *minEl)
				minEl = place;
		}
		return minEl;
	}

	// Find the value and remove all occurances of it
	//	Params:
	//		start: pointer to the first object in the range
	//		end: pointer to the object after the last object in the range
	//		item: the value to be removed
	//	Returns:
	//		pointer to the new end of the array
	template <typename T> T* remove(T* start, T* end, const T& item)
	{
		T* writeIndex = start;
		for (T* readIndex = start; readIndex != end; readIndex++)
		{
			if (*readIndex != item)
			{
				*writeIndex = *readIndex;
				writeIndex++;
			}
		}
		return writeIndex;
	}

	// Finds all occurences old value and replaces it with the new value
	//	Params:
	//		start: pointer to the first object in the range
	//		end: pointer to the object after the last object of the range
	//		oldVal: the value to look for and replace
	//		newVal: the value to replace the oldVal with
	template <typename T> 
	void replace(T* start, T* end, T oldVal, T newVal)
	{
		T* place = find(start, end, oldVal);
		while (place != end)
		{
			*place = newVal;
			place = find(start, end, oldVal);
		}
	}

	template <typename T> T sum(const T* start, const T* end)
	{
		T sum = *start;
		for (const T* place = start + 1; place != end; place++)
			sum += *place;
		return sum;
	}

	/******************************************************************************/
	/*!
	  \brief
		Swaps two objects. There is no return value but the two objects are
		swapped in place.
	  
	  \param left
		The first object to swap.
	  
	  \param right
		The second object to swap.
	*/
	/******************************************************************************/
	template <typename T> 
	void swap(T &left, T &right)
	{
	  T temp(right); // need a temporary copy
	  right = left;
	  left = temp;
	}

	// Swaps the values of two ranges from the start point to the end point
	//	Params:
	//		startFirst: pointer to the first object in the first range
	//		end: pointer to the object after the last object in the first range
	//		startSecond: pointer to the first object in the second range
	template <typename T> 
	void swap_ranges(T* startFirst, T* end, T* startSecond)
	{
		T* placeFirst = startFirst;
		T* placeSecond = startSecond;
		for (; placeFirst != end; placeFirst++, placeSecond++)
			swap(*placeFirst, *placeSecond);
	}
}
