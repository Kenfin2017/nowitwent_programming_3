#ifndef GAMEDIALOG_HH
#define GAMEDIALOG_HH

#include <QDialog>
#include <QDebug>
#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QString>

namespace Ui {
class GameDialog;
}

namespace StudentSide{
class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(QWidget *parent = nullptr);
    ~GameDialog();
    QString getPlayerName() const;
    bool getGameMode() const;
    QString getSize() const;

private slots:
    void playerName_editingFinished();

    void on_normalMode_clicked();

    void on_survivalMode_clicked();

    void on_mapSize_comboBox_currentIndexChanged(int index);

private:
    Ui::GameDialog *ui;
    QString playerName;
    QString mapSize;
    bool hardMode;
};
}
#endif // GAMEDIALOG_HH
