a = int(input().split(': ')[1])
b = int(input().split(': ')[1])
c = int(input().split(': ')[1])

def combo(operand):
    if operand == 4:
        return a
    elif operand == 5:
        return b
    elif operand == 6:
        return c
    else:
        return operand

input()

program = [int(x) for x in input().split(': ')[1].split(',')]

output = []

pc = 0

while pc < len(program):
    opcode = program[pc]
    operand = program[pc + 1]

    if opcode == 3 and a != 0:
        pc = operand
    else:
        if opcode == 0:
            a = a // (2 ** combo(operand))
        elif opcode == 1:
            b = b ^ operand
        elif opcode == 2:
            b = combo(operand) % 8
        elif opcode == 4:
            b = b ^ c
        elif opcode == 5:
            output.append(str(combo(operand) % 8))
        elif opcode == 6:
            b = a // (2 ** combo(operand))
        elif opcode == 7:
            c = a // (2 ** combo(operand))

        pc += 2

print(','.join(output))