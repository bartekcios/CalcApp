#include "memory.h"
#include <QDebug>

Memory::Memory()
{

}

Memory::~Memory()
{

}

void Memory::addValue(ResultType_t a_uValueToAdd)
{
    m_vuMemory.push_back(a_uValueToAdd);
}

bool Memory::removeValue(const MemoryVectorIndex_t a_uIndex)
{
    bool fRetVal = false;

    if(a_uIndex < (MemoryVectorIndex_t)m_vuMemory.size())
    {
        m_vuMemory.removeAt(a_uIndex);
        fRetVal = true;
    }
    else
    {
        qWarning() << "[WRN]Memory::addValue: invalid index value: " << a_uIndex;
    }

    return fRetVal;
}

bool Memory::increaseValue(const MemoryVectorIndex_t a_uIndex, const ResultType_t a_uValue)
{
    bool fRetVal = false;
    if(a_uIndex < (MemoryVectorIndex_t)m_vuMemory.size())
    {
        m_vuMemory[a_uIndex] += a_uValue;
        fRetVal = true;
    }
    else
    {
        qWarning() << "[WRN]Memory::increaseValue: invalid index value: " << a_uIndex;
    }

    return fRetVal;
}

bool Memory::decreaseValue(const MemoryVectorIndex_t a_uIndex, const ResultType_t a_uValue)
{
    bool fRetVal = false;
    if(a_uIndex < (MemoryVectorIndex_t)m_vuMemory.size())
    {
        m_vuMemory[a_uIndex] -= a_uValue;
        fRetVal = true;
    }
    else
    {
        qWarning() << "[WRN]Memory::decreaseValue: invalid index value: " << a_uIndex;
    }

    return fRetVal;
}

MemoryVectorIndex_t Memory::getSize()
{
    return m_vuMemory.size();
}

ResultType_t Memory::getValue(const MemoryVectorIndex_t a_uIndex)
{
    return m_vuMemory[a_uIndex];
}
