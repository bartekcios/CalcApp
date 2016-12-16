#include "calc.h"
#include <QDebug>

constexpr char Calc::m_acValues[];
constexpr Calc::sWordSize Calc::m_asWordsSizes[];

Calc::Calc():
    m_eNumeralSystem(NS_DEC),
    m_eWordSize(WS_QWORD),
    m_eState(S_IDLE),
    m_uResult(0u)
{
    // nothing to do
}

Calc::~Calc()
{
    clearOperationalVectors();
}

bool Calc::addValue(const Calc::eValue a_eValue)
{
    bool fRetVal = false;
    ResultType_t uValue = (ResultType_t)a_eValue;

    if(S_LAST_VALUE == m_eState && 0 < m_vuNumbers.size())
    {
        uint8_t uCurrentBitsAmount = countBits(m_vuNumbers.last());
        // remove from last number last value
        if(NS_BIN == m_eNumeralSystem &&
                (uCurrentBitsAmount+1u <= (uint8_t)m_asWordsSizes[m_eWordSize].m_uBitsSize))
        {
            m_vuNumbers.last() <<= 1u;
            m_vuNumbers.last() += uValue;
            fRetVal = true;

            qDebug() << "[INF]Calc::addValue:bin: last number increased: " << m_vuNumbers.last();
        }
        else if(NS_OCT == m_eNumeralSystem &&
                (uCurrentBitsAmount+3u <= (uint8_t)m_asWordsSizes[m_eWordSize].m_uBitsSize))
        {
            m_vuNumbers.last() <<= 3u;
            m_vuNumbers.last() += uValue;
            fRetVal = true;

            qDebug() << "[INF]Calc::addValue:oct: last number increased: " << m_vuNumbers.last();
        }
        else if(NS_DEC == m_eNumeralSystem &&
                ((m_asWordsSizes[m_eWordSize].m_uMask/2) >= m_vuNumbers.last()*10u+uValue))
        {
            m_vuNumbers.last() *= 10u;
            m_vuNumbers.last() += uValue;
            fRetVal = true;

            qDebug() << "[INF]Calc::addValue:dec: last number increased: " << m_vuNumbers.last();
        }
        else if(NS_HEX == m_eNumeralSystem &&
                (uCurrentBitsAmount+4u <= (uint8_t)m_asWordsSizes[m_eWordSize].m_uBitsSize))
        {
            m_vuNumbers.last() <<= 4u;
            m_vuNumbers.last() += uValue;
            fRetVal = true;

            qDebug() << "[INF]Calc::addValue:hex: last number increased: " << m_vuNumbers.last();
        }
        else
        {
            // nothing to do
            qWarning() << "[WRN]Calc::addValue: last number (" << m_vuNumbers.last() << ") NOT increased by value" << a_eValue;
        }
    }
    else
    {
        // add new number
        m_vuNumbers.push_back(uValue);
        fRetVal = true;

        qDebug() << "[INF]Calc::addValue: new number added: " << uValue;
    }

    if(fRetVal)
    {
        m_eState = S_LAST_VALUE;
    }

    return fRetVal;
}

bool Calc::eraseLastValue(void)
{
    bool fRetVal = false;

    if(S_LAST_VALUE == m_eState && 0 < m_vuNumbers.size())
    {
        // remove from last number last value
        if(NS_BIN == m_eNumeralSystem)
        {
            m_vuNumbers.last() >>= 1;
            fRetVal = true;
        }
        else if(NS_OCT == m_eNumeralSystem)
        {
            m_vuNumbers.last() >>= 3;
            fRetVal = true;
        }
        else if(NS_DEC == m_eNumeralSystem)
        {
            m_vuNumbers.last() /= 10;
            fRetVal = true;
        }
        else if(NS_HEX == m_eNumeralSystem)
        {
            m_vuNumbers.last() >>= 4;
            fRetVal = true;
        }
        else
        {
            // nothing to do
            qWarning() << "[WRN]Calc::eraseLastValue: invalid m_eNumeralSystem: " << m_eNumeralSystem;
        }
    }
    else
    {
        // nothing to do
        qWarning() << "[WRN]Calc::eraseLastValue: last operation was not a number insert: " << m_eState << ", or numbers vector is empty:" << m_vuNumbers.size();
    }

    return fRetVal;
}

