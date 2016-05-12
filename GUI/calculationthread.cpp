#include "calculationthread.h"

void CalculationThread::run()
{
    m_result = ranged_tn(m_data, m_cmin, m_cmax, m_deltac);
    m_dlg->close();
}
void CalculationThread::SetParams(std::vector <double> data, double cmin, double cmax, double deltac)
{
    m_data = data;
    m_cmin = cmin;
    m_cmax = cmax;
    m_deltac = deltac;
}
std::vector< Coord<double> > CalculationThread::GetResult()
{
    return m_result;
}
void CalculationThread::SetWaiter(WaitDialog *dlg)
{
    m_dlg = dlg;
}
