#ifndef CALC_H
#define CALC_H
#include <QString>
#include <QVector>
#include "commontypedefs.h"
#include "memory.h"

class Calc
{
    // interface
    public:
    enum eNumeralSystem
    {
        NS_BIN = 2,
        NS_OCT = 8,
        NS_DEC = 10,
        NS_HEX = 16,
    };

    enum eWordSize
    {
        WS_BYTE = 0,
        WS_WORD,
        WS_DWORD,
        WS_QWORD,
        WS_SIZE
    };

    enum eOperation
    {
        O_HIGH_PRIORITY_START,
        O_MOD,
        O_DIVISION,
        O_MULTIPLICATION,
        O_HIGH_PRIORITY_END,

        O_MEDIUM_PRIORITY_START,
        O_LSH,
        O_RSH,
        O_ROL,
        O_ROR,
        O_OR,
        O_XOR,
        O_NOT,
        O_AND,
        O_MEDIUM_PRIORITY_END,

        O_LOW_PRIORITY_START,
        O_MINUS,
        O_PLUS,
        O_LOW_PRIORITY_END,

        O_LEFT_BRACKET,
        O_RIGHT_BRACKET,
        O_CHANGE_SIGN,
        O_SIZE
    };

    enum eValue
    {
        V_ZERO = 0,
        V_ONE,
        V_TWO,
        V_THREE,
        V_FOUR,
        V_FIVE,
        V_SIX,
        V_SEVEN,
        V_EIGHT,
        V_NINE,
        V_A,
        V_B,
        V_C,
        V_D,
        V_E,
        V_F,
        V_SIZE
    };

    enum eState
    {
        S_IDLE,
        S_LAST_VALUE,
        S_LAST_OPERATION,
        S_SIZE
    };

    // public functions
    Calc();
    virtual ~Calc();
    bool addValue(const eValue a_eValue);
    bool eraseLastValue(void);  // <
    bool addOperation(const eOperation a_eOperation);
    bool changeWordSize(const eWordSize a_eWordSize);
    bool changeNumeralSystem(const eNumeralSystem a_eNumeralSystem);
    void clearOperationalVectors(); // C button
    bool clearLastNumber(); // CE button
    bool calculate(void);
    QString getActualDisplay();
    QString getDisplay(const eNumeralSystem a_eNumeralSystem);
    QString getAllOperations();
    void calculateRoL(void);
    void calculateRoR(void);
    void calculateNot(void);
    void changeSign(void);
    // memory
    void addValueToMemory();
    void increaseValueFromMemory(const MemoryVectorIndex_t a_uIndex);
    void decreaseValueFromMemory(const MemoryVectorIndex_t a_uIndex);
    MemoryVectorIndex_t getMemorySize(void);
    QString getValueFromMemory(const MemoryVectorIndex_t a_uIndex);
    void copyNumberFromMemory(const MemoryVectorIndex_t a_uMemoryVectorIndex);
    bool removeValueFromMemory(const MemoryVectorIndex_t a_uIndex);

private:
    //typedefs
    struct sWordSize
    {
        uint8_t m_uBitsSize;
        ResultType_t m_uMask;
    };

    //members
    Memory m_oMemory;
    eNumeralSystem m_eNumeralSystem;
    eWordSize m_eWordSize;
    eState m_eState;
    QVector<eOperation> m_veOperations;
    QVector<ResultType_t> m_vuNumbers;
    ResultType_t m_uResult;
    static constexpr char m_acValues[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
                                                    //BitsSize|       PositiveMask
    static constexpr sWordSize m_asWordsSizes[] = {{         8, 0x00000000000000ff}/*Byte*/,
                                                   {        16, 0x000000000000ffff}/*Word*/,
                                                   {        32, 0x00000000ffffffff}/*DWord*/,
                                                   {        64, 0xffffffffffffffff}/*QWord*/};

    // private functions
    QString convert(const eNumeralSystem a_eNumeralSystem, const ResultType_t a_uDecimalValue);
    uint8_t countBits(const ResultType_t a_uNumber);
    uint8_t calculateBracket(void);
    bool calculateOperation(const uint8_t a_uLeftOperandIndex, const uint8_t a_uRightOperandIndex, const uint8_t a_uOperationIndex, const uint8_t a_uLeftBracketsCounter);
    void calculateBracketsIndexesAndCount(uint8_t & a_uLeftBracketsCounter, uint8_t & a_uDeepestLeftBracketIndex, uint8_t & a_uDeepestRightBracketIndex);
    bool removeDeepestBrackets(const uint8_t a_uLeftBracketsCounter, const uint8_t a_uDeepestLeftBracketIndex);
    void calculateNumberInBracketIndex(uint8_t & a_uNumberInBracketIndex, const uint8_t a_uDeepestLeftBracketIndex, const uint8_t a_uLeftBracketsCounter);
    void calculatePriorityOperation(const eOperation a_eStartOperation, const eOperation a_eEndOperation, const uint8_t a_uDeepestLeftBracketIndex, uint8_t & a_uDeepestRightBracketIndex, uint8_t a_uNumberInBracketIndex, uint8_t &uLeftBracketsCounter);
    QString convertOperationToQString(const eOperation a_eOperation);
    bool validateBrackets(void);
    ResultType_t castToResultType(const Calc::eWordSize a_eWordSize, const ByteWordSize_t a_uByteSource, const WordWordSize_t a_uWordSource, const DWordWordSize_t a_uDWordSource, const QWordWordSize_t a_uQWordSource);
};

#endif // CALC_H
