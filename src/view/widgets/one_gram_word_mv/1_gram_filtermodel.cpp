#include "1_gram_filtermodel.h"
#include "1_grams_model.h"

OneGramFilterModel::OneGramFilterModel(QObject* parent)
    : GNGFilterModel(parent)
{}
bool OneGramFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const{
    // add local filters here
    return GNGFilterModel::filterAcceptsRow(source_row,source_parent);
}
