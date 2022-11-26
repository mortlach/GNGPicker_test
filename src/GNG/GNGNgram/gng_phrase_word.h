#ifndef GNG_PHRASEWORD_H
#define GNG_PHRASEWORD_H
#include <QVector>
#include "gng_1gram_data.h"
#include "gng_data.h"
#include "utilities.h"

class GNGPhraseWord : public GNGData<QString> // TODO better name
{   // The raw data for a word in an ngram
    public:
    GNGPhraseWord(unsigned int word_index_in_ngram,
                            unsigned int word_length,
                            GNG1GramData* gng_word_data);
    ~GNGPhraseWord() = default;

    unsigned int word_length; // length of word in runes
    unsigned int word_index_in_ngram; // length of word in runes ?? TODO error?? bad name
    QString mustbe_character; // list of definite_interrupter for each character in this word
    QString maybe_interrupter; // list of maybe_interrutpers for each character in this word
    bool mustbe_active; // list of definite_interrupter for each character in this word
    bool maybe_active; // list of maybe_interrutpers for each character in this word
    // after applying a cut keep a copy of what you cut - to knwo if it needs updating
    QString previous_mustbe_character; // list of definite_interrupter for each character in this word
    QString previous_maybe_interrupter; // list of maybe_interrutpers for each character in this word

    bool data_changed_last_apply_cut; // flag set during data applyCuts to signal data changed by cuts
    bool changes_on_last_apply_cut; // flag set during data applyCuts to signal data changed by cuts

    bool setMustBeChar(const QChar& v, int index);
    bool setMayBeChar(const QChar& v, int index);

    inline bool mustBeEmpty(){ return std::all_of(
                    mustbe_character.cbegin(),
                    mustbe_character.cend(),
                    [](QString i){ return i == utilities::empty_string; });
    }
    inline bool mayBeInterrupterEmpty(){ return std::all_of(
                    maybe_interrupter.cbegin(),
                    maybe_interrupter.cend(),
                    [](QString i){ return i == utilities::empty_string; });
    }

    QVector<unsigned int> word_index_in_gng_words; // index of word the 1-gram data
    QVector<unsigned long long> count_in_ngrams;
    unsigned int phrase_index; // index of word in phrase
    GNG1GramData * my_gng_word_data; // ref to 1-gram data for this word_length
    bool setChosenFrom1GramData();
    //
    void setIndexInGNGWords();
     // inital setup of words
    void setFromWords(const QHash<QString, QPair<unsigned long long, unsigned long long>>& words_in);
    bool compareWithWordList(const QVector<QString>& words_in);
    bool data_changed_with_last_compareWithWordList;
    int changes_on_last_compareWithWordList;
    void deleteAt(unsigned int index_to_delete);
    void deleteAt(const QVector<unsigned int>& i);
    QVector<QString> getCurrentUniqueWords(unsigned int index);
    // virtual overloads
    bool setFromFileData(const std::vector<std::vector<std::any>>& raw_data);
    bool getAsFileData(std::vector<std::vector<std::any>>& data_to_fill)const;
    // after words have been set, the word_to_index map can be calculated
    void setWordToIndex();
    // file data paths, local files are ones being used (could be user???)
    // load data
    inline bool load(){ return loadLocalData();}
//    // save always to local file-path
    inline bool save()const{
        std::vector<std::vector<std::any>> data;
        if(getAsFileData(data)){
            return saveFileData(local_data_filepath,data);
        }
        return false;
    }

    //
    bool deleteNotChosen2(bool and_squeeze = false);
    bool deleteNotChosen(bool and_squeeze = false);
    // applies requested rune cuts to
    bool applyCuts();
    bool setNotChosenByMustBeCharacter();
    bool setNotChosenByMaybeInterrutper();
    //
    inline bool mustBeCutsChanged(){ return previous_mustbe_character == mustbe_character;}
    inline bool mayBeCutsChanged(){ return previous_maybe_interrupter == maybe_interrupter;}

    bool loadLocalData();
};

#endif // GNGPHRASEWORD_H
