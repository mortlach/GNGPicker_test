#include "1_grams_model.h"
#include <QColor>

OneGramsModel::OneGramsModel(QObject * parent)
    : GNGModel(parent)
    , words(nullptr)
    , counts(nullptr)
    , runes(nullptr)
    , gematria_sum(nullptr)
    //, editrole_list(QList<int>{Qt::EditRole})
{}
//int OneGramsModel::rowCount(const QModelIndex &) const{
//    return (int)words->size();
//}
int OneGramsModel::columnCount(const QModelIndex &) const{
    return col_count;
}
bool OneGramsModel::setData(const QModelIndex &index, const QVariant &, int role){
    if ( role == Qt::EditRole){
        if(index.column() == chosen_col){
            emit dataChanged(index,index);
        }
        return true;
    }
    return false;
}
QVariant OneGramsModel::data(const QModelIndex& index, int role)const{
    if (!index.isValid()) {
        return QVariant();
    }
    if(role == Qt::DisplayRole){
        if(index.column() == word_col){
            return QVariant((*words)[index.row()]).toString();
        }
        if(index.column() == counts_col){
            return QVariant::fromValue((*counts)[index.row()]).toLongLong();
            // different number formats trials
//            //return QVariant::fromValue((*counts)[index.row()]).toDouble();
//            double n = (double)(*counts)[index.row()];
//            return QString::number(n, 'f', 2);
        }
        if(index.column() == gematria_sum_col){
            return QVariant::fromValue((*gematria_sum)[index.row()]).toInt();
        }
        if(index.column() == runes_col){
            return QVariant((*runes)[index.row()]).toString();
        }
    }
    return GNGModel::data(index, role);
}
QVariant OneGramsModel::headerData(int section, Qt::Orientation orientation, int role)const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch(section ){
            case chosen_col: return QVariant(QString("chosen"));
            case word_col: return QVariant(QString("word"));
            case counts_col: return QVariant(QString("count"));
            case gematria_sum_col: return QVariant(QString("sum"));
            case runes_col: return QVariant(QString("runes"));
        }
    }
    return QVariant();
}
//Qt::ItemFlags OneGramsModel::flags(const QModelIndex &){
//    // all columns are "editable", each can toggle chosen row
//    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
//}
void OneGramsModel::setNewData(GNG1GramData& raw_data){
    beginResetModel();
    words = &raw_data.words;
    counts = &raw_data.counts;
    runes = &raw_data.runes;
    gematria_sum = &raw_data.gematria_sum;
//    GNGData* base_raw_data_ptr;
//    auto p = &raw_data;
//    base_raw_data_ptr = &raw_data;
    GNGModel::setNewData(&raw_data);
    endResetModel();
}
bool OneGramsModel::isChosen(const QModelIndex& index)const{
    return gng_database->isChosen(index.row());
}
//bool OneGramsModel::isChosen(int row)const{
//    return (*chosen)[row];
//}
//bool OneGramsModel::isNotChosen(int row)const{
//    return !isChosen(row);
//}
