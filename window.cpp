#include "window.h"
#include "helper.cpp"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    moveInput = new QLineEdit;
    moveButton = new QPushButton("Move");

    //pre-set a partition in it
    std::string input = "13 5 4 3 1";

    std::vector<int> inputVec = Helper::inputParser(input);
    int inputInt = inputVec[0];
    inputVec.erase(inputVec.begin());

    part = new Partition(inputInt, inputVec);
    Partition* after_move = new Partition(part->move(2,4));
    std::cout << after_move->getLength() << std::endl;
    QTableWidget* table = after_move->makeTable();

    QGroupBox* group_one = new QGroupBox(tr("Integer Partitions"));
    QGroupBox* group_two = new QGroupBox(tr("Transformations"));

    QVBoxLayout* left_lay = new QVBoxLayout;
    QVBoxLayout* right_lay = new QVBoxLayout;

    left_lay->addWidget(part->makeTable());
    left_lay->addWidget(table);
    right_lay->addWidget(moveButton);
    right_lay->addWidget((QWidget* )moveInput);

    group_one->setLayout(left_lay);
    group_two->setLayout(right_lay);

    QHBoxLayout* main_lay = new QHBoxLayout;
    main_lay -> addWidget(group_one);
    main_lay -> addWidget(group_two);

    setLayout(main_lay);

    connect(moveButton, SIGNAL(clicked()), SLOT(slotMoveExtractInput()));
}



void Window::slotMoveExtractInput()
{
    QString* tempInput = new QString(moveInput->text());
    std::cout << tempInput->toStdString() << std::endl;
}
