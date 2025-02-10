.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

	# Prologue
	ebreak
	addi sp, sp, -24
	sw ra, 0(sp)
    sw s0, 4(sp)
	sw s1, 8(sp)
    sw s2, 12(sp)
	sw s3, 16(sp) # descriptor if the file
	sw s4, 20(sp) # pointer of the allocated heap memory

	mv s0 a0
	mv s1 a1
	mv s2 a2

	mv a0 s0
	li a1 0
	jal ra fopen
	li t0 -1
	beq a0 t0 exit27
   
    mv s3 a0 # record the descriptor of the file

	mv a0 s3
	mv a1 s1
	li a2 4
	jal ra fread
	li t0 4
	bne a0 t0 exit29

	mv a0 s3
    mv a1 s2
	li a2 4 
	jal ra fread
	li t0 4
	bne a0 t0 exit29

	lw t0 0(s1)
	lw t1 0(s2)
	mul t2 t0 t1
	slli t2 t2 2
	mv a0 t2
	jal ra malloc
	beq a0 x0 exit26

	mv s4 a0
	mv a0 s3
	mv a1 s4
	lw t0 0(s1)
	lw t1 0(s2)
	mul t2 t0 t1
	slli t2 t2 2
	mv a2 t2
	jal ra fread
	lw t0 0(s1)	
	lw t1 0(s2)
	mul t2 t0 t1
	slli t2 t2 2
	bne a0 t2 exit29

	mv a0 s3
	jal ra fclose
	bne a0 x0 exit28
	
	# Epilogue
	mv a0 s4
	lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
	lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
	addi sp, sp, 24

	ret

exit26:
	li a0 17
	li a1 26
	ecall
exit27:
	li a0 17
	li a1 27
	ecall
exit28:
	li a0 17
	li a1 28
	ecall
exit29:
	li a0 17
	li a1 29
	ecall