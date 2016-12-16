#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton5_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();
    void on_pushButton0_clicked();
    void on_pushButtonA_clicked();
    void on_pushButtonB_clicked();
    void on_pushButtonC_clicked();
    void on_pushButtonD_clicked();
    void on_pushButtonE_clicked();
    void on_pushButtonF_clicked();
    void on_pushButtonLeftBracket_clicked();
    void on_pushButtonRightBracket_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonErase_clicked();
    void on_pushButtonCE_clicked();
    void on_pushButtonPlusMinus_clicked();
    void on_pushButtonMod_clicked();
    void on_pushButtonPlus_clicked();
    void on_pushButtonMinus_clicked();
    void on_pushButtonMultip_clicked();
    void on_pushButtonDiv_clicked();
    void on_pushButtonAnd_clicked();
    void on_pushButtonNot_clicked();
    void on_pushButtonOr_clicked();
    void on_pushButtonXOr_clicked();
    void on_pushButtonRoL_clicked();
    void on_pushButtonRoR_clicked();
    void on_pushButtonLSh_clicked();
    void on_pushButtonRSh_clicked();
    void on_radioButtonQWord_clicked();
    void on_radioButtonDWord_clicked();
    void on_radioButtonWord_clicked();
    void on_radioButtonByte_clicked();
    void on_radioButtonBin_clicked();
    void on_radioButtonOct_clicked();
    void on_radioButtonDec_clicked();
    void on_radioButtonHex_clicked();
    void on_pushButtonCalculate_clicked();
    void on_pushButtonMS_clicked();
    void on_pushButtonMC_clicked();
    void on_pushButtonMPlus_clicked();
    void on_pushButtonMMinus_clicked();
    void on_pushButtonFromMemoryToCalculator_clicked();

private:
    Ui::MainWindow *m_pUI;
    Calc m_calc;
    void initGUI();
    void updateDisplays(void);
    void setBinButtons(void);
    void setOctButtons(void);
    void setDecButtons(void);
    void setHexButtons(void);
    void updateMemoryValues(void);
};

#endif // MAINWINDOW_H
