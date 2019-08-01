####################################################################
# IMPORT
####################################################################

import sys
import math
import pygame

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


####################################################################
# IMPORT
####################################################################


if len(sys.argv) == 2:
    if sys.argv[1] == '-py2':
        PYTHON_V = 2
    elif sys.argv[1] == '-py3':
        PYTHON_V = 3
    else:
        print('Usage: python Corewar_visualizer.py [-py2][-py3]')
        raise SystemExit
else:
    print('Usage: python Corewar_visualizer.py [-py2][-py3]')
    raise SystemExit


####################################################################
# DEFINES
####################################################################


# we'll continue to read the std entry until END_REACHED == 1
END_REACHED = 0
# bool == 1 if xml balise is detect, else 0. That allows different output on std out
SAVE_XML = 0

# Define windows size
WIDTH = 1920
HEIGHT = 1080

# Define colors
BLACK = ( 0, 0, 0 )
WHITE = ( 255, 255, 255 )
GREEN = ( 140, 255, 60 )
RED = (255, 75, 150 )
LIGHT_GRAY = ( 240, 240, 240 )
GRAY = ( 128, 128, 128 )
DARK_GRAY = ( 30, 30, 30 )
BLUE = ( 50, 150, 255 )
LIGHT_BLUE = ( 60, 180, 255 )
DARK_BLUE = ( 15, 50, 85 )

DEFAULT = GRAY
C1 = ( 255, 100, 100 )
C2 = ( 255, 175, 100 )
C3 = ( 255, 255, 100 )
C4 = ( 175, 255, 100 )
C5 = ( 100, 255, 175 )
C6 = ( 100, 255, 255 )
C7 = ( 100, 175, 255 )
C8 = ( 100, 175, 255 )
C9 = ( 100, 100, 255 )
CA = ( 175, 100, 255 )
CB = ( 255, 100, 255 )
CC = ( 255, 100, 255 )
CD = ( 255, 100, 175 )

BLACK = ( 0, 0, 0 )

P_COLOR = [C1,C2,C3,C4,C5,C6,C7,C8,C9,CA,CB,CC,CD]

# initialise the game engine
pygame.init()

# Open a new window
size = (WIDTH, HEIGHT)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("ULTIMATE VISUALIZER TM - [ESCAPE]:quit")
icon = pygame.image.load('corewar_ico.jpg')
pygame.display.set_icon(icon)

#Sounds and musics
#click_sound = pygame.mixer.Sound('*.wav')
music = pygame.mixer.music.load('Pictures Of Purple Skies.mp3')
pygame.mixer.music.play(-1)

# The loop will carry on until the user exit the game (e.g. clicks the close button).
carryOn = True

# The clock will be used to control how fast the screen updates
clock = pygame.time.Clock()


####################################################################
# FUNCTIONS
####################################################################


def get_cells(memory_tree):
    cells = memory_tree.text.split(',')
    size = int(memory_tree.get('size'))
    side = int(math.ceil(math.sqrt(size)))
    cell_height = int(HEIGHT / side)

    return (cells, size, side, cell_height)


def draw_memory(memory_tree, cells, size, side, cell_height):
    #font = pygame.font.SysFont("Arial", cell_height)
    font = pygame.font.Font('NEON CLUB MUSIC.otf', int(cell_height / 2))

    i = 0
    while i < len(cells) - 1:
        val = cells[i]
        pid = int(cells[i + 1])
        x = (int(i / 2) % side) * cell_height
        y = int(int(i / 2) / side) * cell_height

        val = font.render(val, True, BLACK)
        pygame.draw.rect(screen, P_COLOR[pid], (x, y, cell_height, cell_height))
        screen.blit(val, (x + (cell_height / 12), y + (cell_height / 5)))
        i += 2

