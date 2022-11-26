#ifndef NGRAM_TAB_H
#define NGRAM_TAB_H

#include <QWidget>
#include "ngram_model_view_widget.h"
#include "gng_phrase.h"
#include "gng_1grams.h"

namespace Ui {
class NGramTab;
}

class NGramTab : public QWidget
{
    Q_OBJECT

public:
    explicit NGramTab(QWidget *parent = nullptr);
    ~NGramTab();
    bool setNewPhrase();

    void adjustTableSize();
    //void adjustTableSize(unsigned int i);

    void beginReset();
    void endReset();
    void updateWidgets();


    void allWidgetsEnabled(bool value);

private:
    Ui::NGramTab *ui;
    GNGPhrase gng_phrase;
    QList<NgramModelViewWidget*> ngram_mv_widgets;
    void cleanup();

};

#endif // NGRAM_TAB_H
