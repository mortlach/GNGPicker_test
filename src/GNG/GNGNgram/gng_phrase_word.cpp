#include <QFileInfo>
#include <QByteArray>
#include "gng_phrase_word.h"
#include "utilities.h"

GNGPhraseWord::GNGPhraseWord(unsigned int phrase_index,
                                         unsigned int word_length,
                                         GNG1GramData* gng_word_data)
    : GNGData(GNGDataBase::FileType::unique_words)
    //, chosen_words(QVector<QString>())
    //, not_chosen_words(QVector<QString>()) // TODO empty_char ??? const??
    , word_length(word_length) // TODO empty_char ??? const??
    , mustbe_character(QString())
    , maybe_interrupter(QString())
   // , count(QVector<unsigned long long>())
    , mustbe_active(false)
    , maybe_active(false)
    , previous_mustbe_character(mustbe_character)
    , previous_maybe_interrupter(maybe_interrupter)
    , data_changed_last_apply_cut(false)
    , word_index_in_gng_words(QVector<unsigned int>())
    , count_in_ngrams(QVector<unsigned long long>())
    , phrase_index(phrase_index)
    , my_gng_word_data(gng_word_data)
    , changes_on_last_compareWithWordList(0)

{   // init to empty
    mustbe_character.clear();
    maybe_interrupter.clear();
    for(unsigned int i = 0; i < word_length; ++i){
        mustbe_character += utilities::empty_string;
        maybe_interrupter += utilities::empty_string;
    }
}
bool GNGPhraseWord::loadLocalData(){
    qDebug() << "GNGPhraseWord::loadLocalData " << local_data_filepath;
    std::vector<std::vector<std::any>> data;
    if( loadFileData(local_data_filepath,data)){
        return setFromFileData(data);
    }
    return false;
}
void GNGPhraseWord::setIndexInGNGWords(){
    word_index_in_gng_words.clear();
    word_index_in_gng_words.reserve(words.size());
    for(const auto& word : words){
        word_index_in_gng_words.append(my_gng_word_data->word_to_index.value(word));
    }
}
void GNGPhraseWord::deleteAt(unsigned int i){
    words.removeAt(i);
    chosen.removeAt(i);
    word_index_in_gng_words.removeAt(i);
}
void GNGPhraseWord::deleteAt(const QVector<unsigned int>& i){
    for(QVector<unsigned int>::const_reverse_iterator it= i.rbegin(); it!=i.rend(); ++it){
        deleteAt(*it);
    }
}
void GNGPhraseWord::setFromWords(const QHash<QString, QPair<unsigned long long, unsigned long long>>& words_in){
    unsigned int word_count = words_in.size();
    words.clear();
    counts.clear();
    count_in_ngrams.clear();
    chosen.clear();
    words.reserve(word_count);
    counts.reserve(word_count);
    count_in_ngrams.reserve(word_count);
    chosen.reserve(word_count);
    chosen_words.reserve(word_count);
    not_chosen_words.reserve(word_count);
    QHash<QString, QPair<unsigned long long, unsigned long long>>::const_iterator i = words_in.constBegin();
    while (i != words_in.constEnd()) {
        words.push_back(i.key());
        counts.push_back(i.value().first);
        count_in_ngrams.push_back(i.value().second);
        ++i;
    }
    qDebug() << "GNGPhraseWord::setFromWords() PUW_index =" << phrase_index <<
        "added" << word_count << "word";
    setIndexInGNGWords();
    setChosenFrom1GramData();
    finishAFterDataAddedOrDeleted();
}

bool GNGPhraseWord::setChosenFrom1GramData(){
    qDebug() << "setChosenFrom1GramData, start c/nc=" << getChosenCount() <<"/"<< getNotChosenCount();
    Q_ASSERT(chosen.capacity() == words.size() );
    //for(int i =0; i < words.size(); ++i){
    for(const auto& w : words){
        chosen.append(my_gng_word_data->isChosen(w));
    }
    updateChosenSummary();
    return true;
}

