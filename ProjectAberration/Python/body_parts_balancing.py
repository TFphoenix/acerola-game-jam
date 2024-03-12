from itertools import combinations


class Ability:
    def __init__(self,
                 name = "Uninitialized Ability",
                 damage = 0,
                 hitChance = 1.0,
                 specialEffectChance = 0.0,
                 elementType = "none",
                 ):
        self.name = name
        self.damage = damage
        self.hitChance = hitChance
        self.specialEffectChance = specialEffectChance
        self.elementType = elementType

class BodyPart:
    def __init__(self,
                 name = "Uninitialized Body Part",
                 symbol = '?',
                 health = 0,
                 attack = 0,
                 attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0},
                 defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0},
                 criticalChance = 0.0,
                 evasionChance = 0.0,
                 elementType = "none",
                 abilities = []
                 ):
        self.name = name
        self.symbol = symbol
        self.health = health
        self.attack = attack
        self.attackMultipliers = attackMultipliers
        self.defenseMultipliers = defenseMultipliers
        self.criticalChance = criticalChance
        self.evasionChance = evasionChance
        self.elementType = elementType
        self.abilities = abilities
        
class BodyConfiguration:
    def __init__(self,
                 body = BodyPart(),
                 parts = []):
        self.body = body
        self.parts = parts
        self.won = 0
        self.lost = 0
        self._initialize_stats()
        
    def chosen_ability(self):
        return self.abilities[0]
    
    def calculate_damage(self, ability, target):
        damageMultiplier = self.attackMultipliers[ability.elementType]
        damage = (self.attack + ability.damage) * damageMultiplier
        targetMultiplier = target.defenseMultipliers[ability.elementType]
        targetDamageReducer = (targetMultiplier - 1.0) * damage
        damage -= targetDamageReducer
        return damage
    
    def take_damage(self, damage):
        self.currentHealth -= damage
    
    def is_dead(self):
        return self.currentHealth <= 0
    
    def reset(self):
        self.currentHealth = self.health
    
    def win(self):
        self.won += 1
        
    def lose(self):
        self.lost += 1
        
    def _initialize_stats(self):
        self.name = ''
        self.symbol = ''
        self.health = 0
        self.attack = 0
        self.criticalChance = 0
        self.evasionChance = 0
        self.attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0}
        self.defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0}
        self.abilities = []
        
        all = [self.body] + self.parts
        for part in all:
            self.name += part.name
            self.symbol += part.symbol
            self.health += part.health
            self.attack += part.attack
            self.criticalChance += part.criticalChance
            self.evasionChance += part.evasionChance
            for element in part.attackMultipliers:
                self.attackMultipliers[element] += part.attackMultipliers[element]
            for element in part.defenseMultipliers:
                self.defenseMultipliers[element] += part.defenseMultipliers[element]
            self.abilities += part.abilities
        
        self.currentHealth = self.health

# Body Parts
bodies: list[BodyPart] = [
    BodyPart(name = "FireBody", symbol = 'F', health = 300, evasionChance = 0.02, elementType = "fire", defenseMultipliers = {"water": -0.5, "earth": 0.0, "fire": 0.0, "air": 0.5}),
    BodyPart(name = "WaterBody", symbol = 'W', health = 300, evasionChance = 0.02, elementType = "water", defenseMultipliers = {"water": 0.0, "earth": -0.5, "fire": 0.5, "air": 0.0}),
    BodyPart(name = "AirBody", symbol = 'A', health = 300, evasionChance = 0.02, elementType = "air", defenseMultipliers = {"water": 0.0, "earth": 0.5, "fire": -0.5, "air": 0.0}),
    BodyPart(name = "EarthBody", symbol = 'E', health = 300, evasionChance = 0.02, elementType = "earth", defenseMultipliers = {"water": 0.5, "earth": 0.0, "fire": 0.0, "air": -0.5}),
]

bodyParts: list[BodyPart] = [
    BodyPart(name = "FireHorns", symbol = 'h', attack = 10, criticalChance = 0.05, elementType = "fire", attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.5, "air": 0.0}, defenseMultipliers = {"water": -0.25, "earth": 0.0, "fire": 0.0, "air": 0.0},
             abilities = [Ability(name = "FireAttack", damage = 15, hitChance = 1.0, elementType = "fire")]),
    
    BodyPart(name = "WaterTail", symbol = 't', attack = 10, criticalChance = 0.05, elementType = "water", attackMultipliers = {"water": 0.5, "earth": 0.0, "fire": 0.0, "air": 0.0}, defenseMultipliers = {"water": 0.0, "earth": -0.25, "fire": 0.0, "air": 0.0},
             abilities = [Ability(name = "WaterAttack", damage = 15, hitChance = 1.0, elementType = "water")]),
    
    BodyPart(name = "AirWings", symbol = 'w', attack = 10, criticalChance = 0.05, elementType = "air", attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.5}, defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": -0.25, "air": 0.0},
             abilities = [Ability(name = "AirAttack", damage = 15, hitChance = 1.0, elementType = "air")]),
    
    BodyPart(name = "EarthSpikes", symbol = 's', attack = 10, criticalChance = 0.05, elementType = "earth", attackMultipliers = {"water": 0.0, "earth": 0.5, "fire": 0.0, "air": 0.0}, defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": -0.25},
             abilities = [Ability(name = "EarthAttack", damage = 15, hitChance = 1.0, elementType = "earth")]),
]

# Body Part Configurations
configurations = []
for body in bodies:
    for part in bodyParts:
        configurations.append(BodyConfiguration(body, [part]))
        
# Test Configurations
for (p1, p2) in list(combinations(configurations, 2)):
    p1.reset()
    p2.reset()
    while (not p1.is_dead()) or (not p2.is_dead()):
        p1_ability = p1.chosen_ability()
        p2_ability = p2.chosen_ability()
        p1_damage = p1.calculate_damage(p1_ability, p2)
        p2_damage = p2.calculate_damage(p2_ability, p1)
        p1.take_damage(p2_damage)
        p2.take_damage(p1_damage)
        # draw
        if p1.is_dead() and p2.is_dead():
            if p1.currentHealth > p2.currentHealth:
                p1.win()
                p2.lose()
            else:
                p2.win()
                p1.lose()
        # p2 wins
        elif p1.is_dead():
            p2.win()
            p1.lose()
        # p1 wins
        elif p2.is_dead():
            p1.win()
            p2.lose()

# Plot Results
import matplotlib.pyplot as plt
import numpy as np
labels = [str(c.symbol) for c in configurations]
wins = [c.won for c in configurations]
losses = [c.lost for c in configurations]

x = np.arange(len(labels))
width = 0.35
fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, wins, width, label='Wins')
rects2 = ax.bar(x + width/2, losses, width, label='Losses')
ax.set_ylabel('Scores')
ax.set_title('Scores by configuration')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()
fig.tight_layout()
plt.show()