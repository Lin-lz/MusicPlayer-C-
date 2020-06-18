#include "musicplayer.h"
#include "ui_musicplayer.h"

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    QString curPath=QDir::currentPath();

    initWidget();
    initConnectList();

    this->setMinimumSize(800, 600);

    //  backgroung_picture
    //QPixmap bgImage("/pictures/background.jpg");
    QPixmap bgImage(":/pictures/background.jpg");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImage);
    this->setPalette(bgPalette);

    // 应用图标
    this->setWindowIcon(QIcon(":/pictures/musical.png"));

    ui->setupUi(this);
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

// 初始化函数
void MusicPlayer::initWidget()
{
    // 初始化树形控件
    musicTree = new QTreeWidget;
    musicTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    musicTree->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    musicTree->setHeaderLabels(QStringList()<<QStringLiteral("歌手")<<QStringLiteral("歌名")<<QStringLiteral("位置"));
    musicTree->setContextMenuPolicy(Qt::CustomContextMenu);
    // 透明背景
    musicTree->setStyleSheet("QTreeWidget {background-color: transparent;}");
    //musicTree->setStyleSheet("QTreeWidget {font-color: white;}");
    // 隐藏表头
    //musicTree->setHeaderHidden(2);
    // 隐藏第2列(位置)
    musicTree->hideColumn(2);
    // 自适应列宽
    //musicTree->setSectionResizeMode(QHeaderView::ResizeToContents);

    //获取系统当前目录
    //QString curPath=QDir::currentPath();

    // 几个按钮
    btn_Open = new QPushButton;
    //btn_Open->setText("添加音乐");
    btn_Open->setFixedSize(64,64);
    // 图标自适应按钮大小
    btn_Open->setStyleSheet("QPushButton{border-image: url(:/pictures/open_file.ico)}");
    //btn_Open->setIcon(QIcon(":/pictures/open_file.ico"));

    btn_Next = new QPushButton;
    //btn_Next->setText("下一首");
    btn_Next->setFixedSize(64,64);
    btn_Next->setStyleSheet("QPushButton{border-image: url(:/pictures/next.ico)}");
    //btn_Next->setIcon(QIcon(":/pictures/next.ico"));

    btn_Pre = new QPushButton;
    //btn_Pre->setText("上一首");
    btn_Pre->setFixedSize(64,64);
    btn_Pre->setStyleSheet("QPushButton{border-image: url(:/pictures/previous.ico)}");
    //btn_Pre->setIcon(QIcon(":/pictures/previous.ico"));

    btn_Mid = new QPushButton;
    //btn_Mid->setText("播放");
    btn_Mid->setFixedSize(64,64);
    btn_Mid->setStyleSheet("QPushButton{border-image: url(:/pictures/play.ico)}");
    //btn_Mid->setIcon(QIcon(":/pictures/play.ico"));

    Logo = new QLabel(QString("Copyright© 1701 - 10号 - 林亮钊"));
    Logo->setStyleSheet("color:white");  //设置字体颜色为白色

    QTime mov(0,0,0);
    label_time = new QLabel();                      // 显示总时间
    label_time->setStyleSheet("color:white");       //设置字体颜色为白色
    label_time->setText(mov.toString("mm:ss"));
    label_time1 = new QLabel();                     // 显示进度时间
    label_time1->setText(mov.toString("mm:ss"));
    label_time1->setStyleSheet("color:white");      //设置字体颜色为白色

    btn_volume = new QPushButton;                   // 静音按钮
    btn_volume->setFixedSize(36,36);
    btn_volume->setStyleSheet("QPushButton{border-image: url(:/pictures/volume.png)}");
    label_volumeup = new QLabel();
    label_volumeup->setFixedSize(36,36);
    label_volumeup->setStyleSheet("QLabel{border-image: url(:/pictures/volume_up.png)}");

    // 两个滑块
    slider_Music = new QSlider;
    slider_Music->setOrientation(Qt::Horizontal);
    slider_Music->setFixedWidth(450);
    //slider_Music->setStyleSheet("QSlider{border-image: url(:/pictures/dancer_with_music.png)}");

    slider_Sound = new QSlider;
    slider_Sound->setOrientation(Qt::Horizontal);
    //slider_Sound->setStyleSheet("QSlider{border-image: url(:/pictures/slide.png)}");
    slider_Sound->setRange(0,100);
    slider_Sound->setFixedWidth(200);
    slider_Sound->setValue(20);

    // 简单布局
    QVBoxLayout *vLayout = new QVBoxLayout(this);           // 总体 (垂直布局)
    QHBoxLayout *hbtnLayout = new QHBoxLayout;              // 按键 (水平布局)
    QHBoxLayout *h1Layout = new QHBoxLayout;                // 表
    QHBoxLayout *hmusicLayout = new QHBoxLayout;            // 音乐进度条
    QHBoxLayout *hlabelLayout = new QHBoxLayout;            // 信息
    QHBoxLayout *volumeLayout = new QHBoxLayout;            // 音量条 + 图标
    QSpacerItem *hSpacer  = new QSpacerItem(50, 1);
    QSpacerItem *hSpacer2 = new QSpacerItem(100,1);
    QSpacerItem *hSpacer3 = new QSpacerItem(250,1);

    // 按键
    hbtnLayout->addWidget(btn_Open);
    hbtnLayout->addSpacerItem(hSpacer);
    hbtnLayout->addWidget(btn_Pre);
    hbtnLayout->addSpacerItem(hSpacer);
    hbtnLayout->addWidget(btn_Mid);
    hbtnLayout->addSpacerItem(hSpacer);
    hbtnLayout->addWidget(btn_Next);

    // 音量 + 图标
    volumeLayout->addSpacerItem(hSpacer3);
    volumeLayout->addWidget(btn_volume);                    // 静音键
    volumeLayout->addSpacerItem(hSpacer);
    volumeLayout->addWidget(slider_Sound,0,Qt::AlignCenter);
    volumeLayout->addSpacerItem(hSpacer);
    volumeLayout->addWidget(label_volumeup);
    volumeLayout->addSpacerItem(hSpacer3);

    // 树
    h1Layout->addWidget(musicTree);
    //h1Layout->addWidget(sliderSound);

    // 音乐进度条 + 时间
    hmusicLayout->addSpacerItem(hSpacer2);
    hmusicLayout->addWidget(label_time1);
    //hmusicLayout->addSpacerItem(hSpacer);             // 增加间距
    hmusicLayout->addWidget(slider_Music,0,Qt::AlignCenter);
    //hmusicLayout->addSpacerItem(hSpacer);
    hmusicLayout->addWidget(label_time);                // 音乐时间
    hmusicLayout->addSpacerItem(hSpacer2);

    // 信息
    hlabelLayout->addWidget(Logo,0,Qt::AlignCenter);

    // 总体布局
    vLayout->addLayout(h1Layout);                   // 树
    vLayout->addLayout(hmusicLayout);               // 音乐进度条
    vLayout->addLayout(hbtnLayout);                 // 按钮
    vLayout->addLayout(volumeLayout);               // 音量条 + 图标
    vLayout->addLayout(hlabelLayout);               // 信息


    // 其它的
    Player = new QMediaPlayer;                      // 初始化音乐播放器
    Player->setVolume(slider_Sound->value());
    PlayerList = new QMediaPlaylist;                // 初始化播放列表
    Player->setPlaylist(PlayerList);

    musicList = new QVector<QString>;               // 向量容器(显示动态数组)
    curMusic = new QTreeWidgetItem;                 // 列表成员
    curMusicColumn = -1;                            // 播放列表行数
}

