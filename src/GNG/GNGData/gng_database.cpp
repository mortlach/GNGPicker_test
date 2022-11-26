#include "qlocale.h"
#include "gng_database.h"
#include "utilities.h"

GNGDataBase::GNGDataBase(GNGDataBase::FileType type_in,  unsigned int ngram_length)
    : info_string(QString())
    , config(GNGConfig())
    , ngram_length(ngram_length)
    , chosen(QVector<bool>())
    , chosen_count(0)
    , type(type_in)
    , local_data_filedir(QString())
    , raw_data_filedir(QString())
    , local_data_filename(QString())
    , local_data_filepath(QString())
    , raw_data_filepath(QString())
{};
GNGDataBase::~GNGDataBase(){};
void GNGDataBase::updateChosenCounts(){
    chosen_count = chosen.count(true);
    not_chosen_count = chosen.count(false);
}
unsigned int GNGDataBase::size()const{
    return (unsigned int)chosen.size();
}
QString GNGDataBase::timeSince(qint64 ts){
    double ans;
    QLocale c(QLocale::C);
    ans = (double)ts/1000 - (double)timer.elapsed()/1000;
    return c.QLocale::toString(ans,'g',3);
}
bool GNGDataBase::setChosen(unsigned int i, bool value){
    Q_ASSERT( i <= chosen.size() );
    chosen.replace(i, value);
    return chosen.at(i);
}
bool GNGDataBase::getChosen(unsigned int i){
    Q_ASSERT( i <= chosen.size() );
    return chosen.at(i);
}
void GNGDataBase::toggleChosen(unsigned int i){
    Q_ASSERT( i <= chosen.size() );
    chosen.replace(i, !chosen.at(i));
}
bool GNGDataBase::isChosen(unsigned int i){
    return getChosen(i) == true;
}

bool GNGDataBase::isNotChosen(unsigned int i){
    return getChosen(i) == false;
}
QString GNGDataBase::getFullPath(const QString& dir, const QString& filename){
    return QString::fromStdString(utilities::getFullPath(dir.toStdString(),
                                                                 filename.toStdString()));

}
