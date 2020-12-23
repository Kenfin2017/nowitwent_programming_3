#include "gamedialog.hh"
#include "ui_gamedialog.h"
namespace StudentSide{
GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);
    playerName = "";
    scoreLimit = 100;
    mapSize = "large";

    background = new QGraphicsScene(this);
    ui->bus_graphicView->setScene(background);
    image = new QImage();
    image->load(BUS_BACKGROUND_IMAGE, "png");
    unsigned int imageWidth = 330;
    image->scaledToWidth(imageWidth,Qt::FastTransformation);
    ui->bus_graphicView->setFixedSize(360,320);
    ui->bus_graphicView->setBackgroundBrush(*image);

    ui->scoreLimit_spinBox->setValue(100);
    connect(ui->playerName_lineEdit, SIGNAL(QLineEdit::editingFinished()), this, SLOT(GameDialog::playerName_editingFinished()));
    connect(ui->mapSize_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int i){on_mapSize_comboBox_currentIndexChanged(i);});
    connect(ui->scoreLimit_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int limit){on_scoreLimit_spinBox_valueChanged(limit);});
    connect(ui->button_dialog, SIGNAL(QDialogButtonBox::accepted()), this, SLOT(GameDialog::accept()));
    connect(ui->button_dialog, SIGNAL(QDialogButtonBox::rejected()), this, SLOT(GameDialog::reject()));
}

GameDialog::~GameDialog()
{
    delete ui;
}

QString GameDialog::getPlayerName() const
{
    return playerName;
}

QString GameDialog::getSize() const
{
    return mapSize;
}

unsigned int GameDialog::getScoreLimit() const
{
    return scoreLimit;
}

void GameDialog::playerName_editingFinished()
{
    playerName = ui->playerName_lineEdit->text();
}

void GameDialog::on_mapSize_comboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0:
        mapSize = "large";
        break;
    case 1:
        mapSize = "small";
        break;
    default:
        break;
    }
}
void GameDialog::on_playerName_lineEdit_textChanged(const QString &arg1)
{
    playerName = arg1;
}

void GameDialog::on_scoreLimit_spinBox_valueChanged(int arg1)
{
    scoreLimit = (unsigned int)arg1;
}

}

