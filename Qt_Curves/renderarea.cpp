#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    background_color(QColor(0,0,255)),
    shape_color(QColor(255,255,255))
{

}

QSize RenderArea::minimumSizeHint() const {
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const {
    return QSize(400, 200);
}

void RenderArea::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    // Assign the draw color
    painter.setBrush(background_color);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(shape_color);

    // Bounding rectangle for this widget's drawing area
    painter.drawRect(this->rect());
    // Draw diagonal line
    painter.drawLine(this->rect().topLeft(), this->rect().bottomRight());
}
