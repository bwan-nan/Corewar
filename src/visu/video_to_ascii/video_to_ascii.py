import sys
import os.path
import xml.etree.cElementTree as etree
import cv2


############################################################
# DEFINE
############################################################


HEIGHT_LENGTH = 96
OUTPUT_PATH = 'ascii_video.xml'
ASCII_GRADIENT = ["  ", "..", ";;", "//", "++", "))", "UU", "##", "%%", "&&", "@@"]


############################################################
# SECURITY CHECK
############################################################


if (len(sys.argv) != 2):
	print("Usage: python video_to_ascii.py path/video.mp4")
	sys.exit()
else:
	video_path = sys.argv[1]


############################################################
# FILES INIT
############################################################


# create/clear output_file
file = open(OUTPUT_PATH, "w")
file.write("")
file.close


############################################################
# SECURITY CHECK
############################################################


#...


############################################################
# FUNCTIONS
############################################################


def create_ascii_image(frame, dim):
	width = dim[0]
	height = dim[1]
	size = height * width

	output_root = etree.Element('corewar')
	memory = etree.Element('memory', size=str(size))

	ascii_max_index = len(ASCII_GRADIENT) - 1
	x = 0
	y = 0

	text = ''
	while y < height:
		x = 0
		while x < width:
			pixel_color = frame[y][x]
			ascii_color = ASCII_GRADIENT[int(pixel_color * ascii_max_index / 255)]
			#text += ascii_color
			text += str(pixel_color) + ","
			x += 1
		y += 1

	memory.text = text
	output_root.append(memory)
	file = open(OUTPUT_PATH, "a+")
	file.write(etree.tostring(output_root, encoding='UTF-8') + "\n")
	file.close


############################################################
# MAIN
############################################################


video = cv2.VideoCapture(video_path)

# read first image for spec
ret, frame = video.read()
height = frame.shape[0]
width = frame.shape[1]

while(1):
	# we'll lost the first image, don't care
    ret, frame = video.read()
    if (cv2.waitKey(1) & 0xFF == ord('q')) or ret == False:
        break

    # downscale image and convert it to grayscale
    new_width = int(width * HEIGHT_LENGTH / height)
    new_height = int(HEIGHT_LENGTH)
    dim = (new_width, new_height)
    frame = cv2.resize(frame, dim, interpolation =cv2.INTER_AREA)
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # create ascii image
    create_ascii_image(frame, (new_width, new_height))

    cv2.imshow('frame', frame)

file = open(OUTPUT_PATH, "a+")
file.write("<end_reached/>\n")
file.close
video.release()