import pygame


class Balles:
    def __init__(self, x, y):
        self.image = pygame.image.load("balle.png")
        self.rect = pygame.Rect(x, y, 50, 50)
        self.speed = 2
        self.velocity = [0, 0]

    def move(self):
        self.rect.move_ip(self.velocity[0] * self.speed, self.velocity[1] * self.speed)

    def draw(self, screen):
        screen.blit(self.image, self.rect)
