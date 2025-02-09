.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
	# Prologue
	addi t0 x0 1
	blt a1 t0 exit
	
	addi t1, x0, 0 #t1作为index的计数器i
	lw t2, 0(a0)   
	addi t3, x0, 0 #t3存储最大值的索引, 初始值为0

loop_start:
	lw t0, 0(a0)     # 从a0指向的位置加载数据到寄存器t0
    bge t2, t0 loop_continue # 如果t2 >= t0, 跳转到loop_continue
    mv t2, t0
	mv t3, t1




loop_continue:
	addi a0 a0 4	 # a0指向下一个位置


loop_end:
	addi t1, t1, 1  # 计数器加1
    bne t1, a1, loop_start  # 如果计数器不为a1, 继续循环

	mv a0, t3
	ret

exit:
	li a0 36
	ecall