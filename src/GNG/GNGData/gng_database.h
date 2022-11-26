#ifndef GNG_DATA_BASE_H
#define GNG_DATA_BASE_H
#include <QDebug>
#include <QVector>
#include <QString>
#include <QElapsedTimer>
#include "gng_config.h"

/*!
 * \brief The GNGDataBase class
 *        Base class to hold enum and templated words, and other useful stuff
 */
class GNGDataBase
{
public:
    /*!
     * \brief The FileType enum: to enable automatic load save of different data structures
     */
    enum FileType{one_gram = 0,     n_gram_no_chosen = 1,  n_gram_chosen= 2,
                  unique_words = 3, not_known = 4};
    GNGDataBase(FileType type_in = not_known,  unsigned int ngram_length = 1);
    ~GNGDataBase();
    GNGDataBase& operator=(GNGDataBase& other) = default;
    /*!
     * \brief info_string
     */
    QString info_string;
    /*!
     * \brief config
     */
    GNGConfig config;
    /*!
     * \brief ngram_length
     */
    unsigned int ngram_length;
    /*!
     * \brief timer
     */
    QElapsedTimer timer;
    /*!
     * \brief chosen, whatever type of GNG data object you are, you have a chosen
     */
    QVector<bool> chosen; //
    unsigned int chosen_count;
    unsigned int not_chosen_count;

    QString timeSince(qint64 ts);

public:
    bool setChosen(unsigned int i, bool value);
    bool getChosen(unsigned int i);
    void toggleChosen(unsigned int i);
    bool isChosen(unsigned int i);
    bool isNotChosen(unsigned int i);

    bool setChosen(int i, bool value){ return setChosen((unsigned int)i, value ); }
    bool getChosen(int i){ return getChosen((unsigned int)i); }
    void toggleChosen(int i){ return toggleChosen((unsigned int)i); }
    bool isChosen(int i){ return isChosen((unsigned int)i); }
    bool isNotChosen(int i){ return isNotChosen((unsigned int)i); }

    QString getFullPath(const QString& dir, const QString& filename);

    GNGDataBase::FileType type;
    void updateChosenCounts();
    unsigned int size()const;
    //friend class GNGData<>;
//private:
    /*!
     * \brief local_data_filedir
     */
    QString local_data_filedir; // can read and write to
    /*!
     * \brief raw_data_filedir
     */
    QString raw_data_filedir; // only ever read
    /*!
     * \brief local_data_filename
     */
    QString local_data_filename; // can read and write to
    /*!
     * \brief raw_data_filename
     */
    QString raw_data_filename; // only ever read
    /*!
     * \brief local_data_filepath
     */
    QString local_data_filepath; // can read and write to
    /*!
     * \brief raw_data_filepath
     */
    QString raw_data_filepath; // only ever read
};

#endif // GNG_DATA_BASE_H
