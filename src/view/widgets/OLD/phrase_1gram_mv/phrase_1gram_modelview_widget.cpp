#include <QMenu>
#include "one_gram_model_view_widget.h"
#include "ui_one_gram_model_view_widget.h"

PhraseUniqueWordModelViewWidget::PhraseUniqueWordModelViewWidget(unsigned int word_index,


OneGramModelViewWidget::OneGramModelViewWidget(unsigned int word_length,
                                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneGramModelViewWidget) ,
    onegram_selectionmodel(new QItemSelectionModel()) ,
    onegram_sortfilterproxymodel(new OneGramFilterModel(this)) ,
    gng_1grams(GNG1Grams()) ,
    gng_1gram_data(gng_1grams.all_word_data[word_length]) ,
    model(OneGramsModel()),
    word_length(word_length)
{
    ui->setupUi(this);
    model.setNewData( *gng_1gram_data);
    // first label
//    QString text = "WordLength ";
//    text += QString::number(word_length);
//    text += ",  Chosen TODO ";
    //ui->groupBox->setTitle(text);
    onegram_sortfilterproxymodel->setSourceModel(&model);
    ui->tableView->setModel(onegram_sortfilterproxymodel);
    // selection view
    onegram_selectionmodel->setModel(onegram_sortfilterproxymodel);
    ui->tableView->setSelectionModel(onegram_selectionmodel);
    ui->tableView->show();
    //connect(ui->savePushButton, &QPushButton::clicked,this,  &OneGramModelViewWidget::on_savePushButton_clicked_sig );
    update();
}

OneGramModelViewWidget::~OneGramModelViewWidget()
{
    delete ui;
}
void OneGramModelViewWidget::update(){ // main update function
    setLabel();
}
void OneGramModelViewWidget::on_loadPushButton_clicked(){
    gng_1gram_data->loadRawData();
}
void OneGramModelViewWidget::on_findPushButton_clicked(){
   QVariant s = QVariant (ui->findLineEdit->text());

   //startrow =

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
    //gng_1gram_data->deleteNotChosen2();
    update();
}
void OneGramModelViewWidget::on_savePushButton_clicked(){
    gng_1gram_data->saveRawData();
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
void OneGramModelViewWidget::setLabel(const QString& s){
    ui->label->setText(s);
}
void OneGramModelViewWidget::applyFilter(int a){
//    check filters for phrase unqiue words
//           then - way 1-grams no show???
    qDebug() << "ngramApplyFilter" << a;
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
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() +
            ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2));
    ui->tableView->setGeometry(rect);
    ui->tableView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

}
