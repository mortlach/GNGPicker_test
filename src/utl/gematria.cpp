#include "gematria.h"

const QString Gematria::F_LATIN   = QString('F')  ;const QString Gematria::F_RUNE   = QString("ᚠ"); const unsigned int Gematria::F_VALUE = 2;
const QString Gematria::U_LATIN   = QString("U")  ;const QString Gematria::U_RUNE   = QString("ᚢ"); const unsigned int Gematria::U_VALUE = 3;
const QString Gematria::TH_LATIN  = QString("TH") ;const QString Gematria::TH_RUNE  = QString("ᚦ"); const unsigned int Gematria::TH_VALUE = 5;
const QString Gematria::O_LATIN   = QString('O')  ;const QString Gematria::O_RUNE   = QString("ᚩ"); const unsigned int Gematria::O_VALUE = 7;
const QString Gematria::R_LATIN   = QString('R')  ;const QString Gematria::R_RUNE   = QString("ᚱ"); const unsigned int Gematria::R_VALUE = 11;
const QString Gematria::C_LATIN   = QString('C')  ;const QString Gematria::C_RUNE   = QString("ᚳ"); const unsigned int Gematria::C_VALUE = 13;
const QString Gematria::G_LATIN   = QString('G')  ;const QString Gematria::G_RUNE   = QString("ᚷ"); const unsigned int Gematria::G_VALUE = 17;
const QString Gematria::W_LATIN   = QString('W')  ;const QString Gematria::W_RUNE   = QString("ᚹ"); const unsigned int Gematria::W_VALUE = 19;
const QString Gematria::H_LATIN   = QString('H')  ;const QString Gematria::H_RUNE   = QString("ᚻ"); const unsigned int Gematria::H_VALUE = 23;
const QString Gematria::N_LATIN   = QString('N')  ;const QString Gematria::N_RUNE   = QString("ᚾ"); const unsigned int Gematria::N_VALUE = 29;
const QString Gematria::I_LATIN   = QString('I')  ;const QString Gematria::I_RUNE   = QString("ᛁ"); const unsigned int Gematria::I_VALUE = 31;
const QString Gematria::J_LATIN   = QString('J')  ;const QString Gematria::J_RUNE   = QString("ᛂ"); const unsigned int Gematria::J_VALUE = 37;
const QString Gematria::EO_LATIN  = QString("EO") ;const QString Gematria::EO_RUNE  = QString("ᛇ"); const unsigned int Gematria::EO_VALUE = 41;
const QString Gematria::P_LATIN   = QString('P')  ;const QString Gematria::P_RUNE   = QString("ᛈ"); const unsigned int Gematria::P_VALUE = 43;
const QString Gematria::X_LATIN   = QString('X')  ;const QString Gematria::X_RUNE   = QString("ᛉ"); const unsigned int Gematria::X_VALUE = 47;
const QString Gematria::S_LATIN   = QString('S')  ;const QString Gematria::S_RUNE   = QString("ᛋ"); const unsigned int Gematria::S_VALUE = 53;
const QString Gematria::T_LATIN   = QString('T')  ;const QString Gematria::T_RUNE   = QString("ᛏ"); const unsigned int Gematria::T_VALUE = 59;
const QString Gematria::B_LATIN   = QString('B')  ;const QString Gematria::B_RUNE   = QString("ᛒ"); const unsigned int Gematria::B_VALUE = 61;
const QString Gematria::E_LATIN   = QString('E')  ;const QString Gematria::E_RUNE   = QString("ᛖ"); const unsigned int Gematria::E_VALUE = 67;
const QString Gematria::M_LATIN   = QString('M')  ;const QString Gematria::M_RUNE   = QString("ᛗ"); const unsigned int Gematria::M_VALUE = 71;
const QString Gematria::L_LATIN   = QString('L')  ;const QString Gematria::L_RUNE   = QString("ᛚ"); const unsigned int Gematria::L_VALUE = 73;
const QString Gematria::ING_LATIN = QString("ING");const QString Gematria::ING_RUNE = QString("ᛝ"); const unsigned int Gematria::ING_VALUE = 79;
const QString Gematria::OE_LATIN  = QString("OE") ;const QString Gematria::OE_RUNE  = QString("ᛟ"); const unsigned int Gematria::OE_VALUE = 83;
const QString Gematria::D_LATIN   = QString("D")  ;const QString Gematria::D_RUNE   = QString("ᛞ"); const unsigned int Gematria::D_VALUE = 89;
const QString Gematria::A_LATIN   = QString("A")  ;const QString Gematria::A_RUNE   = QString("ᚪ"); const unsigned int Gematria::A_VALUE = 97;
const QString Gematria::AE_LATIN  = QString("AE") ;const QString Gematria::AE_RUNE  = QString("ᚫ"); const unsigned int Gematria::AE_VALUE = 101;
const QString Gematria::Y_LATIN   = QString("Y")  ;const QString Gematria::Y_RUNE   = QString("ᚣ"); const unsigned int Gematria::Y_VALUE = 103;
const QString Gematria::IO_LATIN  = QString("IO") ;const QString Gematria::IO_RUNE  = QString("ᛡ"); const unsigned int Gematria::IO_VALUE = 107;
const QString Gematria::EA_LATIN  = QString("EA") ;const QString Gematria::EA_RUNE  = QString("ᛠ"); const unsigned int Gematria::EA_VALUE = 109;
const QVector<unsigned int> Gematria::rune_value = {Gematria::F_VALUE,
                                                    Gematria::U_VALUE,
                                                    Gematria::TH_VALUE,
                                                    Gematria::O_VALUE,
                                                    Gematria::R_VALUE,
                                                    Gematria::C_VALUE,
                                                    Gematria::G_VALUE,
                                                    Gematria::W_VALUE,
                                                    Gematria::H_VALUE,
                                                    Gematria::N_VALUE,
                                                    Gematria::I_VALUE,
                                                    Gematria::J_VALUE,
                                                    Gematria::EO_VALUE,
                                                    Gematria::P_VALUE,
                                                    Gematria::X_VALUE,
                                                    Gematria::S_VALUE,
                                                    Gematria::T_VALUE,
                                                    Gematria::B_VALUE,
                                                    Gematria::E_VALUE,
                                                    Gematria::M_VALUE,
                                                    Gematria::L_VALUE,
                                                    Gematria::ING_VALUE,
                                                    Gematria::OE_VALUE,
                                                    Gematria::D_VALUE,
                                                    Gematria::A_VALUE,
                                                    Gematria::AE_VALUE,
                                                    Gematria::Y_VALUE,
                                                    Gematria::IO_VALUE,
                                                    Gematria::EA_VALUE};
