#pragma once
#include <iostream>

template <typename T>
class UniquePtr
{
    T* ptr;
public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}
    ~UniquePtr() { delete ptr; }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};

template <typename T>
class SharedPtr
{
    T* ptr;
    int* refCount;
public:
    explicit SharedPtr(T* p = nullptr) : ptr(p), refCount(new int(1)) {}
    ~SharedPtr() { release(); }

    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount)
    {
        (*refCount)++;
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            (*refCount)++;
        }
        return *this;
    }

    T& operator*() { return *ptr;}
    T* operator->() { return ptr;}

private:
    void release()
    {
        if (--(*refCount) == 0)
        {
            delete ptr;
            delete refCount;
        }
    }
};
