#include "gng_ngram.h"
#include "utilities.h"
#include <QDebug>
#include <QVariant>
#include <QFileInfo>

GNGNGram::GNGNGram(QVector<unsigned int> const& word_lengths,
                   unsigned int phrase_index,
                   unsigned int ngram_index)
    : GNGData<QVector<QString>>(n_gram_no_chosen, // default to raw data remember to change to
                                                // n_gram_chosen to load local data after init
                              word_lengths.size())
    , ngram_word_lengths(word_lengths)
    , word_index_in_phrase(QVector<unsigned int>())
    , ngram_index(ngram_index)
    , word_chosen(QVector<QVector<bool>>())
    , default_file_name(QString())
    , data_changed_on_last_setNotChosenByPUW(false) // has to be set when file data is loaded
    , changes_on_last_setNotChosenByPUW(0) // has to be set when file data is loaded
    , can_add_ngrams(true)
{
    // always at least 1 word
    Q_ASSERT (ngram_word_lengths.size() > 0);
    // generate "default" ngram file name from word lengths
    // hacky 100 is an s and 111 is an e .. :(
    if(ngram_word_lengths[0] == 100){
        default_file_name = "s";
    }
    else{
        default_file_name.setNum(ngram_word_lengths[0]) ;
    }
    word_index_in_phrase.push_back( phrase_index);
    for(int i = 1; i < ngram_word_lengths.size(); ++i )
    {
        QTextStream(&default_file_name) << "_" << ngram_word_lengths[i];
        word_index_in_phrase.push_back( phrase_index + i);
    }
    QTextStream(&default_file_name) << ".csv";
}
bool GNGNGram::deleteNotChosen2(bool and_squeze){
    QVector<unsigned int> chosen_indexes = utilities::findIndexesOf<bool>(chosen,true);
    unsigned int start_size = chosen.size();
    unsigned int end_size = chosen_indexes.size();
    unsigned int delete_size = start_size - end_size;
    QVector<QVector<QString>> words2;
    words2.reserve(chosen_indexes.size()) ;
    QVector<bool> chosen2;
    chosen2.reserve(chosen_indexes.size());
    QVector<QString> ngram_string2;
    ngram_string2.reserve(chosen_indexes.size());
    QVector<unsigned long long> counts2;
    counts2.reserve(chosen_indexes.size());
    QVector<QVector<bool>> word_chosen2;
    word_chosen2.reserve(chosen_indexes.size());
    for(const auto& i : chosen_indexes){
        words2.push_back( words.at(i));
        chosen2.push_back( chosen.at(i));
        ngram_string2.push_back( ngram_string.at(i));
        counts2.push_back( counts.at(i));
        word_chosen2.push_back( word_chosen.at(i));
    }
    words = words2;
    chosen = chosen2;
    ngram_string = ngram_string2;
    counts = counts2;
    word_chosen = word_chosen2;
    if(and_squeze){
        squeeze();
    }
    finishAFterDataAddedOrDeleted();
    Q_ASSERT( end_size == words.size());
    Q_ASSERT( end_size == chosen.size());
    Q_ASSERT( end_size == counts.size());
    Q_ASSERT( end_size == ngram_string.size());
    Q_ASSERT( end_size == word_chosen.size());
    qDebug() << "GNGNGram::deleteNotChosen,"  << ngram_index << "start/end/dif =" << start_size
             << end_size << delete_size;
    return true;
}
void GNGNGram::squeeze(){
    words.squeeze();
    chosen.squeeze();
    ngram_string.squeeze();
    counts.squeeze();
    word_chosen.squeeze();
}