bool Calc::addOperation(const Calc::eOperation a_eOperation)
{
    bool fRetVal = false;

    if(S_LAST_VALUE == m_eState)
    {
        // add new operation
        m_veOperations.push_back(a_eOperation);
        m_eState = S_LAST_OPERATION;
        fRetVal = true;

        qDebug() << "[INF]Calc::addOperation: added new operation: " << a_eOperation;
    }
    else if(S_LAST_OPERATION == m_eState)
    {
        if(O_LEFT_BRACKET != a_eOperation &&
                O_RIGHT_BRACKET != a_eOperation)
        {
            // change last operation
            m_veOperations.last() = a_eOperation;
            m_eState = S_LAST_OPERATION;

            qDebug() << "[INF]Calc::addOperation: changed last operation: " << a_eOperation;
        }
        else
        {
            // add new operation
            m_veOperations.push_back(a_eOperation);
            m_eState = S_LAST_OPERATION;

            qDebug() << "[INF]Calc::addOperation: added new operation: " << a_eOperation << ", brackets detected";
        }
        fRetVal = true;
    }
    else
    {
        m_vuNumbers.push_back(0u);
        m_veOperations.push_back(a_eOperation);
        m_eState = S_LAST_OPERATION;
        fRetVal = true;

        qDebug() << "[INF]Calc::addOperation: added first operation: " << a_eOperation;
    }

    return fRetVal;
}

bool Calc::changeWordSize(const Calc::eWordSize a_eWordSize)
{
    bool fRetVal = false;

    if(WS_BYTE <= a_eWordSize && WS_QWORD >= a_eWordSize)
    {
        Calc::eWordSize eOldWordSize = m_eWordSize;

        // convert to correct mask
        if(0 < m_vuNumbers.size())
        {
            // support negative numbers
            if(m_vuNumbers.last() > (m_asWordsSizes[eOldWordSize].m_uMask/2))
            {
                ResultType_t uVal = m_asWordsSizes[eOldWordSize].m_uMask - m_vuNumbers.last();
                ++uVal;

                uint8_t uVal8 = (uint8_t)0u - (uint8_t)uVal;
                uint16_t uVal16 = (uint16_t)0u - (uint16_t)uVal;
                uint32_t uVal32 = (uint32_t)0u - (uint32_t)uVal;
                uint64_t uVal64 = (uint64_t)0u - (uint64_t)uVal;


                // cast to 64 bits
                switch(a_eWordSize)
                {
                case WS_BYTE:
                {
                    m_vuNumbers.last() = (ResultType_t)uVal8;
                    break;
                }
                case WS_WORD:
                {
                    m_vuNumbers.last() = (ResultType_t)uVal16;
                    break;
                }
                case WS_DWORD:
                {
                    m_vuNumbers.last() = (ResultType_t)uVal32;
                    break;
                }
                case WS_QWORD:
                {
                    m_vuNumbers.last() = (ResultType_t)uVal64;
                    break;
                }
                default:
                {
                    // nothing to do
                    qWarning() << "[WRN]Calc::calculateOperation: not supported word size: " << m_eWordSize;
                }
                }
            }
            else
            {
                m_vuNumbers.last() &= m_asWordsSizes[a_eWordSize].m_uMask;
            }
        }

        m_eWordSize = a_eWordSize;

        fRetVal = true;

        qDebug() << "[INF]Calc::changeWordSize: word size changed to: " << m_eWordSize;
    }
    else
    {
        qWarning() << "[WRN]Calc::changeWordSize: unsupported word size:: " << m_eWordSize;
    }

    return fRetVal;
}

bool Calc::changeNumeralSystem(const Calc::eNumeralSystem a_eNumeralSystem)
{
    bool fRetVal = false;

    if(NS_BIN <= a_eNumeralSystem && NS_HEX >= a_eNumeralSystem)
    {
        m_eNumeralSystem = a_eNumeralSystem;

        fRetVal = true;
        qDebug() << "[INF]Calc::changeNumeralSystem: numeral system changed to: " << m_eNumeralSystem;
    }
    else
    {
        qWarning() << "[WRN]Calc::changeNumeralSystem: unsupported numeral system: " << m_eNumeralSystem;
    }

    return fRetVal;
}

