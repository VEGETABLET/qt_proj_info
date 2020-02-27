#include "levelengine.h"
#include "ui_levelengine.h"

LevelEngine::LevelEngine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LevelEngine)
{
    ui->setupUi(this);
    QPushButton * btn = new QPushButton("btn");
    QVBoxLayout * layout_main = new QVBoxLayout();
    layout_main->addWidget(btn);
    setLayout(layout_main);
}

LevelEngine::~LevelEngine()
{
    delete ui;
}
