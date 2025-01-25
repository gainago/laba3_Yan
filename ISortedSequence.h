#pragma once
//#include <functional>

//template <class T>
//using Comparator = std::function<bool(const T&, const T&)>;

template <class T>
class ISortedSequence
{
public:
	virtual int GetLength() const = 0;

	virtual bool IsEmpty() const = 0;

	virtual T Get(int index) const = 0;

	virtual T GetFirst() const = 0;

	virtual T GetLast() const = 0;

	virtual int IndexOf(T element) const = 0;

	virtual ISortedSequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;

	virtual void Add(T element) = 0;
};