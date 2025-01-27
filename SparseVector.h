#pragma once
#include "DictionaryOnSequence.h"
#include <iostream>

template<typename T>
class SparseVector 
{
private:
    DictionaryOnSequence<int, T> dictionary; 
    int size;
    T defaultValue;

public:

    SparseVector(int size, T defaultValue)
        : dictionary(), size(size), defaultValue(defaultValue) {}

    SparseVector(T defaultValue) 
        : dictionary(), size(0), defaultValue(defaultValue) {}

    SparseVector(SparseVector<T>& other)
        : dictionary(other.dictionary), size(other.size), defaultValue(other.defaultValue) {}

    SparseVector(const Sequence<T>& sequence, int size, T defaultValue)
        : dictionary(), size(size), defaultValue(defaultValue)
    {
        if (sequence.GetLength() > size) 
        {
            throw "Sequence length exceeds vector size";
        }

        for (int i = 0; i < sequence.GetLength(); ++i) 
        {
            if (sequence.Get(i) != defaultValue) 
            {
                dictionary.Add(i, sequence.Get(i));
            }
        }
    }

    void Set(int index, T value) 
    {
        if (index < 0) 
        {
            throw "Index out of range";
        }

        if (index >= size)
        {
            Resize(index + 1);
        }

        if (value == defaultValue) 
        {
            if (dictionary.ContainsKey(index)) 
            {
                dictionary.Remove(index);
            }
        }

        else 
        {
            if (dictionary.ContainsKey(index)) 
            {
                dictionary.Remove(index);
            }
            dictionary.Add(index, value);
        }
    }

    T Get(int index) const 
    {
        if (index < 0 || index >= size) 
        {
            throw "Index out of range";
        }
        if (dictionary.ContainsKey(index)) 
        {
            return dictionary.Get(index);
        }
        return defaultValue;
    }

    void Append(T value) 
    {
        if (value != defaultValue)
        {
            dictionary.Add(size, value);
        }
        ++size;
    }

    int GetNonZeroCount() const 
    {
        return dictionary.GetCount();
    }

    void Resize(size_t Size)
    {
        this->size = Size;
    }

    friend std::ostream& operator<<(std::ostream& os, const SparseVector<T>& vector) 
    {
        os << "{ ";
        for (int i = 0; i < vector.size; ++i) 
        {
            os << vector.Get(i);
            if (i != vector.size - 1) 
            {
                os << ", ";
            }
        }
        os << " }";
        return os;
    }


};