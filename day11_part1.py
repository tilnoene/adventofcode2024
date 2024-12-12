numbers = [int(x) for x in input().split()]

def blink(number, turn):
	if turn == 0:
		return 1
	
	strnum = str(number)
	sz = len(strnum)

	if number == 0:
		return blink(1, turn - 1)
	elif sz % 2 == 0:
		return blink(int(strnum[:sz//2]), turn - 1) + blink(int(strnum[sz//2:]), turn - 1)
	else:
		return blink(number * 2024, turn - 1)

answer = 0

for number in numbers:
	answer += blink(number, 25)

print(answer)