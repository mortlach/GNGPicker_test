#ifndef GNG1GRAMDATA_H
#define GNG1GRAMDATA_H
#include <QDebug>
#include <QVector>
#include <QString>
#include <QVariant>
#include <QString>
#include <QHash>
#include <any>
#include <string>
#include <vector>
#include "gng_data.h"
class GNG1GramData : public GNGData<QString>
{
    /*!
    *  * \brief The GNG1GramData class
    * holds raw data from the 1-gram data files, mainly used as the first major
    * cut to the ngram data
    */
public:
    GNG1GramData(unsigned int word_length);
    ~GNG1GramData(){};
    GNG1GramData& operator=(GNG1GramData& other) = default;


    static const QHash<int,QString> raw_1gram_filenames;
    static const QHash<int,QString> local_1gram_filenames;

    /*!
     * \brief runes words converted to runes
     */
    QVector<QString> runes;
    /*!
     * \brief gematria_sum words word's gematria sum
     */
    QVector<unsigned int> gematria_sum;
    /*!
     * \brief word_length  word length in runes
     */
    unsigned int word_length;
    // virtual overlaods
    bool setFromFileData(const std::vector<std::vector<std::any>>& raw_data);
    bool getAsFileData(std::vector<std::vector<std::any>>& data_to_fill)const;
    //
    bool saveLocalData();
    bool saveRawData()const;
    bool loadLocalData();
    bool loadRawData();
    bool copyTo(const QString& copy_to_directory);
    //
    QString wordToRuneWord(const QString& word)const;
    unsigned int wordToGematriaSum(const QString& word)const;

    bool deleteNotChosen(bool and_squeze = false);
    bool deleteNotChosen2(bool and_squeze = false); // faster??

};

#endif // GNG1GRAMDATA_H
