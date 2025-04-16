//
// Created by juanp on 4/16/2025.
//

#ifndef OPTION_H
#define OPTION_H
#include <algorithm>

/**
 * @file Option.h
 * @brief A utility header that defines a template-based `Option` type for optional values.
 *
 * The `Option` class is a lightweight implementation of an optional type, inspired by
 * similar constructs in functional programming languages. It allows for the safe handling
 * of values that may or may not be present, avoiding the need for null pointers or other
 * error-prone constructs.
 *
 * @tparam T The type of the value that the `Option` may contain.
 */

 /**
    * @class Option
    * @brief A template class for representing optional values.
    *
    * The `Option` class provides a way to encapsulate a value that may or may not be present.
    * It uses manual memory management to store the value in an aligned storage buffer, ensuring
    * efficient and safe handling of the underlying type.
    *
    * @tparam T The type of the value that the `Option` may contain.
    */
template <typename T>
struct Option {
private:
    alignas(T) unsigned char storage[sizeof(T)];
    bool has_value;

public:
    Option() : has_value(false) {}

    Option(const T &value) : has_value(true) {
        new(storage) T(value);
    }

    Option(T &&value) : has_value(true) {
        new(storage) T(std::move(value));
    }

    Option(const Option &other) : has_value(other.has_value) {
        if (has_value) {
            new(storage) T(*other);
        }
    }

    Option(Option &&other) noexcept : has_value(other.has_value) {
        if (has_value) {
            new(storage) T(std::move(*other));
            other.reset();
        }
    }

    ~Option() {
        reset();
    }

    Option &operator=(const Option &other) {
        if (this != &other) {
            reset();
            if (other.has_value) {
                new(storage) T(*other);
                has_value = true;
            }
        }
        return *this;
    }

    Option &operator=(Option &&other) noexcept {
        if (this != &other) {
            reset();
            if (other.has_value) {
                new(storage) T(std::move(*other));
                has_value = true;
                other.reset();
            }
        }
        return *this;
    }

    bool isSome() const {
        return has_value;
    }

    bool isNone() const {
        return !has_value;
    }

    T &operator*() {
        return *reinterpret_cast<T*>(storage);
    }

    const T &operator*() const {
        return *reinterpret_cast<const T*>(storage);
    }

    T *operator->() {
        return reinterpret_cast<T*>(storage);
    }

    const T *operator->() const {
        return reinterpret_cast<const T*>(storage);
    }

    void reset() {
        if (has_value) {
            reinterpret_cast<T*>(storage)->~T();
            has_value = false;
        }
    }
};
#endif //OPTION_H
