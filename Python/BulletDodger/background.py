import pygame


class Fond:
    def __init__(self):
        self.image = pygame.image.load("background.jpg").convert()
        self.redimention = (1080, 720)
        self.image = pygame.transform.scale(self.image, self.redimention)

