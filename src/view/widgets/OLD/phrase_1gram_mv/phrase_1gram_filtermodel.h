#ifndef PHRASE_1GRAMS_FILTERMODEL_H
#define PHRASE_1GRAMS_FILTERMODEL_H

#include "gng_filtermodel.h"

class Phrase1GramsilterModel : public GNGFilterModel
{
    Q_OBJECT
public:
    Phrase1GramsilterModel(QObject* parent = 0);
    bool filterAcceptsRow(int source_row,const QModelIndex &source_parent) const;

    inline unsigned int setChosenColumn(unsigned int v){ chosen_column=v; return chosen_column; }
    unsigned int chosen_column;
    //    QVariant headerData(int section, Qt::Orientation orientation,
    //                        int role) const;
    //void setFilter(const QString &s){ filter_mode.clear(); filter_mode = s; invalidateFilter();}
    //QString filter_mode;

    //public slots:
private:
};

#endif // PHRASE_1GRAMS_FILTERMODEL_H
