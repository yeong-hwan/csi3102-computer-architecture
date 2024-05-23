################################################################################

.data

newline:
  .asciiz "\n"
str1:
  .asciiz "INFO: $a0 = "
str2:
  .asciiz "INFO: $a1 = "
str3:
  .asciiz "INFO: $v0 = "

inputStr0:
  .align 1
  .asciiz "This is One String!"
inputStr1:
  .align 1
  .asciiz "This is Another String!"
inputStr2:
  .align 1
  .asciiz "ABCDEFGHIJKLMNOP"
inputStr3:
  .align 1
  .asciiz "ABCDEFGHIJKMNLOP"
inputStr4:
  .align 1
  .asciiz "abcdefghijklmnop"

################################################################################

.text

# compareStrings
#
# $a0: the starting memory address of string0
# $a1: the starting memory address of string1
#
# $v0 =  1 (if string0 > string1)
#        0 (if string0 = string1)
#       -1 (if string0 < string1)
compareStrings:

  # stack <-- $ra
  addi $sp, $sp, -4
  sw $ra, 0($sp)

  #################################
  # FIXME

  # Initialize index to 0
  li $t0, 0

compare_loop:
  # Load characters from both strings
  lb $t1, 0($a0)   # Load character from string0
  lb $t2, 0($a1)   # Load character from string1

  # Compare characters
  beq $t1, $zero, end_compare   # If end of string0, check if end of string1
  beq $t2, $zero, end_compare   # If end of string1, string0 is greater

  sub $t3, $t1, $t2   # Compare characters
  bnez $t3, end_compare   # If characters are different, end comparison

  # Increment index and continue loop
  addi $a0, $a0, 1   # Increment string0 pointer
  addi $a1, $a1, 1   # Increment string1 pointer
  j compare_loop

end_compare:
  # Set return value
  sub $v0, $t1, $t2   # Compare characters
  # $v0 =  1 (if string0 > string1)
  #        0 (if string0 = string1)
  #       -1 (if string0 < string1)

  # FIXME
  #################################

  # $ra <-- stack
  lw $ra, 0($sp)
  addi $sp, $sp, 4

  # return $v0
  jr $ra

.globl main
main:

  # stack <-- $ra, $s0
  addi $sp, $sp, -8
  sw $ra, 0($sp)
  sw $s0, 4($sp)

  ### Example 1

  # print_string str1; print_string inputStr0; print_string newline
  li $v0, 4
  la $a0, str1
  syscall
  li $v0, 4
  la $a0, inputStr0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # print_string str2; print_string inputStr1; print_string newline
  li $v0, 4
  la $a0, str2
  syscall
  li $v0, 4
  la $a0, inputStr1
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # $v0 = compareStrings(inputStr0, inputStr1)
  la $a0, inputStr0
  la $a1, inputStr1
  jal compareStrings

  # $s0 = $v0
  move $s0, $v0

  # print_string str3; print_int $v0; print_string newline
  li $v0, 4
  la $a0, str3
  syscall
  li $v0, 1
  move $a0, $s0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  ### Example 2

  # print_string str1; print_string inputStr1; print_string newline
  li $v0, 4
  la $a0, str1
  syscall
  li $v0, 4
  la $a0, inputStr1
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # print_string str2; print_string inputStr0; print_string newline
  li $v0, 4
  la $a0, str2
  syscall
  li $v0, 4
  la $a0, inputStr0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # $v0 = compareStrings(inputStr1, inputStr0)
  la $a0, inputStr1
  la $a1, inputStr0
  jal compareStrings

  # $s0 = $v0
  move $s0, $v0

  # print_string str3; print_int $v0; print_string newline
  li $v0, 4
  la $a0, str3
  syscall
  li $v0, 1
  move $a0, $s0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  ### Example 3

  # print_string str1; print_string inputStr0; print_string newline
  li $v0, 4
  la $a0, str1
  syscall
  li $v0, 4
  la $a0, inputStr0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # print_string str2; print_string inputStr0; print_string newline
  li $v0, 4
  la $a0, str2
  syscall
  li $v0, 4
  la $a0, inputStr0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # $v0 = compareStrings(inputStr0, inputStr0)
  la $a0, inputStr0
  la $a1, inputStr0
  jal compareStrings

  # $s0 = $v0
  move $s0, $v0

  # print_string str3; print_int $v0; print_string newline
  li $v0, 4
  la $a0, str3
  syscall
  li $v0, 1
  move $a0, $s0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  ### Example 4

  # print_string str1; print_string inputStr2; print_string newline
  li $v0, 4
  la $a0, str1
  syscall
  li $v0, 4
  la $a0, inputStr2
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # print_string str2; print_string inputStr3; print_string newline
  li $v0, 4
  la $a0, str2
  syscall
  li $v0, 4
  la $a0, inputStr3
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # $v0 = compareStrings(inputStr2, inputStr3)
  la $a0, inputStr2
  la $a1, inputStr3
  jal compareStrings

  # $s0 = $v0
  move $s0, $v0

  # print_string str3; print_int $v0; print_string newline
  li $v0, 4
  la $a0, str3
  syscall
  li $v0, 1
  move $a0, $s0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  ### Example 5

  # print_string str1; print_string inputStr3; print_string newline
  li $v0, 4
  la $a0, str1
  syscall
  li $v0, 4
  la $a0, inputStr3
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # print_string str2; print_string inputStr2; print_string newline
  li $v0, 4
  la $a0, str2
  syscall
  li $v0, 4
  la $a0, inputStr2
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # $v0 = compareStrings(inputStr3, inputStr2)
  la $a0, inputStr3
  la $a1, inputStr2
  jal compareStrings

  # $s0 = $v0
  move $s0, $v0

  # print_string str3; print_int $v0; print_string newline
  li $v0, 4
  la $a0, str3
  syscall
  li $v0, 1
  move $a0, $s0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  ### Example 6

  # print_string str1; print_string inputStr2; print_string newline
  li $v0, 4
  la $a0, str1
  syscall
  li $v0, 4
  la $a0, inputStr2
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # print_string str2; print_string inputStr4; print_string newline
  li $v0, 4
  la $a0, str2
  syscall
  li $v0, 4
  la $a0, inputStr4
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # $v0 = compareStrings(inputStr2, inputStr4)
  la $a0, inputStr2
  la $a1, inputStr4
  jal compareStrings

  # $s0 = $v0
  move $s0, $v0

  # print_string str3; print_int $v0; print_string newline
  li $v0, 4
  la $a0, str3
  syscall
  li $v0, 1
  move $a0, $s0
  syscall
  li $v0, 4
  la $a0, newline
  syscall

  # $ra, $s0 <-- stack
  lw $ra, 0($sp)
  lw $s0, 4($sp)
  addi $sp, $sp, 8

  # return;
  jr $ra

################################################################################

