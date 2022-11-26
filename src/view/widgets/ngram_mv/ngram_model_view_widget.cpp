#include "ngram_model_view_widget.h"
#include "ui_ngram_model_view_widget.h"
#include <QCursor>
#include <QMenu>
#include <QSpacerItem>


NgramModelViewWidget::NgramModelViewWidget(unsigned int ngram_index,
                                           QWidget* parent) :
    QWidget(parent),
    ui(new Ui::NgramModelViewWidget) ,
    ngram_selectionmodel(new QItemSelectionModel()) ,
    ngram_sortfilterproxymodel(new NGramFilterModel(this)) ,
    gng_phrase(GNGPhrase()) ,
    gng_ngram(gng_phrase.ngram_data[ngram_index]) ,
    model(NGramModel()),
    ngram_index(ngram_index)
{
    ui->setupUi(this);
    model.setNewData( *gng_ngram);
    // first label
    QString text = "NGram ";
    text += QString::number(ngram_index);
    text += QString(" RuneLengths: ");
    for (int index = 0; index <  gng_ngram->ngram_word_lengths.size(); ++index){
        text += QString::number(gng_ngram->ngram_word_lengths[index]);
        if(index != gng_ngram->ngram_word_lengths.size()-1){
            text += QString("-");
        }
    }
    ngram_sortfilterproxymodel->setSourceModel(&model);
    ngram_sortfilterproxymodel->setChosenColumn(model.chosen_col);
    ui->tableView->setModel(ngram_sortfilterproxymodel);
    // selection view
    ngram_selectionmodel->setModel(ngram_sortfilterproxymodel);
    ui->tableView->setSelectionModel(ngram_selectionmodel);
    ui->tableView->sortByColumn(model.counts_col, Qt::AscendingOrder);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
//    connect(ui->savePushButton, &QPushButton::clicked,this,
//            &NgramModelViewWidget::on_savePushButton_clicked_sig );
    update();
}
NgramModelViewWidget::~NgramModelViewWidget(){
    delete ui;
}
void NgramModelViewWidget::update(){
    updateLabel();
    updateTable();
}
void NgramModelViewWidget::updateLabel(){
    setLabel();
}
void NgramModelViewWidget::updateTable(){
    ui->tableView->update();
}
void NgramModelViewWidget::allWidgetsEnabled(bool value){
    ui->tableView->setEnabled(value);
    ui->savePushButton->setEnabled(value);
    ui->loadPushButton->setEnabled(value);
    ui->findPushButton->setEnabled(value);
    ui->delPushButton->setEnabled(value);
}
void NgramModelViewWidget::setLabel(){
    // todo coudl have base class for this sort of stuff
    QString text = "Chosen = ";
    text += QString::number(gng_ngram->getChosenCount());
    text += "/";
    text += QString::number(model.rowCount());
    setLabel(text);
}
void NgramModelViewWidget::setLabel(const QString& s){
    ui->ngram_model_view_label->setText(s);
}
void NgramModelViewWidget::on_savePushButton_clicked(){
    gng_ngram->saveLocalData();
}
void NgramModelViewWidget::on_loadPushButton_clicked(){
    gng_ngram->load(false);
}

void NgramModelViewWidget::on_tableView_space_bar_sig(){
    QModelIndexList to_toggle;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_toggle.push_back(ngram_sortfilterproxymodel->mapToSource(index));
    }
    model.toggleChosen(to_toggle);
    update();
}
void NgramModelViewWidget::on_findPushButton_clicked(){
    QVariant s = QVariant (ui->findLineEdit->text());
    //startrow =
    QList<QModelIndex> list = model.match(
        model.index(0,1),
        Qt::DisplayRole,
        s,
        Qt::MatchContains | Qt::MatchRecursive
        );
    if(list.size() > 0){
        ngram_selectionmodel->select(list[0], QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        ui->tableView->scrollTo(ngram_sortfilterproxymodel->mapFromSource(list[0]));
        //onegram_selectionmodel->selectRow(list[0], QItemSelectionModel::Select);
        //ui->tableView->scrollTo(list[0]);
        qDebug() << "meh" << list;
    }
}

void NgramModelViewWidget::on_delPushButton_clicked(){
    emit model.beginResetModel();
    gng_ngram->deleteNotChosen2();
    update();
}


void NgramModelViewWidget::on_tableView_left_doubleclick_sig(){
    QModelIndexList to_toggle;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_toggle.push_back(ngram_sortfilterproxymodel->mapToSource(index));
    }
    model.toggleChosen(to_toggle);
    update();
}

void NgramModelViewWidget::applyFilter(int a){
//    check filters for phrase unqiue words
    qDebug() << "ngramApplyFilter" << a;
    switch(a){
        case not_chosen_filter: ngram_sortfilterproxymodel->setFilter("not_chosen"); break;
        case chosen_filter:     ngram_sortfilterproxymodel->setFilter("chosen");     break;
        case all_filter:        ngram_sortfilterproxymodel->setFilter("");           break;
        default:;
    }
}
void NgramModelViewWidget::on_tableView_customContextMenuRequested(){
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
void NgramModelViewWidget::resizeToContents(){
    //breaking from here somewhere...
//    for(int i = 0; i<col_count; ++i ){
//       // ui->tableView->resizeColumnToContents(i);
//    }
    QRect rect = ui->tableView->geometry();
//    rect.setWidth(2 + ui->tableView->verticalHeader()->width() +
//            ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2));
//    ui->tableView->setGeometry(rect);
//    ui->tableView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

}
