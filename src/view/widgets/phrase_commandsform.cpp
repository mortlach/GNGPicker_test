#include "phrase_commandsform.h"
#include "ui_phrase_commandsform.h"

PhraseCommandsForm::PhraseCommandsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhraseCommandsForm)
{
    ui->setupUi(this);
}

PhraseCommandsForm::~PhraseCommandsForm()
{
    delete ui;
}
