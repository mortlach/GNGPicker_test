#ifndef PHRASE_UNIUQE_WORDS_MODEL_H
#define PHRASE_UNIUQE_WORDS_MODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "gng_phrase_word.h"

class PhraseUniqueWordsModel : public QAbstractTableModel
{
    /*!
    *  * \brief The PhraseUniqueWordsModel class
    * holds pointers to raw data, interface for 2-D model representing that data
    * allows editing of chosen, view formatting etc.
    */
    Q_OBJECT
public:
    PhraseUniqueWordsModel(QObject *parent = nullptr);
    ~PhraseUniqueWordsModel() = default;
    // data columns as seen in the view (not necessarily same as data csv files)
    int word_col;
    int chosen_col;
    int col_count;
    // pointers to raw data, stored in GNG objects, i learnt this is much much faster ... so stick with this for model
    QList<QString> *words;
    QList<bool> *chosen;
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
    bool isChosen(const QModelIndex& index)const;
    // set raw_data for raw data pointers
    void setNewData(GNGPhraseWord& raw_data);
    // toggle the chosen value for rows
    void toggleChosen(const QModelIndexList &rows);
    // required for editable table
    using QAbstractTableModel::flags;
    Qt::ItemFlags flags(const QModelIndex& index);
};

#endif // PHRASE_UNIUQE_WORDS_MODEL_H

