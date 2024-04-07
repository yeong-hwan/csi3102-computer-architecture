#ifndef __ASSN1_STU_H__
#define __ASSN1_STU_H__

#include "assn1.h"
#include <iostream>

using namespace std;

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
    // cout << (*_output) << "\n" << endl;
}

template <size_t N> void SignedAdder<N>::advanceCycle()
{
    std::bitset<N> result(0);

    bool carry = false;

    for (size_t i = 0; i < N; ++i)
    {
        result[i] = (*_inputs[0])[i] ^ (*_inputs[1])[i] ^ carry;

        carry = ((*_inputs[0])[i] && (*_inputs[1])[i]) || (((*_inputs[0])[i] || (*_inputs[1])[i]) && carry);
    }

    for (size_t i = 0; i < N; ++i)
    {
        (*_output)[i] = result[i];
    }
}

template <size_t N> void SignedSubtractor<N>::advanceCycle()
{
    std::bitset<N> result(0);

    bool borrow = false;

    for (size_t i = 0; i < N; ++i)
    {
        result[i] = (*_inputs[0])[i] ^ (*_inputs[1])[i] ^ borrow;

        borrow = (!(*_inputs[0])[i] && (*_inputs[1])[i]) || (result[i] && borrow);
    }

    for (size_t i = 0; i < N; ++i)
    {
        (*_output)[i] = result[i];
    }
}

template <size_t N> void LogicalUnit<N>::advanceCycle()
{
    std::bitset<N> result(0);
    unsigned int peration_code = (*_operation).to_ulong();

    // cout << peration_code << endl;

    switch (peration_code)
    {
    // AND
    case 0:
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = (*_inputs[0])[i] & (*_inputs[1])[i];
        }
        break;
    // OR
    case 1:
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = (*_inputs[0])[i] | (*_inputs[1])[i];
        }
        break;
    // XOR
    case 2:
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = (*_inputs[0])[i] ^ (*_inputs[1])[i];
        }
        break;
    // NOT
    case 3:
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = !(*_inputs[0])[i];
        }
        break;
    // NAND
    case 4:
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = !((*_inputs[0])[i] & (*_inputs[1])[i]);
        }
        break;
    // NOR
    case 5:
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = !((*_inputs[0])[i] | (*_inputs[1])[i]);
        }
        break;
    // NOR
    case 6:
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = !((*_inputs[0])[i] ^ (*_inputs[1])[i]);
        }
        break;
    }

    for (size_t i = 0; i < N; ++i)
    {
        (*_output)[i] = result[i];
    }
}

template <size_t N, size_t M> void HashTable<N, M>::advanceCycle()
{
    // Extract index value
    unsigned int index_value = (*_index).to_ulong();

    // Check if isWrite signal is set
    bool is_write = (*_isWrite).to_ulong();

    if (is_write)
    {
        // Update the specified entry with input data
        _entries[index_value] = (*_input);
        // Output 0
        *_output = (unsigned long long)0;
    }
    else
    {
        // Output the value of the specified entry
        *_output = (_entries[index_value]);
    }
}

template <size_t N, size_t D> void DelayQueue<N, D>::advanceCycle()
{
    *_output = _entries[D - 1];

    // Push input to the queue if isPush signal is set
    if ((*_isPush).to_ulong())
    {
        for (size_t i = D - 1; i > 0; --i)
        {
            _entries[i] = (_entries[i - 1]);
        }

        _entries[0] = (*_input);
    }
    else
    {
        for (size_t i = D - 1; i > 0; --i)
        {
            _entries[i] = (_entries[i - 1]);
        }

        std::bitset<N> blank(0);
        _entries[0] = blank;
    }
}

#endif
