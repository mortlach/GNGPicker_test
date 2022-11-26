#include "one_gram_tab.h"
#include "ui_one_gram_tab.h"

OneGramTab::OneGramTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneGramTab),
    ongram_mv_widgets(QList<OneGramModelViewWidget*>()) ,
    gng_1grams(GNG1Grams()){
    ui->setupUi(this);
    for(unsigned int c = 0; c < gng_1grams.all_raw_word_data.size(); ++c){
        ongram_mv_widgets.push_back( new OneGramModelViewWidget(c, false, this));
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
            &OneGramTab::on_filterButtonGroup_buttonClicked);

}
OneGramTab::~OneGramTab(){
    cleanup();
    delete ui;
}
void OneGramTab::cleanup(){
    qDeleteAll(ongram_mv_widgets.begin(), ongram_mv_widgets.end());
    ongram_mv_widgets.clear();
}
void OneGramTab::allWidgetsEnabled(bool value){
    for(auto& item: ongram_mv_widgets){
        item->setEnabled(value);
    }
}
void OneGramTab::adjustTableSize(){
    for(auto& widget : ongram_mv_widgets){
        widget->resizeToContents();
    }
}
void OneGramTab::adjustTableSize(unsigned int i){
    if(i < ongram_mv_widgets.size()){
        ongram_mv_widgets[i]->resizeToContents();
    }
}


void OneGramTab::beginReset(){
    for(auto& item: ongram_mv_widgets){
        item->beginResetModel();
    }
}
void OneGramTab::endReset(){
    for(auto& item: ongram_mv_widgets){
        item->endResetModel();
    }
}

void OneGramTab::on_fontSizeComboBox_currentIndexChanged(int index){
    QFont font;
    font.setPointSize(index+8);
    for(auto& item : ongram_mv_widgets){
        item->ui->tableView->setFont(font);
    }
}
void OneGramTab::on_filterButtonGroup_buttonClicked(QAbstractButton *b){
    for(auto& item : ongram_mv_widgets){
        item->applyFilter( ui->filterButtonGroup->checkedId());
    }
}

