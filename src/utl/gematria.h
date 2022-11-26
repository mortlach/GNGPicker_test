#ifndef GEMATRIA_H
#define GEMATRIA_H

#include<QString>
#include<QHash>

class Gematria
{
public:
    Gematria();
    static const QString F_LATIN  ; static const QString F_RUNE  ; static const unsigned int F_VALUE;
    static const QString U_LATIN  ; static const QString U_RUNE  ; static const unsigned int U_VALUE;
    static const QString TH_LATIN ; static const QString TH_RUNE ; static const unsigned int TH_VALUE;
    static const QString O_LATIN  ; static const QString O_RUNE  ; static const unsigned int O_VALUE;
    static const QString R_LATIN  ; static const QString R_RUNE  ; static const unsigned int R_VALUE;
    static const QString C_LATIN  ; static const QString C_RUNE  ; static const unsigned int C_VALUE;
    static const QString G_LATIN  ; static const QString G_RUNE  ; static const unsigned int G_VALUE;
    static const QString W_LATIN  ; static const QString W_RUNE  ; static const unsigned int W_VALUE;
    static const QString H_LATIN  ; static const QString H_RUNE  ; static const unsigned int H_VALUE;
    static const QString N_LATIN  ; static const QString N_RUNE  ; static const unsigned int N_VALUE;
    static const QString I_LATIN  ; static const QString I_RUNE  ; static const unsigned int I_VALUE;
    static const QString J_LATIN  ; static const QString J_RUNE  ; static const unsigned int J_VALUE;
    static const QString EO_LATIN ; static const QString EO_RUNE ; static const unsigned int EO_VALUE;
    static const QString P_LATIN  ; static const QString P_RUNE  ; static const unsigned int P_VALUE;
    static const QString X_LATIN  ; static const QString X_RUNE  ; static const unsigned int X_VALUE;
    static const QString S_LATIN  ; static const QString S_RUNE  ; static const unsigned int S_VALUE;
    static const QString T_LATIN  ; static const QString T_RUNE  ; static const unsigned int T_VALUE;
    static const QString B_LATIN  ; static const QString B_RUNE  ; static const unsigned int B_VALUE;
    static const QString E_LATIN  ; static const QString E_RUNE  ; static const unsigned int E_VALUE;
    static const QString M_LATIN  ; static const QString M_RUNE  ; static const unsigned int M_VALUE;
    static const QString L_LATIN  ; static const QString L_RUNE  ; static const unsigned int L_VALUE;
    static const QString ING_LATIN; static const QString ING_RUNE; static const unsigned int ING_VALUE;
    static const QString OE_LATIN ; static const QString OE_RUNE ; static const unsigned int OE_VALUE;
    static const QString D_LATIN  ; static const QString D_RUNE  ; static const unsigned int D_VALUE;
    static const QString A_LATIN  ; static const QString A_RUNE  ; static const unsigned int A_VALUE;
    static const QString AE_LATIN ; static const QString AE_RUNE ; static const unsigned int AE_VALUE;
    static const QString Y_LATIN  ; static const QString Y_RUNE  ; static const unsigned int Y_VALUE;
    static const QString IO_LATIN ; static const QString IO_RUNE ; static const unsigned int IO_VALUE;
    static const QString EA_LATIN ; static const QString EA_RUNE ; static const unsigned int EA_VALUE;

    static const QVector<unsigned int> rune_value;
    static const QVector<QString> rune_latin;
    static const QVector<QString> rune_rune;
    static const QHash<QString, QString> latin_to_rune;
    static const QHash<QString, QString> rune_to_latin;


    bool isRuneString(const QString& test);



};

#endif // GEMATRIA_H
