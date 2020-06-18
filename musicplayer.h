#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QDialog>
#include <QString>
#include <QTreeWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
#include <QBitmap>
#include <QTimer>
#include <QTime>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <QDebug>


using namespace std;

namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer();

private slots:
    void openFIle();                                // 选择音频
    void startNext();                               // 点击下一首
    void startPre();                                // 点击上一首
    void startOrStop();                             // 点击播放/暂停
    void musicClicked(QTreeWidgetItem *curItem);    // 鼠标点击列表音乐
    void setMusicRate(int value);                   // 音乐进度条拉动
    void setSoundRate(int value);                   // 音量条拉动
    void getduration(qint64 playtime);              // 获取音频时间
    void updataTree(QMediaPlayer *addMusicItem);    // 更新树数据
    void postionChanged(qint64 value);              // 同步音乐和进度条
    void clearVolume();                             // 静音
    void auto_circle_play();                        // 单曲循环播放
    void auto_next_play();                          // 自动下一首播放
private:
    void initWidget();                              // 初始化函数
    void initConnectList();                         // 建立信号槽
    void startPlay();                               // 开始播放


    // 使用到的控件
    QTreeWidget *musicTree;
    QPushButton *btn_Open;
    QPushButton *btn_Faster;
    QPushButton *btn_Slower;
    QPushButton *btn_Next;
    QPushButton *btn_Pre;
    QPushButton *btn_Mid;
    QPushButton *btn_volume;
    QSlider *slider_Music;
    QSlider *slider_Sound;
    QLabel *Logo;
    QLabel *label_time;
    QLabel *label_time1;
    QLabel *label_volumedown;
    QLabel *label_volumeup;
    QLabel *lab;
    QTime *mov;

    // 其它一些成员变量
    Ui::MusicPlayer *ui;
    QMediaPlayer *Player;                   // 界面
    QString fileDir;                        // 音频路径
    QVector<QString> *musicList;            // 向量容器
    QMediaPlaylist *PlayerList;             // 播放列表
    QTreeWidgetItem *curMusic;              // 列表成员
    int curMusicColumn;                     // 播放列表行数
    bool btn_volume_state = true;           // 静音按钮状态


/*
private:
    Ui::MusicPlayer *ui;
*/
};

#endif // MUSICPLAYER_H
