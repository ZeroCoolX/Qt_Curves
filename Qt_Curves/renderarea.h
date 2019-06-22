#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    // Override so we can control the size
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Asteroid, Cycloid, HuygensCycloid, HypoCycloid};

    // Background color accessors
    void setBackgroundColor(QColor color){this->background_color = color;}
    QColor getBackgroundColor() const {return this->background_color;}

    // Shape accessfors
    void setShape(ShapeType shape){this->shape = shape;}
    ShapeType getShape() const {return this->shape;}

protected:
    // Override so we can control the paint
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QColor background_color;
    QColor shape_color;
    ShapeType shape;

};

#endif // RENDERAREA_H
