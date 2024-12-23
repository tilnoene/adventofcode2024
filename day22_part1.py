def mix(a, b):
    return (a ^ b)

def prune(x):
    return x % 16777216

def next(secret):
    secret = prune(mix(secret * 64, secret))
    secret = prune(mix(secret // 32, secret))
    secret = prune(mix(secret * 2048, secret))

    return secret

ans = 0
values = []

for i in range(4):
    secret = int(input())

    for j in range(2000):
        secret = next(secret)
    
    ans += secret

print(ans)