#ifndef LPPHRASEPICKERMODEL_H
#define LPPHRASEPICKERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "gng_config.h"

class LPPhrasePickerModel : public QAbstractTableModel
{
public:
    LPPhrasePickerModel(QObject *parent = nullptr);

    // QT stuff
    QList<int> editrole_list;
    // required virtual overloads
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // moar virtual overloads
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // required for editable table
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
    //bool isChosen(int row)const;
    //bool isNotChosen(int row)const;
    // set raw_data for raw data pointers
    //void setNewData(GNGData* raw_data);
    void setNewData(QList<bool>* chosen_in, unsigned int* chosen_count_in);
    // toggle the chosen value for rows
    void toggleChosen(const QModelIndexList &rows);
    // required for editable table
    using QAbstractTableModel::flags;
    Qt::ItemFlags flags(const QModelIndex &index);
    GNGConfig config;

    bool loadLPSentData();

    QList<QStringList> lp_sents;
    QList<QList<unsigned int>> lp_sents_word_lengths;
    QList<unsigned int> lp_sents_lengths;
    int col_count;
    int extra_cols;

};

#endif // LPPHRASEPICKERMODEL_H
