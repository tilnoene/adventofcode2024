first = True
INF = 10**10
ERR = 10000000000000

answer = 0

while True:
    try:
        if not first:
            input()
        
        first = False

        line1 = input().split(': ')[1].split(', ')
        line2 = input().split(': ')[1].split(', ')
        line3 = input().split(': ')[1].split(', ')
        
        prize = (int(line3[0].split('=')[-1]), int(line3[1].split('=')[-1]))

        XA, YA = (int(line1[0].split('+')[-1]), int(line1[1].split('+')[-1]))
        XB, YB = (int(line2[0].split('+')[-1]), int(line2[1].split('+')[-1]))
        X, Y = prize

        X += ERR
        Y += ERR

        numb = (YA * X - XA * Y)
        denb = (YA * XB - XA * YB)

        if numb % denb != 0:
            continue
        
        b = numb // denb

        numa = (Y - YB * b)
        dena = YA

        if numa % dena != 0:
            continue
        
        a = numa // dena

        answer += a * 3 + b
    except:
        break

print(answer)