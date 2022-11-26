#ifndef ONE_GRAM_MODEL_VIEW_WIDGET_H
#define ONE_GRAM_MODEL_VIEW_WIDGET_H

#include <QWidget>
#include <QItemSelection>
#include <QAbstractButton>
#include <QSortFilterProxyModel>
#include "1_grams_model.h"
#include "1_gram_filtermodel.h"
#include "ui_one_gram_model_view_widget.h"
#include "gng_1gram_data.h"
#include <functional>

namespace Ui {
class OneGramModelViewWidget;
}

class OneGramModelViewWidget : public QWidget
{
    /*!
    *  * \brief The OneGramModelViewWidget class
    * widget to display / save data for the RAW 1-gram data set
    */
    Q_OBJECT

public:
    explicit OneGramModelViewWidget(unsigned int ngram_index,
                                    bool use_phrase_1grams,
                                    QWidget *parent = nullptr);
    ~OneGramModelViewWidget();
    /*!
     * \brief setLabel
     * \param s
     */
    void setLabel(const QString& s);
    /*!
     * \brief setLabel
     */
    void setLabel();
    void update();
    void updateLabel();
    void updateTable();
    /*!
     * \brief resizeToContents
     */
    void resizeToContents();

    void beginResetModel(){ model.beginResetModel(); }
    void endResetModel(){ model.endResetModel(); }
    void allWidgetsEnabled(bool value);


public slots:
    void on_tableView_customContextMenuRequested();
    void on_tableView_left_doubleclick_sig();
    void on_tableView_space_bar_sig();
    void on_tableView_f_sig();
    void on_tableView_t_sig();
    void on_savePushButton_clicked();
    void on_loadPushButton_clicked();
    void on_findPushButton_clicked();
    void on_deletePushButton_clicked();

signals:

friend class OneGramTab;
friend class Phrase1GramsTab;

private:
    Ui::OneGramModelViewWidget *ui;
    QItemSelectionModel* onegram_selectionmodel;
    OneGramFilterModel* onegram_sortfilterproxymodel;
    GNG1Grams gng_1grams;
    GNG1GramData* gng_1gram_data;
    OneGramsModel model;
    unsigned int word_length;
    void applyFilter(int a);
    enum Constants
    {
        all_filter = 0,
        chosen_filter = 1,
        not_chosen_filter = 2
    };
    bool using_phrase_1grams;


};

#endif // ONE_GRAM_MODEL_VIEW_WIDGET_H
