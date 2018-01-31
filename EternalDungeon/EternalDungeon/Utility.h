#pragma once

#include <algorithm>
#include <random>

#include <Windows.h>
// console font colors
static const size_t color_default = 7;
static const size_t color_black = 0;
static const size_t color_blue = 1;
static const size_t color_green = 2;
static const size_t color_aqua = 3;
static const size_t color_red = 4;
static const size_t color_purple = 5;
static const size_t color_yellow = 6;
static const size_t color_light = 7;
static const size_t color_gray = 8;
static const size_t color_lightBlue = 0xA;
static const size_t color_lightAqua = 0xB;
static const size_t color_lightRed = 0xC;
static const size_t color_lightPurple = 0xD;
static const size_t color_lightYellow = 0xE;
static const size_t color_white = 0xF;

void WaitForUser();

template <class T>
T randomFrom(const T min, const T max)
{
    static std::random_device rdev;
    static std::default_random_engine re(rdev());
    typedef typename std::conditional<
        std::is_floating_point<T>::value,
        std::uniform_real_distribution<T>,
        std::uniform_int_distribution<T>>::type dist_type;
    dist_type uni(min, max);
    return static_cast<T>(uni(re));
}

void Print(std::string str, size_t colorNum = color_default, bool endLine = true);