void Calc::clearOperationalVectors()
{
    m_vuNumbers.clear();
    m_veOperations.clear();

    // reset state (no numbers, no operations, like at the beginning)
    m_eState = S_IDLE;

    qDebug() << "[INF]Calc::clearOperationalVectors: vectors cleared correctly";
}

bool Calc::clearLastNumber()
{
    bool fRetVal = false;

    if(0 < m_vuNumbers.size())
    {
        m_vuNumbers.last() = 0u;
        fRetVal = true;

        qDebug() << "[INF]Calc::clearLastNumber: last number cleared correctly";
    }
    else
    {
        qWarning() << "[WRN]Calc::clearLastNumber: vector is empty!";
    }

    return fRetVal;
}

QString Calc::getActualDisplay()
{
    QString qsRetVal = "";

    if(0u != m_vuNumbers.size())
    {
        qsRetVal = convert(m_eNumeralSystem, m_vuNumbers.last());
    }
    else
    {
        qsRetVal = "0";
    }

    return qsRetVal;
}

QString Calc::getDisplay(const Calc::eNumeralSystem a_eNumeralSystem)
{
    QString qsRetVal = "";

    if(0u != m_vuNumbers.size())
    {
        qsRetVal = convert(a_eNumeralSystem, m_vuNumbers.last());
    }
    else
    {
        qsRetVal = "0";
    }

    return qsRetVal;
}

QString Calc::getAllOperations()
{
    QString qszRetVal = "";
    uint8_t uOperationIndex = 0u;
    uint8_t uNumberIndex = 0u;

    while(uNumberIndex < m_vuNumbers.size() ||
          uOperationIndex < m_veOperations.size())
    {
        //left brackets
        while(uOperationIndex < m_veOperations.size() &&
              O_LEFT_BRACKET == m_veOperations[uOperationIndex])
        {
            // "+)" case
            qszRetVal += convertOperationToQString(m_veOperations[uOperationIndex++]);
        }

        //number
        if(uNumberIndex < m_vuNumbers.size())
        {
            qszRetVal += convert(m_eNumeralSystem, m_vuNumbers[uNumberIndex++]);
        }

        //right brackets
        while(uOperationIndex < m_veOperations.size() &&
              O_RIGHT_BRACKET == m_veOperations[uOperationIndex])
        {
            // "+)" case
            qszRetVal += convertOperationToQString(m_veOperations[uOperationIndex++]);
        }

        //operation - not bracket
        if(uOperationIndex < m_veOperations.size())
        {
            qszRetVal += convertOperationToQString(m_veOperations[uOperationIndex++]);
        }
    }

    return qszRetVal;
}

QString Calc::convert(const Calc::eNumeralSystem a_eNumeralSystem, const ResultType_t a_uDecimalValue)
{
    QString qsRetVal = "";
    ResultType_t uTempVal = a_uDecimalValue;
    unsigned short uNumeralSystem = (unsigned short)a_eNumeralSystem;

    if(0u == a_uDecimalValue)
    {
        qsRetVal = "0";
    }
    else
    {
        // support negative numbers
        if(NS_DEC == a_eNumeralSystem &&
                a_uDecimalValue > (m_asWordsSizes[m_eWordSize].m_uMask/2))
        {
            uTempVal = (m_asWordsSizes[m_eWordSize].m_uMask/2+1) - (uTempVal - (m_asWordsSizes[m_eWordSize].m_uMask/2)) + 1;
        }

        while(0 != uTempVal)
        {
            qsRetVal = m_acValues[(uTempVal%uNumeralSystem)] + qsRetVal;
            uTempVal /= uNumeralSystem;
        }
        // support negative numbers
        if(NS_DEC == a_eNumeralSystem &&
                a_uDecimalValue > (m_asWordsSizes[m_eWordSize].m_uMask/2))
        {
            qsRetVal = "(-" + qsRetVal + ")";
        }
    }


    return qsRetVal;
}

