#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calc.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::MainWindow)
{
    m_pUI->setupUi(this);
    initGUI();
}

MainWindow::~MainWindow()
{
    delete m_pUI;
}

void MainWindow::on_pushButton1_clicked()
{
    m_calc.addValue(Calc::eValue::V_ONE);
    updateDisplays();
}

void MainWindow::on_pushButton2_clicked()
{
    m_calc.addValue(Calc::eValue::V_TWO);
    updateDisplays();
}

void MainWindow::on_pushButton3_clicked()
{
    m_calc.addValue(Calc::eValue::V_THREE);
    updateDisplays();
}

void MainWindow::on_pushButton4_clicked()
{
    m_calc.addValue(Calc::eValue::V_FOUR);
    updateDisplays();
}

void MainWindow::on_pushButton5_clicked()
{
    m_calc.addValue(Calc::eValue::V_FIVE);
    updateDisplays();
}

void MainWindow::on_pushButton6_clicked()
{
    m_calc.addValue(Calc::eValue::V_SIX);
    updateDisplays();
}

void MainWindow::on_pushButton7_clicked()
{
    m_calc.addValue(Calc::eValue::V_SEVEN);
    updateDisplays();
}

void MainWindow::on_pushButton8_clicked()
{
    m_calc.addValue(Calc::eValue::V_EIGHT);
    updateDisplays();
}

void MainWindow::on_pushButton9_clicked()
{
    m_calc.addValue(Calc::eValue::V_NINE);
    updateDisplays();
}

void MainWindow::on_pushButton0_clicked()
{
    m_calc.addValue(Calc::eValue::V_ZERO);
    updateDisplays();
}

void MainWindow::on_pushButtonA_clicked()
{
    m_calc.addValue(Calc::eValue::V_A);
    updateDisplays();
}

void MainWindow::on_pushButtonB_clicked()
{
    m_calc.addValue(Calc::eValue::V_B);
    updateDisplays();
}

void MainWindow::on_pushButtonC_clicked()
{
    m_calc.addValue(Calc::eValue::V_C);
    updateDisplays();
}

void MainWindow::on_pushButtonD_clicked()
{
    m_calc.addValue(Calc::eValue::V_D);
    updateDisplays();
}

void MainWindow::on_pushButtonE_clicked()
{
    m_calc.addValue(Calc::eValue::V_E);
    updateDisplays();
}

void MainWindow::on_pushButtonF_clicked()
{
    m_calc.addValue(Calc::eValue::V_F);
    updateDisplays();
}

void MainWindow::on_pushButtonLeftBracket_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_LEFT_BRACKET);
    updateDisplays();
}

void MainWindow::on_pushButtonRightBracket_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_RIGHT_BRACKET);
    updateDisplays();
}

void MainWindow::on_pushButtonCancel_clicked()
{
    m_calc.clearOperationalVectors();
    updateDisplays();
}

void MainWindow::on_pushButtonErase_clicked()
{
    m_calc.eraseLastValue();
    updateDisplays();
}

void MainWindow::on_pushButtonCE_clicked()
{
    m_calc.clearLastNumber();
    updateDisplays();
}

void MainWindow::on_pushButtonPlusMinus_clicked()
{
    m_calc.changeSign();
    updateDisplays();
}

void MainWindow::on_pushButtonMod_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_MOD);
    updateDisplays();
}

void MainWindow::on_pushButtonPlus_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_PLUS);
    updateDisplays();
}

void MainWindow::on_pushButtonMinus_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_MINUS);
    updateDisplays();
}

void MainWindow::on_pushButtonMultip_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_MULTIPLICATION);
    updateDisplays();
}

void MainWindow::on_pushButtonDiv_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_DIVISION);
    updateDisplays();
}

void MainWindow::on_pushButtonAnd_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_AND);
    updateDisplays();
}

void MainWindow::on_pushButtonNot_clicked()
{
    m_calc.calculateNot();
    updateDisplays();
}

void MainWindow::on_pushButtonOr_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_OR);
    updateDisplays();
}

void MainWindow::on_pushButtonXOr_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_XOR);
    updateDisplays();
}

void MainWindow::on_pushButtonRoL_clicked()
{
    m_calc.calculateRoL();
    updateDisplays();
}

