#ifndef LP_PHRASE_COMMANDS_H
#define LP_PHRASE_COMMANDS_H

#include <QWidget>

namespace Ui {
class LPPhraseCommands;
}

class LPPhraseCommands : public QWidget
{
    Q_OBJECT

public:
    explicit LPPhraseCommands(QWidget *parent = nullptr);
    ~LPPhraseCommands();

private:
    Ui::LPPhraseCommands *ui;
};

#endif // LP_PHRASE_COMMANDS_H
