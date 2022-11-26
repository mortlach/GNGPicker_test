#include "lp_phrasepicker_model.h"
#include "utilities.h"

LPPhrasePickerModel::LPPhrasePickerModel(QObject *parent)
    : QAbstractTableModel(parent)
    , editrole_list(QList<int>{Qt::EditRole})
    , lp_sents(QList<QStringList>())
    , lp_sents_word_lengths(QList<QList<unsigned int>>())
    , lp_sents_lengths(QList<unsigned int>())
    , extra_cols(1)
{
    loadLPSentData();

}
int LPPhrasePickerModel::rowCount(const QModelIndex&) const{
    return lp_sents.size();
}
int LPPhrasePickerModel::columnCount(const QModelIndex&) const{
    return col_count;
}

bool LPPhrasePickerModel::loadLPSentData(){
    lp_sents.clear();
    lp_sents_word_lengths.clear();
    lp_sents_lengths.clear();
    col_count = 0;
    if(utilities::parseLPSentencesDataFile(config.path_to_lp_sentences, lp_sents)){
        for(const auto& sent : lp_sents){
            lp_sents_lengths.push_back(sent.size());
            QList<unsigned int> temp = QList<unsigned int>();
            for(const auto& word : sent){
                temp.push_back(word.size());
            }
            lp_sents_word_lengths.push_back(temp);
        }
    }
    auto mm = std::minmax_element(lp_sents_lengths.begin(), lp_sents_lengths.end());
    col_count = *mm.second+extra_cols;
    //qDebug() << *mm.first << *mm.second << ", col_count ="<< col_count;
    return true;
}
QVariant LPPhrasePickerModel::data(const QModelIndex &index, int role)const{
    if (!index.isValid()) {
        return QVariant();
    }
    if(role == Qt::DisplayRole){
        if(index.column() == 0){
            auto t = QVariant::fromValue(lp_sents_lengths[index.row()]).toInt();
            return  QVariant::fromValue(lp_sents_lengths[index.row()]).toInt();
        }
        else{
//            bool t1 = index.column() > 0;
//            bool t2 = index.row() > lp_sents.size() ;
            if( index.row() < lp_sents.size()) {
                auto this_row = index.row();
                auto this_col = index.column();
                auto data_col = this_col - extra_cols; // data is shifted
                auto& raw_data = lp_sents[this_row];
                auto ss = raw_data.size();
                if(raw_data.size() > data_col){
                  auto f = raw_data[data_col];
                  int x =3;
                  return QVariant::fromValue(raw_data[data_col]).toString();
                }
            }

        }

//        if( (index.column() > 0) )){

//              auto& raw_data = lp_sents[index.row()];
//              if(raw_data.size() >  index.column() + extra_cols){
//                  auto data = raw_data[index.row()];
//                  return QVariant::fromValue(raw_data[index.column()]).toString();
//              }
//          }
//        auto r = index.row();
//        auto c = index.column();
//        auto& raw_data = lp_sents[index.row()];
//        auto s = raw_data.size();
//        if( index.column() <= raw_data.size() ){
//            return QVariant::fromValue(raw_data[index.row()]).toString();
    }
    else if(role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
//    if(role == Qt::ForegroundRole ) {
//        if( (index.column() == chosen_col) && isChosen(index.row()) ){
//            return QVariant(QColor::fromRgb(255,0,0));
//        }
//        return QVariant(QColor::fromRgb(0,0,0));
//    }
    return QVariant();
}
Qt::ItemFlags LPPhrasePickerModel::flags(const QModelIndex&){
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled  | Qt::ItemIsEditable;
}

QVariant LPPhrasePickerModel::headerData(int section, Qt::Orientation orientation, int role)const{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if(section == 0){
            return QVariant(QString("Length"));
        }
        else{
            QString h = QString("Word ") + QString::number(section);
            return QVariant(h);

        }
    }
    return QVariant();
}
//ok, the LP phrase picker
//firts cretae some exmaple data fro a couple of rela LP sentrences
//then create a mdoe lto lok at the save folder to pick you rsentence
//or gui widgets to creat a new phrase
//(or pick a phrase form the LP somehow? )
