#include "rune_cut_selector.h"
#include "ui_rune_cut_selector.h"
#include <QLabel>


RuneCutSelector::RuneCutSelector(QWidget *parent):
    QWidget(parent) ,
    mustberune_spinboxes(QList<RuneSpinBox*>()),
    mayberune_spinboxes(QList<RuneSpinBox*>()),
    ui(new Ui::RuneCutSelector),
    gng_phrase(GNGPhrase()),
    my_phrase_unique_word(nullptr),
//    mustBeButtonGroup(new QButtonGroup(this)), // TODO try with buttonGroups
//    maybeButtonGroup(new QButtonGroup(this)),
    must_be("must_be"),
    could_be_int("could_be_int"),
    current_index(0),
    cut_type(utilities::empty_string)
{
    ui->setupUi(this);
    // set IDs TODO in designer??
//    for(int i = 0; i < 14; ++i){
//        ui->buttonGroup->setId(ui->buttonGroup->buttons()[i], i );
//    }
//    connect(ui->buttonGroup,
//            QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
//            [=](){ updateMyPhrase();});
//    // initial widget setup
}
RuneCutSelector::~RuneCutSelector(){
    delete ui;
}


bool RuneCutSelector::changeWidth(int i){
    setMinimumWidth(i);
    return true;
}


void RuneCutSelector::setup(unsigned int phrase_word_index){
    my_phrase_unique_word = gng_phrase.phrase_unique_words[phrase_word_index];
    addRuneSpinBoxes();
}



void RuneCutSelector::addRuneSpinBoxes(){

//    doing this - connect up singals - then manke rtune-cuts work
//     then the rationlize function ...
//            then quality fo life widgets (auto-filter)

    if(my_phrase_unique_word){
        for(unsigned int i = 0 ; i < my_phrase_unique_word->word_length; ++i){
            int in =utilities::rune_to_number.value(my_phrase_unique_word->mustbe_character[i], 29);
            mustberune_spinboxes.push_back(new RuneSpinBox(this, i, in));
//            mustberune_spinboxes.back()->setValue(utilities::rune_to_number.value(my_phrase_unique_word->mustbe_character[i], 29));// TODO conts int
            connect(mustberune_spinboxes.back(),&QSpinBox::valueChanged, this,
                    &RuneCutSelector::updateMustBe);
            ui->mustbeLayout->addWidget(mustberune_spinboxes.back(),  Qt::AlignLeft);
            in = utilities::rune_to_number.value(my_phrase_unique_word->maybe_interrupter[i], 29);// TODO conts int
            mayberune_spinboxes.push_back(new RuneSpinBox(this, i, in));
            // TODO DISABLED FOR NOW LATER VERSION IMPLMENTATION
            mayberune_spinboxes.back()->setEnabled(false);
            connect(mayberune_spinboxes.back(),&QSpinBox::valueChanged, this,
                    &RuneCutSelector::updateMaybe);
            ui->maybeIntLayout->addWidget(mayberune_spinboxes.back(), Qt::AlignLeft);
        }
        ui->mustbeLayout->addStretch();
        ui->maybeIntLayout->addStretch();
    }
}

void RuneCutSelector::updateMustBe(int value){
    if(my_phrase_unique_word){
        qDebug() << "updateMustBe " << value;
        auto s = sender();
        int i =  mustberune_spinboxes.indexOf(s);
        RuneSpinBox* p = dynamic_cast<RuneSpinBox*>(s);
        unsigned int i2 = p->char_index;
        QChar v = p->textFromValue(value)[0];
        my_phrase_unique_word->setMustBeChar(v, i);
        newRuneCut();
    }
}
void RuneCutSelector::updateMaybe(int value){
    if(my_phrase_unique_word){
        qDebug() << "updateMaybe " << value;
        auto s = sender();
        int i =  mayberune_spinboxes.indexOf(s);
        RuneSpinBox* p = dynamic_cast<RuneSpinBox*>(s);
        QChar v = p->textFromValue(value)[0];
        my_phrase_unique_word->setMayBeChar(v, i);
        newRuneCut();
    }
}