def draw_properties(process, color, x_start, y_start):
    # show properties
    screen.blit(font.render("[player_id] " + process.get("player_id"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 0))
    screen.blit(font.render("[process_id] " + process.get("process_id"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 20))
    screen.blit(font.render("[carry] " + process.get("carry"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 40))
    # show registers
    registers = process.find(".//registers")
    screen.blit(font.render("[REG_0] " + registers.get("r1"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 100))
    screen.blit(font.render("[REG_1] " + registers.get("r2"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 120))
    screen.blit(font.render("[REG_2] " + registers.get("r3"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 140))
    screen.blit(font.render("[REG_3] " + registers.get("r4"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 160))
    screen.blit(font.render("[REG_4] " + registers.get("r5"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 180))
    screen.blit(font.render("[REG_5] " + registers.get("r6"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 200))
    screen.blit(font.render("[REG_6] " + registers.get("r7"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 220))
    screen.blit(font.render("[REG_7] " + registers.get("r8"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 240))
    screen.blit(font.render("[REG_8] " + registers.get("r9"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 260))
    screen.blit(font.render("[REG_9] " + registers.get("r10"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 280))
    screen.blit(font.render("[REG_A] " + registers.get("r11"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 300))
    screen.blit(font.render("[REG_B] " + registers.get("r12"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 320))
    screen.blit(font.render("[REG_C] " + registers.get("r13"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 340))
    screen.blit(font.render("[REG_D] " + registers.get("r14"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 360))
    screen.blit(font.render("[REG_E] " + registers.get("r15"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 380))
    screen.blit(font.render("[REG_F] " + registers.get("r16"), True, WHITE), (HEIGHT + 100, HEIGHT / 2 - 200 + 400))

def draw_processes(processes_tree, cells, cell_height):
    #font = pygame.font.SysFont("Arial", 18)
    font = pygame.font.Font('NEON CLUB MUSIC.otf', 18)

    processes_tree_length = len(processes_tree)
    for i in range(processes_tree_length):
        # highligth
        process = processes_tree[i]
        current_action = process.find(".//current_action")
        current_pos = int(current_action.get("pos"))

        val = cells[current_pos * 2]
        pid = int(cells[current_pos * 2 + 1])
        x = (int(current_pos * 2 / 2) % side) * cell_height
        y = int(int(current_pos * 2 / 2) / side) * cell_height

        #font2 = pygame.font.SysFont("Arial", cell_height)
        font2 = pygame.font.Font('NEON CLUB MUSIC.otf', int(cell_height / 2))
        val = font2.render(val, True, BLACK)
        pygame.draw.rect(screen, WHITE, (x, y, cell_height, cell_height))
        screen.blit(val, (x + (cell_height / 12), y + (cell_height / 5))) 
        
        # show properties
        x_start = 1118
        y_start = 268 + i * 145
        #draw_properties(process, P_COLOR[pid], x_start, y_start)


####################################################################
# MAIN
####################################################################

bg_2 = pygame.image.load("corewar_background_r2.jpg")
line = ''
while carryOn:
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
            if (line == '<corewar>'):
                SAVE_XML = 1
            if SAVE_XML == 1:
                corewar_src += line
            # check if end of file
            if line == '</corewar>':
                SAVE_XML = 0
                break
            if line == '<end_reached/>':
                END_REACHED = 1

    if END_REACHED == 0:
        corewar_src_tree = etree.fromstring(corewar_src)

    # First, clear the screen to white.
    screen.fill(BLACK)
    screen.blit(bg_2, (0, 0))

    # Draw memory grid
    memory_tree = corewar_src_tree.find(".//memory")
    cells, size, side, cell_height = get_cells(memory_tree)
    draw_memory(memory_tree, cells, size, side, cell_height)

    # Draw processes
    processes_tree = corewar_src_tree.find(".//processes")
    draw_processes(processes_tree, cells, cell_height)

    # Go ahead and update the screen with what we've drawn.
    pygame.display.flip()

    # Limit to 60 frames per second.
    clock.tick(120)

#Once we have exited the main program loop we can stop the game engine.
pygame.quit()
