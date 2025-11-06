import pygame
from balles import Balles


class Jeu:
    def __init__(self, screen_0):
        self.screen = screen_0
        self.running = True
        self.clock = pygame.time.Clock()
        self.image = pygame.image.load("background.jpg").convert()  # charge l' image
        # self.rect = self.image.get_rect()
        self.balles = Balles(100, 100)
        self.redimention = (1080, 720)
        self.image = pygame.transform.scale(self.image, self.redimention)  # redimentionne l'image

    def update(self):
        pass

    def display(self):
        self.screen.blit(self.image, (0, 0))  # affiche l'image
        self.balles.draw(self.image)
        pygame.display.flip()  # met a jour l'ecran

    def handling_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False

    def run(self):
        while self.running:
            self.handling_events()
            self.display()
            self.clock.tick(60)


pygame.init()
ecran = pygame.display.set_mode((1080, 720))
jeu = Jeu(ecran)
jeu.run()
