#include <QDir>
#include "gng_1grams.h"
#include "utilities.h"

GNG1GramData GNG1Grams::dummy_model_data = GNG1GramData(0); // to handle bad requets
QList<GNG1GramData*> GNG1Grams::all_raw_word_data = QList<GNG1GramData*>();
QList<GNG1GramData*> GNG1Grams::local_phrase_1gram_data = QList<GNG1GramData*>();
bool GNG1Grams::loaded_phrase_local1gram_files  = false;
bool GNG1Grams::loaded_raw1gram_files  = false;
bool GNG1Grams::loaded_local1gram_files = false;
unsigned int GNG1Grams::onegram_file_count = 14; // TODO add apostrophe words

GNG1Grams::GNG1Grams()
    : GNG1Grams(false)
{}
GNG1Grams::GNG1Grams(bool load_rawfiles)
    : config(GNGConfig())
{
    qDebug()<< "GNG1Grams Constructor called with load_rawfiles=" << load_rawfiles;
    if(load_rawfiles){
        if(!setupAndloadRaw1Grams()){
            qDebug() << "ERROR loading raw 1grams";
        }
    }
}
bool GNG1Grams::setupAndloadRaw1Grams(){
    bool r = true;
//    QString t = config.path_to_raw_1grams;
    if(!loaded_raw1gram_files){
        unsigned int word_length_counter = 1;
//        Q_ASSERT(config.raw_1gram_filenames.size() == config.local_1gram_filename_keys.size());
        all_raw_word_data.clear();
        all_raw_word_data.reserve(onegram_file_count);
        for(unsigned int i =1; i < onegram_file_count + 1; ++i){
            all_raw_word_data.push_back( new GNG1GramData( word_length_counter) );
            all_raw_word_data.back()->info_string = QString("Raw 1-gram, WordLength=" + QString::number(word_length_counter));
            // local directory must be set later when actually creating a phrase todo HACK AF
            //all_raw_word_data.back()->local_data_filename = local_1gram_filenames.value(i);
            qDebug() << all_raw_word_data.back()->raw_data_filename;
            qDebug() << all_raw_word_data.back()->raw_data_filedir;
            qDebug() << all_raw_word_data.back()->raw_data_filepath;
            if( all_raw_word_data.back()->loadRawData() ){
            }
            else{
                r = false;
            }
            ++word_length_counter;
        }
    }
    loaded_raw1gram_files = r;
    return loaded_raw1gram_files;
}
bool GNG1Grams::newConfig()
{
    if(config.has_local_1gram_filenames){
        setLocalDataFileDirectory();
        loaded_local1gram_files = loadAllLocal1Grams();
        if(loaded_local1gram_files){
            loaded_raw1gram_files = false;
        }
    }
    return true;
}
void GNG1Grams::setRawDataFileDirectory(){
    for(auto& item: all_raw_word_data){
        item->raw_data_filedir = config.path_to_raw_1grams;
    }
}
void GNG1Grams::setLocalDataFileDirectory(){
    for(auto& item: all_raw_word_data){
        item->local_data_filedir = config.path_to_local_files;
    }
}
// Raw files
bool GNG1Grams::loadAllRaw1Grams(){
    if(config.has_local_1gram_filenames){
        bool r = true;
        for(auto& item: all_raw_word_data){
            if(item->loadRawData()){
            }
            else{
                r = false;
            }
        }
        return r;
    }
    return false;

}
bool GNG1Grams::loadRaw1GramFile(unsigned int word_length){
    if(hasWordLength(word_length)){
        GNG1GramData&  r = getData(word_length);
        qDebug() << "GNG1Grams::loadRaw1GramFile:" << r.raw_data_filepath << "word_length =" << word_length;
        if(r.loadRawData()){
            r.word_length = word_length;
            return true;
        }
        else{
            qDebug() << "Error loading file";
        }
    }
    return false;
}
bool GNG1Grams::saveAllRaw1Grams()const{
    bool r = true;
    for(const auto& item: all_raw_word_data){
        std::vector<std::vector<std::any>> data_to_write;
        item->getAsFileData(data_to_write);
        bool s = item->save1Gram(item->raw_data_filepath,data_to_write);
        if(s){
        }
        else{
            r = false;
        }
    }
    return r;
}
bool GNG1Grams::saveRaw1GramFile(unsigned int word_length){
    if(hasWordLength(word_length)){
        return all_raw_word_data.at(word_length)->saveRawData();
    }
    return false;
}
bool GNG1Grams::loadAllLocal1GramsFromConfig(){
    bool r = true;
    local_phrase_1gram_data.clear();
    local_phrase_1gram_data.reserve(config.local_1gram_filenames.size());

    QVector<unsigned int> wl = config.getPhraseWordLengths();
    Q_ASSERT(config.local_1gram_filenames.size() == wl.size());
    for(unsigned i=0; i < config.local_1gram_filenames.size(); ++i ){
        local_phrase_1gram_data.push_back( new GNG1GramData(wl.at(i)) );
        local_phrase_1gram_data.back()->setLocalDataFilePath(config.path_to_local_files, config.local_1gram_filenames.at(i));
    }
    return loadAllLocal1Grams();
}

