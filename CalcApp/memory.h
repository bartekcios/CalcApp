#ifndef MEMORY_H
#define MEMORY_H
#include <QVector>
#include "commontypedefs.h"


class Memory
{
public:
    Memory();
    ~Memory();

    void addValue(ResultType_t a_uValueToAdd);
    bool removeValue(const MemoryVectorIndex_t a_uIndex);
    bool increaseValue(const MemoryVectorIndex_t a_uIndex, const ResultType_t a_uValue);
    bool decreaseValue(const MemoryVectorIndex_t a_uIndex, const ResultType_t a_uValue);
    MemoryVectorIndex_t getSize(void);
    ResultType_t getValue(const MemoryVectorIndex_t a_uIndex);

private:
    QVector<ResultType_t> m_vuMemory;
};

#endif // MEMORY_H
