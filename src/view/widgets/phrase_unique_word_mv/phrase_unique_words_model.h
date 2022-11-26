#ifndef PHRASE_UNIUQE_WORDS_MODEL_H
#define PHRASE_UNIUQE_WORDS_MODEL_H
#include <QList>
#include "gng_phrase_word.h"
#include "gng_model.h"


// TODO easily a base class for this and the other table models
class PhraseUniqueWordsModel : public GNGModel
{
    /*!
    *  * \brief The PhraseUniqueWordsModel class
    * holds pointers to raw data, interface for 2-D model representing that data
    * allows editing of chosen, view formatting etc.
    */
    Q_OBJECT
    friend class PhraseUniqueWordModelViewWidget;

public:
    PhraseUniqueWordsModel(QObject *parent = nullptr);
    ~PhraseUniqueWordsModel() = default;
    // pointers to raw data, stored in GNG objects, i learnt this is much much faster ... so stick with this for model
    QList<QString> *words;
    QList<unsigned long long> *counts;
    QList<unsigned long long> *count_in_ngrams;
    //QList<bool> *chosen;
    GNGPhraseWord* current_gngphraseword;
    // QT stuff
    QList<int> editrole_list;
    // required virtual overloads
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // moar virtual overloads
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // required for editable table
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
    // function used when filtering on chosen
    //inline bool isChosen(const QModelIndex& index)const{return (*chosen)[index.row()];}
    void setNewData(GNGPhraseWord& raw_data);
    // toggle the chosen value for rows
    //void toggleChosen(const QModelIndexList &rows);
    // required for editable table
    using QAbstractTableModel::flags;
    Qt::ItemFlags flags(const QModelIndex& index);
    // data columns as seen in the view (not necessarily same as data csv files)
    enum Constants
    {
        word_col =  0,
        count_col = 1,
        count_ngram_col = 2,
        chosen_col = 3,
        col_count = 4,
    };
};

#endif // PHRASE_UNIUQE_WORDS_MODEL_H

