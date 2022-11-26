#ifndef ONEGRAM_FILTERMODEL_H
#define ONEGRAM_FILTERMODEL_H

#include "gng_filtermodel.h"

class OneGramFilterModel : public GNGFilterModel
{
//    Q_OBJECT
public:
    OneGramFilterModel(QObject* parent = 0);
    // custum filter as chosen "bool" is a "string" from the view perspective
    bool filterAcceptsRow(int source_row,const QModelIndex &source_parent) const;
//    void setFilter(const QString &s){
//        filter_mode.clear();
//        filter_mode = s;
//        invalidateFilter();
//    }
//    // which column the chosen / not_chosen
//    int chosen_col;  // must match OneGramsModel
//    QString filter_mode;
    //public slots:
private:
};
#endif // ONEGRAM_FILTERMODEL_H
