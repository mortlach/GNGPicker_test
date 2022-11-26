#include "lp_phrase_picker_tab.h"
#include "ui_lp_phrase_picker_tab.h"
#include "utilities.h"

LPPhrasePickerTab::LPPhrasePickerTab(QWidget *parent) :
      QWidget(parent)
    , phrase_word_lengths(QList<unsigned int>())
    , has_phrase_start(false)
    , has_phrase_end(false)
    , phrase_set_success(false)
    , phrase_text(QString())
    , ui(new Ui::LPPhrasePickerTab)
    , lpsent_selectionmodel(new QItemSelectionModel())
    , lpsent_sortfilterproxymodel(new LPPhrasePickerFilterModel(this))
    , model(LPPhrasePickerModel(this))
    , gematria(Gematria())
{
    ui->setupUi(this);
    lpsent_sortfilterproxymodel->setSourceModel(&model);
    ui->lpSentsTableView->setModel(lpsent_sortfilterproxymodel);
    // selection view
    lpsent_selectionmodel->setModel(lpsent_sortfilterproxymodel);
    ui->lpSentsTableView->setSelectionModel(lpsent_selectionmodel);
    //ui->lpSentsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->lpSentsTableView->setSelectionBehavior();
    ui->lpSentsTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    ui->lpSentsTableView->show();
    ui-> chosenPhraseLabel->setText("Enter word lengths or rune words above");
    //parse_phrase_text();
}
LPPhrasePickerTab::~LPPhrasePickerTab()
{
    delete ui;
}
void LPPhrasePickerTab::setPhrase(const QString& phrase){
    ui->phrasewordLineEdit->setText(phrase);
}
void LPPhrasePickerTab::allWidgetsEnabled(bool value){
    ui->phrasewordLineEdit->setEnabled(value);
    ui->ngram_length_comboBox->setEnabled(value);
    ui->lpSentsTableView->setEnabled(value);
}


void LPPhrasePickerTab::on_phrasewordLineEdit_editingFinished(){
    parse_phrase_text();
}
void LPPhrasePickerTab::parse_phrase_text(){
    phrase_text = ui->phrasewordLineEdit->text();
    char delimiter = ',';
    if( phrase_text.contains(QString(utilities::COMMA))){
        delimiter = utilities::COMMA;
    }
    else if( phrase_text.contains(QString(utilities::SPACE))){
        delimiter = utilities::SPACE;
    }
    else if( phrase_text.contains(QString(utilities::TAB))){
        delimiter = utilities::TAB;
    }
    QStringList list = phrase_text.split(delimiter);
    set_has_phrase_start(list);
    set_has_phrase_end(list);
    set_phrase_word_lengths(list);
    phrase_set_success = has_valid_phrase_data();

    QString chosenPhraseLabelText = QString("");
    if(phrase_set_success){
        for(unsigned int i=0; i<phrase_word_lengths.size(); i++)
        {
            chosenPhraseLabelText += QString::number(phrase_word_lengths[i]);
            chosenPhraseLabelText += ", ";
        }
        chosenPhraseLabelText += " ORIIGNAL TEXT: " + phrase_text;
    }
    else{
        chosenPhraseLabelText = QString("CHOSE PHRASE (Failed to parse ") + phrase_text + QString(")");
    }
    ui-> chosenPhraseLabel->setText(chosenPhraseLabelText);
    qDebug() << "parse phrase" << phrase_text << "phrase_set_success = " << phrase_set_success;
    qDebug() << "emit phrase_chosen()";
    emit phrase_chosen();
}

unsigned int LPPhrasePickerTab::getNgramLength(){
    return ui->ngram_length_comboBox->currentIndex() + 2;
}

QList<unsigned int> LPPhrasePickerTab::getPhraseWorldLengths(){
    return phrase_word_lengths;
}
bool LPPhrasePickerTab::has_valid_phrase_data(){
    bool r = true;
    if(phrase_word_lengths.size()>1){
        uint t = 0;
        if( phrase_word_lengths.contains(t)){
            r = false;
        }
        if(*std::max_element(phrase_word_lengths.begin(), phrase_word_lengths.end()) > 14 ){
            r = false;
        }
    }
    else{
        r = false;
    }
    if(!isValidLPNgram()){
        r = false;
    }
    return r;
}

void LPPhrasePickerTab::set_phrase_word_lengths(const QStringList& list){
    phrase_word_lengths.clear();
    phrase_word_lengths.reserve(list.size());
    for(const auto& item : list){
        bool ok = false;
        uint next_length = item.toUInt(&ok);
        if(ok){
            phrase_word_lengths.push_back(next_length);
        }
        else if( gematria.isRuneString(item)){
            phrase_word_lengths.push_back(item.size());
        }
    }
}
void LPPhrasePickerTab::set_has_phrase_start(const QStringList& list){
    if(list.size() > 0){
        if( (list.first() == "S") || (list.first() == "s")){
            has_phrase_start = true;
            qDebug() <<"Found phrase start";
        }else{
            has_phrase_start = false;
        }
    }
}
void LPPhrasePickerTab::set_has_phrase_end(const QStringList& list){
    if(list.size() > 0){
        if( (list.last() == "E") || (list.last() == "e")){
            has_phrase_end = true;
        }else{
            has_phrase_end = false;
        }
    }
}
bool LPPhrasePickerTab::isValidLPNgram(){
    // todo writte this
    qDebug() <<"LPPhrasePickerTab::isValidLPNgram NOT YET WRITTEN";
    return true;
}