// 建立信号槽
void MusicPlayer::initConnectList()
{
    connect(btn_Open, SIGNAL(clicked()), this, SLOT(openFIle()));
    connect(btn_Next, SIGNAL(clicked()), this, SLOT(startNext()));
    connect(btn_Pre, SIGNAL(clicked()), this, SLOT(startPre()));
    connect(btn_Mid, SIGNAL(clicked()), this, SLOT(startOrStop()));
    connect(btn_volume, SIGNAL(clicked()), this, SLOT(clearVolume()));
    //connect(slider_Music,SIGNAL(valueChanged(int)),this,SLOT(auto_circle_play()));   // 循环播放
    connect(slider_Music,SIGNAL(valueChanged(int)),this,SLOT(auto_next_play()));         // 自动下一首
    connect(slider_Music, SIGNAL(sliderMoved(int)), this, SLOT(setMusicRate(int)));
    connect(slider_Sound, SIGNAL(sliderMoved(int)), this, SLOT(setSoundRate(int)));
    connect(musicTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(musicClicked(QTreeWidgetItem*)));
    connect(Player, SIGNAL(positionChanged(qint64)), this, SLOT(postionChanged(qint64)));
    // 获取音乐时间
    connect(Player,SIGNAL(durationChanged(qint64)),this,SLOT(getduration(qint64)));
}

