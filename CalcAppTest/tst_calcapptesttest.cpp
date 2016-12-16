// done:
// all conversion tests
// started:
// sum
#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <iostream>
#define private public
#include "../CalcApp/calc.h"

class CalcAppTestTest : public QObject
{
    Q_OBJECT

public:
    CalcAppTestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testCaseInitializedValues();

    void testCaseConvertBin_data();
    void testCaseConvertBin();

    void testCaseConvertHex_data();
    void testCaseConvertHex();

    void testCaseConvertOct_data();
    void testCaseConvertOct();

    void testCaseConvertDec_data();
    void testCaseConvertDec();

    void testCaseErase();
    void testCaseChange();
    void testCaseChangeNumeral();

    //operations
    void testCasePlus();
    void testCaseMinus();
    void testCaseDiv();
    void testCaseMult();
    void testCaseMod();
    void testCaseLSH();
    void testCaseRSH();
    void testCaseRoL();
    void testCaseRoR();
    void testCaseOR();
    void testCaseXOR();
    void testCaseAND();
    void testCaseNOT();
    void testCaseChangeSign();

    void testCaseClearOperationalVectors();
    void testCaseClearLastNumber();
    void testCaseGetAllOperations();

    void testCaseChangeBrackets();
    void testCaseBoundaryValues();
    void testCaseBoundaryValuesWord();

    // memory
    void testCaseAddValueToMemory();
    void testCaseRemoveValueFromMemory();
    void testCaseIncreaseValueFromMemory();
    void testCaseDecreaseValueFromMemory();
    void testCaseGetMemorySize();
    void testCaseGetValueFromMemory();

    // numeral systems conversion
    void testCaseQWordToByte();
    void testCaseByteToQWord();
    void testCaseByteToWordSignCheck();
    void testCaseQWordToByteSignCheck();


};



//#include "tst_calcapptesttest.h"
#include <iostream>

using namespace std;

CalcAppTestTest::CalcAppTestTest()
{
}

void CalcAppTestTest::initTestCase()
{
}

void CalcAppTestTest::cleanupTestCase()
{
}

void CalcAppTestTest::testCaseInitializedValues()
{
    Calc calc;

    QCOMPARE(calc.m_eNumeralSystem, Calc::NS_DEC);
    QCOMPARE(calc.m_eState, Calc::S_IDLE);
    QCOMPARE(calc.m_eWordSize, Calc::WS_QWORD);
    QCOMPARE(calc.m_veOperations.size(), 0);
    QCOMPARE(calc.m_vuMemory.size(), 0);
    QCOMPARE(calc.m_vuNumbers.size(), 0);
}

void CalcAppTestTest::testCaseConvertBin_data()
{
    QTest::addColumn<Calc::ResultType_t>("uDecimalValue");
    QTest::addColumn<QString>("qsExpectedResult");

    QTest::newRow("dec conversoin test") << (Calc::ResultType_t)2 << "10";
    QTest::newRow("dec conversoin test") << (Calc::ResultType_t)40 << "101000";
    QTest::newRow("dec conversoin test") << (Calc::ResultType_t)753 << "1011110001";
    QTest::newRow("exception - zero") << (Calc::ResultType_t)0 << "0";

}
void CalcAppTestTest::testCaseConvertBin()
{
    QFETCH(Calc::ResultType_t, uDecimalValue);
    QFETCH(QString, qsExpectedResult);

    Calc calc;
    QCOMPARE(calc.convert(Calc::NS_BIN, uDecimalValue), qsExpectedResult);
}

void CalcAppTestTest::testCaseConvertHex_data()
{
    QTest::addColumn<Calc::ResultType_t>("uDecimalValue");
    QTest::addColumn<QString>("qsExpectedResult");

    QTest::newRow("hex conversoin test") << (Calc::ResultType_t)2 << "2";
    QTest::newRow("hex conversoin test") << (Calc::ResultType_t)40 << "28";
    QTest::newRow("hex conversoin test") << (Calc::ResultType_t)753 << "2F1";
    QTest::newRow("exception - zero") << (Calc::ResultType_t)0 << "0";
}
void CalcAppTestTest::testCaseConvertHex()
{
    QFETCH(Calc::ResultType_t, uDecimalValue);
    QFETCH(QString, qsExpectedResult);

    Calc calc;
    QCOMPARE(calc.convert(Calc::NS_HEX, uDecimalValue), qsExpectedResult);
}

