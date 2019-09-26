	.file	"3-1-1-incremento-atomico.c"
# GNU C11 (Ubuntu 7.4.0-1ubuntu1~18.04.1) version 7.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 7.4.0, GMP version 6.1.2, MPFR version 4.0.1, MPC version 1.1.0, isl version isl-0.19-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu 3-1-1-incremento-atomico.c
# -mtune=generic -march=x86-64 -fverbose-asm -fstack-protector-strong
# -Wformat -Wformat-security
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fasynchronous-unwind-tables -fauto-inc-dec -fchkp-check-incomplete-type
# -fchkp-check-read -fchkp-check-write -fchkp-instrument-calls
# -fchkp-narrow-bounds -fchkp-optimize -fchkp-store-bounds
# -fchkp-use-static-bounds -fchkp-use-static-const-bounds
# -fchkp-use-wrappers -fcommon -fdelete-null-pointer-checks
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
# -ffp-int-builtin-inexact -ffunction-cse -fgcse-lm -fgnu-runtime
# -fgnu-unique -fident -finline-atomics -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots -fivopts
# -fkeep-static-consts -fleading-underscore -flifetime-dse
# -flto-odr-type-merging -fmath-errno -fmerge-debug-strings -fpeephole
# -fplt -fprefetch-loop-arrays -freg-struct-return
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fssa-backprop -fstack-protector-strong
# -fstdarg-opt -fstrict-volatile-bitfields -fsync-libcalls -ftrapping-math
# -ftree-cselim -ftree-forwprop -ftree-loop-if-convert -ftree-loop-im
# -ftree-loop-ivcanon -ftree-loop-optimize -ftree-parallelize-loops=
# -ftree-phiprop -ftree-reassoc -ftree-scev-cprop -funit-at-a-time
# -funwind-tables -fverbose-asm -fzero-initialized-in-bss
# -m128bit-long-double -m64 -m80387 -malign-stringops
# -mavx256-split-unaligned-load -mavx256-split-unaligned-store
# -mfancy-math-387 -mfp-ret-in-387 -mfxsr -mglibc -mieee-fp
# -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone -msse -msse2
# -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.globl	contador
	.bss
	.align 4
	.type	contador, @object
	.size	contador, 4
contador:
	.zero	4
	.text
	.globl	incrementos
	.type	incrementos, @function
incrementos:
.LFB5:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# 3-1-1-incremento-atomico.c:13:     for(int i = 0; i < 100; i++)
	movl	$0, -4(%rbp)	#, i
	jmp	.L2	#
.L3:
# 3-1-1-incremento-atomico.c:14:         __sync_fetch_and_add(&contador, 1);
	lock addl	$1, contador(%rip)	#,,
# 3-1-1-incremento-atomico.c:13:     for(int i = 0; i < 100; i++)
	addl	$1, -4(%rbp)	#, i
.L2:
# 3-1-1-incremento-atomico.c:13:     for(int i = 0; i < 100; i++)
	cmpl	$99, -4(%rbp)	#, i
	jle	.L3	#,
# 3-1-1-incremento-atomico.c:15: }
	nop
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	incrementos, .-incrementos
	.section	.rodata
.LC0:
	.string	"Contador = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$56, %rsp	#,
	.cfi_offset 3, -24
# 3-1-1-incremento-atomico.c:17: int main(){
	movq	%fs:40, %rax	#, tmp134
	movq	%rax, -24(%rbp)	# tmp134, D.3900
	xorl	%eax, %eax	# tmp134
	movq	%rsp, %rax	#, tmp105
	movq	%rax, %rbx	# tmp105, saved_stack.2_18
# 3-1-1-incremento-atomico.c:18:     const int NUMTHREADS = 10;
	movl	$10, -44(%rbp)	#, NUMTHREADS
