#ifndef __ASSN1_STU_H__
#define __ASSN1_STU_H__

#include "assn1.h"

template <size_t N> void NANDGate<N>::advanceCycle()
{
    // Perform the NAND gate operation
    std::bitset<N> result(0); // Initialize result to 0 (for NAND gate)

    // Perform NAND operation for each bit
    for (size_t i = 0; i < N; ++i)
    {
        // NAND operation: result = !(input0 && input1)
        result[i] = !((*_inputs[0])[i] && (*_inputs[1])[i]);
    }

    // Set the output wire's bits
    for (size_t i = 0; i < N; ++i)
    {
        (*_output)[i] = result[i];
    }
}

template <size_t N> void SignedAdder<N>::advanceCycle()
{
    /* FIXME */
}

template <size_t N> void SignedSubtractor<N>::advanceCycle()
{
    /* FIXME */
}

template <size_t N> void LogicalUnit<N>::advanceCycle()
{
    /* FIXME */
}

template <size_t N, size_t M> void HashTable<N, M>::advanceCycle()
{
    /* FIXME */
}

template <size_t N, size_t D> void DelayQueue<N, D>::advanceCycle()
{
    /* FIXME */
}

#endif
