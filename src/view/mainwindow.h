#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QMenu>
#include "lp_phrase_picker_tab.h"
#include "phrase_unique_words_tab.h"
#include "ngram_tab.h"
#include "one_gram_tab.h"
#include "phrase_1grams_tab.h"
#include "gng_1grams.h"
#include "gng_phrase.h"
#include "gng_phrase_worker.h"
#include "gng_config.h"
#include <thread>
#include <QThread>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr,
                        bool test_startup = false);
    ~MainWindow();
    int my_count = 0;
    bool has_phrase;

    //std::thread* worker_thread_old;
    //QThread* worker_thread;
//    static void doNewPhrase(MainWindow& mw);
//    static QList<unsigned int> np_pwl;
//    static bool np_has_phrase_start;
//    static bool np_has_phrase_end;
//    static unsigned int np_ng_length;
//    static GNGPhrase* gng_phrase_ptr;

public slots:

    void on_rationalize_pushButton_clicked();
    void on_loadphrase_pushButton_clicked();
    void on_savephrase_pushButton_clicked();
    void on_newphrase_pushButton_clicked();
    void on_deleteForAllPushButton_clicked();
    void on_canaddngrams_checkBox_toggled();

    void new_phrase_chosen();
    void openProject();
    void saveProject();
    void closeProject();
    void saveAndCloseProject();
    void exitApplication();
    void help();

    void updateGUIForNewPhrase(bool success);

//    void on_doNewPhraseComplete();


signals:
    //void doNewPhraseComplete();

private:
    Ui::MainWindow* ui;
    GNG1Grams gng_words;
    GNGPhrase gng_phrase;
    //GNGPhraseWorker* gng_phrase_worker;
    //GNGPhrase gng_phrase2;
    OneGramTab* one_grams_form;
    NGramTab* ngram_form;
    Phrase1GramsTab* phrase_1grams_form;
    LPPhrasePickerTab* lp_phrase_picker_form;
    PhraseUniqueWordsTab* phrase_unique_words_form;
    GNGConfig config;
    QMenu *fileMenu;
    QMenu *projectsMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *closeAct;
    QAction *saveAndCloseAct;
    QAction *exitAct;
    QAction *helpAct;

    bool loadNewConfig();
    bool loadNewConfig(const QString& start_dir, QString& directory);

    bool setNewPhrase();
    bool setGUIForCurrentPhrase();
    bool loadPhrase();

    void testStartUp();

    bool getDirectory(const QString& start_dir, QString& directory, const QString& message = "")const;
    bool getFileNameAndDir(const QString& start_dir, QString& chosen_dir, QString& chosen_filename)const;
    //bool getFileName(QString& directory)const;
    bool getSaveFileName(const QString& start_dir, QString& path)const;
private:
    void createActions();
    void createMenus();

    void beginAllResetModel();
    void begin1GramResetModel();
    void beginNgramResetModel();
    void beginPUWResetModel();
    void beginP1GResetModel();

    void endAllResetModel();
    void end1GramResetModel();
    void endNgramResetModel();
    void endPUWResetModel();
    void endP1GResetModel();

    void updateAll();
    void update1Gram();
    void updateNgram();
    void updatePUW();
    void updateP1G();

    void allWidgetsEnabled(bool value);

    bool busy;



};
#endif // MAINWINDOW_H