void CalcAppTestTest::testCaseConvertOct_data()
{
    QTest::addColumn<Calc::ResultType_t>("uDecimalValue");
    QTest::addColumn<QString>("qsExpectedResult");

    QTest::newRow("oct conversoin test") << (Calc::ResultType_t)2 << "2";
    QTest::newRow("oct conversoin test") << (Calc::ResultType_t)40 << "50";
    QTest::newRow("oct conversoin test") << (Calc::ResultType_t)753 << "1361";
    QTest::newRow("exception - zero") << (Calc::ResultType_t)0 << "0";
}
void CalcAppTestTest::testCaseConvertOct()
{
    QFETCH(Calc::ResultType_t, uDecimalValue);
    QFETCH(QString, qsExpectedResult);

    Calc calc;
    QCOMPARE(calc.convert(Calc::NS_OCT, uDecimalValue), qsExpectedResult);
}

void CalcAppTestTest::testCaseConvertDec_data()
{
    QTest::addColumn<Calc::ResultType_t>("uDecimalValue");
    QTest::addColumn<QString>("qsExpectedResult");

    QTest::newRow("dec conversoin test") << (Calc::ResultType_t)2 << "2";
    QTest::newRow("dec conversoin test") << (Calc::ResultType_t)40 << "40";
    QTest::newRow("dec conversoin test") << (Calc::ResultType_t)753 << "753";
    QTest::newRow("exception - zero") << (Calc::ResultType_t)0 << "0";
}
void CalcAppTestTest::testCaseConvertDec()
{
    QFETCH(Calc::ResultType_t, uDecimalValue);
    QFETCH(QString, qsExpectedResult);

    Calc calc;
    QCOMPARE(calc.convert(Calc::NS_DEC, uDecimalValue), qsExpectedResult);
}

void CalcAppTestTest::testCasePlus()
{
    Calc calc;

    //123
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_TWO);
    calc.addValue(Calc::V_THREE);

    calc.addOperation(Calc::O_PLUS);

    //567
    calc.addValue(Calc::V_FIVE);
    calc.addValue(Calc::V_SIX);
    calc.addValue(Calc::V_SEVEN);

    calc.calculate();
    QString qszExpected = "690";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseMinus()
{
    Calc calc;

    //567
    calc.addValue(Calc::V_FIVE);
    calc.addValue(Calc::V_SIX);
    calc.addValue(Calc::V_SEVEN);

    calc.addOperation(Calc::O_MINUS);

    //123
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_TWO);
    calc.addValue(Calc::V_THREE);

    calc.calculate();
    QString qszExpected = "444";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseDiv()
{
    Calc calc;

    //369
    calc.addValue(Calc::V_THREE);
    calc.addValue(Calc::V_SIX);
    calc.addValue(Calc::V_NINE);

    calc.addOperation(Calc::O_DIVISION);

    //3
    calc.addValue(Calc::V_THREE);

    calc.calculate();
    QString qszExpected = "123";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseMult()
{
    Calc calc;

    //369
    calc.addValue(Calc::V_THREE);
    calc.addValue(Calc::V_SIX);
    calc.addValue(Calc::V_NINE);

    calc.addOperation(Calc::O_MULTIPLICATION);

    //3
    calc.addValue(Calc::V_THREE);

    calc.calculate();
    QString qszExpected = "1107";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseMod()
{
    Calc calc;

    //369
    calc.addValue(Calc::V_THREE);
    calc.addValue(Calc::V_SIX);
    calc.addValue(Calc::V_NINE);

    calc.addOperation(Calc::O_MOD);

    //78
    calc.addValue(Calc::V_SEVEN);
    calc.addValue(Calc::V_EIGHT);

    calc.calculate();
    QString qszExpected = "57";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseLSH()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //101
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);

    calc.addOperation(Calc::O_LSH);

    //5
    calc.addValue(Calc::V_FIVE);

    calc.calculate();
    QString qszExpected = "10100000";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseRSH()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //10100000
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);

    calc.addOperation(Calc::O_RSH);

    //5
    calc.addValue(Calc::V_FIVE);

    calc.calculate();
    QString qszExpected = "101";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseRoL()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //101
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);

    calc.calculateRoL();

    calc.calculate();
    QString qszExpected = "1010";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseRoR()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //10100000
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);

    calc.calculateRoR();

    calc.calculate();
    QString qszExpected = "1010000";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseOR()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //10100000
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);

    calc.addOperation(Calc::O_OR);

    //111
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);

    calc.calculate();
    QString qszExpected = "10100111";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseXOR()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //10100000
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);

    calc.addOperation(Calc::O_XOR);

    //10100001
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);

    calc.calculate();
    QString qszExpected = "1";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseAND()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //10100000
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);

    calc.addOperation(Calc::O_AND);

    //10100001
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);

    calc.calculate();
    QString qszExpected = "10100000";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseNOT()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);

    //10100000
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);
    calc.addValue(Calc::V_ZERO);

    calc.calculateNot();

    calc.calculate();
    QString qszExpected = "1111111111111111111111111111111111111111111111111111111101011111";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseChangeSign()
{
    Calc calc;

    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);

    calc.changeSign();

    QString qszExpected = "(-111)";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseClearOperationalVectors()
{
    Calc calc;

    calc.addValue(Calc::V_B);
    calc.addOperation(Calc::O_DIVISION);
    calc.addValue(Calc::V_B);

    calc.clearOperationalVectors();

    QCOMPARE(calc.m_veOperations.size(), 0);
    QCOMPARE(calc.m_vuNumbers.size(), 0);
    QCOMPARE(calc.m_eState, Calc::S_IDLE);
}

