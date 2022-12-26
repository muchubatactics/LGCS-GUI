#ifndef WINDOW_H
#define WINDOW_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QGraphicsSceneMouseEvent>
#include <QString>


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow(){}
public slots:
    void addAndGate();
    void addOrGate();
    void addNotGate();

private:
    //icons
    QPixmap andGateIcon;
    QPixmap orGateIcon;
    QPixmap notGateIcon;

    //layouts
    QVBoxLayout* mainLayout;
    QHBoxLayout* toolbarLayout;
    QHBoxLayout* graphicsLayout;
    QHBoxLayout* gatesLayout;

    //graphic scene
    QGraphicsView* canvas;
    QGraphicsScene* scene;

    //logic Gates
    // QList<LogicGate*> gateList;

    
};

class LogicGate : public QGraphicsItem
{
public:
    LogicGate(QGraphicsItem* parent);
    QRectF boundingRect() const override;
    QString getName() const { return Name;}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    QPointF lastMousePos;
    QString Name;
    bool moving = false;

private:
    static int ExistingGates;

};

class AndGate : public LogicGate
{
public:
    AndGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a, bool b);
    bool getOutput() const;

private:
    bool inputA = false;
    bool inputB = false;
    bool output = false;
};

class OrGate : public LogicGate
{
public:
    OrGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a, bool b);
    bool getOutput() const;

private:
    bool inputA = false;
    bool inputB = false;
    bool output = false;
};

class NotGate : public LogicGate
{
public:
    NotGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a);
    bool getOutput() const;

private:
    bool inputA = false;
    bool output = false;
};


#endif // WINDOW_H