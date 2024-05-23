#ifndef __ALU_CONTROL_H__
#define __ALU_CONTROL_H__

#include "DigitalCircuit.h"

#include <cassert>
#include <iostream>
using namespace std;

class ALUControl : public DigitalCircuit
{

  public:
    ALUControl(const Wire<2> *iALUOp, const Wire<6> *iFunct, Wire<4> *oOperation) : DigitalCircuit("ALUControl")
    {
        _iALUOp = iALUOp;
        _iFunct = iFunct;
        _oOperation = oOperation;
    }

    virtual void advanceCycle()
    {
        // std::bitset<2> ALUOp = *_iALUOp;
        // std::bitset<6> Funct = *_iFunct;
        uint8_t ALUOp = static_cast<uint8_t>(_iALUOp->to_ulong());
        uint8_t Funct = static_cast<uint8_t>(_iFunct->to_ulong());
        std::bitset<4> ALUControlSignal;

        // cout << "\n" << ALUOp << endl;
        // cout << Funct << "\n" << endl;

        switch (ALUOp)
        {
        case 0b00:                     // LW, SW (Add)
            ALUControlSignal = 0b0010; // ADD
            break;
        case 0b01:                     // BEQ (Subtract)
            ALUControlSignal = 0b0110; // SUBTRACT
            break;
        case 0b10: // R-type instructions
            switch (Funct & 0b001111)
            {                              // Mask the upper 2 bits to handle xx0000, xx0010, etc.
            case 0b0000:                   // ADD (xx0000)
                ALUControlSignal = 0b0010; // ADD
                break;
            case 0b0010:                   // SUBTRACT (xx0010)
                ALUControlSignal = 0b0110; // SUBTRACT
                break;
            case 0b0100:                   // AND (xx0100)
                ALUControlSignal = 0b0000; // AND
                break;
            case 0b0101:                   // OR (xx0101)
                ALUControlSignal = 0b0001; // OR
                break;
            case 0b1010:                   // SET ON LESS THAN (xx1010)
                ALUControlSignal = 0b0111; // SLT
                break;
            default:
                assert(false && "Invalid Funct field for R-type instruction");
            }
            break;
        default:
            assert(false && "Invalid ALUOp");
        }

        *_oOperation = ALUControlSignal;
    }

  private:
    const Wire<2> *_iALUOp;
    const Wire<6> *_iFunct;
    Wire<4> *_oOperation;
};

#endif
