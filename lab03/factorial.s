.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi a1 x0 1   # a1 result
loop:
    beq a0 x0 exit # a0 != 0
    mul a1 a1 a0   # a1 *= a0 
    addi a0 a0 -1  # a0 -= 1
    j loop         #loop
exit: 
    add a0 a1 x0
    jr ra