uint8_t Calc::countBits(const Calc::ResultType_t a_uNumber)
{
    uint8_t uRetVal = 0;
    ResultType_t uTempVal = a_uNumber;
    while(0 != uTempVal)
    {
        ++uRetVal;
        uTempVal >>=1;
    }

    return uRetVal;
}

bool Calc::calculate(void)
{
    bool fRetVal = false;

    if(false != validateBrackets())
    {
        uint8_t uLeftBracketsCounter = !(0u);

        // calculate all brackets from the deepest
        while(0u != uLeftBracketsCounter)
        {
            uLeftBracketsCounter = calculateBracket();
        }
        // calculate whole expression without brackets
        calculateBracket();

        //reset state to number(no operations left)
        m_eState = S_LAST_VALUE;
    }
    else
    {
        qWarning() << "[WRN]Calc::calculate: brackets validation failed!";
    }

    return fRetVal;
}

uint8_t Calc::calculateBracket(void)
{
    uint8_t uLeftBracketsCounter = 0u;
    uint8_t uDeepestLeftBracketIndex = 0u;
    uint8_t uDeepestRightBracketIndex = 0u;
    uint8_t uNumberInBracketIndex = 0u;

    calculateBracketsIndexesAndCount(uLeftBracketsCounter, uDeepestLeftBracketIndex, uDeepestRightBracketIndex);

    // find operations with high priority
    calculateNumberInBracketIndex(uNumberInBracketIndex, uDeepestLeftBracketIndex, uLeftBracketsCounter);
    calculatePriorityOperation(O_HIGH_PRIORITY_START, O_HIGH_PRIORITY_END, uDeepestLeftBracketIndex, uDeepestRightBracketIndex, uNumberInBracketIndex, uLeftBracketsCounter);

    // find operations with medium priority
    calculateNumberInBracketIndex(uNumberInBracketIndex, uDeepestLeftBracketIndex, uLeftBracketsCounter);
    calculatePriorityOperation(O_MEDIUM_PRIORITY_START, O_MEDIUM_PRIORITY_END, uDeepestLeftBracketIndex, uDeepestRightBracketIndex, uNumberInBracketIndex, uLeftBracketsCounter);

    // find operations with low priority
    calculateNumberInBracketIndex(uNumberInBracketIndex, uDeepestLeftBracketIndex, uLeftBracketsCounter);
    calculatePriorityOperation(O_LOW_PRIORITY_START, O_LOW_PRIORITY_END, uDeepestLeftBracketIndex, uDeepestRightBracketIndex, uNumberInBracketIndex, uLeftBracketsCounter);

    removeDeepestBrackets(uLeftBracketsCounter, uDeepestLeftBracketIndex);
    uLeftBracketsCounter -= (0u == uLeftBracketsCounter) ? 0 : 1;

    return uLeftBracketsCounter;
}

