#pragma once
#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class LinkedListSequence : public Sequence <T>
{
private:
	LinkedList<T> items;
public:
	LinkedListSequence() : items{ LinkedList<T>() } {}
	LinkedListSequence(const T* item, int count) : items{ LinkedList<T>(item, count) } {}
	LinkedListSequence(const LinkedList <T>& other) : items{ LinkedList<T>(other) } {}

	T GetFirst() const override
	{
		return this->items.GetFirst();
	}

	T GetLast() const override
	{
		return this->items.GetLast();
	}

	T Get(int index) const override
	{
		return this->items.Get(index);
	}

	int GetLength() const override
	{
		return this->items.GetLength();
	}

	LinkedListSequence<T>* GetSubsequence(int startIndex, int endIndex) const override
	{
		LinkedListSequence<T>* sub_seq = new LinkedListSequence<T>(*this->items.GetSubList(startIndex, endIndex));
		return sub_seq;
	}

	void Append(const T& item)  override
	{
		this->items.Append(item);
	}

	void Prepend(const T& item)  override
	{
		this->items.Prepend(item);
	}

	void InsertAt(const T& item, int index)  override
	{
		this->items.InsertAt(item, index);
	}

	void Set(const T& item, int index)  override
	{
		this->items.Set(item, index);
	}

	void RemoveAt(int index)
	{
		this->items.RemoveAt(index);
	}

	LinkedListSequence<T>* Concat(const Sequence <T>* other) const override
	{
		LinkedList<T> result(this->items);
		for (int i = 0; i < other->GetLength(); i++)
		{
			result.Append(other->Get(i));
		}
		return new LinkedListSequence<T>(result);
	}
};