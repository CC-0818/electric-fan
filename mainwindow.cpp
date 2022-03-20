#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QMovie>
#include <QByteArray>

#define FANSWITCHYPOS 90
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->hide();
    this->menuBar()->hide();
    setFixedSize(QSize(900, 500));
    fanSwitch = new QPushButton(QString(tr("-")), this);
    fanSwitch->setCheckable(true);
    fanSwitch->setChecked(false);
    fanSwitch->setFixedSize(30, 30);
    fanSwitch->setStyleSheet("QPushButton{background-color: rgba(200, 200, 200, 0.6);color: red;"
                             "border-style: none;"
                             "border-radius: 15px;}"
                             "QPushButton:checked{color: green;}"
                             "QPushButton:hover{background-color: rgba(0, 200, 0, 0.6); color: white;}"
                             "QPushButton:checked:hover{background-color: rgba(200, 0, 0, 0.6); color: white;}"
                             );

    fanSwitch->move(rect().width()/2 - fanSwitch->width() - 40, rect().height()*FANSWITCHYPOS/100 - fanSwitch->height()/2);
    fanLabel = new QLabel(nullptr, this);
    slider = new QSlider(Qt::Horizontal, this);
    slider->move(rect().width()/2, rect().height()*FANSWITCHYPOS/100 - slider->height()/2);
    fanMovie = new QMovie(":/res/electric fan.gif", QByteArray(), this);
    fanMovie->setCacheMode(QMovie::CacheAll);
    fanLabel->resize(rect().width(), rect().height());
    fanMovie->setScaledSize(QSize(fanLabel->size()));
    fanLabel->setMovie(fanMovie);
    fanMovie->start();
    fanMovie->setPaused(true);
    slider->raise();
    fanSwitch->raise();
    slider->setValue(100);
    slider->setMinimum(110);
    slider->setMaximum(200);
    fanMovie->setSpeed(slider->value());

    connect(fanSwitch, &QPushButton::toggled, [=](bool checked) {
        if (checked == true) {
            fanMovie->setPaused(false);
            fanSwitch->setText(tr("O"));
        } else {
            fanMovie->setPaused(true);
            fanSwitch->setText(tr("-"));
        }
    });

    connect(slider, &QSlider::valueChanged, [=](int value) {
        fanMovie->setSpeed(value);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


