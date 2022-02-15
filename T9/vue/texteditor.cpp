#include "texteditor.h"


TextEditor::TextEditor() : QWidget()
{
    globalLayout = new QGridLayout;

    // Setting the TextBox
    textBox = new QGroupBox;
    textBoxLayout = new QGridLayout;
    text = new TextDisplayer("../../../../model/WordList/fr_sans_accents.txt");
    textBoxLayout->addWidget(text, 0, 0);
    textBox->setLayout(textBoxLayout);

    globalLayout->addWidget(textBox, 0, 0);

    // Setting the arrows for the cursor
    textArrows = new CursorArrows;
    globalLayout->addWidget(textArrows, 1, 0);


    // Setting the Keyboard configuration
    keyBoardBox = new QGroupBox;
    keyBoardBoxLayout = new QGridLayout;

    QString alphabet[9] = {"abc", "def", "ghi", "jkl", "mno", "pqr", "stu", "vwx","yz"};
    for (int i=1; i<10; i++) {
        keyBoard[i] = new QPushButton(QString::number(i)+"\n"+alphabet[i-1]);
        keyBoardBoxLayout->addWidget(keyBoard[i], ((i-1)/3)+1, (i-1)%3);
    }
    keyBoard[0] = new QPushButton("0\n.!?"); keyBoardBoxLayout->addWidget(keyBoard[0], 4, 1);
    keyBoard[0]->setEnabled(false);
    keyBoard[10] = new QPushButton("⇧\nMaj"); keyBoardBoxLayout->addWidget(keyBoard[10], 4, 0);
    keyBoard[10]->setEnabled(false);  // Not functional for now
    keyBoard[11] = new QPushButton("⌫\nDel"); keyBoardBoxLayout->addWidget(keyBoard[11], 4, 2);

    // Linking the buttons with the keyboard
    keyBoard[1]->setShortcut(Qt::Key_1);
    keyBoard[2]->setShortcut(Qt::Key_2);
    keyBoard[3]->setShortcut(Qt::Key_3);
    keyBoard[4]->setShortcut(Qt::Key_4);
    keyBoard[5]->setShortcut(Qt::Key_5);
    keyBoard[6]->setShortcut(Qt::Key_6);
    keyBoard[7]->setShortcut(Qt::Key_7);
    keyBoard[8]->setShortcut(Qt::Key_8);
    keyBoard[9]->setShortcut(Qt::Key_9);
    keyBoard[0]->setShortcut(Qt::Key_0);
    keyBoard[10]->setShortcut(Qt::Key_Shift);
    keyBoard[11]->setShortcut(Qt::Key_Backspace);

    keyBoardBox->setLayout(keyBoardBoxLayout);
    globalLayout->addWidget(keyBoardBox,2,0);


    // Setting the Selector
    selectorBox = new QGroupBox;
    selectorBoxLayout = new QGridLayout;

    wordChoicesBox = new QGroupBox;
    wordChoicesBoxLayout = new QGridLayout;
    wordChoices = new WordChoiceDisplayer;
    wordChoicesBoxLayout->addWidget(wordChoices, 0,0);
    wordChoicesBox->setLayout(wordChoicesBoxLayout);
    selectorBoxLayout->addWidget(wordChoicesBox,0,0);

    arrows = new Selector;
    selectorBoxLayout->addWidget(arrows, 1, 0);

    selectorBox->setLayout(selectorBoxLayout);
    globalLayout->addWidget(selectorBox,0,1,3,1);

    setLayout(globalLayout);


    // Connect signals and slots for the keyBoard
    for (int i=1; i<10; i++) {
    QObject::connect(keyBoard[i], SIGNAL(QPushButton::clicked), text, SLOT([=]() { text->addDigit(i); }));
    }
    QObject::connect(keyBoard[11], SIGNAL(QPushButton::clicked), text, SLOT(TextDisplayer::rmDigit));
    QObject::connect(keyBoard[0], SIGNAL(QPushButton::clicked), wordChoices, SLOT(WordChoiceDisplayer::displayPunctuation));

    QObject::connect(wordChoices, SIGNAL(WordChoiceDisplayer::newPunctuationSelected), text, SLOT(TextDisplayer::addPunctuation));

    QObject::connect(text, SIGNAL(TextDisplayer::enablePunctuation), keyBoard[0], SLOT([=]() { keyBoard[0]->setEnabled(true); }));
    QObject::connect(text, SIGNAL(TextDisplayer::disablePunctuation), keyBoard[0], SLOT([=]() { keyBoard[0]->setEnabled(false); }));

    QObject::connect(text, SIGNAL(TextDisplayer::newDigitSequence), wordChoices, SLOT(WordChoiceDisplayer::getNewWord));

    QObject::connect(textArrows, SIGNAL(CursorArrows::pressedLeft), text, SLOT(TextDisplayer::moveLeft));
    QObject::connect(textArrows, SIGNAL(CursorArrows::pressedRight), text, SLOT(TextDisplayer::moveRight));

    QObject::connect(arrows, SIGNAL(Selector::pressedUp), wordChoices, SLOT(WordChoiceDisplayer::moveUp));
    QObject::connect(arrows, SIGNAL(Selector::pressedDown), wordChoices, SLOT(WordChoiceDisplayer::moveDown));

    QObject::connect(arrows, SIGNAL(Selector::pressedSelect), wordChoices, SLOT(WordChoiceDisplayer::select));
    QObject::connect(wordChoices, SIGNAL(WordChoiceDisplayer::newWordSelected), text, SLOT(TextDisplayer::addWord));
}
