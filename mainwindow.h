#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_action_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel  *playlistModel;
    QMediaPlayer        *player;
    QMediaPlaylist      *playlist;
};

#endif // MAINWINDOW_H
