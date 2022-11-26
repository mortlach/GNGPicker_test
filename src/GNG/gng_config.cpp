#include <QFile>
#include <QList>
#include <QDir>
#include "gng_config.h"


bool GNGConfig::has_full_config = false;
bool GNGConfig::has_raw_1gram_filenames = false;
bool GNGConfig::has_local_1gram_filenames = false;
bool GNGConfig::has_local_ngram_files = false;
bool GNGConfig::has_local_phrase_word_filesnames = false;
bool GNGConfig::has_phrase_word_lengths = false;
bool GNGConfig::has_phrase_ngram_length = false;
bool GNGConfig::has_path_to_lp_sentences = false;
bool GNGConfig::has_save_directory = false;
bool GNGConfig::has_path_to_raw_1grams = false;
bool GNGConfig::has_path_to_raw_ngrams = false;
bool GNGConfig::has_path_to_local_files = false;
bool GNGConfig::has_config = true; // TODO this is a partial config flag - ie enough to get started NOT WORKING
bool GNGConfig::has_phrase_start_set = false;
bool GNGConfig::has_phrase_end_set = false;

QMap<QString, QVariant> GNGConfig::config = QMap<QString, QVariant>();

// TODO: in the future the 2 ' words should be added
//QStringList GNGConfig::raw_1gram_filenames = QStringList(14);
//QStringList GNGConfig::local_1gram_filenames = QStringList(14);
//
QString const GNGConfig::phrase_word_lengths_key = QString("phrase_word_lengths");
QList<unsigned int> GNGConfig::phrase_word_lengths= QList<unsigned int>();
// N-gram length for current phrase (if any)
QString const GNGConfig::phrase_ngram_length_key = QString("phrase_ngram_length");
QString GNGConfig::phrase_ngram_length = QString("");
// phrase start  /  end flags
QString const GNGConfig::has_phrase_start_key = QString("has_phrase_start");
bool GNGConfig::has_phrase_start = false;
QString const GNGConfig::has_phrase_end_key = QString("has_phrase_end");
bool GNGConfig::has_phrase_end = false;
//
QString const GNGConfig::local_ngram_filenames_key = QString("local_ngram_filenames");
QStringList GNGConfig::local_ngram_filenames = QStringList();
//
QString const GNGConfig::local_phrase_word_filenames_key = QString("local_phrase_word_filenames");
QStringList GNGConfig::local_phrase_word_filenames = QStringList();
QString GNGConfig::config_directory = QString("config_directory");
QString GNGConfig::config_filename = QString("config_filename");
/* key value pairs */
QString const GNGConfig::path_to_lp_sentences_key = QString("path_to_lp_sentences");
QString GNGConfig::path_to_lp_sentences = QString("");
//
QString const GNGConfig::save_directory_key = QString("save_directory");
QString GNGConfig::save_directory = QString("");
//
QString const GNGConfig::path_to_raw_1grams_key = QString("path_to_raw_1grams");
QString GNGConfig::path_to_raw_1grams = QString("");
//
QString const GNGConfig::path_to_raw_ngrams_key = QString("path_to_raw_ngrams");
QString GNGConfig::path_to_raw_ngrams = QString("");
//
QString const GNGConfig::path_to_local_files_key = QString("path_to_local_files");
QString GNGConfig::path_to_local_files = QString("");
////

//todo this below all just needs ot change to fit in better, but it will lead to clearner read write/
//NO choice on names for raw_data on first instance ...
//names for local are also pre chosen ...

//QStringList const GNGConfig::raw_1gram_filename_keys = QStringList()<<"raw_1grams_01"<<"raw_1grams_02"<<"raw_1grams_03"
//                                                    <<"raw_1grams_04"<<"raw_1grams_05"<<"raw_1grams_06"
//                                                    <<"raw_1grams_07"<<"raw_1grams_08"<<"raw_1grams_09"
//                                                   <<"raw_1grams_10"<<"raw_1grams_11"<<"raw_1grams_12"
//                                                  <<"raw_1grams_13"<<"raw_1grams_14";

