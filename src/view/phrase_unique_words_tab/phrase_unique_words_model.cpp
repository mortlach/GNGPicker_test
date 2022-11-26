#include "phrase_unique_words_model.h"
#include <QColor>

PhraseUniqueWordsModel::PhraseUniqueWordsModel(QObject *parent)
    : QAbstractTableModel(parent)
    , word_col(0)
    , chosen_col(1)
    , col_count(2)
    , words(nullptr)
    , chosen(nullptr)
    , current_gngphraseword(nullptr)
    , editrole_list(QList<int>{Qt::EditRole})
{}
int PhraseUniqueWordsModel::rowCount(const QModelIndex&) const{
    return (int)words->size();
}
int PhraseUniqueWordsModel::columnCount(const QModelIndex&) const{
    return col_count;
}
void PhraseUniqueWordsModel::toggleChosen(const QModelIndexList&rows){
    for(const QModelIndex &in: rows){
        (*chosen)[in.row()] = !(*chosen)[in.row()];
        emit dataChanged(index(in.row(), chosen_col),index(in.row(), chosen_col));
        //emit dataChanged(in,in);
    }
}

bool PhraseUniqueWordsModel::setData(const QModelIndex &index, const QVariant &, int role){
        if ( role == Qt::EditRole){
            if(index.column() == chosen_col){
    //            QMap<QString, QList<QVariant>>::iterator it = my_data.begin();
    //            std::advance(it, index.row());
    //            it.value().replace(2, value.toBool());
                emit dataChanged(index,index);
            }
            return true;
        }
        return false;
    }

QVariant PhraseUniqueWordsModel::data(const QModelIndex &index, int role)const{
    if (!index.isValid()) {
        return QVariant();
    }
    if(role == Qt::DisplayRole){
        if(index.column() == word_col){
            return QVariant((*words)[index.row()]);
        }
        if(index.column() == chosen_col){
            return QVariant::fromValue((*chosen)[index.row()]).toBool();
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
QVariant PhraseUniqueWordsModel::headerData(int section, Qt::Orientation orientation, int role)const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch(section ){
            case 0: return QVariant(QString("word"));
            case 1: return QVariant(QString("chosen"));
        }
    }
    return QVariant();
}

Qt::ItemFlags PhraseUniqueWordsModel::flags(const QModelIndex&){
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled  | Qt::ItemIsEditable;
}

void PhraseUniqueWordsModel::setNewData(GNGPhraseWord& raw_data){
    beginResetModel();
    words = &raw_data.words;
    chosen = &raw_data.chosen;
    current_gngphraseword = &raw_data;
    endResetModel();
}
bool PhraseUniqueWordsModel::isChosen(const QModelIndex& index)const{
    return (*chosen)[index.row()];
}
