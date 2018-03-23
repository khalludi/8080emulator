#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "emu_shell.h"

/* typedef struct ConditionCodes {    
   uint8_t    z:1;    
   uint8_t    s:1;    
   uint8_t    p:1;    
   uint8_t    cy:1;    
   uint8_t    ac:1;    
   uint8_t    pad:3;    
   } ConditionCodes;

   typedef struct State8080 {    
   uint8_t    a;    
   uint8_t    b;    
   uint8_t    c;    
   uint8_t    d;    
   uint8_t    e;    
   uint8_t    h;    
   uint8_t    l;    
   uint16_t    sp;    
   uint16_t    pc;    
   uint8_t     *memory;    
   struct      ConditionCodes      cc;    
   uint8_t     int_enable;    
   } State8080; */

uint8_t Parity(uint8_t num) {
    uint8_t ret = 0;
    for (uint8_t i = 0; i < 8; i++) {
        ret += num & (1 << i);
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
    
    return cycles;

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
}


char Emulate8080Op(State8080* state)    
{   
    char cycles = 0;
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)    
    {    
        case 0x00: cycles = 4; break;                   //NOP is easy!    
        case 0x01:                          //LXI   B,word    
                   state->c = state->memory[state->pc+1];    
                   state->b = state->memory[state->pc+2];    
                   state->pc += 2;                  //advance 2 more bytes    
                   cycles = 10;
                   break;    
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
                       cycles = 5;
                       break;
                   }
        case 0x06:                          // MVI B,D8
                   state->b = opcode[1];
                   state->pc += 1;
                   cycles = 7;
                   break;
        case 0x07:                          // RLC
                   state->cc.cy = state->a & 0x80;
                   state->a = (state->a << 1) + state->cc.cy;
                   cycles = 4;
                   break;
        case 0x08: cycles = 4; break;
        case 0x09:                          // DAD B
                   {
                       uint16_t answer = (((uint16_t) state->b << 8) + (uint16_t) state->c) + (((uint16_t) state->h << 8) + (uint16_t) state->l);
                       state->cc.cy = answer > 0xFFFF;
                       state->h = (answer >> 8) & 0xFF;
                       state->l = answer & 0xFF;
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
                       cycles = 5;
                       break;
                   }
        case 0x0e:                          // MVI C,D8
                   state->c = opcode[1];
                   state->pc += 1;
                   cycles = 7;
                   break;
        case 0x0f:                          // RRC
                   state->cc.cy = state->a & 0x01;
                   state->a = (state->a >> 1) + (state->cc.cy << 7);
                   cycles = 4;
                   break;
        case 0x10: cycles = 4; break;
        case 0x11:                          //LXI   D,word    
                   state->e = opcode[1];    
                   state->d = opcode[2];    
                   state->pc += 2;                  //advance 2 more bytes    
                   cycles = 10;
                   break;    
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
                       cycles = 5;
                       break;
                   }
        case 0x16:                          // MVI D,D8
                   state->d = opcode[1];
                   state->pc += 1;
                   cycles = 7;
                   break;
        case 0x17:                          // RAL
                   cycles = 4;
                   break;
        case 0x18: cycles = 4; break;
        case 0x19:                          // DAD D
                   {
                       uint16_t answer = (((uint16_t) state->d << 8) + (uint16_t) state->e) + (((uint16_t) state->h << 8) + (uint16_t) state->l);
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
                       cycles = 5;
                       break;
                   }
        case 0x1e:                          // MVI E,D8
                   state->e = opcode[1];
                   state->pc += 1;
                   cycles = 7;
                   break;
        case 0x21:                          //LXI   H,word    
                   state->l = opcode[1];    
                   state->h = opcode[2];    
                   state->pc += 2;                  //advance 2 more bytes    
                   cycles = 10;
                   break;    
        case 0x23:                          // INX H
                   {
                       uint16_t answer = ((uint16_t) state->h << 8) + (uint16_t) state->l + 1;
                       state->h = (answer >> 8) & 0xFF;
                       state->l = answer & 0xFF;
                       cycles = 5;
                       break;
                   }
        case 0x24:                          // INR H
                   {
                       uint8_t answer = state->h + 1;
                       state->h = answer;
                       state->cc.z = (answer == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.p = Parity(answer);
                       cycles = 5;
                       break;
                   }
        case 0x25:                          // DCR H
                   {
                       uint8_t answer = state->h + ~(0x01) + 1;
                       state->h = answer;
                       state->cc.z = (answer == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.p = Parity(answer);
                       cycles = 5;
                       break;
                   }
        case 0x26:                          // MVI H,D8
                   state->h = opcode[1];
                   state->pc += 1;
                   cycles = 7;
                   break;
        case 0x28: cycles = 4; break;
        case 0x29:                          // DAD H
                   {
                       uint16_t answer = (((uint16_t) state->h << 8) + (uint16_t) state->l) + (((uint16_t) state->h << 8) + (uint16_t) state->l);
                       state->cc.cy = answer > 0xFFFF;
                       state->h = (answer >> 8) & 0xFF;
                       state->l = answer & 0xFF;
                       cycles = 10;
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
                       cycles = 5;
                       break;
                   }
        case 0x2e:                          // MVI L,D8
                   state->l = opcode[1];
                   state->pc += 1;
                   cycles = 7;
                   break;
        case 0x31:                          //LXI   SP,word (D16)   
                   state->sp = ((uint16_t) opcode[2] << 8) | opcode[1];    
                   state->pc += 2;                  //advance 2 more bytes    
                   cycles = 10;
                   break;    
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
        case 0x3a:                          // LDA adr
                   {
                       uint16_t addr = ((uint16_t) opcode[2] << 8) | opcode[1];
                       state->a = state->memory[addr];
                       state->pc += 2;
                       cycles = 13;
                       break;
                   }
        case 0x3b:                          // DCX SP
                   state->sp = (state->sp + ~(0x0001) + 1) & 0xFFFF;
                   cycles = 5;
                   break;
        case 0x3c:                          // INR A
                   {
                       uint8_t answer = state->a + 1;
                       state->a = answer;
                       state->cc.z = (answer == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.p = Parity(answer);
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
                       cycles = 5;
                       break;
                   }
        case 0x3e:                          // MVI A,D8
                   state->a = opcode[1];
                   state->pc += 1;
                   cycles = 7;
                   break;
        case 0x41: state->b = state->c; cycles = 5; break;    //MOV B,C    
        case 0x42: state->b = state->d; cycles = 5; break;    //MOV B,D    
        case 0x43: state->b = state->e; cycles = 5; break;    //MOV B,E
        case 0x46:                          // MOV B,M
                   {
                       uint16_t offset = ((uint16_t) state->h << 8) | state->l;
                       state->b = state->memory[offset];
                       cycles = 7;
                       break;
                   }
        case 0x4f: state->c = state->a; cycles = 5; break;
        case 0x56:                          // MOV D,M
                   {
                       uint16_t offset = ((uint16_t) state->h << 8) | state->l;
                       state->d = state->memory[offset];
                       cycles = 7;
                       break;
                   }
        case 0x57: state->d = state->a; cycles = 5; break;
        case 0x5e:                          // MOV E,M
                   {
                       uint16_t offset = ((uint16_t) state->h << 8) | state->l;
                       state->e = state->memory[offset];
                       cycles = 7;
                       break;
                   }
        case 0x5f: state->e = state->a; cycles = 5; break;
        case 0x66:                          // MOV H,M
                   {
                       uint16_t offset = ((uint16_t) state->h << 8) | state->l;
                       state->h = state->memory[offset];
                       cycles = 7;
                       break;
                   }
        case 0x67: state->h = state->a; cycles = 5; break;
        case 0x6f: state->l = state->a; cycles = 5; break;      // MOV L,A
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
                   /*******************   ADD   ***********************/
        case 0x80:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->b;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x81:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->c;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }

        case 0x82:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->d;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x83:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->e;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x84:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->h;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x85:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->l;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x86:
                   {
                       uint16_t offset = (state->h<<8) | (state->l);
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->memory[offset];
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 7;
                       break;
                   }
        case 0x87:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->a;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
                   /*******************   ADC   ********************/
        case 0x88:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->b + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x89:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->c + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x8a:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->d + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x8b:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->e + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x8c:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->h + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x8d:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->l + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x8e:
                   {
                       uint16_t offset = (state->h<<8) | (state->l);
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->memory[offset] + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 7;
                       break;
                   }
        case 0x8f:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->a + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
                   /*******************   SUB   ********************/
        case 0x90:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->b) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x91:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->c) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x92:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->d) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x93:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->e) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x94:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->h) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x95:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->l) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x96:
                   {
                       uint16_t offset = (state->h<<8) | (state->l); 
                       uint16_t answer = (uint16_t) state->a + ~(state->memory[offset]) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 7;
                       break;
                   }
        case 0x97:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->a) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
                   /*******************   SBB   ********************/
        case 0x98:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy  + ~((uint16_t) state->b) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x99:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy  + ~((uint16_t) state->c) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x9a:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy  + ~((uint16_t) state->d) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x9b:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy  + ~((uint16_t) state->e) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x9c:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy  + ~((uint16_t) state->h) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x9d:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy  + ~((uint16_t) state->l) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0x9e:
                   {
                       uint16_t offset = (state->h<<8) | (state->l); 
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy + ~(state->memory[offset]) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 7;
                       break;
                   }
        case 0x9f:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->cc.cy  + ~((uint16_t) state->a) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
                   /*******************   ANA   ********************/
        case 0xa0:
                   {
                       uint16_t answer = ((uint16_t) state->a) & ((uint16_t) state->b);
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
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
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xa9:
                   {
                       uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->c);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xaa:
                   {
                       uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->d);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xab:
                   {
                       uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->e);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xac:
                   {
                       uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->h);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xad:
                   {
                       uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->l);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xae:
                   {
                       uint16_t offset = (state->h<<8) | (state->l); 
                       uint16_t answer = ((uint16_t) state->a) ^ (state->memory[offset]);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 7;
                       break;
                   }
        case 0xaf:
                   {
                       uint16_t answer = ((uint16_t) state->a) ^ ((uint16_t) state->a);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
                   /*******************   ORA   ********************/
        case 0xb0:
                   {
                       uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->b);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xb1:
                   {
                       uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->c);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xb2:
                   {
                       uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->d);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xb3:
                   {
                       uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->e);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xb4:
                   {
                       uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->h);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xb5:
                   {
                       uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->l);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
        case 0xb6:
                   {
                       uint16_t offset = (state->h<<8) | (state->l); 
                       uint16_t answer = ((uint16_t) state->a) | (state->memory[offset]);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 7;
                       break;
                   }
        case 0xb7:
                   {
                       uint16_t answer = ((uint16_t) state->a) | ((uint16_t) state->a);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = 0;
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       cycles = 4;
                       break;
                   }
                   /*******************   CMP   ********************/
        case 0xb8:
                   {
                       uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->b) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 4;
                       break;
                   }
        case 0xb9:
                   {
                       uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->c) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 4;
                       break;
                   }
        case 0xba:
                   {
                       uint16_t answer = ((uint16_t) state->a) + ((uint16_t) state->d) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 4;
                       break;
                   }
        case 0xbb:
                   {
                       uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->e) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 4;
                       break;
                   }
        case 0xbc:
                   {
                       uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->h) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 4;
                       break;
                   }
        case 0xbd:
                   {
                       uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->l) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 4;
                       break;
                   }
        case 0xbe:
                   {
                       uint16_t offset = (state->h<<8) | (state->l); 
                       uint16_t answer = ((uint16_t) state->a) + ~(state->memory[offset]) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 7;
                       break;
                   }
        case 0xbf:
                   {
                       uint16_t answer = ((uint16_t) state->a) + ~((uint16_t) state->a);
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = ~(answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       cycles = 4;
                       break;
                   }
        case 0xc0:                          // RNZ
                   {
                       if (state->cc.z == 0) {
                           uint16_t _pc = (state->memory[state->sp] << 8) | state->memory[state->sp+1];
                           state->pc = _pc+2;
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
                       cycles = 10;
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
        case 0xc5:                          // PUSH B
                   {
                       state->sp -= 2;
                       state->memory[state->sp] = state->c;
                       state->memory[state->sp+1] = state->b;
                       cycles = 11;
                       break;
                   }
        case 0xc6:                          // ADI D8
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                       state->pc += 1;
                       cycles = 7;
                       break;
                   }
        case 0xc8:                          // RZ
                   {
                       if (state->cc.z == 1) {
                           uint16_t _pc = (state->memory[state->sp] << 8) | state->memory[state->sp+1];
                           state->pc = _pc+2;
                           state->sp += 2;
                           cycles = 11;
                       } else {
                           cycles = 5;
                       }
                       break;
                   }
        case 0xc9:                          // RET
                   {
                       uint16_t _pc = (state->memory[state->sp] << 8) | state->memory[state->sp+1];
                       state->pc = _pc+2;
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
        case 0xcd:                          // CALL adr
                   {
                       uint16_t _pc = ((state->memory[state->pc+2]) << 8) | (state->memory[state->pc+1]);
                       state->memory[state->sp-1] = (uint8_t) (state->pc & 0xff);
                       state->memory[state->sp-2] = (uint8_t) (state->pc >> 8);
                       state->sp = (uint16_t) (state->sp - 2);
                       state->pc = _pc - 1;
                       cycles = 17;
                       break;
                   }
        case 0xd0:                          // RNC
                   {
                       if (state->cc.cy == 0) {
                           uint16_t _pc = (state->memory[state->sp] << 8) | state->memory[state->sp+1];
                           state->pc = _pc+2;
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
        case 0xd3:                          // OUT D8
                   {
                       state->pc += 1;
                       cycles = 10;
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
                       uint8_t answer = state->a + ~(state->memory[state->pc+1]) + 1;
                       state->a = answer;
                       state->cc.z = (answer == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.p = Parity(answer);
                       state->pc += 1;
                       cycles = 7;
                       break;
                   }
        case 0xd8:                          // RC
                   {
                       if (state->cc.cy == 1) {
                           uint16_t _pc = (state->memory[state->sp] << 8) | state->memory[state->sp+1];
                           state->pc = _pc+2;
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
                           cycles = 11;
                       } else {
                           state->pc += 2;
                           cycles = 5;
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
        case 0xe5:                          // PUSH H
                   {
                       state->sp -= 2;
                       state->memory[state->sp] = state->l;
                       state->memory[state->sp+1] = state->h;
                       cycles = 11;
                       break;
                   }
        case 0xe6:                          // ANI D8
                   {
                       uint16_t answer = state->a & state->memory[state->pc+1];
                       state->cc.cy = 0;
                       state->cc.z = ((state->a & 0x0F) == 0x00);
                       state->cc.p = Parity(answer);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->pc += 1;
                       state->a = answer;
                       cycles = 7;
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
        case 0xfb: state->int_enable = 1; cycles = 4; break; // EI
        case 0xfe:                          // CPI D8
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->memory[state->pc+1]) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->pc += 1;
                       cycles = 7;
                       break;
                   }

        default:   UnimplementedInstruction(state); break;

    }    
    state->pc+=1;
    return cycles;
    // print out processor state 
    /*printf("\tC=%d,P=%d,S=%d,Z=%d\n", state->cc.cy, state->cc.p,
            state->cc.s, state->cc.z);
    printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x PC %04x SP %04x\n",
            state->a, state->b, state->c, state->d,
            state->e, state->h, state->l, state->pc, state->sp);
    */
}
/*
int _main() {
    printf("IT COMPILED !!!\n");
    // Create a state
    State8080 state;

    // Load argument into memory
    FILE *fileptr = fopen("../res/invaders","rb");
    fseek(fileptr, 0, SEEK_END);
    long filelen = ftell(fileptr);
    rewind(fileptr);

    char *buffer = (char *)malloc((filelen+1)*sizeof(char)); 
    fread(buffer, filelen, 1, fileptr);
    state.memory = (uint8_t *) buffer;
    // Call Emulate
    // Repeat emulator
    Emulate8080Op(&state);

    return 0;
}
*/





