	.text
	.globl	sum
	.type	sum, @function
sum:
	pushl	%ebp
	movl	%esp, %ebp

	# You should not change anything above here.
	
	# This next line determines the total size of your stack
	# frame. Here, we are saving 40 bytes in the stack frame,
	# which is definitely overkill for this small example. You can
	# change this if you want, but there's no need to do so.
	subl	$40, %esp
	
	# Implement the body of this function below these comments.
	# The parameter for this functio is allocated on the stack at
	# addresss 8(%ebp).  You can use -4(%ebp) and -8(%ebp) for the
	# local variables.  The order of the local variables i and res
	# on the stack is up to you.

	cmpl	$0, 8(%ebp)
	jg		.L1
	movl	$-1, %eax
	jmp		.L0

.L1:	
	movl	$0, -8(%ebp)
	movl	$1, -4(%ebp)
	movl	-4(%ebp), %edx
	movl	-8(%ebp), %ecx

.L2:
	addl	%edx, %ecx
	incl	%edx
	cmpl	%edx, 8(%ebp)
	jl		.L4 	
	jmp		.L2

.L4:
	# The return value is stored in the register %eax. As written,
        # this function returns 0. Change this next line so that it
	# returns the value stored in the variable res.
	movl	%ecx, %eax
.L0:
	# You should not change anything below here.
	leave
	ret
	.size	sum, .-sum