const QVector<QString> Gematria::rune_latin = {Gematria::F_LATIN,
                                               Gematria::U_LATIN,
                                               Gematria::TH_LATIN,
                                               Gematria::O_LATIN,
                                               Gematria::R_LATIN,
                                               Gematria::C_LATIN,
                                               Gematria::G_LATIN,
                                               Gematria::W_LATIN,
                                               Gematria::H_LATIN,
                                               Gematria::N_LATIN,
                                               Gematria::B_LATIN,
                                               Gematria::T_LATIN,
                                               Gematria::S_LATIN,
                                               Gematria::X_LATIN,
                                               Gematria::P_LATIN,
                                               Gematria::EO_LATIN,
                                               Gematria::J_LATIN,
                                               Gematria::I_LATIN,
                                               Gematria::E_LATIN,
                                               Gematria::M_LATIN,
                                               Gematria::L_LATIN,
                                               Gematria::ING_LATIN,
                                               Gematria::OE_LATIN,
                                               Gematria::D_LATIN,
                                               Gematria::A_LATIN,
                                               Gematria::AE_LATIN,
                                               Gematria::Y_LATIN,
                                               Gematria::IO_LATIN,
                                               Gematria::EA_LATIN};
const QVector<QString> Gematria::rune_rune = {Gematria::F_RUNE,
                                              Gematria::U_RUNE ,
                                              Gematria::TH_RUNE ,
                                              Gematria::O_RUNE ,
                                              Gematria::R_RUNE ,
                                              Gematria::C_RUNE ,
                                              Gematria::G_RUNE ,
                                              Gematria::W_RUNE ,
                                              Gematria::H_RUNE ,
                                              Gematria::N_RUNE ,
                                              Gematria::I_RUNE ,
                                              Gematria::J_RUNE ,
                                              Gematria::EO_RUNE,
                                              Gematria::P_RUNE ,
                                              Gematria::X_RUNE ,
                                              Gematria::S_RUNE ,
                                              Gematria::T_RUNE ,
                                              Gematria::B_RUNE ,
                                              Gematria::E_RUNE ,
                                              Gematria::M_RUNE ,
                                              Gematria::L_RUNE ,
                                              Gematria::ING_RUNE ,
                                              Gematria::OE_RUNE,
                                              Gematria::D_RUNE ,
                                              Gematria::A_RUNE ,
                                              Gematria::AE_RUNE ,
                                              Gematria::Y_RUNE ,
                                              Gematria::IO_RUNE ,
                                              Gematria::EA_RUNE };
