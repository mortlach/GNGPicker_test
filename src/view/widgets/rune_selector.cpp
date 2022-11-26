#include "rune_selector.h"
#include "ui_rune_selector.h"



QMap<QString, QString> RuneSelector::latin_to_rune =  {
           {QString("F"), QString("ᚠ")}         , {QString("U"), QString("ᚢ")}         , {QString("TH"), QString("ᚦ")}
         , {QString('O'), QString("ᚩ")}         , {QString('R'), QString("ᚱ")}         , {QString('C'), QString("ᚳ")}
         , {QString('G'), QString("ᚷ")}         , {QString('W'), QString("ᚹ")}         , {QString('H'), QString("ᚻ")}
         , {QString('N'), QString("ᚾ")}         , {QString('I'), QString("ᛁ")}         , {QString('J'), QString("ᛂ")}
         , {QString("EO"), QString("ᛇ")}        , {QString('P'), QString("ᛈ")}         , {QString('X'), QString("ᛉ")}
         , {QString('S'), QString("ᛋ")}         , {QString('T'), QString("ᛏ")}         , {QString('B'), QString("ᛒ")}
         , {QString('E'), QString("ᛖ")}         , {QString('M'), QString("ᛗ")}         , {QString('L'), QString("ᛚ")}
         , {QString("ING"), QString("ᛝ")}       , {QString("OE"), QString("ᛟ")}         , {QString("D"), QString("ᛞ")}
         , {QString("A"), QString("ᚪ")}         , {QString("AE"), QString("ᚫ")}         , {QString("Y"), QString("ᚣ")}
         , {QString("IO"), QString("ᛡ")}        , {QString("EA"), QString("ᛠ")}
     };
QMap<QString, QString> RuneSelector::rune_to_latin = {
           {QString("ᚠ"), QString("F")}         , {QString("ᚢ"), QString("U")}         , {QString("ᚦ"), QString("TH")}
         , {QString("ᚩ"), QString('O')}         , {QString("ᚱ"), QString('R')}         , {QString("ᚳ"), QString('C')}
         , {QString("ᚷ"), QString('G')}         , {QString("ᚹ"), QString('W')}         , {QString("ᚻ"), QString('H')}
         , {QString("ᚾ"), QString('N')}         , {QString("ᛁ"), QString('I')}         , {QString("ᛂ"), QString('J')}
         , {QString("ᛇ"), QString("EO")}         , {QString("ᛈ"), QString('P')}         , {QString("ᛉ"), QString('X')}
         , {QString("ᛋ"), QString('S')}         , {QString("ᛏ"), QString('T')}         , {QString("ᛒ"), QString('B')}
         , {QString("ᛖ"), QString('E')}         , {QString("ᛗ"), QString('M')}         , {QString("ᛚ"), QString('L')}
         , {QString("ᛝ"), QString("ING")}         , {QString("ᛟ"), QString("OE")}         , {QString("ᛞ"), QString("D")}
         , {QString("ᚪ"), QString("A")}         , {QString("ᚫ"), QString("AE")}         , {QString("ᚣ"), QString("Y")}
         , {QString("ᛡ"), QString("IO")}         , {QString("ᛠ"), QString("EA")}     };




