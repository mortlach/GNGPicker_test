#include "gng_1gram_data.h"
#include "gng_data.h"

const QHash<int,QString> GNG1GramData::raw_1gram_filenames{
    {1, "raw1grams_01.csv"},    {2, "raw1grams_02.csv"},    {3, "raw1grams_03.csv"},
    {4, "raw1grams_04.csv"},    {5, "raw1grams_05.csv"},    {6, "raw1grams_06.csv"},
    {7, "raw1grams_07.csv"},    {8, "raw1grams_08.csv"},    {9, "raw1grams_09.csv"},
    {10, "raw1grams_10.csv"},    {11, "raw1grams_11.csv"},    {12, "raw1grams_12.csv"},
    {13, "raw1grams_13.csv"},    {14, "raw1grams_14.csv"},
};

const QHash<int,QString> GNG1GramData::local_1gram_filenames{
    {1,  "local_1grams_01.csv"},    {2,  "local_1grams_02.csv"},    {3,  "local_1grams_03.csv"},
    {4,  "local_1grams_04.csv"},    {5,  "local_1grams_05.csv"},    {6,  "local_1grams_06.csv"},
    {7,  "local_1grams_07.csv"},    {8,  "local_1grams_08.csv"},    {9,  "local_1grams_09.csv"},
    {10, "local_1grams_10.csv"},    {11, "local_1grams_11.csv"},    {12, "local_1grams_12.csv"},
    {13, "local_1grams_13.csv"},    {14, "local_1grams_14.csv"},
};

GNG1GramData::GNG1GramData(unsigned int word_length)
    : GNGData<QString>(FileType::one_gram)
    , runes(QVector<QString>())
    , gematria_sum(QVector<unsigned int>())
    , word_length(word_length)
{
    qDebug() << "\n*** NEW GNG1GramData word_length =" << word_length << "***";
    if(word_length == 0){
        info_string = QString("Dummy 1-gram data WordLen=0");
    }else{
        setRawDataFilePath(config.path_to_raw_1grams, raw_1gram_filenames.value(word_length));
        setLocalDataFilePath(config.path_to_local_files, local_1gram_filenames.value(word_length));
    }
}
bool GNG1GramData::setFromFileData(const std::vector<std::vector<std::any>>& raw_data){
    words.clear();
    counts.clear();
    chosen.clear();
    runes.clear();
    runes.clear();
    gematria_sum.clear();
    words.reserve((qsizetype)raw_data.size());
    chosen.reserve((qsizetype)raw_data.size());
    chosen.reserve((qsizetype)raw_data.size());
    runes.reserve((qsizetype)raw_data.size());
    gematria_sum.reserve((qsizetype)raw_data.size());
    for(const auto& item : raw_data){
        words.append(QString::fromStdString(std::any_cast<std::string>(item.at(0))));
        counts.append(std::any_cast<unsigned long long>(item.at(1)));
        chosen.append(std::any_cast<bool>(item.at(2)));
        runes.append(QString::fromStdString(std::any_cast<std::string>(item.at(3))));
        gematria_sum.append(std::any_cast<unsigned int>(item.at(4)));
    }
    // ALWAYS call this after items added / deleted
    finishAFterDataAddedOrDeleted();
    return true;
}
QString GNG1GramData::wordToRuneWord(const QString& word)const{
    unsigned int index = 0;
    if( getWordIndex(word, index)){
        return runes[index];
    }
    return QString();
}
unsigned int GNG1GramData::wordToGematriaSum(const QString& word)const{
    unsigned int index = 0;
    if( getWordIndex(word, index)){
        return gematria_sum[index];
    }
    return 0;
}
bool GNG1GramData::getAsFileData(std::vector<std::vector<std::any>>& data_to_fill)const{
    data_to_fill.clear();
    data_to_fill.reserve(words.size());
    for(unsigned int i = 0; i < words.size(); ++i){ // !
        std::vector<std::any> next_line;
        next_line.reserve(5);
        next_line.push_back( std::any(words.at(i).toStdString())  );
        next_line.push_back( std::any(counts.at(i)) );
        next_line.push_back( std::any(chosen.at(i)) );
        next_line.push_back( std::any(runes.at(i).toStdString()) );
        next_line.push_back( std::any(gematria_sum.at(i)) );
        data_to_fill.push_back(next_line);
    }
    return true;
}