bool Calc::calculateOperation(const uint8_t a_uLeftOperandIndex, const uint8_t a_uRightOperandIndex, const uint8_t a_uOperationIndex, const uint8_t a_uLeftBracketsCounter)
{
    bool fRetVal = false;
    uint8_t uResult8 = 0u;
    uint16_t uResult16 = 0u;
    uint32_t uResult32 = 0u;
    uint64_t uResult64 = 0u;
    ResultType_t uResult = 0u;

    if((0u == a_uLeftBracketsCounter ||
        (a_uLeftOperandIndex < a_uRightOperandIndex &&
         a_uRightOperandIndex < m_vuNumbers.size())) &&
            a_uOperationIndex < m_veOperations.size())
    {
        // calculate result
        switch(m_veOperations[a_uOperationIndex])
        {
        // the highest priority
        case O_DIVISION:
        {
            if(0u < m_vuNumbers[a_uRightOperandIndex])
            {
                uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] / (uint8_t)m_vuNumbers[a_uRightOperandIndex];
                uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] / (uint16_t)m_vuNumbers[a_uRightOperandIndex];
                uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] / (uint32_t)m_vuNumbers[a_uRightOperandIndex];
                uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] / (uint64_t)m_vuNumbers[a_uRightOperandIndex];
                fRetVal = true;
            }
            else
            {

            }
            break;
        }
        case O_MULTIPLICATION:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] * (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] * (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] * (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] * (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        case O_MOD:
        {
            if(0u < m_vuNumbers[a_uRightOperandIndex])
            {
                uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] % (uint8_t)m_vuNumbers[a_uRightOperandIndex];
                uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] % (uint16_t)m_vuNumbers[a_uRightOperandIndex];
                uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] % (uint32_t)m_vuNumbers[a_uRightOperandIndex];
                uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] % (uint64_t)m_vuNumbers[a_uRightOperandIndex];
                fRetVal = true;
            }
            else
            {

            }
            break;
        }
            // medium priority
        case O_LSH:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] << (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] << (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] << (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] << (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        case O_RSH:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] >> (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] >> (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] >> (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] >> (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        case O_OR:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] | (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] | (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] | (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] | (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        case O_XOR:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] ^ (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] ^ (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] ^ (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] ^ (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        case O_AND:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] & (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] & (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] & (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] & (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        case O_PLUS:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] + (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] + (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] + (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] + (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        case O_MINUS:
        {
            uResult8  = (uint8_t) m_vuNumbers[a_uLeftOperandIndex] - (uint8_t)m_vuNumbers[a_uRightOperandIndex];
            uResult16 = (uint16_t)m_vuNumbers[a_uLeftOperandIndex] - (uint16_t)m_vuNumbers[a_uRightOperandIndex];
            uResult32 = (uint32_t)m_vuNumbers[a_uLeftOperandIndex] - (uint32_t)m_vuNumbers[a_uRightOperandIndex];
            uResult64 = (uint64_t)m_vuNumbers[a_uLeftOperandIndex] - (uint64_t)m_vuNumbers[a_uRightOperandIndex];
            fRetVal = true;
            break;
        }
        default:
        {
            // nothing to do
            qWarning() << "[WRN]Calc::calculateOperation: not supported operation: " <<
                          m_veOperations[a_uOperationIndex] <<
                          " " << a_uLeftOperandIndex <<
                          " " << a_uRightOperandIndex;
            break;
        }
        }

        if(fRetVal)
        {
            // cast to 64 bits
            switch(m_eWordSize)
            {
            case WS_BYTE:
            {
                uResult = (ResultType_t)uResult8;
                break;
            }
            case WS_WORD:
            {
                uResult = (ResultType_t)uResult16;
                break;
            }
            case WS_DWORD:
            {
                uResult = (ResultType_t)uResult32;
                break;
            }
            case WS_QWORD:
            {
                uResult = (ResultType_t)uResult64;
                break;
            }
            default:
            {
                // nothing to do
                qWarning() << "[WRN]Calc::calculateOperation: not supported word size: " << m_eWordSize;
            }
            }
            // fix vectors
            m_vuNumbers[a_uLeftOperandIndex] = uResult;
            m_vuNumbers.remove(a_uRightOperandIndex);
            m_veOperations.remove(a_uOperationIndex);
        }
    }
    else
    {
        // nothing to do
        qWarning() << "[WRN]Calc::calculateOperation: not valid indexes: " <<
                      a_uLeftOperandIndex << " " <<
                      a_uRightOperandIndex << " " <<
                      m_veOperations[a_uOperationIndex];
    }

    return fRetVal;
}

void Calc::calculateBracketsIndexesAndCount(uint8_t & a_uLeftBracketsCounter, uint8_t & a_uDeepestLeftBracketIndex, uint8_t & a_uDeepestRightBracketIndex)
{
    for(uint8_t uI=0; uI<m_veOperations.size();++uI)
    {
        if(O_LEFT_BRACKET == m_veOperations[uI])
        {
            a_uDeepestLeftBracketIndex = uI;
            ++a_uLeftBracketsCounter;
        }
    }

    // calculate the deepest bracket
    for(uint8_t uI=a_uDeepestLeftBracketIndex; uI<m_veOperations.size();++uI)
    {
        if(O_RIGHT_BRACKET == m_veOperations[uI])
        {
            a_uDeepestRightBracketIndex = uI;
            break;
        }
    }

    if(0u == a_uLeftBracketsCounter)
    {
        a_uDeepestLeftBracketIndex = 0u;
        a_uDeepestRightBracketIndex = m_veOperations.size();
    }
}

