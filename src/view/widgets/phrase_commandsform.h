#ifndef PHRASE_COMMANDSFORM_H
#define PHRASE_COMMANDSFORM_H

#include <QWidget>

namespace Ui {
class PhraseCommandsForm;
}

class PhraseCommandsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PhraseCommandsForm(QWidget *parent = nullptr);
    ~PhraseCommandsForm();

private:
    Ui::PhraseCommandsForm *ui;
};

#endif // PHRASE_COMMANDSFORM_H
