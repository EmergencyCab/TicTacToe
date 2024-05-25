#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGameButtonClicked(); // Handles all game button clicks

private:
    Ui::MainWindow *ui;
    char currentPlayer = 'X'; // Initialize current player to 'X'
    bool checkWinCondition(); // Function to check for a win
    void disableButtons();    // Function to disable all buttons
    void resetGame(); //Function to reset the game after one winner
};

#endif // MAINWINDOW_H