RuneSelector::RuneSelector(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RuneSelector)
    , widget_to_rune_char(QMap<QCheckBox*, QString>{
           {ui->f_rune, QString("ᚠ")},{ui->u_rune,  QString("ᚢ")},{ui->th_rune,QString("ᚦ")},{ui->o_rune, QString("ᚩ")}
         , {ui->r_rune, QString("ᚱ")},{ui->c_rune,  QString("ᚳ")},{ui->g_rune, QString("ᚷ")},{ui->w_rune, QString("ᚹ")}
         , {ui->h_rune, QString("ᚻ")},{ui->n_rune,  QString("ᚾ")},{ui->i_rune, QString("ᛁ")},{ui->j_rune, QString("ᛂ")}
         , {ui->eo_rune,QString("ᛇ")},{ui->p_rune,  QString("ᛈ")},{ui->x_rune, QString("ᛉ")},{ui->s_rune, QString("ᛋ")}
         , {ui->t_rune, QString("ᛏ")},{ui->b_rune,  QString("ᛒ")},{ui->e_rune, QString("ᛖ")},{ui->m_rune, QString("ᛗ")}
         , {ui->l_rune, QString("ᛚ")},{ui->ing_rune,QString("ᛝ")},{ui->oe_rune,QString("ᛟ")},{ui->d_rune, QString("ᛞ")}
         , {ui->a_rune, QString("ᚪ")},{ui->ae_rune, QString("ᚫ")},{ui->y_rune, QString("ᚣ")},{ui->io_rune,QString("ᛡ")}
         , {ui->ea_rune,QString("ᛠ")}})
    , rune_char_to_widget(QMap<QString, QCheckBox*>{
           {QString("ᚠ"), ui->f_rune  }
         , {QString("ᚢ"), ui->u_rune  }
         , {QString("ᚦ"), ui->th_rune }
         , {QString("ᚩ"), ui->o_rune  }
         , {QString("ᚱ"), ui->r_rune  }
         , {QString("ᚳ"), ui->c_rune  }
         , {QString("ᚷ"), ui->g_rune  }
         , {QString("ᚹ"), ui->w_rune  }
         , {QString("ᚻ"), ui->h_rune  }
         , {QString("ᚾ"), ui->n_rune  }
         , {QString("ᛁ"), ui->i_rune  }
         , {QString("ᛂ"), ui->j_rune  }
         , {QString("ᛇ"), ui->eo_rune }
         , {QString("ᛈ"), ui->p_rune  }
         , {QString("ᛉ"), ui->x_rune  }
         , {QString("ᛋ"), ui->s_rune  }
         , {QString("ᛏ"), ui->t_rune  }
         , {QString("ᛒ"), ui->b_rune  }
         , {QString("ᛖ"), ui->e_rune  }
         , {QString("ᛗ"), ui->m_rune  }
         , {QString("ᛚ"), ui->l_rune  }
         , {QString("ᛝ"), ui->ing_rune}
         , {QString("ᛟ"), ui->oe_rune }
         , {QString("ᛞ"), ui->d_rune  }
         , {QString("ᚪ"), ui->a_rune  }
         , {QString("ᚫ"), ui->ae_rune }
         , {QString("ᚣ"), ui->y_rune  }
         , {QString("ᛡ"), ui->io_rune }
         , {QString("ᛠ"), ui->ea_rune }})
    , rune_mode(true)
    , single_select_mode(true)
{
    ui->setupUi(this);
    ui->gridLayout->setAlignment(ui->latinRunePushButton , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->f_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->u_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->th_rune, Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->o_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->r_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->c_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->g_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->w_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->h_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->n_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->i_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->j_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->eo_rune, Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->p_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->x_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->s_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->t_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->b_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->e_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->m_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->l_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->ing_rune, Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->oe_rune, Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->d_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->a_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->ae_rune, Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->y_rune , Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->io_rune, Qt::AlignHCenter);
    ui->gridLayout->setAlignment(ui->ea_rune, Qt::AlignHCenter);
    //connect(ui->latin_rune_pushButton, SIGNAL(clicked()), this, SLOT(on_latin_rune_pushButton_clicked()));
    connect(ui->runeButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
        [=](QAbstractButton *button){ setSelected(button);});

}
RuneSelector::~RuneSelector()
{
    delete ui;
}
bool RuneSelector::setActiveRunes(const QString& value){
    return setActiveRunes(QList<QString>(value));
}
bool RuneSelector::setActiveRunes(const QList<QString>& values){
    if(!single_select_mode ){
        for(const auto& v : values){
            rune_char_to_widget[v]->setChecked(true);
        }
        return true;
    }
    else if(single_select_mode && (values.size() == 1) ){
        for(const auto& v : values){
            rune_char_to_widget[v]->setChecked(true);
        }
        return true;
    }
    return false;
}
QStringList RuneSelector::getSelectedRunes(){
    QStringList r = QStringList();
    for(const auto& widget : ui->runeButtonGroup->buttons()){
        if(widget->isChecked()){
           r << widget_to_rune_char[(QCheckBox*)widget];
        }
    }
    return r;
}

