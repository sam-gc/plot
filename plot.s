	.file	"main.c"
	.globl	blank_function
	.data
	.align 32
	.type	blank_function, @object
	.size	blank_function, 68
blank_function:
	.long	0
	.long	-1071382528
	.long	0
	.long	1076101120
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.byte	0
	.zero	3
	.long	600
	.long	400
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	0
	.byte	-1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.zero	2
	.text
	.globl	initSDL
	.type	initSDL, @function
initSDL:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$136, %esp
	movl	8(%ebp), %eax
	movl	%eax, -108(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	leal	-92(%ebp), %eax
	movl	$1953459280, (%eax)
	movw	$8250, 4(%eax)
	movb	$0, 6(%eax)
	movl	-108(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	strcat
	movl	$32, (%esp)
	call	SDL_Init
	movl	$0, 4(%esp)
	leal	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_WM_SetCaption
	movl	$0, 12(%esp)
	movl	$32, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_SetVideoMode
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L3
	call	__stack_chk_fail
.L3:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	initSDL, .-initSDL
	.globl	makeColor
	.type	makeColor, @function
makeColor:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$28, %esp
	movl	12(%ebp), %ecx
	movl	16(%ebp), %edx
	movl	20(%ebp), %eax
	movb	%cl, -20(%ebp)
	movb	%dl, -24(%ebp)
	movb	%al, -28(%ebp)
	movzbl	-20(%ebp), %eax
	movb	%al, -3(%ebp)
	movzbl	-24(%ebp), %eax
	movb	%al, -2(%ebp)
	movzbl	-28(%ebp), %eax
	movb	%al, -1(%ebp)
	movl	8(%ebp), %eax
	movzwl	-3(%ebp), %edx
	movw	%dx, (%eax)
	movzbl	-1(%ebp), %edx
	movb	%dl, 2(%eax)
	movl	8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE6:
	.size	makeColor, .-makeColor
	.section	.rodata
.LC0:
	.string	"--range"
.LC1:
	.string	"%lf,%lf"
.LC2:
	.string	"--bounds"
.LC3:
	.string	"--noaxes"
.LC4:
	.string	"--plotcolor"
.LC5:
	.string	"%hhu,%hhu,%hhu"
.LC6:
	.string	"--axescolor"
.LC7:
	.string	"--backcolor"
.LC8:
	.string	"--window"
.LC9:
	.string	"%d,%d"
	.text
	.globl	parseArgs
	.type	parseArgs, @function
parseArgs:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$156, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	leal	-96(%ebp), %edx
	movl	$blank_function, %ebx
	movl	$17, %eax
	movl	%edx, %edi
	movl	%ebx, %esi
	movl	%eax, %ecx
	rep movsl
	movl	16(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -56(%ebp)
	movl	$0, -108(%ebp)
	jmp	.L7
.L17:
	movl	-108(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -104(%ebp)
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	-108(%ebp), %eax
	jle	.L8
	movl	-108(%ebp), %eax
	addl	$1, %eax
	leal	0(,%eax,4), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	jmp	.L9
.L8:
	movl	$0, %eax
.L9:
	movl	%eax, -100(%ebp)
	movl	$.LC0, 4(%esp)
	movl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L10
	leal	-96(%ebp), %eax
	addl	$8, %eax
	movl	%eax, 12(%esp)
	leal	-96(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$.LC1, 4(%esp)
	movl	-100(%ebp), %eax
	movl	%eax, (%esp)
	call	__isoc99_sscanf
	jmp	.L11
.L10:
	movl	$.LC2, 4(%esp)
	movl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L12
	leal	-96(%ebp), %eax
	addl	$16, %eax
	movl	%eax, 12(%esp)
	leal	-96(%ebp), %eax
	addl	$24, %eax
	movl	%eax, 8(%esp)
	movl	$.LC1, 4(%esp)
	movl	-100(%ebp), %eax
	movl	%eax, (%esp)
	call	__isoc99_sscanf
	movb	$1, -31(%ebp)
	jmp	.L11
.L12:
	movl	$.LC3, 4(%esp)
	movl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L13
	movb	$1, -52(%ebp)
	jmp	.L11
.L13:
	movl	$.LC4, 4(%esp)
	movl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L14
	leal	-96(%ebp), %eax
	addl	$58, %eax
	movl	%eax, 16(%esp)
	leal	-96(%ebp), %eax
	addl	$57, %eax
	movl	%eax, 12(%esp)
	leal	-96(%ebp), %eax
	addl	$56, %eax
	movl	%eax, 8(%esp)
	movl	$.LC5, 4(%esp)
	movl	-100(%ebp), %eax
	movl	%eax, (%esp)
	call	__isoc99_sscanf
	jmp	.L11
.L14:
	movl	$.LC6, 4(%esp)
	movl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L15
	leal	-96(%ebp), %eax
	addl	$61, %eax
	movl	%eax, 16(%esp)
	leal	-96(%ebp), %eax
	addl	$60, %eax
	movl	%eax, 12(%esp)
	leal	-96(%ebp), %eax
	addl	$59, %eax
	movl	%eax, 8(%esp)
	movl	$.LC5, 4(%esp)
	movl	-100(%ebp), %eax
	movl	%eax, (%esp)
	call	__isoc99_sscanf
	jmp	.L11
.L15:
	movl	$.LC7, 4(%esp)
	movl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L16
	leal	-96(%ebp), %eax
	addl	$64, %eax
	movl	%eax, 16(%esp)
	leal	-96(%ebp), %eax
	addl	$63, %eax
	movl	%eax, 12(%esp)
	leal	-96(%ebp), %eax
	addl	$62, %eax
	movl	%eax, 8(%esp)
	movl	$.LC5, 4(%esp)
	movl	-100(%ebp), %eax
	movl	%eax, (%esp)
	call	__isoc99_sscanf
	jmp	.L11
.L16:
	movl	$.LC8, 4(%esp)
	movl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L11
	leal	-96(%ebp), %eax
	addl	$52, %eax
	movl	%eax, 12(%esp)
	leal	-96(%ebp), %eax
	addl	$48, %eax
	movl	%eax, 8(%esp)
	movl	$.LC9, 4(%esp)
	movl	-100(%ebp), %eax
	movl	%eax, (%esp)
	call	__isoc99_sscanf
.L11:
	addl	$1, -108(%ebp)
.L7:
	movl	-108(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	.L17
	fldl	-88(%ebp)
	fldl	-96(%ebp)
	fsubrp	%st, %st(1)
	movl	-48(%ebp), %eax
	movl	%eax, -124(%ebp)
	fildl	-124(%ebp)
	fdivrp	%st, %st(1)
	fstpl	-64(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, %edx
	leal	-96(%ebp), %ebx
	movl	$17, %eax
	movl	%edx, %edi
	movl	%ebx, %esi
	movl	%eax, %ecx
	rep movsl
	movl	8(%ebp), %eax
	addl	$156, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE7:
	.size	parseArgs, .-parseArgs
	.globl	plotFunction
	.type	plotFunction, @function
plotFunction:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$116, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	fldl	24(%eax)
	fldz
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L40
.L35:
	movl	8(%ebp), %eax
	fldl	24(%eax)
	fchs
	jmp	.L22
.L40:
	fldz
.L22:
	fstpl	-64(%ebp)
	movl	8(%ebp), %eax
	fldl	(%eax)
	fldz
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L23
.L36:
	movl	8(%ebp), %eax
	fldl	8(%eax)
	fldz
	fxch	%st(1)
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L23
.L37:
	movl	8(%ebp), %eax
	fldl	(%eax)
	fchs
	movl	8(%ebp), %eax
	fldl	8(%eax)
	movl	8(%ebp), %eax
	fldl	(%eax)
	fsubrp	%st, %st(1)
	fdivrp	%st, %st(1)
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	movl	%eax, -100(%ebp)
	fildl	-100(%ebp)
	fmulp	%st, %st(1)
	jmp	.L26
.L23:
	fld1
	fchs
.L26:
	fstpl	-56(%ebp)
	movl	8(%ebp), %eax
	fldl	24(%eax)
	fldz
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L27
.L38:
	movl	8(%ebp), %eax
	fldl	16(%eax)
	fldz
	fxch	%st(1)
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L27
.L39:
	movl	8(%ebp), %eax
	fldl	16(%eax)
	movl	8(%ebp), %eax
	fldl	16(%eax)
	movl	8(%ebp), %eax
	fldl	24(%eax)
	fsubrp	%st, %st(1)
	fdivrp	%st, %st(1)
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	movl	%eax, -100(%ebp)
	fildl	-100(%ebp)
	fmulp	%st, %st(1)
	jmp	.L30
.L27:
	fld1
	fchs
.L30:
	fstpl	-48(%ebp)
	movl	8(%ebp), %eax
	fldl	16(%eax)
	movl	8(%ebp), %eax
	fldl	24(%eax)
	fsubrp	%st, %st(1)
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	movl	%eax, -100(%ebp)
	fildl	-100(%ebp)
	fdivrp	%st, %st(1)
	fstpl	-40(%ebp)
	movl	8(%ebp), %eax
	movzwl	62(%eax), %edx
	movw	%dx, -81(%ebp)
	movzbl	64(%eax), %eax
	movb	%al, -79(%ebp)
	movl	8(%ebp), %eax
	movzwl	56(%eax), %edx
	movw	%dx, -78(%ebp)
	movzbl	58(%eax), %eax
	movb	%al, -76(%ebp)
	movl	8(%ebp), %eax
	movzwl	59(%eax), %edx
	movw	%dx, -75(%ebp)
	movzbl	61(%eax), %eax
	movb	%al, -73(%ebp)
	movw	$0, -32(%ebp)
	movw	$0, -30(%ebp)
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	movw	%ax, -28(%ebp)
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	movw	%ax, -26(%ebp)
	movzbl	-79(%ebp), %eax
	movzbl	%al, %ebx
	movzbl	-80(%ebp), %eax
	movzbl	%al, %ecx
	movzbl	-81(%ebp), %eax
	movzbl	%al, %edx
	movl	16(%ebp), %eax
	movl	4(%eax), %eax
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	SDL_MapRGB
	movl	%eax, 8(%esp)
	leal	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_FillRect
	movl	$0, -72(%ebp)
	jmp	.L31
.L32:
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	movl	%eax, -100(%ebp)
	fildl	-100(%ebp)
	movl	-72(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	fldl	(%eax)
	fdivl	-40(%ebp)
	fldl	-64(%ebp)
	fdivl	-40(%ebp)
	faddp	%st, %st(1)
	fsubrp	%st, %st(1)
	fnstcw	-90(%ebp)
	movzwl	-90(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -92(%ebp)
	fldcw	-92(%ebp)
	fistpl	-68(%ebp)
	fldcw	-90(%ebp)
	movl	-72(%ebp), %eax
	movw	%ax, -16(%ebp)
	movl	-68(%ebp), %eax
	movw	%ax, -14(%ebp)
	movw	$1, -12(%ebp)
	movw	$1, -10(%ebp)
	movzbl	-76(%ebp), %eax
	movzbl	%al, %ebx
	movzbl	-77(%ebp), %eax
	movzbl	%al, %ecx
	movzbl	-78(%ebp), %eax
	movzbl	%al, %edx
	movl	16(%ebp), %eax
	movl	4(%eax), %eax
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	SDL_MapRGB
	movl	%eax, 8(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_FillRect
	addl	$1, -72(%ebp)
.L31:
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	cmpl	-72(%ebp), %eax
	jg	.L32
	movl	8(%ebp), %eax
	movzbl	44(%eax), %eax
	testb	%al, %al
	jne	.L19
	fldl	-56(%ebp)
	fnstcw	-90(%ebp)
	movzwl	-90(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -92(%ebp)
	fldcw	-92(%ebp)
	fistps	-94(%ebp)
	fldcw	-90(%ebp)
	movzwl	-94(%ebp), %eax
	movw	%ax, -24(%ebp)
	movw	$0, -22(%ebp)
	movw	$1, -20(%ebp)
	movl	8(%ebp), %eax
	movl	52(%eax), %eax
	movw	%ax, -18(%ebp)
	movw	$0, -16(%ebp)
	fldl	-48(%ebp)
	fldcw	-92(%ebp)
	fistps	-94(%ebp)
	fldcw	-90(%ebp)
	movzwl	-94(%ebp), %eax
	movw	%ax, -14(%ebp)
	movl	8(%ebp), %eax
	movl	48(%eax), %eax
	movw	%ax, -12(%ebp)
	movw	$1, -10(%ebp)
	movzbl	-73(%ebp), %eax
	movzbl	%al, %ebx
	movzbl	-74(%ebp), %eax
	movzbl	%al, %ecx
	movzbl	-75(%ebp), %eax
	movzbl	%al, %edx
	movl	16(%ebp), %eax
	movl	4(%eax), %eax
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	SDL_MapRGB
	movl	%eax, 8(%esp)
	leal	-24(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_FillRect
	movzbl	-73(%ebp), %eax
	movzbl	%al, %ebx
	movzbl	-74(%ebp), %eax
	movzbl	%al, %ecx
	movzbl	-75(%ebp), %eax
	movzbl	%al, %edx
	movl	16(%ebp), %eax
	movl	4(%eax), %eax
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	SDL_MapRGB
	movl	%eax, 8(%esp)
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_FillRect
.L19:
	addl	$116, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	plotFunction, .-plotFunction
	.section	.rodata
.LC13:
	.string	"SDL_VIDEO_CENTERED=1"
	.align 4
.LC14:
	.string	"node parse.js \"%s\" %lf %lf %lf %d"
.LC15:
	.string	"r"
.LC16:
	.string	"%lf"
	.text
	.globl	main
	.type	main, @function
main:
.LFB9:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$288, %esp
	movl	%ecx, %eax
	movl	4(%eax), %edx
	movl	%edx, -236(%ebp)
	movl	%gs:20, %edx
	movl	%edx, -12(%ebp)
	xorl	%edx, %edx
	movl	%esp, %edx
	movl	%edx, %ebx
	leal	-184(%ebp), %edx
	movl	-236(%ebp), %ecx
	movl	%ecx, 8(%esp)
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	parseArgs
	subl	$4, %esp
	movl	$.LC13, (%esp)
	call	putenv
	movl	-132(%ebp), %ecx
	movl	-136(%ebp), %edx
	movl	-236(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	initSDL
	movl	%eax, -220(%ebp)
	movl	-136(%ebp), %edx
	fldl	-152(%ebp)
	fldl	-176(%ebp)
	fldl	-184(%ebp)
	fxch	%st(2)
	movl	-144(%ebp), %eax
	movl	%edx, 36(%esp)
	fstpl	28(%esp)
	fstpl	20(%esp)
	fstpl	12(%esp)
	movl	%eax, 8(%esp)
	movl	$.LC14, 4(%esp)
	leal	-112(%ebp), %eax
	movl	%eax, (%esp)
	call	sprintf
	movl	$.LC15, 4(%esp)
	leal	-112(%ebp), %eax
	movl	%eax, (%esp)
	call	popen
	movl	%eax, -216(%ebp)
	movl	-136(%ebp), %eax
	leal	-1(%eax), %edx
	movl	%edx, -212(%ebp)
	sall	$3, %eax
	leal	7(%eax), %edx
	movl	$16, %eax
	subl	$1, %eax
	addl	%edx, %eax
	movl	$16, -244(%ebp)
	movl	$0, %edx
	divl	-244(%ebp)
	imull	$16, %eax, %eax
	subl	%eax, %esp
	leal	40(%esp), %eax
	addl	$7, %eax
	shrl	$3, %eax
	sall	$3, %eax
	movl	%eax, -208(%ebp)
	movl	$0, -224(%ebp)
	jmp	.L42
.L48:
	movl	-224(%ebp), %eax
	leal	0(,%eax,8), %edx
	movl	-208(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, 8(%esp)
	movl	$.LC16, 4(%esp)
	movl	-216(%ebp), %eax
	movl	%eax, (%esp)
	call	__isoc99_fscanf
	movzbl	-119(%ebp), %eax
	testb	%al, %al
	jne	.L59
.L43:
	movl	-208(%ebp), %eax
	movl	-224(%ebp), %edx
	fldl	(%eax,%edx,8)
	fldl	-168(%ebp)
	fxch	%st(1)
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L58
.L56:
	movl	-208(%ebp), %eax
	movl	-224(%ebp), %edx
	fldl	(%eax,%edx,8)
	fstpl	-168(%ebp)
	jmp	.L44
.L58:
	movl	-208(%ebp), %eax
	movl	-224(%ebp), %edx
	fldl	(%eax,%edx,8)
	fldl	-160(%ebp)
	fucomip	%st(1), %st
	fstp	%st(0)
	jbe	.L44
.L57:
	movl	-208(%ebp), %eax
	movl	-224(%ebp), %edx
	fldl	(%eax,%edx,8)
	fstpl	-160(%ebp)
	jmp	.L44
.L59:
	nop
.L44:
	addl	$1, -224(%ebp)
.L42:
	movl	-136(%ebp), %eax
	cmpl	-224(%ebp), %eax
	jg	.L48
	movl	-216(%ebp), %eax
	movl	%eax, (%esp)
	call	pclose
	movzbl	-119(%ebp), %eax
	testb	%al, %al
	jne	.L49
	fldl	-160(%ebp)
	fldl	-168(%ebp)
	fldl	-160(%ebp)
	fsubrp	%st, %st(1)
	movl	-132(%ebp), %eax
	movl	%eax, -240(%ebp)
	fildl	-240(%ebp)
	fdivrp	%st, %st(1)
	fldl	.LC17
	fmulp	%st, %st(1)
	fsubrp	%st, %st(1)
	fstpl	-160(%ebp)
	fldl	-168(%ebp)
	fldl	-168(%ebp)
	fldl	-160(%ebp)
	fsubrp	%st, %st(1)
	movl	-132(%ebp), %eax
	movl	%eax, -240(%ebp)
	fildl	-240(%ebp)
	fdivrp	%st, %st(1)
	fldl	.LC17
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fstpl	-168(%ebp)
.L49:
	movl	-208(%ebp), %eax
	movl	-220(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	leal	-184(%ebp), %eax
	movl	%eax, (%esp)
	call	plotFunction
	movl	-220(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_Flip
	jmp	.L50
.L53:
	movzbl	-204(%ebp), %eax
	movzbl	%al, %eax
	cmpl	$12, %eax
	jne	.L50
.L51:
	call	SDL_Quit
	movl	$0, %eax
	jmp	.L52
.L50:
	leal	-204(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_WaitEvent
	testl	%eax, %eax
	jne	.L53
	movl	-220(%ebp), %eax
	movl	%eax, (%esp)
	call	SDL_FreeSurface
	call	SDL_Quit
	movl	$0, %eax
.L52:
	movl	%ebx, %esp
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L55
	call	__stack_chk_fail
.L55:
	leal	-8(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC17:
	.long	0
	.long	1078198272
	.ident	"GCC: (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
