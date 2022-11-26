#ifndef GNG_FILTERMODEL_H
#define GNG_FILTERMODEL_H

#include <QSortFilterProxyModel>

class GNGFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    GNGFilterModel(QObject* parent = nullptr);
    bool filterAcceptsRow(int source_row,const QModelIndex &source_parent) const;
    void setFilter(const QString &s){
        filter_mode.clear();
        filter_mode = s;
        invalidateFilter();
    }
    QString filter_mode; // must match NgramsModel
    int chosen_col;
    //public slots:
private:
};
#endif // GNG_FILTERMODEL_H
