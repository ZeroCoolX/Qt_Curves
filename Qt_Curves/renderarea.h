#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    // Override so we can control the size
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Astroid,
                    Cycloid,
                    HuygensCycloid,
                    HypoCycloid,
                    Line,
                    Circle,
                    Fancy,
                    Starfish};

    // Background color accessors
    void setBackgroundColor(QColor color){this->_backgroundColor = color;}
    QColor getBackgroundColor() const {return this->_backgroundColor;}

    void setShapeColor(QColor color){this->_drawPen.setColor(color);}
    QColor getShapeColor() const {return this->_drawPen.color();}

    // Accessors
    void setShape(ShapeType shape){this->_shape = shape; this->on_shape_changed();}
    ShapeType getShape() const {return this->_shape;}

    void setPixelScale(float pixelScale){this->_pixelScale = pixelScale; this->repaint();}
    float getPixelScale() const {return this->_pixelScale;}

    void setIntervalLength(float interval){this->_intervalLength = interval; this->repaint();}
    float getIntervalLength() const {return this->_intervalLength;}

    void setStepCount(int stepCount){this->_stepCount = stepCount; this->repaint();}
    int getStepCount() const {return this->_stepCount;}

protected:
    // Override so we can control the paint
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    void on_shape_changed();
    void draw_shape(QPainter *painter);
    QPointF compute_curve(float theta);       // dispatch function based on _shape's type
    QPointF compute_astroid(float theta);
    QPointF compute_cycloid(float theta);
    QPointF compute_huygens(float theta);
    QPointF compute_hypo(float theta);
    QPointF compute_line(float theta);
    QPointF compute_circle(float theta);
    QPointF compute_fancy(float theta);
    QPointF compute_starfish(float theta);

private:
    QColor _backgroundColor;
    ShapeType _shape;
    QPen _drawPen;

    // Curve computation members
    float _intervalLength;
    float _pixelScale;
    int _stepCount;
};

#endif // RENDERAREA_H
