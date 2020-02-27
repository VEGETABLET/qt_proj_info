#ifndef LEVELENGINE_H
#define LEVELENGINE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "string"
#include "fstream"

namespace Ui {
class LevelEngine;
}

class LevelEngine : public QWidget
{
    Q_OBJECT

public:
    explicit LevelEngine(QWidget *parent = nullptr);
    ~LevelEngine();

private:
    Ui::LevelEngine *ui;
};

#endif // LEVELENGINE_H
