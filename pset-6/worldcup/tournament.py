# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    # aqui usar ter a pasta abeeta de csv.DictReader e armazenar o inteiro
    # de teams dos times que estão sendo usados neste pset
    arquivo = sys.argv[1]
    with open(arquivo) as f:
        leitor = csv.DictReader(f)
        for team in leitor:
            team["rating"] = int(team["rating"])
            teams.append(team)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # vai pegar os vencedores da função simulate_tournament
    #  e armazenar em counts[winners]
    for y in range(N):
        winners = simulate_tournament(teams)
        if winners in counts:
            counts[winners] += 1
        else:
            counts[winners] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # aqui como é dito acima : ela vai mostrar a porcentagem de vitórias de
    # cada time 
    while len(teams) > 1:
        teams = simulate_round(teams)
    return teams[0]["team"]


if __name__ == "__main__":
    main()
