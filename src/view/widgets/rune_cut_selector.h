#ifndef RUNE_CUT_SELECTOR_H
#define RUNE_CUT_SELECTOR_H

#include <QWidget>
#include <QTextEdit>
#include "gng_phrase.h"
#include "gng_phrase_word.h"
#include "rune_spinbox.h"

namespace Ui {
class RuneCutSelector;
}

class RuneCutSelector : public QWidget
{
    Q_OBJECT

public:
    explicit RuneCutSelector(QWidget *parent = nullptr);
    ~RuneCutSelector();
    void setMyPhrase(GNGPhrase& new_phrase);
    inline void setCutType(const QString& new_type){cut_type = new_type;}
    inline void setMustBe(){ setCutType(must_be);}
    inline void setCouldBeInt(){ setCutType(could_be_int);}
    inline QString getCutType()const{ return cut_type;}
    inline bool isCouldBeInt()const{ return cut_type == could_be_int;}
    inline bool isMustBe()const{ return cut_type == must_be;}
    void setup(unsigned int phrase_word_index);
    void addRuneSpinBoxes();
    QList<QString> getActiveChars();
    void setGui(const QString& data, bool active);
    void setGUiFromPhraseData();

    QList<RuneSpinBox*> mustberune_spinboxes;
    QList<RuneSpinBox*> mayberune_spinboxes;

    bool changeWidth(int i);
    void newRuneCut();

    void toggleApplyButton(bool state);

public slots:
    //void on_activeCheckBox_stateChanged(int state);
    void updateMyPhrase();
    // connect externally when new phrase word index is chosen
    void updatePhraseWordIndex(unsigned int new_index);
    void updateMustBe(int value);
    void updateMaybe(int value);
    void on_applyPushButton_clicked();

public: signals:
    void runeCutSelector();

friend class PhraseUniqueWordModelViewWidget;

private:
    Ui::RuneCutSelector *ui;
    GNGPhrase gng_phrase;
    GNGPhraseWord * my_phrase_unique_word;
//    QButtonGroup* mustBeButtonGroup;
//    QButtonGroup* maybeButtonGroup;
    const QString must_be;
    const QString could_be_int;
    unsigned int current_index;
    QString cut_type; // must_be, could_be_interrupter corresponds to differnt data in my_phrase_unique_word
};

#endif // RUNE_CUT_SELECTOR_H
