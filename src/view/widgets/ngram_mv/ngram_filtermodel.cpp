#include "ngram_filtermodel.h"
#include "ngram_model.h"

NGramFilterModel::NGramFilterModel(QObject* parent)
    : GNGFilterModel(parent)
    , chosen_column(0)
{}
bool NGramFilterModel::filterAcceptsRow(int source_row,const QModelIndex &source_parent) const{
    // add local filters here
//    return GNGFilterModel::filterAcceptsRow(source_row,source_parent);
//}

//bool GNGFilterModel::filterAcceptsRow(int source_row,const QModelIndex &source_parent) const{
    if( filter_mode == "all")
        return true;
    if( filter_mode == "chosen"){
        //gngModel* m = dynamic_cast<gngModel*>(sourceModel());
        //return dynamic_cast<gngModel*>(sourceModel())->isChosen(source_row);
        bool c = sourceModel()->data(sourceModel()->index(source_row, chosen_column, source_parent)).toBool();
        if(c)
            return true;
        return false;
    }
    if( filter_mode == "not_chosen"){
        //gngModel* m = dynamic_cast<gngModel*>(sourceModel());
        //return dynamic_cast<gngModel*>(sourceModel())->isNotChosen(source_row);
        bool c = sourceModel()->data(sourceModel()->index(source_row, chosen_column, source_parent)).toBool();
        if(!c)
            return true;
        return false;
    }
    return true;
}

