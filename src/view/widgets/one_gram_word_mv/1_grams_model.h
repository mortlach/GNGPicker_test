#ifndef ONE_GRAMS_MODEL_H
#define ONE_GRAMS_MODEL_H
#include <QList>
#include "gng_1grams.h"
#include "gng_model.h"
#include <QDebug>

class OneGramsModel : public GNGModel
{
/*!
*  * \brief The OneGramsModel class
* holds pointers to raw data, interface for 2-D model representing that data
* allows editing of chsoen, view formatting etc.
*/
//    Q_OBJECT
    friend class OneGramModelViewWidget;
public:
    OneGramsModel(QObject * parent = nullptr);
    ~OneGramsModel() = default;
    // pointers to raw data, stored in GNG objects, i learnt this is much much faster ... so stick with this for model
    QList<QString> * words;
    QList<unsigned long long> * counts;
    QList<QString> * runes;
    QList<unsigned int> * gematria_sum;
    // QT stuff
    //QList<int> editrole_list;
    // required virtual overloads
    //int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    // moar virtual overloads
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // required for editable table
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole)override;
    // function used when filtering on chosen
    bool isChosen(const QModelIndex& index)const;

    //    bool isChosen(int row)const;
//    bool isNotChosen(int row)const;
    // set raw_data for raw data pointers
    void setNewData(GNG1GramData& raw_data);
    // toggle the chosen value for rows
    //void toggleChosen(const QModelIndexList& rows);
    // required for editable table
    //using QAbstractTableModel::flags;
    //Qt::ItemFlags flags(const QModelIndex& index);
    enum Constants
    {
        word_col =  1,
        counts_col = 2,
        chosen_col = GNGModel::chosen_col,
        runes_col = 4,
        gematria_sum_col = 3,
        col_count = 5
    };
};

#endif // ONE_GRAMS_MODEL_H
