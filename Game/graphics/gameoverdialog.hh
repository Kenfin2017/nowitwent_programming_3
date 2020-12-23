#ifndef GAMEOVERDIALOG_HH
#define GAMEOVERDIALOG_HH

#include <QDialog>

namespace Ui {
class GameOverDialog;
}
namespace StudentSide {
class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDialog(QWidget *parent = nullptr, unsigned int playerScore = 0, QString playerName = "Anonymous");
    ~GameOverDialog();
    void setPlayerName(QString playerName);
    void setPlayerScore(unsigned int playerScore);
private slots:
    void on_exit_btn_clicked();

signals:
    void gameRetry();

    void gameExit();

private:
    Ui::GameOverDialog *ui;
    unsigned int playerScore_;
    QString playerName_;
};
}
#endif // GAMEOVERDIALOG_HH
