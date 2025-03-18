import math

count = 0

def foo(n):
    global count
    count += 1
    if n <= 1:
        return 1
    return foo(n / 4) + foo(n / 4)  # Aqui, n / 4 sempre será float

n = 10000
print(math.floor(2 * math.sqrt(n) - 1))
foo(n)
print(count)
