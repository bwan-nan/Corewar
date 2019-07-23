try:
  from lxml import etree
  print("running with lxml.etree")
except ImportError:
  try:
    # Python 2.5
    import xml.etree.cElementTree as etree
    print("running with cElementTree on Python 2.5+")
  except ImportError:
    try:
      # Python 2.5
      import xml.etree.ElementTree as etree
      print("running with ElementTree on Python 2.5+")
    except ImportError:
      try:
        # normal cElementTree install
        import cElementTree as etree
        print("running with cElementTree")
      except ImportError:
        try:
          # normal ElementTree install
          import elementtree.ElementTree as etree
          print("running with ElementTree")
        except ImportError:
          print("Failed to import ElementTree from any known place")
import sys
import math

if len(sys.argv) == 2:
    if sys.argv[1] == '-py2':
        PYTHON_V = 2
    elif sys.argv[1] == '-py3':
        PYTHON_V = 3
    else:
        print('Usage: python visu-hex [-py2][-py3]')
        raise SystemExit
else:
    print('Usage: python visu-hex [-py2][-py3]')
    raise SystemExit


####################################################################
# DEFINES
####################################################################


END_REACHED = 0

# Define size
WIDTH = 1920
HEIGHT = 1080

# Defne some colors
GREEN = ( 140, 255, 60 )
RED = ( 255, 75, 150 )
DARK_GRAY = ( 30, 30, 30 )

BLACK = ( 0, 0, 0 )

P_COLOR = [GREEN, RED]

# Import the pygame library and initialise the game engine
import pygame

pygame.init()

# Open a new window
size = (WIDTH, HEIGHT)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("ULTIMATE VISUALIZER TM - [ESCAPE]:quit")

# The loop will carry on until the user exit the game (e.g. clicks the close button).
carryOn = True

# The clock will be used to control how fast the screen updates
clock = pygame.time.Clock()


####################################################################
# MAIN
####################################################################


def draw_memory(memory_tree):
    print('draw_memory')
    size = int(memory_tree.get('size'))
    ceils = memory_tree.text.split(',')

    side = int(math.ceil(math.sqrt(size)))
    ceil_height = int(HEIGHT / side)
    font = pygame.font.SysFont("Arial", ceil_height)

    i = 0
    while i < len(ceils) - 1:
        val = ceils[i]
        id = int(ceils[i + 1])
        x = (int(i / 2) % side) * ceil_height
        y = int(int(i / 2) / side) * ceil_height
        print('x', x)
        print('y', y)
        print('ceil_height', ceil_height)

        val = font.render(val, True, BLACK)
        pygame.draw.rect(screen, P_COLOR[id - 1], (x, y, ceil_height, ceil_height))
        screen.blit(val, (x + (ceil_height / 12), y + (ceil_height / 5)))
        i += 2

line = ''

while carryOn:

    # First, clear the screen to white.
    screen.fill(BLACK)

    for event in pygame.event.get(): # User did something
        if event.type == pygame.QUIT: # If user clicked close
            carryOn = False # Flag that we are done so we exit this loop
        if event.type == pygame.KEYDOWN: # If user clicked close
            pressed = pygame.key.get_pressed()
            if pressed[pygame.K_ESCAPE]:
                carryOn = False # Flag that we are done so we exit this loop

    if END_REACHED == 0:
        corewar_src = ''
        while True:
            try:
                if PYTHON_V == 3:
                    line = input()
                else:
                    line = raw_input()
            except EOFError:
                break
            line = str(line)
            corewar_src += line
            # check if end of file
            if line == '</corewar>':
                break
            if line == '<end_reached/>':
                END_REACHED = 1
        print('this is the end...')

    if END_REACHED == 0:
        corewar_src_tree = etree.fromstring(corewar_src)
    memory_tree = corewar_src_tree.find(".//memory")
    #print(etree.tostring(memory_tree, encoding='UTF-8'))
    draw_memory(memory_tree)

    # --- Go ahead and update the screen with what we've drawn.
    pygame.display.flip()

    # --- Limit to 60 frames per second
    clock.tick(60)

#Once we have exited the main program loop we can stop the game engine:
pygame.quit()
print('... my friend')
