#ifndef PHRASE_UNIUQE_WORDSTABLEVIEW_H
#define PHRASE_UNIUQE_WORDSTABLEVIEW_H
#include <QWidget>
#include <QTableView>
#include <QKeyEvent>
#include <QMouseEvent>

class PhraseUniqueWordsTableView : public QTableView
{
    Q_OBJECT
public:
    PhraseUniqueWordsTableView(QWidget *parent = nullptr);

public: signals:
    void space_bar_sig();
    void alt_f_sig();
    void alt_a_sig();
    void alt_c_sig();
    void alt_n_sig();
    void ctrl_c_sig();
    void left_doubleclick_sig();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent( QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

    int count;
};

#endif // PHRASE_UNIUQE_WORDSTABLEVIEW_H
