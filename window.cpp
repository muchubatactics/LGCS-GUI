
//logic Gate Class
// class LogicGate
// {
// public:
//     LogicGate(QString name, int numInputs, int numOutputs)
//         : m_name(name), m_numInputs(numInputs), m_numOutputs(numOutputs)
//     {
//         // Create labels for the gate's inputs and outputs
//         for (int i = 0; i < numInputs; i++)
//         {
//             m_inputLabels.append(new QLabel("0"));
//         }
//         for (int i = 0; i < numOutputs; i++)
//         {
//             m_outputLabels.append(new QLabel("0"));
//         }
//     }
//     QString name() const { return m_name; }

//     // Get the number of inputs and outputs
//     int numInputs() const { return m_numInputs; }
//     int numOutputs() const { return m_numOutputs; }

//     // Get the labels for the inputs and outputs
//     const QList<QLabel*>& inputLabels() const { return m_inputLabels; }
//     const QList<QLabel*>& outputLabels() const { return m_outputLabels; }

// private:
//     // The name of the gate
//     QString m_name;

//     // The number of inputs and outputs
//     int m_numInputs;
//     int m_numOutputs;

//     // Labels for the inputs and outputs
//     QList<QLabel*> m_inputLabels;
//     QList<QLabel*> m_outputLabels;

// };

// void MainWindow::addAndGate()
// {
//     // Create a new AND gate
//     LogicGate* andGate = new LogicGate("AND", 2, 1);
//     // Create a layout for the AND gate
//     QVBoxLayout* gateLayout = new QVBoxLayout();
//     gatesLayout->addLayout(gateLayout);
//     // Add the name of the gate to the layout
//     QLabel* nameLabel = new QLabel(andGate->name());
//     gateLayout->addWidget(nameLabel);
//     // Add the input labels to the layout
//     QHBoxLayout* inputsLayout = new QHBoxLayout();
//     gateLayout->addLayout(inputsLayout);
//     foreach (QLabel* inputLabel, andGate->inputLabels())
//     {
//         inputsLayout->addWidget(inputLabel);
//     }
//     // Add the output labels to the layout
//     QHBoxLayout* outputsLayout = new QHBoxLayout();
//     gateLayout->addLayout(outputsLayout);
//     foreach (QLabel* outputLabel, andGate->outputLabels())
//     {
//         outputsLayout->addWidget(outputLabel);
//     }
// }

// void MainWindow::addOrGate()
// {
//     // Create a new OR gate
//     LogicGate* orGate = new LogicGate("OR", 2, 1);
//     // Create a layout for the OR gate
//     QVBoxLayout* gateLayout = new QVBoxLayout();
//     gatesLayout->addLayout(gateLayout);
//     // Add the name of the gate to the layout
//     QLabel* nameLabel = new QLabel(orGate->name());
//     gateLayout->addWidget(nameLabel);
//     // Add the input labels to the layout
//     QHBoxLayout* inputsLayout = new QHBoxLayout();
//     gateLayout->addLayout(inputsLayout);
//     foreach (QLabel* inputLabel, orGate->inputLabels())
//     {
//         inputsLayout->addWidget(inputLabel);
//     }
//     // Add the output labels to the layout
//     QHBoxLayout* outputsLayout = new QHBoxLayout();
//     gateLayout->addLayout(outputsLayout);
//     foreach (QLabel* outputLabel, orGate->outputLabels())
//     {
//         outputsLayout->addWidget(outputLabel);
//     }   

// }

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
        andGateIcon.load("/home/muchubatactics/ccpp/project/man/1x/and.png");
        orGateIcon.load("/home/muchubatactics/ccpp/project/man/1x/or.png");
        notGateIcon.load("/home/muchubatactics/ccpp/project/man/1x/not.png");


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
    QVBoxLayout* gatelay = new QVBoxLayout;
    QLabel *gatename = new QLabel;
    gatename->setText(andgate->getName());
    gatelay->addWidget(gatename);
    QLineEdit *inputa = new QLineEdit;
    QLineEdit *inputb = new QLineEdit;
    QLabel *outputy = new QLabel;
    gatelay->addWidget(inputa);
    gatelay->addWidget(inputb);
    gatelay->addWidget(outputy);
    gatesLayout->addLayout(gatelay);

    QObject::connect(inputa, &QLineEdit::textChanged, [&]() {
        bool a = (inputa->text() == "1");
        bool b = (inputb->text() == "1");
        andgate->setInputs(a, b);
        outputy->setText(andgate->getOutput() ? "1" : "0");
    });
    QObject::connect(inputb, &QLineEdit::textChanged, [&]() {
        bool a = (inputa->text() == "1");
        bool b = (inputb->text() == "1");
        andgate->setInputs(a, b);
        outputy->setText(andgate->getOutput() ? "1" : "0");
    });



}

void MainWindow::addOrGate()
{
    OrGate* orgate = new OrGate(nullptr);
    scene->addItem(orgate);
    QVBoxLayout* gatelay = new QVBoxLayout;
    QLabel *gatename = new QLabel;
    gatename->setText(orgate->getName());
    gatelay->addWidget(gatename);
    QLineEdit *inputa = new QLineEdit;
    QLineEdit *inputb = new QLineEdit;
    QLabel *outputy = new QLabel;
    gatelay->addWidget(inputa);
    gatelay->addWidget(inputb);
    gatelay->addWidget(outputy);
    gatesLayout->addLayout(gatelay);

}

void MainWindow::addNotGate()
{
    NotGate* notgate = new NotGate(nullptr);
    scene->addItem(notgate);
    QVBoxLayout* gatelay = new QVBoxLayout;
    QLabel *gatename = new QLabel;
    gatename->setText(notgate->getName());
    gatelay->addWidget(gatename);
    QLineEdit *inputa = new QLineEdit;
    QLabel *outputy = new QLabel;
    gatelay->addWidget(inputa);
    gatelay->addWidget(outputy);
    gatesLayout->addLayout(gatelay);

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