#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fileButton_clicked();

    void on_singlevalueBox_toggled(bool arg1);

    void on_multiplevaluesBox_toggled(bool arg1);

    void on_saveButton_clicked();

    void on_actionAbout_triggered();

    void on_actionClose_triggered();

    void on_resultsButton_clicked();

private:
    Ui::MainWindow *ui;

    // TnStatistic functions and variables.
    std::vector <double> data;
    bool LoadFile(QString path);

};

#endif // MAINWINDOW_H
