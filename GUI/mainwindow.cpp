#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plotdialog.h"
#include "waitdialog.h"
#include "calculationthread.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/icon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open CSV or data file.", "", "");
    ui->fileEdit->setText(file);
}

void MainWindow::on_singlevalueBox_toggled(bool arg1)
{
    if (arg1 && ui->multiplevaluesBox->isChecked())
    {
        ui->multiplevaluesBox->setChecked(false);
        ui->resultsButton->setText("Get Results");
    }

    if (!arg1 && !ui->multiplevaluesBox->isChecked())
    {
        ui->multiplevaluesBox->setChecked(true);
        ui->resultsButton->setText("Plot");
    }
}

void MainWindow::on_multiplevaluesBox_toggled(bool arg1)
{
    if (arg1 && ui->singlevalueBox->isChecked())
    {
        ui->singlevalueBox->setChecked(false);
        ui->resultsButton->setText("Plot");
    }

    if (!arg1 && !ui->singlevalueBox->isChecked())
    {
        ui->singlevalueBox->setChecked(true);
        ui->resultsButton->setText("Get Results");
    }
}

void MainWindow::on_saveButton_clicked()
{
    // Check if file exist.
    if (this->LoadFile(ui->fileEdit->text()))
    {
        // Ask the user for the save path.
        QString savefilepath = QFileDialog::getSaveFileName(this, "Save result to text file", "result.txt", "Text files (*.txt)");
        if (savefilepath.size() != 0)
        {
            // Try to create the output file.
            QFile file(savefilepath);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::critical(this, "Error", "Can't create output file.");
                return;
            }

            // Calculate results and output to file.
            double sample_mean = mean(this->data);
            double sample_std_error = standard_error(this->data);

            QString output;
            output.append("The mean of the data is: ");
            output.append(QString::number(sample_mean));
            output.append("\nThe lower 95% confidence limit of the mean is: ");
            output.append(QString::number(sample_mean - sample_std_error));
            output.append("\nThe upper 95% confidence limit of the mean is: ");
            output.append(QString::number(sample_mean + sample_std_error));
            output.append("\nUpper percentage point at alpha value 0.01 is: ");
            output.append(QString::number(upper_percentage_point(0.01)));
            output.append("\nUpper percentage point at alpha value 0.05 is: ");
            output.append(QString::number(upper_percentage_point(0.05)));
            output.append("\nUpper percentage point at alpha value 0.1 is: ");
            output.append(QString::number(upper_percentage_point(0.1)));

            if (ui->singlevalueBox->isChecked())
            {
                output.append("\nTn value: ");
                output.append(QString::number(tn(this->data, ui->cvalueEdit->text().toDouble())));
            }
            if (ui->multiplevaluesBox->isChecked())
            {
                double cmin = ui->minimumcEdit->text().toDouble();
                double cmax = ui->maximumcEdit->text().toDouble();
                double deltac = ui->deltacEdit->text().toDouble();

                WaitDialog waitdlg(this);
                CalculationThread thread;
                thread.SetParams(this->data, cmin, cmax, deltac);
                thread.SetWaiter(&waitdlg);
                thread.start();
                waitdlg.exec();

                std::vector< Coord<double> > result = thread.GetResult();
                output.append("\nTn values:\n");

                for (unsigned i = 0; i < result.size(); ++i)
                {
                    output.append(QString::number(result[i].GetX()));
                    output.append(", ");
                    output.append(QString::number(result[i].GetY()));
                    output.append("\n");
                }
            }

            QTextStream outstream(&file);
            outstream << output;
            file.close();
        }
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "If you use this program for academic purposes, please cite as: \n"
                                      "C. M. Rodríguez-Martínez, H.F. Coronel-Brizio (2016) Tn Symmetry "
                                      "Statistic [Computer program]. Available at: http://github.com/CarlosManuelRodr/TnSymmetryStatistic");
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_resultsButton_clicked()
{
    // Check if file exist.
    if (this->LoadFile(ui->fileEdit->text()))
    {
        // Calculate results and output to file.
        double sample_mean = mean(this->data);
        double sample_std_error = standard_error(this->data);

        if (ui->singlevalueBox->isChecked())
        {
            QString output;
            output.append("The mean of the data is: ");
            output.append(QString::number(sample_mean));
            output.append("\nThe lower 95% confidence limit of the mean is: ");
            output.append(QString::number(sample_mean - sample_std_error));
            output.append("\nThe upper 95% confidence limit of the mean is: ");
            output.append(QString::number(sample_mean + sample_std_error));
            output.append("\nUpper percentage point at alpha value 0.01 is: ");
            output.append(QString::number(upper_percentage_point(0.01)));
            output.append("\nUpper percentage point at alpha value 0.05 is: ");
            output.append(QString::number(upper_percentage_point(0.05)));
            output.append("\nUpper percentage point at alpha value 0.1 is: ");
            output.append(QString::number(upper_percentage_point(0.1)));
            output.append("\nTn value: ");
            output.append(QString::number(tn(this->data, ui->cvalueEdit->text().toDouble())));

            QMessageBox::about(this, "Results", output);
        }
        if (ui->multiplevaluesBox->isChecked())
        {
            double cmin = ui->minimumcEdit->text().toDouble();
            double cmax = ui->maximumcEdit->text().toDouble();
            double deltac = ui->deltacEdit->text().toDouble();

            WaitDialog waitdlg(this);
            CalculationThread thread;
            thread.SetParams(this->data, cmin, cmax, deltac);
            thread.SetWaiter(&waitdlg);
            thread.start();
            waitdlg.exec();

            PlotDialog dlg(this);
            dlg.SetPlot(thread.GetResult(), cmin, cmax, sample_mean, sample_std_error, upper_percentage_point(0.01),
                        upper_percentage_point(0.05), upper_percentage_point(0.1));
            dlg.exec();
        }
    }
}

bool MainWindow::LoadFile(QString path)
{
    if (path.size() != 0)
    {
        if (!aux_file_exist(path.toStdString().c_str()))
        {
            QMessageBox::warning(this, "Warning", "File doesn't exist.");
            return false;
        }

        std::string ext = aux_get_file_extension(path.toStdString());
        if (ext == "csv")
            data = aux_csv_file_to_vector(path.toStdString());
        else
            data = aux_dat_file_to_vector(path.toStdString());

        if (data.empty())
        {
            QMessageBox::critical(this, "Error", "Invalid data.");
            return false;
        }
        else
            return true;
    }
    else
    {
        QMessageBox::warning(this, "Warning", "No data file.");
        return false;
    }
}