void CalcAppTestTest::testCaseClearLastNumber()
{
    Calc calc;

    // BBB
    calc.changeNumeralSystem(Calc::NS_HEX);
    calc.addValue(Calc::V_B);
    calc.addValue(Calc::V_B);
    calc.addValue(Calc::V_B);

    calc.clearLastNumber();

    QCOMPARE(calc.m_vuNumbers.last(), 0u);
}

void CalcAppTestTest::testCaseGetAllOperations()
{
    Calc calc;

    calc.addValue(Calc::V_ONE);
    calc.addOperation(Calc::O_AND);
    calc.addValue(Calc::V_TWO);
    calc.addOperation(Calc::O_PLUS);
    calc.addOperation(Calc::O_LEFT_BRACKET);
    calc.addValue(Calc::V_THREE);
    calc.addOperation(Calc::O_DIVISION);
    calc.addValue(Calc::V_FOUR);
    calc.addOperation(Calc::O_MULTIPLICATION);
    calc.addValue(Calc::V_FIVE);
    calc.addOperation(Calc::O_RIGHT_BRACKET);
    calc.addOperation(Calc::O_RSH);
    calc.addValue(Calc::V_SIX);
    calc.addOperation(Calc::O_MOD);
    calc.addValue(Calc::V_SEVEN);

    QString qszExpected = "1AND2+(3/4*5Rsh6MOD7";

    QCOMPARE(calc.getAllOperations(), qszExpected);
}

void CalcAppTestTest::testCaseErase()
{
    Calc calc;
    calc.addValue(Calc::V_SIX);
    calc.eraseLastValue();
    calc.calculate();

    QCOMPARE(calc.m_uResult, 0u);
}

void CalcAppTestTest::testCaseChangeNumeral()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);
    calc.addValue(Calc::V_ONE);
    calc.eraseLastValue();
    calc.calculate();
    QString qszExpected = "0";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}
void CalcAppTestTest::testCaseChange()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);
    calc.addValue(Calc::V_ONE);
    calc.addOperation(Calc::O_PLUS);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ZERO);
    calc.calculate();
    QString qszExpected = "11";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseChangeBrackets()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_BIN);
    calc.addValue(Calc::V_ONE);
    calc.addOperation(Calc::O_RIGHT_BRACKET);
    calc.addOperation(Calc::O_RIGHT_BRACKET);
    calc.addOperation(Calc::O_RIGHT_BRACKET);
    calc.calculate();
    QString qszExpected = "1";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}
void CalcAppTestTest::testCaseBoundaryValues()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_DEC);
    calc.changeWordSize(Calc::WS_BYTE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_TWO);
    calc.addValue(Calc::V_SEVEN);
    calc.addOperation(Calc::O_PLUS);
    calc.addValue(Calc::V_TWO);

    calc.calculate();
    QString qszExpected = "(-127)";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}
