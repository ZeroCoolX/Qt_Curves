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
        this->setBackgroundColor(Qt::red);
        break;
    case Cycloid:
        _scale = 4;
        _intervalLength = 6.f * M_PI;
        _stepCount = 128;
        this->setBackgroundColor(Qt::green);
        break;
    case HuygensCycloid:
        _scale = 4;
        _intervalLength = 4.f * M_PI;
        _stepCount = 256;
        this->setBackgroundColor(Qt::blue);
        break;
    case HypoCycloid:
        _scale = 15;
        _intervalLength = 2.f * M_PI;
        _stepCount = 256;
        this->setBackgroundColor(QColor(102, 0, 204)); // purple
        break;
    default:
        break;
    }
}

QPointF RenderArea::compute_curve(float theta){
    switch(_shape){
    case Astroid:
        return compute_astroid(theta);
        break;
    case Cycloid:
        return compute_cycloid(theta);
        break;
    case HuygensCycloid:
        return compute_huygens(theta);
        break;
    case HypoCycloid:
        return compute_hypo(theta);
        break;
    default:
        break;
    }
    return QPointF(0, 0);
}

// x(theta) = aCos^3(theta)
// y(theta) = aSin^3(theta)
// http://mathworld.wolfram.com/Astroid.html
QPointF RenderArea::compute_astroid(float theta){
    auto cosCurve = cos(theta);
    auto sinCurve = sin(theta);

    auto xCoord = 2.f * pow(cosCurve, 3);
    auto yCoord = 2.f * pow(sinCurve, 3);

    return QPointF(xCoord, yCoord);
}

// http://mathworld.wolfram.com/Cycloid.html
QPointF RenderArea::compute_cycloid(float theta){
    return QPointF(
                1.5f * (1 - cos(theta)),
                1.5f * (theta - sin(theta))
                );
}

// ???
QPointF RenderArea::compute_huygens(float theta){
    return QPointF(
                4 * (3 * cos(theta) - cos(3 * theta)),
                4 * (3 * sin(theta) - sin(3 * theta))
                );
}

// http://mathworld.wolfram.com/Hypocycloid.html
QPointF RenderArea::compute_hypo(float theta){
    return QPointF(
                1.5f * (2 * cos(theta) + cos(2 * theta)),
                1.5 * (2 * sin(theta) - sin(2 * theta))
                );
}

void RenderArea::draw_shape(QPainter *painter){
    QPoint center {this->rect().center()};
    auto step {_intervalLength / _stepCount};

    for(auto theta{0.f}; theta < _intervalLength; theta += step){
        // compute shape's curve
        QPointF point = compute_curve(theta);
        // calculate individual point
        QPoint pixel;
        pixel.setX(static_cast<int>(point.x() * _scale + center.x()));
        pixel.setY(static_cast<int>(point.y() * _scale + center.y()));
        // draw point
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
    this->draw_shape(&painter);
}