bool GNGNGram::deleteNotChosen(bool and_squeze){
    unsigned int start_size = chosen.size();
    QVector<unsigned int> not_chosen_indexes = utilities::findIndexesOf<bool>(chosen,false);
    unsigned int delete_size = not_chosen_indexes.size();
    unsigned int end_size = start_size - delete_size;
    for(auto it = not_chosen_indexes.rbegin(); it != not_chosen_indexes.rend(); it++ ){
        words.removeAt(*it);
        chosen.removeAt(*it);
        ngram_string.removeAt(*it);
        counts.removeAt(*it);
        word_chosen.removeAt(*it);
    }
    if(and_squeze){
        squeeze();
    }
    finishAFterDataAddedOrDeleted();
    Q_ASSERT( end_size == words.size());
    Q_ASSERT( end_size == chosen.size());
    Q_ASSERT( end_size == counts.size());
    Q_ASSERT( end_size == ngram_string.size());
    Q_ASSERT( end_size == word_chosen.size());
    qDebug() << "GNGNGram::deleteNotChosen,"  << ngram_index << "start/end/dif =" << start_size
             << end_size << delete_size;
    return true;
}
bool GNGNGram::makeConsistentWordsChosenAndPUW(const GNGPhraseWord* puw, int& changes){
    //timer.start();
    //auto ts = timer.elapsed();
    changes = 0;
    if( hasWordAtIndex(puw->phrase_index)){
        int ngram_index = getLocalIndexOfPhraseIndex(puw->phrase_index);
        //qInfo() << info_string << "setWordsChosenByPUW," << ngram_index << " " << puw->phrase_index;
        // choose the smallest of puw chosen / not chosen words and copy to puw_words
        QVector<QString> puw_words;
        bool puw_words_are_chosen;
        //unsigned int cc = puw->getChosenCount();
//        /unsigned int ncc = puw->getNotChosenCount();
        if(puw->getChosenCount() >= puw->getNotChosenCount()){
            puw_words_are_chosen = true;
            puw_words = puw->getChosenWordsCRef();
            //qInfo() << "puw_words are chosen, size() =" <<puw_words.size();
        }
        else{
            puw_words_are_chosen = false;
            puw_words = puw->getNotChosenWords();
            //qInfo() << "puw_words are NOT chosen, size() =" <<puw_words.size();
        }
        Q_ASSERT(words.size() == word_chosen.size());
        int counter1=0, counter2=0;

// NEW VERSION, BUT BROKE?
//        for(unsigned int i =0; i < words.size(); ++i){
//            bool& ngram_word_is_currently_chosen = word_chosen[i][ngram_index];
//            bool ngram_word_in_puw_words = puw_words.contains( words.at(i).at(ngram_index) );
//            counter1 += 1;
//            // 3 true/false items, puw_words_are_chosen ngram_word_in_puw_words ngram_is_currently_chosen
//            // ngram_is_currently_chosen needed to know if a change has been made
//            if( puw_words_are_chosen &&  ngram_word_in_puw_words &&  ngram_word_is_currently_chosen ){
//                // ngram_word in chosen words && ngram_word is chosen
//                counter2+=1;
//            }
//            else if( puw_words_are_chosen &&  ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
//                // ngram_word in chosen words && ngram_word is NOT chosen, flip
//                ngram_word_is_currently_chosen = true;
//                changes +=1;
//                counter2+=1;
//            }
//            else if( puw_words_are_chosen && !ngram_word_in_puw_words &&  ngram_word_is_currently_chosen ){
//                // ngram_word NOT in chosen words && ngram_word is chosen, flip
//                ngram_word_is_currently_chosen = false;
//                changes +=1;
//                counter2+=1;
//            }
//            else if( puw_words_are_chosen && !ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
//                // ngram_word NOT in chosen words && ngram_word is NOT chosen
//                counter2+=1;
//            }
//            else if( !puw_words_are_chosen &&  ngram_word_in_puw_words &&  ngram_word_is_currently_chosen ){
//                // ngram_word in NOT chosen words && ngram_word is chosen, flip
//                ngram_word_is_currently_chosen = false;
//                changes +=1;
//                counter2+=1;
//            }
//            else if( !puw_words_are_chosen && !ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
//                // ngram_word NOT in NOT chosen words && ngram_word is NOT chosen, flip
//                ngram_word_is_currently_chosen = true;
//                changes +=1;
//                counter2+=1;
//                //qDebug() << "can you see me NOW?";
//            }
//            else if( !puw_words_are_chosen && ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
//                counter2+=1;
//            }
//            else if( !puw_words_are_chosen && !ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
//                ngram_word_is_currently_chosen = true;
//                changes +=1;
//                counter2+=1;
//                //qDebug() << "can you see me NOW?";
//            }
//            else if( !puw_words_are_chosen && !ngram_word_in_puw_words && ngram_word_is_currently_chosen ){
//                counter2+=1;
//            }
//            else{
//                qDebug() << "ERROR (unexpetced case not handled.)";
//                qDebug() << "puw_words_are_chosen =" << puw_words_are_chosen;
//                qDebug() << "ngram_word_in_puw_words =" << ngram_word_in_puw_words;
//                qDebug() << "ngram_word_is_currently_chosen =" << ngram_word_is_currently_chosen;
//            }
//        }
    // loop over every word in the ngram and set to puw_words_chosen, AND count number of changes
        QList<QList<QString>>::const_iterator w_it = words.constBegin();
        QList<QList<bool>>::iterator wc_it = word_chosen.begin();
        while( (w_it != words.constEnd()) && (wc_it != word_chosen.end()) ) {
            bool& ngram_word_is_currently_chosen = (*wc_it)[ngram_index];
            const QString& ngram_word = (*w_it)[ngram_index];
            bool ngram_word_in_puw_words = puw_words.contains(ngram_word);
            counter1 += 1;
            // 3 items (each either true, false
            // TODO too complex re-do someway?? or maybe not
            // puw_words_are_chosen ngram_word_in_puw_words ngram_is_currently_chosen (needed to know if a change has been made)
                 if( puw_words_are_chosen &&  ngram_word_in_puw_words &&  ngram_word_is_currently_chosen ){
                    // ngram_word in chosen words && ngram_word is chosen
                      counter2+=1;
                 }
            else if( puw_words_are_chosen &&  ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
                     // ngram_word in chosen words && ngram_word is NOT chosen, flip
                     ngram_word_is_currently_chosen = true;
                     changes +=1;
                     counter2+=1;
                 }
            else if( puw_words_are_chosen && !ngram_word_in_puw_words &&  ngram_word_is_currently_chosen ){
                     // ngram_word NOT in chosen words && ngram_word is chosen, flip
                     ngram_word_is_currently_chosen = false;
                     changes +=1;
                     counter2+=1;
                 }
            else if( puw_words_are_chosen && !ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
                     // ngram_word NOT in chosen words && ngram_word is NOT chosen
                     counter2+=1;
                 }
            else if( !puw_words_are_chosen &&  ngram_word_in_puw_words &&  ngram_word_is_currently_chosen ){
                     // ngram_word in NOT chosen words && ngram_word is chosen, flip
                     ngram_word_is_currently_chosen = false;
                     changes +=1;
                     counter2+=1;
                 }
             else if( !puw_words_are_chosen && !ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
                     // ngram_word NOT in NOT chosen words && ngram_word is NOT chosen, flip
                     ngram_word_is_currently_chosen = true;
                      changes +=1;
                      counter2+=1;
                      //qDebug() << "can you see me NOW?";
                  }
             else if( !puw_words_are_chosen && ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
                     counter2+=1;
                }
            else if( !puw_words_are_chosen && !ngram_word_in_puw_words && !ngram_word_is_currently_chosen ){
                     ngram_word_is_currently_chosen = true;
                     changes +=1;
                     counter2+=1;
                     //qDebug() << "can you see me NOW?";
                 }
            else if( !puw_words_are_chosen && !ngram_word_in_puw_words && ngram_word_is_currently_chosen ){
                      counter2+=1;
            }
            else{
                     qDebug() << "ERROR (unexpetced case not handled.)";
                     qDebug() << "puw_words_are_chosen =" << puw_words_are_chosen;
                     qDebug() << "ngram_word_in_puw_words =" << ngram_word_in_puw_words;
                     qDebug() << "ngram_word_is_currently_chosen =" << ngram_word_is_currently_chosen;
                 }
            ++w_it;
            ++wc_it;
        }
        //qDebug() << counter1 << counter2;
        Q_ASSERT(counter1 == counter2);
        //qDebug() << "TIMING: setWordsChosenByPUW took" << timeSince(ts);
    }
    return true;
}
bool GNGNGram::makeConsistentWordsChosenAndPUW(const QVector<GNGPhraseWord*>& phrase_unique_words){
    changes_on_last_setWordsChosenByPUW = 0;
    for(auto& puw : phrase_unique_words){
        int changes = 0;
        puw->updateChosenSummary();
        if(makeConsistentWordsChosenAndPUW(puw, changes)){
            changes_on_last_setWordsChosenByPUW += changes;
        }
    }
    data_changed_on_last_setWordsChosenByPUW = changes_on_last_setWordsChosenByPUW > 0;
//    qDebug() << "GNGNGram::setWordsChosenByPUW return " << data_changed_on_last_setWordsChosenByPUW <<
//                ", changes " << changes_on_last_setWordsChosenByPUW;
    return data_changed_on_last_setWordsChosenByPUW;
}
QSet<QString> GNGNGram::getUniqueChosenWordsAtPhraseWordIndex(unsigned int pwi)const{
    int li = getLocalIndexOfPhraseIndex(pwi);
    if(li != -1){
        return getUniqueChosenWordsAtNgramWordIndex(li);
    }
    return QSet<QString>();
}
QSet<QString> GNGNGram::getUniqueChosenWordsAtNgramWordIndex(unsigned int ngram_word_index)const{
    QSet<QString> r;
    if( ngram_word_index <= ngram_word_lengths.size()) // ngram_word_index is valid
    {
        for(unsigned int i = 0; i < words.size(); ++i){
            if(chosen.at(i)){
                r.insert(words.at(i).at(ngram_word_index));
            }
        }
    }
    return r;
}

