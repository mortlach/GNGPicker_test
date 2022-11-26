#include <QFile>
#include <QLocale>
#include "utilities.h"
#include "gng_phrase.h"

QVector<unsigned int> GNGPhrase::word_lengths;
unsigned int GNGPhrase::phrase_word_count = 0;
unsigned int GNGPhrase::phrase_item_count = 0;
unsigned int GNGPhrase::ngram_length = 0;
bool GNGPhrase::has_phrase_start = false;
bool GNGPhrase::has_phrase_end = false;
QVector<QVector<unsigned int>> GNGPhrase::ngram_word_lengths = QVector<QVector<unsigned int>>();
QVector<GNGNGram*> GNGPhrase::ngram_data = QVector<GNGNGram*>();
GNGNGram* GNGPhrase::start_ngram_data = nullptr;
GNGNGram* GNGPhrase::end_ngram_data = nullptr;
QVector<GNGPhraseWord*> GNGPhrase::phrase_unique_words = QVector<GNGPhraseWord*>(); // holds amortized data from each ngram for each word in the phrase
GNGPhrase::GNGPhrase()
    : config(GNGConfig())
    , gng_words(GNG1Grams())
{}
GNGPhrase::~GNGPhrase(){
    qDebug() << "GNGPhrase destructor called, need to safely delte items ?? ";//    cleanupNgramData();//    cleanupPhraseUniqueWords();
}
QString GNGPhrase::timeSince(int ts){
    int ms_now = QTime::currentTime().msecsSinceStartOfDay();
    double d_delta_s = (double)( ms_now - ts)/1000.0;
    QString r = QString::number(d_delta_s);
    return r;
}

