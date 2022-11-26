#include "lp_phrase_commands.h"
#include "ui_lp_phrase_commands.h"

LPPhraseCommands::LPPhraseCommands(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LPPhraseCommands)
{
    ui->setupUi(this);
}

LPPhraseCommands::~LPPhraseCommands()
{
    delete ui;
}
