#ifndef RUNE_SELECTOR_H
#define RUNE_SELECTOR_H

#include <QWidget>
#include <QMap>
#include <QCheckBox>
#include <QGroupBox>
#include <QStringList>
#include "utilities.h"

namespace Ui {
class RuneSelector;
}

class RuneSelector : public QWidget
{
    Q_OBJECT

public:
    explicit RuneSelector(QWidget *parent = nullptr);
    ~RuneSelector();

    QStringList getSelectedRunes();
    QString getSelectedRune();
    bool enable();
    bool disable();
    //bool setSelected(const QStringList& selected);
    bool setSelected(QAbstractButton *button);
    bool selectNone();

    bool setActiveRunes(const QString& value);
    bool setActiveRunes(const QList<QString>& values);



    inline bool setSingleSelect(bool v){ single_select_mode=v; return single_select_mode; }

public slots:
    void on_latinRunePushButton_clicked();

public: signals:
    void newRuneSelected();

private:
    Ui::RuneSelector *ui;
    QMap<QCheckBox*, QString> widget_to_rune_char;
    QMap<QString, QCheckBox*> rune_char_to_widget;
    QList<QString> rune_chars;

    bool rune_mode;
    bool single_select_mode;

    static QMap<QString, QString> latin_to_rune;
    static QMap<QString, QString> rune_to_latin;
};

class RuneSelector2 : public QWidget
{
    Q_OBJECT

public:
    explicit RuneSelector2(QWidget *parent = nullptr,int max_col = 6);
    ~RuneSelector2();

    int max_col;
public slots:
    void setSelected(QAbstractButton * b);

signals:
    void newChoice(const QString& text );

};


#endif // RUNE_SELECTOR_H
