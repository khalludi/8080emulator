#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "emu_shell.h"

uint8_t Parity(uint8_t num) {
    uint8_t ret = 0;
    for (uint8_t i = 0; i < 8; i++) {
        if ((num >> i & 0x01) == 1)
            ret += 1;
    }
    if (ret % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

void UnimplementedInstruction(State8080* state)
{
    //pc will have advanced one, so undo that
    printf ("Error: Unimplemented instruction %02x, %02x, %02x\n", state->memory[state->pc], state->memory[state->pc+1], state->memory[state->pc+2]);
    exit(1);
}

char numCycles(State8080* state) {
    char cycles = 0;
    unsigned char opcode = state->memory[state->pc];

    switch(opcode) {
        case 0x00:
        case 0x08:
        case 0x10:
        case 0x18:
        case 0x28:
        case 0x38:
        case 0xcb:
        case 0xd9:
        case 0xdd:
        case 0xed:
        case 0xfd:
        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85:
        case 0x87:
        case 0x88:
        case 0x89:
        case 0x8a:
        case 0x8b:
        case 0x8c:
        case 0x8d:
        case 0x8f:
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95:
        case 0x97:
        case 0x98:
        case 0x99:
        case 0x9a:
        case 0x9b:
        case 0x9c:
        case 0x9d:
        case 0x9f:
        case 0xa0:
        case 0xa1:
        case 0xa2:
        case 0xa3:
        case 0xa4:
        case 0xa5:
        case 0xa7:
        case 0xa8:
        case 0xa9:
        case 0xaa:
        case 0xab:
        case 0xac:
        case 0xad:
        case 0xaf:
        case 0xb0:
        case 0xb1:
        case 0xb2:
        case 0xb3:
        case 0xb4:
        case 0xb5:
        case 0xb7:
        case 0xb8:
        case 0xb9:
        case 0xba:
        case 0xbb:
        case 0xbc:
        case 0xbd:
        case 0xbf:
        case 0x07:
        case 0x0f:
        case 0x17:
        case 0x1f:
        case 0x27:
        case 0x2f:
        case 0x37:
        case 0x3f:
        case 0xeb:          // XCHG
        case 0xf3:
        case 0xfb:
            cycles = 4;
            break;

        case 0xe9:
        case 0xf9:
        case 0x03:          // INX
        case 0x13:
        case 0x23:
        case 0x33:
        case 0x40:          // MOV
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4a:
        case 0x4b:
        case 0x4c:
        case 0x4d:
        case 0x4f:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5a:
        case 0x5b:
        case 0x5c:
        case 0x5d:
        case 0x5f:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
        case 0x6f:
        case 0x78:
        case 0x79:
        case 0x7a:
        case 0x7b:
        case 0x7c:
        case 0x7d:
        case 0x7f:
        case 0x04:          // INR
        case 0x0c:
        case 0x14:
        case 0x1c:
        case 0x24:
        case 0x2c:
        case 0x3c:
        case 0x05:          // DCR
        case 0x0d:
        case 0x15:
        case 0x1d:
        case 0x25:
        case 0x2d:
        case 0x3d:
        case 0x0b:          // DCX
        case 0x1b:
        case 0x2b:
        case 0x3b:
            cycles = 5;
            break;

        case 0x02:          // STAX
        case 0x12:
        case 0x0a:          // LDAX
        case 0x1a:
        case 0x46:          // MOV M
        case 0x4e:
        case 0x56:
        case 0x5e:
        case 0x66:
        case 0x6e:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x77:
        case 0x7e:
        case 0x76:          // HLT
        case 0x06:          // MVI
        case 0x0e:
        case 0x16:
        case 0x1e:
        case 0x26:
        case 0x2e:
        case 0x3e:
        case 0x86:          // ADD - CMP M
        case 0x8e:
        case 0x96:
        case 0x9e:
        case 0xa6:
        case 0xae:
        case 0xb6:
        case 0xbe:
        case 0xc6:          // ADI
        case 0xce:          // ACI
        case 0xd6:          // SUI
        case 0xde:          // SBB
        case 0xe6:          // ANI
        case 0xee:          // XRI
        case 0xf6:          // ORI
        case 0xfe:          // CPI
            cycles = 7;
            break;

        case 0xc9:          // RET
        case 0xdb:          // IN
        case 0xd3:          // OUT
        case 0x01:          // LXI
        case 0x11:
        case 0x21:
        case 0x31:
        case 0xc1:          // POP
        case 0xd1:
        case 0xe1:
        case 0xf1:
        case 0x09:          // DAD
        case 0x19:
        case 0x29:
        case 0x39:
        case 0x36:          // MVI M
        case 0x34:          // INR/DCR M
        case 0x35:
        case 0xc2:          // JMP's
        case 0xc3:
        case 0xca:
        case 0xd2:
        case 0xda:
        case 0xe2:
        case 0xea:
        case 0xf2:
        case 0xfa:
            cycles = 10;
            break;

        case 0xc7:          // RST
        case 0xcf:
        case 0xd7:
        case 0xdf:
        case 0xe7:
        case 0xef:
        case 0xf7:
        case 0xff:
        case 0xc5:          // PUSH
        case 0xd5:
        case 0xe5:
        case 0xf5:
            cycles = 11;
            break;

        case 0x32:          // STA
        case 0x3a:          // LDA
            cycles = 13;
            break;

        case 0x22:          // SHLD
        case 0x2a:          // LHLD
            cycles = 16;
            break;

        case 0xcd:          // CALL
            cycles = 17;
            break;

        case 0xe3:          // XTHL
            cycles = 18;
            break;
    }

    if (opcode == 0xdc) {
        if (state->cc.cy == 1) {
            return 17;
        } else {
            return 11;
        }
    }


    if (opcode == 0xd4) {
        if (state->cc.cy == 0) {
            return 17;
        } else {
            return 11;
        }
    }

    if (opcode == 0xcc) {
        if (state->cc.z == 1) {
            return 17;
        } else {
            return 11;
        }
    }

    if (opcode == 0xc4) {
        if (state->cc.z == 0) {
            return 17;
        } else {
            return 11;
        }
    }

    if (opcode == 0xf4) {
        if (state->cc.p == 0) {
            return 17;
        } else {
            return 11;
        }
    }

    if (opcode == 0xfc) {
        if (state->cc.s == 1) {
            return 17;
        } else {
            return 11;
        }
    }

    if (opcode == 0xec) {
        if (state->cc.p == 1) {
            return 17;
        } else {
            return 11;
        }
    }

    if (opcode == 0xe4) {
        if (state->cc.p == 0) {
            return 17;
        } else {
            return 11;
        }
    }

    if (opcode == 0xd8) {
        if (state->cc.cy == 1) {
            return 11;
        } else {
            return 5;
        }
    }

    if (opcode == 0xd0) {
        if (state->cc.cy == 0) {
            return 11;
        } else {
            return 5;
        }
    }

    if (opcode == 0xc8) {
        if (state->cc.z == 1) {
            return 11;
        } else {
            return 5;
        }
    }

    if (opcode == 0xc0) {
        if (state->cc.z == 0) {
            return 11;
        } else {
            return 5;
        }
    }

    if (opcode == 0xf0) {
        if (state->cc.s == 0) {
            return 11;
        } else {
            return 5;
        }
    }

    if (opcode == 0xf8) {
        if (state->cc.s == 1) {
            return 11;
        } else {
            return 5;
        }
    }

    if (opcode == 0xe8) {
        if (state->cc.p == 1) {
            return 11;
        } else {
            return 5;
        }
    }

    if (opcode == 0xe0) {
        if (state->cc.p == 0) {
            return 11;
        } else {
            return 5;
        }
    }

    return cycles;
}


char Emulate8080Op(State8080* state)
{
    char cycles = 0;
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)
    {
        case 0x00: cycles = 4; break;                   //NOP is easy!
        case 0x01:                          //LXI   B,word
        {
            state->c = state->memory[state->pc+1];
            state->b = state->memory[state->pc+2];
            state->pc += 2;                  //advance 2 more bytes
            break;
        }
        case 0x02:                          // STAX B
        {
            uint16_t offset = ((uint16_t) state->b << 8) + (uint16_t) state->c;
            state->memory[offset] = state->a;
            cycles = 7;
            break;
        }
        case 0x03:                          // INX B
        {
            uint16_t answer = ((uint16_t) state->b << 8) + (uint16_t) state->c + 1;
            state->b = (answer >> 8) & 0xFF;
            state->c = answer & 0xFF;
            cycles = 5;
            break;
        }
        case 0x04:                          // INR B
        {
            uint8_t answer = state->b + 1;
            state->b = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->b & 0xf) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x05:                          // DCR B
        {
            uint8_t answer = state->b + ~(0x01) + 1;
            state->b = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->b & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x06:                          // MVI B,D8
        {
            state->b = opcode[1];
            state->pc += 1;
            cycles = 7;
            break;
        }
        case 0x07:                          // RLC
        {
            uint8_t tmp = (state->a & 0x80) >> 7;
            state->a = ((state->a << 1) | tmp) & 0x00ff;
            state->cc.cy = tmp;
            break;
        }
        case 0x08: cycles = 4; break;
        case 0x09:                          // DAD B
        {
            uint32_t answer = (((uint16_t) state->b << 8) | (uint16_t) state->c) + (((uint16_t) state->h << 8) | (uint16_t) state->l);
            state->cc.cy = answer > 0xFFFF;
            state->h = (answer >> 8) & 0xFF;
            state->l = answer & 0x00FF;
            cycles = 10;
            break;
        }
        case 0x0a:                          // LDAX B
        {
            uint16_t offset = ((uint16_t) state->b << 8) + (uint16_t) state->c;
            state->a = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x0b:                          // DCX B
        {
            uint16_t answer = ((uint16_t) state->b << 8) + (uint16_t) state->c;
            answer = answer + ~(0x0001) + 1;
            state->b = (answer >> 8) & 0xFF;
            state->c = answer & 0xFF;
            cycles = 5;
            break;
        }
        case 0x0c:                          // INR C
        {
            uint8_t answer = state->c + 1;
            state->c = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->c & 0xf) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x0d:                          // DCR C
        {
            uint8_t answer = state->c + ~(0x01) + 1;
            state->c = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->c & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x0e:                          // MVI C,D8
        {
            state->c = opcode[1];
            state->pc += 1;
            cycles = 7;
            break;
        }
        case 0x0f:                          // RRC
        {
            uint8_t tmp = state->a & 0x01;
            state->a = (state->a >> 1) | (tmp << 7);
            state->cc.cy = tmp;
            break;
        }
        case 0x10: cycles = 4; break;
        case 0x11:                          //LXI   D,word
        {
            state->e = opcode[1];
            state->d = opcode[2];
            state->pc += 2;                  //advance 2 more bytes
            cycles = 10;
            break;
        }
        case 0x12:                          // STAX D
        {
            uint16_t offset = ((uint16_t) state->d << 8) + (uint16_t) state->e;
            state->memory[offset] = state->a;
            cycles = 7;
            break;
        }
        case 0x13:                          // INX D
        {
            uint16_t answer = ((uint16_t) state->d << 8) + (uint16_t) state->e + 1;
            state->d = (answer >> 8) & 0xFF;
            state->e = answer & 0xFF;
            cycles = 5;
            break;
        }
        case 0x14:                          // INR D
        {
            uint8_t answer = state->d + 1;
            state->d = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->d & 0xf) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x15:                          // DCR D
        {
            uint8_t answer = state->d + ~(0x01) + 1;
            state->d = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->d & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x16:                          // MVI D,D8
        {
            state->d = opcode[1];
            state->pc += 1;
            cycles = 7;
            break;
        }
        case 0x17:
        {
            uint8_t tmp = (state->a & 0x80) >> 7;
            state->a = ((state->a << 1) & 0xff) | state->cc.cy;
            state->cc.cy = tmp;
            break;
        }                         // RAL
        case 0x18: cycles = 4; break;
        case 0x19:                          // DAD D
        {
            uint32_t answer = (((uint16_t) state->d << 8) + (uint16_t) state->e) + (((uint16_t) state->h << 8) + (uint16_t) state->l);
            state->cc.cy = answer > 0xFFFF;
            state->h = (answer >> 8) & 0xFF;
            state->l = answer & 0xFF;
            cycles = 10;
            break;
        }
        case 0x1a:                          // LDAX D
        {
            uint16_t offset = ((uint16_t) state->d << 8) + (uint16_t) state->e;
            state->a = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x1b:                          // DCX D
        {
            uint16_t answer = ((uint16_t) state->d << 8) + (uint16_t) state->e;
            answer = answer + ~(0x0001) + 1;
            state->d = (answer >> 8) & 0xFF;
            state->e = answer & 0xFF;
            cycles = 5;
            break;
        }
        case 0x1c:                          // INR E
        {
            uint8_t answer = state->e + 1;
            state->e = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->e & 0xf) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x1d:                          // DCR E
        {
            uint8_t answer = state->e + ~(0x01) + 1;
            state->e = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->e & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x1e:                          // MVI E,D8
        {
            state->e = opcode[1];
            state->pc += 1;
            cycles = 7;
            break;
        }
        case 0x1f:                          // RAR
        {
            uint8_t tmp = state->a & 0x01;
            state->a = (state->a >> 1) | (state->cc.cy << 7);
            state->cc.cy = tmp;
            break;
        }
        case 0x21:                          // LXI   H,word
        {
            state->l = opcode[1];
            state->h = opcode[2];
            state->pc += 2;                 //advance 2 more bytes
            break;
        }
        case 0x22:                          // SHLD
        {
            uint16_t ans = (state->memory[state->pc+2] << 8) | state->memory[state->pc+1];
            state->memory[ans] = state->l;
            state->memory[ans+1] = state->h;
            state->pc += 2;
            break;
        }
        case 0x23:                          // INX H
        {
            uint16_t answer = ((uint16_t) state->h << 8) + (uint16_t) state->l + 1;
            state->h = (answer >> 8) & 0xFF;
            state->l = answer & 0xFF;
            break;
        }
        case 0x24:                          // INR H
        {
            uint8_t answer = state->h + 1;
            state->h = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->h & 0xf) + 1 > 0xf);
            break;
        }
        case 0x25:                          // DCR H
        {
            uint8_t answer = state->h + ~(0x01) + 1;
            state->h = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->h & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x26:                          // MVI H,D8
        {
            state->h = opcode[1];
            state->pc += 1;
            cycles = 7;
            break;
        }
        case 0x27:                          // DAA
        {
            if (state->cc.ac || (state->a & 0xf) > 9) {
                state->cc.ac = ((state->a & 0xf) + 6 > 0xf);
                state->a += 6;
            }
            if (state->cc.cy || (state->a >> 4) > 9) {
                state->cc.cy = (((state->a & 0xf0) + 0x60) >> 4 > 0xf);
                state->a = (((state->a >> 4) + 6) << 4) | (state->a & 0xf);
                state->a = state->a & 0x00ff;
            }
        }
        case 0x28: cycles = 4; break;
        case 0x29:                          // DAD H
        {
            uint32_t answer = (((uint16_t) state->h << 8) + (uint16_t) state->l) + (((uint16_t) state->h << 8) + (uint16_t) state->l);
            state->cc.cy = answer > 0xFFFF;
            state->h = (answer >> 8) & 0xFF;
            state->l = answer & 0xFF;
            cycles = 10;
            break;
        }
        case 0x2a:                          // LHLD adr
        {
            uint16_t _pc = ((uint16_t) opcode[2] << 8) | opcode[1];
            state->l = state->memory[_pc];
            state->h = state->memory[_pc + 1];
            state->pc += 2;
            break;
        }
        case 0x2b:                          // DCX H
        {
            uint16_t answer = ((uint16_t) state->h << 8) + (uint16_t) state->l;
            answer = answer + ~(0x0001) + 1;
            state->h = (answer >> 8) & 0xFF;
            state->l = answer & 0xFF;
            cycles = 5;
            break;
        }
        case 0x2c:                          // INR L
        {
            uint8_t answer = state->l + 1;
            state->l = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->l & 0xf) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x2d:                          // DCR L
        {
            uint8_t answer = state->l + ~(0x01) + 1;
            state->l = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->l & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x2e:                          // MVI L,D8
        {
            state->l = opcode[1];
            state->pc += 1;
            break;
        }
        case 0x2f:                          // CMA
        {
            state->a = (uint8_t) ((~state->a) & 0x00ff);
            break;
        }
        case 0x31:                          // LXI SP,D16
        {
            state->sp = ((uint16_t) opcode[2] << 8) | opcode[1];
            state->pc += 2;                  //advance 2 more bytes
            break;
        }
        case 0x32:                          // STA adr
        {
            uint16_t addr = ((uint16_t) opcode[2] << 8) | opcode[1];
            state->memory[addr] = state->a;
            state->pc += 2;
            cycles = 13;
            break;
        }
        case 0x33:                          // INX SP
        state->sp = (state->sp + 1) & 0xFFFF;
        cycles = 5;
        break;
        case 0x34:                          // INR M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | (state->l);
            uint16_t answer = state->memory[offset] + 1;
            state->memory[offset] = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer & 0xFF);
            state->cc.ac = ((state->memory[offset] & 0xf) + 1 > 0xf);
            cycles = 10;
            break;
        }
        case 0x35:                          // DCR M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | (state -> l);
            uint16_t answer = state->memory[offset] + ~(0x01) + 1;
            state->memory[offset] = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->memory[offset] & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 10;
            break;
        }
        case 0x36:                          // MVI M,D8
        {
            uint16_t offset = ((uint16_t) state->h << 8) | (state -> l);
            state->memory[offset] = opcode[1];
            state->pc += 1;
            cycles = 10;
            break;
        }
        case 0x37:                          // STC
        {
            state->cc.cy = 1;
            break;
        }
        case 0x39:                          // DAD SP
        {
            uint32_t answer = state->sp + (((uint16_t) state->h << 8) + (uint16_t) state->l);
            state->cc.cy = answer > 0xFFFF;
            state->h = (answer >> 8) & 0xFF;
            state->l = answer & 0xFF;
            break;
        }
        case 0x3a:                          // LDA adr
        {
            uint16_t addr = ((uint16_t) opcode[2] << 8) | opcode[1];
            state->a = state->memory[addr];
            state->pc += 2;
            break;
        }
        case 0x3b:                          // DCX SP
        {
            state->sp = (state->sp + ~(0x0001) + 1) & 0xFFFF;
            break;
        }
        case 0x3c:                          // INR A
        {
            uint8_t answer = state->a + 1;
            state->a = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->a & 0xf) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x3d:                          // DCR A
        {
            uint8_t answer = state->a + ~(0x01) + 1;
            state->a = answer;
            state->cc.z = (answer == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.ac = ((state->a & 0xf) + ~(0x1) + 1 > 0xf);
            cycles = 5;
            break;
        }
        case 0x3e:                          // MVI A,D8
        {
            state->a = opcode[1];
            state->pc += 1;
            cycles = 7;
            break;
        }
        case 0x3f: state->cc.cy = ~(state->cc.cy); break; // CMC
        case 0x41: state->b = state->c; break;    //MOV B,C
        case 0x42: state->b = state->d; break;    //MOV B,D
        case 0x43: state->b = state->e; break;    //MOV B,E
        case 0x44: state->b = state->h; break;
        case 0x45: state->b = state->l; break;
        case 0x46:                          // MOV B,M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->b = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x47: state->b = state->a; break;      // MOV B,A
        case 0x48: state->c = state->b; break;
        case 0x49: state->c = state->c; break;
        case 0x4a: state->c = state->d; break;
        case 0x4b: state->c = state->e; break;
        case 0x4c: state->c = state->h; break;
        case 0x4d: state->c = state->l; break;
        case 0x4e:                          // MOV C,M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->c = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x4f: state->c = state->a; break;
        case 0x50: state->d = state->b; break;
        case 0x51: state->d = state->c; break;
        case 0x52: state->d = state->d; break;
        case 0x53: state->d = state->e; break;
        case 0x54: state->d = state->h; break;
        case 0x55: state->d = state->l; break;
        case 0x56:                          // MOV D,M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->d = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x57: state->d = state->a; cycles = 5; break;
        case 0x58: state->e = state->b; break;
        case 0x59: state->e = state->c; break;
        case 0x5a: state->e = state->d; break;
        case 0x5b: state->e = state->e; break;
        case 0x5c: state->e = state->h; break;
        case 0x5d: state->e = state->l; break;
        case 0x5e:                          // MOV E,M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->e = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x5f: state->e = state->a; break;
        case 0x60: state->h = state->b; break;
        case 0x61: state->h = state->c; break;                  // MOV H,C
        case 0x62: state->h = state->d; break;
        case 0x63: state->h = state->e; break;
        case 0x64: state->h = state->h; break;
        case 0x65: state->h = state->l; break;
        case 0x66:                          // MOV H,M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->h = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x67: state->h = state->a; break;
        case 0x68: state->l = state->b; break;
        case 0x69: state->l = state->c; break;
        case 0x6a: state->l = state->d; break;
        case 0x6b: state->l = state->e; break;
        case 0x6c: state->l = state->h; break;
        case 0x6d: state->l = state->l; break;
        case 0x6e:                          // MOV L,M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->l = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x6f: state->l = state->a; break;      // MOV L,A
        case 0x70:                          // MOV M,B
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->memory[offset] = state->b;
            cycles = 7;
            break;
        }
        case 0x71:                          // MOV M,C
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->memory[offset] = state->c;
            cycles = 7;
            break;
        }
        case 0x72:                          // MOV M,D
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->memory[offset] = state->d;
            cycles = 7;
            break;
        }
        case 0x73:                          // MOV M,E
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->memory[offset] = state->e;
            cycles = 7;
            break;
        }
        case 0x74:                          // MOV M,H
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->memory[offset] = state->h;
            cycles = 7;
            break;
        }
        case 0x75:                          // MOV M,L
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->memory[offset] = state->l;
            cycles = 7;
            break;
        }
        case 0x77:                          // MOV M,A
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->memory[offset] = state->a;
            cycles = 7;
            break;
        }
        case 0x78: state->a = state->b; cycles = 5; break;
        case 0x79: state->a = state->c; cycles = 5; break;
        case 0x7a: state->a = state->d; cycles = 5; break;      // MOV A,D
        case 0x7b: state->a = state->e; cycles = 5; break;      // MOV A,E
        case 0x7c: state->a = state->h; cycles = 5; break;      // MOV A,H
        case 0x7d: state->a = state->l; cycles = 5; break;
        case 0x7e:                          // MOV A,M
        {
            uint16_t offset = ((uint16_t) state->h << 8) | state->l;
            state->a = state->memory[offset];
            cycles = 7;
            break;
        }
        case 0x7f: state->a = state->a; break;
        /*******************   ADD   ***********************/
        case 0x80:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->b;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->b & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x81:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->c;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->c & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }

        case 0x82:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->d;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->d & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x83:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->e;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->e & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x84:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->h;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->h & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x85:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->l;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->l & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x86:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->memory[offset];
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->memory[offset] & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 7;
            break;
        }
        case 0x87:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->a;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->a & 0xf) > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        /*******************   ADC   ********************/
        case 0x88:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->b + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->b & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x89:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->c + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->c & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x8a:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->d + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->d & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x8b:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->e + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->e & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x8c:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->h + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->h & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x8d:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->l + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->l & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x8e:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->memory[offset] + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->memory[offset] & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 7;
            break;
        }
        case 0x8f:
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->a + (uint16_t) state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (state->a & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        /*******************   SUB   ********************/
        case 0x90:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->b) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->b & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x91:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->c) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->c & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x92:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->d) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->d & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x93:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->e) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->e & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x94:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->h) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->h & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x95:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->l) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->l & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x96:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a + ~(state->memory[offset]) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->memory[offset] & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 7;
            break;
        }
        case 0x97:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->a) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(state->a & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        /*******************   SBB   ********************/
        case 0x98:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy  + (uint16_t) state->b) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->b & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x99:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy  + (uint16_t) state->c) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->c & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x9a:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy  + (uint16_t) state->d) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->d & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x9b:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy  + (uint16_t) state->e) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->e & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x9c:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy  + (uint16_t) state->h) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->h & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x9d:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy  + (uint16_t) state->l) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->l & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0x9e:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy + state->memory[offset]) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->memory[offset] & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 7;
            break;
        }
        case 0x9f:
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->cc.cy  + (uint16_t) state->a) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + state->cc.cy + ~(state->a & 0xf) + 1 > 0xf);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        /*******************   ANA   ********************/
        case 0xa0:
        {
            uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->b);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xa1:
        {
            uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->c);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xa2:
        {
            uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->d);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xa3:
        {
            uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->e);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xa4:
        {
            uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->h);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xa5:
        {
            uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->l);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xa6:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = ((uint16_t) state->a) & (state->memory[offset]);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 7;
            break;
        }
        case 0xa7:
        {
            uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->a);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        /*******************   XRA   ********************/
        case 0xa8:
        {
            uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->b);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xa9:
        {
            uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->c);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xaa:
        {
            uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->d);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xab:
        {
            uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->e);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xac:
        {
            uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->h);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xad:
        {
            uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->l);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xae:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = ((uint16_t) state->a) ^ (state->memory[offset]);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 7;
            break;
        }
        case 0xaf:
        {
            uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->a);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        /*******************   ORA   ********************/
        case 0xb0:
        {
            uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->b);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xb1:
        {
            uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->c);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xb2:
        {
            uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->d);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xb3:
        {
            uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->e);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xb4:
        {
            uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->h);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xb5:
        {
            uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->l);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        case 0xb6:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = ((uint16_t) state->a) | (state->memory[offset]);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 7;
            break;
        }
        case 0xb7:
        {
            uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->a);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = 0;
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = 0;
            state->a = answer & 0xff;
            cycles = 4;
            break;
        }
        /*******************   CMP   ********************/
        case 0xb8:
        {
            uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->b) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->b & 0xf) + 1 > 0xf);
            cycles = 4;
            break;
        }
        case 0xb9:
        {
            uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->c) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->c & 0xf) + 1 > 0xf);
            cycles = 4;
            break;
        }
        case 0xba:
        {
            uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->d) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->d & 0xf) + 1 > 0xf);
            cycles = 4;
            break;
        }
        case 0xbb:
        {
            uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->e) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->e & 0xf) + 1 > 0xf);
            cycles = 4;
            break;
        }
        case 0xbc:
        {
            uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->h) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->h & 0xf) + 1 > 0xf);
            cycles = 4;
            break;
        }
        case 0xbd:
        {
            uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->l) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->l & 0xf) + 1 > 0xf);
            cycles = 4;
            break;
        }
        case 0xbe:
        {
            uint16_t offset = (state->h<<8) | (state->l);
            uint16_t answer = ((uint16_t) state->a) + ~(state->memory[offset]) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->memory[offset] & 0xf) + 1 > 0xf);
            cycles = 7;
            break;
        }
        case 0xbf:
        {
            uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->a);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = ~(answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a) + ~(state->a & 0xf) + 1 > 0xf);
            cycles = 4;
            break;
        }
        case 0xc0:                          // RNZ
        {
            if (state->cc.z == 0) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
                cycles = 11;
            } else {
                cycles = 5;
            }
            break;
        }
        case 0xc1:                          // POP B
        {
            state->c = state->memory[state->sp];
            state->b = state->memory[state->sp+1];
            state->sp += 2;
            break;
        }
        case 0xc2:                          // JNZ adr
        {
            if (state->cc.z == 0) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc = state->pc - 1;
            } else {
                state->pc += 2;
            }
            cycles = 10;
            break;
        }
        case 0xc3:                          // JMP adr
        {
            state->pc = (opcode[2] << 8) | opcode[1];
            state->pc = state->pc - 1;
            cycles = 10;
            break;
        }
        case 0xc4:                          // CNZ adr
        {
            if (state->cc.z == 0)
            {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            }
            else {
                state->pc += 2;
            }
            break;
        }
        case 0xc5:                          // PUSH B
        {
            state->sp -= 2;
            state->memory[state->sp] = state->c;
            state->memory[state->sp+1] = state->b;
            break;
        }
        case 0xc6:                          // ADI D8
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (opcode[1] & 0xf) > 0xf);
            state->a = answer & 0xff;
            state->pc += 1;
            break;
        }
        case 0xc8:                          // RZ
        {
            if (state->cc.z == 1) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
                cycles = 11;
            } else {
                cycles = 5;
            }
            break;
        }
        case 0xc9:                          // RET
        {
            uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
            //printf("END INTERRUPT!\n");
            state->pc = _pc;
            state->sp += 2;
            cycles = 10;
            break;
        }
        case 0xca:                          // JZ adr
        {
            if (state->cc.z == 1) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc -= 1;
            } else {
                state->pc += 2;
            }
            cycles = 10;
            break;
        }
        case 0xcc:                          // CZ adr
        {
            if (state->cc.z == 1) {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            } else {
                state->pc += 2;
            }
            break;
        }
        case 0xcd:                          // CALL adr
        {
            if (state->cpu_diag) {
                if (5 ==  ((opcode[2] << 8) | opcode[1]))
                {
                    if (state->c == 9)
                    {
                        uint16_t offset = (state->d<<8) | (state->e);
                        uint8_t *str = &state->memory[offset+3];  //skip the prefix bytes
                        while (*str != '$')
                            printf("%c", *str++);
                        printf("\n");
                    }
                    else if (state->c == 2)
                    {
                        //saw this in the inspected code, never saw it called
                        printf ("print char routine called\n");
                    }
                    break;
                }
                else if (0 == ((opcode[2] << 8) | opcode[1]))
                {
                    exit(0); break;
                }
            }

            uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
            uint16_t _pc2 = state->pc + 2;
            state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
            state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
            state->sp = (uint16_t) (state->sp - 2);
            state->pc = _pc - 1;
            break;
        }
        case 0xce:                          // ADI D8
        {
            uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1] + state->cc.cy;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + (opcode[1] & 0xf) + state->cc.cy > 0xf);
            state->a = answer & 0xff;
            state->pc += 1;
            break;
        }
        case 0xd0:                          // RNC
        {
            if (state->cc.cy == 0) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
                cycles = 11;
            } else {
                cycles = 5;
            }
            break;
        }
        case 0xd1:                          // POP D
        {
            state->e = state->memory[state->sp];
            state->d = state->memory[state->sp+1];
            state->sp += 2;
            cycles = 10;
            break;
        }
        case 0xd2:                          // JNC adr
        {
            if (state->cc.cy == 0) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc -= 1;
                cycles = 11;
            } else {
                state->pc += 2;
                cycles = 5;
            }
            break;
        }
        case 0xd3:                          // OUT D8
        {
            state->pc += 1;
            cycles = 10;
            break;
        }
        case 0xd4:                          // CNC adr
        {
            if (state->cc.cy == 0)
            {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            }
            else {
                state->pc += 2;
            }
            break;
        }
        case 0xd5:                          // PUSH D
        {
            state->sp -= 2;
            state->memory[state->sp] = state->e;
            state->memory[state->sp+1] = state->d;
            cycles = 11;
            break;
        }
        case 0xd6:                          // SUI D8
        {
            uint16_t answer = state->a + ~(opcode[1]) + 1;
            state->a =  (uint8_t) (answer & 0xff);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.cy = (answer > 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(opcode[1] & 0xf) + 1 > 0xf);
            state->pc += 1;
            break;
        }
        case 0xd8:                          // RC
        {
            if (state->cc.cy == 1) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
                cycles = 11;
            } else {
                cycles = 5;
            }
            break;
        }
        case 0xda:                          // JC adr
        {
            if (state->cc.cy == 1) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc -= 1;
            } else {
                state->pc += 2;
            }
            break;
        }
        case 0xdc:                          // CC adr
        {
            if (state->cc.cy == 1)
            {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            }
            else {
                state->pc += 2;
            }
            break;
        }
        case 0xde:                          // SBI D8
        {
            uint16_t answer = state->a + ~(((opcode[2] << 8) | opcode[1]) + state->cc.cy) + 1;
            state->a = (uint8_t) (answer & 0xff);
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.p = Parity(answer);
            state->cc.cy = (answer > 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(((opcode[2] << 8) | opcode[1]) + state->cc.cy & 0xf) + 1 > 0xf);
            state->pc += 1;
            break;
        }
        case 0xe0:                          // RPO
        {
            if (state->cc.p == 0) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
            }
            break;
        }
        case 0xe1:                          // POP H
        {
            state->l = state->memory[state->sp];
            state->h = state->memory[state->sp+1];
            state->sp += 2;
            cycles = 10;
            break;
        }
        case 0xe2:                          // JPO adr
        {
            if (state->cc.p == 0) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc -= 1;
            } else {
                state->pc += 2;
            }
            break;
        }
        case 0xe3:                          // XTHL
        {
            uint16_t ans = ((state->h << 8) | state->l) - 1;
            state->l = state->memory[state->sp];
            state->h = state->memory[state->sp+1];
            state->memory[state->sp] = ans & 0xff;
            state->memory[state->sp+1] = (ans & 0xff00) >> 8;
            break;
        }
        case 0xe4:                          // CPO adr
        {
            if (state->cc.p == 0)
            {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            }
            else {
                state->pc += 2;
            }
            break;
        }
        case 0xe5:                          // PUSH H
        {
            state->sp -= 2;
            state->memory[state->sp] = state->l;
            state->memory[state->sp+1] = state->h;
            break;
        }
        case 0xe6:                          // ANI D8
        {
            uint16_t answer = state->a & opcode[1];
            state->cc.cy = 0;
            state->cc.z = ((answer & 0x00ff) == 0x00);
            state->cc.p = Parity(answer);
            state->cc.s = ((answer & 0x80) != 0);
            state->pc += 1;
            state->a = (uint8_t) answer & 0xff;
            cycles = 7;
            break;
        }
        case 0xe8:                          // RPE
        {
            if (state->cc.p == 1) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
                cycles = 11;
            } else {
                cycles = 5;
            }
            break;
        }
        case 0xe9:                          // PCHL
        {
            state->pc = (state->h << 8) | state->l;
            state->pc -= 1;
            break;
        }
        case 0xea:                          // JPE adr
        {
            if (state->cc.p == 1) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc -= 1;
            } else {
                state->pc += 2;
            }
            break;
        }
        case 0xeb:                          // XCHG
        {
            uint8_t tmp1 = state->e;
            uint8_t tmp2 = state->d;
            state->e = state->l;
            state->d = state->h;
            state->l = tmp1;
            state->h = tmp2;
            cycles = 4;
            break;
        }
        case 0xec:                          // CPE adr
        {
            if (state->cc.p == 1)
            {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            }
            else {
                state->pc += 2;
            }
            break;
        }
        case 0xee:                          // XRI D8
        {
            uint16_t answer = state->a ^ state->memory[state->pc+1];
            state->cc.cy = 0;
            state->cc.z = ((answer & 0x00ff) == 0x00);
            state->cc.p = Parity(answer);
            state->cc.s = ((answer & 0x80) != 0);
            state->pc += 1;
            state->a = (uint8_t) answer & 0xff;
            break;
        }
        case 0xf0:                          // RP
        {
            if (state->cc.p == 1) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
            } else {
            }
            break;
        }
        case 0xf1:                          // POP PSW
        {
            uint8_t answer = state->memory[state->sp];
            state->cc.s = ((answer & 0x80) >> 7) == 0x01;
            state->cc.z = ((answer & 0x40) >> 6) == 0x01;
            state->cc.ac = ((answer & 0x10) >> 4) == 0x01;
            state->cc.p = ((answer & 0x04) >> 2) == 0x01;
            state->cc.cy = (answer & 0x01) == 0x01;
            state->a = state->memory[state->sp+1];
            state->sp += 2;
            cycles = 10;
            break;
        }
        case 0xf2:                          // JP adr
        {
            if (state->cc.s == 0) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc -= 1;
            } else {
                state->pc += 2;
            }
            break;
        }
        case 0xf4:                          // CP adr
        {
            if (state->cc.p == 1)
            {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            }
            else {
                state->pc += 2;
            }
            break;
        }
        case 0xf5:                          // PUSH PSW
        {
            uint8_t answer = 0x02 | state->cc.cy;
            answer = answer | (state->cc.p << 2);
            answer = answer | (state->cc.ac << 4);
            answer = answer | (state->cc.z << 6);
            answer = answer | (state->cc.s << 7);
            state->memory[state->sp-1] = state->a;
            state->memory[state->sp-2] = answer;
            state->sp -= 2;
            cycles = 11;
            break;
        }
        case 0xf6:                          // ORI
        {
            uint16_t answer = state->a | opcode[1];
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->a = (uint8_t) answer & 0xff;
            state->pc += 1;
            break;
        }
        case 0xf8:                          // RM
        {
            if (state->cc.s == 1) {
                uint16_t _pc = (state->memory[state->sp+1] << 8) | state->memory[state->sp];
                state->pc = _pc;
                state->sp += 2;
            }
            break;
        }
        case 0xf9:                          // SPHL
        {
            state->memory[state->sp+1] = state->h;
            state->memory[state->sp] = state->l;
            break;
        }
        case 0xfa:                          // JM adr
        {
            if (state->cc.s == 1) {
                state->pc = (opcode[2] << 8) | opcode[1];
                state->pc -= 1;
            } else {
                state->pc += 2;
            }
            break;
        }
        case 0xfb: state->int_enable = 1; break; // EI
        case 0xfc:                          // CM adr
        {
            if (state->cc.s == 1)
            {
                uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                uint16_t _pc2 = state->pc + 2;
                state->memory[state->sp-1] = (uint8_t) (_pc2 >> 8);
                state->memory[state->sp-2] = (uint8_t) (_pc2 & 0xff);
                state->sp = (uint16_t) (state->sp - 2);
                state->pc = _pc - 1;
            }
            else {
                state->pc += 2;
            }
            break;
        }
        case 0xfe:                          // CPI D8
        {
            uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->memory[state->pc+1]) + 1;
            state->cc.z = ((answer & 0x00ff) == 0);
            state->cc.s = ((answer & 0x80) != 0);
            state->cc.cy = (answer > 0xff);
            state->cc.p = Parity(answer & 0xff);
            state->cc.ac = ((state->a & 0xf) + ~(opcode[1] & 0xf) + 1 > 0xf);
            state->pc += 1;
            cycles = 7;
            break;
        }

        default:   UnimplementedInstruction(state); break;

    }
    state->pc+=1;
    return cycles;
}
