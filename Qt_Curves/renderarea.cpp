#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>
#include "math.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    backgroundColor(Qt::blue),
    shapeColor(Qt::white),
    shape(Astroid)
{

}

QSize RenderArea::minimumSizeHint() const {
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

// x(theta) = aCos^3(theta)
// y(theta) = aSin^3(theta)
QPointF RenderArea::compute_arc_length(float theta){
    auto cosCurve = cos(theta);
    auto sinCurve = sin(theta);

    auto xCoord = 2.f * pow(cosCurve, 3);
    auto yCoord = 2.f * pow(sinCurve, 3);

    return QPointF(xCoord, yCoord);
}

void RenderArea::compute_astroid(QPainter *painter){
    QPoint center {this->rect().center()};
    auto stepCount {256};
    auto scale {40.f};
    float intervalLength {2 * M_PI};
    auto step {intervalLength / stepCount};

    // generating a curve function
    for(auto theta{0.f}; theta < intervalLength; theta += step){
        QPointF point = compute_arc_length(theta);

        QPoint pixel;
        pixel.setX(static_cast<int>(point.x() * scale + center.x()));
        pixel.setY(static_cast<int>(point.y() * scale + center.y()));

        painter->drawPoint(pixel);
    }
}

// Gets called every frame
void RenderArea::paintEvent(QPaintEvent *event){
    // silence unused warning
    Q_UNUSED(event);

    QPainter painter(this);
    // Assign the draw color
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Change background render color
    switch(shape){
    case Astroid:
        backgroundColor = Qt::red;
        break;
    case Cycloid:
        backgroundColor = Qt::green;
        break;
    case HuygensCycloid:
        backgroundColor = Qt::blue;
        break;
    case HypoCycloid:
        backgroundColor = Qt::yellow;
        break;
    default:
        backgroundColor = Qt::blue;
        break;
    }
    painter.setBrush(backgroundColor);
    painter.setPen(shapeColor);

    // Drawing area
    painter.drawRect(this->rect());
    this->compute_astroid(&painter);

}
