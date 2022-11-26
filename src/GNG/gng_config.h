#ifndef GNGCONFIG_H
#define GNGCONFIG_H

#include <QString>
#include <QVariant>
#include <QString>
#include <QMap>


class GNGConfig
{
public:
    GNGConfig();
    GNGConfig(const QString& directory, const QString& filename);

    // before pasing reset all data
    void clearValues();
    // general parse function
    void parseConfigFile();
    // parsing sub functions, add as needed
    void checkKeyValues(const QStringList& key_value);
    void checkForRaw1GramFileNames(const QStringList& key_value);
    void checkForLocal1GramFileNames(const QStringList& key_value);
    void checkForLocalNGramFileNames(const QStringList& key_value);
    void checkForLocalPhraseWordFileNames(const QStringList& key_value);
    void checkForPhraseWordLengths(const QStringList& key_value);
    // after parsing set some high level flags
    void checkStatus();
    // updates to config when creating new phrase
    void setConfigForNewPhrase(const QString& new_dir);
    // save file
    bool save();

    QList<unsigned int> getPhraseWordLengths()const;
    void setPhraseWordLengths(const QList<unsigned int>& word_lengths);

    void setPhraseNgramLength(unsigned int ngram_length);
    unsigned int getPhraseNgramLength()const;

    // flags
    static bool has_config; // TODO this is for a minimial viaalbel setup (1grams etc but no phrase needed)
    static bool has_full_config;
    static bool has_raw_1gram_filenames;
    static bool has_local_1gram_filenames;
    static bool has_local_ngram_files;
    static bool has_local_phrase_word_filesnames;
    static bool has_phrase_word_lengths;
    static bool has_phrase_ngram_length;
    static bool has_path_to_lp_sentences;
    static bool has_save_directory;
    static bool has_path_to_raw_1grams;
    static bool has_path_to_raw_ngrams;
    static bool has_path_to_local_files;
    static QMap<QString, QVariant> config;
    // lists of filenames
    // Number of local ngrams depends on phrase, so keep in list (orderd the same as the phrase)
    static QString const local_phrase_word_filenames_key;
    static QStringList local_phrase_word_filenames;
    // Word lengths for current phrase (if any)
    static QString const phrase_word_lengths_key;
    static QList<unsigned int> phrase_word_lengths;
    // N-gram length for current phrase (if any)
    static QString const phrase_ngram_length_key;
    static QString phrase_ngram_length;
    //
    static QString config_directory;
    static QString config_filename;
    /* key value pairs for config definitions */
    // LP sentences
    static QString const path_to_lp_sentences_key;
    static QString path_to_lp_sentences;
    // default save directory
    static QString const save_directory_key;
    static QString save_directory;
    // 1 grams
    static QString const path_to_raw_1grams_key;
    static QString path_to_raw_1grams;
    // raw ngrams grams
    static QString const path_to_raw_ngrams_key;
    static QString path_to_raw_ngrams;
    // path to phrase data
    static QString const path_to_local_files_key;
    static QString path_to_local_files;
    // local_ngram_files_key;
    static QString const local_ngram_filenames_key;
    static QStringList local_ngram_filenames;
    // There are only ever 14 1 gram files, track them individually (these are the keys names)
//    static QStringList const raw_1gram_filename_keys;
    static QString const local_1gram_filenames_key;
    static QStringList local_1gram_filenames;

    static QString const has_phrase_start_key;
    static bool has_phrase_start_set;
    static bool has_phrase_start;
    static QString const has_phrase_end_key;
    static bool has_phrase_end_set;
    static bool has_phrase_end;

    // parsing chars
    static const char  DOUBLE_QUOTE = '"';
    static const char  COMMENT = '#';
    static const char  SPACE = ' ';
    static const char  TAB = '\t';
    static const char  NEW_LINE = '\n';
    static const char  COLON = ':';
    static const char  COMMA = ',';
    static const char  CURLY_OPEN = '{';
    static const char  CURLY_CLOSE = '}';
    static const char  UNDERSCORE = '_';
    static const char  EQUALS = '=';
};
#endif // GNGCONFIG_H
