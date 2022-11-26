//#include "gngngram.h"
//#include "gng_1grams.h"
//#include "utilities.h"
//#include <QDebug>
//#include <QVariant>
//#include <QFileInfo>
//#include <algorithm>


//// -=-------------------------------------------------------------------------------------
//// -=-------------------------------------------------------------------------------------
//// -=-------------------------------------------------------------------------------------
//// -=-------------------------------------------------------------------------------------
//// -=-------------------------------------------------------------------------------------
//// -=-------------------------------------------------------------------------------------
//// -=-------------------------------------------------------------------------------------
//GNGNGram::GNGNGram(QMap<QString, QVariant>* config,
//                   QList<unsigned int> const& word_lengths,
//                   unsigned int phrase_index ,
//                   GNG1Grams* gng_words)
//    : config(config)
//    , ngram_word_lengths(word_lengths)
//    , word_index_in_phrase(QList<unsigned int>())
//    , ngram_length(ngram_word_lengths.size())
//    , ngram_word_data(QList<GNGNgramWordRawData>())
//    , count(QList<unsigned long long>())
//    , default_file_name(QString())
//    , gng_words(gng_words)
//    , ngram_count(0) // has to be set when file data is loaded
//{
//    Q_ASSERT (ngram_word_lengths.size() > 0); // always at least 1 word
//    // generate "default" ngram file name from word lengths
//    default_file_name.setNum(ngram_word_lengths[0]) ;
//    word_index_in_phrase.push_back( phrase_index);
//    for(int i = 1; i < ngram_word_lengths.size(); ++i )
//    {
//        QTextStream(&default_file_name) << "_" << ngram_word_lengths[i];
//        word_index_in_phrase.push_back( phrase_index + i);
//    }
//    QTextStream(&default_file_name) << ".csv";
//}
//GNGNGram::GNGNGram(const GNGNGram& copy)
//    : config(copy.config)
//    , ngram_word_lengths(copy.ngram_word_lengths)
//    , word_index_in_phrase(copy.word_index_in_phrase)
//    , ngram_length(copy.ngram_length)
//    , ngram_word_data(copy.ngram_word_data)
//    , count(copy.count)
//    , chosen(copy.chosen)
//    , default_file_name(copy.default_file_name)
//    , gng_words(copy.gng_words)
//    , ngram_count(copy.ngram_count)
//{}
//void GNGNGram::setLocalDataFilePath(QString const &directory,  QString const &file_name){
//    std::string dir = std::string(directory.toStdString());
//    std::string filename = std::string(file_name.toStdString());
//    raw_data_file.fromStdString(utilities::getFullPath(dir, filename));
//}
//void GNGNGram::setRawDataFilePath(QString const &directory,  QString const &file_name){
//    std::string dir = std::string(directory.toStdString());
//    std::string filename = std::string(file_name.toStdString());
//    local_data_file.fromStdString(utilities::getFullPath(dir, filename));
//}
//bool GNGNGram::loadLocalDataFile(){
//    return loadFile(local_data_file);
//}
//bool GNGNGram::loadRawDataFile(){
//    return loadFile(raw_data_file);
//}
//bool GNGNGram::loadFile(QString const& directory,  QString const& file_name){
//    std::vector<std::vector<std::any>> file_data;
//    if(utilities::readNGramfile(directory.toStdString(),file_name.toStdString(),file_data)){
//        //setFromRawData(file_data);
//        return true;
//    }
//    return false;
//}
//bool GNGNGram::loadFile(QString const& path){
//    std::vector<std::vector<std::any>> file_data;
//    if(utilities::readNGramfile(path.toStdString(),file_data)){
//        //setFromRawData(file_data);
//        return true;
//    }
//    return false;
//}

//// need to re-write the load data file
////it might be worth startign a new porjetcc to do the data loading from scracth tro macth the new paradigm!""

//bool GNGNGram::loadData(){ // default (e.g. for raw ngram files)
//    return loadData((*config)[utilities::path_to_google_ngrams_key].toString()); }
//bool GNGNGram::loadData(QString const& directory){ // load from user specified directory (e.g. for save files)
//    return loadData(directory, default_file_name);
//}

//bool GNGNGram::loadData(QString const& directory, QString const& file_name) // load from user specified directory and filename
//{   // actually load some data the raw data is loaded into standard c++ types
//    std::vector<std::vector<std::any>> file_data;
//    if(utilities::read1Gramfile(directory.toStdString(), file_name.toStdString(), file_data))
//    {   // if loaded successfully add new GNGNgramWordRawData objects for each word in the ngram
//        ngram_count = file_data.size();
//        for(unsigned int i = 0; i < ngram_length; ++i )
//        {   // each word data (GNGNgramWordRawData) is contained in here
//            unsigned int this_word_length = ngram_word_lengths[i];
//            ngram_word_data.push_back(GNGNgramWordRawData(word_index_in_phrase[i], this_word_length, &gng_words->getData(this_word_length)));
//            GNGNgramWordRawData& next_word_data = ngram_word_data.back();
//            // fill data file_data is a vector of, vector of strings then a number
//            for(const auto& item : file_data )
//            {
//                //QString next_ngram_word = QString::fromStdString(std::any_cast<std::string>(item[i]));
//                next_word_data.addWord(QString::fromStdString(std::any_cast<std::string>(item[i])));
//            }
//        }
//        for(const auto& item : file_data )
//        {   // add counts, always the last part of each file_data item
//            count.push_back( std::any_cast<unsigned long long>(item.back()));
//            chosen.push_back(true);
//        }
//        return true;
//    }
//    return false;
//}


