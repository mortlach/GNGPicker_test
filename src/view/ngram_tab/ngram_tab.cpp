#include "ngram_tab.h"
#include "ui_ngram_tab.h"

NGramTab::NGramTab(QWidget *parent) :
    QWidget(parent) ,
    ui(new Ui::NGramTab) ,
    gng_phrase(GNGPhrase()) ,
    ngram_mv_widgets(QList<NgramModelViewWidget*>())
{
    ui->setupUi(this);
}
NGramTab::~NGramTab(){
    cleanup();
    delete ui;
}
bool NGramTab::setNewPhrase(){
    cleanup();
    for(unsigned int c = 0; c < gng_phrase.ngram_data.size(); ++c){
        ngram_mv_widgets.push_back( new NgramModelViewWidget(c, this));
        ui->ngramScrollAreaLayout->addWidget(ngram_mv_widgets.back());
    }
    ui->ngramScrollAreaLayout->addStretch();
    adjustTableSize();
    return true;
}
void NGramTab::allWidgetsEnabled(bool value){
    for(auto& item: ngram_mv_widgets){
        item->setEnabled(value);
    }
}
void NGramTab::cleanup(){
    qDeleteAll(ngram_mv_widgets.begin(), ngram_mv_widgets.end());
    ngram_mv_widgets.clear();
}

void NGramTab::adjustTableSize(){
    for(auto& widget : ngram_mv_widgets){
        widget->resizeToContents();
    }
}
void NGramTab::beginReset(){
    for(auto& item: ngram_mv_widgets){
        item->beginResetModel();
    }
}
void NGramTab::endReset(){
    for(auto& item: ngram_mv_widgets){
        item->endResetModel();
    }
}
void NGramTab::updateWidgets(){
    for(auto& item: ngram_mv_widgets){
        item->update();
    }
}

//void NGramTab::adjustTableSize(unsigned int i){
//    if(i < ngram_mv_widgets.size()){
//        ngram_mv_widgets[i]->resizeToContents();
//    }
//}



//ngramTabHorizontalLayout
