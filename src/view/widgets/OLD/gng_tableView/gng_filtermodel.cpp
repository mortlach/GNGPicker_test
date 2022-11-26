#include "gng_filtermodel.h"
#include "gng_model.h"

GNGFilterModel::GNGFilterModel(QObject* parent)
    : QSortFilterProxyModel(parent)
    , filter_mode(QString("all"))
    , chosen_col(GNGModel::chosen_col)
{
    dynamicSortFilter();
    setFilterKeyColumn(0);
}
bool GNGFilterModel::filterAcceptsRow(int source_row,const QModelIndex &source_parent) const{
    if( filter_mode == "all")
        return true;
    if( filter_mode == "chosen"){
        //gngModel* m = dynamic_cast<gngModel*>(sourceModel());
        //return dynamic_cast<gngModel*>(sourceModel())->isChosen(source_row);
        bool c = sourceModel()->data(sourceModel()->index(source_row, chosen_col, source_parent)).toBool();
        if(c)
            return true;
        return false;
    }
    if( filter_mode == "not_chosen"){
        //gngModel* m = dynamic_cast<gngModel*>(sourceModel());
        //return dynamic_cast<gngModel*>(sourceModel())->isNotChosen(source_row);
        bool c = sourceModel()->data(sourceModel()->index(source_row, chosen_col, source_parent)).toBool();
        if(!c)
            return true;
        return false;
    }
    return true;
}