bool GNGNGram::setChosenByNgramWordsChosen(){
    Q_ASSERT(chosen.size() == word_chosen.size());
    for(unsigned int i=0; i < chosen.size(); ++i){
        if( can_add_ngrams ){
            chosen.replace(i, !word_chosen.at(i).contains(false));
        }
        else if(word_chosen.at(i).contains(false)){
                chosen.replace(i,false);
        }
    }
    return true;
}

int GNGNGram::getLocalIndexOfPhraseIndex(unsigned int phrase_index)const{
    int r = -1;
    for(int i = 0; i < word_index_in_phrase.size(); ++i ){
        if(word_index_in_phrase.at(i) == phrase_index){
            r = i;
        }
    }
    return r;
}
// ============================================================================
// ============================================================================
// ============================================================================
bool GNGNGram::saveLocalData() const{
    qDebug() << "GNGNGram::saveLocalData " << local_data_filepath;
    std::vector<std::vector<std::any>> data;
    if( getAsFileData(data)){
        return saveFileData(local_data_filepath, data, ngram_length);
    }
    return false;
}
bool GNGNGram::loadLocalData(){
    qDebug() << "GNGNGram::loadLocalData " << local_data_filepath;
    std::vector<std::vector<std::any>> data;
    if( loadFileData(local_data_filepath,data, ngram_length)){
        return setFromFileData(data);
    }
    return false;
}
bool GNGNGram::loadRawData(){
    qDebug() << "GNGNGram::loadRawData " << raw_data_filepath;
    std::vector<std::vector<std::any>> data;
    if( loadFileData(raw_data_filepath,data, ngram_length)){
       return setFromFileData(data);
    }
    return false;
}
// dont EVER USE!!!
bool GNGNGram::saveRawData()const{
    qDebug() << "This should never be called.";
    std::vector<std::vector<std::any>> data;
    if( getAsFileData(data)){
        //return saveFileData(raw_data_filepath, data);
    }
    return false;
}