void RuneCutSelector::newRuneCut(){

    if(my_phrase_unique_word->mustBeCutsChanged()){

    }

}

void RuneCutSelector::on_applyPushButton_clicked(){
    bool data_changed = my_phrase_unique_word->applyCuts();
    if(my_phrase_unique_word->data_changed_last_apply_cut ){
        emit runeCutSelector();
    }
}


void RuneCutSelector::toggleApplyButton(bool state){

    if(state){
        ui->applyPushButton->setEnabled(true);
        // other stuff
    }
    else{
        ui->applyPushButton->setEnabled(false);
        // other stuff
    }

}







void RuneCutSelector::updateMyPhrase(){
    if(my_phrase_unique_word){
//        if( ui->activeCheckBox->isChecked()){
//            // get data and set in in my_phrase
//            QString r = ui->runeSelector->getSelectedRune();
//            QList<QString> active_chars = getActiveChars();
//            if(isCouldBeInt()){
//                my_phrase_unique_word->maybe_interrupter = active_chars;
//                my_phrase_unique_word->maybe_active = true;
//                my_phrase_unique_word->mustbe_active = false;
//            }
//            else if(isMustBe()){
//                my_phrase_unique_word->maybe_interrupter = active_chars;
//                my_phrase_unique_word->mustbe_active = true;
//                my_phrase_unique_word->maybe_active = false;
//            }
//            else{
//                //QDebug << "RuneCutSelector";
//            }
//        }
//        else{
//            // my_phrase data must be blank
//            my_phrase_unique_word->mustbe_active = false;
//            my_phrase_unique_word->maybe_active = false;
//        }
    }
    else{
        qDebug() << "updateMyPhrase, my_phrase_unique_word is null";
    }
}

void RuneCutSelector::setGUiFromPhraseData(){
    if(my_phrase_unique_word){
        if(isCouldBeInt()){
            setGui(my_phrase_unique_word->maybe_interrupter,my_phrase_unique_word->maybe_active);
        }
        else if(isMustBe()){
            setGui(my_phrase_unique_word->maybe_interrupter,my_phrase_unique_word->maybe_active);
        }
    }
    else{
        qDebug() << "setGUiFromPhraseData, my_phrase_unique_word is null";
    }
}
void RuneCutSelector::setGui(const QString& data, bool active){
        qDebug() << "RuneCutSelector::setGui called TODO";
    //    for(int i = 0; i < 14; ++i){
//        if( i < data.size()){
//            if( data[i] == utilities::empty_string){
//                ui->buttonGroup->button(i)->setChecked(false);
//            }
//            else{
//                ui->buttonGroup->button(i)->setChecked(true);
//                ui->runeSelector->setActiveRunes(data[i]);
//            }
//        }
//        else{
//            ui->buttonGroup->button(i)->setChecked(false);
//            ui->buttonGroup->button(i)->setDisabled(true);
//        }
//    }
//    ui->activeCheckBox->setChecked(active);
}
void RuneCutSelector::updatePhraseWordIndex(unsigned int new_index){
    current_index = new_index;
    if(gng_phrase.phrase_word_count > new_index) {
        my_phrase_unique_word = gng_phrase.phrase_unique_words[current_index];
        setGUiFromPhraseData();
    }
    else{
        qDebug() << "ERROR updatePhraseWordIndex, gng_phrase.phrase_word_count > new_index, ";
    }
}
QList<QString> RuneCutSelector::getActiveChars(){
//    QString r = ui->runeSelector->getSelectedRune();
    QList<QString> active_chars;
//    for(int i = 0; i < 14; ++i){
//        if(ui->buttonGroup->button(i)->isChecked()){
//            active_chars.push_back(r);
//        }
//        else{
//            active_chars.push_back(utilities::empty_string);
//        }
//    }
    return active_chars;
}



