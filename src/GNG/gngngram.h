//#ifndef GNGNGRAM_H
//#define GNGNGRAM_H
//#include <QList>
//#include <QString>
//#include <QDebug>
//#include "gng_1grams.h"
///*
//    words - are lists of words of lengths 1 to 14, each is unique, and is "chosen" or not
//    ngrams contain multiple groups of n words, each is unique, and is "chosen" or not
//    phrases contain multiple groups of n-grams
//        for each word in phrase there are (possible) multiple n-grams that contain thsi word
//        build a "unique list of words" based on what has been selected in the ngram
//        the unique words are chosen or not, first based on gng-words
//        the n-grams are then updated based on unique words
//        they can either be cut, or tagged not chosen
//        if they are tagged not chosen other words in teh ngram are now "possible not chosen"
//        so an iteration is now reuired to chekc if we can "cut" more words
//*/
//class GNGNgramWordRawData // TODO better name
//{   // The raw data for a word in an ngram
//    public:
////    person(const person &) = default;                // 1/5: Copy Ctor
////    person(person &&) noexcept = default;            // 4/5: Move Ctor
////    person& operator=(const person &) = default;     // 2/5: Copy Assignment
////    person& operator=(person &&) noexcept = default; // 5/5: Move Assignment
////    ~person() noexcept = default;                    // 3/5: Dtor

//    GNGNgramWordRawData(unsigned int word_index_in_ngram,
//                            unsigned int word_length,
//                            GNG1GramData* gng_word_data);
//        ~GNGNgramWordRawData() = default;
//        GNGNgramWordRawData& operator=(const GNGNgramWordRawData& other)
//        {
//            word_length = other.word_length;
//            words = other.words;
//            chosen = other.chosen;
//            definite_character = other.definite_character;
//            maybe_interrupter = other.maybe_interrupter;
//            word_index_in_gng_words =  other.word_index_in_gng_words;
//            phrase_index =  other.phrase_index;
//            my_gng_word_data = other.my_gng_word_data;
//            return *this;
//        }
//        //
//        unsigned int word_length; // length of word in runes
//        QList<QString> words; // list of words
//        QList<bool> chosen; // list of is word chosen
//        QList<QString> definite_character; // list of definite_interrupter for each character in this word
//        QList<QString> maybe_interrupter; // list of maybe_interrutpers for each character in this word
//        QList<unsigned int> word_index_in_gng_words; // index of word the 1-gram data
//        unsigned int phrase_index; // index of word in phrase
//        GNG1GramData * my_gng_word_data; // ref to 1-gram data for this word_length

//        QString local_data_filedir; // can read and write to
//        QString local_data_filename; // can read and write to
//        QString local_data_filepath; // can read and write to
//        //
//        void setIndexInGNGWords();
//        QList<QString> getNotChosenWords();
//        void addWord(const QString& word);
//        void deleteAt(unsigned int index_to_delete);
//        void deleteAt(const QList<unsigned int>& i);
//        QList<QString> getCurrentUniqueWords(unsigned int index);
//        unsigned int getChosenCount(){ return chosen.count(true);};

//        // todo need to write these, simile to 1gram sthan update manager to use new functions
//        bool setFromRawData(const std::vector<std::vector<std::any>>& raw_data);
//        bool getAsRawData(std::vector<std::vector<std::any>>& data_to_fill)const;
//        // after words have been set, the word_to_index map can be calculated
//        void setWordToIndex();
//        // file data paths, local files are ones being used (could be user???)
//        void setLocalDataFilePath(QString const& path);
//        void setLocalDataFilePath(QString const& directory,  QString const& filename);
//        // load data
//        bool load();
//        // save always to local file-path
//        bool save()const;
//        //bool readCSVFile(const QString& path, std::vector<std::vector<std::string>>& file_data);

//};

//class GNGNGram
//{   // Data from a single "n-gram file"
//    public:
//        GNGNGram(QMap<QString, QVariant>* config,
//                 const QList<unsigned int>& word_lengths,
//                 unsigned int phrase_index,
//                 GNG1Grams* gng_words);
//        GNGNGram(const GNGNGram&);
//        ~GNGNGram() = default;
//        GNGNGram& operator=(const GNGNGram& other)
//        {
//            config = other.config;
//            ngram_word_lengths = other.ngram_word_lengths;
//            word_index_in_phrase = other.word_index_in_phrase;
//            ngram_length = other.ngram_length;
//            count = other.count;
//            chosen =  other.chosen;
//            gng_words = other.gng_words;
//            config = other.config;
//            return *this;
//        }
//        // data
//        QMap<QString, QVariant>* config; // config holds paths to directories etc
//        QList<unsigned int> ngram_word_lengths; // length of each word in ngram
//        QList<unsigned int> word_index_in_phrase; // each ngram is part of a phrase, contains which index in phrase each word here has
//        unsigned int ngram_length; // how many words in ngram
//        QList<GNGNgramWordRawData> ngram_word_data; // data for each word
//        QList<unsigned long long> count; // counts in ngrams data
//        QList<bool> chosen; // is entire ngram chosen or not (e.g. if at least 1 word is not chosen this should be false)
//        QString default_file_name; // default file name
//        GNG1Grams * gng_words; // ref to 1-gram word data
//        unsigned int ngram_count; // number of ngrams (e.g. equal to ngram_word_data[0].words.size())


//        QString raw_data_file; // only ever read
//        QString local_data_file; // can read and write to
//        // methods
//        // one of these should be called to set data
//        void setLocalDataFilePath(QString const& directory,  QString const& file_name);
//        void setRawDataFilePath(QString const& directory,  QString const& file_name);
//        bool loadLocalDataFile();
//        bool loadRawDataFile();
//        bool loadFile(QString const& directory,  QString const& file_name);
//        bool loadFile(QString const& path);

//        bool loadData(); // default based on values passed to constructor
//        bool loadData(QString const& directory); // load from user specified directory
//        bool loadData(QString const& directory, QString const& file_name); // load from user specified directory and filename
//        bool hasWordAtIndex(unsigned int index){ return word_index_in_phrase.indexOf(index) != -1; };
//        bool deleteByWord(const QList<QString>& delete_words, unsigned int word_index); // uses GNGNGram::ngram_word_data[word_index].words that match delete_words
//        bool deleteByChosenWord(unsigned int word_index); // uses GNGNGram::ngram_word_data[word_index].chosen
//        bool deleteByChosenNgram(); // uses GNGNGram::chosen
//        bool deleteByIndex(const QList<unsigned int>& indexes_to_delete); // deletes all entries that match indexes_to_delete (ngram_word_data, count, chosen, update ngram_count)
//        bool addUniqueWords(unsigned int index, QList<QString>& list_to_fill )const; // adds any words at index that are not already in list_to_fill
//        bool addUniqueChosenWords(unsigned int index, QList<QString>& list_to_fill )const;
//        bool setNgramNotChosenByWordsAtIndex(unsigned int word_index, const QList<QString>& not_chosen_words);
//        unsigned int getChosenCount(){ return chosen.count(true);};
//};



//#endif // GNGNGRAM_H