// 获取音乐时间
void MusicPlayer::getduration(qint64 playtime)
{
    playtime = Player->duration();
    int h,m,s;
    playtime /= 1000;                           //获得的时间是以毫秒为单位的
    h = playtime/3600;                          // hours
    m = (playtime-h*3600)/60;                   // minutes
    s = playtime-h*3600-m*60;                   // seconds
    label_time->setText(QString("%2:%3").arg(m).arg(s));    //把int型转化为string类型后再设置为label的text
    //label_time->setStyleSheet("color:white");             //设置字体颜色为白色
    //label_time->setText(QIn(playtime));
}

// 添加音乐
void MusicPlayer::openFIle()
{
    fileDir = QFileDialog::getOpenFileName(this, "添加歌曲", "../musicplayer", "*.mp3");
    // 没有选择文件，则提示
    if(fileDir.isEmpty())
    {
        QMessageBox::information(nullptr, "提示", "未添加新歌曲");
    }
    // 选择了文件，则更新树
    else
    {
        // 如果列表中无此歌曲，则添加
        if(std::find(musicList->begin(), musicList->end(), fileDir) == musicList->end())
        {
            // QUrl读取的是本地绝对路径

            QMediaPlayer *addMusicItem = new QMediaPlayer;
            addMusicItem->setMedia(QMediaContent(QUrl::fromLocalFile(fileDir)));
            musicList->push_back(fileDir);
            // new add
            // 设置播放模式
            //顺序播放
            //PlayerList->setPlaybackMode(QMediaPlaylist::Loop);
            //单曲循环
            //PlayerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
            //随机播放
            //PlayerList->setPlaybackMode(QMediaPlaylist::Random);

            PlayerList->addMedia(QUrl::fromLocalFile(fileDir));
            //m_mPlayerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);


            //Player->setPlaylist(PlayerList);

            updataTree(addMusicItem);
            QMessageBox::information(nullptr, "提示", "歌曲添加成功");
        }
        else
        {
            QMessageBox::information(nullptr, "提示", "歌曲已存在");
        }
    }
}

// 提取歌名，歌手
//void MusicPlayer::singer_name()
//{
    //char *total,target;

    //QString s = fileDir;
    //total[] = s.split("^[a-zA-Z]:\/\.*/(.*?)\.mp3");
    //target = total[1];
//}

// 更新树
void MusicPlayer::updataTree(QMediaPlayer *addMusicItem)
{

    //获取歌手，歌名
    QStringList total = fileDir.split("/");
    QString target = total[5];
    QStringList singer_name = target.split("-");
    QString singer = singer_name[0];
    QString name = singer_name[1].replace(".mp3","");


    // 然后将文件信息丢入树
    QStringList addMusicItemInfo;

    addMusicItemInfo.append(singer);
    addMusicItemInfo.append(name);
    //addMusicItemInfo.append(album);

    addMusicItemInfo.append(fileDir);

    musicTree->addTopLevelItem(new QTreeWidgetItem(musicTree, addMusicItemInfo));

}

// 点击下一首
void MusicPlayer::startNext()
{
    if(!(musicTree->itemBelow(curMusic)))
    {
        QMessageBox::information(nullptr,"提示", "已经是最后一首了");
    }
    else
    {
        curMusic = musicTree->itemBelow(curMusic);
        startPlay();
        QString s = curMusic->text(2);
        QStringList total = s.split("/");
        QString target = total[5];
        QString name = target.replace(".mp3","");
        this -> setWindowTitle("MusicPlayer( " + name + " 正在播放 )");      // 设置窗口标题
    }
}

// 点击上一首
void MusicPlayer::startPre()
{
    if(!(musicTree->itemAbove(curMusic)))
    {
        QMessageBox::information(nullptr, "提示", "已经是第一首了");
    }
    else
    {
        curMusic = musicTree->itemAbove(curMusic);
        startPlay();
        // 获取歌手歌名并设置窗口标题
        QString s = curMusic->text(2);
        QStringList total = s.split("/");
        QString target = total[5];
        QString name = target.replace(".mp3","");
        this -> setWindowTitle("MusicPlayer( " + name + " 正在播放 )");      // 设置窗口标题
    }
}

