#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    background_color(Qt::blue),
    shape_color(Qt::white),
    shape(Asteroid)
{

}

QSize RenderArea::minimumSizeHint() const {
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

// Gets called every frame
void RenderArea::paintEvent(QPaintEvent *event){
    // silence unuse warning
    Q_UNUSED(event);

    QPainter painter(this);
    // Assign the draw color
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Change background render color
    switch(shape){
    case Asteroid:
        background_color = Qt::red;
        break;
    case Cycloid:
        background_color = Qt::green;
        break;
    case HuygensCycloid:
        background_color = Qt::blue;
        break;
    case HypoCycloid:
        background_color = Qt::yellow;
        break;
    default:
        background_color = Qt::blue;
        break;
    }
    painter.setBrush(background_color);
    painter.setPen(shape_color);

    // Bounding rectangle for this widget's drawing area
    painter.drawRect(this->rect());
    // Draw diagonal line
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
}
