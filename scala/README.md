# Stack Machine

Stack 1
1
2
3

add

Stack 2
3 <- 1 + 2
3

push 5

Stack 3

5
5
3

sub

Stack 4
0 <- 5 - 5
3

## Language:

Terms: instruction

cmp = -1 | 0 | 1

Instruction: add | sub | div | mod | mul | rshift | lshift | jmp | cmp | je <n> <addressing-mode>><step> | fork

add | sub | div | mod | mul | rshift | lshift | cmp | pop
 - no argument
 
- [x] add
- [x] sub
- [x] div
- [x] mul 
- [x] jmp 
 
jmp:
 - mode:address
 
mode: abs|rel

number: integer | float

'
je:
  - number
  - mode:address
  

fork:
    - optional mode:address
    
print:
  - print value as character
  
push:
  - number

print_stack
  - optional count
  
cmp:
 compare two operand in the stack
 
 result: -1(low) 0(equal) 1(high)

## Example:

```
push 2
push 3
push 'c'
add
jmp -3

push 2
push 5
push 10
push 11
print_stack
div
add
sub
push 13
lshift
fork
push 11
push 13
add
push 15
push 16
print
pop
push 1
push 2
cmp
je -1 rel:-3
```