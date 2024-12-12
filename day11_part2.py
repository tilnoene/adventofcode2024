numbers = [int(x) for x in input().split()]

mem = {}

def blink(number, turn):
	if turn == 0:
		return 1
	
	ans = mem.get((number, turn), 0)

	if ans != 0:
		return ans

	strnum = str(number)
	sz = len(strnum)

	if number == 0:
		ans = blink(1, turn - 1)
	elif sz % 2 == 0:
		ans = blink(int(strnum[:sz//2]), turn - 1) + blink(int(strnum[sz//2:]), turn - 1)
	else:
		ans = blink(number * 2024, turn - 1)
	
	mem[(number, turn)] = ans

	return ans

answer = 0

for number in numbers:
	cur = blink(number, 75)
	answer += cur

print(answer)