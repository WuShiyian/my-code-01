#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QVBoxLayout>
#include <QStringList>
#include <QCoreApplication>
#include <QDir>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onJobChanged(const QString &jobName);

private:
    QComboBox* m_cbxJob;
    QChartView* m_chartView;
    QChart* m_chart;
    QBarSeries* m_barSeries;
    QBarSet* m_barSet;

    double readDefaultRate(const QString &jobName);
    void updateChart(double rate);
};

#endif // MAINWINDOW_H
