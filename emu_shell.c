#include <stdint.h>
#include <stdio.h>

typedef struct ConditionCodes {    
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
} State8080;

void UnimplementedInstruction(State8080* state)    
{    
    //pc will have advanced one, so undo that    
    printf ("Error: Unimplemented instruction\n");    
    exit(1);    
}

void Emulate8080Op(State8080* state)    
{    
    unsigned char *opcode = &state->memory[state->pc];

    switch(*opcode)    
    {    
        case 0x00: break;                   //NOP is easy!    
        case 0x01:                          //LXI   B,word    
                   state->c = opcode[1];    
                   state->b = opcode[2];    
                   state->pc += 2;                  //Advance 2 more bytes    
                   break;    
                   /*....*/    
        case 0x41: state->b = state->c; break;    //MOV B,C    
        case 0x42: state->b = state->d; break;    //MOV B,D    
        case 0x43: state->b = state->e; break;    //MOV B,E    
        /*******************   ADD   ***********************/
        case 0x80:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->b;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x81:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->c;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }

        case 0x82:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->d;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x83:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->e;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x84:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->h;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x85:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->l;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
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
                   }
        case 0x87:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->a;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
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
                   }
        case 0x89:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->c + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x8a:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->d + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x8b:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->e + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x8c:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->h + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x8d:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->l + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
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
                   }
        case 0x8f:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) state->a + (uint16_t) state->cc.cy;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0x90:
                   {
                       uint16_t answer = (uint16_t) state->a + ~((uint16_t) state->b) + 1;
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }
        case 0xC6:
                   {
                       uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1];
                       state->cc.z = ((answer & 0xff) == 0);
                       state->cc.s = ((answer & 0x80) != 0);
                       state->cc.cy = (answer > 0xff);
                       state->cc.p = Parity(answer & 0xff);
                       state->a = answer & 0xff;
                   }

        default:   UnimplementedInstruction(state); break;

    }    
    state->pc+=1;    
}

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
