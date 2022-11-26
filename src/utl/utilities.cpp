#include "utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <any>
#include <QDebug>
#include <QDir>
#include <QVariant>

namespace utilities{
    std::string getFullPath(const std::string& directory, const std::string& filename){
        std::filesystem::path full_path = directory;
        if(filename != std::string("")){
            full_path /= filename;
        }
        return std::filesystem::absolute(full_path).u8string();
    }
//    bool parseConfigFile(const QString &full_path, QMap<QString, QVariant>& config){
//        QString p = full_path;
//        QFile file(full_path);
//        if(!file.exists()){
//            qDebug() << "parseConfigFile ERROR, bad path, " << full_path;
//            return false;
//        }
//        config.clear();
//        if (file.open(QFile::ReadOnly)) {
//            QTextStream in(&file);
//            bool reading_data = false;
//            while (!in.atEnd()) {
//                QString line = in.readLine();
//                QString original_line = line;
//                // trim each line
//                line = line.trimmed();
//                if(line.isEmpty()){
//                    continue;
//                }
//                // check for start end tags
//                if(line[0] == utilities::CURLY_OPEN){
//                    reading_data = true;
//                    continue;
//                }
//                if(line[0] == utilities::CURLY_CLOSE){
//                    break;
//                }
//                if(reading_data){
//                    // remove to the right of comment char #
//                    int pos = line.lastIndexOf(utilities::COMMENT);
//                    if( pos != -1){
//                        line = line.left(pos);
//                        line = line.trimmed();
//                    }
//                    // split on colon :
//                    QStringList key_value = line.split(utilities::COLON);
//                    if(key_value.length() != 2){
//                        qDebug() << "parseConfigFile skipping over this line: " << original_line;
//                        continue;
//                    }
//                    for( QString& item: key_value ){
//                        item = item.trimmed();
//                    }
//                    // assume config values have "\"" remove them
//                    // strip any end commas !!! TODO not sure about this
//                    if(key_value[1].back() == utilities::COMMA){
//                        key_value[1].chop(1);
//                    }
//                    if(key_value[1].back() == utilities::DOUBLE_QUOTE){
//                        key_value[1].chop(1);
//                    }
//                    if(key_value[1].front() == utilities::DOUBLE_QUOTE){
//                        key_value[1].remove(0,1);
//                    }
//                    config[key_value[0]] = QVariant(key_value[1]);
//                }
//            }
//        }
//        // check for expected keys
//        if(!config.contains(utilities::path_to_unique_google_ngram_words_key)){
//            return false;
//        }
//        if(!config.contains(utilities::save_directory_key)){
//            return false;
//        }
//        return true;
//    }
//    bool parseConfigFile(const QString &directory, const QString &filename, QMap<QString, QVariant>& config){
//        QDir dir(directory);
//        QString full_path = dir.absoluteFilePath(filename);
//        return parseConfigFile(full_path, config);
//    }

    // TODO move to class
    bool parseLPSentencesDataFile(const QString &full_path, QList<QStringList>& file_data)
    {
        QString p = full_path;
        QFile file(full_path);
        if(!file.exists()){
            qDebug() << "parseLPSentencesDataFile ERROR, bad path, " << full_path;
            return false;
        }
        file_data.clear();
        if (file.open(QFile::ReadOnly)) {
            QTextStream in(&file);
            bool reading_data = false;
            while (!in.atEnd()) {
                QString line = in.readLine();
                QString original_line = line;
                // trim each line
                line = line.trimmed();
                if(line.isEmpty()){
                    continue;
                }
                // check for start end tags
                if(line.at(0) == utilities::CURLY_OPEN){
                    reading_data = true;
                    continue;
                }
                if(line.at(0) == utilities::CURLY_CLOSE){
                    break;
                }
                if(reading_data){
                    // remove to the right of comment char #
                    int pos = line.lastIndexOf(utilities::COMMENT);
                    if( pos != -1){
                        line = line.left(pos);
                        line = line.trimmed();
                    }
                    // split on space ' '
                    QStringList data = line.split(utilities::SPACE);
                    if(data.length() < 1 ){
                        qDebug() << "parseLPSentencesDataFile skipping over this line: " << original_line;
                        continue;
                    }else{

                        file_data.push_back(data);
                    }
                }
            }
        }
        return true;
    }
    /* generic write csv file */
    bool writeCSVFile(const std::string &directory, const std::string &filename,
                      const std::vector<std::vector<std::string>>& file_data){
        return utilities::writeCSVFile(utilities::getFullPath(directory,filename), file_data);
    }
    bool writeCSVFile(const std::string& path,const std::vector<std::vector<std::string>>& file_data)
    {
        auto p = std::filesystem::absolute(path);
        std::ofstream  file;
        file.open(p);
        if (!file) {
            qDebug() << "failed to open file: " << p.string().c_str();
            return false;
        }{
            for(const auto& item : file_data){
                for(unsigned int i = 0; i < item.size() -1; ++i ){
                    file << item.at(i);
                    file << utilities::COMMA;
                }
                file << item.back();
                file << std::endl;
            }
        }
        file.close();
        qDebug() << path.c_str() << " wrote ok by write1GramDataFile";
        return true;

    }

    /* generic read csv file */
    bool readCSVFile(const std::string &directory, std::string &filename,
                     std::vector<std::vector<std::string>>& file_data){
        return utilities::readCSVFile(utilities::getFullPath(directory,filename), file_data);
    }
    bool readCSVFile(const std::string& path, std::vector<std::vector<std::string>>& file_data){
        auto p = std::filesystem::absolute(path);
        std::ifstream  file;
        file.open(p);
        //file.open(path);
        if (!file) {
            qDebug() << "readCSVFile failed to open file: " << path.c_str();
            return false;
        }
        else {
            //std::vector<std::vector<std::string>>::const_iterator file_data_it = file_data.cbegin();
            auto line_count = std::count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(), '\n');
            file_data.clear();
            file_data.reserve(line_count);
            qDebug() << "Read:" << path.c_str();
            int lineindex = 0;                     // file line counter
            std::string line;
            file.seekg(0, std::ios::beg);
            while (std::getline(file, line))
            {
                line.erase(remove(line.begin(),line.end(),' '),line.end()); // no spaces allowed!
                // parse the read line into separate pieces(tokens) with "," as the delimiter
                std::string tmp;
                std::stringstream ss(line);
                std::vector<std::string> new_data;
                // TODO no error checking
                while(std::getline(ss, tmp, utilities::COMMA)){
                    new_data.push_back(tmp);
                }
                file_data.push_back(new_data);
                lineindex++;
            }
        }
        return true;
    }

    bool allRuneChar(const QString& word){
        return false;
    }

};// namespace utilities