// 自动循环播放
void MusicPlayer::auto_circle_play()
{
    if(slider_Music->value() == slider_Music->maximum())
    {
        startPlay();
    }
}

// 自动跳转下一首播放
void MusicPlayer::auto_next_play()
{
    if(slider_Music->value() == slider_Music->maximum())
    {
        startNext();
    }
}

// 播放/暂停按钮被点击
void MusicPlayer::startOrStop()
{
    if(!musicList->size())
    {
        QMessageBox::information(nullptr, "提示", "请先添加音乐");
        return;
    }

    if(Player->state() == QMediaPlayer::PlayingState)
    {
        Player->pause();

        //btn_Mid->setText("播放");
        //btn_Mid->setIcon(QIcon(":/pictures/play.ico"));
        btn_Mid->setStyleSheet("QPushButton{border-image: url(:/pictures/play.ico)}");
        this -> setWindowTitle("MusicPlayer");      // 设置窗口标题
    }
    else
    {
        Player->play();
        //btn_Mid->setText("暂停");
        //btn_Mid->setIcon(QIcon(":/pictures/pause.ico"));
        btn_Mid->setStyleSheet("QPushButton{border-image: url(:/pictures/pause.ico)}");
        // 获取歌手歌名并设置窗口标题
        QString s = curMusic->text(2);
        QStringList total = s.split("/");
        QString target = total[5];
        QString name = target.replace(".mp3","");
        this -> setWindowTitle("MusicPlayer( " + name + " 正在播放 )");      // 设置窗口标题
    }
}

// 开始播放
void MusicPlayer::startPlay()
{
    Player->setMedia(QUrl::fromLocalFile(curMusic->text(2)));   // 路径
    //Player->setMedia(QUrl::fromLocalFile(fileDir));           //testing
    Player->play();

    // 获取歌手歌名
    QString s = curMusic->text(2);
    QStringList total = s.split("/");
    QString target = total[5];
    QString name = target.replace(".mp3","");
    this -> setWindowTitle("MusicPlayer( " + name + " 正在播放 )");      // 设置窗口标题

    //btn_Mid->setText("暂停");
    //btn_Mid->setIcon(QIcon(":/pictures/pause.ico"));
    btn_Mid->setStyleSheet("QPushButton{border-image: url(:/pictures/pause.ico)}");
    musicTree->setCurrentItem(curMusic);
}

// 播放或暂停
void MusicPlayer::musicClicked(QTreeWidgetItem *curItem)
{
    curMusic = curItem;
    startPlay();
}

// 播放进度条滑动
void MusicPlayer::setMusicRate(int value)
{
    int moved;
    Player -> setPosition(value * 1000);                            //如果滑块改变位置，则改变音乐进度
    moved = value * 1000;                                           //让播放时间等于音乐进度（毫秒）
    QTime moveTime(0,(moved/60000) % 60,(moved / 1000) % 60);       //设置时间
    label_time1->setText(moveTime.toString("mm:ss"));               //显示时间
}


// 播放条跟随音乐滑动
void MusicPlayer::postionChanged(qint64 value)
{
    slider_Music->setMaximum(Player->duration() / 1000);            //设置滑块的长度范围为音乐长.00度
    slider_Music->setValue(value / 1000);                           //如果音乐进度改变，则改变滑块显示位置
    QTime moveTime(0,(value/60000) % 60,(value / 1000) % 60);       //设置时间
    label_time1->setText(moveTime.toString("mm:ss"));               //显示时间
}

// 音量条滑动
void MusicPlayer::setSoundRate(int value)
{
    Player->setVolume(value);
}

// 静音
void MusicPlayer::clearVolume()
{
    if(btn_volume_state == true)
    {
        Player->setVolume(0);
        btn_volume_state=false;
        btn_volume->setStyleSheet("QPushButton{border-image: url(:/pictures/volume_mute.png)}");
    }
    else
    {
        btn_volume_state=true;
        Player->setVolume(slider_Sound->value());
        btn_volume->setStyleSheet("QPushButton{border-image: url(:/pictures/volume.png)}");
    }
}