void MainWindow::on_pushButtonRoR_clicked()
{
    m_calc.calculateRoR();
    updateDisplays();
}

void MainWindow::on_pushButtonLSh_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_LSH);
    updateDisplays();
}

void MainWindow::on_pushButtonRSh_clicked()
{
    m_calc.addOperation(Calc::eOperation::O_RSH);
    updateDisplays();
}

void MainWindow::on_radioButtonQWord_clicked()
{
    m_calc.changeWordSize(Calc::WS_QWORD);
    updateDisplays();
}

void MainWindow::on_radioButtonDWord_clicked()
{
    m_calc.changeWordSize(Calc::WS_DWORD);
    updateDisplays();
}

void MainWindow::on_radioButtonWord_clicked()
{
    m_calc.changeWordSize(Calc::WS_WORD);
    updateDisplays();
}

void MainWindow::on_radioButtonByte_clicked()
{
    m_calc.changeWordSize(Calc::WS_BYTE);
    updateDisplays();
}

void MainWindow::on_radioButtonBin_clicked()
{
    m_calc.changeNumeralSystem(Calc::NS_BIN);
    updateDisplays();
    setBinButtons();
    updateMemoryValues();
}

void MainWindow::on_radioButtonOct_clicked()
{
    m_calc.changeNumeralSystem(Calc::NS_OCT);
    updateDisplays();
    setOctButtons();
    updateMemoryValues();
}

void MainWindow::on_radioButtonDec_clicked()
{
    m_calc.changeNumeralSystem(Calc::NS_DEC);
    updateDisplays();
    setDecButtons();
    updateMemoryValues();
}

void MainWindow::on_radioButtonHex_clicked()
{
    m_calc.changeNumeralSystem(Calc::NS_HEX);
    updateDisplays();
    setHexButtons();
    updateMemoryValues();
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    m_calc.calculate();
    updateDisplays();
}

void MainWindow::initGUI()
{
    setDecButtons();
    updateDisplays();
}

void MainWindow::updateDisplays()
{
    m_pUI->labelResult->setText(m_calc.getActualDisplay());
    m_pUI->labelBin->setText(m_calc.getDisplay(Calc::NS_BIN));
    m_pUI->labelOct->setText(m_calc.getDisplay(Calc::NS_OCT));
    m_pUI->labelDec->setText(m_calc.getDisplay(Calc::NS_DEC));
    m_pUI->labelHex->setText(m_calc.getDisplay(Calc::NS_HEX));
    m_pUI->labelOperationsList->setText(m_calc.getAllOperations());
}

void MainWindow::setBinButtons(void)
{
    m_pUI->pushButton0->setHidden(false);
    m_pUI->pushButton1->setHidden(false);
    m_pUI->pushButton2->setHidden(true);
    m_pUI->pushButton3->setHidden(true);
    m_pUI->pushButton4->setHidden(true);
    m_pUI->pushButton5->setHidden(true);
    m_pUI->pushButton6->setHidden(true);
    m_pUI->pushButton7->setHidden(true);
    m_pUI->pushButton8->setHidden(true);
    m_pUI->pushButton9->setHidden(true);
    m_pUI->pushButtonA->setHidden(true);
    m_pUI->pushButtonB->setHidden(true);
    m_pUI->pushButtonC->setHidden(true);
    m_pUI->pushButtonD->setHidden(true);
    m_pUI->pushButtonE->setHidden(true);
    m_pUI->pushButtonF->setHidden(true);
}

void MainWindow::setOctButtons(void)
{
    m_pUI->pushButton0->setHidden(false);
    m_pUI->pushButton1->setHidden(false);
    m_pUI->pushButton2->setHidden(false);
    m_pUI->pushButton3->setHidden(false);
    m_pUI->pushButton4->setHidden(false);
    m_pUI->pushButton5->setHidden(false);
    m_pUI->pushButton6->setHidden(false);
    m_pUI->pushButton7->setHidden(false);
    m_pUI->pushButton8->setHidden(true);
    m_pUI->pushButton9->setHidden(true);
    m_pUI->pushButtonA->setHidden(true);
    m_pUI->pushButtonB->setHidden(true);
    m_pUI->pushButtonC->setHidden(true);
    m_pUI->pushButtonD->setHidden(true);
    m_pUI->pushButtonE->setHidden(true);
    m_pUI->pushButtonF->setHidden(true);
}

