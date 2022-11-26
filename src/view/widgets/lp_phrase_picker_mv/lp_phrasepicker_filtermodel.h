#ifndef LPPHRASEPICKERFILTERMODEL_H
#define LPPHRASEPICKERFILTERMODEL_H

#include <QSortFilterProxyModel>

class LPPhrasePickerFilterModel : public QSortFilterProxyModel
{
public:
    LPPhrasePickerFilterModel(QObject* parent = nullptr);
};

#endif // LPPHRASEPICKERFILTERMODEL_H
