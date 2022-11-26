#ifndef PHRASE_UNIUQE_WORDS_TAB_H
#define PHRASE_UNIUQE_WORDS_TAB_H
#include <QMainWindow>
#include <QItemSelection>
#include <QAbstractButton>
#include <QSortFilterProxyModel>
#include "gng_phrase.h"
#include "phrase_unique_word_modelview_widget.h"
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui { class PhraseUniqueWordsTab; }
QT_END_NAMESPACE

class PhraseUniqueWordsTab : public QMainWindow
{
    Q_OBJECT
public:
    PhraseUniqueWordsTab(QWidget *parent = nullptr);
    ~PhraseUniqueWordsTab();

    int my_count = 0; // dummy counter for testing

    void setModel(unsigned int word);
    bool setNewPhrase();

    void adjustTableSize();
    void adjustTableSize(unsigned int i);

    void beginReset();
    void endReset();
    void updateWidgets();

    void allWidgetsEnabled(bool value);


public slots:
    void on_phraseWordDataChanged();

signals:
//    void data_changed();
//    void unique_words_data_changed();

private:
    // pointers for QT stuff
    Ui::PhraseUniqueWordsTab* ui;
    QList<PhraseUniqueWordModelViewWidget*> phraseword_mv_widgets;

    GNGPhrase gng_phrase;
    void cleanup();

};
#endif // PHRASE_UNIUQE_WORDS_TAB_H
