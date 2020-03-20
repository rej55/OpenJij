/**
 * @file utilities.hpp
 * @author Fumiya Watanabe
 * @brief Utilities for cpp_dimod
 * @version 0.1
 * @date 2020-03-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef UTILITIES_HPP__
#define UTILITIES_HPP__

#include <unordered_map>

/**
 * @brief Insert or assign a element of unordered_map (for C++14 or C++11)
 * 
 * @tparam C_key 
 * @tparam C_value 
 * @param um 
 * @param key 
 * @param val 
 */

template <class C_key, class C_value, class Hash>
void insert_or_assign
(
    std::unordered_map<C_key, C_value, Hash> &um,
    const C_key &key,
    const C_value &val
)
{
    // insert
    if(um.count(key)==0)
    {
        um.insert({{key, val}});
    }
    // assign
    else
    {
        um[key] = val;
    }
}

#endif