//bool GNGNGram::deleteByWord(const QList<QString>& delete_words, unsigned int word_index)
//{
//    if( word_index_in_phrase.contains(word_index) )
//    { // ngram contains this word index? loop over words adn see if they are in delete_words , todo better methods?
//        GNGNgramWordRawData& this_index_word_data = ngram_word_data[word_index_in_phrase.indexOf(word_index)];
//        QList<unsigned int> indexes_to_delete;
//        unsigned int counter = 0;
//        for(const auto& it:this_index_word_data.words ){
//            if(delete_words.contains(it)){
//                indexes_to_delete.push_back(counter);
//            }
//            ++counter;
//        }
//        return deleteByIndex(indexes_to_delete);
//    }
//    return true;
//}
//bool GNGNGram::deleteByChosenWord(unsigned int word_index)
//{// uses GNGNGram::ngram_word_data[word_index].chosen
//    if( word_index_in_phrase.contains(word_index) )
//    { // ngram contains this word index. loop over words and see if they are in delete_words , todo better methods?
//        GNGNgramWordRawData& this_index_word_data = ngram_word_data[word_index_in_phrase.indexOf(word_index)];
//        QList<unsigned int> indexes_to_delete;
//        unsigned int counter = 0;
//        for(const auto& it : this_index_word_data.chosen){
//            if(!it){
//                indexes_to_delete.push_back(counter);
//            }
//            ++counter;
//        }
//        return deleteByIndex(indexes_to_delete);
//    }
//    return true;
//}
//bool GNGNGram::deleteByChosenNgram()
//{// uses GNGNGram::chosen
//    QList<unsigned int> indexes_to_delete;
//    unsigned int counter = 0;
//    for(const auto& it : chosen ){
//        if(it){
//            indexes_to_delete.push_back(counter);
//        }
//        ++counter;
//    }
//    return deleteByIndex(indexes_to_delete);
//}
//bool GNGNGram::deleteByIndex(const QList<unsigned int>& indexes_to_delete)
//{   // deletes all entries that match indexes_to_delete (ngram_word_data, count, chosen, update ngram_count)
//    //  ACTUALLY DOES THE DELETE, iterate from high to low in indexes_to_delete to not
//    for(auto& word_data : ngram_word_data )
//    {  // delete items in each GNGNgramWordRawData list
//        word_data.deleteAt(indexes_to_delete);
//    }
//    for (QList<unsigned int>::const_reverse_iterator it= indexes_to_delete.rbegin(); it!=indexes_to_delete.rend(); ++it)
//    {    // delete items in GNGNGram lists
//        count.removeAt(*it);
//        chosen.removeAt(*it);
//        --ngram_count;
//    }
//    return true;
//}
//bool GNGNGram::addUniqueWords(unsigned int index, QList<QString>& list_to_fill ) const
//{
//    int i = word_index_in_phrase.indexOf(index);
//    if( i == -1){
//        return false;
//    }
//    else{
//        for(const auto& word : ngram_word_data[i].words){
//            if(!list_to_fill.contains(word)){
//                list_to_fill.push_back(word);
//            }
//        }
//    }
//    return true;
//}
//bool GNGNGram::addUniqueChosenWords(unsigned int index, QList<QString>& list_to_fill ) const
//{
//    int i = word_index_in_phrase.indexOf(index);
//    if( i == -1){
//        return false;
//    }
//    else{
//        Q_ASSERT( ngram_word_data[i].words.size() == ngram_word_data[i].chosen.size());
//        Q_ASSERT( ngram_word_data[i].words.size() == chosen.size());
//        for(unsigned int c = 0; c < chosen.size(); ++c  ){

//            if(chosen[c]){// &&
//                if(ngram_word_data[i].chosen[c]){
//                    if( !list_to_fill.contains( ngram_word_data[i].words[c] )){
//                        list_to_fill.push_back(ngram_word_data[i].words[c]);
//                    }
//                }
//                else{
//                    qDebug() << "this here should not happen";
//                }
//            }
//        }
//    }
//    return true;
//}
//bool GNGNGram::setNgramNotChosenByWordsAtIndex(unsigned int word_index, const QList<QString>& not_chosen_words)
//{
//    int i = word_index_in_phrase.indexOf(word_index);
//    if( i == -1){
//        return false;
//    }
//    else{
//        Q_ASSERT( ngram_word_data[i].words.size() == ngram_word_data[i].chosen.size());
//        Q_ASSERT( ngram_word_data[i].words.size() == chosen.size());
//        for(unsigned int c = 0; c < chosen.size(); ++c  ){

//            if( not_chosen_words.contains( ngram_word_data[i].words[c] )){
//                ngram_word_data[i].chosen[c] = false;
//                chosen[c] = false;
//            }
//        }
//    }
//    return true;
//}




