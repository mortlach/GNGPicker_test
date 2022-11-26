#include "lp_phrasepicker_filtermodel.h"

LPPhrasePickerFilterModel::LPPhrasePickerFilterModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    dynamicSortFilter();
    setFilterKeyColumn(0);
}
