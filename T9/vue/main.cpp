#include "texteditor.h"

//#include "../model/dictionary.hpp"
//#include "../model/sentence.hpp"
//#include "../model/word.hpp"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TextEditor *textWindow = new TextEditor;

//    QWidget window;

//    QTextEdit *textBox = new QTextEdit("");

//    QGridLayout *layout = new QGridLayout;
//    layout->addWidget(textBox, 0, 0);

//    window.setLayout(layout);

//    window.show();

//    QWidget textWindow;

//    QPushButton *bouton1 = new QPushButton("Bonjour");

//    QGridLayout *layout = new QGridLayout;
//    layout->addWidget(bouton1, 1, 0);

//    textWindow.setLayout(layout);

    textWindow->show();

    return a.exec();
}
