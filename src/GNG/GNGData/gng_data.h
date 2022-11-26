#ifndef GNG_DATA_H
#define GNG_DATA_H
#include <QDebug>
#include <QDir>
#include <QVector>
#include <QVector>
#include <QString>
#include <QVariant>
#include <QString>
#include <QHash>
#include <any>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include "gng_database.h"
#include "gng_config.h"
#include "utilities.h"
#include <fstream>
/*!
 * \brief The GNGData class
 *        Base class for ngram and phrase data, can also load and save data to files
 */
template<typename T>
class GNGData: public GNGDataBase
{
public:
    GNGData();
    GNGData(GNGDataBase::FileType type_in);
    GNGData(GNGDataBase::FileType type_in,  unsigned int ngram_length);
    virtual ~GNGData(){ };
    GNGData& operator=(GNGData& other) = default;

    QVector<unsigned long long> counts; // their everythgihgn has a count ...
    QHash<T, unsigned int> word_to_index;

    QVector<T> words; //
    QVector<T> chosen_words;
    QVector<T> not_chosen_words;
    //
    /*!
     * \brief loadFileData:
     * \param full_path
     * \param data_to_fill
     * \return
     */
    bool loadFileData(const QString& full_path,
                      std::vector<std::vector<std::any>>& data_to_fill,
                      unsigned int ngram_length = 0)const;
    bool saveFileData(const QString& full_path,
                      const std::vector<std::vector<std::any>>& data_to_save,
                      unsigned int ngram_length = 0)const;
    //
    virtual bool setFromFileData(const std::vector<std::vector<std::any>>& raw_data) = 0;
    /*!
     * \brief finishSetFromFileData: ALWAYS CALL THIS AFTER and when you have added  / deleted data to this class
     * e.g. overloaded setFromFileData and any deleteNotChosen functions
     * \return bool, succeess
     */
    void finishAFterDataAddedOrDeleted();
    /*!
     * \brief getAsFileData, converts relevant class data fro eahc word to generalized format (e.g. for writing to file)
     * \param data_to_fill, object to copy data into
     * \return bool, success
     */
    virtual bool getAsFileData(std::vector<std::vector<std::any>>& data_to_fill)const = 0;
    /*!
     * \brief setLocalDataFilePath
     * \param directory
     * \param file_name
     */
    void setLocalDataFilePath(QString const& directory,  QString const& file_name);
    /*!
     * \brief setRawDataFilePath
     * \param directory
     * \param filename
     */
    void setRawDataFilePath(QString const& directory,  QString const& filename);
    /*!
     * \brief setRawDataFilePath
     * \param path
     */
    void setRawDataFilePath(QString const& path);
    /*!
     * \brief setLocalDataFilePath
     * \param path
     */
    void setLocalDataFilePath(QString const& path);
    /*!
     * \brief getChosenCount
     * \return
     */
    unsigned int getChosenCount()const;
    /*!
     * \brief getNotChosenCount
     * \return
     */
    unsigned int getNotChosenCount()const;
    // set / get chosen/ not_chosen
    /*!
     * \brief updateChosenSummary
     */
    void updateChosenSummary();
    /*!
     * \brief setChosenWords
     */
    void setChosenWords();
    /*!
     * \brief inChosenWords, is a word in chosen_words (assumes chosen_words is up to date).
     * \param word_to_check
     * \return bool, result
     */
    bool inChosenWords(const T& word_to_check)const;
    /*!
     * \brief inNotChosenWords, is a word in not_chosen_words (assumes not_chosen_words is up to date).
     * \param word_to_check
     * \return bool, result
     */
    bool inNotChosenWords(const T& word_to_check)const;
    /*!
     * \brief getChosenWords, copy chosen_words
     * \return QVector<T>
     */
    QVector<T> getChosenWords()const;
    /*!
     * \brief getNotChosenWords, copy not_chosen_words
     * \return QVector<T>
     */
    QVector<T> getNotChosenWords()const;
    /*!
     * \brief getChosenWordsCRef get chosen_words
     * \return const QVector<T>&
     */
    const QVector<T>& getChosenWordsCRef()const;
    /*!
     * \brief getNotChosenWordsCRef, get not_chosen_words
     * \return const QVector<T>&
     */
    const QVector<T>& getNotChosenWordsCRef()const;
    // friends
    friend class GNG1Grams;
    friend class GNGPhraseWord;
    friend class GNGNGram;
    friend class GNG1GramData;
    friend class GNGPhrase;

private:
    // use public load save
    /*!
     * \brief load1Gram, load onegram file data
     * \param full_path, path to file
     * \param data_to_write, data to fille
     * \return bool, success
     */
    bool load1Gram(const QString& full_path,
                     std::vector<std::vector<std::any>>& data_to_fill)const;
    /*!
     * \brief loadNGramNoChosen, load onegram file data with no chosen column
     * \param full_path, path to file
     * \param data_to_write, data to fille
     * \return bool, success
     */
    bool loadNGramNoChosen(const QString& full_path,
                           std::vector<std::vector<std::any>>& data_to_fill,
                           unsigned int ngram_length = 0)const;
    /*!
     * \brief loadNGramWithChosen, load N-gram file data
     * \param full_path, path to file
     * \param data_to_write, data to fille
     * \return bool, success

     */
    bool loadNGramWithChosen(const QString& full_path,
                             std::vector<std::vector<std::any>>& data_to_fill,
                             unsigned int ngram_length = 0)const;
    /*!
     * \brief loadPUW
     * \param full_path, path to file
     * \param data_to_write, data to fille
     * \return bool, success
     */
    bool loadPUW(const QString& full_path,
                 std::vector<std::vector<std::any>>& data_to_write)const;
    /*!
     * \brief saveOneGram, save 1-gram data
     * \param full_path, path to file
     * \param data_to_write, data to save
     * \return bool, success
     */
    bool save1Gram(const QString& full_path,
                     const std::vector<std::vector<std::any>>& data_to_write)const;
    /*!
     * \brief saveNGram, save N-gram data
     * \param full_path, path to file
     * \param data_to_write, data to save
     * \return bool, success
     */
    bool saveNGram(const QString& full_path,
                   const std::vector<std::vector<std::any>>& data_to_fill,
                   unsigned int ngram_length = 0)const;
    /*!
     * \brief savePUW, save PUW data
     * \param full_path, path to file
     * \param data_to_write, data to save
     * \return bool, success
     */
    bool savePUW(const QString& full_path,
                 const std::vector<std::vector<std::any>>& data_to_write)const;

