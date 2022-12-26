#include "window.h"
#include <iostream>

MainWindow::MainWindow()
{
    // Create a layout for the main window
        mainLayout = new QVBoxLayout(this);

        // Create a toolbar with buttons for adding gates
        toolbarLayout = new QHBoxLayout();
        mainLayout->addLayout(toolbarLayout);

        // Add a button for adding an AND gate
        QPushButton* andButton = new QPushButton("Add AND gate");
        connect(andButton, SIGNAL(clicked()), this, SLOT(addAndGate()));
        toolbarLayout->addWidget(andButton);

        // Add a button for adding an OR gate
        QPushButton* orButton = new QPushButton("Add OR gate");
        connect(orButton, SIGNAL(clicked()), this, SLOT(addOrGate()));
        toolbarLayout->addWidget(orButton);

        // Add a button for adding an NOT gate
        QPushButton* notButton = new QPushButton("Add NOT gate");
        connect(notButton, SIGNAL(clicked()), this, SLOT(addNotGate()));
        toolbarLayout->addWidget(notButton);

        //graphics
        graphicsLayout = new QHBoxLayout;
        canvas = new QGraphicsView;
        scene = new QGraphicsScene;
        canvas->setScene(scene);
        graphicsLayout->addWidget(canvas);
        mainLayout->addLayout(graphicsLayout);

        // Create a layout for the gates
        gatesLayout = new QHBoxLayout();
        mainLayout->addLayout(gatesLayout);

        //icons
        andGateIcon.load(":/1x/and.png");
        orGateIcon.load(":/1x/or.png");
        notGateIcon.load(":/1x/not.png");


        //setting icons
        andButton->setIcon(andGateIcon);
        orButton->setIcon(orGateIcon);
        notButton->setIcon(notGateIcon);



        // Add some initial gates to the layout
        // addAndGate();
        // addOrGate();
}

void MainWindow::addAndGate()
{
    AndGate* andgate = new AndGate(nullptr);
    scene->addItem(andgate);
    gatesLayout->addLayout(andgate->getlayout());

}

void MainWindow::addOrGate()
{
    OrGate* orgate = new OrGate(nullptr);
    scene->addItem(orgate);
    gatesLayout->addLayout(orgate->getlayout());

}

void MainWindow::addNotGate()
{
    NotGate* notgate = new NotGate(nullptr);
    scene->addItem(notgate);
    gatesLayout->addLayout(notgate->getlayout());

}

int LogicGate::ExistingGates = 0;

LogicGate::LogicGate(QGraphicsItem* parent = nullptr) : QGraphicsItem(parent)
{
    ExistingGates++;
    Name = QString::number(ExistingGates);
}

void LogicGate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        moving = true;
        lastMousePos = event->pos();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void LogicGate::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (moving)
    {
        QPointF delta = event->pos() - lastMousePos;
        setPos(pos() + delta);
        lastMousePos = event->pos();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void LogicGate::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        moving = false;
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

QRectF LogicGate::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}

AndGate::AndGate(QGraphicsItem *parent) : LogicGate(parent)
{
    gatelay = new QVBoxLayout;
    gatename = new QLabel;
    gatename->setText(this->getName());
    gatelay->addWidget(gatename);
    inputa = new QLineEdit;
    inputb = new QLineEdit;
    outputy = new QLabel;
    gatelay->addWidget(inputa);
    gatelay->addWidget(inputb);
    gatelay->addWidget(outputy);


    QObject::connect(inputa, SIGNAL(textChanged(QString)), this, SLOT(updateOutput(QString)));
    QObject::connect(inputb, SIGNAL(textChanged(QString)), this, SLOT(updateOutput(QString)));

}

void AndGate::updateOutput(QString)
{
    bool a = (inputa->text() == "1");
    bool b = (inputb->text() == "1");
    this->setInputs(a,b);
    outputy->setText(this->getOutput() ? "1" : "0");

}
void AndGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //AND gate symbol
    painter->drawRect(-30, -30, 60, 60);
    painter->drawText(-16, 5, "AND " + Name );
    //inputs and outputs of the AND gate
    painter->drawLine(-45, -25, -30, -25);
    painter->drawText(-50, -21, "A");
    painter->drawLine(-45, 25, -30, 25);
    painter->drawText(-50, 29, "B");
    painter->drawLine(30, 0, 45, 0);
    painter->drawText(45, 4, "Y");
}

void AndGate::setInputs(bool a, bool b)
{
    inputA = a;
    inputB = b;
    output = inputA && inputB;
    update();
}

bool AndGate::getOutput() const
{
    return output;
}

OrGate::OrGate(QGraphicsItem *parent = nullptr) : LogicGate(parent)
{
    gatelay = new QVBoxLayout;
    gatename = new QLabel;
    gatename->setText(this->getName());
    gatelay->addWidget(gatename);
    inputa = new QLineEdit;
    inputb = new QLineEdit;
    outputy = new QLabel;
    gatelay->addWidget(inputa);
    gatelay->addWidget(inputb);
    gatelay->addWidget(outputy);

    QObject::connect(inputa, SIGNAL(textChanged(QString)), this, SLOT(updateOutput(QString)));
    QObject::connect(inputb, SIGNAL(textChanged(QString)), this, SLOT(updateOutput(QString)));

}

void OrGate::updateOutput(QString)
{
    bool a = (inputa->text() == "1");
    bool b = (inputb->text() == "1");
    this->setInputs(a,b);
    outputy->setText(this->getOutput() ? "1" : "0");

}

void OrGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //OR gate symbol
    painter->drawRect(-30, -30, 60, 60);
    painter->drawText(-14, 5, "OR " + Name );
    //inputs and outputs of the OR gate
    painter->drawLine(-45, -25, -30, -25);
    painter->drawText(-50, -21, "A");
    painter->drawLine(-45, 25, -30, 25);
    painter->drawText(-50, 29, "B");
    painter->drawLine(30, 0, 45, 0);
    painter->drawText(45, 4, "Y");
}

void OrGate::setInputs(bool a, bool b)
{
    inputA = a;
    inputB = b;
    output = inputA || inputB;
    update();
}

bool OrGate::getOutput() const
{
    return output;
}

NotGate::NotGate(QGraphicsItem *parent = nullptr) : LogicGate(parent)
{
    gatelay = new QVBoxLayout;
    gatename = new QLabel;
    gatename->setText(this->getName());
    gatelay->addWidget(gatename);
    inputa = new QLineEdit;
    outputy = new QLabel;
    gatelay->addWidget(inputa);
    gatelay->addWidget(outputy);

    QObject::connect(inputa, SIGNAL(textChanged(QString)), this, SLOT(updateOutput(QString)));

}

void NotGate::updateOutput(QString)
{
    bool a = (inputa->text() == "1");
    this->setInputs(a);
    outputy->setText(this->getOutput() ? "1" : "0");

}

void NotGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //OR gate symbol
    painter->drawRect(-30, -30, 60, 60);
    painter->drawText(-16, 5, "NOT " + Name );
    //inputs and outputs of the OR gate
    painter->drawLine(-45, 0, -30, 0);
    painter->drawText(-50, 4, "A");
    painter->drawLine(30, 0, 45, 0);
    painter->drawText(45, 4, "Y");
}

void NotGate::setInputs(bool a)
{
    inputA = a;
    output = !inputA;
    update();
}

bool NotGate::getOutput() const
{
    return output;
}
