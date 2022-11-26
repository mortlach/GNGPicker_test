#ifndef LP_SENTENCE_PICKER_FORM_H
#define LP_SENTENCE_PICKER_FORM_H

#include <QMainWindow>
#include <QWidget>
#include <QItemSelection>
#include "lp_phrasepicker_model.h"
#include "gematria.h"
#include "lp_phrasepicker_filtermodel.h"

namespace Ui {class LPPhrasePickerTab;}
class LPPhrasePickerTab : public QWidget
{
    Q_OBJECT

public:
    explicit LPPhrasePickerTab(QWidget* parent = nullptr);
    ~LPPhrasePickerTab();
    QList<unsigned int> phrase_word_lengths;
    bool has_phrase_start;
    bool has_phrase_end;
    bool phrase_set_success;
    QString phrase_text;
    void setPhrase(const QString& phrase);
    unsigned int getNgramLength();
    QList<unsigned int> getPhraseWorldLengths();
    bool has_valid_phrase_data();
    void set_phrase_word_lengths(const QStringList& list);
    void set_has_phrase_start(const QStringList& list);
    void set_has_phrase_end(const QStringList& list);
    bool isValidLPNgram();
    void parse_phrase_text();

    void allWidgetsEnabled(bool value);

public slots:
    void on_phrasewordLineEdit_editingFinished();

signals:
    void phrase_chosen();

friend class MainWindow;
private:
    Ui::LPPhrasePickerTab *ui;
    QItemSelectionModel* lpsent_selectionmodel;
    LPPhrasePickerFilterModel* lpsent_sortfilterproxymodel;
    LPPhrasePickerModel model;
    Gematria gematria;
};

#endif // LP_SENTENCE_PICKER_FORM_H
