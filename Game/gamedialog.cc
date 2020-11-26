#include "gamedialog.hh"
#include "ui_gamedialog.h"
namespace StudentSide{
GameDialog::GameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameDialog)
{
    ui->setupUi(this);
    playerName = "";
    hardMode = false;
    mapSize = "large";
    ui->normal_option->setChecked(true);
    ui->survival_option->setChecked(false);

    connect(ui->playerName_lineEdit, SIGNAL(QLineEdit::editingFinished()), this, SLOT(GameDialog::playerName_editingFinished()));
    connect(ui->normal_option, SIGNAL(QRadioButton::clicked()), this, SLOT(GameDialog::on_normalMode_clicked()));
    connect(ui->survival_option, SIGNAL(QRadioButton::clicked()), this, SLOT(GameDialog::on_survivalMode_clicked()));
    connect(ui->mapSize_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int i){on_mapSize_comboBox_currentIndexChanged(i);});

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

bool GameDialog::getGameMode() const
{
    return hardMode;
}

QString GameDialog::getSize() const
{
    return mapSize;
}

void GameDialog::playerName_editingFinished()
{
    playerName = ui->playerName_lineEdit->text();
}

void GameDialog::on_normalMode_clicked()
{
    hardMode = false;
}

void GameDialog::on_survivalMode_clicked()
{
    hardMode = true;
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
}
