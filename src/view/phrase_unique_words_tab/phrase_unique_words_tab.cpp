#include <QCursor>
#include <QMenu>
#include <QSpacerItem>
#include "phrase_unique_words_tab.h"
#include "ui_phrase_unique_words_tab.h"
#include "phrase_unique_word_modelview_widget.h"
//#include "ui_phrase_unique_word_modelview_widget.h"

PhraseUniqueWordsTab::PhraseUniqueWordsTab(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::PhraseUniqueWordsTab),
      phraseword_mv_widgets(QList<PhraseUniqueWordModelViewWidget*>()) ,
      gng_phrase(GNGPhrase())
{
    ui->setupUi(this);
}
PhraseUniqueWordsTab::~PhraseUniqueWordsTab(){
    cleanup();
    delete ui;
}
void PhraseUniqueWordsTab::allWidgetsEnabled(bool value){
    for(auto& item: phraseword_mv_widgets){
        item->setEnabled(value);
    }
}
bool PhraseUniqueWordsTab::setNewPhrase(){
    cleanup();
    for(auto c = 0; c < gng_phrase.phrase_unique_words.size(); ++c){
        phraseword_mv_widgets.push_back( new PhraseUniqueWordModelViewWidget(c, this));
        ui->puwScrollAreaLayout->addWidget(phraseword_mv_widgets.back());
    }
    ui->puwScrollAreaLayout->addStretch();
    adjustTableSize();
    return true;
}

void PhraseUniqueWordsTab::on_phraseWordDataChanged(){
}
void PhraseUniqueWordsTab::cleanup(){
    qDeleteAll(phraseword_mv_widgets.begin(), phraseword_mv_widgets.end());
    phraseword_mv_widgets.clear();
}
void PhraseUniqueWordsTab::adjustTableSize(){
    for(auto& widget : phraseword_mv_widgets){
        widget->resizeToContents();
    }
}
void PhraseUniqueWordsTab::adjustTableSize(unsigned int i){
    if(i < phraseword_mv_widgets.size()){
        phraseword_mv_widgets[i]->resizeToContents();
    }
}

void PhraseUniqueWordsTab::beginReset(){
    for(auto& item: phraseword_mv_widgets){
        item->beginResetModel();
    }
}
void PhraseUniqueWordsTab::endReset(){
    for(auto& item: phraseword_mv_widgets){
        item->endResetModel();
    }
}
void PhraseUniqueWordsTab::updateWidgets(){
    for(auto& item: phraseword_mv_widgets){
        item->update();
    }
}
