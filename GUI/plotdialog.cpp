#include "plotdialog.h"
#include "ui_plotdialog.h"
#include "../common/spline.h"
#include <QVector>
#include <QFileDialog>

PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

void PlotDialog::SetPlot(std::vector< Coord<double> > data, double cmin, double cmax, double s_mean,
                         double std_error, double pp1, double pp2, double pp3)
{
    // Create graph and assign data.
    // Tn plot.
    unsigned size = (unsigned) data.size();
    QVector<double> c(size), t_n(size);
    for (unsigned i = 0; i < size; ++i)
    {
        c[i] = data[i].GetX();
        t_n[i] = data[i].GetY();
    }
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(c, t_n);
    ui->plot->graph(0)->setName("Tn");

    // Mean plot.
    tk::spline s;   // Interpolation to draw the means.
    s.set_points(c.toStdVector(), t_n.toStdVector());
    QVector<double> mu(2), y1(2);
    mu[0] = mu[1] = s_mean;
    y1[0] = 0.0;
    y1[1] = s(s_mean);
    ui->plot->addGraph();
    QPen blueDotPen;
    blueDotPen.setColor(QColor(30, 40, 255, 150));
    blueDotPen.setStyle(Qt::DotLine);
    blueDotPen.setWidthF(2);
    ui->plot->graph(1)->setPen(blueDotPen);
    ui->plot->graph(1)->setData(mu, y1);
    ui->plot->graph(1)->setName("μ");

    // Std error plots.
    QVector<double> stdeminus(2), stdeplus(2), y2(2), y3(2);
    stdeminus[0] = stdeminus[1] = s_mean - std_error;
    stdeplus[0] = stdeplus[1] = s_mean + std_error;
    y2[0] = 0.0;
    y3[0] = 0.0;
    y2[1] = s(s_mean - std_error);
    y3[1] = s(s_mean + std_error);
    QPen lightBlueDotPen1;
    lightBlueDotPen1.setColor(QColor(30, 80, 150, 100));
    lightBlueDotPen1.setStyle(Qt::DotLine);
    lightBlueDotPen1.setWidthF(2);
    QPen lightBlueDotPen2;
    lightBlueDotPen2.setColor(QColor(30, 150, 150, 100));
    lightBlueDotPen2.setStyle(Qt::DotLine);
    lightBlueDotPen2.setWidthF(2);
    ui->plot->addGraph();
    ui->plot->graph(2)->setPen(lightBlueDotPen1);
    ui->plot->graph(2)->setData(stdeminus, y2);
    ui->plot->graph(2)->setName("μ-Δμ");
    ui->plot->addGraph();
    ui->plot->graph(3)->setPen(lightBlueDotPen2);
    ui->plot->graph(3)->setData(stdeplus, y3);
    ui->plot->graph(3)->setName("μ+Δμ");

    // Percentage points plots.
    QVector<double> x(2), ppv1(2), ppv2(2), ppv3(2);
    x[0] = cmin;
    x[1] = cmax;
    ppv1[0] = ppv1[1] = pp1;
    ppv2[0] = ppv2[1] = pp2;
    ppv3[0] = ppv3[1] = pp3;
    ui->plot->addGraph();
    ui->plot->graph(4)->setPen(QPen(Qt::blue));
    ui->plot->graph(4)->setData(x, ppv1);
    ui->plot->graph(4)->setName("99% CL");
    ui->plot->addGraph();
    ui->plot->graph(5)->setPen(QPen(Qt::green));
    ui->plot->graph(5)->setData(x, ppv2);
    ui->plot->graph(5)->setName("95% CL");
    ui->plot->addGraph();
    ui->plot->graph(6)->setPen(QPen(Qt::red));
    ui->plot->graph(6)->setData(x, ppv3);
    ui->plot->graph(6)->setName("90% CL");

    ui->plot->xAxis->setLabel("c");
    ui->plot->yAxis->setLabel("T");
    ui->plot->xAxis->setRange(cmin, cmax);

    ui->plot->legend->setVisible(true);
    ui->plot->replot();
}

void PlotDialog::on_saveButton_clicked()
{
    QString savefilepath = QFileDialog::getSaveFileName(this, "Save result to image file", "result.png", "png file (*.png)");
    if (savefilepath.size() != 0)
        ui->plot->savePng(savefilepath);
    else
        return;
}

void PlotDialog::on_closeButton_clicked()
{
    this->close();
}
