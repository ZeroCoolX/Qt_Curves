#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>
#include "math.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    _backgroundColor(Qt::blue),
    _drawPen(Qt::white),
    _shape(Astroid)
{
    this->_drawPen.setWidth(2);
    this->on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const {
    return QSize(400, 400);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

void RenderArea::on_shape_changed(){
    switch(_shape){
    case Astroid:
        _pixelScale = 90.f;
        _intervalLength = 2.f * M_PI;
        _stepCount = 256;
        this->setBackgroundColor(Qt::red);
        break;
    case Cycloid:
        _pixelScale = 10.f;
        _intervalLength = 4.f * M_PI;
        _stepCount = 128;
        this->setBackgroundColor(Qt::green);
        break;
    case HuygensCycloid:
        _pixelScale = 15.f;
        _intervalLength = 4.f * M_PI;
        _stepCount = 256;
        this->setBackgroundColor(Qt::blue);
        break;
    case HypoCycloid:
        _pixelScale = 40;
        _intervalLength = 2.f * M_PI;
        _stepCount = 256;
        this->setBackgroundColor(QColor(102, 0, 204)); // purple
        break;
    case Line:
        _pixelScale = 100;
        _intervalLength = 2.f;
        _stepCount = 128;
        break;
    case Circle:
        _pixelScale = 100;
        _intervalLength = 2.f * M_PI;
        _stepCount = 128;
        break;
    case Fancy:
        _pixelScale = 10;
        _intervalLength = 12.f * M_PI;
        _stepCount = 512;
        break;
    case Starfish:
        _pixelScale = 25;
        _intervalLength = 6.f * M_PI;
        _stepCount = 256;
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
    case Line:
        return compute_line(theta);
        break;
    case Circle:
        return compute_circle(theta);
        break;
    case Fancy:
        return compute_fancy(theta);
        break;
    case Starfish:
        return compute_starfish(theta);
        break;
    default:
        break;
    }
    return QPointF(0, 0);
}


// http://mathworld.wolfram.com/Astroid.html
QPointF RenderArea::compute_astroid(float theta){
    auto xCoord = 2.f * pow(cos(theta), 3);
    auto yCoord = 2.f * pow(sin(theta), 3);

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

QPointF RenderArea::compute_line(float theta){
    return QPointF(1.f - theta,1.f - theta);
}

QPointF RenderArea::compute_circle(float theta){
    return QPointF(
                cos(theta),
                sin(theta)
                );
}

QPointF RenderArea::compute_fancy(float theta){
    auto xCoord = 11 * cos(theta) - 6 * cos((11.f / 6.f) * theta);
    auto yCoord = 11 * sin(theta) - 6 * sin((11.f / 6.f) * theta);
    return QPointF(xCoord, yCoord);
}

QPointF RenderArea::compute_starfish(float theta){
    auto radius {3.f};
    auto R{5.f};
    auto diameter{5.f};

    auto xCoord = (R - radius) * cos(theta) + diameter * cos((theta * ((R - radius) / radius)));
    auto yCoord = (R - radius) * sin(theta) - diameter * sin((theta * ((R - radius) / radius)));

    return QPointF(xCoord, yCoord);
}

void RenderArea::draw_shape(QPainter *painter){
    QPoint center {this->rect().center()};

    QPointF prevPoint {compute_curve(0.f)};
    QPoint prevPixel(
                static_cast<int>(prevPoint.x() * _pixelScale + center.x()),
                static_cast<int>(prevPoint.y() * _pixelScale + center.y())
                );

    QPoint pixel;
    QPointF point;

    auto step {_intervalLength / _stepCount};

    for(auto theta{0.f}; theta < _intervalLength; theta += step){
        // compute shape's curve
        point = compute_curve(theta);

        // calculate individual point
        pixel.setX(static_cast<int>(point.x() * _pixelScale + center.x()));
        pixel.setY(static_cast<int>(point.y() * _pixelScale + center.y()));

        // draw line from last pixel and this pixel for a consistent render
        painter->drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }

    // Final draw to ensure the shape connects
    point = compute_curve(_intervalLength);

    // calculate individual point
    pixel.setX(static_cast<int>(point.x() * _pixelScale + center.x()));
    pixel.setY(static_cast<int>(point.y() * _pixelScale + center.y()));

    // draw line from last pixel and this pixel for a consistent render
    painter->drawLine(pixel, prevPixel);
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
    painter.setPen(_drawPen);

    // Drawing area
    painter.drawRect(this->rect());
    this->draw_shape(&painter);
}
