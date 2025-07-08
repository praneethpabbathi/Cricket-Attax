# Cricket-Attax – OOP-Based Card Game

## Overview

**Cricket Attax** is a 2-player, console-based card game built in **C++** using fundamental **Object-Oriented Programming (OOP)** principles.  
The project models cricketers as cards and simulates gameplay based on real-world stats, announcer-driven comparisons.

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

Inspired by the card games I enjoyed as a child, this project was created to revisit and strengthen my understanding of Object-Oriented Programming in C++. By modeling cricketers as dynamic card entities, I aimed to apply key OOP principles—such as inheritance, polymorphism, virtual inheritance, and abstract class design—in a practical and engaging way. Building a game from scratch also allowed me to explore real-time decision logic, stat-based comparisons, and gameplay mechanics in a structured, object-oriented environment.
---

## Game Rules & How It Works

- Two players are dealt an equal number of shuffled cards.
- Each card represents a cricketer with real-life stats and is one of the following types:
  - **Batsman**
  - **Bowler**
  - **AllRounder** (inherits both Batsman and Bowler stats)
- An **announcer** (alternates between players) selects a valid stat based on the top card types of both players.
- The selected stat is compared:
  - The player with the **higher stat value** wins the round and collects both cards (plus any tie-pile).
  - If there is a **tie**:
    - Both cards go into the **tie-pile**
    - The announcer role switches
  - The next round winner collects the **entire tie-pile**
  - The **winner becomes the announcer** for the next round; if tied, announcer switches
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

---

## Possible Improvements

- Add a graphical interface using a GUI library like SFML or Qt.
- Allow user input to create custom card decks.
- Add support for 3–4 players.
- Implement stat-based difficulty levels or power-up(traditionally known as GOLD,SILVER) cards.

---

## Data Source

Cricketer stats were sourced and formatted from publicly available data on:

- [ESPN Cricinfo](https://www.espncricinfo.com/)

These stats include:
- Runs, Wickets, Strike Rate, Economy, Batting/Bowling Averages, Matches, Age, and more.

---