bool GNG1GramData::saveLocalData(){
    std::vector<std::vector<std::any>> data;
    if( getAsFileData(data)){

        if( local_data_filepath == QString("") )
        {
            if( (local_data_filename == QString("")) || (local_data_filedir == QString(""))){
                return false;
            }
            else{
                local_data_filepath = QString::fromStdString(utilities::getFullPath(local_data_filedir.toStdString(),
                                                                                    local_data_filename.toStdString()));
            }
        }
        return saveFileData(local_data_filepath, data);
    }
    return false;
}
bool GNG1GramData::saveRawData()const{
    std::vector<std::vector<std::any>> data;
    if( getAsFileData(data)){
        return saveFileData(raw_data_filepath, data);
    }
    return false;
}
bool GNG1GramData::loadLocalData(){
    std::vector<std::vector<std::any>> data;
    if( loadFileData(local_data_filepath,data)){
        return setFromFileData(data);
    }
    return false;
}
bool GNG1GramData::loadRawData(){
    std::vector<std::vector<std::any>> data;
    if( loadFileData(raw_data_filepath,data)){
        return setFromFileData(data);
    }
    return false;
}

bool GNG1GramData::copyTo(const QString& copy_to_directory){

    QString original_path = raw_data_filepath;
    local_data_filedir = copy_to_directory;
    local_data_filepath = getFullPath(local_data_filedir, local_data_filename);
    if(QFile::copy(raw_data_filepath, local_data_filepath  +".csv")){
        qDebug() << "COPIED:" << raw_data_filepath << "to" <<  local_data_filepath;
        return true;
    }
    else{
        qDebug() << "COPY ERROR:" << raw_data_filepath << "to" <<  local_data_filepath;
    }
    return false;
}


bool GNG1GramData::deleteNotChosen2(bool and_squeze){
    // faster than delete from orignal lists
    QVector<unsigned int> chosen_indexes = utilities::findIndexesOf<bool>(chosen,true);
    unsigned int start_size = chosen.size();
    unsigned int end_size = chosen_indexes.size();
    unsigned int delete_size = start_size - end_size;
    QVector<QString> words2;
    words2.reserve(chosen_indexes.size()) ;
    QVector<bool> chosen2;
    chosen2.reserve(chosen_indexes.size());
    QVector<QString> runes2;
    runes2.reserve(chosen_indexes.size());
    QVector<unsigned long long> counts2;
    counts2.reserve(chosen_indexes.size());
    QVector<unsigned int> gematria_sum2;
    gematria_sum2.reserve(chosen_indexes.size());
    for(const auto& i : chosen_indexes){
        words2.push_back( words.at(i));
        chosen2.push_back( chosen.at(i));
        runes2.push_back( runes.at(i));
        counts2.push_back( counts.at(i));
        gematria_sum2.push_back( gematria_sum.at(i));
    }
    words = words2;
    chosen = chosen2;
    runes = runes2;
    counts = counts2;
    gematria_sum = gematria_sum2;
    finishAFterDataAddedOrDeleted();
    Q_ASSERT( end_size == words.size());
    Q_ASSERT( end_size == chosen.size());
    Q_ASSERT( end_size == counts.size());
    Q_ASSERT( end_size == gematria_sum.size());
    Q_ASSERT( end_size == runes.size());
    qDebug() << "GNG1GramData::deleteNotChosen,"  << word_length << "start/end/dif =" << start_size
             << end_size << delete_size;
    return true;
}
//void GNG1GramData::squeeze(){
//    words.squeeze();
//    chosen.squeeze();
//    ngram_string.squeeze();
//    counts.squeeze();
//    word_chosen.squeeze();
//}

bool GNG1GramData::deleteNotChosen(bool){
    unsigned int start_size = chosen.size();
    QVector<unsigned int> not_chosen_indexes = utilities::findIndexesOf<bool>(chosen,false);
    unsigned int delete_size = not_chosen_indexes.size();
    unsigned int end_size = start_size - delete_size;
    for(auto it = not_chosen_indexes.rbegin(); it != not_chosen_indexes.rend(); it++ ){
        words.removeAt(*it);
        chosen.removeAt(*it);
        counts.removeAt(*it);
        runes.removeAt(*it);
        gematria_sum.removeAt(*it);
    }
    finishAFterDataAddedOrDeleted();
    Q_ASSERT( end_size == words.size());
    Q_ASSERT( end_size == chosen.size());
    Q_ASSERT( end_size == counts.size());
    Q_ASSERT( end_size == runes.size());
    Q_ASSERT( end_size == gematria_sum.size());
    qDebug() << "GNG1GramData::deleteNotChosen,"  << word_length << "start/end/dif =" << start_size
             << end_size << delete_size;
    return true;
}
