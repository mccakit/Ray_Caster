#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <stdfloat>
#include <thread>
#include <fstream>
#include <cmath>

using flt = double;
using f64 = std::float64_t;
using f32 = std::float32_t;
using f16 = std::float16_t;
using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;


template<typename T>
class CustomVector : public std::vector<T>
{
public:
    using std::vector<T>::vector;

    int size() const
    {
        return static_cast<int>(std::vector<T>::size());
    }
    void append(const T& item)
    {
        std::vector<T>::push_back(item);
    }
    void pop()
    {
        std::vector<T>::pop_back();
    }
};

template<typename T>
using arr = CustomVector<T>;
using str = std::string;
using out = std::ostream;
using in = std::istream;
std::ostream& cout = std::cout;
std::istream& cin = std::cin;

template<typename T>
using ptr = std::shared_ptr<T>;

using thread = std::jthread;
using mutex = std::mutex;
using lock = std::scoped_lock<std::mutex>;

template<typename T>
constexpr T&& move(T& t)
{
    return static_cast<T &&>(t);
}

enum fmode
{
    append    = 1,
    read     = 8,
    write    = 16
};
class CustomFile : public std::fstream
{
public:
    using std::fstream::fstream;
    void open(const std::string& filename, const fmode& mode)
    {
        std::fstream::open(filename, static_cast<std::ios::openmode>(mode));
    }
};
using file = CustomFile;

template<typename T, typename U>
T cast(const U& value)
{
    return static_cast<T>(value);
}
template<typename T>
using init_list = std::initializer_list<T>;
template<typename T1, typename T2>

auto pow(T1 base, T2 exponent) {
    return std::pow(base, exponent);
}
template <typename T>
auto sqrt(T base) {
    return std::sqrt(base);
}