void CalcAppTestTest::testCaseBoundaryValuesWord()
{
    Calc calc;
    calc.changeNumeralSystem(Calc::NS_HEX);
    calc.changeWordSize(Calc::WS_WORD);
    calc.addValue(Calc::V_SEVEN);
    calc.addValue(Calc::V_F);
    calc.addValue(Calc::V_F);
    calc.addValue(Calc::V_F);
    calc.addOperation(Calc::O_PLUS);
    calc.addValue(Calc::V_ONE);
    calc.changeNumeralSystem(Calc::NS_DEC);
    calc.calculate();
    QString qszExpected = "(-32768)";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseAddValueToMemory()
{
    Calc calc;

    //95
    calc.addValue(Calc::V_NINE);
    calc.addValue(Calc::V_FIVE);

    calc.addValueToMemory();

    QCOMPARE(calc.m_vuMemory.size(), 1);
    QCOMPARE(calc.m_vuMemory.last(), 95u);
}

void CalcAppTestTest::testCaseRemoveValueFromMemory()
{
    Calc calc;

    //95
    calc.addValue(Calc::V_NINE);
    calc.addValue(Calc::V_FIVE);

    calc.addValueToMemory();
    calc.removeValueFromMemory(0);  // remove first item

    QCOMPARE(calc.m_vuMemory.size(), 0);
}

void CalcAppTestTest::testCaseIncreaseValueFromMemory()
{
    Calc calc;

    //95
    calc.addValue(Calc::V_NINE);
    calc.addValue(Calc::V_FIVE);
    calc.addValueToMemory();

    calc.clearOperationalVectors();

    calc.addValue(Calc::V_NINE);

    calc.increaseValueFromMemory(0);// increase first value

    QString qszExpected  = "104";

    QCOMPARE(calc.getValueFromMemory(0), qszExpected);
}

void CalcAppTestTest::testCaseDecreaseValueFromMemory()
{
    Calc calc;

    //95
    calc.addValue(Calc::V_NINE);
    calc.addValue(Calc::V_FIVE);
    calc.addValueToMemory();

    calc.clearOperationalVectors();

    calc.addValue(Calc::V_NINE);

    calc.decreaseValueFromMemory(0);// decrease first value

    QString qszExpected  = "86";

    QCOMPARE(calc.getValueFromMemory(0), qszExpected);
}

void CalcAppTestTest::testCaseGetMemorySize()
{
    Calc calc;

    //95
    calc.addValue(Calc::V_NINE);
    calc.addValue(Calc::V_FIVE);
    calc.addValueToMemory();

    QCOMPARE(calc.getMemorySize(), (uint8_t)calc.m_vuMemory.size());
}

void CalcAppTestTest::testCaseGetValueFromMemory()
{
    Calc calc;

    //95
    calc.addValue(Calc::V_NINE);
    calc.addValue(Calc::V_FIVE);
    calc.addValueToMemory();

    QString qszExpected  = "95";

    QCOMPARE(calc.getValueFromMemory(0), qszExpected);
}

void CalcAppTestTest::testCaseQWordToByte()
{
    Calc calc;

    calc.changeNumeralSystem(Calc::NS_BIN);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);

    QString qszExpected  = "111111111";

    QCOMPARE(calc.getActualDisplay(), qszExpected);

    calc.changeWordSize(Calc::WS_BYTE);

    qszExpected  = "11111111";

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseByteToQWord()
{
    Calc calc;

    calc.changeNumeralSystem(Calc::NS_BIN);
    calc.changeWordSize(Calc::WS_BYTE);

    //11111111
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);\

    QString qszExpected  = "11111111";

    QCOMPARE(calc.getActualDisplay(), qszExpected);

    calc.changeWordSize(Calc::WS_QWORD);

    qszExpected = "1111111111111111111111111111111111111111111111111111111111111111";
    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseByteToWordSignCheck()
{
    Calc calc;

    calc.changeNumeralSystem(Calc::NS_BIN);
    calc.changeWordSize(Calc::WS_BYTE);

    //11111111
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);

    calc.changeNumeralSystem(Calc::NS_DEC);

    const QString qszExpected  = "(-1)";

    QCOMPARE(calc.getActualDisplay(), qszExpected);

    calc.changeWordSize(Calc::WS_QWORD);

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

void CalcAppTestTest::testCaseQWordToByteSignCheck()
{
    Calc calc;

    calc.changeNumeralSystem(Calc::NS_BIN);
    calc.changeWordSize(Calc::WS_QWORD);

    //11111111111111111111111111111111
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);
    calc.addValue(Calc::V_ONE);

    calc.changeNumeralSystem(Calc::NS_DEC);

    const QString qszExpected  = "(-1)";

    QCOMPARE(calc.getActualDisplay(), qszExpected);

    calc.changeWordSize(Calc::WS_BYTE);

    QCOMPARE(calc.getActualDisplay(), qszExpected);
}

QTEST_MAIN(CalcAppTestTest)

#include "tst_calcapptesttest.moc"