    /*!
     * \brief setWordToIndex: fill the hash map for 'quick' word index lookup
     */
    void setWordToIndex();
    /*!
     * \brief isChosen true if word is chosen
     * \param word(s) to lookup
     * \return bool
     */
    bool isChosen(const T& word);
    /*!
     * \brief isNotChosen true if word is NOT chosen
     * \param word: word(s) to lookup
     * \return bool
     */
    bool isNotChosen(const T& word);
    /*!
     * \brief hasWordAtIndex is there word in word_to_index
     * \param word_to_lookup
     * \return bool
     */
    bool hasWordAtIndex(const T& word_to_lookup)const;
    /*!
     * \brief getWordIndex: get index of word in words
     * \param word_to_lookup
     * \param index ref to unsigned int var to write result to
     * \return bool, true if word is in words
     */
    bool getWordIndex(const T& word_to_lookup, unsigned int& index)const;
    /*!
     * \brief getWordIndex no safety (may crash!)
     * \param word_to_lookup
     * \return unsigned int result
     */
    unsigned int getWordIndex(const T& word_to_lookup)const;

};
template<typename T>
inline
GNGData<T>::GNGData()
    : GNGData(GNGDataBase::not_known, 0)
{}
template<typename T>
inline GNGData<T>::GNGData(GNGDataBase::FileType type_in)
    : GNGData(type_in, 0)
{}
template<typename T>
inline
GNGData<T>::GNGData(GNGDataBase::FileType type_in, unsigned int ngram_length)
    : GNGDataBase(type_in, ngram_length)
    , word_to_index(QHash<T, unsigned int>())
    , words(QVector<T>())
    , chosen_words(QVector<T>())
    , not_chosen_words(QVector<T>())
{}


