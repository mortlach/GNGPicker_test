#ifndef GNG_PHRASE_H
#define GNG_PHRASE_H

#include <QString>
#include <QVariant>
#include <QVector>
#include <QElapsedTimer>
#include "gng_ngram.h"
#include "gng_phrase_word.h"
#include "gng_1grams.h"
#include "gng_config.h"


class GNGPhrase
{   // Top level class for a phrase of ngrams (each of ngram_length words)
    // for each word in the phrase a set of unique words can be
    // constructed from the chosen ngram data
    // also can load and save data
public:
    GNGPhrase();
    ~GNGPhrase();
    GNGConfig config;
    static QVector<unsigned int> word_lengths;
    static unsigned int phrase_word_count;
    static unsigned int phrase_item_count; // includes start and end ( TODO punctuation!)
    static bool has_phrase_start;
    static bool has_phrase_end;
    static unsigned int ngram_length;
    static QVector<QVector<unsigned int>> ngram_word_lengths;
    static GNGNGram* start_ngram_data; // sepcial members for these object as they don't have a "full" role"
    static GNGNGram* end_ngram_data; // sepcial members for these object as they don't have a "full" role"
    static QVector<GNGNGram*>ngram_data;
    static QVector<GNGPhraseWord*> phrase_unique_words; // holds amortized data from each ngram for each word in the phrase

    GNG1Grams gng_words;

    // main load phrase or set new phrase from start
    bool loadPhrase();
    bool newPhrase(QVector<unsigned int> const& word_lengths_in,
                   bool has_phrase_start,
                   bool has_phrase_end,
                   unsigned int ngram_length_in);
    // call first when setting new phrase
    void initializeForNewWordLengths(QVector<unsigned int> const& word_lengths_in, unsigned int ngram_length_in);
    // load phrase data from files
    bool loadPhrase1Grams();
    bool savePhrase1Grams();
    bool loadPhraseNgrams( bool default_location);
    bool savePhraseNgrams(bool default_location);
    bool loadPhraseUniqueWords();
    bool savePhraseUniqueWords();
    // on new phrase the PUW are set from ngrams
    bool initPUWData();
    // for each unique word in the phrase, set the chosen flag to be the same as the 1-gram chosen flag
    bool setPhraseUniqueWordsChosenBy1Grams();
    // for each ngram the phrase, set the chosen flag to match PUW
    bool setNgramChosenByPhraseUniqueWords();
    // delete ngram sthat are not chosen
    bool deleteAllNotChosenWords(bool and_squeze = false);
    bool deleteNotChosenPhraseWords();
    bool deleteNotChosenNgrams(bool and_squeze = false);
    // rationalise all
    bool rationlizeEverythingChosen();
    bool rationlizePUWAndNgramDataOnce();

    QVector<QPair<int, int>> getNgramsWithPhraseIndex(unsigned int this_phrase_index);
    /*!
     * \brief setPUWChosenByNgrams update phrase_unique_words with latest ngram
     * choices, flag if phrase_unique_words changes
     * \return did phrase_unique_words change?
     */
    bool setPUWChosenByNgrams();
//    /*!
//     * \brief setNGramNotChosenByPUW
//     * for each phrase_unique_words in each ngram_data, set NGram not chosen if
//     * it's words in phrase_unique_words are not chosen in phrase_unique_words,
//     * flag if phrase_unique_words changes
//     * \return did ngram_data change?
//     */
//    bool setNGramNotChosenByPUW();

    void newPhraseThread();


    bool rationalizeNgramsByPUW();
    bool rationalizePUWByNgrams();


    //
    bool rationlizeChosenForPUWAndNgram();
    /*!
     * \brief setNGramNotChosenByPUW
     * for each phrase_unique_words in each ngram_data, set NGram not chosen if
     * it's words in phrase_unique_words are not chosen in phrase_unique_words,
     * flag if phrase_unique_words changes
     * \return did ngram_data change?
     */
    bool setNGramWordsChosenByPUW();
    bool can_add_ngrams;
    bool setCanAddNgrams(bool v);
    bool setNgramChosenByNgramWordsChosen();

    bool setPUWChosenByNGramsChosen();

    QElapsedTimer timer;
    QString timeSince(int ts);
    //QString timeSince(QElapsedTimer& mytimer,qint64 ts);
    //QString timeSince(QTime& mytimer,int ts);


    // get some data, TODO maybe tidy up at some point
    QHash<QString, QPair<unsigned long long, unsigned long long> > getUniqueChosenWordsAndCountsAtPhraserWordIndex(unsigned int pwi)const;
    QVector<QString> getUniqueChosenWordsAtPhraserWordIndex(unsigned int pwi)const;

//    QVector<QVector<QString>> getNgramDataUniqueWords()const;
//    QVector<QVector<QString>> getNgramDataUniqueChosenWords()const;

    // on delete
    void cleanupNgramData();
    void cleanupPhraseUniqueWords();
    //void setNewNgramAndPUWObjects();

    bool cutByTags();
    bool cutByStartWords();
    bool setEndWord();

    bool finishAfterDataAddedOrDeleted();
    bool finishAfterDataAddedOrDeletedNgrams();
    bool finishAfterDataAddedOrDeletedPUW();
    bool finishAfterDataAddedOrDeletedP1G();


    bool updateChosenSummary();
    bool updateChosenSummaryNgrams();
    bool updateChosenSummaryPUW();
    bool updateChosenSummaryP1G();



};

#endif // GNG_PHRASE_H
