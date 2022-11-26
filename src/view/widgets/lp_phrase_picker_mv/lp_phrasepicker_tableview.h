#ifndef LP_PHRASEPICKER_TABLEVIEW_H
#define LP_PHRASEPICKER_TABLEVIEW_H
#include <QWidget>
#include <QTableView>
#include <QKeyEvent>
#include <QMouseEvent>

class LPPhrasePickerTableview : public QTableView
{
    Q_OBJECT
public:
    LPPhrasePickerTableview(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent( QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QString copyRowText()const;

};

#endif // LP_PHRASEPICKER_TABLEVIEW_H
