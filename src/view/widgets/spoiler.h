#ifndef SPOILER_H
#define SPOILER_H
/*
 * Thanks to
 * https://stackoverflow.com/questions/32476006/how-to-make-an-expandable-collapsable-section-widget-in-qt/37119983#37119983
*/
#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>

class Spoiler : public QWidget {
    Q_OBJECT
private:
    QGridLayout mainLayout;
    QToolButton toggleButton;
    QFrame headerLine;
    QParallelAnimationGroup toggleAnimation;
    QScrollArea contentArea;
    int animationDuration{300};
    void setTitle( const QString & title);
    void animate(const bool checked);
public:
    explicit Spoiler(QWidget *parent = 0, const QString & title = "", const int animationDuration = 300);
    void setContentLayout(QLayout & contentLayout); }



;

#endif // SPOILER_H
