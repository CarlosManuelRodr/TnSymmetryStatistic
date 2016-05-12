#ifndef _AUXILIARY
#define _AUXILIARY

#include <string>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <iostream>
#include <vector>
#include "TnStatistic.h"

/****************************
*                           *
*    Auxiliary functions.   *
*                           *
****************************/

template <class N> std::string aux_num_to_string(const N d)
{
    std::ostringstream oss;
    oss << d;
    return oss.str();
}
template <class N> N aux_string_to_num(const std::string &s)
{
    std::istringstream i(s);
    N x;
    if (!(i >> x))
        return 0;
    return static_cast<N>(x);
}
template <class N> std::vector<N> aux_csv_to_vector(const std::string in)
{
    std::string m_in = in;
    std::vector<N> out;
    int startPos = 0;

    for (unsigned int i=0; i<m_in.length(); i++)
    {
        if (m_in[i] == ',')
        {
            out.push_back(aux_string_to_num<N>(m_in.substr(startPos, i-startPos)));
            startPos = i+1;
        }
        if (i+1 == m_in.length())
        {
            if (m_in[in.length()-1] == '\n' || m_in[in.length()-1] == '\r')
                out.push_back(aux_string_to_num<N>(m_in.substr(startPos, m_in.length()-startPos-1)));
            else
                out.push_back(aux_string_to_num<N>(m_in.substr(startPos, m_in.length()-startPos)));
        }
    }
    return out;
}
std::string aux_get_file_extension(const std::string filepath);
bool aux_file_exist(const char *fileName);
std::string aux_get_file_contents(const char *filename);
std::vector<double> aux_dat_file_to_vector(const std::string filepath);
std::vector<double> aux_csv_file_to_vector(const std::string filepath);
void aux_number_to_file(const std::string filepath, const double number);
void aux_coordvector_to_file(const std::string filepath, std::vector< Coord<double> > v);
void aux_print_coordvector(std::vector< Coord<double> > v);

#endif
