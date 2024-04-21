.data

newline:
  .asciiz "\n"

str0:
  .asciiz "Enter a 32-bit unsigned integer (in decimal): "
str1:
  .asciiz "INFO: calculateGCD returned:\n"
str2:
  .asciiz "INFO:   $v0 = "

.text

# $a0: a 32-bit unsigned integer
# $a1: a 32-bit unsigned integer
# $v0: the greatest common divisor of $a0 and $a1
calculateGCD:

################################################################################
# FIXME

  # Set up initial values
  move $t0, $a0      # $t0 = $a0
  move $t1, $a1      # $t1 = $a1

  gcd_loop:
    # Check if $t1 is 0, if so, $t0 contains the GCD
    beq $t1, $zero, gcd_done

    # Calculate remainder: $t0 % $t1 and store it in $t2
    divu $t0, $t1
    mfhi $t2           # Remainder is stored in $t2

    # Update $t0 to $t1 and $t1 to the remainder ($t2)
    move $t0, $t1      # $t0 = $t1
    move $t1, $t2      # $t1 = $t2

    # Repeat the loop
    j gcd_loop

  gcd_done:
    # GCD is in $t0, store it in $v0
    move $v0, $t0

# FIXME
################################################################################

  # return
  jr $ra

.globl main
main:

  # print_string str0; $t0 = read_int
  li $v0, 4
  la $a0, str0
  syscall
  li $v0, 5
  syscall
  move $t0, $v0

  # print_string str0; $t1 = read_int
  li $v0, 4
  la $a0, str0
  syscall
  li $v0, 5
  syscall
  move $t1, $v0

  # $s0 = $ra; $s1 = $a0; $s2 = $a1
  move $s0, $ra
  move $s1, $a0
  move $s2, $a1

  # call calculateGCD
  move $a0, $t0
  move $a1, $t1
  jal calculateGCD

  # $ra = $s0; $a0 = $s1; $a1 = $s2
  move $ra, $s0
  move $a0, $s1
  move $a1, $s2

  # $t0 = $v0
  move $t0, $v0

  # print_string str1
  li $v0, 4
  la $a0, str1
  syscall

  # print_string str2; print_int $t0; print_string newline
  li $v0, 4
  la $a0, str2
  syscall
  li $v0, 1
  move $a0, $t0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # return 0
  li $v0, 0
  jr $ra