// ===========================================================
// New phrase - not loaded from existing data, but created from raw data
bool GNGPhrase::newPhrase(QVector<unsigned int> const& word_lengths_in,
                          bool has_phrase_start_in,
                          bool has_phrase_end_in,
                          unsigned int ngram_length_in){
    auto ts = QTime::currentTime().msecsSinceStartOfDay();
    config.setPhraseWordLengths(word_lengths_in);
    config.setPhraseNgramLength(ngram_length_in);
    qDebug() << "\n\tTIMING: newPhrase: 11  config.save() =" << timeSince(ts) << "secs\n";
    qDebug() << "\n\t*****************************************";
    qDebug() << "\n\t****            New Phrase          ****";
    qDebug() << "\tword_lengths_in = " << word_lengths_in;
    qDebug() << "\tngram_length_in = " << ngram_length_in;
    qDebug() << "\tconfig.path_to_local_files = " << config.path_to_local_files;
    // copy data
    QVector<unsigned int> unique_word_lengths_in;
    for(const auto& item: word_lengths_in){
        if(!unique_word_lengths_in.contains(item)){
            unique_word_lengths_in.push_back(item);
        }
    }
    qDebug() << "\n\t**** setUpNewPhrase1Grams";
    bool should_continue  = gng_words.setUpNewPhrase1Grams(unique_word_lengths_in);

    // int startmytimer = QTime::currentTime().msecsSinceStartOfDay();
    has_phrase_start = has_phrase_start_in;
    has_phrase_end = has_phrase_end_in;
//    // sets up containers and ngram-meta-data
//    // loads raw data from default location (with no chosen col)
    if(!config.has_config){ // TODO has_config is a minimum viable flag not yet working
        qDebug() << "error in config";
    }
    //
    auto t0 = QTime::currentTime().msecsSinceStartOfDay();
    initializeForNewWordLengths(word_lengths_in,ngram_length_in);
    qDebug() << "\n\tTIMING: newPhrase: 1 initializeForNewWordLengths took " << timeSince(t0) << "secs\n";
    // load phrase ngrams from default - set local file but save AFTER rationalization
    auto t1 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = loadPhraseNgrams(true);
    qDebug() << "\n\tTIMING: newPhrase: 2 loadPhraseNgrams =" <<timeSince(t1) << timeSince(t0) << "secs\n";
    if( !should_continue ){
        return false;
    }
    // add data to PUW using ngram data, set local file but save AFTER rationalization
    auto t2 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = initPUWData();
    qDebug() << "\n\tTIMING: newPhrase: 3 initPUWData =" <<  timeSince(t2) << timeSince(t0)  << "secs\n";
    if( !should_continue ){ qDebug() << "initPUWData false"; return false;}
    auto t3 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = deleteAllNotChosenWords();
    qDebug() << "\n\tTIMING: newPhrase: 4 deleteNotChosenPhraseWords =" << timeSince( t3) << timeSince(t0)  << "secs\n";
    if( !should_continue ){ qDebug() << "!!ERROR!! deleteNotChosenPhraseWords false";return false;}
    auto t4 = QTime::currentTime().msecsSinceStartOfDay();
    bool ngram_data_changed = rationalizeNgramsByPUW();
    qDebug() << "\n\tTIMING: newPhrase: 5 rationalizeNgramsByPUW ="  << timeSince(t4) << timeSince(t0)  << "secs\n";
    //if( !should_continue ){qDebug() << "!!ERROR!! setNGramChosenByPUW false";return false;}
    // delete the ngrams that are false (!!only do on a new_phrase after this user decides!!)
    auto t5 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = deleteAllNotChosenWords(true);
    qDebug() << "\n\tTIMING: newPhrase: 6 deleteAllNotChosenWords =" << timeSince(t5) << timeSince(t0) << "secs\n";
    if( !should_continue ){qDebug() << "!!ERROR!! deleteAllNotChosenWords false";return false;}
    auto t6 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = rationlizeChosenForPUWAndNgram();
    qDebug() << "\n\tTIMING: newPhrase: 7 rationlizeChosenForPUWAndNgram =" << timeSince(t6) << timeSince(t0) << "secs\n";
    //should_continue = rationlizeEverythingChosen();
    if( !should_continue ){qDebug() << "!!ERROR!! rationlizeChosenForPUWAndNgram false";return false;}
    // force delete of not chosen words
    auto t7 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = deleteAllNotChosenWords();
    qDebug() << "\n\tTIMING: newPhrase: 8 deleteAllNotChosenWords ="   << timeSince(t7) << timeSince(t0) << "secs\n";
    if( !should_continue ){qDebug() << "!!ERROR!! deleteAllNotChosenWords false";return false;}
    // save files
    auto t8 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = savePhraseNgrams(true);
    qDebug() << "\n\tTIMING: newPhrase: 9 savePhraseNgrams =" <<  timeSince(t8) << timeSince(t0) << "secs\n";
    if( !should_continue ){qDebug() << "!!ERROR!! savePhraseNgrams false"; return false;}
    // save PUW data
    auto t9 = QTime::currentTime().msecsSinceStartOfDay();
    should_continue = savePhraseUniqueWords();
    qDebug() << "\n\tTIMING: newPhrase: 10 savePhraseUniqueWords =" << timeSince(t9) << timeSince(t0) << "secs\n";
    if( !should_continue ){qDebug() << "savePhraseUniqueWords false"; return false;}
    qDebug() << "Created new phrase";
    auto t10 = QTime::currentTime().msecsSinceStartOfDay();
    config.save();
    qDebug() << "\n\tTIMING: newPhrase: END TOTAL TIME =" << timeSince(t0) << "secs\n";
    qDebug() << "Created new phrase saved";
    return should_continue;
}
bool GNGPhrase::rationalizeNgramsByPUW(){
    bool changes = setNGramWordsChosenByPUW();
    if(changes){
       setNgramChosenByNgramWordsChosen();
    }
    return changes;
}
bool GNGPhrase::setNGramWordsChosenByPUW(){
    qDebug() << "GNGPhrase::setNGramWordsChosenByPUW";
    bool ngram_changed = false;
    int total_changes = 0;
    for(auto& ngram : ngram_data){
        if(ngram->makeConsistentWordsChosenAndPUW(phrase_unique_words)){
            total_changes += ngram->changes_on_last_setWordsChosenByPUW;
            ngram_changed = true;
        }
    }
    if(true){qDebug() << "ngram changes " << total_changes;}
    return ngram_changed;
}
bool GNGPhrase::setNgramChosenByNgramWordsChosen(){
    // loop over Ngrams and set main chosen = false if a PUW chosen = false
    for( auto& ngram : ngram_data){
        ngram->setChosenByNgramWordsChosen();
    }
    return true;
}
bool GNGPhrase::setPUWChosenByNGramsChosen(){
    //auto t0 = timer.elapsed();
    //qDebug() << "\n!!! setPUWChosenByNgram !!!";
    bool puw_changed = false;
    bool display_message = true;
    for(unsigned i = 0; i < phrase_word_count; ++i){
        //qDebug() << "get latest unique chosen word list at index " << i;
        QVector<QString> data = getUniqueChosenWordsAtPhraserWordIndex(i);
        //QVector<QString> data =  getUniqueChosenWordsAtPhraserWordIndex(i);
        //qDebug() << "latest word count = " << data.size() << ", now compare with exisiting data";
        if(phrase_unique_words[i]->compareWithWordList(data)){
            //qDebug() << "phrase_unique_words changed " << phrase_unique_words[i]->changes_on_last_compareWithWordList;
            puw_changed = true;
            if(display_message){
                qDebug() << "latest word count = " << data.size() << ", now comapre with exisiting data";
                display_message = false;
            }
        }
    }
    //qDebug() << "TIMING: setPUWChosenByNGramsChosen took" << timeSince(t0);
    return puw_changed;
}
bool GNGPhrase::rationlizeChosenForPUWAndNgram(){
    bool carry_on = true;
    unsigned int counter = 0;
    unsigned int max_counter = 5;
    qDebug() << "rationlizeChosenForPUWAndNgram LOOP";
    auto t0 = QTime::currentTime().msecsSinceStartOfDay();
    while(carry_on){
        counter +=1;
        // assume this iteration will succeed
        auto loop_start = QTime::currentTime().msecsSinceStartOfDay();
        bool ngram_changed = rationalizeNgramsByPUW();
        qDebug() << "LOOP:" << counter <<  "rationalizeNgramsByPUW took ="
                 << timeSince(loop_start) << " seconds";
//        if(ngram_changed){
//            qDebug() << "ngram_changed during rationalizeNgramsByPUW, carry_on!";
//        }
        auto setPUWChosenByNGramsChosen_start = QTime::currentTime().msecsSinceStartOfDay();
        bool puw_changed = setPUWChosenByNGramsChosen();
        qDebug() << "LOOP:" << counter <<  "setPUWChosenByNGramsChosen took ="
                 << timeSince(setPUWChosenByNGramsChosen_start) << " seconds";
//        if(ngram_changed){
//            qDebug() << "puw_changed during setPUWChosenByNGramsChosen, carry_on!";
//        }
        carry_on = ngram_changed || puw_changed;
        if(!carry_on){
            qDebug() << "No changes this loop, exiting";
        }
        if(counter == max_counter){
            qDebug() << "rationlize counter =" << max_counter << "stopping";
            carry_on = false;
        }
        qDebug() << "LOOP:" << counter << "time=" << timeSince(setPUWChosenByNGramsChosen_start);
    }
    qDebug() << "TOTAL rationlizeChosenForPUWAndNgram time=" << timeSince(t0);
    return true;
}
bool GNGPhrase::initPUWData() // TODO better name // set PUW based on Ngram data
{   // fill word_data, "unique words form each ngram"
    // loop over each word index, get the ngrams that have that word, get each word
    // this is the initial one on startup
    // add add data to PUW using ngram data, set local file and save
    qDebug() << "GNGPhrase::initPUWData()";
    config.local_phrase_word_filenames.clear();
    for(auto& item : phrase_unique_words){
        auto next_word_index = item->phrase_index;
        //qDebug() << "next_word_index = " << next_word_index << ", get unique_chosen_words";
        QHash<QString, QPair<unsigned long long, unsigned long long>>this_index_unique_chosen_words = getUniqueChosenWordsAndCountsAtPhraserWordIndex(next_word_index);
        //qDebug() << "set GNGPhraseWord words for this index to unique_chosen_words";
        item -> setFromWords(this_index_unique_chosen_words);
        // set file name
        std::string file_name = "phrase_word_";
        file_name += std::to_string(next_word_index);
        file_name += ".csv";
        std::string fp = utilities::getFullPath(config.path_to_local_files.toStdString(), file_name);
        item->setLocalDataFilePath(QString::fromStdString(fp));
        config.local_phrase_word_filenames.push_back(QString::fromStdString(file_name));
        qDebug() << "updated config and set this PUW local_data_filepath to" << item->local_data_filepath;
    }
    return cutByTags();
}
bool GNGPhrase::cutByTags(){
    return cutByStartWords() && setEndWord();
}
bool GNGPhrase::setEndWord(){
    // TODO
    qDebug() << "setEndWord IS NOT WRITTEN YET!!";
    return true;
}
bool GNGPhrase::cutByStartWords(){
    if(has_phrase_start){
        qDebug() << "cutByStartWords active";
        QVector<unsigned int> start_ngram_length = QVector<unsigned int>();
        start_ngram_length.push_back(100);
        for(unsigned int i = 1; i < ngram_length; ++i){
            start_ngram_length.push_back(word_lengths.front());
        }
        start_ngram_data = new GNGNGram(start_ngram_length, 100, 0 );
        start_ngram_data->info_string = QString("NGram Start DATA:" + start_ngram_data->default_file_name);
    }
    else{
        return true;
    }
    if(start_ngram_data){
        if(start_ngram_data->load(true)){
            // now get unique words and set not chosen in relevant PUW words
            qDebug() << "get unique_words from " << start_ngram_data->info_string;
            for(unsigned int index = 1; index  < 2; ++index ){
                QVector<QString> unique_words;
                for(const auto& word : start_ngram_data->words){
                    if( !unique_words.contains(word[index])){
                        unique_words.push_back(word[index]);
                    }
                }
                qDebug() << "unique_words.size() = " << unique_words.size() << " words";
                qDebug() << "checking against PUW part " << index-1 << ", word count = " << phrase_unique_words[index-1]->words.size();
                // now set chosen in index -1 in PUW
                unsigned int counter = 0;
                for(unsigned int i = 0; i < phrase_unique_words[index-1]->words.size(); ++ i){
                    if( !unique_words.contains(phrase_unique_words[index-1]->words[i])){
                        qDebug() << phrase_unique_words[index-1]->words[i] << " not a start word";
                        phrase_unique_words[index-1]->chosen[i] = false;
                        counter += 1;
                    }
                }
                qDebug() << "set not chosen for " << counter << " words";
            }
            return true;
        }
    }
    return false;
}
bool GNGPhrase::setPhraseUniqueWordsChosenBy1Grams(){
    // select chosen by uniqueword flag
    qDebug() << "setPhraseUniqueWordsChosenBy1Grams, loop over phrase_unique_words";
    // breaks here!
    for(auto& puw : phrase_unique_words){
        puw->setChosenFrom1GramData();
//        // get the GNG1GramData for this puw word_length
//        GNG1GramData* puw_gng_word = gng_words.all_word_data[puw->word_length-1]; // TODO functions to get pointers by word length for ease of flow
//        // get the chosen words from GNG1GramData
//        bool set_ok = puw_gng_word->setChosenWords();
//        QVector<QString> chosen_1gram_words = puw_gng_word->getChosenWords();
//        // for each puw word
//        for(unsigned int i = 0; i <  puw->size(); ++i){
//            puw->chosen[i] = chosen_1gram_words.contains(puw->words[i]);
//        }
        unsigned int true_count = puw->chosen.count(true);
        unsigned int false_count = puw->size() - true_count;
        qDebug() << "puw index =" << puw->phrase_index << "," <<  true_count << "/"  << puw->size();
    }
    return true;
}
bool GNGPhrase::rationlizePUWAndNgramDataOnce(){
    bool data_changed = false;
    bool show_message_1 = true;
    bool show_message_2 = true;
    bool show_message_3 = true;
    bool show_message_4 = true;
    qDebug() << "rationlizePUWAndNgramDataOnce START";
    for(auto& puw : phrase_unique_words)
    {
        unsigned int this_phrase_index = puw->phrase_index;
        qDebug() << "\rationlizePUWAndNgramDataOnce START: this_phrase_index =" << this_phrase_index;
        QVector<QPair<int,int>> ngrams_with_this_phrase_index = getNgramsWithPhraseIndex(this_phrase_index);
        qDebug() << "\nLOOP START: this_phrase_index =" << this_phrase_index <<
                    ", found" << ngrams_with_this_phrase_index.size() << "ngrams";
        // for each ngrams_with_this_phrase_index set the phrase words not chosen
        for(auto& item: ngrams_with_this_phrase_index){
            auto& ngram = ngram_data[item.first];
            unsigned int puw_ngram_index = item.second;
            // first set individual phrase words to match PUW words chosen
            Q_ASSERT( ngram->words.size() == ngram->word_chosen.size() );
            Q_ASSERT( ngram->chosen.size() == ngram->word_chosen.size() );
            for(unsigned int i = 0; i < ngram->word_chosen.size(); ++i ){
                ngram->word_chosen[i].replace( puw_ngram_index,
                                              puw->isChosen( ngram->words.at(i).at(puw_ngram_index)));
            }
//            QVector<QVector<QString>>::const_iterator i = ngram->words.constBegin();
//            QVector<QVector<bool>>::iterator j = ngram->word_chosen.begin();
//            QVector<bool>::iterator k = ngram->chosen.begin();
//            //while( (i != ngram->words.constEnd()) && (j != ngram->word_chosen.end()) && (k != ngram->chosen.end())) {
//            while( (i != ngram->words.constEnd()) && (j != ngram->word_chosen.end()) ) {
//                (*j)[puw_ngram_index] = puw->isChosen( (*i)[puw_ngram_index] );
//                ++i;
//                ++j;
//            }
        }
        // Then compare word_chosen with chosen adn make consistent
        for(auto& item: ngrams_with_this_phrase_index){
            auto& ngram = ngram_data[item.first];
            unsigned int puw_ngram_index = item.second;
            // first set individual phrase words to match PUW words chosen
            QVector<QVector<bool>>::iterator j = ngram->word_chosen.begin();
            QVector<bool>::iterator k = ngram->chosen.begin();
            while((j != ngram->word_chosen.end()) && (k != ngram->chosen.end())) {
                bool all_word_chosen = j->contains(false);
                if( *k && all_word_chosen ){

                }
                else if( !(*k) && all_word_chosen ){
                    *k = true;
                    data_changed = true; // need another iteration
                    if(show_message_2){
                        qDebug() << "ngram chosen = FALSE, all_word_chosen= TRUE set to TRUE.";
                        show_message_2 = false;
                    }
                }
                else if( *k && !all_word_chosen ){
                    *k = false;
                    data_changed = true; // need another iteration
                    if(show_message_3){
                        qDebug() << "ngram chosen = TRUE, all_word_chosen= FALSE set to FALSE";
                        show_message_3 = false;
                    }
                }
                ++j;
                ++k;
            }
        }
    }//for(auto& puw : phrase_unique_words){
    return data_changed;
}
// ===========================================================
// rationlize NGrams and PUW
bool GNGPhrase::rationlizeEverythingChosen(){
/* for each puw word, go to each ngram that contains it,
find the index of puw in ngram (similar to exisitng functions)
get inChosenNGrams words and notInchosenNgramsWords
for each chosen ngram, look it up in puw using new index function thing!
then do if else comparisons above
record how many changes,
simple loop until no changes, or be smart about when to stop, */
    bool carry_on = true;
    unsigned int counter = 0;
    unsigned int max_counter = 5;
    qDebug() << "rationlizeEverythingChosen2";
    while(carry_on){
        // assume this iteration will succeed
        carry_on = rationlizePUWAndNgramDataOnce();
        counter +=1;
        qDebug() << "rationlize counter = " << counter;
        if(counter == max_counter){
            qDebug() << "rationlize counter =" << max_counter << "stopping";
            carry_on = false;
        }
    }
    updateChosenSummary();
    return true;
}

