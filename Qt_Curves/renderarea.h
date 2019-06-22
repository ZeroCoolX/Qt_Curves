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

    enum Shapes {Asteroid, Cycloid, HuygensCycloid, HypoCycloid};

    void setBackgroundColor(QColor color){background_color = color;}
    QColor getBackgroundColor() const {return background_color;}

protected:
    // Override so we can control the paint
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QColor background_color;
    QColor shape_color;

};

#endif // RENDERAREA_H
