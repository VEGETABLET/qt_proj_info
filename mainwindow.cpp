#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    stackedWidget = new QStackedWidget(this); //виджет для манипулирования
    //setCentralWidget(stackedWidget); //

    ui->setupUi(this);

    QResource::registerResource("res.qrc"); // для ресурсов
    /* Подключаю стили */
    f_style.setFileName(":/styles/style_default");
    f_style.open(QFile::ReadOnly);
    str_style = f_style.readAll();
    f_style.close();
    setStyleSheet(str_style);
    /* *************** */
    data_path = "data/"; // для старого файла
    load_home(parent); //загружаю меню
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_home(QWidget * parent)
{
    QVBoxLayout * layout_main = new QVBoxLayout(); //основной layout
     //основной layout
    load_pic(parent, layout_main);
    load_levels(parent, layout_main);
    load_menu(parent, layout_main);
    layout_main->update();
    ui->centralwidget->setLayout(layout_main); //отрисовываю основной layout
    stackedWidget->addWidget(ui->centralwidget);
    stackedWidget->setCurrentIndex(0);
    this->setCentralWidget(stackedWidget);
    //this->setLayout(layout_main);
}

void MainWindow::load_pic(QWidget * parent, QVBoxLayout * layout_main)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    //int height = rec.height(); //высота
    int width = rec.width(); //ширина
    QLabel * label = new QLabel();
    QPixmap pic_menu(":/images/pic_menu");
    double pic_prop = double(pic_menu.height()) / double(pic_menu.width()); //отношение высоты к ширине картинки
    pic_menu = pic_menu.scaled(width / 2, (width * pic_prop) / 2);
    label->setPixmap(pic_menu); //ставлю на label картинку
    layout_main->addWidget(label); //добавляю label с картинкой
}

void MainWindow::load_menu(QWidget * parent, QVBoxLayout * layout_main)
{

    QHBoxLayout * layout_tools_btns = new QHBoxLayout(); //layout с кнопками управления внизу
    layout_tools_btns->setSpacing(15); //пробел между кнопками

    QPushButton * btn_settings = new QPushButton("Настройки", parent);
    QPushButton * btn_documentation = new QPushButton("Документация", parent);
    QPushButton * btn_close = new QPushButton("Выйти", parent);


    connect(btn_settings, SIGNAL(clicked()), this, SLOT(settings()));
    connect(btn_close, SIGNAL(clicked()), this, SLOT(close_window()));
    connect(btn_documentation, SIGNAL(clicked()), this, SLOT(close_window));


    layout_tools_btns->addWidget(btn_documentation); // Добавляю кнопки управления
    layout_tools_btns->addWidget(btn_settings);      // На layout с управлением
    layout_tools_btns->addWidget(btn_close);
    layout_main->addItem(layout_tools_btns); //добавляю layout с кнопками управления на основной layout

    layout_main->update();
}

void MainWindow::load_levels(QWidget * parent, QVBoxLayout * layout_main)
{
    /* Отрисовка меню */
    QGridLayout * layout_levels = new QGridLayout(); //layout c кнопками уровней

    /* В последствие это всё заменит файл стилей */
    layout_levels->setContentsMargins(5, 5, 5, 5); //расстояние от краев со всех сторон
    layout_levels->setSpacing(15); //растояние между кнопками
    /* Эти настройки с layout */
    /* */
    /* Отрисовка меню  кнопками перехода на уровни */
    std::ifstream file(data_path + "levels.data");
    std::string buff;
    QString btn_text, level_file;
    QStringList qbuff;
    for(int i = 0; !file.eof(); i++ )
    {
        for(int j = 0; j < 4 && !file.eof(); j++ )
        {
            getline(file, buff);
            qbuff = QString::fromStdString(buff).split("=");
            btn_text = qbuff[0];
            level_data_map[qbuff[0]] = qbuff[1]; //формат <имя уровня> <папка с файлами уровня>
            QPushButton * btn = new QPushButton(btn_text, parent);      /* Создаю кнопки */
            btn->setCheckable(true);
            connect(btn, SIGNAL(clicked()), this, SLOT(load_level()));
            //ui->layout_grid_levels->addWidget(btn);
            layout_levels->addWidget(btn, i, j); //добавляю в основной layout новый с кнопками
        }
    }
    file.close();
    layout_main->addItem(layout_levels); //добавляю кнопки с уровнями в основной layout
    /* */
    //setLayout(layout_main);
    layout_main->update();
}

void MainWindow::load_level()
{
    QPushButton * btn = (QPushButton *) sender();
    QString str = btn->text();
    std::cout << level_data_map.value(str).toStdString() << std::endl;

    //QVBoxLayout * layout_level = new QVBoxLayout();
    LevelEngine * level = new LevelEngine();
    //QLabel * label = new QLabel();
    stackedWidget->addWidget(level);
    stackedWidget->setCurrentWidget(level);
    //stackedWidget->setCurrentWidget(label);


}

void MainWindow::settings()
{
    //QVBoxLayout * layout_settings = new QVBoxLayout();
/*
    QMenu * menu_theme = new QMenu("Тема"); //выбор темы
    menu_theme->addAction("Тёмная", SLOT(change_theme()));
    menu_theme->addAction("Светлая", SLOT(change_theme()));
    QCheckBox * box_sounds = new QCheckBox("Звук"); //включение/отключение звука
    connect(box_sounds, SIGNAL(stateChanged()), this, SLOT(sound_change()));

    QPushButton * btn_back = new QPushButton("Домой"); //кнопка назад
    connect(btn_back, SIGNAL(clicked()), this, SLOT(load_home()));

    //layout_settings->addWidget(menu_theme);
    //layout_settings->addWidget(box_sounds);
    layout_settings->addWidget(btn_back);

    ui->centralwidget->setLayout(layout_settings); //отрисовываю layout
*/
}

/*  */
void MainWindow::change_theme()
{

}

void MainWindow::sound_changed()
{

}

void MainWindow::documentation_opener()
{

}
/*  */

void MainWindow::close_window()
{
    close();
}
