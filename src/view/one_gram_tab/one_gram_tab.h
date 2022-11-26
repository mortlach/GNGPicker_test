#ifndef ONE_GRAM_TAB_H
#define ONE_GRAM_TAB_H

#include <QWidget>
#include "one_gram_model_view_widget.h"
#include "gng_1grams.h"


namespace Ui {
class OneGramTab;
}

class OneGramTab : public QWidget
{
    Q_OBJECT

public:
    explicit OneGramTab(QWidget *parent = nullptr);
    ~OneGramTab();
    void setup();

    void adjustTableSize();
    void adjustTableSize(unsigned int i);

    void beginReset();
    void endReset();

    void allWidgetsEnabled(bool value);


public slots:
    void on_fontSizeComboBox_currentIndexChanged(int index);
    void on_filterButtonGroup_buttonClicked(QAbstractButton *b);

private:
    Ui::OneGramTab *ui;
    QList<OneGramModelViewWidget*> ongram_mv_widgets;
    void cleanup();

    GNG1Grams gng_1grams;

};

#endif // ONE_GRAM_TAB_H
