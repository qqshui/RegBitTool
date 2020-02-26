#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete signalMapper;
    delete hexNumRegExpValidator;
    delete binNumRegExpValidator;
    delete decNumRegExpValidator;
}

void MainWindow::init()
{
    buttonList.append(ui->toolButton_00);
    buttonList.append(ui->toolButton_01);
    buttonList.append(ui->toolButton_02);
    buttonList.append(ui->toolButton_03);
    buttonList.append(ui->toolButton_04);
    buttonList.append(ui->toolButton_05);
    buttonList.append(ui->toolButton_06);
    buttonList.append(ui->toolButton_07);
    buttonList.append(ui->toolButton_08);
    buttonList.append(ui->toolButton_09);
    buttonList.append(ui->toolButton_10);
    buttonList.append(ui->toolButton_011);
    buttonList.append(ui->toolButton_012);
    buttonList.append(ui->toolButton_013);
    buttonList.append(ui->toolButton_014);
    buttonList.append(ui->toolButton_015);
    buttonList.append(ui->toolButton_016);
    buttonList.append(ui->toolButton_017);
    buttonList.append(ui->toolButton_018);
    buttonList.append(ui->toolButton_019);
    buttonList.append(ui->toolButton_020);
    buttonList.append(ui->toolButton_021);
    buttonList.append(ui->toolButton_022);
    buttonList.append(ui->toolButton_023);
    buttonList.append(ui->toolButton_024);

    buttonList.append(ui->toolButton_025);
    buttonList.append(ui->toolButton_026);
    buttonList.append(ui->toolButton_027);
    buttonList.append(ui->toolButton_028);
    buttonList.append(ui->toolButton_029);
    buttonList.append(ui->toolButton_030);
    buttonList.append(ui->toolButton_031);

    for(int i=0;i<32;i++){
        buttonList[i]->setCheckable(true);
    }

    initSignalMap();
    setRegExpValidator();
    regval = 0;
    regvalChangeLocked = false;
    updateUI(regval);

}

void MainWindow::updateUI(int32_t value)
{

    updateBitButton(value);
    updateHexLineEdit(value);
    updateDecLineEdit(value);
    updateBinLineEdit(value);
}

void MainWindow::updateBitButton(int32_t value)
{

    //for bit button
    for(int i=0;i<32;i++){
        if((value >> i) & 0x1){
            buttonList[i]->setChecked(true);
            buttonList[i]->setText("1");
        }else{
            buttonList[i]->setChecked(false);
            buttonList[i]->setText("0");
        }
    }

}

void MainWindow::updateHexLineEdit(int32_t value)
{
    //for hex
    char chBuf[8];
    sprintf(chBuf,"%08x",value);
    QString hex = QString::fromUtf8(chBuf);
    ui->lineEdit_hex->setText(hex);


}

void MainWindow::updateDecLineEdit(int32_t value)
{
    QString dec = QString::number( value );
    ui->lineEdit_dec->setText(dec);
}

void MainWindow::updateBinLineEdit(int32_t value)
{
    //for bin
    QString bin;
    for(int i=0;i<32;i++){
        if((value >> i) & 0x1){
            bin.insert(0,"1");
        }else{
            bin.insert(0,"0");
        }
    }
    //add space per 4 bit
    QString formatbin ;
    for(int i=0;i < 32;i+=4){
        formatbin.append( bin.mid(i,4) );
        formatbin.append(" ");
    }
    formatbin = formatbin.trimmed();

    ui->lineEdit_bin->setText(formatbin);

}



void MainWindow::on_lineEdit_hex_textChanged(const QString &)
{
    if(regvalChangeLocked){
        return;
    }
    bool ok;
    uint uintRegVal = ui->lineEdit_hex->text().toUInt(&ok,16);
    regval = uintRegVal;
    regvalChangeLocked = true;
    updateDecLineEdit(regval);
    updateBinLineEdit(regval);
    updateBitButton(regval);
    regvalChangeLocked = false;
}

void MainWindow::initSignalMap()
{
    signalMapper = new QSignalMapper(this);

    for (int i = 0; i < buttonList.count(); ++i) {
        connect(buttonList[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(buttonList[i], i);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(clickButton(int)));
}


void MainWindow::clickButton(int id){

    int32_t bitmask = 1;

    if(buttonList[id]->isChecked()){
        regval |= (bitmask << id);
    }else{
        regval &= ~(bitmask << id);
    }
    regvalChangeLocked = true;
    updateBitButton(regval);
    updateHexLineEdit(regval);
    updateDecLineEdit(regval);
    updateBinLineEdit(regval);
    regvalChangeLocked = false;
}
void MainWindow::setRegExpValidator(){
    QRegExp regExp("[a-fA-F0-9]{8}");
    hexNumRegExpValidator = new QRegExpValidator(regExp, this);
    ui->lineEdit_hex->setValidator(hexNumRegExpValidator);

    QRegExp binRegExp("[01]{32}");
    binNumRegExpValidator = new QRegExpValidator(binRegExp, this);
    ui->lineEdit_bin->setValidator(binNumRegExpValidator);

    QRegExp decRegExp("[0-9]{32}");
    decNumRegExpValidator = new QRegExpValidator(decRegExp, this);
    ui->lineEdit_dec->setValidator(decNumRegExpValidator);

}



void MainWindow::on_lineEdit_bin_textChanged(const QString &)
{
    if(regvalChangeLocked){
        return;
    }
    QString formatBin = ui->lineEdit_bin->text();
    QString bin;
    for(int i=0;i<formatBin.length();i++){
        if(formatBin.at(i) == QChar('0') || formatBin.at(i) == QChar('1') ){
            bin.append(formatBin.at(i) );
        }
    }
    bool ok;
    regval = bin.toUInt(&ok,2);

    regvalChangeLocked = true;
    updateBitButton(regval);
    updateHexLineEdit(regval);
    updateDecLineEdit(regval);
    regvalChangeLocked = false;
}

void MainWindow::on_lineEdit_dec_textChanged(const QString &)
{
    if(regvalChangeLocked){
        return;
    }
    QString dec = ui->lineEdit_dec->text();

    bool ok;
    regval = dec.toUInt(&ok,10);

    regvalChangeLocked = true;
    updateBitButton(regval);
    updateHexLineEdit(regval);
    updateBinLineEdit(regval);
    regvalChangeLocked = false;
}
