#include "phrase_unique_words_model.h"
#include <QColor>

PhraseUniqueWordsModel::PhraseUniqueWordsModel(QObject *parent)
    : GNGModel(parent)
    , words(nullptr)
    , counts(nullptr)
    , count_in_ngrams(nullptr)
    , current_gngphraseword(nullptr)
    , editrole_list(QList<int>{Qt::EditRole})
{}
int PhraseUniqueWordsModel::rowCount(const QModelIndex&) const{
    return (int)words->size();
}
int PhraseUniqueWordsModel::columnCount(const QModelIndex&) const{
    return col_count;
}
bool PhraseUniqueWordsModel::setData(const QModelIndex &index, const QVariant &, int role){
    if ( role == Qt::EditRole){
            if(index.column() == chosen_col){
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
        if(index.column() == PhraseUniqueWordsModel::word_col){
            return QVariant((*words)[index.row()]);
        }
        if(index.column() == chosen_col){
            return QVariant::fromValue(
                       gng_database->getChosen(index.row())
                       ).toBool();
        }
        if(index.column() == count_ngram_col){
            return QVariant::fromValue((*count_in_ngrams)[index.row()]).toLongLong();
        }
        if(index.column() == count_col){
            return QVariant::fromValue((*counts)[index.row()]).toLongLong();
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
            case word_col: return QVariant(QString("word"));
            case chosen_col: return QVariant(QString("chosen"));
            case count_ngram_col: return QVariant(QString("Ngram Count"));
            case count_col: return QVariant(QString("Total Count"));
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
    counts = &raw_data.counts;
    count_in_ngrams = &raw_data.count_in_ngrams;
    current_gngphraseword = &raw_data;
    GNGModel::setNewData(&raw_data);
    endResetModel();
}

