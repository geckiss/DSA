#pragma once

template<typename T>
class Comparator {
public:

	virtual bool compare(T item1, T item2) = 0;
};
