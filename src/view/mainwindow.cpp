#include <QLineEdit>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, bool test_startup)
    : QMainWindow(parent)
    , has_phrase(false)
    , ui(new Ui::MainWindow())
    , gng_phrase(GNGPhrase())
//    , gng_phrase_worker(new GNGPhraseWorker(gng_phrase))
    , gng_words(GNG1Grams())
    , one_grams_form(new OneGramTab(this))
    , ngram_form(new NGramTab(this))
    , phrase_1grams_form(new Phrase1GramsTab(this))
    , lp_phrase_picker_form(new LPPhrasePickerTab(this))
    , phrase_unique_words_form(new PhraseUniqueWordsTab(this))
    , config(GNGConfig())
    , fileMenu(nullptr)
    , projectsMenu(nullptr)
    , openAct(nullptr)
    , saveAct(nullptr)
    , closeAct(nullptr)
    , saveAndCloseAct(nullptr)
    , exitAct(nullptr)
    , helpAct(nullptr)
    , busy(false)
{
    ui->setupUi(this);
    setWindowTitle("Google Ngram Cribbing");
    //ui->lpphrasetab_verticalLayout->addWidget(lp_phrase_picker_form);
    ui->oneGramTabLayout->addWidget(one_grams_form);
    ui->lpPhraseTabLayout->addWidget(lp_phrase_picker_form);
    ui->phraseNGramTabLayout->addWidget(ngram_form);
    ui->phraseWordTabLayout->addWidget(phrase_unique_words_form);
    ui->phrase1GramTabLayout->addWidget(phrase_1grams_form);
    ui->newphrase_pushButton->setEnabled(false);
    QObject::connect(lp_phrase_picker_form, &LPPhrasePickerTab::phrase_chosen, this, &MainWindow::new_phrase_chosen);
    //new_phrase_chosen();
    createActions();
    fileMenu = menuBar()->addMenu(tr("&Main"));
    fileMenu->addAction(helpAct);
    fileMenu->addAction(exitAct);
    projectsMenu = menuBar()->addMenu(tr("&More Projects"));
    projectsMenu->addAction(openAct);
    projectsMenu->addAction(saveAct);
    projectsMenu->addAction(closeAct);
    projectsMenu->addAction(saveAndCloseAct);
    //on_newphrase_pushButton_clicked();
    //loadPhrase();
}
void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open: TODO"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an Existing Project"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openProject);
    saveAct = new QAction(tr("&Save: TODO"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save Current Project"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveProject);
    closeAct = new QAction(tr("&Close: TODO"), this);
    closeAct->setShortcuts(QKeySequence::Close);
    closeAct->setStatusTip(tr("Close Current Project"));
    connect(closeAct, &QAction::triggered, this, &MainWindow::closeProject);
    saveAndCloseAct = new QAction(tr("&Save and Close: TODO"), this);
    saveAndCloseAct->setStatusTip(tr("Save and Close Current Project: TODO"));
    connect(saveAndCloseAct, &QAction::triggered, this, &MainWindow::saveAndCloseProject);
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit: TODO"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exitApplication);
    helpAct = new QAction(tr("&Help: For now try tooltips"), this);
    helpAct->setStatusTip(tr("Help!"));
    connect(helpAct, &QAction::triggered, this, &MainWindow::help);
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::openProject(){
    qDebug() << "Open Project: TODO ;) " ;
}
void MainWindow::saveProject(){
    qDebug() << "Save Project: TODO ;) " ;
}
void MainWindow::closeProject(){
    qDebug() << "Close Project: TODO ;) " ;
}
void MainWindow::saveAndCloseProject(){
    qDebug() << "Save and Close Project: TODO ;) " ;
}
void MainWindow::exitApplication(){
    qDebug() << "Exit TODO ;) " ;
    close();
}
void MainWindow::help()
{
    qDebug() << "Help me - common!" ;
}
void MainWindow::testStartUp(){}

void MainWindow::new_phrase_chosen(){
    qDebug() << "MainWindow::new_phrase_chosen()" << lp_phrase_picker_form->phrase_set_success;
    if( lp_phrase_picker_form->phrase_set_success ){
        ui->newphrase_pushButton->setEnabled(true);
    }
    else{
        ui->newphrase_pushButton->setEnabled(false);
    }
}

void MainWindow::on_loadphrase_pushButton_clicked(){
    has_phrase = loadPhrase();
    if(!setGUIForCurrentPhrase()){
        qDebug() <<"!ERROR loading phrase";
    }
}
void MainWindow::on_savephrase_pushButton_clicked(){
    gng_phrase.savePhraseNgrams(false);
    gng_phrase.savePhraseUniqueWords();
}

void MainWindow::on_newphrase_pushButton_clicked(){
    has_phrase = setNewPhrase();
//    if(!setGUIForCurrentPhrase()){
//        qDebug() <<"!ERROR setting new phrase FROM on_newphrase_pushButton_clicked ";
//    }
}
bool MainWindow::setNewPhrase(){
    QString new_dir;
    bool should_continue = getDirectory(config.save_directory, new_dir);
    if( !should_continue ){return false;}
    QDir dir = QDir(new_dir);
    QStringList nameFilters;
    QFileInfoList files =  dir.entryInfoList(nameFilters);
    for(const auto& file : files){
        QFile f = file.filePath();
        f.remove();
    }
    if( !should_continue ){return false;}
    // set local directory in config,
    QDir app_exe_path = QDir(QCoreApplication::applicationDirPath());
    QString new_dir_relative = app_exe_path.relativeFilePath(dir.absolutePath());
    config.setConfigForNewPhrase(new_dir_relative);
    if( !should_continue ){return false;}
    // set new phrase in gng_phrase by setting paramters in gng_phrase_worker
    // then set up new QThread, pass worker to there to do the work
    if(!busy){
        busy = true;
        allWidgetsEnabled(false);
        QThread* worker_thread = new QThread();
        GNGPhraseWorker* gng_phrase_worker = new GNGPhraseWorker(gng_phrase);
        gng_phrase_worker->
                setNewPhraseParameters(lp_phrase_picker_form->phrase_word_lengths,
                                       lp_phrase_picker_form->has_phrase_start,
                                       lp_phrase_picker_form->has_phrase_end,
                                       lp_phrase_picker_form->getNgramLength());
        gng_phrase_worker->moveToThread(worker_thread);
        //connect( worker, &Worker::error, this, &MyClass::errorString);
        connect(worker_thread, &QThread::started, gng_phrase_worker, &GNGPhraseWorker::processNewPhrase);
        connect(gng_phrase_worker, &GNGPhraseWorker::finished, worker_thread, &QThread::quit);
        //connect(gng_phrase_worker, &GNGPhraseWorker::finished, gng_phrase_worker, &GNGPhraseWorker::deleteLater);
        connect(worker_thread, &QThread::finished, worker_thread, &QThread::deleteLater);
        connect(gng_phrase_worker, &GNGPhraseWorker::finished, this, &MainWindow::updateGUIForNewPhrase);
        worker_thread->start();
    }
    return true;
}
void MainWindow::updateGUIForNewPhrase(bool success){
    if(setGUIForCurrentPhrase()){
        qDebug() <<"newPhrase complete";
    }
    else{
        qDebug() <<"!ERROR setting new phrase doNewPhrase";
    }
    allWidgetsEnabled(true);
    busy = false;
}
bool MainWindow::loadPhrase(){
    if(loadNewConfig()){
        return gng_phrase.loadPhrase();
    }
    return false;
}
bool MainWindow::setGUIForCurrentPhrase(){
    if(has_phrase){
        bool puw_form_set_ok = phrase_unique_words_form->setNewPhrase();
        bool ngram_form_set_ok = ngram_form->setNewPhrase();
        bool phrase_1grams_tab_set_ok = phrase_1grams_form->setNewPhrase();
        return puw_form_set_ok && ngram_form_set_ok &&phrase_1grams_tab_set_ok;
    }
    return false;
}


bool MainWindow::loadNewConfig(){
    QString chosen_dir,chosen_filename;
    if(getFileNameAndDir(config.save_directory,
                          chosen_dir,
                          chosen_filename)){
        return loadNewConfig(chosen_dir,chosen_filename);
    }
    return false;
}
bool MainWindow::loadNewConfig(const QString& directory, QString& filename){
    config.config_directory = directory;
    config.config_filename = filename;
    config.parseConfigFile();
    if( config.has_full_config ){
        qDebug() << "New config loaded from" << directory << "," <<filename;
    }else{
        qDebug() << "ERROR loading config from" << directory << "," << filename;
    }
    return config.has_full_config;
}

void MainWindow::on_rationalize_pushButton_clicked(){
    qDebug() << "on_rationalize_pushButton_clicked";
    beginAllResetModel();
    if(!busy){
        busy = true;
        allWidgetsEnabled(false);
        QThread* worker_thread = new QThread();
        GNGPhraseWorker* gng_phrase_worker = new GNGPhraseWorker(gng_phrase);
        gng_phrase_worker->moveToThread(worker_thread);
        //connect( worker, &Worker::error, this, &MyClass::errorString);
        connect(worker_thread, &QThread::started, gng_phrase_worker, &GNGPhraseWorker::processRationlize);
        connect(gng_phrase_worker, &GNGPhraseWorker::finished, worker_thread, &QThread::quit);
        //connect(gng_phrase_worker, &GNGPhraseWorker::finished, gng_phrase_worker, &GNGPhraseWorker::deleteLater);
        connect(worker_thread, &QThread::finished, worker_thread, &QThread::deleteLater);
        connect(gng_phrase_worker, &GNGPhraseWorker::finished, this, &MainWindow::updateGUIForNewPhrase);
        worker_thread->start();
    }
    endAllResetModel();
    updateAll();
}

void MainWindow::on_canaddngrams_checkBox_toggled(){
    gng_phrase.setCanAddNgrams(ui->canaddngrams_checkBox->isChecked());
}
void MainWindow::on_deleteForAllPushButton_clicked(){

}
bool MainWindow::getFileNameAndDir(const QString& start_dir,
                                   QString& chosen_dir, QString& chosen_filename)const
{
    qDebug() << "getDirectory()";
    QFileDialog* fileDlg = new QFileDialog(nullptr,"Choose File",start_dir);
    fileDlg->setFileMode(QFileDialog::AnyFile);
    bool worked = false;
    if (fileDlg->exec()==QDialog::Accepted) {
        QStringList fl = fileDlg->selectedFiles();
        if (!fl.isEmpty()){
            QString fn = fl[0];
            QFileInfo fi(fn);
            chosen_dir = fi.absolutePath();
            chosen_filename = fi.fileName();
            worked = true;
        }
        else{
            worked = false;
        }
    }
    return worked;
}
bool MainWindow::getDirectory(const QString& start_dir, QString& path, const QString& message)const
{
    QString m = "Choose Directory";
    if( message != ""){
        m = message;
    }
    qDebug() << "getDirectory()";
    QFileDialog* fileDlg = new QFileDialog(nullptr, m, start_dir);
    fileDlg->setFileMode(QFileDialog::Directory);
    fileDlg->setViewMode(QFileDialog::List);
    fileDlg->setOption(QFileDialog::ShowDirsOnly);
    fileDlg->setOption(QFileDialog::HideNameFilterDetails);
    bool worked = false;
    if (fileDlg->exec()) {
        QStringList fl = fileDlg->selectedFiles();
        if (!fl.isEmpty()){
            QString fn = fl[0];
            path = QFileInfo(fn).absoluteFilePath();
            worked = true;
        }
        else{
            worked = false;
        }
    }
    return worked;
}
bool MainWindow::getSaveFileName(const QString& start_dir, QString& path)const
{
    qDebug() << "getSaveFileName()";
    QFileDialog* fileDlg = new QFileDialog(nullptr,"Choose Directory");
    fileDlg->setDirectory(start_dir);
    fileDlg->setFileMode(QFileDialog::AnyFile);
    bool worked = false;
    if (fileDlg->exec()==QDialog::Accepted) {
        QStringList fl = fileDlg->selectedFiles();
        if (!fl.isEmpty()){
            QString fn = fl[0];
            path = QFileInfo(fn).absoluteFilePath();
            worked = false;
        }
        else{
            worked = true;
        }
    }
    return worked;
}

void MainWindow::beginAllResetModel(){
    begin1GramResetModel();
    beginNgramResetModel();
    beginPUWResetModel();
    beginP1GResetModel();
}
void MainWindow::begin1GramResetModel(){
    phrase_1grams_form->beginReset();
}
void MainWindow::beginNgramResetModel(){
    ngram_form->beginReset();
}
void MainWindow::beginPUWResetModel(){
    phrase_unique_words_form->beginReset();
}
void MainWindow::beginP1GResetModel(){
    phrase_1grams_form->beginReset();
}

void MainWindow::endAllResetModel(){
    end1GramResetModel();
    endNgramResetModel();
    endPUWResetModel();
    endP1GResetModel();
}
void MainWindow::end1GramResetModel(){
    phrase_1grams_form->endReset();
}
void MainWindow::endNgramResetModel(){
    ngram_form->endReset();
}
void MainWindow::endPUWResetModel(){
    phrase_unique_words_form->endReset();
}
void MainWindow::endP1GResetModel(){
    phrase_1grams_form->endReset();
}
void MainWindow::updateAll(){
    update1Gram();
    updateNgram();
    updatePUW();
    updateP1G();
}
void MainWindow::update1Gram(){
   // one_grams_form->updateWidgets();
}
void MainWindow::updateNgram(){
    ngram_form->updateWidgets();
}
void MainWindow::updatePUW(){
    phrase_unique_words_form->updateWidgets();
}
void MainWindow::updateP1G(){
    phrase_1grams_form->updateWidgets();
}
void MainWindow::allWidgetsEnabled(bool value)
{
    phrase_1grams_form->setEnabled(value);
    phrase_unique_words_form->setEnabled(value);
    ngram_form->setEnabled(value);
    one_grams_form->setEnabled(value);

    ui->rationalize_pushButton->setEnabled(value);
    ui->loadphrase_pushButton->setEnabled(value);
    ui->savephrase_pushButton->setEnabled(value);
    ui->newphrase_pushButton->setEnabled(value);
    ui->canaddngrams_checkBox->setEnabled(value);
    ui->deleteForAllPushButton->setEnabled(value);

}
