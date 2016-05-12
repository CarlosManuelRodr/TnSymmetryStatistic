#ifndef CALCULATIONTHREAD_H
#define CALCULATIONTHREAD_H

#include <QThread>
#include "../common/TnStatistic.h"
#include "../common/Auxiliary.h"
#include "waitdialog.h"

class CalculationThread : public QThread
{
    Q_OBJECT

protected:
    std::vector< Coord<double> > m_result;
    std::vector <double> m_data;
    double m_cmin, m_cmax, m_deltac;
    WaitDialog *m_dlg;

    void run();

public:
    void SetWaiter(WaitDialog *dlg);
    void SetParams(std::vector <double> data, double cmin, double cmax, double deltac);
    std::vector< Coord<double> > GetResult();
};

#endif // CALCULATIONTHREAD_H
