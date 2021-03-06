{
	"runtime/jit: tail_call within bounds, prog once",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_3, 0),
	BPF_LD_MAP_FD(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_tail_call),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	},
	.fixup_prog1 = { 1 },
	.result = ACCEPT,
	.retval = 42,
},
{
	"runtime/jit: tail_call within bounds, prog loop",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_3, 1),
	BPF_LD_MAP_FD(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_tail_call),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	},
	.fixup_prog1 = { 1 },
	.result = ACCEPT,
	.retval = 41,
},
{
	"runtime/jit: tail_call within bounds, no prog",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_3, 2),
	BPF_LD_MAP_FD(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_tail_call),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	},
	.fixup_prog1 = { 1 },
	.result = ACCEPT,
	.retval = 1,
},
{
	"runtime/jit: tail_call out of bounds",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_3, 256),
	BPF_LD_MAP_FD(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_tail_call),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	},
	.fixup_prog1 = { 1 },
	.result = ACCEPT,
	.retval = 2,
},
{
	"runtime/jit: pass negative index to tail_call",
	.insns = {
	BPF_MOV64_IMM(BPF_REG_3, -1),
	BPF_LD_MAP_FD(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_tail_call),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	},
	.fixup_prog1 = { 1 },
	.result = ACCEPT,
	.retval = 2,
},
{
	"runtime/jit: pass > 32bit index to tail_call",
	.insns = {
	BPF_LD_IMM64(BPF_REG_3, 0x100000000ULL),
	BPF_LD_MAP_FD(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_tail_call),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	},
	.fixup_prog1 = { 2 },
	.result = ACCEPT,
	.retval = 42,
	/* Verifier rewrite for unpriv skips tail call here. */
	.retval_unpriv = 2,
},
