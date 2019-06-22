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

    enum ShapeType {Astroid, Cycloid, HuygensCycloid, HypoCycloid};

    // Background color accessors
    void setBackgroundColor(QColor color){this->_backgroundColor = color;}
    QColor getBackgroundColor() const {return this->_backgroundColor;}

    // Shape accessfors
    void setShape(ShapeType shape){this->_shape = shape; this->on_shape_changed();}
    ShapeType getShape() const {return this->_shape;}

protected:
    // Override so we can control the paint
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    void on_shape_changed();
    void compute_astroid(QPainter *painter);
    QPointF compute_arc_length(float t);

private:
    QColor _backgroundColor;
    QColor _shapeColor;
    ShapeType _shape;

    // Curve computation members
    float _intervalLength;
    float _scale;
    int _stepCount;
};

#endif // RENDERAREA_H
