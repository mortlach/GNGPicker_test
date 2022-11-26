#include "phrase_unique_words_tableview.h"
#include <QObject>
#include <QHeaderView>

PhraseUniqueWordsTableView::PhraseUniqueWordsTableView(QWidget *parent) :
  QTableView(parent)
, count(0)
{
    setEnabled(true);
    //installEventFilter(this);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setFocusPolicy(Qt::WheelFocus);
    setSortingEnabled(true);
    setAlternatingRowColors(true);
    //setEnabled(true);
    horizontalHeader()->setVisible(true);
    verticalHeader()->setVisible(true);
    horizontalHeader()->setSectionsClickable(true);
    //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionsClickable(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

bool PhraseUniqueWordsTableView::eventFilter(QObject *obj, QEvent *event)
{
    // requires installEventFilter(this);
//    if (event->type() == QEvent::KeyPress) {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//        if(keyEvent->key() == Qt::Key_Space)
//        {
//            qDebug() << "Ate key press" << keyEvent->key();
//            emit table_space_bar();
//            return true;
//        }
//    }
    return QTableView::eventFilter(obj, event);
}


void PhraseUniqueWordsTableView::keyPressEvent(QKeyEvent *event)
{
    if( (event->key() == Qt::Key_Space)  && !event->isAutoRepeat() ){
            emit space_bar_sig();
    }
    else if( (event->key() == Qt::Key_F)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_f_sig();}
    else if( (event->key() == Qt::Key_A)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_a_sig();}
    else if( (event->key() == Qt::Key_C)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_c_sig();}
    else if( (event->key() == Qt::Key_N)  && (int(event->modifiers()) == Qt::AltModifier) ){emit alt_n_sig();}
    else if( (event->key() == Qt::Key_C)  && (int(event->modifiers()) == Qt::ControlModifier) ){emit ctrl_c_sig();}
    else{
        qDebug() << "other caught";
        QTableView::keyPressEvent(event);
    }
}
void PhraseUniqueWordsTableView::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton ){
        qDebug() << "PhraseUniqueWordsTableView left double click caught";
        emit left_doubleclick_sig();
    }
    // may have to call the parent's method for other cases
    //PhraseUniqueWordsTableView::mouseDoubleClickEvent( e );
}
