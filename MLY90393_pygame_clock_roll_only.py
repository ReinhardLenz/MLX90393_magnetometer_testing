import pygame
import serial
import math
from time import sleep
# Initialize Pygame
pygame.init()
# Constants for screen dimensions and colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
SCREEN_WIDTH = 400
SCREEN_HEIGHT = 400
CENTER = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
# Set up the display
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Angle Visualization")
# Open serial port (make sure the baudrate matches the Arduino baudrate)
ser = serial.Serial('COM6', 9600)
# Function to draw the pointer
def draw_pointer(angle, length):
    angle_rad = math.radians(angle)
    end_point = (CENTER[0] + length * math.sin(angle_rad), CENTER[1] - length * math.cos(angle_rad))
    pygame.draw.line(screen, BLACK, CENTER, end_point, 3)
# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    # Read line from serial port
    if ser.inWaiting() > 0:
        line = ser.readline().decode('utf-8').strip()

        # Parse the angle value after 'Z:'
        if line.startswith('Y:'):
            split_line = line.split()
            if len(split_line) == 2:
                try:
                    angle = float(split_line[1])
                    # Clear screen
                    screen.fill(WHITE)
                    # Draw the pointer
                    draw_pointer(angle, 100)
                    # Update the display
                    pygame.display.flip()
                except ValueError:
                    pass  # If the value is not a float, pass
    sleep(0.5)  # Wait for the next reading
# Close Pyserial before exiting
ser.close()
# Quit Pygame
pygame.quit()