const QHash<QString, QString> Gematria::latin_to_rune = QHash<QString, QString>{
    {Gematria::F_LATIN  , Gematria::F_RUNE  },
    {Gematria::U_LATIN  , Gematria::U_RUNE  },
    {Gematria::TH_LATIN , Gematria::TH_RUNE },
    {Gematria::O_LATIN  , Gematria::O_RUNE   },
    {Gematria::R_LATIN  , Gematria::R_RUNE   },
    {Gematria::C_LATIN  , Gematria::C_RUNE   },
    {Gematria::G_LATIN  , Gematria::G_RUNE   },
    {Gematria::W_LATIN  , Gematria::W_RUNE   },
    {Gematria::H_LATIN  , Gematria::H_RUNE   },
    {Gematria::N_LATIN  , Gematria::N_RUNE   },
    {Gematria::I_LATIN  , Gematria::I_RUNE  },
    {Gematria::J_LATIN  , Gematria::J_RUNE  },
    {Gematria::EO_LATIN , Gematria::EO_RUNE },
    {Gematria::P_LATIN  , Gematria::P_RUNE  },
    {Gematria::X_LATIN  , Gematria::X_RUNE  },
    {Gematria::S_LATIN  , Gematria::S_RUNE  },
    {Gematria::T_LATIN  , Gematria::T_RUNE  },
    {Gematria::B_LATIN  , Gematria::B_RUNE  },
    {Gematria::E_LATIN  , Gematria::E_RUNE  },
    {Gematria::M_LATIN  , Gematria::M_RUNE  },
    {Gematria::L_LATIN  , Gematria::L_RUNE  },
    {Gematria::ING_LATIN, Gematria::ING_RUNE},
    {Gematria::OE_LATIN , Gematria::OE_RUNE },
    {Gematria::D_LATIN  , Gematria::D_RUNE  },
    {Gematria::A_LATIN  , Gematria::A_RUNE  },
    {Gematria::AE_LATIN , Gematria::AE_RUNE },
    {Gematria::Y_LATIN  , Gematria::Y_RUNE  },
    {Gematria::IO_LATIN , Gematria::IO_RUNE },
    {Gematria::EA_LATIN , Gematria::EA_RUNE }
};
const QHash<QString, QString> Gematria::rune_to_latin =QHash<QString, QString> {
    {Gematria::F_RUNE   , Gematria::F_LATIN  },
    {Gematria::U_RUNE   , Gematria::U_LATIN  },
    {Gematria::TH_RUNE  , Gematria::TH_LATIN },
    {Gematria::N_RUNE   , Gematria::O_LATIN  },
    {Gematria::H_RUNE   , Gematria::R_LATIN  },
    {Gematria::W_RUNE   , Gematria::C_LATIN  },
    {Gematria::G_RUNE   , Gematria::G_LATIN  },
    {Gematria::C_RUNE   , Gematria::W_LATIN  },
    {Gematria::R_RUNE   , Gematria::H_LATIN  },
    {Gematria::O_RUNE   , Gematria::N_LATIN  },
    {Gematria::I_RUNE   , Gematria::I_LATIN  },
    {Gematria::J_RUNE   , Gematria::J_LATIN  },
    {Gematria::EO_RUNE  , Gematria::EO_LATIN },
    {Gematria::P_RUNE   , Gematria::P_LATIN  },
    {Gematria::X_RUNE   , Gematria::X_LATIN  },
    {Gematria::S_RUNE   , Gematria::S_LATIN  },
    {Gematria::T_RUNE   , Gematria::T_LATIN  },
    {Gematria::B_RUNE   , Gematria::B_LATIN  },
    {Gematria::E_RUNE   , Gematria::E_LATIN  },
    {Gematria::M_RUNE   , Gematria::M_LATIN  },
    {Gematria::L_RUNE   , Gematria::L_LATIN  },
    {Gematria::ING_RUNE , Gematria::ING_LATIN},
    {Gematria::OE_RUNE  , Gematria::OE_LATIN },
    {Gematria::D_RUNE   , Gematria::D_LATIN  },
    {Gematria::A_RUNE   , Gematria::A_LATIN  },
    {Gematria::AE_RUNE  , Gematria::AE_LATIN },
    {Gematria::Y_RUNE   , Gematria::Y_LATIN  },
    {Gematria::IO_RUNE  , Gematria::IO_LATIN },
    {Gematria::EA_RUNE  , Gematria::EA_LATIN }
};
Gematria::Gematria(){}
bool Gematria::isRuneString(const QString& test){
    for(const auto& item: test){
        if( !rune_rune.contains(item)){
            return false;
        }
    }
    return true;
}