//QStringList const GNGConfig::local_1gram_filename_keys = QStringList()<<"local_1grams_01"<<"local_1grams_02"<<"local_1grams_03"
//                                                    <<"local_1grams_04"<<"local_1grams_05"<<"local_1grams_06"
//                                                    <<"local_1grams_07"<<"local_1grams_08"<<"local_1grams_09"
//                                                   <<"local_1grams_10"<<"local_1grams_11"<<"local_1grams_12"
//                                                  <<"local_1grams_13"<<"local_1grams_14";
QString const GNGConfig::local_1gram_filenames_key = QString("local_1gram_filenames");
QStringList GNGConfig::local_1gram_filenames = QStringList();



GNGConfig::GNGConfig()
{}
GNGConfig::GNGConfig(const QString& directory, const QString& filename)
{
    //TODO i need to save relative paths so that phrases are portable between computers
    config_directory = directory;
    config_filename = filename;
    parseConfigFile();
}

void GNGConfig::setConfigForNewPhrase(const QString& new_dir){
    config_directory = new_dir;
    path_to_local_files = new_dir;
    config_filename = "config.txt";
}

bool GNGConfig::save(){
    QDir dir(config_directory);
    QString full_path = dir.absoluteFilePath(config_filename);
    QFile file(full_path);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "# all new key-value pairs should go on a new line" << NEW_LINE;
        stream << "# comments can come after '#' char"<< NEW_LINE;
        stream << "# all file paths MUST use forward slash / as a seperator"<< NEW_LINE;
        stream << "# relative directories ./ are from application binary"<< NEW_LINE;
        stream << NEW_LINE;
        stream  << path_to_lp_sentences_key  << EQUALS  <<  path_to_lp_sentences  << NEW_LINE;
        stream  << save_directory_key        << EQUALS  <<  save_directory        << NEW_LINE;
        stream  << path_to_raw_1grams_key    << EQUALS  <<  path_to_raw_1grams    << NEW_LINE;
        stream  << path_to_raw_ngrams_key    << EQUALS  <<  path_to_raw_ngrams    << NEW_LINE;
        stream  << path_to_local_files_key   << EQUALS  <<  path_to_local_files   << NEW_LINE;
        stream  << phrase_ngram_length_key   << EQUALS  <<  phrase_ngram_length   << NEW_LINE;
        stream  << has_phrase_start_key   << EQUALS  <<  has_phrase_start   << NEW_LINE;
        stream  << has_phrase_end_key   << EQUALS  <<  has_phrase_end   << NEW_LINE;
        // write QLists ...
        stream  << phrase_word_lengths_key  << EQUALS ;
        for(const auto& item: phrase_word_lengths){
            stream << item;
            if(item != phrase_word_lengths.back()){
                stream << COMMA;
            }
        }
        stream << NEW_LINE;
        stream << local_1gram_filenames_key << EQUALS ;
        for(const auto& item: local_1gram_filenames){
            stream << item;
            if(item != local_1gram_filenames.back()){
                stream << COMMA;
            }
        }
        stream << NEW_LINE;

        stream << local_ngram_filenames_key << EQUALS ;
        for(const auto& item: local_ngram_filenames){
            stream << item;
            if(item != local_ngram_filenames.back()){
                stream << COMMA;
            }
        }
        stream  << NEW_LINE;
        stream  << local_phrase_word_filenames_key  << EQUALS ;
        for(const auto& item: local_phrase_word_filenames){
            stream << item;
            if(item != local_phrase_word_filenames.back()){
                stream << COMMA;
            }
        }
        stream  <<  NEW_LINE;
        stream.flush();
    }
    else{
        qDebug() << "save ERROR, bad path, " << full_path;
        return false;
    }
    qDebug() << "config saved " << full_path;
    return true;
}
void GNGConfig::setPhraseWordLengths(const QList<unsigned int>& word_lengths){
    phrase_word_lengths = word_lengths;
}
void GNGConfig::setPhraseNgramLength(unsigned int ngram_length){
    phrase_ngram_length = QString::number(ngram_length);
}
QList<unsigned int> GNGConfig::getPhraseWordLengths()const{
    return phrase_word_lengths;
}
unsigned int GNGConfig::getPhraseNgramLength()const{
    bool ok;
    unsigned int r = phrase_ngram_length.toUInt(&ok);
    if(ok){
        return r;
    }
    return 0;
}
void GNGConfig::clearValues()
{
    has_full_config = false;
    has_raw_1gram_filenames = false;
    has_local_1gram_filenames = false;
    has_local_ngram_files = false;
    has_local_phrase_word_filesnames = false;
    has_phrase_word_lengths = false;
    has_phrase_ngram_length = false;
    has_phrase_start_set = false;
    has_phrase_end_set = false;
    local_1gram_filenames = QStringList();
    local_ngram_filenames = QStringList();
    local_phrase_word_filenames = QStringList();
    phrase_word_lengths= QList<unsigned int>();
    phrase_ngram_length = QString("");
    path_to_lp_sentences = QString("");
    save_directory = QString("");
    path_to_raw_1grams = QString("");
    path_to_raw_ngrams = QString("");
    path_to_local_files = QString("");
}
void GNGConfig::parseConfigFile(){
    clearValues();
    QDir dir(config_directory);
    QString full_path = dir.absoluteFilePath(config_filename);
    qDebug() << "GNGConfig::parseConfigFile at" << config_directory;
    QFile file(full_path);
    if(!file.exists()){
        qDebug() << "parseConfigFile ERROR, bad path, " << full_path;
        has_full_config = false;
        return;
    }
    config.clear();
    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString original_line = line;
            // trim each line !!!
            line = line.trimmed();
            if(line.isEmpty()){
                continue;
            }
            if(line[0] == COMMENT){
                continue;
            }
            QStringList key_value = line.split(EQUALS);
            if(key_value.size() != 2){
                continue;
            }
            // omfg
            key_value[0] = key_value[0].trimmed();
            checkKeyValues(key_value);
        }
    }
    checkStatus();
}
void GNGConfig::checkStatus(){
//    has_raw_1gram_filenames = raw_1gram_filenames.size() == 14;
    has_local_1gram_filenames = local_1gram_filenames.size() > 0;
    has_local_ngram_files = local_ngram_filenames.size() > 0;
    has_local_phrase_word_filesnames = local_phrase_word_filenames.size() > 1;
    has_phrase_word_lengths = phrase_word_lengths_key.size() > 1;
    has_phrase_ngram_length = phrase_ngram_length != QString("");
    has_path_to_lp_sentences = path_to_lp_sentences != QString("");
    has_save_directory       = save_directory != QString("");
    has_path_to_raw_1grams   = path_to_raw_1grams != QString("");
    has_path_to_raw_ngrams   = path_to_raw_ngrams != QString("");
    has_path_to_local_files  = path_to_local_files != QString("");

    // TODO add more tests
//    Q_ASSERT( local_phrase_word_filenames.size() == phrase_word_lengths.size() );
//    Q_ASSERT( local_phrase_word_filenames.size() == phrase_word_lengths.size() );

    if(!has_local_1gram_filenames){
        qDebug() << "has_raw_1gram_filenames is false";
    }
    if(!has_local_ngram_files){
        qDebug() << "has_local_ngram_files is false";
    }
    if(!has_local_phrase_word_filesnames){
        qDebug() << "has_local_phrase_word_filesnames is false";
    }
    if(!has_phrase_word_lengths){
        qDebug() << "has_phrase_word_lengths is false";
    }
    if(!has_phrase_ngram_length){
        qDebug() << "has_phrase_ngram_length is false";
    }
    if(!has_path_to_lp_sentences){
        qDebug() << "has_path_to_lp_sentences is false";
    }
    if(!has_save_directory){
        qDebug() << "has_save_directory is false";
    }
    if(!has_path_to_raw_1grams){
        qDebug() << has_path_to_raw_1grams<<"is false";
    }
    if(!has_path_to_raw_ngrams){
        qDebug() << has_path_to_raw_ngrams<<"is false";
    }
    if(!has_path_to_local_files){
        qDebug() << has_path_to_local_files<<"is false";
    }
    if(!has_phrase_start_set){
        qDebug() << has_phrase_start_set<<"is false";
    }
    if(!has_phrase_end_set){
        qDebug() << has_phrase_end_set<<"is false";
    }
    has_full_config =    has_local_1gram_filenames
                      && has_local_ngram_files
                      && has_local_phrase_word_filesnames
                      && has_phrase_word_lengths
                      && has_phrase_ngram_length
                      && has_path_to_lp_sentences
                      && has_save_directory
                      && has_path_to_raw_1grams
                      && has_path_to_raw_ngrams
                      && has_path_to_local_files
                      && has_phrase_start_set
                      && has_phrase_end_set

        ;
}
// omfg
void GNGConfig::checkKeyValues(const QStringList& key_value){
    // list values
    //checkForRaw1GramFileNames(key_value);
    checkForLocal1GramFileNames(key_value);
    checkForLocalNGramFileNames(key_value);
    checkForLocalPhraseWordFileNames(key_value);
    checkForPhraseWordLengths(key_value);
    // others
    if( key_value[0].contains(phrase_ngram_length_key)  ){
        phrase_ngram_length = QString(key_value.at(1)).trimmed(); // trim each string!!!
    }
    else if( key_value[0].contains(path_to_raw_1grams_key)  ){
        path_to_raw_1grams = QString(key_value.at(1)).trimmed(); // trim each string!!!
    }
    else if( key_value[0].contains(path_to_lp_sentences_key)  ){
        path_to_lp_sentences = QString(key_value.at(1)).trimmed(); // trim each string!!!
    }
    else if( key_value[0].contains(save_directory_key)  ){
        save_directory = QString(key_value.at(1)).trimmed(); // trim each string!!!
    }
    else if( key_value[0].contains(path_to_raw_ngrams_key)  ){
        path_to_raw_ngrams = QString(key_value.at(1)).trimmed(); // trim each string!!!
    }
    else if( key_value[0].contains(path_to_local_files_key)  ){
        path_to_local_files = QString(key_value.at(1)).trimmed(); // trim each string!!!
    }
    else if( key_value[0].contains(has_phrase_start_key)  ){
        if(QString(key_value.at(1)).trimmed() == "1"){
            has_phrase_start = true;
        }
        else{
            has_phrase_start = false;
        }
        has_phrase_start_set = true;
    }
    else if( key_value[0].contains(has_phrase_end_key)  ){
        if(QString(key_value.at(1)).trimmed() == "1"){
            has_phrase_end = true;
        }
        else{
            has_phrase_end = false;
        }
        has_phrase_end_set = true;
    }
    else{

    }
}
void GNGConfig::checkForLocalNGramFileNames(const QStringList& key_value){
    auto index = local_ngram_filenames_key.indexOf(key_value[0]);
    if( index != -1){
        local_ngram_filenames.clear();
        QStringList values = key_value.at(1).split(COMMA);
        for(const auto& value: values){
            local_ngram_filenames.push_back(value.trimmed());
        }
    }
}
//void GNGConfig::checkForRaw1GramFileNames(const QStringList& key_value){
////    auto cc = QString::compare(key_value[0], raw_1grams_01);
//    auto index = raw_1gram_filename_keys.indexOf(key_value[0]);
//    if( index != -1){
//        raw_1gram_filenames.replace(index, key_value[1].trimmed() );
//    }
//}
void GNGConfig::checkForLocal1GramFileNames(const QStringList& key_value){
    auto index = local_1gram_filenames_key.indexOf(key_value[0]);
    if( index != -1){
        local_1gram_filenames.clear();
        QStringList values = key_value.at(1).split(COMMA);
        for(const auto& value: values){
            local_1gram_filenames.push_back(value.trimmed());
        }
    }
}
void GNGConfig::checkForLocalPhraseWordFileNames(const QStringList& key_value){
    auto index = local_phrase_word_filenames_key.indexOf(key_value[0]);
    if( index != -1){
        local_phrase_word_filenames.clear();
        QStringList values = key_value.at(1).split(COMMA);
        for(const auto& value: values){
            local_phrase_word_filenames.push_back(value.trimmed());
        }
    }
}
void GNGConfig::checkForPhraseWordLengths(const QStringList& key_value){
    auto index = phrase_word_lengths_key.indexOf(key_value[0]);
    if( index != -1){
        phrase_word_lengths.clear();
        QStringList values = key_value.at(1).split(COMMA);
        for(const auto& value: values){
            phrase_word_lengths.push_back( (unsigned int)value.trimmed().toInt());
        }
        qDebug() << "GNGConfig::checkForPhraseWordLengths = " << phrase_word_lengths;
    }
}
