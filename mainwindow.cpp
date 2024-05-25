#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->currentPlayerSymbolLabel->setText(QString(currentPlayer)); // Display the current player's symbol

    // Connect all buttons to the onGameButtonClicked slot using a loop
    for (int i = 1; i <= 9; ++i) {
        QPushButton *button = findChild<QPushButton*>(QString("pushButton_%1").arg(i));
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::onGameButtonClicked);
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

// Slot function called when a game button is clicked
void MainWindow::onGameButtonClicked() {
    // Get the button that was clicked
    // `sender()` gets the object that triggered this function, which should be a button
    // `qobject_cast<QPushButton*>` makes sure the object is a button
    // This allows us to safely use button-specific functions
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (button && button->text().isEmpty()) { // Check if the button hasn't already been clicked
        button->setText(QString(currentPlayer)); // Set the text to the current player's symbol

        if (checkWinCondition()) { // Check if the current move wins the game
            ui->label_3->setText(QString("Player %1 wins!").arg(currentPlayer)); // Display winner message
            disableButtons(); // Disable all buttons to stop further clicks
            return; // Stop further playing
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Change the current player
        ui->currentPlayerSymbolLabel->setText(QString(currentPlayer)); // Update the current player label
    }
}


// Function to check if there's a winning condition on the board
bool MainWindow::checkWinCondition() {
    // Check all rows for a win
    for (int i = 1; i <= 7; i += 3) {
        if (!findChild<QPushButton*>(QString("pushButton_%1").arg(i))->text().isEmpty() &&
            findChild<QPushButton*>(QString("pushButton_%1").arg(i))->text() == findChild<QPushButton*>(QString("pushButton_%1").arg(i+1))->text() &&
            findChild<QPushButton*>(QString("pushButton_%1").arg(i+1))->text() == findChild<QPushButton*>(QString("pushButton_%1").arg(i+2))->text()) {
            return true;  // Row win
        }
    }

    // Check all columns for a win
    for (int i = 1; i <= 3; ++i) {
        if (!findChild<QPushButton*>(QString("pushButton_%1").arg(i))->text().isEmpty() &&
            findChild<QPushButton*>(QString("pushButton_%1").arg(i))->text() == findChild<QPushButton*>(QString("pushButton_%1").arg(i+3))->text() &&
            findChild<QPushButton*>(QString("pushButton_%1").arg(i+3))->text() == findChild<QPushButton*>(QString("pushButton_%1").arg(i+6))->text()) {
            return true;  // Column win
        }
    }

    // Check main diagonal for a win
    if (!findChild<QPushButton*>("pushButton_1")->text().isEmpty() &&
        findChild<QPushButton*>("pushButton_1")->text() == findChild<QPushButton*>("pushButton_5")->text() &&
        findChild<QPushButton*>("pushButton_5")->text() == findChild<QPushButton*>("pushButton_9")->text()) {
        return true;  // Main diagonal win
    }

    // Check anti-diagonal for a win
    if (!findChild<QPushButton*>("pushButton_3")->text().isEmpty() &&
        findChild<QPushButton*>("pushButton_3")->text() == findChild<QPushButton*>("pushButton_5")->text() &&
        findChild<QPushButton*>("pushButton_5")->text() == findChild<QPushButton*>("pushButton_7")->text()) {
        return true;  // Anti-diagonal win
    }

    return false;  // No win found
}

// Function to disable all buttons after a win
void MainWindow::disableButtons() {
    for (int i = 1; i <= 9; ++i) {
        QPushButton *button = findChild<QPushButton*>(QString("pushButton_%1").arg(i));
        if (button) {
            button->setDisabled(true); // Disable the button to stop further clicks
        }
    }
}