bool Calc::removeDeepestBrackets(const uint8_t a_uLeftBracketsCounter, const uint8_t a_uDeepestLeftBracketIndex)
{
    bool fRetVal = false;

    if(0u != a_uLeftBracketsCounter)
    {
        //after remove left bracket, right bracket shifts to left's index
        m_veOperations.remove(a_uDeepestLeftBracketIndex);
        m_veOperations.remove(a_uDeepestLeftBracketIndex);

        fRetVal = true;
    }

    return fRetVal;
}

void Calc::calculateNumberInBracketIndex(uint8_t & a_uNumberInBracketIndex, const uint8_t a_uDeepestLeftBracketIndex, const uint8_t a_uLeftBracketsCounter)
{
    // if no brackets left, start from the beginning
    if(0u == a_uLeftBracketsCounter)
    {
        a_uNumberInBracketIndex = 0u;
    }
    else
    {
        a_uNumberInBracketIndex = a_uDeepestLeftBracketIndex - a_uLeftBracketsCounter;
    }
}

void Calc::calculatePriorityOperation(const eOperation a_eStartOperationPriority, const eOperation a_eEndOperationPriority, const uint8_t a_uDeepestLeftBracketIndex, uint8_t & a_uDeepestRightBracketIndex, uint8_t a_uNumberInBracketIndex, uint8_t & a_uLeftBracketsCounter)
{
    for(uint8_t uI = a_uDeepestLeftBracketIndex; uI<a_uDeepestRightBracketIndex; ++uI)
    {
        bool fOperationFinished = false;
        if(a_eStartOperationPriority < m_veOperations[uI] &&
                a_eEndOperationPriority > m_veOperations[uI])
        {
            fOperationFinished = calculateOperation(a_uNumberInBracketIndex, a_uNumberInBracketIndex+1, uI, a_uLeftBracketsCounter);
            if(fOperationFinished)
            {
                --a_uDeepestRightBracketIndex;
            }
        }
        ++a_uNumberInBracketIndex;
        if(fOperationFinished)
        {
            // check once again the same index - new operation
            --a_uNumberInBracketIndex;
            --uI;
        }
    }
}

QString Calc::convertOperationToQString(const Calc::eOperation a_eOperation)
{
    QString qszRetVal = "";

    switch(a_eOperation)
    {
    case O_MOD:
    {
        qszRetVal = "MOD";
        break;
    }
    case O_DIVISION:
    {
        qszRetVal = "/";
        break;
    }
    case O_MULTIPLICATION:
    {
        qszRetVal = "*";
        break;
    }
    case O_LSH:
    {
        qszRetVal = "Lsh";
        break;
    }
    case O_RSH:
    {
        qszRetVal = "Rsh";
        break;
    }
    case O_ROL:
    {
        qszRetVal = "RoL";
        break;
    }
    case O_ROR:
    {
        qszRetVal = "RoR";
        break;
    }
    case O_OR:
    {
        qszRetVal = "OR";
        break;
    }
    case O_XOR:
    {
        qszRetVal = "XOR";
        break;
    }
    case O_AND:
    {
        qszRetVal = "AND";
        break;
    }
    case O_MINUS:
    {
        qszRetVal = "-";
        break;
    }
    case O_PLUS:
    {
        qszRetVal = "+";
        break;
    }
    case O_LEFT_BRACKET:
    {
        qszRetVal = "(";
        break;
    }
    case O_RIGHT_BRACKET:
    {
        qszRetVal = ")";
        break;
    }
    default:
    {
        // nothing to do
        qWarning() << "[WRN]Calc::convertOperationToQString: invalid operation: " << a_eOperation;
        break;
    }
    }

    return qszRetVal;
}

