#ifndef PHRASE_1GRAMS_TAB_H
#define PHRASE_1GRAMS_TAB_H
#include <QWidget>
#include "one_gram_model_view_widget.h"

namespace Ui {
class Phrase1GramsTab;
}

class Phrase1GramsTab : public QWidget
{
    Q_OBJECT

public:
    explicit Phrase1GramsTab(QWidget *parent = nullptr);
    ~Phrase1GramsTab();
    void setup();

    void adjustTableSize();
    void adjustTableSize(unsigned int i);

    bool setNewPhrase();

    void beginReset();
    void endReset();
    void updateWidgets();

    void allWidgetsEnabled(bool value);


public slots:
    void on_fontSizeComboBox_currentIndexChanged(int index);
    void on_filterButtonGroup_buttonClicked(QAbstractButton *b);

private:
    Ui::Phrase1GramsTab *ui;
    QList<OneGramModelViewWidget*> ongram_mv_widgets;
    void cleanup();

    GNG1Grams gng_1grams;

};

#endif // PHRASE_1GRAMS_TAB_H
