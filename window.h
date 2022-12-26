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

class LogicGate : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    LogicGate(QGraphicsItem* parent);
    QRectF boundingRect() const override;
    QString getName() const { return Name;}
    QVBoxLayout* getlayout() const { return gatelay;}



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    QPointF lastMousePos;
    QString Name;
    bool moving = false;

    QVBoxLayout* gatelay;
    QLabel *gatename;

private:
    static int ExistingGates;

};

class AndGate : public LogicGate
{
    Q_OBJECT
public:
    AndGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a, bool b);
    bool getOutput() const;

public slots:
    void updateOutput(QString);

private:
    bool inputA = false;
    bool inputB = false;
    bool output = false;
    QLineEdit* inputa;
    QLineEdit* inputb;
    QLabel* outputy;
    
};

class OrGate : public LogicGate
{
    Q_OBJECT
public:
    OrGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a, bool b);
    bool getOutput() const;

public slots:
    void updateOutput(QString);

private:
    bool inputA = false;
    bool inputB = false;
    bool output = false;
    QLineEdit* inputa;
    QLineEdit* inputb;
    QLabel* outputy;
};

class NotGate : public LogicGate
{
    Q_OBJECT
public:
    NotGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a);
    bool getOutput() const;

public slots:
    void updateOutput(QString);

private:
    bool inputA = false;
    bool output = false;
    QLineEdit* inputa;
    QLabel* outputy;
};


#endif // WINDOW_H
