#ifndef GAMEDIALOG_HH
#define GAMEDIALOG_HH

#include <QDialog>
#include <QDebug>
#include <QLineEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QString>
#include <QGraphicsScene>
#include <QSpinBox>

namespace Ui {
class GameDialog;
}

namespace StudentSide{

const QString BUS_BACKGROUND_IMAGE = ":/images/offlinedata/bus_animated_red.png";
class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(QWidget *parent = nullptr);
    ~GameDialog();

    /**
     * @brief getPlayerName
     * @return value of playerName field
     */
    QString getPlayerName() const;

    /**
     * @brief getSize
     * @return value of mapSize_combobox selected option
     */
    QString getSize() const;

    /**
     * @brief getScoreLimit
     * @return value of scoreLimit_spinbox
     */
    unsigned int getScoreLimit() const;

private slots:
    void playerName_editingFinished();

    void on_mapSize_comboBox_currentIndexChanged(int index);

    void on_playerName_lineEdit_textChanged(const QString &arg1);

    void on_scoreLimit_spinBox_valueChanged(int arg1);

private:
    QGraphicsScene* background;
    Ui::GameDialog *ui;
    QString playerName;
    QString mapSize;
    unsigned int scoreLimit;
    QImage* image;
};
}
#endif // GAMEDIALOG_HH