bool GNGPhrase::setCanAddNgrams(bool v){
    can_add_ngrams=v;
    for(auto& ngram :ngram_data){
        ngram->setCanAddNgrams(can_add_ngrams);
    }
    return can_add_ngrams;
}
// ===========================================================
// load and/or NEW phrase setup functions, clears old data and does everything
// up to file data loading
void GNGPhrase::initializeForNewWordLengths(QVector<unsigned int> const& word_lengths_in, unsigned int ngram_length_in){
    // TODO move to individual functions if ever needed to be called individually
    cleanupNgramData();
    cleanupPhraseUniqueWords();
    word_lengths = word_lengths_in;
    phrase_word_count = (unsigned int)word_lengths_in.size();
    phrase_item_count = phrase_word_count;
    if(has_phrase_start) phrase_item_count += 1;
    if(has_phrase_end) phrase_item_count += 1;
    ngram_length = ngram_length_in;
    for(unsigned int i = 0; i < word_lengths.size() - ngram_length + 1; ++i ){
        QVector<unsigned int> next_ngram_length = QVector<unsigned int>();
        for(unsigned int j = 0; j < ngram_length; ++j ){
            next_ngram_length.push_back(word_lengths[i+j]);
        }
        ngram_word_lengths.push_back(next_ngram_length);
    }
    //qDebug() << "GNGPhrase::initializeForNewWordLengths ngram_word_lengths " << ngram_word_lengths;
    //
    // set up the (as yet empty) GNGNGram objects
    //qDebug() << "GNGPhrase::initializeForNewWordLengths set up the (as yet empty) GNGNGram objects";
    //
    int counter = 0;
    //qDebug() << "ngram_word_lengths.size() = " << ngram_word_lengths.size();
    //qDebug() << "ngram_word_lengths = " << ngram_word_lengths;
    for(const auto& ngram_word_length :  ngram_word_lengths ){
        //GNGNGram n = GNGNGram(ngram_word_length, counter );
        ngram_data.push_back( new GNGNGram(ngram_word_length, counter, counter) );
        ngram_data.back()->info_string = QString("NGram: " + QString::number(counter) +
                                                 " DATA: " + ngram_data.back()->default_file_name);
        counter +=1;
        qDebug() << "\t**NEW** Ngram" << counter << ngram_data.back()->info_string;
    }
    // set up the (as yet empty) GNGPhraseWord objects
    counter = 0;
    for(unsigned int next_word_index = 0; next_word_index < phrase_word_count; ++next_word_index ){
        unsigned int next_word_length = word_lengths[next_word_index];
        phrase_unique_words.push_back(new GNGPhraseWord(next_word_index,
                                                        next_word_length,
                                                        gng_words.getPrase1GramPtrAtWordLength(next_word_length)));
        phrase_unique_words.back()->info_string = QString("PUW index = " + QString::number(next_word_index) +
                                                          ", len=" + QString::number(next_word_length));
        counter +=1;
        qDebug() << "\t**NEW** PUW " << counter << phrase_unique_words.back()->info_string;
    }
    // TODO config check
}
// ===========================================================
// get data lists (mostly for convenience atm)
QHash<QString, QPair<unsigned long long, unsigned long long>  > GNGPhrase::getUniqueChosenWordsAndCountsAtPhraserWordIndex(unsigned int pwi)const{
    qDebug() << "GNGPhrase::getUniqueChosenWordsAtPhraserWordIndex";
    //QVector<QString> r;
    QHash<QString, QPair<unsigned long long, unsigned long long>> unique_words_and_count;
    //unsigned int ngram_count = 0;
    for(const auto & ngram : ngram_data ){
        // TODO the below should be in an ngram function ...they should know how to get thsi data
        int local_index = ngram->getLocalIndexOfPhraseIndex(pwi);
        if(local_index != -1){
            //qDebug() << "NGRAM index=" << ngram_count<< ", found pwi=" << pwi << " at local_index=" << local_index;
            for(unsigned int i = 0; i < ngram->size(); ++i)
            {
                if(ngram->chosen.at(i)){
//                    r.push_back(ngram->words[i][local_index]);
                    if(unique_words_and_count.contains(ngram->words.at(i).at(local_index))){
                        unique_words_and_count[ngram->words.at(i).at(local_index)].first += ngram->counts.at(i);
                        unique_words_and_count[ngram->words.at(i).at(local_index)].second += 1;
                    }
                    else{
                        unique_words_and_count[ngram->words.at(i).at(local_index)].first = ngram->counts.at(i);
                        unique_words_and_count[ngram->words.at(i).at(local_index)].second = 1;
                    }
                }
            }
        }
    }
//    QSet<QString> s(r.begin(), r.end());
//    qDebug() << "Found " << s.size() << " / " << r.size() << " unique / total chosen words at index = " << pwi;
    qDebug() << "Found" <<  unique_words_and_count.size() << "unique_words_and_count.size() ";
    return unique_words_and_count;
}
QVector<QString> GNGPhrase::getUniqueChosenWordsAtPhraserWordIndex(unsigned int pwi)const{
    //qDebug() << "GNGPhrase::getUniqueChosenWordsAtPhraserWordIndex";
    QSet<QString> unique_words;
    for(const auto & ngram : ngram_data ){
        unique_words.unite( ngram->getUniqueChosenWordsAtPhraseWordIndex(pwi));
    }
    qDebug() << "Found" <<  unique_words.size() << "unique words for phrase index" << pwi;
    return unique_words.values();
}
// ===========================================================
// utility, returns pairs of ngram index and phrase index in ngram
QVector<QPair<int, int>> GNGPhrase::getNgramsWithPhraseIndex(unsigned int this_phrase_index){
    QVector<QPair<int,int>> ngrams_with_this_phrase_index;
    for(auto& ngram: ngram_data)
    {   // first check if ngram has word at same index as PUW
        QPair<int,int> np{-1,-1};
        if(ngram->hasWordAtIndex(this_phrase_index)){
            np.first = ngram->ngram_index;
            np.second = ngram->getLocalIndexOfPhraseIndex(this_phrase_index);
            ngrams_with_this_phrase_index.push_back(np);
        }
    }
    return ngrams_with_this_phrase_index;
}
// ===========================================================
// delete not chosen elements
bool GNGPhrase::deleteAllNotChosenWords(bool and_squeze){
    bool r1 = deleteNotChosenPhraseWords();
    bool r2 = deleteNotChosenNgrams(and_squeze);
    return r1 && r2;
}
bool GNGPhrase::deleteNotChosenPhraseWords(){
    bool r = true;
    int t1 = QTime::currentTime().msecsSinceStartOfDay();
    for(auto& phrase_word : phrase_unique_words ){
        int t2 = QTime::currentTime().msecsSinceStartOfDay();
        bool f = phrase_word->deleteNotChosen2();
        // qDebug() << "phrase_word" << phrase_word->phrase_index << timeSince(t2) << "secs\n";
        if(!f){
            r = false;
        }
    }
    //qDebug() <<"deleteNotChosenPhraseWords took " << timeSince(t1) << "secs\n";
    return r;
}
bool GNGPhrase::deleteNotChosenNgrams(bool and_squeze){
    bool r = true;
    int t0 = QTime::currentTime().msecsSinceStartOfDay();
    for(auto& ngram : ngram_data ){
        int t2 = QTime::currentTime().msecsSinceStartOfDay();
        bool f = ngram->deleteNotChosen2(and_squeze);
        qDebug() << "ngram" << ngram->ngram_index << timeSince(t2) << "secs";
        if(!f){
            r = false;
        }
    }
    qDebug() <<"deleteNotChosenNgrams took " << timeSince(t0) << "secs";
    return r;
}
// ===========================================================
// delete stuff
void GNGPhrase::cleanupNgramData(){
    //qDebug() << "cleanupNgramData called, ngram_data.size() " << ngram_data.size();
    qDeleteAll(ngram_data.begin(), ngram_data.end());
    delete start_ngram_data;
    delete end_ngram_data;
    start_ngram_data = nullptr;
    end_ngram_data = nullptr;
    ngram_data.clear();
    ngram_word_lengths.clear();
}
void GNGPhrase::cleanupPhraseUniqueWords(){
    qDeleteAll(phrase_unique_words.begin(), phrase_unique_words.end());
    phrase_unique_words.clear();
    //qDebug() << "cleanupPhraseUniqueWords called, phrase_unique_words.size() " << phrase_unique_words.size();
}
// ===========================================================
// Load and save data
bool GNGPhrase::loadPhrase1Grams(){
    qDebug() << "loadPhrase1Grams config.local_1gram_filenames =" << config.local_1gram_filenames;
    return gng_words.loadAllLocal1GramsFromConfig();
}
bool GNGPhrase::savePhrase1Grams(){
    return gng_words.saveAllLocal1Grams();
}
bool GNGPhrase::loadPhraseNgrams(bool default_location){
    bool r = true;
    if(!default_location){
        qDebug() << config.local_ngram_filenames.size();
        qDebug() << ngram_data.size();
        Q_ASSERT(config.local_ngram_filenames.size() == ngram_data.size());
    }
    for(unsigned int i =0; i < ngram_data.size(); ++i){
        if(default_location){
            ngram_data.at(i)->setLocalDataFilePath(config.path_to_local_files,
                                                "local_" + ngram_data.at(i)->default_file_name);
        }
        else{
            ngram_data.at(i)->setLocalDataFilePath(config.path_to_local_files,
                                                config.local_ngram_filenames.at(i));
        }
        bool s = ngram_data.at(i)->load(default_location);
        if(!s){
            r = false;
        }
    }
    return r;
}
bool GNGPhrase::savePhraseNgrams(bool default_location){
    // if default_location then the data has not yet been saved to local
    if(default_location){
        config.local_ngram_filenames.clear();
    }
    bool s = true;
    for(auto& item: ngram_data){
        item->type = GNGDataBase::n_gram_chosen;
        if(default_location){
            config.local_ngram_filenames.push_back(item->local_data_filename);
        }
        if(!item->saveLocalData()){
            s = false;
        }
    }
    return s;
}
bool GNGPhrase::loadPhraseUniqueWords(){
    Q_ASSERT(config.local_phrase_word_filenames.size() == phrase_unique_words.size());
    bool r = true;
    for(unsigned int i =0; i < phrase_unique_words.size(); ++i){
        phrase_unique_words.at(i)->setLocalDataFilePath(config.path_to_local_files,
                                   config.local_phrase_word_filenames[i]);
        bool s = phrase_unique_words[i]->load();
        if(!s){
            r = false;
        }
    }
    return r;
}
bool GNGPhrase::savePhraseUniqueWords(){
    bool r = true;
    for(const auto& word: phrase_unique_words){
        bool s = word->save();
        if(!s){
            r = false;
        }
    }
    return r;
}
bool GNGPhrase::loadPhrase(){
    // ASSUME CONFIG IS ALREADY SET!
    if(!config.has_full_config){
        qDebug() << "!!error!! in config";
        return false;
    }
    // assume config is set "correctly" and cascade information through to all GNGPhrase objects
    // TODO the above ...
    bool load_p1G = gng_words.loadAllLocal1GramsFromConfig();
    if(!load_p1G){
        qDebug() << "!!ERROR!! gng_words.loadAllLocal1GramsFromConfig failed to load local 1Gram files";
        return false;
    }
    initializeForNewWordLengths(config.getPhraseWordLengths(), config.getPhraseNgramLength());
    // load PUW
    bool load_puw = loadPhraseUniqueWords();
    if(!load_puw){
        qDebug() << "!!ERROR!! GNGPhrase::loadPhrase failed to load local PUW files";
        return false;
    }
    qDebug() << "GNGPhrase::loadPhraseUniqueWords success.";
    // load NGRAM
    bool load_ngram = loadPhraseNgrams(false);
    if(!load_ngram){
        qDebug() << "!!ERROR!!" << "GNGPhrase::loadPhrase failed to load local ngram files";
        return false;
    }
    qDebug() << "GNGPhrase::loadPhraseNgrams success.";
    return load_ngram && load_puw && load_p1G;
}
bool GNGPhrase::finishAfterDataAddedOrDeleted(){
    return finishAfterDataAddedOrDeletedNgrams() && finishAfterDataAddedOrDeletedPUW() && finishAfterDataAddedOrDeletedP1G() ;
}

