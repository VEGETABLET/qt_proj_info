#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QFile>
#include "string"
#include "fstream"
#include "iostream"
#include <QResource>
#include <QLabel>
#include <QDesktopWidget>
#include <QStackedWidget>
//#include <QStackedLayout>
#include <QGuiApplication>
#include <levelengine.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void load_levels(QWidget * parent, QVBoxLayout * layout_main);
    void load_menu(QWidget * parent, QVBoxLayout * layout_main);
    void set_style();
    void load_home(QWidget * parent);
    void load_pic(QWidget * parent, QVBoxLayout * layout_main);

private:
    Ui::MainWindow *ui;
    std::string data_path;
    QMap <QString, QString> level_data_map;
    QString str_style;
    QFile f_style;
    QStackedWidget * stackedWidget;

private slots:
    void load_level();
    void settings();
    void documentation_opener();
    void close_window();
    void change_theme();
    void sound_changed();

};
#endif // MAINWINDOW_H
