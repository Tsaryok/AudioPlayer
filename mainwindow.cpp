#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    playlistModel = new QStandardItemModel(this);
    ui->playlistView->setModel(playlistModel);

    playlistModel->setHorizontalHeaderLabels(QStringList() << tr("Audio Track") << ("File Path"));
    ui->playlistView->hideColumn(1);
    ui->playlistView->verticalHeader()->setVisible(false);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->resizeColumnsToContents();
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    player->setVolume(50);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setNotifyInterval(1000);

    connect(ui->previousButton, &QPushButton::clicked, playlist, &QMediaPlaylist::previous);
    connect(ui->nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->playButton, &QPushButton::toggled, [this](bool checked){
        if (checked)
            player->play();
        else
            player->pause();
    });

    connect(ui->volumeSlider, &QSlider::valueChanged, [this](int value){
        player->setVolume(value);
    });

    connect(ui->volumeButton, &QPushButton::toggled, [this](bool checked){
        player->setMuted(!checked);
    });

    connect(ui->shuffleButton, &QPushButton::clicked, [this](){
        //playlist->shuffle();
    });

    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
        playlist->setCurrentIndex(index.row());
    });

    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->currentTrack->setText(playlistModel->data(playlistModel->index(index, 0)).toString());

    });

    connect(player, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status){
        if (status == 6){
            int duration = player->duration()/1000;
            int seconds = duration % 60;
            int minuts = duration/60;
            ui->allTrackTime->setText(QString().sprintf("%02d:%02d",minuts,seconds));
            ui->trackTimeSlider->setMaximum(duration);
        }
    });

    connect(player, &QMediaPlayer::positionChanged, [this](qint64 position){
            int seconds = position/1000 % 60;
            int minuts = position/60000;
            ui->currentTrackTime->setText(QString().sprintf("%02d:%02d",minuts,seconds));
            ui->trackTimeSlider->setValue(position/1000);
    });

    connect(ui->trackTimeSlider, &QSlider::sliderMoved, [this](int position){
        player->setPosition(ui->trackTimeSlider->value()*1000);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    delete playlistModel;
    delete player;
    delete playlist;
}

void MainWindow::on_add_action_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString(), tr("Audio Files (*.mp3)"));
    foreach (QString filePath, files){
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        playlistModel->appendRow(items);
        playlist->addMedia(QUrl(filePath));
    }
}
