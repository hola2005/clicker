#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QTime>
#include <QRandomGenerator>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerTimeout);

    clicks = 0;
    counting = false;
    level = 1;

    ui->easyLevelButton->setChecked(true);

    results << 0 << 0;
}
QTime startTime;

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_exitButton_clicked()
{
    QApplication::exit();
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
    counting = false;
    ui->clickButton->move(250, 250);
}

void MainWindow::on_resultsButton_clicked()
{
    QString message = "Highscore Easy: " + QString::number(results[0]) + "\n"
                      "Highscore Medium: " + QString::number(results[1]) + "\n"
                      "Highscore Hard: " + QString::number(results[2]);
    QMessageBox::information(this, "Highscores", message);
}

void MainWindow::on_easyLevelButton_clicked()
{
    level = 1;
    ui->clickButton->setStyleSheet("background-color: green");
    ui->highscoreLabel->setText("Highscore: " + QString::number(results[level - 1]));
}

void MainWindow::on_mediumLevelButton_clicked()
{
    level = 2;
    ui->clickButton->setStyleSheet("background-color: yellow");
    ui->highscoreLabel->setText("Highscore: " + QString::number(results[level - 1]));
}

void MainWindow::on_hardLevelButton_clicked()
{
    level = 3;
    ui->clickButton->setStyleSheet("background-color: red");
    ui->highscoreLabel->setText("Highscore: " + QString::number(results[level - 1]));
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        clicks++;
        ui->clicksLabel->setText("Clicks: " + QString::number(clicks));
    }
}

void MainWindow::on_startButton_clicked()
{
    clicks = 0;
    ui->clicksLabel->setText("Clicks: 0");
    counting = true;
    startTime = QTime::currentTime();
    timer->start(1000);

    if (level == 1) {
        int x = QRandomGenerator::global()->bounded(200, 400);
        int y = QRandomGenerator::global()->bounded(200, 400);
        ui->clickButton->move(x, y);
    } else if (level == 2) {
        int x = QRandomGenerator::global()->bounded(100, 500);
        int y = QRandomGenerator::global()->bounded(100, 500);
        ui->clickButton->move(x, y);
    } else if (level == 3) {
        int x = QRandomGenerator::global()->bounded(0, 600);
        int y = QRandomGenerator::global()->bounded(0, 600);
        ui->clickButton->move(x, y);
    }
}

void MainWindow::timerTimeout()
{

    QTime currentTime = QTime::currentTime();
    int timeElapsed = currentTime.msecsTo(startTime);
    int timeLeft = 10 - timeElapsed / 1000;


    if (timeLeft <= 0) {
        timer->stop();
        counting = false;

        if (clicks > results[level - 1]) {
            results[level - 1] = clicks;
            ui->highscoreLabel->setText("Highscore: " + QString::number(results[level - 1]));
            QMessageBox::information(this, "New Highscore!", "Congratulations, you set a new highscore!");
        }

        ui->clickButton->move(250, 250);
        clicks = 0;
        ui->clicksLabel->setText("Clicks: 0");
        ui->timeLabel->setText("Time left: 10s");
    }
}

void MainWindow::on_easyLevelButton_toggled(bool checked)
{
    if (checked) {
        level = 1;
        ui->clickButton->setStyleSheet("background-color: green");
        ui->highscoreLabel->setText("Highscore: " + QString::number(results[level - 1]));
    }
}

void MainWindow::on_mediumLevelButton_toggled(bool checked)
{
    if (checked) {
        level = 2;
        ui->clickButton->setStyleSheet("background-color: yellow");
        ui->highscoreLabel->setText("Highscore: " + QString::number(results[level - 1]));
    }
}

void MainWindow::on_hardLevelButton_toggled(bool checked)
{
    if (checked) {
        level = 3;
        ui->clickButton->setStyleSheet("background-color: red");
        ui->highscoreLabel->setText("Highscore: " + QString::number(results[level - 1]));
    }
}