void Calc::calculateRoL(void)
{
    uint8_t uResult8 = 0u;
    uint16_t uResult16 = 0u;
    uint32_t uResult32 = 0u;
    uint64_t uResult64 = 0u;

    if(0 != m_vuNumbers.size())
    {
        //              shift to right                   or with left bit which goes to right
        uResult8  = (((uint8_t) m_vuNumbers.last()) << 1) | (((uint8_t) m_vuNumbers.last()) >> (m_asWordsSizes[WS_BYTE].m_uBitsSize-1));
        uResult16 = (((uint16_t)m_vuNumbers.last()) << 1) | (((uint16_t) m_vuNumbers.last()) >> (m_asWordsSizes[WS_WORD].m_uBitsSize-1));
        uResult32 = (((uint32_t)m_vuNumbers.last()) << 1) | (((uint32_t) m_vuNumbers.last()) >> (m_asWordsSizes[WS_DWORD].m_uBitsSize-1));
        uResult64 = (((uint64_t)m_vuNumbers.last()) << 1) | (((uint64_t) m_vuNumbers.last()) >> (m_asWordsSizes[WS_QWORD].m_uBitsSize-1));

        // cast to 64 bits
        switch(m_eWordSize)
        {
        case WS_BYTE:
        {
            m_vuNumbers.last() = (ResultType_t)uResult8;
            break;
        }
        case WS_WORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult16;
            break;
        }
        case WS_DWORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult32;
            break;
        }
        case WS_QWORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult64;
            break;
        }
        default:
        {
            // nothing to do
            qWarning() << "[WRN]Calc::calculateRoL: not supported word size: " << m_eWordSize;
        }
        }
    }
    else
    {
        qWarning() << "[WRN]Calc::calculateRoL: empty numbers vector.";
    }
}

void Calc::calculateRoR()
{
    uint8_t uResult8 = 0u;
    uint16_t uResult16 = 0u;
    uint32_t uResult32 = 0u;
    uint64_t uResult64 = 0u;

    if(0 != m_vuNumbers.size())
    {
        //              shift to right                   OR operation with left bit which goes to right
        uResult8  = (((uint8_t) m_vuNumbers.last()) >> 1) | (((uint8_t) m_vuNumbers.last()) << (m_asWordsSizes[WS_BYTE].m_uBitsSize-1));
        uResult16 = (((uint16_t)m_vuNumbers.last()) >> 1) | (((uint16_t) m_vuNumbers.last()) << (m_asWordsSizes[WS_WORD].m_uBitsSize-1));
        uResult32 = (((uint32_t)m_vuNumbers.last()) >> 1) | (((uint32_t) m_vuNumbers.last()) << (m_asWordsSizes[WS_DWORD].m_uBitsSize-1));
        uResult64 = (((uint64_t)m_vuNumbers.last()) >> 1) | (((uint64_t) m_vuNumbers.last()) << (m_asWordsSizes[WS_QWORD].m_uBitsSize-1));

        // cast to 64 bits
        switch(m_eWordSize)
        {
        case WS_BYTE:
        {
            m_vuNumbers.last() = (ResultType_t)uResult8;
            break;
        }
        case WS_WORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult16;
            break;
        }
        case WS_DWORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult32;
            break;
        }
        case WS_QWORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult64;
            break;
        }
        default:
        {
            // nothing to do
            qWarning() << "[WRN]Calc::calculateRoR: not supported word size: " << m_eWordSize;
        }
        }
    }
    else
    {
        qWarning() << "[WRN]Calc::calculateRoR: empty numbers vector.";
    }
}

void Calc::calculateNot()
{
    if(0 < m_vuNumbers.size())
    {
        m_vuNumbers.last() ^= m_asWordsSizes[m_eWordSize].m_uMask;
    }
}

void Calc::addValueToMemory()
{
    if(0 < m_vuNumbers.size())
    {
        m_vuMemory.push_back(m_vuNumbers.last());
    }
    else
    {
        m_vuMemory.push_back(0u);
    }
}

void Calc::removeValueFromMemory(const uint8_t a_uIndex)
{
    if(a_uIndex < m_vuMemory.size())
    {
        m_vuMemory.removeAt(a_uIndex);
    }
    else
    {
        qWarning() << "[WRN]Calc::removeValueFromMemory: invalid index value: " << a_uIndex;
    }
}

void Calc::increaseValueFromMemory(const uint8_t a_uIndex)
{
    if(a_uIndex < m_vuMemory.size() &&
            0 < m_vuNumbers.size())
    {
        m_vuMemory[a_uIndex] += m_vuNumbers.last();
    }
    else
    {
        qWarning() << "[WRN]Calc::increaseValueFromMemory: invalid index value: " << a_uIndex << " or empty numbers vector";
    }
}

