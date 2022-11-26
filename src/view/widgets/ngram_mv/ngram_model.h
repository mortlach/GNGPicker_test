#ifndef NGRAM_MODEL_H
#define NGRAM_MODEL_H
//#include <QAbstractTableModel>
#include <QList>
#include "gng_phrase_word.h"
#include "gng_phrase.h"
#include "gng_model.h"

// TODO easily a base class for this and the other table model-view classes etc
class NGramModel : public GNGModel
{
    /*!
    *  * \brief The NGramModel class
    * holds pointers to raw data, interface for 2-D model representing that data
    * allows editing of chosen, view formatting etc.
    */    Q_OBJECT
    friend class NgramModelViewWidget;
public:
    NGramModel(QObject *parent = nullptr);
    ~NGramModel() = default;
    // pointers to raw data, stored in GNG objects, i learnt this is much much faster ... so stick with this for model
    //ok i learnt this is much much faster ... so stick with this for model
    QList<QList<QString>>* ngrams;
    QList<unsigned long long>* counts;
    QList<bool>* chosen;
    QList<QList<bool>> *word_chosen;
    unsigned int ngram_length;
    int ngram_word0_col;
    int ngram_word1_col;
    int ngram_word2_col;
    int ngram_word3_col;
    int ngram_word4_col;
    int counts_col;
    int chosen_col;
    int col_count;

    // QT stuff
    //QList<int> editrole_list;
    // required virtual overloads
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // moar virtual overloads
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // required for editable table
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
    // function used when filtering on chosen
    //bool isChosen(const QModelIndex& index)const;
//    bool isChosen(int row)const;
//    bool isNotChosen(int row)const;
    // set raw_data for raw data pointers
    void setNewData(GNGNGram& raw_data);
    // toggle the chosen value for rows
    //void toggleChosen(const QModelIndexList &rows);
    // required for editable table
    //using QAbstractTableModel::flags;
    //Qt::ItemFlags flags(const QModelIndex &index);
    // data columns as seen in the view (not necessarily same as data csv files)
//    enum Constants
//    {
//        ngram_col = 1,
//        counts_col = 2,
//        chosen_col = GNGModel::chosen_col,
//        col_count = 3
//    };

};

#endif // NGRAM_MODEL_H