bool GNGPhraseWord::setFromFileData(const std::vector<std::vector<std::any>>& raw_data){
    words.clear();
    chosen.clear();
    count_in_ngrams.clear();
    counts.clear();
    words.reserve(raw_data.size());
    chosen.reserve(raw_data.size());
    count_in_ngrams.reserve(raw_data.size());
    counts.reserve(raw_data.size());
    chosen_words.reserve(raw_data.size());
    not_chosen_words.reserve(raw_data.size());
    // 0, string // 1, ull //2, ull // 3, bool
    for(const auto& item : raw_data){
        words.push_back(QString::fromStdString(std::any_cast<std::string>(item.at(0))));
        counts.push_back(std::any_cast<unsigned long long >(item.at(1)));
        count_in_ngrams.push_back(std::any_cast<unsigned long long >(item.at(2)));
        chosen.push_back(std::any_cast<bool>(item.at(3)));
    }
    setIndexInGNGWords();
    finishAFterDataAddedOrDeleted();
    return true;
}
bool GNGPhraseWord::getAsFileData(std::vector<std::vector<std::any>>& data_to_fill)const{
    data_to_fill.clear();
    data_to_fill.reserve(words.size());
    for(unsigned int i = 0; i < words.size(); ++i){ // !
        std::vector<std::any> next_line;
        next_line.reserve(4);
        next_line.push_back( std::any(words.at(i).toStdString())  );
        next_line.push_back( std::any(counts.at(i)) );
        next_line.push_back( std::any(count_in_ngrams.at(i)) );
        next_line.push_back( std::any(chosen.at(i)));
        data_to_fill.push_back(next_line);
    }
    return true;
}
bool GNGPhraseWord::deleteNotChosen2(bool){
    // faster than delete from orignal lists
    QVector<unsigned int> chosen_indexes = utilities::findIndexesOf<bool>(chosen,true);
    unsigned int start_size = chosen.size();
    unsigned int end_size = chosen_indexes.size();
    unsigned int delete_size = start_size - end_size;
    QVector<QString> words2;
    words2.reserve(chosen_indexes.size()) ;
    QVector<bool> chosen2;
    chosen2.reserve(chosen_indexes.size());
    QVector<unsigned long long> counts2;
    counts2.reserve(chosen_indexes.size());
    QVector<unsigned long long> count_in_ngrams2;
    count_in_ngrams2.reserve(chosen_indexes.size());
    for(const auto& i : chosen_indexes){
        words2.push_back( words.at(i));
        chosen2.push_back( chosen.at(i));
        counts2.push_back( counts.at(i));
        count_in_ngrams2.push_back( count_in_ngrams.at(i));
    }
    words = words2;
    chosen = chosen2;
    counts = counts2;
    count_in_ngrams = count_in_ngrams2;
    finishAFterDataAddedOrDeleted();
    Q_ASSERT( end_size == words.size());
    Q_ASSERT( end_size == chosen.size());
    Q_ASSERT( end_size == counts.size());
    Q_ASSERT( end_size == count_in_ngrams.size());
    qDebug() << "GNGPhraseWord::deleteNotChosen,"  << word_length << "start/end/dif =" << start_size
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
bool GNGPhraseWord::deleteNotChosen(bool){
    unsigned int start_size = chosen.size();
    QVector<unsigned int> not_chosen_indexes = utilities::findIndexesOf<bool>(chosen,false);
    unsigned int delete_size = not_chosen_indexes.size();
    unsigned int end_size = start_size - delete_size;
    for(auto it = not_chosen_indexes.rbegin(); it != not_chosen_indexes.rend(); it++ ){
        words.removeAt(*it);
        chosen.removeAt(*it);
        counts.removeAt(*it);
        count_in_ngrams.removeAt(*it);
    }
    finishAFterDataAddedOrDeleted();
    Q_ASSERT( end_size == words.size());
    Q_ASSERT( end_size == chosen.size());
    Q_ASSERT( end_size == counts.size());
    Q_ASSERT( end_size == count_in_ngrams.size());
    qDebug() << "GNGPhraseWord::deleteNotWords,"  << phrase_index << "start/end/dif =" << start_size
            << end_size << delete_size;
    return true;
}
bool GNGPhraseWord::applyCuts(){
    // set this flag to first at start of routine
    // if data changes are made set true
    data_changed_last_apply_cut = false;
    return setNotChosenByMustBeCharacter();
    // TODO here KEY functionality
    // setNotChosenByMaybeInterrutper(); TODO
}
bool GNGPhraseWord::setNotChosenByMustBeCharacter(){
    qDebug() << "setNotChosenByMustBeCharacter NEEDS DEBUG AND CROSS CHECK";
    qDebug() << "mustbe_character = " << mustbe_character;
    qDebug() << "mustbe_character.size() = " << mustbe_character.size();
    previous_mustbe_character = mustbe_character;
    // loop over every word
    for(unsigned int counter = 0; counter < words.size(); ++counter  ){
        QString& next_word = words[counter];
        bool& next_chosen = chosen[counter];
        unsigned int& next_gng_word_index = word_index_in_gng_words[counter];
        QString& next_runes = my_gng_word_data->runes[next_gng_word_index];
        qDebug() << "next_word = " << next_word;
        qDebug() << "next_chosen = " << next_chosen;
        qDebug() << "next_gng_word_index = " << next_gng_word_index;
        qDebug() << "next_runes = " << next_runes;
        // only change True to False
        if(next_chosen){
            for(unsigned int  c = 0; c < mustbe_character.size(); ++c ){
                QChar& nc = mustbe_character[c];
                QChar& nr = next_runes[c];
                if( nc != utilities::empty_char){
                    if(nc == nr ){
                        next_chosen = false;
                        data_changed_last_apply_cut = true;
                        // TODO emit
                    }
                }
            }
        }
    }
    return true;
}
bool GNGPhraseWord::setMustBeChar(const QChar& v, int index){
    if(index < mustbe_character.size()){
        qDebug() << mustbe_character;
        mustbe_character.replace(index, 1, v);
        qDebug() << mustbe_character;
        return true;
    }
    return false;
}
bool GNGPhraseWord::setMayBeChar(const QChar& v, int index){
    if(index < maybe_interrupter.size()){
        maybe_interrupter.replace(index, 1, v);
        return true;
    }
    return false;
}
bool GNGPhraseWord::setNotChosenByMaybeInterrutper()
{
    // TODO make work then make better
//    // indexes that don't contain interrutper:
//    QVector<unsigned int> not_interrupter = QVector<unsigned int>();
//    for(auto i = 0 ; i < maybe_interrupter.size(); ++i ){
//        if(maybe_interrupter[i] != utilities::empty_string)

//    }
    return true;
}
bool GNGPhraseWord::compareWithWordList(const QVector<QString>& words_in){
    // words_in are the unique chosen words from the ngrams
    // Only words in words_in can be set to chosen, otherwise, set to not chosen
    // THIS FUNCTION DOES NOT AFFECT WORDS THAT ARE IN words_in
    data_changed_with_last_compareWithWordList = false;
    changes_on_last_compareWithWordList = 0;
    // for over each local word, if it is NOT in words_in, set it's chosen = False, and count changes
    Q_ASSERT(words.size() == chosen.size());
    for(unsigned int i = 0; i < words.size(); ++i){
        //const QString& next_word = words.at(i);
        //bool& next_chosen = chosen[i];
        int index = words_in.indexOf(words.at(i));
        if(index == -1){
            if(chosen.at(i)){
                chosen.replace(i,false);
                changes_on_last_compareWithWordList += 1;
                if(changes_on_last_compareWithWordList == 1){
                    qDebug() << "PUW DATA CHANGED GNGPhraseWord::compareWithWordList\nPUWindex =" << phrase_index
                             << words.at(i) << " NOT IN passed words_in, chosen " << chosen.at(i);
                }
            }
        }
    }
    data_changed_with_last_compareWithWordList = changes_on_last_compareWithWordList > 0;
    //qDebug() << "Did data change? = " << data_changed_with_last_compareWithWordList;
    return data_changed_with_last_compareWithWordList;
}
