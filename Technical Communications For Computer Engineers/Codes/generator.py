import sys
from random import choice
from string import ascii_lowercase


# n -> length of text string
# m -> length of pattern string
# lim -> maximum number of characters from alphabet used
n, m, lim = map(int, sys.argv[1:4])
if lim == 2:

    cur = 0
    pattern = ''.join(choice(ascii_lowercase[:min(lim, len(ascii_lowercase))]) for _ in range(m))
    pattern = 'ab' * (m // 2)

    while cur + m <= n:
        if cur + 2 * m > n:
            print(pattern, end='')
        else:
            print(pattern[:-1], 'x', sep='', end='')
        cur += m
    
    if cur < n:
        print(''.join(choice(ascii_lowercase[:min(lim, len(ascii_lowercase))]) for _ in range(n - cur)))
    else:
        print()
    
    print(pattern)

else:
    print(''.join(choice(ascii_lowercase[:min(lim, len(ascii_lowercase))]) for _ in range(n)))
    print(''.join(choice(ascii_lowercase[:min(lim, len(ascii_lowercase))]) for _ in range(m)))
