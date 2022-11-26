#include "phrase_1grams_tab.h"
#include "ui_phrase_1grams_tab.h"

Phrase1GramsTab::Phrase1GramsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Phrase1GramsTab)
{
    ui->setupUi(this);
}

Phrase1GramsTab::~Phrase1GramsTab()
{
    delete ui;
}
