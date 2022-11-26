QT       += core gui
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++17 console
#CONFIG -= app_bundle

QMAKE_CXXFLAGS += -Og
#QMAKE_CXXFLAGS += -Og
#QMAKE_CXXFLAGS -= -O1
#QMAKE_CXXFLAGS -= -O2
#QMAKE_CXXFLAGS -= -O3

DESTDIR = $$PWD # build to source dir. to allow for relative imports

INCLUDEPATH += src/utl
INCLUDEPATH += src/GNG
INCLUDEPATH += src/GNG/GNG1grams
INCLUDEPATH += src/GNG/GNGNgram
INCLUDEPATH += src/GNG/GNGData
INCLUDEPATH += src/view
INCLUDEPATH += src/view/one_gram_tab
INCLUDEPATH += src/view/lp_phrase_picker_tab
INCLUDEPATH += src/view/ngram_tab
INCLUDEPATH += src/view/phrase_unique_words_tab
INCLUDEPATH += src/view/phrase_1grams_tab
INCLUDEPATH += src/view/widgets
INCLUDEPATH += src/view/widgets/lp_phrase_commands
INCLUDEPATH += src/view/widgets/ngram_mv
INCLUDEPATH += src/view/widgets/phrase_unique_word_mv
INCLUDEPATH += src/view/widgets/lp_phrase_picker_mv
INCLUDEPATH += src/view/widgets/ngram_mv
INCLUDEPATH += src/view/widgets/gng_data_view
INCLUDEPATH += src/view/widgets/one_gram_word_mv

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    src/GNG/GNGNgram/gng_phrase_worker.cpp \
    src/utl/gematria.cpp \
    src/view/phrase_1grams_tab/phrase_1grams_tab.cpp
SOURCES += src/GNG/GNGData/gng_data.cpp 
SOURCES += src/GNG/GNGData/gng_database.cpp 
SOURCES += src/view/widgets/gng_data_view/gng_data_view.cpp 
SOURCES += src/view/widgets/gng_data_view/gng_filtermodel.cpp 
SOURCES += src/view/widgets/gng_data_view/gng_model.cpp 
SOURCES += src/view/widgets/gng_data_view/gng_tableview.cpp 
SOURCES += src/view/widgets/rune_spinbox.cpp
SOURCES += src/view/widgets/spoiler.cpp
SOURCES += src/GNG/GNG1grams/gng_1gram_data.cpp
SOURCES += src/GNG/GNG1grams/gng_1grams.cpp
SOURCES += src/GNG/GNGNgram/gng_ngram.cpp
SOURCES += src/GNG/GNGNgram/gng_phrase.cpp
SOURCES += src/GNG/GNGNgram/gng_phrase_word.cpp
SOURCES += src/GNG/gng_config.cpp
SOURCES += src/utl/utilities.cpp

# main window
SOURCES += src/view/mainwindow.cpp
# has 4 tabs
SOURCES += src/view/ngram_tab/ngram_tab.cpp
SOURCES += src/view/one_gram_tab/one_gram_tab.cpp
SOURCES += src/view/phrase_unique_words_tab/phrase_unique_words_tab.cpp
SOURCES += src/view/widgets/lp_phrase_commands/lp_phrase_commands.cpp
SOURCES += src/view/widgets/mainword_commands.cpp
SOURCES += src/view/widgets/ngram_mv/ngram_filtermodel.cpp
SOURCES += src/view/widgets/ngram_mv/ngram_model.cpp
SOURCES += src/view/widgets/ngram_mv/ngram_model_view_widget.cpp
SOURCES += src/view/widgets/one_gram_word_mv/1_gram_filtermodel.cpp
SOURCES += src/view/widgets/one_gram_word_mv/1_grams_model.cpp
SOURCES += src/view/widgets/one_gram_word_mv/one_gram_model_view_widget.cpp
SOURCES += src/view/widgets/phrase_commandsform.cpp
SOURCES += src/view/widgets/phrase_unique_word_mv/phrase_unique_word_modelview_widget.cpp
SOURCES += src/view/widgets/phrase_unique_word_mv/phrase_unique_words_filtermodel.cpp
SOURCES += src/view/widgets/phrase_unique_word_mv/phrase_unique_words_model.cpp
SOURCES += src/view/widgets/rune_cut_selector.cpp
SOURCES += src/view/widgets/rune_selector.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += src/GNG/GNG1grams/gng_1gram_data.h  \
    src/GNG/GNGNgram/gng_phrase_worker.h \
    src/utl/gematria.h \
    src/view/phrase_1grams_tab/phrase_1grams_tab.h \
