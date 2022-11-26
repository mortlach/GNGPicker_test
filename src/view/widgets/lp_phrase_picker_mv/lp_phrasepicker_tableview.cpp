#include "lp_Phrasepicker_tableview.h"
#include <QObject>
#include <QHeaderView>
#include <QApplication>
#include <QClipboard>

LPPhrasePickerTableview::LPPhrasePickerTableview(QWidget* parent) :
    QTableView(parent)
{
    //setSelectionBehavior(QAbstractItemView::SelectRows);
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

bool LPPhrasePickerTableview::eventFilter(QObject *obj, QEvent *event)
{   // see  OneGramTableView::eventFilter
    return QTableView::eventFilter(obj, event);
}
void LPPhrasePickerTableview::keyPressEvent(QKeyEvent *event)
{
//    if( (event->key() == Qt::Key_Space)
//            && !event->isAutoRepeat() ){
//        emit space_bar_sig();
//    }
//    else if( (event->key() == Qt::Key_F)
//             && (int(event->modifiers()) == Qt::AltModifier) ){
//        emit alt_f_sig();
//    }
    if(event->matches(QKeySequence::Copy)){
       QApplication::clipboard()->setText(copyRowText());
    }
    else if((event->key() == Qt::Key_C)
            && (int(event->modifiers()) == Qt::ControlModifier) ){
            QApplication::clipboard()->setText(copyRowText());
    }
    else{
        qDebug() << "other caught";
        QTableView::keyPressEvent(event);
    }
}
void LPPhrasePickerTableview::mouseDoubleClickEvent( QMouseEvent * e )
{   //may have to call the parent's method for other cases
    QTableView::mouseDoubleClickEvent( e );
}

QString LPPhrasePickerTableview::copyRowText()const{
    QItemSelectionRange range = selectionModel()->selection().first();
//    for (auto i = range.top(); i <= range.bottom(); ++i)
//    {
    auto i = range.top();
    QStringList rowContents;
    for (auto j = range.left(); j <= range.right(); ++j)
        rowContents << model()->index(i,j).data().toString();
    return rowContents.join("\t");;
}


