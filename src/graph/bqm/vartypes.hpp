/**
 * @file vartypes.hpp
 * @author Fumiya Watanabe
 * @brief Definition of variable type
 * @version 0.1
 * @date 2020-03-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef VARTYPES_HPP__
#define VARTYPES_HPP__

#include <iostream>

/**
 * @brief Enum class for representing problem type
 * 
 */
enum class Vartype
{
    SPIN = 0,
    BINARY,
    NONE = -1,
};

/**
 * @brief Check that the variable has appropriate value
 * 
 * @param var 
 * @param vartype 
 * @return true or false
 */
bool check_vartype
(
    int32_t var,
    Vartype vartype
)
{
    if(vartype == Vartype::SPIN)
    {
        if(var == 1 || var == -1)
        {
            return true;
        }
        else
        {
            std::cerr << "Spin variable must be +1 or -1." << std::endl;
            return false;
        }
    }
    else if(vartype == Vartype::BINARY)
    {
        if(var == 1 || var == 0)
        {
            return true;
        }
        else
        {
            std::cerr << "Binary variable must be 1 or 0." << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "Unknown variable type." << std::endl;
    }
};

#endif