Cricket Attax – OOP-Based C++ Card Game
Overview
Cricket Attax is a 2-player, console-based card game implemented in C++ using Object-Oriented Programming (OOP) principles. Each player competes using a deck of cricketer cards (Batsman, Bowler, or All-Rounder), where rounds are decided based on statistical comparisons chosen by an announcer. The game simulates real-world cricket statistics and turn-based logic in an interactive format.

Table of Contents
Game Rules

Project Structure

OOP Concepts Used

Challenges and Solutions

Possible Improvements

Data Source

Game Rules
Two players are each dealt an equal number of shuffled cards.

Each card represents a cricketer and is of type: Batsman, Bowler, or All-Rounder.

An announcer (rotating between players) selects a valid stat (e.g., runs, wickets, strike rate) from the top card types of both players.

The top cards are compared using the selected stat:

The player with the higher value wins the round and collects both cards (and any tie pile).

If it's a tie:

Both cards go to a tie pile.

The announcer role is passed to the other player.

The winner of a tie-break round claims the entire tie pile.

The game ends when:

One player runs out of cards (they lose), or

A predefined maximum round limit is reached, and the player with more cards wins.

Project Structure
Cricketer_Card (Abstract Class): Defines the base structure for all cards.

Batsman_Card: Inherits from Cricketer_Card; includes batting-specific stats.

Bowler_Card: Inherits from Cricketer_Card; includes bowling-specific stats.

AllRounder: Inherits from both Batsman_Card and Bowler_Card using virtual inheritance.

Player Class: Maintains each player’s deck using a queue. Supports operations like adding/removing cards and accessing top card stats.

Game Class: Manages gameplay loop, round logic, announcer handling, tie resolution, and declaring the winner.

OOP Concepts Used
Abstraction: Cricketer_Card serves as an abstract base class with pure virtual functions like get_score().

Polymorphism: Derived classes override virtual methods like get_score() and print_card() for runtime behavior.

Inheritance: Specialized card types like Batsman_Card, Bowler_Card, and AllRounder inherit from the base class.

Virtual Inheritance: AllRounder uses virtual inheritance to resolve ambiguity caused by multiple inheritance (diamond problem).

Encapsulation: Player and game state data are kept private and accessed via public member functions.

Challenges and Solutions
Diamond Problem: The AllRounder class inherits from both Batsman_Card and Bowler_Card, which in turn inherit from Cricketer_Card.
Solution: Applied virtual public inheritance to ensure a single instance of the base class is shared.

Tie-break Logic: Implementing correct handling of tie rounds and managing a growing tie pile.
Solution: Used a queue to manage tie pile and incorporated logic to assign it correctly when a player wins.

Stat Selection: Ensuring announcer only picks valid stats depending on the card types in play.
Solution: Dynamically determined valid stats from both players’ top cards each round.

Possible Improvements
Add a graphical user interface (GUI) using Qt or SFML.

Extend support for more than 2 players.

Enable player profile saving and custom deck creation.

Add AI strategy for stat selection instead of random or manual choice.

Data Source
Player stats (runs, wickets, averages, etc.) were collected and formatted from ESPN Cricinfo.

