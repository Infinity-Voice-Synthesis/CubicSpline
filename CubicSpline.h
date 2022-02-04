#pragma once

#include <QtWidgets/QMainWindow>
#include <QVector>
#include <QMap>
#include <QPainter>
#include "CubicS.h"

class CubicSpline : public QMainWindow
{
    Q_OBJECT

public:
    CubicSpline(QWidget *parent = Q_NULLPTR);
    ~CubicSpline();

private:
    CubicS* cubic = nullptr;
    QVector<QPair<double, double>> points;
    double* x = nullptr;
    double* y = nullptr;
    double* a = nullptr;
    double* b = nullptr;
    double* c = nullptr;
    double* d = nullptr;

    void spline();

protected:
    void paintEvent(QPaintEvent* event)override;
};
