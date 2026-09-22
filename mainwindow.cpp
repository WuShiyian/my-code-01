#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("职业违约率");
    this->resize(600,400);

    QWidget* centralWgt = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout(centralWgt);
    this->setCentralWidget(centralWgt);

    m_cbxJob = new QComboBox();
    m_cbxJob->addItems({"程序员","教师","销售","个体户","公务员"});
    vLayout->addWidget(m_cbxJob);

    // ========== 只在构造函数创建一次图表 ==========
    m_chart = new QChart();
    m_barSeries = new QBarSeries();
    m_barSet = new QBarSet("违约率");
    m_barSeries->append(m_barSet);
    m_chart->addSeries(m_barSeries);

    QCategoryAxis* axisX = new QCategoryAxis();
    axisX->append("违约率",0);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0,0.2);
    axisY->setTitleText("违约率");

    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_barSeries->attachAxis(axisX);
    m_barSeries->attachAxis(axisY);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    vLayout->addWidget(m_chartView);

    connect(m_cbxJob, &QComboBox::currentTextChanged, this, &MainWindow::onJobChanged);
    onJobChanged(m_cbxJob->currentText());
}


MainWindow::~MainWindow()
{
}

void MainWindow::onJobChanged(const QString &jobName)
{
    double rate = readDefaultRate(jobName);
    if(rate < 0)
    {
        QMessageBox::warning(this,"错误","未找到csv文件或对应职业数据！");
        return;
    }
    updateChart(rate);
}

double MainWindow::readDefaultRate(const QString &jobName)
{
    QFile file(QDir::cleanPath(QCoreApplication::applicationDirPath() + "/../credit_data.csv"));

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return -1.0;
    }
    QTextStream stream(&file);
    QString line;
    stream.readLine();

    while(!stream.atEnd())
    {
        line = stream.readLine();
        QStringList parts = line.split(",");
        if(parts.size() <3) continue;
        QString job = parts[0].trimmed();
        if(job == jobName)
        {
            bool ok;
            double rate = parts[2].trimmed().toDouble(&ok);
            file.close();
            if(ok) return rate;
            else return -1;
        }
    }
    file.close();
    return -1.0;
}

void MainWindow::updateChart(double rate)
{
    // 清空旧柱子数据，不重新创建图表
    m_barSet->remove(0, m_barSet->count());
    m_barSet->append(rate);

    // 坐标轴直接复用，不用重复addAxis
    m_chart->setTitle("当前职业违约率");
}

