from itertools import combinations
import random


class Ability:
    def __init__(self,
                 name = "Uninitialized Ability",
                 damage = 0,
                 hitChance = 1.0,
                 specialEffectChance = 0.0,
                 elementType = "neutral",
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
                 attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0, "neutral": 0.0},
                 defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0, "neutral": 0.0},
                 criticalChance = 0.0,
                 evasionChance = 0.0,
                 elementType = "neutral",
                 abilities = []
                 ):
        self.name = name
        self.symbol = symbol
        self.health = health
        self.attack = attack
        self.attackMultipliers = attackMultipliers
        self.attackMultipliers['neutral'] = 0.0
        self.defenseMultipliers = defenseMultipliers
        self.defenseMultipliers['neutral'] = 0.0
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
        # evasion chance
        evasionRng = random.uniform(0.0, 1.0)
        if evasionRng <= target.evasionChance:
            return 0
        
        # hit chance
        hitRng = random.uniform(0.0, 1.0)
        if ability.hitChance < hitRng:
            return 0
        
        # damage
        damageMultiplier = self.attackMultipliers[ability.elementType]
        damageDealt = self.attack + ability.damage
        damage = damageDealt + (damageDealt * damageMultiplier)
        targetMultiplier = target.defenseMultipliers[ability.elementType]
        targetDamageReducer = (targetMultiplier - 1.0) * damage
        damage -= targetDamageReducer
        
        # critical chance
        criticalRng = random.uniform(0.0, 1.0)
        if criticalRng <= self.criticalChance:
            damage *= 2
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
        self.attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0, "neutral": 0.0}
        self.defenseMultipliers = {"water": 1.0, "earth": 1.0, "fire": 1.0, "air": 1.0, "neutral": 1.0}
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
    # BodyPart(name = "NeutralBody", symbol = 'N1', health = 200, evasionChance = 0.2, elementType = "neutral", defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0}),
    # BodyPart(name = "NeutralBody", symbol = 'N2', health = 200, evasionChance = 0.2, elementType = "neutral", defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0}),
    # BodyPart(name = "NeutralBody", symbol = 'N3', health = 200, evasionChance = 0.2, elementType = "neutral", defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0})
    
    BodyPart(name = "FireBody", symbol = 'F', health = 230, evasionChance = 0.05, elementType = "fire", defenseMultipliers = {"water": -0.5, "earth": 0.0, "fire": 0.0, "air": 0.5}),
    BodyPart(name = "WaterBody", symbol = 'W', health = 180, evasionChance = 0.25, elementType = "water", defenseMultipliers = {"water": 0.0, "earth": -0.5, "fire": 0.5, "air": 0.0}),
    BodyPart(name = "AirBody", symbol = 'A', health = 150, evasionChance = 0.3, elementType = "air", defenseMultipliers = {"water": 0.0, "earth": 0.5, "fire": -0.5, "air": 0.0}),
    BodyPart(name = "EarthBody", symbol = 'E', health = 250, evasionChance = 0.01, elementType = "earth", defenseMultipliers = {"water": 0.5, "earth": 0.0, "fire": 0.0, "air": -0.5})
]

bodyParts: list[BodyPart] = [
    # BodyPart(name = "Neutral", symbol = 'n1', attack = 15, criticalChance = 0.0, elementType = "neutral", attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0}, defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0},
    #          abilities = [Ability(name = "NeutralAttack", damage = 15, hitChance = 0.8, elementType = "neutral")]),
    # BodyPart(name = "Neutral", symbol = 'n2', attack = 15, criticalChance = 0.0, elementType = "neutral", attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0}, defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0},
    #          abilities = [Ability(name = "NeutralAttack", damage = 15, hitChance = 0.8, elementType = "neutral")]),
    # BodyPart(name = "Neutral", symbol = 'n3', attack = 15, criticalChance = 0.0, elementType = "neutral", attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0}, defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.0},
    #          abilities = [Ability(name = "NeutralAttack", damage = 15, hitChance = 0.8, elementType = "neutral")])
    
    BodyPart(name = "FireHorns", symbol = 'h', attack = 17, criticalChance = 0.04, elementType = "fire", attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.5, "air": 0.0}, defenseMultipliers = {"water": -0.25, "earth": 0.0, "fire": 0.0, "air": 0.0},
             abilities = [Ability(name = "FireAttack", damage = 20, hitChance = 0.8, elementType = "fire")]),
    BodyPart(name = "WaterTail", symbol = 't', attack = 12, criticalChance = 0.07, elementType = "water", attackMultipliers = {"water": 0.5, "earth": 0.0, "fire": 0.0, "air": 0.0}, defenseMultipliers = {"water": 0.0, "earth": -0.25, "fire": 0.0, "air": 0.0},
             abilities = [Ability(name = "WaterAttack", damage = 15, hitChance = 1.0, elementType = "water")]),
    BodyPart(name = "AirWings", symbol = 'w', attack = 18, criticalChance = 0.15, elementType = "air", attackMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": 0.5}, defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": -0.25, "air": 0.0},
             abilities = [Ability(name = "AirAttack", damage = 12, hitChance = 0.9, elementType = "air")]),
    BodyPart(name = "EarthSpikes", symbol = 's', attack = 10, criticalChance = 0.2, elementType = "earth", attackMultipliers = {"water": 0.0, "earth": 0.5, "fire": 0.0, "air": 0.0}, defenseMultipliers = {"water": 0.0, "earth": 0.0, "fire": 0.0, "air": -0.25},
             abilities = [Ability(name = "EarthAttack", damage = 14, hitChance = 1.0, elementType = "earth")])
]

# Body Part Configurations
configurations = []
for body in bodies:
    for part in bodyParts:
        configurations.append(BodyConfiguration(body, [part]))
        
# Test Configurations
ROUNDS = 1000

configurationsCombinations = list(combinations(configurations, 2))
movesPerCombatSum = 0
maxCombatMoves = 0
minCombatMoves = 10000
for _ in range(ROUNDS):
    for (p1, p2) in configurationsCombinations:
        p1.reset()
        p2.reset()
        movesPerCombat = 0
        while (not p1.is_dead()) or (not p2.is_dead()):
            movesPerCombat += 1
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
        movesPerCombatSum += movesPerCombat
        maxCombatMoves = movesPerCombat if movesPerCombat > maxCombatMoves else maxCombatMoves
        minCombatMoves = movesPerCombat if movesPerCombat < minCombatMoves else minCombatMoves
avgMovesPerCombat = movesPerCombatSum / (ROUNDS * len(configurationsCombinations))

# Print Results
print(f'Average Moves per Combat: {avgMovesPerCombat}')
print(f'Min Moves per Combat: {minCombatMoves}')
print(f'Max Moves per Combat: {maxCombatMoves}')

# Plot Results
import matplotlib.pyplot as plt
import numpy as np
labels = [str(c.symbol) for c in configurations]
wins = [c.won for c in configurations]
losses = [c.lost for c in configurations]

x = np.arange(len(labels))
width = 0.35
fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, wins, width, label='Wins', color='yellowgreen')
rects2 = ax.bar(x + width/2, losses, width, label='Losses', color='orangered')
ax.set_ylabel('Scores')
ax.set_title('Scores by configuration')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()
fig.tight_layout()
plt.show()