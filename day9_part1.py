line = input()
disk = []
last_used_index = 0

for i in range(len(line)):
    if i % 2 == 0:
        for j in range(int(line[i])):
            disk.append(str(last_used_index))
        
        last_used_index += 1
    else:
        for j in range(int(line[i])):
            disk.append('.')

it = 0
jt = len(disk) - 1

while (it < jt):
    if disk[it] != '.':
        it += 1
    elif disk[jt] == '.':
        jt -= 1
    else:
        disk[it] = disk[jt]
        disk[jt] = '.'
        it += 1
        jt -= 1

checksum = 0

for i in range(len(disk)):
    if disk[i] == '.':
        break
    
    checksum += i * int(disk[i])

print(checksum)