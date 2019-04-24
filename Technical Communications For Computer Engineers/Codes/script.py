import os

sizes = [
    ['1000', '34', '2'],
    ['1000', '34', '26'],
    ['1000', '300', '2'],
    ['1000', '300', '26'],
    ['10000', '1000', '2'],
    ['10000', '1000', '26'],
    ['10000', '3000', '2'],
    ['10000', '3000', '26'],
    ['100000', '334', '2'],
    ['100000', '334', '26'],
    ['100000', '30000', '2'],
    ['100000', '30000', '26']
]

for i in range(len(sizes)):
    os.system(f'python3 generator.py {sizes[i][0]} {sizes[i][1]} {sizes[i][2]} > inputs/{i + 1}.txt')