QString RuneSelector::getSelectedRune(){
    if(single_select_mode){
        for(const auto& widget : ui->runeButtonGroup->buttons()){
            if(widget->isChecked()){
               return widget_to_rune_char[(QCheckBox*)widget];
            }
        }
    }
    return utilities::empty_string;
}



bool RuneSelector::enable(){
    for(const auto& widget : ui->runeButtonGroup->buttons()){
        widget->setEnabled(true);
    }
    return true;
}
bool RuneSelector::disable(){
    for(const auto& widget : ui->runeButtonGroup->buttons()){
        widget->setEnabled(false);
    }
    return true;
}
bool RuneSelector::setSelected(QAbstractButton *button){
    if(single_select_mode){
        if( button->isChecked()){
            selectNone();
            button->setChecked(true);
            emit newRuneSelected();
        }
    }
    return true;
}
bool RuneSelector::selectNone(){
    for(const auto& widget : ui->runeButtonGroup->buttons()){
        widget->setChecked(false);
    }
    return true;
}
void RuneSelector::on_latinRunePushButton_clicked(){
    if(rune_mode){
        for(const auto& widget : ui->runeButtonGroup->buttons()){
            auto text = ((QCheckBox*)widget)->text();
            auto new_text = rune_to_latin[text];
            qDebug()  << "rune_mode" << new_text;
            widget->setText(new_text);
            ui->latinRunePushButton->setText("Runic");
        }
    }else{
        for(const auto& widget : ui->runeButtonGroup->buttons()){
            auto new_text = latin_to_rune[ ((QCheckBox*)widget)->text()];
            qDebug() << "not rune mode" << new_text;
            widget->setText(new_text);
            ui->latinRunePushButton->setText("Latin");
        }
    }
    rune_mode = !rune_mode;
}

//    ui->f_rune;
//    ui->u_rune;
//    ui->th_rune;
//    ui->o_rune;
//    ui->r_rune;
//    ui->c_rune;
//    ui->g_rune;
//    ui->w_rune;
//    ui->h_rune;
//    ui->n_rune;
//    ui->i_rune;
//    ui->j_rune;
//    ui->eo_rune;
//    ui->p_rune;
//    ui->x_rune;
//    ui->s_rune;
//    ui->t_rune;
//    ui->b_rune;
//    ui->e_rune;
//    ui->m_rune;
//    ui->l_rune;
//    ui->ing_rune;
//    ui->oe_rune;
//    ui->d_rune;
//    ui->a_rune;
//    ui->ae_rune;
//    ui->y_rune;
//    ui->io_rune;
//    ui->ea_rune;
RuneSelector2::~RuneSelector2(){}