template<typename T>
inline void GNGData<T>::updateChosenSummary(){
    setChosenWords();
    updateChosenCounts();
//    qDebug() << "updateChosenSummary()" << info_string << "c/nc =" << chosen_count << "/"
//             << not_chosen_count << ", c/nc size =" << chosen_words.size() << "/" << not_chosen_words.size() ;
    Q_ASSERT( (chosen_count + not_chosen_count) == words.size());
    Q_ASSERT( chosen_count == chosen_words.size());
    Q_ASSERT( not_chosen_count == not_chosen_words.size());
}
template<typename T>
inline void GNGData<T>::finishAFterDataAddedOrDeleted(){
    setWordToIndex();
    updateChosenSummary();
    Q_ASSERT(chosen_words.size() == chosen_count);
    Q_ASSERT(not_chosen_words.size() == not_chosen_count);
}
template<typename T>
inline void GNGData<T>::setChosenWords(){
    chosen_words.clear();
    not_chosen_words.clear();
    Q_ASSERT(chosen.size() == words.size());
   // this failed when i tried to szve and load a phrase_1_gram
    for(unsigned int i = 0; i < chosen.size(); ++i){
        if(chosen[i]){
            chosen_words.push_back(words[i]);
        }
        else{
            not_chosen_words.push_back(words[i]);
        }
    }
}
template<typename T>
inline bool GNGData<T>::inChosenWords(const T& word_to_check)const{ return chosen_words.contains(word_to_check);}
template<typename T>
inline bool GNGData<T>::inNotChosenWords(const T& word_to_check)const{ return not_chosen_words.contains(word_to_check);}
template<typename T>
inline QVector<T> GNGData<T>::getChosenWords()const{ return chosen_words;}
template<typename T>
inline QVector<T> GNGData<T>::getNotChosenWords()const{ return not_chosen_words;}
template<typename T>
inline const QVector<T>& GNGData<T>::getChosenWordsCRef()const{ return chosen_words;}
template<typename T>
inline const QVector<T>& GNGData<T>::getNotChosenWordsCRef()const{ return not_chosen_words;}
template<typename T>
unsigned int GNGData<T>::getChosenCount()const{ return chosen.count(true);}
template<typename T>
unsigned int GNGData<T>::getNotChosenCount()const{ return chosen.count(false);}
template<typename T>
inline
bool GNGData<T>::loadFileData(const QString& full_path,
                          std::vector<std::vector<std::any>>& data_to_fill, unsigned int ngram_length)const{
    switch(type){
        case GNGDataBase::one_gram:        return load1Gram(full_path, data_to_fill);
        case GNGDataBase::n_gram_no_chosen:return loadNGramNoChosen(full_path, data_to_fill, ngram_length);
        case GNGDataBase::n_gram_chosen:   return loadNGramWithChosen(full_path, data_to_fill, ngram_length);
        case GNGDataBase::unique_words:    return loadPUW(full_path, data_to_fill);
        default:                           return false;
    }
    return false;
}
template<typename T>
inline
bool GNGData<T>::saveFileData(const QString& full_path,
                              const std::vector<std::vector<std::any>>& data_to_save,
                              unsigned int ngram_length)const{
    switch(type){
        case GNGDataBase::one_gram:         return save1Gram(full_path, data_to_save);
        case GNGDataBase::n_gram_chosen:    return saveNGram(full_path, data_to_save, ngram_length);
        case GNGDataBase::unique_words:     return savePUW(full_path, data_to_save);
        case GNGDataBase::n_gram_no_chosen: return false;
        default:                            return false;
    }
    return false;
}
// use public load save
template<typename T>
inline
bool GNGData<T>::load1Gram(const QString& full_path, std::vector<std::vector<std::any>>& data_to_fill)const{
    std::vector<std::vector<std::string>> file_string_data;
    //if(utilities::readCSVFile(path, file_string_data)){
    if(utilities::readCSVFile(full_path.toStdString(), file_string_data)){
        data_to_fill.clear();
        data_to_fill.reserve(file_string_data.size());
        for(const auto& item : file_string_data){
            std::vector<std::any> next_entry;
            next_entry.reserve(5);
            next_entry.push_back( std::any( std::any_cast<std::string>(item.at(0))));
            next_entry.push_back( std::any(std::stoull(std::any_cast<std::string>(item.at(1))))) ;
            next_entry.push_back( std::any((bool)std::stoi(item.at(2))));
            next_entry.push_back( std::any(item.at(3)));
            next_entry.push_back( std::any( (unsigned int)std::stoul(item.at(4))));
           data_to_fill.push_back(next_entry);
        }
        return true;
    }
    return false;
}
template<typename T>
inline
bool GNGData<T>::loadNGramNoChosen(const QString& full_path,
                                  std::vector<std::vector<std::any>>& data_to_fill,
                                  unsigned int ngram_length)const{
    qDebug() << "loadNGramNoChosen" << full_path;
    std::vector<std::vector<std::string>> file_string_data;
    if(utilities::readCSVFile(full_path.toStdString(), file_string_data)){
        unsigned int read_items_per_line = 0, read_count_index=0, fill_items_per_line =0;
        // check ngram size
        if(file_string_data.size() > 0 ){
            read_items_per_line = file_string_data.at(0).size();
            Q_ASSERT(ngram_length == (read_items_per_line -1));
            read_count_index = ngram_length;
            fill_items_per_line = 2*ngram_length + 2;
        }
        data_to_fill.clear();
        data_to_fill.reserve(file_string_data.size());
        for(const auto& item : file_string_data){
            std::vector<std::any> next_line_data;
            next_line_data.reserve(fill_items_per_line);
            for (unsigned int i = 0; i < ngram_length; ++i) {
                next_line_data.push_back(std::any(item.at(i)));
            }
            for (unsigned int i = 0; i < ngram_length; ++i) {
                next_line_data.push_back(std::any(true));
            }
            next_line_data.push_back( std::any(std::stoull(item.at(read_count_index))));
            next_line_data.push_back(std::any(true));
            data_to_fill.push_back(next_line_data);
        }
        return true;
    }
    return false;
}
template<typename T>
bool GNGData<T>::loadNGramWithChosen(const QString& full_path,
                                     std::vector<std::vector<std::any>>& data_to_fill,
                                     unsigned int ngram_length)const{
    std::vector<std::vector<std::string>> file_string_data;
    if(utilities::readCSVFile(full_path.toStdString(), file_string_data)){
        unsigned int items_per_line = 0, count_index, chosen_index;
        // check ngram size
        if(file_string_data.size() > 0 ){
            items_per_line = file_string_data.at(0).size();
            Q_ASSERT(ngram_length == (items_per_line - 2) / 2);
            count_index = items_per_line - 2;
            chosen_index = items_per_line - 1;
        }
        data_to_fill.clear();
        data_to_fill.reserve(file_string_data.size());
        for(const auto& item : file_string_data){
            std::vector<std::any> next_line_data;
            next_line_data.reserve(items_per_line);
            bool bool_value;
            for (unsigned int i = 0; i < ngram_length; ++i) {
                next_line_data.push_back(std::any(item.at(i)));
            }
            for (unsigned int i = ngram_length; i < 2*ngram_length; ++i) {
                Q_ASSERT( (item.at(i) == "1") || (item.at(i) == "0"));
                utilities::stringToBool(item.at(i), bool_value);
                next_line_data.push_back(std::any(bool_value));
            }
            next_line_data.push_back(std::any(std::stoull(item.at(count_index))));
            Q_ASSERT( (item.at(chosen_index) == "1") || (item.at(chosen_index) == "0"));
            utilities::stringToBool(item.at(chosen_index), bool_value);
            next_line_data.push_back(std::any(bool_value));
            data_to_fill.push_back(next_line_data);
        }
        return true;
    }
    return false;
}
template<typename T>
inline
bool GNGData<T>::loadPUW(const QString& full_path, std::vector<std::vector<std::any>>& data_to_fill)const{
    std::vector<std::vector<std::string>> file_string_data;
    if(utilities::readCSVFile(full_path.toStdString(), file_string_data)){
        data_to_fill.clear();
        data_to_fill.reserve(file_string_data.size());
        for(const auto& item : file_string_data){
            std::vector<std::any> next_entry;
            next_entry.reserve(4);
            next_entry.push_back(std::any(item.at(0)));
            next_entry.push_back(std::any(std::stoull(item.at(1))));
            next_entry.push_back(std::any(std::stoull(item.at(2))));
            next_entry.push_back(std::any((bool)std::stoi(item.at(3))));
            data_to_fill.push_back(next_entry);
        }
        return true;
    }
    return false;
}
template<typename T>
inline
bool GNGData<T>::save1Gram(const QString& full_path,const std::vector<std::vector<std::any>>& data_to_write)const{
    qDebug() << "GNGData<T>::saveOneGram, " << full_path;
    std::vector<std::vector<std::string>> string_data;
    for(const auto& item: data_to_write){
        if(item.size() != 5){// !
            qDebug() << "GNGData<T>::saveOneGram ERROR not enough columns in file";
            return false;
        }
        std::vector<std::string> next_line;// !
        next_line.reserve(5);
        next_line.push_back(std::any_cast<std::string>(item.at(0)));
        next_line.push_back(std::to_string(std::any_cast<unsigned long long>(item.at(1))));
        next_line.push_back(std::to_string(std::any_cast<bool>(item.at(2))));
        next_line.push_back(std::any_cast<std::string>(item.at(3)));
        next_line.push_back(std::to_string(std::any_cast<unsigned int>(item.at(4))));
        string_data.push_back(next_line);
    }
    return utilities::writeCSVFile(full_path.toStdString(), string_data);
}
template<typename T>
inline
bool GNGData<T>::saveNGram(const QString& full_path,
                          const std::vector<std::vector<std::any>>& data_to_write,
                          unsigned int ngram_length)const{
    std::vector<std::vector<std::string>> string_data;
    unsigned int count_index, chosen_index=0, items_per_line = 0;
    // work out ngram size
    if(data_to_write.size() > 0){
        items_per_line = data_to_write[0].size();
        Q_ASSERT( (items_per_line - 2) / 2 == ngram_length);
        count_index = items_per_line - 2;
        chosen_index = items_per_line - 1;
    }
    for(const auto& item: data_to_write){
        std::vector<std::string> next_line;
        next_line.reserve(items_per_line);
        for(unsigned int i = 0; i < ngram_length; ++i ){
            next_line.push_back(std::any_cast<std::string>(item.at(i)));
        }
        for(unsigned int i = 0; i < ngram_length; ++i ){
            next_line.push_back(std::to_string(std::any_cast<bool>(item.at(ngram_length+i))));
        }
        next_line.push_back(std::to_string(std::any_cast<unsigned long long>(item.at(count_index))));
        next_line.push_back(std::to_string(std::any_cast<bool>(item.at(chosen_index))));
        string_data.push_back(next_line);
    }
//    for(const auto& entry: data_to_write){
////        std::vector<std::any>::const_iterator entry_it = entry.begin();
//        std::vector<std::string> next_line;
//        next_line.reserve(items_per_line);
//        for(unsigned int i = 0; i < ngram_length; ++i ){
//            next_line.push_back(std::any_cast<std::string>(entry.at(i)));
//            ++entry_it;
//        }
//        for(unsigned int i = 0; i < ngram_length; ++i ){
//            next_line.push_back(std::to_string(std::any_cast<bool>(*entry_it)));
//            ++entry_it;
//      }
//        next_line.push_back(std::to_string(std::any_cast<unsigned long long>(*entry_it)));
//        ++entry_it;
//        next_line.push_back(std::to_string(std::any_cast<bool>(*entry_it)));
//        ++entry_it;
//        string_data.push_back(next_line);
//    }
    return utilities::writeCSVFile(full_path.toStdString(), string_data);
}
template<typename T>
inline
bool GNGData<T>::savePUW(const QString& full_path,const std::vector<std::vector<std::any>>& data_to_write)const{
    std::vector<std::vector<std::string>> string_data;
    for(const auto& item: data_to_write){
        if(item.size() != 4){// !
            qDebug() << "GNGData<T>::savePUW ERROR number of columns not correct in file" << full_path;
            return false;
        }
        std::vector<std::string> next_line;// !
        next_line.reserve(4);
        next_line.push_back(std::any_cast<std::string>(item.at(0)));
        next_line.push_back(std::to_string (std::any_cast<unsigned long long>(item.at(1))));
        next_line.push_back(std::to_string (std::any_cast<unsigned long long>(item.at(2))));
        next_line.push_back(std::to_string (std::any_cast<bool>(item.at(3))));
        string_data.push_back(next_line);
    }
    return utilities::writeCSVFile(full_path.toStdString(), string_data);
}
template<typename T>
inline
void GNGData<T>::setLocalDataFilePath(QString const& directory,  QString const& file_name){
    local_data_filename = file_name;
    local_data_filedir = directory;
    local_data_filepath = QString::fromStdString(utilities::getFullPath(directory.toStdString(), file_name.toStdString()));
}
template<typename T>
inline
void GNGData<T>::setRawDataFilePath(QString const& directory,  QString const& filename){
    raw_data_filename = filename;
    raw_data_filedir = directory;
    raw_data_filepath = QString::fromStdString(utilities::getFullPath(directory.toStdString(), filename.toStdString()));
}
template<typename T>
inline
void GNGData<T>::setRawDataFilePath(QString const& path){
    QFileInfo fi(path);
    raw_data_filedir = fi.absolutePath();
    raw_data_filename = fi.fileName();
    raw_data_filepath = path;
}
template<typename T>
inline
void GNGData<T>::setLocalDataFilePath(QString const& path){
    QFileInfo fi(path);
    local_data_filedir = fi.absolutePath();
    local_data_filename = fi.fileName();
    local_data_filepath = path;
}
template<typename T>
inline
void GNGData<T>::setWordToIndex(){
    word_to_index.clear();
    word_to_index.reserve(words.size());
    for(unsigned int i =0; i < words.size(); ++i ){
        auto it = word_to_index.find(words[i]);
        if( it == word_to_index.end()){
            word_to_index[words[i]] = i;
        }
        else{
            qDebug() << "!!ERROR!!" << words[i] << " already entered";
        }
    }
}
template<typename T>
inline
bool GNGData<T>::isChosen(const T& word){
    unsigned int index = 0;
    if(getWordIndex(word,index)){
        return chosen[index] == true;
    }
    return false;
}
template<typename T>
inline
bool GNGData<T>::isNotChosen(const T& word){
    unsigned int index = 0;
    if(getWordIndex(word,index)){
        return chosen[index] == false;
    }
    return false;
}
template<typename T>
inline
bool GNGData<T>::hasWordAtIndex(const T& word_to_lookup)const{
    return word_to_index.contains(word_to_lookup);
}
// TODO is this used much?
template<typename T>
inline
bool GNGData<T>::getWordIndex(const T& word_to_lookup, unsigned int& index)const{
    if(word_to_index.contains(word_to_lookup)){
        index = word_to_index[word_to_lookup];
        return true;
    }
    return false;
}
template<typename T>
inline
    unsigned int GNGData<T>::getWordIndex(const T& word_to_lookup)const{
    return word_to_index.at(word_to_lookup);
}
#endif // GNG_DATA_H
