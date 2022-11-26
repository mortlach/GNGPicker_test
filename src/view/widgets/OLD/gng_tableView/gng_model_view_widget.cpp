//#include "ngram_model_view_widget.h"
//#include "ui_ngram_model_view_widget.h"
//#include <QCursor>
//#include <QMenu>
//#include <QSpacerItem>


//NgramModelViewWidget::NgramModelViewWidget(unsigned int ngram_index,
//                                           QWidget* parent) :
//    QWidget(parent),
//    ui(new Ui::NgramModelViewWidget) ,
//    ngram_selectionmodel(new QItemSelectionModel()) ,
//    ngram_sortfilterproxymodel(new NGramFilterModel(this)) ,
//    gng_phrase(GNGPhrase()) ,
//    gng_ngram(&gng_phrase.ngram_data[ngram_index]) ,
//    model(NGramModel()),
//    ngram_index(ngram_index)
//{
//    ui->setupUi(this);
//    model.setNewData( *gng_ngram);
//    // first label
//    QString text = "NGram ";
//    text += QString::number(ngram_index);
//    text += QString(" RuneLengths: ");
//    for (int index = 0; index <  gng_ngram->ngram_word_lengths.size(); ++index){
//        text += QString::number(gng_ngram->ngram_word_lengths[index]);
//        if(index != gng_ngram->ngram_word_lengths.size()-1){
//            text += QString("-");
//        }
//    }
//    ui->groupBox->setTitle(text);
//    ngram_sortfilterproxymodel->setSourceModel(&model);
//    ui->tableView->setModel(ngram_sortfilterproxymodel);
//    // selection view
//    ngram_selectionmodel->setModel(ngram_sortfilterproxymodel);
//    ui->tableView->setSelectionModel(ngram_selectionmodel);
//    ui->tableView->show();
//    update();
//}
//NgramModelViewWidget::~NgramModelViewWidget(){
//    delete ui;
//}
//void NgramModelViewWidget::update(){
//    setLabel();
//}
//void NgramModelViewWidget::setLabel(){
//    QString text = "Count = ";
//    text += QString::number(model.rowCount());
//    setLabel(text);
//}
//void NgramModelViewWidget::setLabel(const QString& s){
//    ui->ngram_model_view_label->setText(s);
//}
//void NgramModelViewWidget::on_tableView_space_bar_sig(){
//    QModelIndexList to_toggle;
//    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
//        qDebug() << "row/col" << index.row() << "/" << index.column();
//        to_toggle.push_back(ngram_sortfilterproxymodel->mapToSource(index));
//    }
//    model.toggleChosen(to_toggle);
//}
//void NgramModelViewWidget::on_tableView_left_doubleclick_sig(){
//    QModelIndexList to_toggle;
//    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
//        qDebug() << "row/col" << index.row() << "/" << index.column();
//        to_toggle.push_back(ngram_sortfilterproxymodel->mapToSource(index));
//    }
//    model.toggleChosen(to_toggle);
//}
//void NgramModelViewWidget::applyFilter(int a){
//    qDebug() << "ngramApplyFilter" << a;
//    switch(a){
//        case not_chosen_filter: ngram_sortfilterproxymodel->setFilter("not_chosen"); break;
//        case chosen_filter:     ngram_sortfilterproxymodel->setFilter("chosen");     break;
//        case all_filter:        ngram_sortfilterproxymodel->setFilter("");           break;
//        default:;
//    }
//}
//void NgramModelViewWidget::on_tableView_customContextMenuRequested(){
//    //qDebug() << pt.x() << pt.y();
//    //qDebug() << "showContextMenu passed" << pt.x() << pt.y();
//    //QPoint globalPos = ui->tableView->mapToGlobal(pt);
//    //qDebug() << globalPos.x() << globalPos.y();
//    qDebug() << QCursor().pos().x() << QCursor().pos().y();
//    QPoint pt2 = QPoint(QCursor().pos().x() - 100 , QCursor().pos().y()  );
//    QMenu contextMenu(tr("NGRAM Filter Menu"), this);
//    QAction* all = contextMenu.addAction("Filer: All");
//    QAction* chosen = contextMenu.addAction("Filer: Chosen");
//    QAction* not_chosen = contextMenu.addAction("Filer: Not Chosen");
//    //QAction* reload = contextMenu.addAction("Reload Data");
//    QAction* selectedItem = contextMenu.exec(pt2);
//    if (selectedItem == all){ applyFilter(all_filter); }
//    if (selectedItem == chosen){ applyFilter(chosen_filter); }
//    if (selectedItem == not_chosen){ applyFilter(not_chosen_filter); }
//    //if (selectedItem == reload){ applyFilter(3); }
//}
