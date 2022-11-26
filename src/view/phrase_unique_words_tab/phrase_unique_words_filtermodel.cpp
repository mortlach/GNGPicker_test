#include "phrase_unique_words_filtermodel.h"

PhraseUniqueWordsFilterModel::PhraseUniqueWordsFilterModel(QObject* parent) :
    QSortFilterProxyModel(parent)
  , filter_mode(QString("all"))
{
    dynamicSortFilter();
    setFilterKeyColumn(0);
}
bool PhraseUniqueWordsFilterModel::filterAcceptsRow(int source_row,const QModelIndex &source_parent) const{
//    auto c = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toString();
    if( filter_mode == "all") return true;
    if( filter_mode == "chosen"){
        bool c = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toBool();
        if(c)
            return true;
        return false;
    }
    if( filter_mode == "not_chosen"){
        bool c = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toBool();
        if(!c)
            return true;
        return false;
    }
    return true;
}
//QVariant MyFilterModel::headerData(int section, Qt::Orientation orientation,int role) const
//{
//}
