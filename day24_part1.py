variables = {}

def calc(v1, operation, v2):
    if operation == 'XOR':
        return v1 ^ v2
    elif operation == 'AND':
        return v1 & v2;
    else:
        return v1 | v2;

while True:
    line = input()

    if line == '':
        break
    
    name, value = line.split(': ')
    variables[name] = int(value)

expressions = []
cnt = {}
aux = 0

while True:
    try:
        expression, result = input().split(' -> ')
        v1, operation, v2 = expression.split(' ')
        expressions.append((v1, operation, v2, result))
        
        cnt[result] = cnt.get(result, 0) + 1
        aux += 1
    except:
        break

while True:
    flag = False

    for v1, operation, v2, result in expressions:
        if result not in variables and v1 in variables and v2 in variables:
            flag = True
            variables[result] = calc(variables[v1], operation, variables[v2])

    if not flag:
        break

s = ''
it = 0

while True:
    name = f'z{str(it).rjust(2, "0")}'

    if name not in variables:
        break
    
    s += str(variables[name])
    it += 1

s = s[::-1]

# print(s)
print(int(s, 2))