# 3-1-1-incremento-atomico.c:19:     pthread_t threads[NUMTHREADS];
	movl	-44(%rbp), %eax	# NUMTHREADS, tmp106
	cltq
	subq	$1, %rax	#, _2
	movq	%rax, -40(%rbp)	# _2, D.3888
	movl	-44(%rbp), %eax	# NUMTHREADS, tmp107
	cltq
	movq	%rax, %rsi	# _4, _5
	movl	$0, %edi	#, _5
	movl	-44(%rbp), %eax	# NUMTHREADS, tmp109
	cltq
	movq	%rax, %rdx	# _9, _10
	movl	$0, %ecx	#, _10
	movl	-44(%rbp), %eax	# NUMTHREADS, tmp110
	cltq
	salq	$3, %rax	#, _24
	leaq	7(%rax), %rdx	#, tmp111
	movl	$16, %eax	#, tmp132
	subq	$1, %rax	#, tmp112
	addq	%rdx, %rax	# tmp111, tmp113
	movl	$16, %ecx	#, tmp133
	movl	$0, %edx	#, tmp116
	divq	%rcx	# tmp133
	imulq	$16, %rax, %rax	#, tmp115, tmp117
	subq	%rax, %rsp	# tmp117,
	movq	%rsp, %rax	#, tmp118
	addq	$7, %rax	#, tmp119
	shrq	$3, %rax	#, tmp120
	salq	$3, %rax	#, tmp121
	movq	%rax, -32(%rbp)	# tmp121, threads.0
# 3-1-1-incremento-atomico.c:21:     for (int i = 0; i < NUMTHREADS; i++)
	movl	$0, -48(%rbp)	#, i
	jmp	.L5	#
.L6:
# 3-1-1-incremento-atomico.c:22:         pthread_create(&threads[i], NULL, incrementos, NULL);
	movl	-48(%rbp), %eax	# i, tmp123
	cltq
	leaq	0(,%rax,8), %rdx	#, tmp124
	movq	-32(%rbp), %rax	# threads.0, tmp125
	addq	%rdx, %rax	# tmp124, _14
	movl	$0, %ecx	#,
	leaq	incrementos(%rip), %rdx	#,
	movl	$0, %esi	#,
	movq	%rax, %rdi	# _14,
	call	pthread_create@PLT	#
# 3-1-1-incremento-atomico.c:21:     for (int i = 0; i < NUMTHREADS; i++)
	addl	$1, -48(%rbp)	#, i
.L5:
# 3-1-1-incremento-atomico.c:21:     for (int i = 0; i < NUMTHREADS; i++)
	movl	-48(%rbp), %eax	# i, tmp126
	cmpl	-44(%rbp), %eax	# NUMTHREADS, tmp126
	jl	.L6	#,
# 3-1-1-incremento-atomico.c:24:     for(int i = 0; i < NUMTHREADS; i++)
	movl	$0, -52(%rbp)	#, i
	jmp	.L7	#
.L8:
# 3-1-1-incremento-atomico.c:25:         pthread_join(threads[i], NULL);
	movq	-32(%rbp), %rax	# threads.0, tmp127
	movl	-52(%rbp), %edx	# i, tmp129
	movslq	%edx, %rdx	# tmp129, tmp128
	movq	(%rax,%rdx,8), %rax	# *threads.0_26, _15
	movl	$0, %esi	#,
	movq	%rax, %rdi	# _15,
	call	pthread_join@PLT	#
# 3-1-1-incremento-atomico.c:24:     for(int i = 0; i < NUMTHREADS; i++)
	addl	$1, -52(%rbp)	#, i
.L7:
# 3-1-1-incremento-atomico.c:24:     for(int i = 0; i < NUMTHREADS; i++)
	movl	-52(%rbp), %eax	# i, tmp130
	cmpl	-44(%rbp), %eax	# NUMTHREADS, tmp130
	jl	.L8	#,
# 3-1-1-incremento-atomico.c:27:     printf("Contador = %d\n", contador);
	movl	contador(%rip), %eax	# contador, contador.1_16
	movl	%eax, %esi	# contador.1_16,
	leaq	.LC0(%rip), %rdi	#,
	movl	$0, %eax	#,
	call	printf@PLT	#
# 3-1-1-incremento-atomico.c:29:     return 0;
	movl	$0, %eax	#, _30
	movq	%rbx, %rsp	# saved_stack.2_18,
# 3-1-1-incremento-atomico.c:30: }
	movq	-24(%rbp), %rcx	# D.3900, tmp135
	xorq	%fs:40, %rcx	#, tmp135
	je	.L10	#,
	call	__stack_chk_fail@PLT	#
.L10:
	movq	-8(%rbp), %rbx	#,
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
