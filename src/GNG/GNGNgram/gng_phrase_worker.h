#ifndef GNGPHRASEWORKER_H
#define GNGPHRASEWORKER_H

#include <QObject>
#include "gng_phrase.h"

class GNGPhraseWorker : public QObject {
    Q_OBJECT
public:
    GNGPhraseWorker(GNGPhrase& gng_phrase);
    ~GNGPhraseWorker();
    GNGPhrase* gng_phrase_ptr;


    void setNewPhraseParameters(QList<unsigned int> pwl_in,
                                bool has_phrase_start_in,
                                bool has_phrase_end_in,
                                unsigned int ng_length_in);
    inline bool lastProcessWasASuccess()const{ return last_process_was_success;}
    inline bool isWorking()const{ return is_working;}
    inline bool isNotWorking()const{ return !isWorking();}

public slots:
    void processNewPhrase();
    void processRationlize();

signals:
    void finished(bool success);
    void error(QString err);

private:

    QList<unsigned int> pwl;
    bool has_phrase_start;
    bool has_phrase_end;
    unsigned int ng_length;

    bool last_process_was_success;
    bool is_working;

};
#endif // GNGPHRASEWORKER_H
