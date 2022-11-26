#ifndef GNG_DATA_VIEW_H
#define GNG_DATA_VIEW_H
#include <QWidget>
#include <QItemSelection>
#include <QAbstractButton>

namespace Ui {
class GNGDataView;
}

/*!
 * \brief The GNGDataView class
 */
class GNGDataView : public QWidget
{
    Q_OBJECT

public:
    explicit GNGDataView(QWidget *parent = nullptr);
    ~GNGDataView();

//    void setLabel(const QString& s);
//    void setLabel();
//    void resizeToContents();
public slots:
//    void on_tableView_customContextMenuRequested();
//    void on_tableView_left_doubleclick_sig();
//    void on_tableView_space_bar_sig();
//    void on_tableView_f_sig();
//    void on_tableView_t_sig();

//    virtual void test();

//    void on_savePushButton_clicked();
//    void on_loadPushButton_clicked();
//    void on_findPushButton_clicked();
//    void update(); // main update function

signals:
    friend class OneGramTab;

private:
    Ui::GNGDataView *ui;
//    QItemSelectionModel* selectionModel;
//    GNGFilterModel* sortFilterProxyModel;
//    GNGModel* model;
//    GNG1GramData* gng_1gram_data;
//    OneGramsModel model;
//    unsigned int word_length;
//    void applyFilter(int a);
//    enum Constants
//    {
//        all_filter = 0,
//        chosen_filter = 1,
//        not_chosen_filter = 2
//    };
};

#endif // GNG_DATA_VIEW_H
