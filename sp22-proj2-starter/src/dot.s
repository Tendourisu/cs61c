.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
	ebreak
	# Prologue
	addi t0 x0 1
	blt a2 t0 exit36
	blt a3 t0 exit37
    blt a4 t0 exit37

    # Initialize dot product to 0
    li t4 0
	
	addi t0, x0, 0 #t0作为index的计数器i
	slli a3 a3 2
	slli a4 a4 2

loop_start:
	lw t1, 0(a0)     # 从a0指向的位置加载数据到寄存器t1
    lw t2, 0(a1)     # 从a1指向的位置加载数据到寄存器t2
	mul t3, t1, t2  # 计算t1 * t2
	add t4, t4, t3  # 累加t3到a0中

loop_end:
	addi t0, t0, 1  # 计数器加1
	add a0 a0 a3 # a0指向下一个位置
	add a1 a1 a4 # a1指向下一个位置
    bne t0, a2, loop_start  # 如果计数器不为a1, 继续循环
	mv a0, t4
	ret
	

exit36:
	li a0 17
	li a1 36
	ecall
exit37:
	li a0 17
	li a1 37
	ecall
