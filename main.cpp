#include <QApplication>
#include "window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    
    return app.exec();
}

// #include <QApplication>
// #include <QGraphicsView>
// #include <QGraphicsScene>
// #include <QGraphicsPixmapItem>
// #include <QHBoxLayout>
// #include <QVBoxLayout>
// #include <QPushButton>

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     // Create the main window
//     QWidget *window = new QWidget;
//     window->setWindowTitle("Circuit Designer");

//     // Create a layout for the main window
//     QVBoxLayout *layout = new QVBoxLayout;

//     // Create a canvas area for the circuit
//     QGraphicsView *canvas = new QGraphicsView;
//     QGraphicsScene *scene = new QGraphicsScene;
//     canvas->setScene(scene);
//     layout->addWidget(canvas);

//     // Create icons for the logic gates
//     QPixmap andGateIcon("/home/muchubatactics/ccpp/project/man/1x/and.png");
//     QPixmap orGateIcon("/home/muchubatactics/ccpp/project/man/1x/or.png");
//     QPixmap notGateIcon("/home/muchubatactics/ccpp/project/man/1x/not.png");

//     // Create buttons for adding the logic gates to the canvas
//     QPushButton *addAndGateButton = new QPushButton;
//     addAndGateButton->setIcon(andGateIcon);
//     QPushButton *addOrGateButton = new QPushButton;
//     addOrGateButton->setIcon(orGateIcon);
//     QPushButton *addNotGateButton = new QPushButton;
//     addNotGateButton->setIcon(notGateIcon);

//     // Create a layout for the buttons
//     QHBoxLayout *buttonLayout = new QHBoxLayout;
//     buttonLayout->addWidget(addAndGateButton);
//     buttonLayout->addWidget(addOrGateButton);
//     buttonLayout->addWidget(addNotGateButton);

//     // Add the button layout to the main layout
//     layout->addLayout(buttonLayout);

//     // Set the main layout for the main window
//     window->setLayout(layout);

//     // Connect signals and slots for the buttons
//     QObject::connect(addAndGateButton, &QPushButton::clicked, [=]() {
//         // Add an AND gate to the canvas when the button is clicked
//         QGraphicsPixmapItem *gate = new QGraphicsPixmapItem(andGateIcon);
//         scene->addItem(gate);
//         // Set the gate as draggable
//         gate->setFlag(QGraphicsItem::ItemIsMovable);
//     });
//     QObject::connect(addOrGateButton, &QPushButton::clicked, [=]() {
//         // Add an OR gate to the canvas when the button is clicked
//         QGraphicsPixmapItem *gate = new QGraphicsPixmapItem(orGateIcon);
//         scene->addItem(gate);
//         // Set the gate as draggable
//         gate->setFlag(QGraphicsItem::ItemIsMovable);
//     });
//     QObject::connect(addNotGateButton, &QPushButton::clicked, [=]() {
//         // Add a NOT gate to the canvas when the button is clicked
//         QGraphicsPixmapItem *gate = new QGraphicsPixmapItem(notGateIcon);
//         scene->addItem(gate);
//         // Set the gate as draggable
//         gate->setFlag(QGraphicsItem::ItemIsMovable);
//     });

//     // Show the main window
//     window->show();

//     // Run the application
//     return app.exec();
// }


// #include <QApplication>


// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     // Create the main window
//     QWidget *window = new QWidget;
//     window->setWindowTitle("Logic Gates");

//     // Create the canvas and the AND gate graphics
//     QGraphicsView *canvas = new QGraphicsView;
//     AndGateGraphics *andGate = new AndGateGraphics("1");
//     QGraphicsScene *scene = new QGraphicsScene;
//     scene->addItem(andGate);
//     canvas->setScene(scene);

//     // Create the input line edits and the output label
//     QLineEdit *inputA = new QLineEdit;
//     QLineEdit *inputB = new QLineEdit;
//     QLabel *output = new QLabel;

//     // Set the layout for the main window
//     QVBoxLayout *layout = new QVBoxLayout;
//     layout->addWidget(canvas);
//     layout->addWidget(inputA);
//     layout->addWidget(inputB);
//     layout->addWidget(output);
//     window->setLayout(layout);

//     // Connect the line edits to the AND gate
//     QObject::connect(inputA, &QLineEdit::textChanged, [&]() {
//         bool a = (inputA->text() == "1");
//         bool b = (inputB->text() == "1");
//         andGate->setInputs(a, b);
//         output->setText(andGate->getOutput() ? "1" : "0");
//     });
//     QObject::connect(inputB, &QLineEdit::textChanged, [&]() {
//         bool a = (inputA->text() == "1");
//         bool b = (inputB->text() == "1");
//         andGate->setInputs(a, b);
//         output->setText(andGate->getOutput() ? "1" : "0");
//     });

//     // Show the main window
//     window->show();

//     return app.exec();
// }


