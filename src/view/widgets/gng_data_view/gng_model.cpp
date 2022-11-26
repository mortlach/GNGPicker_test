#include "gng_model.h"
#include <QColor>

GNGModel::GNGModel(QObject *parent)
    : QAbstractTableModel(parent)
    , gng_database(nullptr)
    , editrole_list(QList<int>{Qt::EditRole})
{}
int GNGModel::rowCount(const QModelIndex&) const{
    if(gng_database){
        return (int)gng_database->size();
    }
    return 0;
}
void GNGModel::setChosen(const QModelIndexList&rows){
    for(const QModelIndex &in: rows){
        gng_database->setChosen(in.row(), true);
        emit dataChanged(index(in.row(), chosen_col),index(in.row(), chosen_col));
    }
}
void GNGModel::setNotChosen(const QModelIndexList&rows){
    for(const QModelIndex &in: rows){
        gng_database->setChosen(in.row(), false);
        emit dataChanged(index(in.row(), chosen_col),index(in.row(), chosen_col));
    }
}
void GNGModel::toggleChosen(const QModelIndexList&rows){
    for(const QModelIndex &in: rows){
        gng_database->toggleChosen(in.row());
        emit dataChanged(index(in.row(), chosen_col),index(in.row(), chosen_col));
    }
}
QVariant GNGModel::data(const QModelIndex &index, int role)const{
    if(role == Qt::DisplayRole){
        if(index.column() == GNGModel::chosen_col){

//             auto t = QVariant::fromValue(

//                         gng_database->getChosen(index.row())

//                         //(*chosen)[index.row()]
//                         ).toBool();

            return QVariant::fromValue(
                        gng_database->getChosen(index.row())
                        //(*chosen)[index.row()]
                        ).toBool();
        }
        return QVariant();
    }
    if(role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
    if(role == Qt::ForegroundRole ) {
        if( (index.column() == chosen_col) && isChosen(index) ){
            return QVariant(QColor::fromRgb(255,0,0));
        }
        return QVariant(QColor::fromRgb(0,0,0));
    }
    return QVariant();
}
//QVariant GNGModel::headerData(int section, Qt::Orientation orientation, int role)const{
//    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
//        switch( section ){
//            case ngram_col: return QVariant(QString("ngram"));
//            case counts_col: return QVariant(QString("count"));
//            case chosen_col: return QVariant(QString("chosen"));
//        }
//    }
//    return QVariant();
//}
Qt::ItemFlags GNGModel::flags(const QModelIndex&){
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled  | Qt::ItemIsEditable;
}
void GNGModel::setNewData(GNGDataBase* gng_database_in){
    gng_database = gng_database_in;
}
bool GNGModel::isChosen(const QModelIndex& index)const{
    return gng_database->getChosen(index.row()) == true;
}
bool GNGModel::isNotChosen(const QModelIndex& index)const{
    return  gng_database->getChosen(index.row()) == false;
}
//QModelIndexList GNGModel::match(const QModelIndex &start,
//                                int role,
//                      const QVariant &value,
//                      int hits, Qt::MatchFlags flags)const{

//    qDebug() << "how to match??" << value;

//    return QModelIndexList();
//}

bool GNGModel::findNextWord(const QString& word){


    return false;
}

