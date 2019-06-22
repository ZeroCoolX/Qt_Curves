#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>
#include "math.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    _backgroundColor(Qt::blue),
    _shapeColor(Qt::white),
    _shape(Astroid)
{
    this->on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

void RenderArea::on_shape_changed(){
    switch(_shape){
    case Astroid:
        _scale = 40.f;
        _intervalLength = 2.f * M_PI;
        _stepCount = 256;
        break;
    case Cycloid:
        break;
    case HuygensCycloid:
        break;
    case HypoCycloid:
        break;
    default:
        break;
    }
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
    auto step {_intervalLength / _stepCount};

    // generating a curve function
    for(auto theta{0.f}; theta < _intervalLength; theta += step){
        QPointF point = compute_arc_length(theta);

        QPoint pixel;
        pixel.setX(static_cast<int>(point.x() * _scale + center.x()));
        pixel.setY(static_cast<int>(point.y() * _scale + center.y()));

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

    painter.setBrush(_backgroundColor);
    painter.setPen(_shapeColor);

    // Drawing area
    painter.drawRect(this->rect());
    this->compute_astroid(&painter);

}
