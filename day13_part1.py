first = True
INF = 10**10

answer = 0

while True:
    try:
        if not first:
            input()
        
        first = False

        line1 = input().split(': ')[1].split(', ')
        line2 = input().split(': ')[1].split(', ')
        line3 = input().split(': ')[1].split(', ')
        
        a = (int(line1[0].split('+')[-1]), int(line1[1].split('+')[-1]))
        b = (int(line2[0].split('+')[-1]), int(line2[1].split('+')[-1]))
        prize = (int(line3[0].split('=')[-1]), int(line3[1].split('=')[-1]))

        score = INF

        for i in range(100 + 1):
            for j in range(100 + 1):
                x = i * a[0] + j * b[0]
                y = i * a[1] + j * b[1]

                if (x, y) == prize:
                    score = min(score, 3 * i + j)

        if score != INF:
            answer += score
    except:
        break

print(answer)