void MainWindow::setDecButtons(void)
{
    m_pUI->pushButton0->setHidden(false);
    m_pUI->pushButton1->setHidden(false);
    m_pUI->pushButton2->setHidden(false);
    m_pUI->pushButton3->setHidden(false);
    m_pUI->pushButton4->setHidden(false);
    m_pUI->pushButton5->setHidden(false);
    m_pUI->pushButton6->setHidden(false);
    m_pUI->pushButton7->setHidden(false);
    m_pUI->pushButton8->setHidden(false);
    m_pUI->pushButton9->setHidden(false);
    m_pUI->pushButtonA->setHidden(true);
    m_pUI->pushButtonB->setHidden(true);
    m_pUI->pushButtonC->setHidden(true);
    m_pUI->pushButtonD->setHidden(true);
    m_pUI->pushButtonE->setHidden(true);
    m_pUI->pushButtonF->setHidden(true);
}

void MainWindow::setHexButtons(void)
{
    m_pUI->pushButton0->setHidden(false);
    m_pUI->pushButton1->setHidden(false);
    m_pUI->pushButton2->setHidden(false);
    m_pUI->pushButton3->setHidden(false);
    m_pUI->pushButton4->setHidden(false);
    m_pUI->pushButton5->setHidden(false);
    m_pUI->pushButton6->setHidden(false);
    m_pUI->pushButton7->setHidden(false);
    m_pUI->pushButton8->setHidden(false);
    m_pUI->pushButton9->setHidden(false);
    m_pUI->pushButtonA->setHidden(false);
    m_pUI->pushButtonB->setHidden(false);
    m_pUI->pushButtonC->setHidden(false);
    m_pUI->pushButtonD->setHidden(false);
    m_pUI->pushButtonE->setHidden(false);
    m_pUI->pushButtonF->setHidden(false);
}

void MainWindow::updateMemoryValues(void)
{
    m_pUI->listWidgetMemory->clear();
    for(int i=0;i<m_calc.getMemorySize();++i)
    {
        m_pUI->listWidgetMemory->addItem(m_calc.getValueFromMemory(i));
    }
}

void MainWindow::on_pushButtonMS_clicked()
{
    m_calc.addValueToMemory();
    m_pUI->listWidgetMemory->addItem(m_calc.getValueFromMemory(m_calc.getMemorySize()-1));
}

void MainWindow::on_pushButtonMC_clicked()
{
    m_calc.removeValueFromMemory(m_pUI->listWidgetMemory->currentRow());
    qDeleteAll(m_pUI->listWidgetMemory->selectedItems());
}

void MainWindow::on_pushButtonMPlus_clicked()
{
    if(0 < m_pUI->listWidgetMemory->count() && 0 != m_pUI->listWidgetMemory->currentItem())
    {
        m_calc.increaseValueFromMemory(m_pUI->listWidgetMemory->currentRow());
        m_pUI->listWidgetMemory->currentItem()->setText(m_calc.getValueFromMemory(m_pUI->listWidgetMemory->currentRow()));
    }
    else
    {
        qDebug() << "[WRN]MainWindow::on_pushButtonMPlus_clicked: empty list or item was not selected!";
    }
}

void MainWindow::on_pushButtonMMinus_clicked()
{
    if(0 < m_pUI->listWidgetMemory->count() && 0 != m_pUI->listWidgetMemory->currentItem())
    {
        m_calc.decreaseValueFromMemory(m_pUI->listWidgetMemory->currentRow());
        m_pUI->listWidgetMemory->currentItem()->setText(m_calc.getValueFromMemory(m_pUI->listWidgetMemory->currentRow()));
    }
    else
    {
        qDebug() << "[WRN]MainWindow::on_pushButtonMMinus_clicked: empty list or item was not selected!";
    }
}

void MainWindow::on_pushButtonFromMemoryToCalculator_clicked()
{
    if(0 < m_pUI->listWidgetMemory->count() && 0 != m_pUI->listWidgetMemory->currentItem())
    {
        m_calc.copyNumberFromMemory(m_pUI->listWidgetMemory->currentRow());
        updateDisplays();
    }
    else
    {
        qDebug() << "[WRN]MainWindow::on_pushButtonFromMemoryToCalculator_clicked: empty list or item was not selected!";
    }
}
