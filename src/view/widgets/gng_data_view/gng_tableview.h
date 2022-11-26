#ifndef GNG_TABLEVIEW_H
#define GNG_TABLEVIEW_H
#include <QWidget>
#include <QTableView>
#include <QKeyEvent>
#include <QMouseEvent>

class GNGTableView : public QTableView
{
    Q_OBJECT
public:
    GNGTableView(QWidget *parent = nullptr);

    void allWidgetsEnabled(bool value);

public: signals:
    void space_bar_sig();
    void alt_f_sig();
    void f_sig();
    void t_sig();
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

#endif // GNG_TABLEVIEW_H
