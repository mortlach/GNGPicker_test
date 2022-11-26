#include <QMenu>
#include "one_gram_model_view_widget.h"
#include "ui_one_gram_model_view_widget.h"


OneGramModelViewWidget::OneGramModelViewWidget(unsigned int word_length,
                                bool use_phrase_1grams,
                                QWidget *parent) :
            QWidget(parent),
            ui(new Ui::OneGramModelViewWidget) ,
            onegram_selectionmodel(new QItemSelectionModel()) ,
            onegram_sortfilterproxymodel(new OneGramFilterModel(this)) ,
            gng_1grams(GNG1Grams()) ,
            gng_1gram_data(nullptr) ,
            model(OneGramsModel()),
            word_length(word_length),
            using_phrase_1grams(use_phrase_1grams)
{
    if(!using_phrase_1grams){
        gng_1gram_data = gng_1grams.all_raw_word_data.at(word_length);
    }
    else{
        gng_1gram_data = gng_1grams.getPrase1GramPtrAtWordLength(word_length);
    }
    if(gng_1gram_data){
        ui->setupUi(this);
        model.setNewData( *gng_1gram_data);
        onegram_sortfilterproxymodel->setSourceModel(&model);
        ui->tableView->setModel(onegram_sortfilterproxymodel);
        onegram_selectionmodel->setModel(onegram_sortfilterproxymodel);
        ui->tableView->setSelectionModel(onegram_selectionmodel);
        ui->tableView->show();
        ui->tableView->resizeColumnsToContents();
        // NO DELETE for raw 1 grams
        if(!using_phrase_1grams){
            ui->deletePushButton->setEnabled(false);
        }
        update();
    }else{
        qDebug() << "ERROR gng_1gram_data is null";
    }
}
OneGramModelViewWidget::~OneGramModelViewWidget()
{
    delete ui;
}
void OneGramModelViewWidget::allWidgetsEnabled(bool value){
    ui->tableView->setEnabled(value);
    ui->savePushButton->setEnabled(value);
    ui->loadPushButton->setEnabled(value);
    ui->findPushButton->setEnabled(value);
    ui->deletePushButton->setEnabled(value);
}
void OneGramModelViewWidget::on_loadPushButton_clicked(){
    if(using_phrase_1grams){
        gng_1gram_data->loadLocalData();
    }
    else{
        gng_1gram_data->loadRawData();
    }
    update();
}
void OneGramModelViewWidget::on_findPushButton_clicked(){
   QVariant s = QVariant (ui->findLineEdit->text());
   QList<QModelIndex> list = model.match(
        model.index(0,1),
        Qt::DisplayRole,
        s,
        Qt::MatchContains | Qt::MatchRecursive
        );
   if(list.size() > 0){
       onegram_selectionmodel->select(list[0], QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
       ui->tableView->scrollTo(onegram_sortfilterproxymodel->mapFromSource(list[0]));
       //onegram_selectionmodel->selectRow(list[0], QItemSelectionModel::Select);
       //ui->tableView->scrollTo(list[0]);
       qDebug() << "meh" << list;
   }
}
void OneGramModelViewWidget::on_deletePushButton_clicked(){
    if(using_phrase_1grams){
        gng_1gram_data->deleteNotChosen2();
    }
    else{
    }
    update();
}
void OneGramModelViewWidget::on_savePushButton_clicked(){
    if(using_phrase_1grams){
        gng_1gram_data->saveLocalData();
    }
    else{
        gng_1gram_data->saveRawData();
    }
}
void OneGramModelViewWidget::on_tableView_t_sig(){
    QModelIndexList to_set_t;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_set_t.push_back(onegram_sortfilterproxymodel->mapToSource(index));
    }
    model.setChosen(to_set_t);
    update();
}
void OneGramModelViewWidget::on_tableView_f_sig(){
    QModelIndexList to_set_f;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_set_f.push_back(onegram_sortfilterproxymodel->mapToSource(index));
    }
    model.setNotChosen(to_set_f);
    update();
}

void OneGramModelViewWidget::on_tableView_space_bar_sig(){
    QModelIndexList to_toggle;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_toggle.push_back(onegram_sortfilterproxymodel->mapToSource(index));
    }
    model.toggleChosen(to_toggle);
    update();
}
void OneGramModelViewWidget::on_tableView_left_doubleclick_sig(){
    QModelIndexList to_toggle;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_toggle.push_back(onegram_sortfilterproxymodel->mapToSource(index));
    }
    model.toggleChosen(to_toggle);
    update();
}
void OneGramModelViewWidget::setLabel(){
    QString text = "Chosen = ";
    text += QString::number(gng_1gram_data->getChosenCount());
    text += "/";
    text += QString::number(model.rowCount());
    setLabel(text);
}
void OneGramModelViewWidget::update(){
    updateLabel();
    updateTable();
    //TODO how to force update of the tableview after data changed ??
}
void OneGramModelViewWidget::updateLabel(){
    setLabel();
}
void OneGramModelViewWidget::updateTable(){
    ui->tableView->update();
}
void OneGramModelViewWidget::setLabel(const QString& s){
    ui->label->setText(s);
}
void OneGramModelViewWidget::applyFilter(int a){
    qDebug() << "OneGramModelViewWidget::applyFilter" << a;
    switch(a){
        case not_chosen_filter: onegram_sortfilterproxymodel->setFilter("not_chosen"); break;
        case chosen_filter:     onegram_sortfilterproxymodel->setFilter("chosen");     break;
        case all_filter:        onegram_sortfilterproxymodel->setFilter("");           break;
        default:;
    }
}
void OneGramModelViewWidget::on_tableView_customContextMenuRequested(){
    //qDebug() << pt.x() << pt.y();
    //qDebug() << "showContextMenu passed" << pt.x() << pt.y();
    //QPoint globalPos = ui->tableView->mapToGlobal(pt);
    //qDebug() << globalPos.x() << globalPos.y();
    qDebug() << QCursor().pos().x() << QCursor().pos().y();
    QPoint pt2 = QPoint(QCursor().pos().x() - 100 , QCursor().pos().y()  );
    QMenu contextMenu(tr("NGRAM Filter Menu"), this);
    QAction* all = contextMenu.addAction("Filer: All");
    QAction* chosen = contextMenu.addAction("Filer: Chosen");
    QAction* not_chosen = contextMenu.addAction("Filer: Not Chosen");
    //QAction* reload = contextMenu.addAction("Reload Data");
    QAction* selectedItem = contextMenu.exec(pt2);
    if (selectedItem == all){ applyFilter(all_filter); }
    if (selectedItem == chosen){ applyFilter(chosen_filter); }
    if (selectedItem == not_chosen){ applyFilter(not_chosen_filter); }
    //if (selectedItem == reload){ applyFilter(3); }
}

void OneGramModelViewWidget::resizeToContents(){
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2
                  + ui->tableView->verticalHeader()->width()
                  + ui->tableView->columnWidth(0)
                  + ui->tableView->columnWidth(1)
                  + ui->tableView->columnWidth(2));
    ui->tableView->setGeometry(rect);
    ui->tableView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}
