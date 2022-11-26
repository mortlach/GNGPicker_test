#ifndef PHRASE_UNIUQE_WORDS_FILTERMODEL_H
#define PHRASE_UNIUQE_WORDS_FILTERMODEL_H

#include <QSortFilterProxyModel>

class PhraseUniqueWordsFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    PhraseUniqueWordsFilterModel(QObject* parent = 0);
    bool filterAcceptsRow(int source_row,const QModelIndex &source_parent) const;
    //    QVariant headerData(int section, Qt::Orientation orientation,
    //                        int role) const;
    void setFilter(const QString &s){ filter_mode.clear(); filter_mode = s; invalidateFilter();}

    QString filter_mode;

    //public slots:
private:
};

#endif // PHRASE_UNIUQE_WORDS_FILTERMODEL_H
