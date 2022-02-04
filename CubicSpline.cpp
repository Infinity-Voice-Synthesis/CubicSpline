#include "CubicSpline.h"

CubicSpline::CubicSpline(QWidget *parent)
    : QMainWindow(parent)
{
    this->points.append(qMakePair(0.1, 0.5));
    this->points.append(qMakePair(0.2, 0.1));
    this->points.append(qMakePair(0.3, 0.6));
    this->points.append(qMakePair(0.35, 0.2));
    this->points.append(qMakePair(0.4, 0.7));
    this->points.append(qMakePair(0.6, 0.5));
    this->points.append(qMakePair(0.7, 0.8));
    this->points.append(qMakePair(0.8, 0.2));
    this->points.append(qMakePair(0.9, 0.4));
    this->spline();
}

CubicSpline::~CubicSpline()
{
    if (this->cubic != nullptr) {
        delete this->cubic;
        this->cubic = nullptr;
    }
    if (this->x != nullptr) {
        delete[] this->x;
        this->x = nullptr;
    }
    if (this->y != nullptr) {
        delete[] this->y;
        this->y = nullptr;
    }
    if (this->a != nullptr) {
        delete[] this->a;
        this->a = nullptr;
    }
    if (this->b != nullptr) {
        delete[] this->b;
        this->b = nullptr;
    }
    if (this->c != nullptr) {
        delete[] this->c;
        this->c = nullptr;
    }
    if (this->d != nullptr) {
        delete[] this->d;
        this->d = nullptr;
    }
}

void CubicSpline::spline()
{
    if (this->cubic != nullptr) {
        delete this->cubic;
        this->cubic = nullptr;
    }
    if (this->x != nullptr) {
        delete[] this->x;
        this->x = nullptr;
    }
    if (this->y != nullptr) {
        delete[] this->y;
        this->y = nullptr;
    }
    if (this->a != nullptr) {
        delete[] this->a;
        this->a = nullptr;
    }
    if (this->b != nullptr) {
        delete[] this->b;
        this->b = nullptr;
    }
    if (this->c != nullptr) {
        delete[] this->c;
        this->c = nullptr;
    }
    if (this->d != nullptr) {
        delete[] this->d;
        this->d = nullptr;
    }

    if (this->points.size() < 2) {
        return;
    }

    this->x = new double[this->points.size()];
    this->y = new double[this->points.size()];
    for (int i = 0; i < this->points.size(); i++) {
        memcpy(&(this->x[i]), &(this->points.at(i).first), sizeof(double));
        memcpy(&(this->y[i]), &(this->points.at(i).second), sizeof(double));
    }

    this->cubic = new CubicS(this->x, this->y, this->points.size());
    
    this->a = new double[this->points.size() - 1];
    this->b = new double[this->points.size() - 1];
    this->c = new double[this->points.size() - 1];
    this->d = new double[this->points.size() - 1];

    this->cubic->caculate(this->a, this->b, this->c, this->d);
}

void CubicSpline::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    if (this->cubic == nullptr) {
        return;
    }

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::GlobalColor::blue);
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);
    pen.setWidth(2);
    painter.setPen(pen);

    QPolygon poly;
    for (int i = 0; i < this->width(); i++) {
        QPoint point(i, this->height() * this->cubic->result(i / (double)this->width()));
        poly.append(point);
    }
    painter.drawPoints(poly);

    pen.setColor(Qt::GlobalColor::black);
    pen.setWidth(1);
    painter.setPen(pen);

    QBrush brush;
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    brush.setColor(Qt::GlobalColor::red);
    painter.setBrush(brush);

    for (int i = 0; i < this->points.size(); i++) {
        QPoint point(this->width() * this->points.at(i).first, this->height() * this->points.at(i).second);
        painter.drawEllipse(point, 4, 4);
    }
}
