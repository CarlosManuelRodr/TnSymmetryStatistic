#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include <vector>
#include "../common/TnStatistic.h"

namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(QWidget *parent = 0);
    ~PlotDialog();

    void SetPlot(std::vector< Coord<double> > data, double cmin, double cmax, double s_mean,
                 double std_error, double pp1, double pp2, double pp3);

private slots:
    void on_saveButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PlotDialog *ui;
};

#endif // PLOTDIALOG_H
