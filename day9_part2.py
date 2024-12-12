line = input()
disk = []
last_used_index = 0

for i in range(len(line)):
    if i % 2 == 0:
        disk.append([last_used_index, int(line[i])])
        last_used_index += 1
    else:
        disk.append(['.', int(line[i])])

last_used_index -= 1

for i in range(len(disk) - 1, -1, -1):
    if disk[i][0] == last_used_index:
        for j in range(i):
            if disk[j][0] == '.' and disk[j][1] >= disk[i][1]:
                remain = disk[j][1] - disk[i][1]

                middle = [ [ disk[i][0], disk[i][1] ] ]
                disk[i][0] = '.'

                if remain > 0:
                    middle += [ ['.', remain] ]

                aux = disk[:j] + middle + disk[(j + 1):]

                disk = aux

                break

        last_used_index -= 1

s = []

for e in disk:
    for j in range(e[1]):
        s.append(str(e[0]))

def get_checksum(disk):
    checksum = 0

    for i in range(len(disk)):
        if disk[i] != '.':
            checksum += i * int(disk[i])

    return checksum

print(get_checksum(s))