//
// Created by Citiral on 24/11/2015.
//

#ifndef REVERSE_TRACER_RESULT_H
#define REVERSE_TRACER_RESULT_H

#include <type_traits>
#include <utility>
#include <new>
#include <ostream>

template <class T>
class Result {
public:
    Result():_some(false) {

    }

    Result(T& t):_some(true) {
        new(&_t) T(t);
    }

    Result(const Result<T>& result): _some(result._some) {
        if (_some)
            new(&_t) T(result.value());
    }


    template <class... Args>
    Result(Args... args):_some(true) {
        new (&_t) T(std::forward<Args>(args)...);
    }

    bool is_some() const {
        return _some;
    }

    bool is_none() const {
        return !_some;
    }

    T& value() {
        return *reinterpret_cast<T*>(&_t);
    }

    const T& value() const {
        return *reinterpret_cast<const T*>(&_t);
    }

    T& value_or(T& val) {
        if (_some)
            return *reinterpret_cast<T*>(&_t);
        return val;
    }

    const T& value_or(const T& val) const {
        if (_some)
            return *reinterpret_cast<const T*>(&_t);
        return val;
    }

    T& operator->() {
        return (T)_t;
    }

    operator bool() const {
        return _some;
    }

    Result& operator=(const Result& r) {
        if (_some)
            value().~T();

        _some = r._some;

        if (_some)
            new (&_t) T(r.value());

        return *this;
    }

    Result& operator=(const T& r) {
        if (_some)
            value().~T();

        _some = true;
        new (&_t) T(r);

        return *this;
    }

    static Result<T> None;

private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type _t;
    bool _some;
};

template <class T>
Result<T> Result<T>::None = Result<T>();

template <class T>
std::ostream& operator<<(std::ostream& os, const Result<T>& obj)
{
    if (obj.is_some())
        os << obj.value();
    else
        os << "None";
    return os;
}

#endif //REVERSE_TRACER_RESULT_H