void Calc::decreaseValueFromMemory(const uint8_t a_uIndex)
{
    if(a_uIndex < m_vuMemory.size() &&
            0 < m_vuNumbers.size())
    {
        m_vuMemory[a_uIndex] -= m_vuNumbers.last();
    }
    else
    {
        qWarning() << "[WRN]Calc::decreaseValueFromMemory: invalid index value: " << a_uIndex << " or empty numbers vector";
    }
}

uint8_t Calc::getMemorySize(void)
{
    return m_vuMemory.size();
}

QString Calc::getValueFromMemory(const uint8_t a_uIndex)
{
    QString qszRetVal = "";

    if(a_uIndex < m_vuMemory.size())
    {
        qszRetVal = convert(m_eNumeralSystem, m_vuMemory[a_uIndex]);
    }
    else
    {
        qWarning() << "[WRN]Calc::getValueFromMemory: invalid index value: " << a_uIndex;
    }

    return qszRetVal;
}

void Calc::changeSign()
{
    uint8_t  uResult8 = 0u;
    uint16_t uResult16 = 0u;
    uint32_t uResult32 = 0u;
    uint64_t uResult64 = 0u;

    if(0 < m_vuNumbers.size())
    {
        // negative to positive
        if(0u == m_vuNumbers.last())
        {
            uResult8  = 0u;
            uResult16 = 0u;
            uResult32 = 0u;
            uResult64 = 0u;
        }
        else if(m_vuNumbers.last() > (m_asWordsSizes[m_eWordSize].m_uMask/2))
        {
            uResult8  = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
            uResult16 = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
            uResult32 = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
            uResult64 = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
        }
        else
        {
            // positive to negative
            uResult8  = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
            uResult16 = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
            uResult32 = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
            uResult64 = m_asWordsSizes[m_eWordSize].m_uMask - m_vuNumbers.last() + 1u;
        }

        // cast to 64 bits
        switch(m_eWordSize)
        {
        case WS_BYTE:
        {
            m_vuNumbers.last() = (ResultType_t)uResult8;
            break;
        }
        case WS_WORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult16;
            break;
        }
        case WS_DWORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult32;
            break;
        }
        case WS_QWORD:
        {
            m_vuNumbers.last() = (ResultType_t)uResult64;
            break;
        }
        default:
        {
            // nothing to do
            qWarning() << "[WRN]Calc::changeSign: not supported word size: " << m_eWordSize;
        }
        }
    }
    else
    {
        // nothing to do
        qWarning() << "[WRN]Calc::changeSign: empty numbers vector: " << m_eWordSize;
    }
}

void Calc::copyNumberFromMemory(const Calc::ResultType_t a_uMemoryVectorIndex)
{
    if(a_uMemoryVectorIndex < (Calc::ResultType_t)m_vuMemory.size())
    {
        if(0 < m_vuNumbers.size())
        {
            // change last number
            m_vuNumbers.last() = m_vuMemory[a_uMemoryVectorIndex];
        }
        else
        {
            // create first number
            m_vuNumbers.push_back(m_vuMemory[a_uMemoryVectorIndex]);
        }

        m_eState = S_LAST_VALUE;

        qDebug() << "[INF]Calc::changeLastNumber: last value changed.";
    }
    else
    {
        // nothing to do
        qWarning() << "[WRN]Calc::changeLastNumber: empty memory vector";
    }
}

bool Calc::validateBrackets()
{
    bool fRetVal = true;
    int iBracketsBalance = 0;

    for(int i=0;i<m_veOperations.size();++i)
    {
        if(O_LEFT_BRACKET == m_veOperations[i])
        {
            ++iBracketsBalance;
        }

        if(O_RIGHT_BRACKET == m_veOperations[i])
        {
            --iBracketsBalance;
        }

        if(0 > iBracketsBalance)
        {
            fRetVal = false;
            break;
        }
    }
    if(0 != iBracketsBalance)
    {
        fRetVal = false;
    }

    return fRetVal;
}

























