#include "gng_phrase_worker.h"

GNGPhraseWorker::GNGPhraseWorker(GNGPhrase& gng_phrase):
    gng_phrase_ptr(&gng_phrase)
  , pwl(QList<unsigned int>())
  , has_phrase_start(false)
  , has_phrase_end(false)
  , ng_length(0)
  , last_process_was_success(false)
  , is_working(false)
{}
GNGPhraseWorker::~GNGPhraseWorker(){
}
void GNGPhraseWorker::setNewPhraseParameters(QList<unsigned int> pwl_in,
                            bool has_phrase_start_in,
                            bool has_phrase_end_in,
                            unsigned int ng_length_in)
{
    pwl = pwl_in;
    has_phrase_start = has_phrase_start_in;
    has_phrase_end = has_phrase_end_in;
    ng_length = ng_length_in;
}

void GNGPhraseWorker::processNewPhrase()
{
    is_working = true;
    last_process_was_success = false;
    last_process_was_success = gng_phrase_ptr->newPhrase(pwl,
                                           has_phrase_start,
                                           has_phrase_end,
                                           ng_length);
    is_working = false;
    emit finished(last_process_was_success);
}
void GNGPhraseWorker::processRationlize()
{
    is_working = true;
    last_process_was_success = false;
    last_process_was_success = gng_phrase_ptr->rationlizeChosenForPUWAndNgram();
    is_working = false;
    emit finished(last_process_was_success);
}
