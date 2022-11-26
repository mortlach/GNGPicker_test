#ifndef NGRAM_MODEL_VIEW_WIDGET_H
#define NGRAM_MODEL_VIEW_WIDGET_H

#include <QWidget>
#include <QItemSelection>
#include <QAbstractButton>
#include "ngram_model.h"
#include "ngram_filtermodel.h"
#include "ui_ngram_model_view_widget.h"
#include "gng_phrase.h"
#include <functional>

namespace Ui {
class NgramModelViewWidget;
}

class NgramModelViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NgramModelViewWidget(unsigned int ngram_index, QWidget* parent = nullptr);
    ~NgramModelViewWidget();
    //inline void setNewPhrase(GNGPhrase& phrase_in){phrase = &phrase_in;}
    //bool setNewNgram(unsigned int index);

    void setLabel(const QString& s);
    void setLabel();
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
    void update(); // main update function
    void updateLabel(); // main update function
    void updateTable(); // main update function

private:
    Ui::NgramModelViewWidget* ui;
    QItemSelectionModel* ngram_selectionmodel;
    NGramFilterModel* ngram_sortfilterproxymodel;
    GNGPhrase gng_phrase;
    GNGNGram* gng_ngram;
    NGramModel model;
    unsigned int ngram_index;
    void applyFilter(int a);
    enum Constants
    {
        all_filter = 0,
        chosen_filter = 1,
        not_chosen_filter = 2
    };

};

#endif // NGRAM_MODEL_VIEW_WIDGET_H
