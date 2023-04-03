#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_easyLevelButton_clicked();
    void on_mediumLevelButton_clicked();
    void on_hardLevelButton_clicked();
    void on_resultsButton_clicked();
    void on_exitButton_clicked();
    void timerTimeout();
    void on_easyLevelButton_toggled(bool checked);
    void on_mediumLevelButton_toggled(bool checked);
    void on_hardLevelButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int clicks;
    bool counting;
    QTime time;
    int level;
    QList<int> results;
};

#endif // MAINWINDOW_H
