#pragma once
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <string>

namespace CSV
{
    template <typename T>
    void write(
        const std::vector<std::pair<T,T>> &t_vector_vector,
        std::ostream& t_file = std::cout,
        std::string t_delimeter = " ")
    {
        for (std::pair<T,T> temp : t_vector_vector)
        {
            t_file << temp.first << t_delimeter << temp.second << '\n';
        }
        t_file << '\n';
    }

    template <typename T>
    void write(
        const std::vector<T> &t_vector,
        std::ostream& t_file = std::cout,
        std::string t_delimeter = " ")
    {
        for (T temp : t_vector)
        {
            t_file << temp << t_delimeter;
        }
        t_file << '\n';
    }

    template <typename T>
    void write(
        const std::set<T> &t_set,
        std::ostream& t_file = std::cout,
        std::string t_delimeter = " ")
    {
        for (T temp : t_set)
        {
            t_file << temp << t_delimeter;
        }
        t_file << '\n';
    }

    template <typename T>
    void write(
        const std::vector<std::vector<T>> &t_vector_vector,
        std::ostream& t_file = std::cout,
        std::string t_delimeter = " ")
    {
        for (std::vector<T> temp : t_vector_vector)
        {
            write(temp,t_file,t_delimeter);
        }
        t_file << '\n';
    }

    template <typename T>
    void write(
        const std::vector<std::set<T>> &t_vector_set,
        std::ostream& t_file = std::cout,
        std::string t_delimeter = " ")
    {
        for (std::set<T> temp : t_vector_set)
        {
            write(temp,t_file,t_delimeter);
        }
        t_file << '\n';
    }
}