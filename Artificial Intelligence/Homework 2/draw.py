# Import a library of functions called 'pygame'
import pygame
from math import pi
import sys
import time

W = 1000
H = 600

def adjust(polygon):

    rev = []
    
    for point in polygon:
        rev.append(point)
        rev[-1][1] = H - rev[-1][1]
    
    return rev

pygame.init()
 
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BLUE =  (0, 0, 255)

size = [W, H]
screen = pygame.display.set_mode(size)
 
pygame.display.set_caption("Block Placements")

done = False
clock = pygame.time.Clock()

file = sys.argv[1]
rectangles = []

n, length = 0, 0

with open(file) as f:
    for f in f.readlines():
        if f == '\n':
            break
        if n == 0:
            n, length = map(float, f.split())
            n = int(n)
            continue
        rectangles.append(list(map(float, f.split())))

cursor = 0
scale = 30
while not done:

    clock.tick(10)
     
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
     
    screen.fill(WHITE)
 
    if cursor < len(rectangles):
        for i in range(cursor + 1):
            if rectangles[i][1] == 0:
                polygon = [[rectangles[i][2]*scale, rectangles[i][3]*scale]]
                polygon.append([rectangles[i][2]*scale + length*scale, rectangles[i][3]*scale])
                polygon.append([rectangles[i][2]*scale + length*scale, rectangles[i][3]*scale + scale])
                polygon.append([rectangles[i][2]*scale, rectangles[i][3]*scale + scale])
                print(polygon)
            else:
                polygon = [[rectangles[i][2]*scale, rectangles[i][3]*scale]]
                polygon.append([rectangles[i][2]*scale + scale, rectangles[i][3]*scale])
                polygon.append([rectangles[i][2]*scale + scale, rectangles[i][3]*scale + length*scale])
                polygon.append([rectangles[i][2]*scale, rectangles[i][3]*scale + length*scale])
                print(polygon)

            polygon = adjust(polygon)
            pygame.draw.polygon(screen, BLACK, polygon, 3)
            pygame.draw.polygon(screen, BLUE, polygon, 0)
        cursor += 1
        print(cursor)
        pygame.display.update()
  
    time.sleep(0.5)
 
pygame.quit()