bool GNG1Grams::loadAllLocal1Grams(){
    bool r = true;
    for(auto& item: local_phrase_1gram_data){
        if(item->loadLocalData()){
        }
        else{
            r = false;
        }
    }
    return r;
}
bool GNG1Grams::saveAllLocal1Grams()const{
    bool r = true;
    for(const auto& item: local_phrase_1gram_data){
        if(item->saveLocalData()){
        }
        else{
            r = false;
        }
    }
    return r;
}
bool GNG1Grams::saveLocal1GramFile(unsigned int word_length){
    if(hasWordLength(word_length)){
        return local_phrase_1gram_data[word_length]->saveLocalData();
    }
    return false;
}bool GNG1Grams::loadLocal1GramFile(unsigned int word_length){
    if(hasWordLength(word_length)){
        GNG1GramData&  r = getData(word_length);
        r.loadLocalData();
        r.word_length = word_length;
        return true;
    }
    return false;
}



int GNG1Grams::getWordLengthIndex(int word_length){
    int index = 0;
    for(const auto& item : all_raw_word_data){
        if(item->word_length == (unsigned int)word_length){
            return index;
        }
        ++index;
    }
    return -1;
}
bool GNG1Grams::hasWordLength(int word_length){
    for(const auto& item : all_raw_word_data){
        if(item->word_length == (unsigned int)word_length) return true;
    }
    return false;
}
GNG1GramData& GNG1Grams::getData(unsigned int word_length){
    if(hasWordLength(word_length)){
        return *all_raw_word_data[getWordLengthIndex(word_length)];
    }
    qDebug() << "ERROR: GNG1Grams has no wordlength = " << word_length;
    return dummy_model_data;
}

bool GNG1Grams::setUpNewPhrase1Grams(const QVector<unsigned int>& word_lengths){
    bool s = true;
    local_phrase_1gram_data.clear();
    local_phrase_1gram_data.reserve(word_lengths.size());
    config.local_1gram_filenames.clear();
    config.local_1gram_filenames.reserve(word_lengths.size());
    for(auto& item : word_lengths){
        local_phrase_1gram_data.push_back( new GNG1GramData( item) );
        *local_phrase_1gram_data.back() = getData(item); // (!?)
        local_phrase_1gram_data.back()->info_string = QString("local 1-gram, WordLength=" + QString::number(item));
        local_phrase_1gram_data.back()->setLocalDataFilePath(config.path_to_local_files, local_phrase_1gram_data.back()->local_data_filename);
        if(local_phrase_1gram_data.back()->saveLocalData()){
            config.local_1gram_filenames.push_back( local_phrase_1gram_data.back()->local_data_filename);
        }
        else{
            s = false;
        }
    }
    return s;
}
GNG1GramData* GNG1Grams::getPrase1GramPtrAtWordLength(unsigned int word_length_in){
    for(unsigned int i = 0;i < local_phrase_1gram_data.size(); ++i){
        if( local_phrase_1gram_data.at(i)->word_length == word_length_in){
            return local_phrase_1gram_data[i];
        }
    }
    return nullptr;
}
GNG1GramData& GNG1Grams::getPrase1GramRefAtWordLength(unsigned int word_length_in){
    for(unsigned int i = 0;i < local_phrase_1gram_data.size(); ++i){
        if( local_phrase_1gram_data.at(i)->word_length == word_length_in){
            return getPrase1GramRefAtWordLength(i);
        }
    }
    return dummy_model_data;
}

bool GNG1Grams::copyRaw1GramsToConfigLocalDirectory(const QVector<unsigned int>& word_lengths){
    bool s = true;
    for(auto& item : word_lengths){
        if(!getData(item).copyTo(config.path_to_local_files)){
               s = false;
        }
    }
    return s;
}
