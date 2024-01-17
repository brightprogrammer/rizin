// SPDX-FileCopyrightText: 2013-2015 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: LGPL-3.0-only

// instruction set : http://www.tachyonsoft.com/inst390m.htm

#include <rz_asm.h>
#include <rz_lib.h>

#include "cs_helper.h"

CAPSTONE_DEFINE_PLUGIN_FUNCTIONS(sysz);

static int sysz_disassemble(RzAsm *a, RzAsmOp *op, const ut8 *buf, int len) {
	CapstoneContext *ctx = (CapstoneContext *)a->plugin_data;
	int n, ret;
	ut64 off = a->pc;
	cs_insn *insn = NULL;
	cs_mode mode = CS_MODE_BIG_ENDIAN;
	op->size = 0;

	if (ctx->omode != mode) {
		cs_close(&ctx->handle);
		ctx->omode = -1;
	}
	if (!ctx->handle) {
		ret = cs_open(CS_ARCH_SYSZ, mode, &ctx->handle);
		if (ret) {
			return -1;
		}
		ctx->omode = mode;
		cs_option(ctx->handle, CS_OPT_DETAIL, CS_OPT_OFF);
	}

	n = cs_disasm(ctx->handle, (const ut8 *)buf, len, off, 1, &insn);
	if (n > 0) {
		if (insn->size > 0) {
			op->size = insn->size;
			char *buf_asm = rz_str_newf("%s%s%s",
				insn->mnemonic, insn->op_str[0] ? " " : "",
				insn->op_str);
			if (buf_asm) {
				char *ptrstr = strstr(buf_asm, "ptr ");
				if (ptrstr) {
					memmove(ptrstr, ptrstr + 4, strlen(ptrstr + 4) + 1);
				}
				rz_asm_op_set_asm(op, buf_asm);
				free(buf_asm);
			}
		}
		cs_free(insn, n);
	} else {
		rz_asm_op_set_asm(op, "invalid");
		return -1;
	}
	return op->size;
}

RzAsmPlugin rz_asm_plugin_sysz = {
	.name = "sysz",
	.desc = "SystemZ CPU disassembler",
	.license = "BSD",
	.arch = "sysz",
	.bits = 32 | 64,
	.endian = RZ_SYS_ENDIAN_BIG,
	.init = sysz_init,
	.fini = sysz_fini,
	.disassemble = &sysz_disassemble,
	.mnemonics = sysz_mnemonics,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_sysz,
	.version = RZ_VERSION
};
#endif
