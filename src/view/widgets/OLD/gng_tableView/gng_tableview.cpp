#include "gng_tableview.h"
#include <QObject>
#include <QHeaderView>

GNGTableView::GNGTableView(QWidget* parent) :
    QTableView(parent) ,
    count(0)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setFocusPolicy(Qt::WheelFocus);
    setSortingEnabled(true);
    setAlternatingRowColors(true);
    //setEnabled(true);
    horizontalHeader()->setVisible(true);
    verticalHeader()->setVisible(true);
    horizontalHeader()->setSectionsClickable(true);
    //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    verticalHeader()->setSectionsClickable(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

bool GNGTableView::eventFilter(QObject *obj, QEvent *event)
{
    // see  OneGramTableView::eventFilter
    return QTableView::eventFilter(obj, event);
}
void GNGTableView::keyPressEvent(QKeyEvent *event)
{
    if( (event->key() == Qt::Key_Space)  && !event->isAutoRepeat() ){
        emit space_bar_sig();
    }
    else if( (event->key() == Qt::Key_F)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_f_sig();}
    else if( (event->key() == Qt::Key_F)  ){emit f_sig();}
    else if( (event->key() == Qt::Key_T)  ){emit t_sig();}
    else if( (event->key() == Qt::Key_A)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_a_sig();}
    else if( (event->key() == Qt::Key_C)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_c_sig();}
    else if( (event->key() == Qt::Key_N)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_n_sig();}
    else if( (event->key() == Qt::Key_C)  && (int(event->modifiers()) == Qt::ControlModifier) ){emit ctrl_c_sig();}
    else{
        qDebug() << "other caught";
        QTableView::keyPressEvent(event);
    }
}
void GNGTableView::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton ){
        qDebug() << "GNGTableView left double click caught";
        emit left_doubleclick_sig();
    }
    // may have to call the parent's method for other cases
    //GNGTableView::mouseDoubleClickEvent( e );
}

// TODO add this and other useful things
//void resizeToContents(){
//    ui->tableView->resizeColumnToContents(0);
//    ui->tableView->resizeColumnToContents(1);
//    ui->tableView->resizeColumnToContents(2);
//    QRect rect = ui->tableView->geometry();
//    rect.setWidth(2 + ui->tableView->verticalHeader()->width() +
//            ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2));
//    ui->tableView->setGeometry(rect);
//    ui->tableView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

//}
