#pragma once

#include <cassert>
#include <cstdlib>
#include <utility>
using namespace std;
template <typename Type>
class ArrayPtr {
public:
    ArrayPtr() = default;
    explicit ArrayPtr(size_t size) {
        if (size == 0) {
            raw_ptr_ = nullptr;
        }
        else {
            raw_ptr_ = new Type[size];
        }
    }
    explicit ArrayPtr(Type* raw_ptr) noexcept {
        raw_ptr_ = raw_ptr;
    }
    ArrayPtr(const ArrayPtr&) = delete;

    ArrayPtr(ArrayPtr&& other) {
        raw_ptr_ = exchange(other.raw_ptr_, nullptr);
    }

    ~ArrayPtr() {
        delete[] raw_ptr_;
        raw_ptr_ = nullptr;
    }

    ArrayPtr& operator=(const ArrayPtr&) = delete;

    ArrayPtr& operator=(ArrayPtr&& other) {
        raw_ptr_ = exchange(other.raw_ptr_, raw_ptr_);
        return *this;
    }

    [[nodiscard]] Type* Release() noexcept {
        auto* ref = raw_ptr_;
        raw_ptr_ = nullptr;
        return ref;
    }

    Type& operator[](size_t index) noexcept {
        return raw_ptr_[index];
    }

    const Type& operator[](size_t index) const noexcept {
        return raw_ptr_[index];
    }

    explicit operator bool() const {
        return raw_ptr_ != nullptr;
    }
    

    Type* Get() const noexcept {
        return raw_ptr_;
    }

    void swap(ArrayPtr& other) noexcept {  
        std::swap(other.raw_ptr_,raw_ptr_);
    }

private:
    Type* raw_ptr_ = nullptr;
};