#include "gng_data_view.h"
//#include "ui_gng_data_view.h"

GNGDataView::GNGDataView(QWidget *parent) :
    QWidget(parent)
    // ,ui(new Ui::GNGDataView)
{
   // ui->setupUi(this);
}
GNGDataView::~GNGDataView()
{
   // delete ui;
}

//void GNGDataView::on_savePushButton_clicked(){
//    //gng_1gram_data->saveRawData();
//}
//void GNGDataView::on_tableView_t_sig(){
//    QModelIndexList to_set_t;
//    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
//        //qDebug() << "row/col" << index.row() << "/" << index.column();
//        to_set_t.push_back(sortFilterProxyModel->mapToSource(index));
//    }
//    model->setChosen(to_set_t);
//    update();
//}
