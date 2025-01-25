#pragma once
#include <type_traits>
template <typename T>
class ShrdPtr
{
private:
    T* ptr;
    size_t* ref_count;

    void add_ref()
    {
        if (ref_count)
        {
            ++(*ref_count);
        }
    }

    void release()
    {
        if (ref_count)
        {
            --(*ref_count);
            if (*ref_count == 0)
            {
                delete ptr;
                delete ref_count;
            }
            ptr = nullptr;
            ref_count = nullptr;
        }
    }

    ShrdPtr(T* p, size_t* count)
        : ptr(p), ref_count(count)
    {
        add_ref();
    }

public:
    ShrdPtr() : ptr(nullptr), ref_count(nullptr) {}

    explicit ShrdPtr(T* p)
        : ptr(p), ref_count(p ? new size_t(1) : nullptr) {}

    ShrdPtr(const ShrdPtr<T>& other)
        : ptr(other.ptr), ref_count(other.ref_count)
    {
        add_ref();
    }

    ShrdPtr<T>& operator=(const ShrdPtr<T>& other)
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            add_ref();
        }
        return *this;
    }

    template <typename U>
    operator ShrdPtr<U>() const
    {
        static_assert(std::is_base_of<U, T>::value, "T must be derived from U");
        return ShrdPtr<U>(ptr, ref_count);
    }

    ShrdPtr<T>& operator=(std::nullptr_t)
    {
        release();
        return *this;
    }

    ~ShrdPtr()
    {
        release();
    }

    T& operator*()
    {
        if (!ptr) throw "Dereferencing a null pointer";
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }

    const T& operator*() const
    {
        if (!ptr) throw "Dereferencing a null pointer";
        return *ptr;
    }

    const T* operator->() const
    {
        return ptr;
    }

    explicit operator bool() const
    {
        return ptr != nullptr;
    }

    bool operator!() const
    {
        return ptr == nullptr;
    }

    void reset(T* p = nullptr)
    {
        release();
        if (p)
        {
            ptr = p;
            ref_count = new size_t(1);
        }
        else
        {
            ptr = nullptr;
            ref_count = nullptr;
        }
    }

    size_t use_count() const
    {
        return ref_count ? *ref_count : 0;
    }
};


