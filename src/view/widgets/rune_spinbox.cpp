#include "rune_spinbox.h"
#include <QFont>


RuneSpinBox::RuneSpinBox(QWidget* parent, unsigned int char_index, int start_index):
    QSpinBox(parent) ,
    char_index(char_index)
{
    setRange(0,29);
    QFont f = QFont();
    f.setPointSize(11);
    setFont(f);
    setMaximumSize(30,20);
    setValue(start_index);
}




//QMap<QString, QString> RuneSelector::latin_to_rune =  {
//"F",    "ᚠ",
//"U",    "ᚢ",
//"TH",   "ᚦ",
//'O',    "ᚩ",
//'R',    "ᚱ",
//'C',    "ᚳ",
//'G',    "ᚷ",
//'W',    "ᚹ",
//'H',    "ᚻ",
//'N',    "ᚾ",
//'I',    "ᛁ",
//'J',    "ᛂ",
//"EO",   "ᛇ",
//"P",    "ᛈ",
//"X",    "ᛉ",
//"S",    "ᛋ",
//"T",    "ᛏ",
//"B",    "ᛒ",
//"E",    "ᛖ",
//"M",    "ᛗ",
//"L",    "ᛚ",
//"ING",  "ᛝ",
//"OE",   "ᛟ",
//"D",    "ᛞ",
//"A",    "ᚪ",
//"AE",   "ᚫ",
//"Y",    "ᚣ",
//"IO",   "ᛡ",
//"EA",  "ᛠ"
//     };
