#ifndef GNG_1GRAMS_H
#define GNG_1GRAMS_H
#include <QDebug>
#include <QList>
#include <QString>
#include <QVariant>
#include <QString>
#include <QHash>
#include <map>
#include <any>
#include <string>
#include <vector>
#include "gng_1gram_data.h"
#include "gng_config.h"

class GNG1Grams
{
     /*!
     * \brief GNG1Grams holds all raw 1-gram data and can load and save
     * (Once intially created) just create this class where you need to
     * access all Raw 1-gram data
     * \param load_rawfiles load file data on instanitation
     */
public:
    GNG1Grams();
    GNG1Grams(bool load_rawfiles);
    GNG1Grams(const GNG1Grams&);
    ~GNG1Grams() = default;
    GNGConfig config;
    static GNG1GramData dummy_model_data; // to handle bad requets
    static QList<GNG1GramData*>all_raw_word_data;
    static bool loaded_raw1gram_files;
    static bool loaded_local1gram_files;
    static QList<GNG1GramData*>local_phrase_1gram_data;
    static bool loaded_phrase_local1gram_files;
    static unsigned int onegram_file_count;
private:
    // this is first called on startup
    bool setupAndloadRaw1Grams();
public:
    bool setUpNewPhrase1Grams(const QVector<unsigned int>& word_lengths);
    // when making a new phrase object, copy 1-gram data to phrase directory (local)
    bool copyRaw1GramsToConfigLocalDirectory(const QVector<unsigned int>& word_lengths);
    // LOAD SAVE functions Always use use below functions
    // Raw directory is where the original 1-gram data is, |used when a new phrase is created.
    // local directory is the directory of the current phrase (if there is one)
    bool loadAllRaw1Grams();
    bool loadRaw1GramFile(unsigned int  word_length);
    bool saveRaw1GramFile(unsigned int  word_length);
    bool saveAllRaw1Grams()const;
    bool loadAllLocal1GramsFromConfig();
    bool loadAllLocal1Grams();
    bool loadLocal1GramFile(unsigned int  word_length);
    bool saveAllLocal1Grams()const;
    bool saveLocal1GramFile(unsigned int  word_length);
    // set file paths
    void setRawDataFileDirectory();
    void setLocalDataFileDirectory();
    // when new config is loaded / created run this
    bool newConfig();
    // try to check if data exists before requesting
    bool hasWordLength(int word_length);
    int  getWordLengthIndex(int word_length);
    // get ref to raw data object
    GNG1GramData& getData(unsigned int word_length);
    GNG1GramData& getPrase1GramRefAtWordLength(unsigned int word_length);
    GNG1GramData* getPrase1GramPtrAtWordLength(unsigned int word_length);
};

#endif // GNG_1GRAMS_H
