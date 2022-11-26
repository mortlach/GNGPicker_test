#ifndef PHRASE_UNIQUE_WORD_MODELVIEW_WIDGET_H
#define PHRASE_UNIQUE_WORD_MODELVIEW_WIDGET_H

#include <QWidget>
#include <QItemSelection>
#include <QAbstractButton>
#include <QSortFilterProxyModel>
#include "phrase_unique_words_model.h"
#include "phrase_unique_words_filtermodel.h"
#include "gng_phrase.h"
#include "gng_phrase_word.h"
#include "rune_cut_selector.h"

namespace Ui {class PhraseUniqueWordModelViewWIdget;}
class PhraseUniqueWordModelViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PhraseUniqueWordModelViewWidget(unsigned int word_index,
                                             QWidget *parent = nullptr);
    ~PhraseUniqueWordModelViewWidget();
    bool setNewWord(unsigned int index);
    void setLabel(const QString& s);
    void setLabel();
    void update();
    void updateLabel();
    void updateTable();

    void resizeToContents();

    void beginResetModel(){ model.beginResetModel(); }
    void endResetModel(){ model.beginResetModel(); }
    void allWidgetsEnabled(bool value);

public slots:
    void on_tableView_customContextMenuRequested();
    void on_tableView_left_doubleclick_sig();
    void on_tableView_space_bar_sig();
    void on_savePushButton_clicked();
    void on_loadPushButton_clicked();
    void on_findPushButton_clicked();
    void on_delPushButton_clicked();

public: signals:
    void phraseWordDataChanged();

friend class PhraseUniqueWordsTab;

private:
    Ui::PhraseUniqueWordModelViewWIdget *ui;
    RuneCutSelector* runeCutSelector;
    QItemSelectionModel* puw_selectionmodel;
    PhraseUniqueWordsFilterModel* puw_sortfilterproxymodel;
    GNGPhrase gng_phrase;
    GNGPhraseWord* gng_phrase_word;
    PhraseUniqueWordsModel model;
    unsigned int word_index;
    void applyFilter(int a);
};

#endif // PHRASE_UNIQUE_WORD_MODELVIEW_WIDGET_H
