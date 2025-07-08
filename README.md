# Cricket-Attax – OOP-Based Card Game

## Overview

**Cricket Attax** is a 2-player, console-based card game built in **C++** using fundamental **Object-Oriented Programming (OOP)** principles.  
The project models cricketers as cards and simulates gameplay based on real-world stats, announcer-driven comparisons, and strategic tie-break mechanics.

---

## Table of Contents

- [Motivation](#motivation)
- [Game Rules & How It Works](#game-rules--how-it-works)
- [Project Structure](#project-structure)
- [OOP Concepts Used](#oop-concepts-used)
- [Challenges & How I Solved Them](#challenges--how-i-solved-them)
- [Possible Improvements](#possible-improvements)
- [Data Source](#data-source)

---

## Motivation

This project was created to apply object-oriented principles to a game environment while reinforcing key C++ concepts like inheritance, polymorphism, encapsulation, and abstract class design. It also aimed to simulate a dynamic and engaging card-based battle using real cricket data.

---

## Game Rules & How It Works

- Two players are dealt an equal number of shuffled cards.
- Each card represents a cricketer with real-life stats:
  - **Batsman**, **Bowler**, or **AllRounder** (inherits both).
- An **announcer** (rotating between players) chooses a valid stat based on the card types on top of each deck.
- The selected stat is compared:
  - The player with the **higher stat value** wins the round and collects both cards (and any tie-pile).
  - If there is a **tie**, both cards go to the tie-pile, and the announcer role switches.
  - The next round winner collects the **entire tie-pile**.
- The game ends when:
  - A player runs out of cards (they lose), or
  - A maximum round limit (e.g., 99) is reached — the player with more cards wins.

---

## Project Structure

- Implemented three types of Cricketer cards using inheritance and polymorphism:
  - `Batsman_Card` – includes `Runs`, `Average`, `Strike Rate`
  - `Bowler_Card` – includes `Wickets`, `Economy`, `Bowling Average`
  - `AllRounder` – inherits from both Batsman and Bowler

- Designed a `Player` class to:
  - Maintain a queue of cards (player’s deck)
  - Handle card addition/removal and stat retrieval
  - Support human vs. bot logic

- Built a `Game` class to:
  - Shuffle and distribute cards
  - Allow announcers to choose valid stats
  - Compare cards and determine round outcomes
  - Manage the tie-pile and announcer switching
  - Track total rounds and declare the final winner

---

## OOP Concepts Used

- **Abstract Classes:**  
  - `Cricketer_Card` is an abstract base class with a pure virtual `get_score()` method.

- **Polymorphism:**  
  - Functions like `get_score()` and `print_card()` are overridden in derived classes for dynamic behavior.

- **Inheritance:**  
  - `Batsman_Card`, `Bowler_Card`, and `AllRounder` inherit from the base class.

- **Virtual Inheritance:**  
  - Used in `AllRounder` to resolve the **diamond problem** caused by multiple inheritance from `Cricketer_Card`.

- **Encapsulation:**  
  - Game and Player states are encapsulated using private data members with public interfaces.

---

## Challenges & How I Solved Them

- **Diamond Problem:**  
  - Occurred because `AllRounder` inherits from both `Batsman_Card` and `Bowler_Card`, which themselves inherit from `Cricketer_Card`.  
  - **Solution:** Used `virtual public` inheritance to ensure only one instance of the base class exists.

- **Tie-break Logic:**  
  - Managing multiple consecutive ties and dynamic announcer switching was tricky.  
  - **Solution:** Implemented a `tiePile` queue and alternating announcer logic to handle complex edge cases.

---

## Possible Improvements

- Add a graphical interface using a GUI library like SFML or Qt.
- Allow user input to create custom card decks.
- Add support for 3–4 players.
- Implement stat-based difficulty levels or power-up cards.

---

## Data Source

Cricketer stats were sourced and formatted from publicly available data on:

- [ESPN Cricinfo](https://www.espncricinfo.com/)

These stats include:
- Runs, Wickets, Strike Rate, Economy, Batting/Bowling Averages, Matches, Age, and more.

---
