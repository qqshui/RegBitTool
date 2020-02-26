#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QSignalMapper>
#include <QRegExpValidator>
#include <QRegExp>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initSignalMap();
private slots:

    void on_lineEdit_hex_textChanged(const QString &);


    void on_lineEdit_bin_textChanged(const QString &);

    void on_lineEdit_dec_textChanged(const QString &);

    void clickButton(int id);

private:
    Ui::MainWindow *ui;
    int32_t regval;
    QVector<QToolButton *> buttonList;
    void init();
    void updateUI(int32_t value);
    void updateBitButton(int32_t value);
    void updateHexLineEdit(int32_t value);
    void updateDecLineEdit(int32_t value);
    void updateBinLineEdit(int32_t value);
    QSignalMapper *signalMapper;
    QRegExpValidator *hexNumRegExpValidator;
    QRegExpValidator *binNumRegExpValidator;
    QRegExpValidator *decNumRegExpValidator;
    void setRegExpValidator();
    bool regvalChangeLocked;

};

#endif // MAINWINDOW_H