RuneSelector2::RuneSelector2(QWidget *parent, int max_col ) :
    QWidget(parent) ,
    max_col( max_col )
{



QGridLayout *layout= new QGridLayout;
QCheckBox *ch1 = new QCheckBox(this);
layout->addWidget(ch1,0,0); // adds the widget at position 0 row and 0 column(ok)
QCheckBox *ch2 = new QCheckBox(this);
QCheckBox * empty  = new QCheckBox(this);   empty -> setText("empty");
QCheckBox * F  = new QCheckBox(this);       F -> setText("F / ᚠ");
QCheckBox * U = new QCheckBox(this);        U -> setText("U / ᚢ");
QCheckBox * TH  = new QCheckBox(this);      TH -> setText("TH / ᚦ");
QCheckBox * O = new QCheckBox(this);        O -> setText("O / ᚩ");
QCheckBox * R = new QCheckBox(this);        R -> setText("R / ᚱ");
QCheckBox * C = new QCheckBox(this);        C -> setText("C / ᚳ");
QCheckBox * G = new QCheckBox(this);        G -> setText("G / ᚷ");
QCheckBox * W = new QCheckBox(this);        W -> setText("W / ᚹ");
QCheckBox * H = new QCheckBox(this);        H -> setText("H / ᚻ");
QCheckBox * N = new QCheckBox(this);        N -> setText("N / ᚾ");
QCheckBox * I = new QCheckBox(this);        I -> setText("I / ᛁ");
QCheckBox * J = new QCheckBox(this);        J -> setText("J / ᛂ");
QCheckBox * EO = new QCheckBox(this);       EO -> setText("EO / ᛇ");
QCheckBox * P = new QCheckBox(this);        P -> setText("P / ᛈ");
QCheckBox * X = new QCheckBox(this);        X -> setText("X / ᛉ");
QCheckBox * S = new QCheckBox(this);        S -> setText("S / ᛋ");
QCheckBox * T = new QCheckBox(this);        T -> setText("T / ᛏ");
QCheckBox * B = new QCheckBox(this);        B -> setText("B / ᛒ");
QCheckBox * E = new QCheckBox(this);        F -> setText("E / ᛖ");
QCheckBox * M = new QCheckBox(this);        E -> setText("M / ᛗ");
QCheckBox * L = new QCheckBox(this);        L -> setText("L / ᛚ");
QCheckBox * ING = new QCheckBox(this);      ING -> setText("ING / ᛝ");
QCheckBox * OE  = new QCheckBox(this);      OE->setText("OE / ᛟ");
QCheckBox * D = new QCheckBox(this);        D ->setText("D / ᛞ");
QCheckBox * A = new QCheckBox(this);        A ->setText("A / ᚪ");
QCheckBox * AE  = new QCheckBox(this);      AE->setText("AE / ᚫ");
QCheckBox * Y = new QCheckBox(this);        Y ->setText("Y / ᚣ");
QCheckBox * IO  =new QCheckBox(this);       IO->setText("IO / ᛡ");
QCheckBox * EA  =new QCheckBox(this);       EA->setText("EA / ᛠ");

QList<QCheckBox* > w = {
empty,F    ,U    ,TH   ,
O    ,R    ,C    ,G    ,
W    ,H    ,N    ,I    ,
J    ,EO   ,P    ,X    ,
S    ,T    ,B    ,F    ,
E    ,L    ,ING  ,OE   ,
D    ,A    ,AE   ,Y    ,
IO   ,EA };
QButtonGroup* group = new QButtonGroup(this);
group->setExclusive(true);
int row_count = 0;
int col_count = 0;
for(auto& item : w){
    layout->addWidget(item,row_count,col_count,  Qt::AlignHCenter);
    col_count += 1;
    if( col_count == max_col){
        row_count +=1;
        col_count = 0;
    }
    group->addButton(item);
    //layout->setAlignment(w, Qt::AlignHCenter);
}

//connect(ui->latin_rune_pushButton, SIGNAL(clicked()), this, SLOT(on_latin_rune_pushButton_clicked()));
connect(group, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
    [=](QAbstractButton *button){ setSelected(button);});

}

void RuneSelector2::setSelected(QAbstractButton * b){

    if(b->isChecked()){
        emit newChoice(b->objectName());
    }

}




//stuff

//empty->
//F    ->
//U    ->
//TH   ->
//O    ->
//R    ->
//C    ->
//G    ->
//W    ->
//H    ->
//N    ->
//I    ->
//J    ->
//EO   ->
//P    ->
//X    ->
//S    ->
//T    ->
//B    ->
//F    ->
//E    ->
//L    ->
//ING  ->
//OE   ->
//D    ->
//A    ->
//AE   ->
//Y    ->
//IO   ->
//EA   ->









//QString("empty");
//QString("F / ᚠ");
//QString("U / ᚢ");
//QString("TH / ᚦ");
//QString("O / ᚩ");
//QString("R / ᚱ");
//QString("C / ᚳ");
//QString("G / ᚷ");
//QString("W / ᚹ");
//QString("H / ᚻ");
//QString("N / ᚾ");
//QString("I / ᛁ");
//QString("J / ᛂ");
//QString("EO / ᛇ");
//QString("P / ᛈ");
//QString("X / ᛉ");
//QString("S / ᛋ");
//QString("T / ᛏ");
//QString("B / ᛒ");
//QString("E / ᛖ");
//QString("M / ᛗ");
//QString("L / ᛚ");
//QString("ING / ᛝ");
//QString("OE / ᛟ");
//QString("D / ᛞ");
//QString("A / ᚪ");
//QString("AE / ᚫ");
//QString("Y / ᚣ");
//QString("IO / ᛡ");
//QString("EA / ᛠ");




