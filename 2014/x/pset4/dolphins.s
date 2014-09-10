	.file	"dolphins.c"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	$0, -4(%ebp)
	movl	%ecx, -8(%ebp)
	movl	%eax, -12(%ebp)
	cmpl	$2, -8(%ebp)
	jne	.LBB0_14
# BB#1:
	movl	-12(%ebp), %eax
	movl	4(%eax), %eax
	subl	$16, %esp
	movl	%eax, (%esp)
	calll	atoi
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	cmpl	$0, -16(%ebp)
	jle	.LBB0_13
# BB#2:
	movl	-16(%ebp), %eax
	movl	%esp, %ecx
	movl	%ecx, -20(%ebp)
	leal	15(,%eax,4), %eax
	andl	$-16, %eax
	movl	%esp, %ecx
	subl	%eax, %ecx
	movl	%ecx, %esp
	movl	$1, -24(%ebp)
	movl	$0, -28(%ebp)
	movl	%ecx, -40(%ebp)         # 4-byte Spill
.LBB0_3:                                # =>This Inner Loop Header: Depth=1
	movl	-28(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jge	.LBB0_6
# BB#4:                                 #   in Loop: Header=BB0_3 Depth=1
	calll	getAge
	movl	-28(%ebp), %ecx
	movl	-40(%ebp), %edx         # 4-byte Reload
	movl	%eax, (%edx,%ecx,4)
# BB#5:                                 #   in Loop: Header=BB0_3 Depth=1
	movl	-28(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -28(%ebp)
	jmp	.LBB0_3
.LBB0_6:
	movl	$0, -32(%ebp)
.LBB0_7:                                # =>This Inner Loop Header: Depth=1
	movl	-32(%ebp), %eax
	cmpl	-16(%ebp), %eax
	jge	.LBB0_12
# BB#8:                                 #   in Loop: Header=BB0_7 Depth=1
	movl	-24(%ebp), %eax
	movl	-32(%ebp), %ecx
	movl	-40(%ebp), %edx         # 4-byte Reload
	movl	(%edx,%ecx,4), %ecx
	cmpl	(%ecx), %eax
	jge	.LBB0_10
# BB#9:                                 #   in Loop: Header=BB0_7 Depth=1
	movl	-32(%ebp), %eax
	movl	-40(%ebp), %ecx         # 4-byte Reload
	movl	(%ecx,%eax,4), %eax
	movl	(%eax), %eax
	movl	%eax, -24(%ebp)
.LBB0_10:                               #   in Loop: Header=BB0_7 Depth=1
	jmp	.LBB0_11
.LBB0_11:                               #   in Loop: Header=BB0_7 Depth=1
	movl	-32(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -32(%ebp)
	jmp	.LBB0_7
.LBB0_12:
	leal	.L.str, %eax
	movl	-24(%ebp), %ecx
	subl	$16, %esp
	movl	%eax, (%esp)
	movl	%ecx, 4(%esp)
	calll	printf
	addl	$16, %esp
	movl	%eax, -4(%ebp)
	movl	$1, -36(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, %esp
	jmp	.LBB0_14
.LBB0_13:
	movl	$1, -4(%ebp)
.LBB0_14:
	movl	-4(%ebp), %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
.Ltmp0:
	.size	main, .Ltmp0-main

	.globl	getAge
	.align	16, 0x90
	.type	getAge,@function
getAge:                                 # @getAge
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	leal	.L.str1, %eax
	movl	%eax, (%esp)
	calll	printf
	movl	$4, %ecx
	movl	$4, (%esp)
	movl	%eax, -8(%ebp)          # 4-byte Spill
	movl	%ecx, -12(%ebp)         # 4-byte Spill
	calll	malloc
	movl	%eax, -4(%ebp)
	calll	GetInt
	movl	-4(%ebp), %ecx
	movl	%eax, (%ecx)
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	movl	-4(%ebp), %eax
	cmpl	$0, (%eax)
	jge	.LBB1_3
# BB#2:                                 #   in Loop: Header=BB1_1 Depth=1
	calll	GetInt
	movl	-4(%ebp), %ecx
	movl	%eax, (%ecx)
	jmp	.LBB1_1
.LBB1_3:
	movl	-4(%ebp), %eax
	addl	$24, %esp
	popl	%ebp
	ret
.Ltmp1:
	.size	getAge, .Ltmp1-getAge

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "The oldest dolphin is %d \n"
	.size	.L.str, 27

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "Please enter an age for this dolphin \n"
	.size	.L.str1, 39


	.section	".note.GNU-stack","",@progbits
