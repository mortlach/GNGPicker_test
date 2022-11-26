#include "phrase_1grams_tab.h"
#include "ui_phrase_1grams_tab.h"

Phrase1GramsTab::Phrase1GramsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Phrase1GramsTab),
    ongram_mv_widgets(QList<OneGramModelViewWidget*>()) ,
    gng_1grams(GNG1Grams()){
    ui->setupUi(this);
}
Phrase1GramsTab::~Phrase1GramsTab(){
    cleanup();
    delete ui;
}
void Phrase1GramsTab::allWidgetsEnabled(bool value){
    for(auto& item: ongram_mv_widgets){
        item->setEnabled(value);
    }
}
void Phrase1GramsTab::cleanup(){
    qDeleteAll(ongram_mv_widgets.begin(), ongram_mv_widgets.end());
    ongram_mv_widgets.clear();
}
void Phrase1GramsTab::beginReset(){
    for(auto& item: ongram_mv_widgets){
        item->beginResetModel();
    }
}
void Phrase1GramsTab::endReset(){
    for(auto& item: ongram_mv_widgets){
        item->endResetModel();
    }
}
void Phrase1GramsTab::updateWidgets(){
    for(auto& item: ongram_mv_widgets){
        item->update();
    }
}
void Phrase1GramsTab::adjustTableSize(){
    for(auto& widget : ongram_mv_widgets){
        widget->resizeToContents();
    }
}
void Phrase1GramsTab::adjustTableSize(unsigned int i){
    if(i < ongram_mv_widgets.size()){
        ongram_mv_widgets.at(i)->resizeToContents();
    }
}
void Phrase1GramsTab::on_fontSizeComboBox_currentIndexChanged(int index){
    QFont font;
    font.setPointSize(index+8);
    for(auto& item : ongram_mv_widgets){
        item->ui->tableView->setFont(font);
    }
}
void Phrase1GramsTab::on_filterButtonGroup_buttonClicked(QAbstractButton *b){
    for(auto& item : ongram_mv_widgets){
        item->applyFilter( ui->filterButtonGroup->checkedId());
    }
}
bool Phrase1GramsTab::setNewPhrase(){
    //broke around here
    qDebug() << gng_1grams.local_phrase_1gram_data.size();
    for(unsigned int c = 0; c < gng_1grams.local_phrase_1gram_data.size(); ++c){
        ongram_mv_widgets.push_back(
                    new OneGramModelViewWidget(
                        gng_1grams.local_phrase_1gram_data.at(c)->word_length ,
                        true, this));
        ui->scrollAreaLayout->addWidget(ongram_mv_widgets.back());
    }
    ui->scrollAreaLayout->addStretch();
    adjustTableSize();
    ui->filterButtonGroup->setId(ui->filterAll, OneGramModelViewWidget::all_filter);
    ui->filterButtonGroup->setId(ui->filterChosen, OneGramModelViewWidget::chosen_filter);
    ui->filterButtonGroup->setId(ui->filterNotChosen, OneGramModelViewWidget::not_chosen_filter);
    connect(ui->filterButtonGroup,
            QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this,
            &Phrase1GramsTab::on_filterButtonGroup_buttonClicked);
    return true;
}