bool GNGPhrase::finishAfterDataAddedOrDeletedNgrams(){
    for(auto& item: ngram_data){
        item->finishAFterDataAddedOrDeleted();
    }
    return true;
}

bool GNGPhrase::finishAfterDataAddedOrDeletedPUW(){
    for(auto& item: phrase_unique_words){
        item->finishAFterDataAddedOrDeleted();
    }
    return true;
}

bool GNGPhrase::finishAfterDataAddedOrDeletedP1G(){
    for(auto& item: gng_words.local_phrase_1gram_data){
        item->finishAFterDataAddedOrDeleted();
    }
    return true;
}

bool GNGPhrase::updateChosenSummary(){
    return updateChosenSummaryNgrams() && updateChosenSummaryPUW() && updateChosenSummaryP1G() ;
}
bool GNGPhrase::updateChosenSummaryNgrams(){
    for(auto& item: ngram_data){
        item->updateChosenSummary();
    }
    return true;
}

bool GNGPhrase::updateChosenSummaryPUW(){
    for(auto& item: phrase_unique_words){
        item->updateChosenSummary();
    }
    return true;
}
bool GNGPhrase::updateChosenSummaryP1G(){
    for(auto& item: gng_words.local_phrase_1gram_data){
        item->updateChosenSummary();
    }
    return true;
}
