// SPDX-FileCopyrightText: 2018 thestr4ng3r <info@florianmaerkl.de>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef PIC_BASELINE_H
#define PIC_BASELINE_H

#include <rz_types.h>
#include <rz_asm.h>

typedef enum {
	PIC_BASELINE_OP_ARGS_NONE = 0,
	PIC_BASELINE_OP_ARGS_2F,
	PIC_BASELINE_OP_ARGS_3F,
	PIC_BASELINE_OP_ARGS_3K,
	PIC_BASELINE_OP_ARGS_1D_5F,
	PIC_BASELINE_OP_ARGS_5F,
	PIC_BASELINE_OP_ARGS_3B_5F,
	PIC_BASELINE_OP_ARGS_8K,
	PIC_BASELINE_OP_ARGS_9K
} PicBaselineOpArgs;

#define PIC_BASELINE_OP_ARGS_2F_MASK_F    0x3
#define PIC_BASELINE_OP_ARGS_3F_MASK_F    0x7
#define PIC_BASELINE_OP_ARGS_3K_MASK_K    0x7
#define PIC_BASELINE_OP_ARGS_1D_5F_MASK_D (1 << 5)
#define PIC_BASELINE_OP_ARGS_1D_5F_MASK_F 0x1f
#define PIC_BASELINE_OP_ARGS_5F_MASK_F    0x1f
#define PIC_BASELINE_OP_ARGS_3B_5F_MASK_B (0x7 << 5)
#define PIC_BASELINE_OP_ARGS_3B_5F_MASK_F 0x1f
#define PIC_BASELINE_OP_ARGS_8K_MASK_K    0xff
#define PIC_BASELINE_OP_ARGS_9K_MASK_K    0x1ff

typedef struct _pic_baseline_op {
	const char *mnemonic;
	PicBaselineOpArgs args;
} PicBaselineOpInfo;

typedef enum {
	PIC_BASELINE_OPCODE_NOP = 0,
	PIC_BASELINE_OPCODE_OPTION,
	PIC_BASELINE_OPCODE_SLEEP,
	PIC_BASELINE_OPCODE_CLRWDT,
	PIC_BASELINE_OPCODE_TRIS,
	PIC_BASELINE_OPCODE_MOVLB,
	PIC_BASELINE_OPCODE_RETURN,
	PIC_BASELINE_OPCODE_RETFIE,
	PIC_BASELINE_OPCODE_MOVWF,
	PIC_BASELINE_OPCODE_CLRF,
	PIC_BASELINE_OPCODE_CLRW,
	PIC_BASELINE_OPCODE_SUBWF,
	PIC_BASELINE_OPCODE_DECF,
	PIC_BASELINE_OPCODE_IORWF,
	PIC_BASELINE_OPCODE_ANDWF,
	PIC_BASELINE_OPCODE_XORWF,
	PIC_BASELINE_OPCODE_ADDWF,
	PIC_BASELINE_OPCODE_MOVF,
	PIC_BASELINE_OPCODE_COMF,
	PIC_BASELINE_OPCODE_INCF,
	PIC_BASELINE_OPCODE_DECFSZ,
	PIC_BASELINE_OPCODE_RRF,
	PIC_BASELINE_OPCODE_RLF,
	PIC_BASELINE_OPCODE_SWAPF,
	PIC_BASELINE_OPCODE_INCFSZ,
	PIC_BASELINE_OPCODE_BCF,
	PIC_BASELINE_OPCODE_BSF,
	PIC_BASELINE_OPCODE_BTFSC,
	PIC_BASELINE_OPCODE_BTFSS,
	PIC_BASELINE_OPCODE_RETLW,
	PIC_BASELINE_OPCODE_CALL,
	PIC_BASELINE_OPCODE_GOTO,
	PIC_BASELINE_OPCODE_MOVLW,
	PIC_BASELINE_OPCODE_IORLW,
	PIC_BASELINE_OPCODE_ANDLW,
	PIC_BASELINE_OPCODE_XORLW,
	PIC_BASELINE_OPCODE_INVALID
} PicBaselineOpcode;

PicBaselineOpcode pic_baseline_get_opcode(ut16 instr);
PicBaselineOpArgs pic_baseline_get_opargs(PicBaselineOpcode opcode);
const PicBaselineOpInfo *pic_baseline_get_op_info(PicBaselineOpcode opcode);
int pic_baseline_disassemble(RzAsmOp *op, char *opbuf, const ut8 *b, int l);

#endif // PIC_BASELINE_H
