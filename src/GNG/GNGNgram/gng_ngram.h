#ifndef GNG_NGRAM_H
#define GNG_NGRAM_H
#include <QVector>
#include <QString>
#include <QDebug>
#include "gng_data.h"
#include "gng_phrase_word.h"

class GNGNGram : public GNGData<QVector<QString>>
{   // Data from a single "n-gram file"
/*!
*  * \brief Data from a single "n-gram file"
*  data stored in phrases, and in base class words
*  chosen is for each ngrma in total
*  QVector<bool> word_chosen is for each phrase showing if each individual word is chosen
*/
    public:
        GNGNGram(const QVector<unsigned int>& word_lengths,
                 unsigned int phrase_index,
                 unsigned int ngram_index);
        GNGNGram(GNGNGram&) = default;
        ~GNGNGram() = default;
        // data
        /*!
         * \brief ngram_word_lengths, length of each word in ngram
         */
        QVector<unsigned int> ngram_word_lengths;
        /*!
         * \brief word_index_in_phrase, each ngram is part of a phrase, this contains the
         * index in phrase for each word in this ngram
         */
        QVector<unsigned int> word_index_in_phrase;
        /*!
         * \brief ngram_index, which ngram is this in the phrase? the 1st, end etc, count from 0
         */
        unsigned int ngram_index;
        /*!
         * \brief ngram_string, each ngram as a single string
         */
        QVector<QString> ngram_string; // each ngram as a single string (for display purposes) TODO RENAME
        /*!
         * \brief word_chosen
         */
        QVector<QVector<bool>> word_chosen; // each word in each ngram can be individual chosen / not chosen
        /*!
         * \brief default_file_name The default Ngram file name in the data (based on
         * the word lengths in the ngram). Default files DO NOT HAVE ANY CHOSEN COLUMN
         * (it's a waste of space) instead local copies are made for a particular solution
         * and the chosen column is added on creation
         */
        QString default_file_name;
        /*!
         * \brief data_changed_on_last_setNotChosenByPUW
         */
        bool data_changed_on_last_setNotChosenByPUW;
        /*!
         * \brief data_changed_on_last_setWordsChosenByPUW
         */
        bool data_changed_on_last_setWordsChosenByPUW;
        /*!
         * \brief changes_on_last_setNotChosenByPUW
         */
        unsigned int changes_on_last_setNotChosenByPUW;
        /*!
         * \brief changes_on_last_setWordsChosenByPUW
         */
        unsigned int changes_on_last_setWordsChosenByPUW;
        /*!
         * \brief hasWordAtIndex. does this ngram object have a words at the passed index?
         * \param index
         * \return bool, result
         */
        inline bool hasWordAtIndex(unsigned int index)const{ return word_index_in_phrase.contains(index); };

        // functions to rationalize with puw
        /*!
         * \brief makeConsistentWordsChosenAndPUW, set word_chosen values consistent with the passed GNGPhraseWord (PUW),
         * \param phrase_unique_words, puw to harmonize with
         * \param changes, int& to store number of changes made to word_chosen
         * \return bool, true if any changes were made to word_chosen
         */
        bool makeConsistentWordsChosenAndPUW(const GNGPhraseWord* phrase_unique_words, int& changes);
        /*!
         * \brief setWordsChosenByPUW, harmonize word_chosen for many GNGPhraseWord
         * \param phrase_unique_words, vector of GNGPhraseWord
         * \return bool, tru eif any changes were made to
         */
        bool makeConsistentWordsChosenAndPUW(const QVector<GNGPhraseWord*>& phrase_unique_words);
        /*!
         * \brief can_add_ngrams
         */
        bool can_add_ngrams;
        /*!
         * \brief setCanAddNgrams, set state of can_add_ngrams
         * \param new_value,
         * \return bool, new can_add_ngrams
         */
        inline bool setCanAddNgrams(bool new_value){can_add_ngrams=new_value; return can_add_ngrams;}
        /*!
         * \brief setChosenByNgramWordsChosen
         * \return
         */
        bool setChosenByNgramWordsChosen();

        // rationilize data, flags and counters
        /*!
         * \brief setNGramNotChosenByPUW
         * \param phrase_unique_words
         * \return
         */
       // bool setNGramNotChosenByPUW(const QVector<GNGPhraseWord*>& phrase_unique_words);
        /*!
         * \brief getUniqueChosenWordsAtPhraserWordIndex
         * \param index
         * \return
         */
        QSet<QString> getUniqueChosenWordsAtPhraseWordIndex(unsigned int index)const;
        QSet<QString> getUniqueChosenWordsAtNgramWordIndex(unsigned int ngram_word_index)const;

        void squeeze();

        //bool setNgramWordNotChosenByPUW(unsigned int word_index, const GNGPhraseWord& puw );
        // outside this class always use load
        bool load(bool default_location = true); // Can only ever load from 1 of two palces
        // delete all entrie that have chosen == false
        bool deleteNotChosen(bool and_squeze = false);
        bool deleteNotChosen2(bool and_squeze = false); // faster??
        // The index of the passed phrase_index in the ngram words QVector TODO better names thsi is word index in phrase
        int getLocalIndexOfPhraseIndex(unsigned int phrase_index)const;


        bool addUniqueChosenWords(unsigned int index, QVector<QString>& list_to_fill )const;
        // only ever save to local
        bool saveLocalData() const;
private:
        bool loadLocalData();
        bool loadRawData();
        bool saveRawData()const;
        bool loadDefaultFileData(); // this version loads a raw file with NO chosen column
        // virtual overloads
        bool setFromFileData(const std::vector<std::vector<std::any>>& raw_data); // has chosen column!
        bool getAsFileData(std::vector<std::vector<std::any>>& r)const;           // has chosen column!
};

#endif // GNGNGRAM_H
