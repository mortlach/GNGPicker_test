#ifndef NGRAM_FILTERMODEL_H
#define NGRAM_FILTERMODEL_H

#include "gng_filtermodel.h"

class NGramFilterModel : public GNGFilterModel
{
    Q_OBJECT
public:
    NGramFilterModel(QObject* parent = 0);

    inline unsigned int setChosenColumn(unsigned int v){ chosen_column=v; return chosen_column; }
    unsigned int chosen_column;

    bool filterAcceptsRow(int source_row,const QModelIndex &source_parent) const;
    //public slots:
    void setFilter(const QString &s){
        filter_mode.clear();
        filter_mode = s;
        invalidateFilter();
    }
private:
};
#endif // NGRAM_FILTERMODEL_H
