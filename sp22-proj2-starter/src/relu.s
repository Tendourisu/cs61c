.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
	# Prologue
	addi t0 x0 1
	blt a1 t0 exit

loop_start:
	lw t0, 0(a0)     # 从a0指向的位置加载数据到寄存器t0
    bgez t0, loop_continue # 如果t0 >= 0, 跳转到loop_continue
    sw zero, 0(a0)   # 否则将0存储回原位置




loop_continue:
	addi a0 a0 4	 # a0指向下一个位置


loop_end:
	addi a1, a1, -1  # 减少计数器
    bnez a1, loop_start  # 如果计数器不为0, 继续循环

	# Epilogue


	ret

exit:
	li a0 36
	ecall
