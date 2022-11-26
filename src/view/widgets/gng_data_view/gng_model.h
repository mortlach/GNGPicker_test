#ifndef GNG_MODEL_H
#define GNG_MODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "gng_data.h"

// TODO easily a base class for this and the other table model-view classes etc
class GNGModel : public QAbstractTableModel
{
    /*!
    *  * \brief The NGramModel class
    * holds pointers to raw data, interface for 2-D model representing that data
    * allows editing of chosen, view formatting etc.
    */    Q_OBJECT
    friend class PhraseUniqueWordModel;
    friend class NGramModel;
    friend class OneGramsModel;

public:
    GNGModel(QObject *parent = nullptr);
    ~GNGModel() = default;
    GNGDataBase* gng_database;
    // TODO add words???
    //QList<QList<QString>>* words;
    // QT stuff
    QList<int> editrole_list;
    // required virtual overloads, columnCount done in derived classes
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // function used when filtering on chosen
    bool isChosen(const QModelIndex& index)const;
    bool isNotChosen(const QModelIndex& index)const;
    void setNewData(GNGDataBase* gng_database_in);
    // toggle the chosen value for rows
    void toggleChosen(const QModelIndexList &rows);
    void setChosen(const QModelIndexList &rows);
    void setNotChosen(const QModelIndexList &rows);
    // required for editable table
    using QAbstractTableModel::flags;
    Qt::ItemFlags flags(const QModelIndex &index);
    // data columns as seen in the view (not necessarily same as data csv files)
    // TODO search for wordfs
//    QModelIndexList match(const QModelIndex &start, int role,
//                          const QVariant &value,
//                          int hits = 1,
//                          Qt::MatchFlags flags = Qt::MatchFlags(Qt::MatchStartsWith|Qt::MatchWrap)) const override;

    bool findNextWord(const QString& word);

    enum Constants
    {
        chosen_col = 0,
    };

};

#endif // GNG_MODEL_H
