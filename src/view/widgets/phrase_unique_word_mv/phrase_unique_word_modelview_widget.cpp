#include <QCursor>
#include <QMenu>
#include <QSpacerItem>
#include "phrase_unique_word_modelview_widget.h"
#include "ui_phrase_unique_word_modelview_widget.h"
#include "ui_rune_cut_selector.h"

PhraseUniqueWordModelViewWidget::PhraseUniqueWordModelViewWidget(unsigned int word_index,
                                                                 QWidget* parent) :
    QWidget(parent),
    ui(new Ui::PhraseUniqueWordModelViewWIdget) ,
    runeCutSelector(new RuneCutSelector()) ,
    puw_selectionmodel ( new QItemSelectionModel() ) ,
    puw_sortfilterproxymodel(new PhraseUniqueWordsFilterModel()) ,
    gng_phrase(GNGPhrase()) ,
    gng_phrase_word(gng_phrase.phrase_unique_words[word_index]) ,
    model(PhraseUniqueWordsModel(this)),
    word_index(word_index)
{
    ui->setupUi(this);
    model.setNewData(*gng_phrase_word);
    QString text = QString("RuneLength = ");
    text += QString::number(gng_phrase_word->word_length);
    //ui->groupBox->setTitle(text);
    puw_sortfilterproxymodel->setSourceModel(&model);
    puw_sortfilterproxymodel->setChosenColumn(model.chosen_col);
    ui->tableView->setModel(puw_sortfilterproxymodel);
    // selection view
    puw_selectionmodel->setModel(puw_sortfilterproxymodel);
    ui->tableView->setSelectionModel(puw_selectionmodel);
    ui->tableView->show();
    ui->spoiler->setContentLayout(*runeCutSelector->ui->gridLayout);
    runeCutSelector->setup(word_index);
    update();
}
PhraseUniqueWordModelViewWidget::~PhraseUniqueWordModelViewWidget(){
    delete ui;
}
void PhraseUniqueWordModelViewWidget::allWidgetsEnabled(bool value){
    ui->tableView->setEnabled(value);
    ui->savePushButton->setEnabled(value);
    ui->loadPushButton->setEnabled(value);
    ui->findPushButton->setEnabled(value);
    ui->delPushButton->setEnabled(value);
}
void PhraseUniqueWordModelViewWidget::on_savePushButton_clicked(){
    gng_phrase_word->save();
}
void PhraseUniqueWordModelViewWidget::on_loadPushButton_clicked(){
    gng_phrase_word->load();
}
void PhraseUniqueWordModelViewWidget::on_findPushButton_clicked(){
    QVariant s = QVariant (ui->findLineEdit->text());
    //startrow =
    QList<QModelIndex> list = model.match(
        model.index(0,0),
        Qt::DisplayRole,
        s,
        Qt::MatchContains | Qt::MatchRecursive
        );
    if(list.size() > 0){
        puw_selectionmodel->select(list[0], QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
        ui->tableView->scrollTo(puw_sortfilterproxymodel->mapFromSource(list[0]));
        //onegram_selectionmodel->selectRow(list[0], QItemSelectionModel::Select);
        //ui->tableView->scrollTo(list[0]);
        qDebug() << "meh" << list;
    }
}
void PhraseUniqueWordModelViewWidget::on_delPushButton_clicked(){
    emit model.beginResetModel();
    gng_phrase_word->deleteNotChosen2();
    update();
    emit model.endResetModel();
}
void PhraseUniqueWordModelViewWidget::setLabel(const QString& s){
    ui->label_1->setText(s);
}
void PhraseUniqueWordModelViewWidget::setLabel(){
    // todo could have base class for this sort of stuff
    QString text = "Chosen = ";
    text += QString::number(gng_phrase_word->getChosenCount());
    text += "/";
    text += QString::number(model.rowCount());
    setLabel(text);
}

void PhraseUniqueWordModelViewWidget::update(){
    updateLabel();
    updateTable();
}
void PhraseUniqueWordModelViewWidget::updateLabel(){
    setLabel();
}
void PhraseUniqueWordModelViewWidget::updateTable(){
    ui->tableView->update();
}
void PhraseUniqueWordModelViewWidget::on_tableView_space_bar_sig(){
    QModelIndexList to_toggle;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_toggle.push_back(puw_sortfilterproxymodel->mapToSource(index));
    }
    model.toggleChosen(to_toggle);
    update();
}
void PhraseUniqueWordModelViewWidget::on_tableView_left_doubleclick_sig(){
    QModelIndexList to_toggle;
    for(const QModelIndex& index: ui->tableView->selectionModel()->selectedRows()){
        //qDebug() << "row/col" << index.row() << "/" << index.column();
        to_toggle.push_back(puw_sortfilterproxymodel->mapToSource(index));
    }
    model.toggleChosen(to_toggle);
    update();
}
void PhraseUniqueWordModelViewWidget::on_tableView_customContextMenuRequested(){
    //qDebug() << pt.x() << pt.y();
    //qDebug() << "showContextMenu passed" << pt.x() << pt.y();
    //QPoint globalPos = ui->tableView->mapToGlobal(pt);
    //qDebug() << globalPos.x() << globalPos.y();
    qDebug() << QCursor().pos().x() << QCursor().pos().y();
    QPoint pt2 = QPoint(QCursor().pos().x() - 100 , QCursor().pos().y()  );
    QMenu contextMenu(tr("PUW Filter Menu"), this);
    QAction *all = contextMenu.addAction("Filer: All");
    QAction *chosen = contextMenu.addAction("Filer: Chosen");
    QAction *not_chosen = contextMenu.addAction("Filer: Not Chosen");
    QAction *reload = contextMenu.addAction("Reload Data");
    QAction* selectedItem = contextMenu.exec(pt2);
    if (selectedItem == all){ applyFilter(0); }
    if (selectedItem == chosen){ applyFilter(1); }
    if (selectedItem == not_chosen){ applyFilter(2); }
    if (selectedItem == reload){ applyFilter(3); }
}
void PhraseUniqueWordModelViewWidget::applyFilter(int a)
{
//    qDebug() << "puwApplyFilter" << a;
    switch(a){
        case 0: puw_sortfilterproxymodel->setFilter(""); break;
        case 1: puw_sortfilterproxymodel->setFilter("chosen"); break;
        case 2: puw_sortfilterproxymodel->setFilter("not_chosen"); break;
        default:;
    }
}

void PhraseUniqueWordModelViewWidget::resizeToContents(){
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() +
            ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2));
    ui->tableView->setGeometry(rect);
    ui->tableView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    int i = ui->tableView->width();
    runeCutSelector->changeWidth(i);
}


