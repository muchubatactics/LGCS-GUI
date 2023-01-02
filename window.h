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
#include <QDebug>
#include <QRegion>

class LogicGate : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    LogicGate(QGraphicsItem* parent);
    QRectF boundingRect() const override;
    QString getName() const { return Name;}
    QVBoxLayout* getlayout() const { return gatelay;}
    virtual int forCast() = 0;

    void setPosition(const QPointF& pos)
    {
        position = pos;
    }

    friend class MainWindow;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    QPointF lastMousePos;
    QString Name;
    bool moving = false;

    QVBoxLayout* gatelay;
    QLabel *gatename;
    static QVector<LogicGate*> gates;

    int setTest;
    QPointF position;
    qreal height = 100;
    qreal width = 100;

private:
    static int ExistingGates;

};

class Draw : public QGraphicsItem
{
public:
    Draw(QGraphicsItem* parent);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    static void setButton(QPushButton*);
    static QList<QGraphicsItem *> overlappedGates(QGraphicsScene* scene);
    static bool pathWithInregion(QGraphicsItem*, QPainterPath*);
    QPainterPath* getPath() const;
    
    friend class LogicGate;
    friend class MainWindow;

private:
    static QVector<Draw*> allPaths;
    static QPushButton* button;
    QPainterPath* currentPath;
};



class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow(){}

    friend class Draw;
public slots:
    void addAndGate();
    void addOrGate();
    void addNotGate();
    void simulate();

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
    static QGraphicsView* canvas;
    static QGraphicsScene* scene;

    //logic Gates
    // QList<LogicGate*> gateList;

    //drawing
    QPushButton* drawButton;
    Draw* draw;
    

    //simulation
    QPushButton* simButton;
    QHBoxLayout* simLayout;
    QLabel* resLabel;

    int result;

    
};



class AndGate : public LogicGate
{
    Q_OBJECT
public:
    AndGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a, bool b);
    bool getOutput() const;
    virtual int forCast() {return 1;}
    bool ifInputsAreSet()
    {
        if(inputa->text().isEmpty() || inputb->text().isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void setA(bool a) 
    {
        inputA = a;
        output = inputA && inputB;
        update();
        inputa->setText(QString::number(a ? 1 : 0)); 
        outputy->setText(QString::number(this->getOutput() ? 1 : 0));
    }
    void setB(bool b) 
    {
        inputB = b;
        output = inputA && inputB;
        update(); 
        inputb->setText(QString::number(b ? 1 : 0)); 
        outputy->setText(QString::number(this->getOutput() ? 1 : 0));
    }
    bool inputA = false;
    bool inputB = false;
    bool output = false;
    QLineEdit* inputa;
    QLineEdit* inputb;
    QLabel* outputy;

public slots:
    void updateOutput(QString);

private:
    
};

class OrGate : public LogicGate
{
    Q_OBJECT
public:
    OrGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a, bool b);
    bool getOutput() const;
    virtual int forCast() {return 2;}
    bool ifInputsAreSet()
    {
        if(inputa->text().isEmpty() || inputb->text().isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void setA(bool a) 
    {
        inputA = a;
        output = inputA || inputB;
        update();
        inputa->setText(QString::number(a ? 1 : 0)); 
        outputy->setText(QString::number(this->getOutput() ? 1 : 0));
    }
    void setB(bool b) 
    {
        inputB = b;
        output = inputA || inputB;
        update(); 
        inputb->setText(QString::number(b ? 1 : 0)); 
        outputy->setText(QString::number(this->getOutput() ? 1 : 0));
    }

    bool inputA = false;
    bool inputB = false;
    bool output = false;
    QLineEdit* inputa;
    QLineEdit* inputb;
    QLabel* outputy;

public slots:
    void updateOutput(QString);

private:
};

class NotGate : public LogicGate
{
    Q_OBJECT
public:
    NotGate(QGraphicsItem* parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setInputs(bool a);
    bool getOutput() const;
    virtual int forCast() {return 3;}
    bool ifInputsAreSet()
    {
        if(inputa->text().isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void setA(bool a) 
    {
        inputA = a;
        output = !inputA;
        update();
        inputa->setText(QString::number(a ? 1 : 0)); 
        outputy->setText(QString::number(this->getOutput() ? 1 : 0));
    }


public slots:
    void updateOutput(QString);

private:
    bool inputA = false;
    bool output = false;
    QLineEdit* inputa;
    QLabel* outputy;
};



#endif // WINDOW_H
