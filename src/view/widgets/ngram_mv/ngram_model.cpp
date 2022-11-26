#include "ngram_model.h"
#include <QColor>

NGramModel::NGramModel(QObject *parent)
    : GNGModel(parent)
    , ngrams(nullptr)
    , counts(nullptr)
    , chosen(nullptr)
    , word_chosen(nullptr)
    , ngram_length(0)
    , ngram_word0_col(0)
    , ngram_word1_col(1)
    , ngram_word2_col(100)
    , ngram_word3_col(100)
    , ngram_word4_col(100)
    , counts_col(100)
    , chosen_col(100)
    , col_count(0)
{}
int NGramModel::rowCount(const QModelIndex&) const{
    return (int)ngrams->size();
}
int NGramModel::columnCount(const QModelIndex&) const{
    return col_count;
}
bool NGramModel::setData(const QModelIndex &index, const QVariant &, int role){
        if ( role == Qt::EditRole){
            if(index.column() == chosen_col){
                emit dataChanged(index,index);
            }
            return true;
        }
        return false;
    }

QVariant NGramModel::data(const QModelIndex &index, int role)const{
    if (!index.isValid()) {
        return QVariant();
    }
    if(role == Qt::DisplayRole){
        if(index.column() == ngram_word0_col) return QVariant((*ngrams)[index.row()][ngram_word0_col]);
        if(index.column() == ngram_word1_col) return QVariant((*ngrams)[index.row()][ngram_word1_col]);
        if(index.column() == ngram_word2_col) return QVariant((*ngrams)[index.row()][ngram_word2_col]);
        if(index.column() == ngram_word3_col) return QVariant((*ngrams)[index.row()][ngram_word3_col]);
        if(index.column() == ngram_word4_col) return QVariant((*ngrams)[index.row()][ngram_word4_col]);
        if(index.column() == counts_col) return QVariant::fromValue((*counts)[index.row()]).toLongLong();
        if(index.column() == chosen_col) return QVariant::fromValue((*chosen)[index.row()]).toBool();
    }
    if(role == Qt::DisplayRole){
        if(index.column() == chosen_col){
            return QVariant::fromValue(gng_database->getChosen(index.row()));
        }
        if(index.column() == ngram_word0_col){
        }
//        int ngram_word0_col;
//        int ngram_word1_col;
//        int ngram_word2_col;
//        int ngram_word3_col;
//        int ngram_word4_col;
//        int counts_col;
        return QVariant();
    }
    if(role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
    if(role == Qt::ForegroundRole ) {
        if( (index.column() == chosen_col) && isChosen(index) ){
            return QVariant(QColor::fromRgb(255,0,0));
        }
        if(index.column() == ngram_word0_col && (*word_chosen)[index.row()][0] ){
            return QVariant(QColor::fromRgb(255,0,0));
        }
        if(index.column() == ngram_word1_col && (*word_chosen)[index.row()][1] ){
            return QVariant(QColor::fromRgb(255,0,0));
        }
        if(index.column() == ngram_word2_col && (*word_chosen)[index.row()][2] ){
            return QVariant(QColor::fromRgb(255,0,0));
        }
        if(index.column() == ngram_word3_col && (*word_chosen)[index.row()][3] ){
            return QVariant(QColor::fromRgb(255,0,0));
        }
        if(index.column() == ngram_word4_col && (*word_chosen)[index.row()][4] ){
            return QVariant(QColor::fromRgb(255,0,0));
        }
        return QVariant(QColor::fromRgb(0,0,0));
    }
    return QVariant();
    //    return GNGModel::data(index, role);
}
QVariant NGramModel::headerData(int section, Qt::Orientation orientation, int role)const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if(section == ngram_word0_col)  return QVariant(QString("word 1"));
            if(section == ngram_word1_col)  return QVariant(QString("word 2"));
            if(section == ngram_word2_col)  return QVariant(QString("word 3"));
            if(section == ngram_word3_col)  return QVariant(QString("word 4"));
            if(section == chosen_col)  return QVariant(QString("chosen"));
            if(section == counts_col)  return QVariant(QString("count"));
    }
    return QVariant();
}
//Qt::ItemFlags NGramModel::flags(const QModelIndex&){
//    return Qt::ItemIsSelectable | Qt::ItemIsEnabled  | Qt::ItemIsEditable;
//}
void NGramModel::setNewData(GNGNGram& raw_data){
    // reset these to dummy values before asssigning "correct ones"
    ngram_word2_col = 100;
    ngram_word3_col = 100;
    ngram_word4_col = 100;
    beginResetModel();
    ngrams = &raw_data.words;
    counts = &raw_data.counts;
    chosen = &raw_data.chosen;
    word_chosen = &raw_data.word_chosen;
    ngram_length = raw_data.ngram_length;
    ngram_word0_col = 0;
    ngram_word1_col = 1;
    switch(ngram_length ){
        case 3: ngram_word2_col = 2; break;
        case 4: ngram_word2_col = 2; ngram_word3_col = 3; break;
        case 5: ngram_word2_col = 2; ngram_word3_col = 3; ngram_word4_col = 4; break;
    }
    counts_col = ngram_length;
    chosen_col = counts_col + 1;
    col_count = chosen_col+1;
    GNGModel::setNewData(&raw_data);

    qDebug() << "ngram_word0_col =" << ngram_word0_col;
    qDebug() << "ngram_word1_col =" << ngram_word1_col;
    qDebug() << "ngram_word2_col =" << ngram_word2_col;
    qDebug() << "ngram_word3_col =" << ngram_word3_col;
    qDebug() << "ngram_word4_col =" << ngram_word4_col;
    qDebug() << "counts_col =" << counts_col;
    qDebug() << "chosen_col =" << chosen_col;
    qDebug() << "col_count =" << col_count;

    endResetModel();
}
