#ifndef __ALU_H__
#define __ALU_H__

#include "DigitalCircuit.h"

#include <cassert>
#include <iostream>
using namespace std;

class ALU : public DigitalCircuit
{

  public:
    ALU(const Wire<4> *iALUControl, const Wire<32> *iInput0, const Wire<32> *iInput1, Wire<32> *oOutput, Wire<1> *oZero)
        : DigitalCircuit("ALU")
    {
        _iALUControl = iALUControl;
        _iInput0 = iInput0;
        _iInput1 = iInput1;
        _oOutput = oOutput;
        _oZero = oZero;
    }

    virtual void advanceCycle()
    {
        // Read the inputs
        std::bitset<32> input0 = *_iInput0;
        std::bitset<32> input1 = *_iInput1;
        std::bitset<32> result;
        uint16_t control = static_cast<uint16_t>(_iALUControl->to_ulong());

        // Perform the operation based on the control signal
        switch (control)
        {
        case 0b0000: // AND
            result = input0 & input1;
            break;
        case 0b0001: // OR
            result = input0 | input1;
            break;
        case 0b0010: // ADD
            result = std::bitset<32>(input0.to_ulong() + input1.to_ulong());
            break;
        case 0b0110: // SUBTRACT
            result = std::bitset<32>(input0.to_ulong() - input1.to_ulong());
            break;
        case 0b0111: // SET ON LESS THAN
            result = (input0.to_ulong() < input1.to_ulong()) ? std::bitset<32>(1) : std::bitset<32>(0);
            break;
        case 0b1100: // NOR
            result = ~(input0 | input1);
            break;
        default:
            assert(false && "Invalid ALU control signal");
        }

        // cout << "\n" << input0 << endl;
        // cout << input1 << endl;
        // cout << control << "\n" << endl;
        // cout << result << "\n" << endl;

        // Set the output wire
        *_oOutput = result;

        // Set the zero flag
        _oZero->set(0, result.to_ulong() == 0 ? 1 : 0);
    }

  private:
    const Wire<4> *_iALUControl;
    const Wire<32> *_iInput0;
    const Wire<32> *_iInput1;
    Wire<32> *_oOutput;
    Wire<1> *_oZero;
};

#endif
