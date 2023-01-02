#include "window.h"
#include <iostream>
#include <exception>


QGraphicsView* MainWindow::canvas;
QGraphicsScene* MainWindow::scene;
QVector<LogicGate*> LogicGate::gates;

MainWindow::MainWindow()
{

    result = - 1;
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
    canvas->setMouseTracking(true);
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

    //drawing
    drawButton = new QPushButton("Draw");
    drawButton->setCheckable(true);
    //QObject::connect(drawButton, &QPushButton::clicked, [&](){drawButton->setChecked(!drawButton->isChecked());});
    toolbarLayout->addWidget(drawButton);
    Draw::setButton(drawButton);
    draw = new Draw(nullptr);


    //simulation
    simButton = new QPushButton("Simulate");
    connect(simButton, SIGNAL(clicked()), this, SLOT(simulate()));
    toolbarLayout->addWidget(simButton);
    simLayout = new QHBoxLayout;
    mainLayout->addLayout(simLayout);
    resLabel = new QLabel;
    resLabel->setText("RESULT: " + QString::number(result));
    simLayout->addWidget(resLabel);

    // Add some initial gates to the layout
    // addAndGate();
    // addOrGate();
}
QPushButton* Draw::button;

void MainWindow::simulate()
{
    const std::type_info& and_type = typeid(AndGate*);
    const std::type_info& or_type = typeid(OrGate*);
    const std::type_info& not_type = typeid(NotGate*);

    std::sort(LogicGate::gates.begin(), LogicGate::gates.end(), [](const LogicGate* a, const LogicGate* b){
        return a->pos().x() < b->pos().x();
    });

    QVector<Draw*> overlaps;

    for(LogicGate* b : LogicGate::gates)
    {
        //if its the final gate
        if(b == LogicGate::gates.last())
        {
            if(dynamic_cast<AndGate*>(b))
            {
                AndGate* res = dynamic_cast<AndGate*>(b);
                result = res->getOutput() ? 1 : 0;
                resLabel->setText("RESULT: " + QString::number(result));
                
            }
            if(dynamic_cast<OrGate*>(b))
            {
                OrGate* res = dynamic_cast<OrGate*>(b);
                result = res->getOutput() ? 1 : 0;
                qDebug() << result;
                resLabel->setText("RESULT: " + QString::number(result));
            }
            if(dynamic_cast<NotGate*>(b))
            {
                NotGate* res = dynamic_cast<NotGate*>(b);
                result = res->getOutput() ? 1 : 0;
                resLabel->setText("RESULT: " + QString::number(result));
            }
            return;
        }

        for(Draw* a : Draw::allPaths)
        {
            if(Draw::pathWithInregion(b, a->getPath()))
            {
                overlaps.append(a);
            }
        }
        if(overlaps.length() == 1)
        {
            if(AndGate* res = dynamic_cast<AndGate*>(b))
            {
                qDebug() << "and " + res->getName();
                qDebug() << res->inputA;
                qDebug() << res->inputB;
                qDebug() << res->getOutput();
                if(res->ifInputsAreSet())
                {
                    for(LogicGate* c : LogicGate::gates)
                    {
                        if( c == b)
                        {
                            continue;
                        }
                        if(Draw::pathWithInregion(c, overlaps[0]->getPath()))
                        {
                            if(AndGate* res1 = dynamic_cast<AndGate*>(c))
                            {
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                                if(res1->setTest == 1)
                                {
                                    res1->setB(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            if(OrGate* res1 = dynamic_cast<OrGate*>(c))
                            {
                                if(res1->setTest == 0)
                                {
                                    qDebug() << res->getOutput();
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                                if(res1->setTest == 1)
                                {
                                    qDebug() << res->getOutput();
                                    res1->setB(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            if(NotGate* res1 = dynamic_cast<NotGate*>(c))
                            {
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            
                        }
                    }
                }

            }
            if(dynamic_cast<OrGate*>(b))
            {
                OrGate* res = dynamic_cast<OrGate*>(b);
                if(res->ifInputsAreSet())
                {
                    for(LogicGate* c : LogicGate::gates)
                    {
                        if( c == b)
                        {
                            continue;
                        }
                        if(Draw::pathWithInregion(c, overlaps[0]->getPath()))
                        {
                            if(dynamic_cast<AndGate*>(c))
                            {
                                AndGate* res1 = dynamic_cast<AndGate*>(c);
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                                if(res1->setTest == 1)
                                {
                                    res1->setB(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                                
                            }
                            if(dynamic_cast<OrGate*>(c))
                            {
                                OrGate* res1 = dynamic_cast<OrGate*>(c);
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                                if(res1->setTest == 1)
                                {
                                    res1->setB(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            if(dynamic_cast<NotGate*>(c))
                            {
                                NotGate* res1 = dynamic_cast<NotGate*>(c);
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            
                        }
                    }
                }
                
            }
            if(dynamic_cast<NotGate*>(b))
            {
                NotGate* res = dynamic_cast<NotGate*>(b);
                if(res->ifInputsAreSet())
                {
                    for(LogicGate* c : LogicGate::gates)
                    {
                        if(c == b)
                        {
                            continue;
                        }
                        if(Draw::pathWithInregion(c, overlaps[0]->getPath()))
                        {
                            if(dynamic_cast<AndGate*>(c))
                            {
                                AndGate* res1 = dynamic_cast<AndGate*>(c);
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                                if(res1->setTest == 1)
                                {
                                    res1->setB(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            if(dynamic_cast<OrGate*>(c))
                            {
                                OrGate* res1 = dynamic_cast<OrGate*>(c);
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                                if(res1->setTest == 1)
                                {
                                    res1->setB(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            if(dynamic_cast<NotGate*>(c))
                            {
                                NotGate* res1 = dynamic_cast<NotGate*>(c);
                                if(res1->setTest == 0)
                                {
                                    res1->setA(res->getOutput());
                                    res1->setTest++;
                                    break;
                                }
                            }
                            
                        }
                    }
                }
                
            }

        }
        if(overlaps.length() == 2)
        {
            //if it overlaps with only 2 paths then its a not gate or a final gate, but we already have a test for final gate;
            NotGate* res = dynamic_cast<NotGate*>(b);
            std::sort(overlaps.begin(), overlaps.end(), [](const Draw* a, const Draw* b){
                return a->getPath()->boundingRect().x() < b->getPath()->boundingRect().x();
            });
            for(LogicGate* c : LogicGate::gates)
            {
                if(c == b)
                {
                    continue;
                }
                if(Draw::pathWithInregion(c,overlaps.last()->getPath()))
                {
                    if(dynamic_cast<AndGate*>(c))
                    {
                        AndGate* res1 = dynamic_cast<AndGate*>(c);
                        if(res1->setTest == 0)
                        {
                            res1->setA(res->getOutput());
                            res1->setTest++;
                            break;
                        }
                        if(res1->setTest == 1)
                        {
                            res1->setB(res->getOutput());
                            res1->setTest++;
                            break;
                        }
                    }
                    if(dynamic_cast<OrGate*>(c))
                    {
                        OrGate* res1 = dynamic_cast<OrGate*>(c);
                        if(res1->setTest == 0)
                        {
                            res1->setA(res->getOutput());
                            res1->setTest++;
                            break;
                        }
                        if(res1->setTest == 1)
                        {
                            res1->setB(res->getOutput());
                            res1->setTest++;
                            break;
                        }
                        
                    }
                    if(dynamic_cast<NotGate*>(c))
                    {
                        NotGate* res1 = dynamic_cast<NotGate*>(c);
                        if(res1->setTest == 0)
                        {
                            res1->setA(res->getOutput());
                            res1->setTest++;
                            break;
                        }
                    }                            
                }
            }
            
    
        }
        if(overlaps.length() == 3)
        {
            std::sort(overlaps.begin(), overlaps.end(), [](const Draw* a, const Draw* b){
                return a->getPath()->boundingRect().x() < b->getPath()->boundingRect().x();
            });
            if(dynamic_cast<AndGate*>(b))
            {
                AndGate* res = dynamic_cast<AndGate*>(b);
                for(LogicGate* c : LogicGate::gates)
                {
                    if(c == b)
                    {
                        continue;
                    }
                    if(Draw::pathWithInregion(c, overlaps.last()->getPath()))
                    {
                        if(dynamic_cast<AndGate*>(c))
                        {
                            AndGate* res1 = dynamic_cast<AndGate*>(c);
                            if(res1->setTest == 0)
                            {
                                res1->setA(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                            if(res1->setTest == 1)
                            {
                                res1->setB(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                            
                        }
                        if(dynamic_cast<OrGate*>(c))
                        {
                            OrGate* res1 = dynamic_cast<OrGate*>(c);
                            if(res1->setTest == 0)
                            {
                                res1->setA(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                            if(res1->setTest == 1)
                            {
                                res1->setB(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                            
                        }
                        if(dynamic_cast<NotGate*>(c))
                        {
                            NotGate* res1 = dynamic_cast<NotGate*>(c);
                            if(res1->setTest == 0)
                            {
                                res1->setA(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                        }                            
                    }
                }

            }
            if(dynamic_cast<OrGate*>(b))
            {
                OrGate* res = dynamic_cast<OrGate*>(b);
                for(LogicGate* c : LogicGate::gates)
                {
                    if(c == b)
                    {
                        continue;
                    }
                    if(Draw::pathWithInregion(c, overlaps.last()->getPath()))
                    {
                        if(dynamic_cast<AndGate*>(c))
                        {
                            AndGate* res1 = dynamic_cast<AndGate*>(c);
                            if(res1->setTest == 0)
                            {
                                res1->setA(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                            if(res1->setTest == 1)
                            {
                                res1->setB(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                          
                        }
                        if(dynamic_cast<OrGate*>(c))
                        {
                            OrGate* res1 = dynamic_cast<OrGate*>(c);
                            if(res1->setTest == 0)
                            {
                                res1->setA(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                            if(res1->setTest == 1)
                            {
                                res1->setB(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                          
                        }
                        if(dynamic_cast<NotGate*>(c))
                        {
                            NotGate* res1 = dynamic_cast<NotGate*>(c);
                            if(res1->setTest == 0)
                            {
                                res1->setA(res->getOutput());
                                res1->setTest++;
                                break;
                            }
                        }                            
                    }
                }

            }
        }
        overlaps.clear();
    }


    for(auto a : LogicGate::gates)
    {
        if(AndGate* res = dynamic_cast<AndGate*>(a))
        {
            res->setTest = 0;
        }
        if(OrGate* res = dynamic_cast<OrGate*>(a))
        {
            res->setTest = 0;
        }
        if(NotGate* res = dynamic_cast<NotGate*>(a))
        {
            res->setTest = 0;        
        }

    }

    
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
    setTest = 0;
    ExistingGates++;
    Name = QString::number(ExistingGates);
}

void LogicGate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if (event->button() == Qt::LeftButton && !Draw::button->isChecked())
    {
        moving = true;
        lastMousePos = event->pos();
        event->accept();
    }
    else
    {
        event->ignore();
    }
    update();
}

void LogicGate::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    if (moving)
    {
        QPointF delta = event->pos() - lastMousePos;
        this->setPos(this->pos() + delta);
        lastMousePos = event->pos();
        event->accept();
    }
    else
    {
        event->ignore();
    }
    update();
}

void LogicGate::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton && !Draw::button->isChecked())
    {
        moving = false;
        event->accept();
    }
    else
    {
        event->ignore();
    }
    update();
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

    gates.append(this);

}

void AndGate::updateOutput(QString)
{
    bool a = (inputa->text() == "1");
    bool b = (inputb->text() == "1");
    this->setInputs(a,b);
    outputy->setText(this->getOutput() ? "1" : "0");
    update();

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
    return inputA && inputB;
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
    gates.append(this);

}

void OrGate::updateOutput(QString)
{
    bool a = (inputa->text() == "1");
    bool b = (inputb->text() == "1");
    this->setInputs(a,b);
    outputy->setText(this->getOutput() ? "1" : "0");
    update();

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
    return inputA || inputB;
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
    gates.append(this);

}

void NotGate::updateOutput(QString)
{
    bool a = (inputa->text() == "1");
    this->setInputs(a);
    outputy->setText(this->getOutput() ? "1" : "0");
    update();

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
    return !inputA;
}


//drawing
QVector<Draw*> Draw::allPaths;

Draw::Draw(QGraphicsItem* parent = nullptr) : QGraphicsItem(parent)
{
    currentPath = new QPainterPath;
    MainWindow::scene->addItem(this);
} 

QRectF Draw::boundingRect() const
{
    return QRectF(0, 0, 1920, 1080);
}

void Draw::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)
{
    QPen pen;
    pen.setWidth(5);
    painter->setPen(pen);
    for(Draw* path : allPaths)
    {
        painter->drawPath(*path->getPath());
    }
}

void Draw::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(button->isChecked())
    {
        Draw* newPath = new Draw(nullptr);
        allPaths.append(newPath);
        newPath->currentPath->moveTo(event->pos());
        update();    
    }
}


void Draw::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(button->isChecked())
    {
        Draw* currentPath = allPaths.last();
        currentPath->currentPath->lineTo(event->pos());
        update();
    }
}

void Draw::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if(button->isChecked())
    {
        update();
    }
}

void Draw::setButton(QPushButton* bb)
{
    button = bb;
}


void Draw::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout << "\nDouble click\n";
    QList<QGraphicsView*> views = this->scene()->views();
    QGraphicsView *view = views.first();
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);
    QGraphicsItem *item = this->scene()->itemAt(view->mapToScene(event->pos().toPoint()), view->transform());
    if(item && qgraphicsitem_cast<QGraphicsPathItem*>(item))
    {
        std::cout << "\neh\n";
        for(int i = 0; i < allPaths.size(); i++)
        {
            if(qgraphicsitem_cast<QGraphicsPathItem*>(item) == qgraphicsitem_cast<QGraphicsPathItem*>(allPaths[i]))
            {
                allPaths.remove(i);
                break;
            }
        }
        this->scene()->removeItem(item);
        this->update();
    }
}


QPainterPath* Draw::getPath() const
{
    return currentPath;
}


QList<QGraphicsItem *> Draw::overlappedGates(QGraphicsScene* scene)
{
    QList<QGraphicsItem* > theList;
    for(Draw* path : allPaths)
    {
        QList<QGraphicsItem *> temp = scene->items(*path->getPath());
        std::cout << "\nerere "<< temp.length() << "\n";
        for(QGraphicsItem* item : temp)
        {
            theList.append(item);
    
        }
    }

    return theList;

}

bool Draw::pathWithInregion(QGraphicsItem* item, QPainterPath* path)
{
    QRegion a(QRect(item->pos().x() - 50, item->pos().y() - 50, 100, 100));
    QPoint b = path->pointAtPercent(0).toPoint();
    QPoint c = path->pointAtPercent(1).toPoint();
    if(a.contains(b) || a.contains(c))
    {
        return true;
    }
    else
    {
        return false;
    }
}
