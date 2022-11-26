#ifndef RUNE_SPINBOX_H
#define RUNE_SPINBOX_H

#include <QSpinBox>
#include <QList>
#include "utilities.h"

class RuneSpinBox  : public QSpinBox{
        Q_OBJECT
public:
    RuneSpinBox(QWidget* parent = nullptr, unsigned int char_index = 0, int start_index = 0);

    bool rune_mode = false;
    bool letter_mode = true;
    int char_index;
//    todo keep buildiong interface to this - link it to actual data
//    add in convenice buttons (like filter all table sin view radio buttons)

    //inline void setValue(int i){ setValue(i);}

    QString textFromValue(int value) const
    {
        if(value == 29){
            return "_"; // TODO make constant
        }
        else if(rune_mode){
            return utilities::number_to_rune[value];
        }
        else{
            return utilities::number_to_letter[value]; // TODO this is not going to work in general for letters
        }
    }

};

#endif // RUNESPINBOX_H
