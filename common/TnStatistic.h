#ifndef TNSTATISTIC_H
#define TNSTATISTIC_H
#include <vector>

/****************************
*                           *
*    Coordinate storage     *
*                           *
****************************/

template <class T> class Coord
{
public:
    T m_x, m_y;
    Coord();
    Coord(T x, T y);
    T GetX();
    T GetY();
};

template <class T> Coord<T>::Coord()
{
    m_x = 0;
    m_y = 0;
}
template <class T> Coord<T>::Coord(T x, T y)
{
    m_x = x;
    m_y = y;
}
template <class T> T Coord<T>::GetX()
{
    return m_x;
}
template <class T> T Coord<T>::GetY()
{
    return m_y;
}


/****************************
*                           *
*        Tn Statistic       *
*                           *
****************************/

double mean(const std::vector<double> &y);
double standard_deviation(const std::vector<double> &y);
double standard_error(const std::vector<double> &y);
double upper_percentage_point(const double alpha);

double tn_zero(const std::vector<double> &y);
double tn(std::vector<double> y, const double c);
std::vector< Coord<double> > ranged_tn(const std::vector<double> &y, const double cmin, const double cmax, const double deltac);

#endif /* TNSTATISTIC_H */