bool GNGNGram::load(bool default_location ) // this version loads a raw file with NO chosen column
{
    if(default_location){
        type = n_gram_no_chosen;
        return loadDefaultFileData();
    }
    type = n_gram_chosen;
    return loadLocalData();
}

bool GNGNGram::loadDefaultFileData() // this version loads a raw file with NO chosen column
{
    setRawDataFilePath( config.path_to_raw_ngrams, default_file_name);
    return loadRawData();
}
bool GNGNGram::setFromFileData(const std::vector<std::vector<std::any>>& raw_data) {
    if(raw_data.size() < 1){
        return false;
    }
    Q_ASSERT(raw_data[0].size() == 2* ngram_length + 2 );
    words.clear();
    ngram_string.clear();
    counts.clear();
    chosen.clear();
    word_chosen.clear();
    words.reserve(raw_data.size());
    ngram_string.reserve(raw_data.size());
    counts.reserve(raw_data.size());
    chosen.reserve(raw_data.size());
    word_chosen.reserve(raw_data.size());
    for(const auto& item : raw_data )
    {   // bit odd
        QVector<QString> next_words;
        next_words.reserve(ngram_length);
        QVector<bool> base_word_chosen;
        base_word_chosen.reserve(ngram_length);
        std::vector<std::any>::const_iterator it = item.begin();
        for(int i = 0; i < (int)ngram_length; ++i){
            next_words.push_back(QString::fromStdString(std::any_cast<std::string>(*it)));
            ++it;
        }
        for(int i = 0; i < (int)ngram_length; ++i){
            base_word_chosen.push_back(std::any_cast<bool>(*it));
            ++it;
        }
        counts.push_back( std::any_cast<unsigned long long>(*it));
        ++it;
        chosen.push_back( std::any_cast<bool>(*it));
        words.push_back(next_words);
        ngram_string.push_back(next_words.join(" "));
        word_chosen.push_back(base_word_chosen);
    }
    finishAFterDataAddedOrDeleted();
    return true;
}
bool GNGNGram::getAsFileData(std::vector<std::vector<std::any>>& data_to_fill)const{
    data_to_fill.clear();
    data_to_fill.reserve(words.size());
    for(unsigned int i = 0; i < words.size(); ++i){ // !
        std::vector<std::any> next_line;
        next_line.reserve(ngram_length*2 + 2);
        for(const auto& w : words.at(i)){
            std::string nw = w.toStdString();
            next_line.push_back( std::any( nw ) );
        }
        for(const auto& w : word_chosen.at(i)){
            next_line.push_back( std::any( w ) );
        }
        next_line.push_back( std::any(counts.at(i)) );
        next_line.push_back( std::any(chosen.at(i)) );
        data_to_fill.push_back(next_line);
    }
    return true;
}