HEADERS += src/GNG/GNGData/gng_data.h 
HEADERS += src/GNG/GNGData/gng_database.h 
HEADERS += src/view/widgets/gng_data_view/gng_data_view.h 
HEADERS += src/view/widgets/gng_data_view/gng_filtermodel.h 
HEADERS += src/view/widgets/gng_data_view/gng_model.h 
HEADERS += src/view/widgets/gng_data_view/gng_tableview.h 
HEADERS += src/view/widgets/rune_spinbox.h
HEADERS += src/view/widgets/spoiler.h
HEADERS += src/GNG/GNG1grams/gng_1grams.h
HEADERS += src/GNG/GNGNgram/gng_ngram.h
HEADERS += src/GNG/GNGNgram/gng_phrase.h
HEADERS += src/GNG/GNGNgram/gng_phrase_word.h
HEADERS += src/GNG/gng_config.h
HEADERS += src/utl/utilities.h


# generic tableview
# main window
HEADERS += src/view/mainwindow.h

# has 4 tabs
# TODO lp phrase picker
HEADERS += src/view/lp_phrase_picker_tab/lp_phrase_picker_tab.h
SOURCES += src/view/lp_phrase_picker_tab/lp_phrase_picker_tab.cpp
HEADERS += src/view/widgets/lp_phrase_picker_mv/lp_phrasepicker_filtermodel.h
SOURCES += src/view/widgets/lp_phrase_picker_mv/lp_phrasepicker_filtermodel.cpp
HEADERS += src/view/widgets/lp_phrase_picker_mv/lp_phrasepicker_model.h
SOURCES += src/view/widgets/lp_phrase_picker_mv/lp_phrasepicker_model.cpp
HEADERS += src/view/widgets/lp_phrase_picker_mv/lp_phrasepicker_tableview.h
SOURCES += src/view/widgets/lp_phrase_picker_mv/lp_phrasepicker_tableview.cpp
# 1 gram
HEADERS += src/view/phrase_1grams_tab/phrase_1grams_tab.h

# 1 gram
HEADERS += src/view/one_gram_tab/one_gram_tab.h
HEADERS += src/view/widgets/one_gram_word_mv/1_gram_filtermodel.h
HEADERS += src/view/widgets/one_gram_word_mv/1_grams_model.h
HEADERS += src/view/widgets/one_gram_word_mv/one_gram_model_view_widget.h

# puw tableview
HEADERS += src/view/ngram_tab/ngram_tab.h
HEADERS += src/view/widgets/ngram_mv/ngram_filtermodel.h
HEADERS += src/view/widgets/ngram_mv/ngram_model.h
HEADERS += src/view/widgets/ngram_mv/ngram_model_view_widget.h

# puw tableview
HEADERS += src/view/phrase_unique_words_tab/phrase_unique_words_tab.h
HEADERS += src/view/widgets/phrase_unique_word_mv/phrase_unique_word_modelview_widget.h
HEADERS += src/view/widgets/phrase_unique_word_mv/phrase_unique_words_filtermodel.h
HEADERS += src/view/widgets/phrase_unique_word_mv/phrase_unique_words_model.h

HEADERS += src/view/widgets/lp_phrase_commands.h
HEADERS += src/view/widgets/lp_phrase_commands/lp_phrase_commands.h
HEADERS += src/view/widgets/mainword_commands.h

HEADERS += src/view/widgets/phrase_commandsform.h
HEADERS += src/view/widgets/rune_cut_selector.h
HEADERS += src/view/widgets/rune_selector.h

DISTFILES += config.txt \
    new_config.txt \
    notes.txt

FORMS += src/view/mainwindow.ui \
    src/view/phrase_1grams_tab/phrase_1grams_tab.ui
FORMS += src/view/lp_phrase_picker_tab/lp_phrase_picker_tab.ui
FORMS += src/view/one_gram_tab/one_gram_tab.ui
FORMS += src/view/ngram_tab/ngram_tab.ui
FORMS += src/view/phrase_unique_words_tab/phrase_unique_words_tab.ui
FORMS += src/view/widgets/lp_phrase_commands/lp_phrase_commands.ui
FORMS += src/view/widgets/one_gram_word_mv/one_gram_model_view_widget.ui
FORMS += src/view/widgets/ngram_mv/ngram_model_view_widget.ui
FORMS += src/view/widgets/phrase_unique_word_mv/phrase_unique_word_modelview_widget.ui
FORMS += src/view/widgets/phrase_commandsform.ui
FORMS += src/view/widgets/rune_cut_selector.ui
FORMS += src/view/widgets/rune_selector.ui
