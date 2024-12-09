# Knucklebones Game - Class Design

## Class Design

### Dice Class
#### Data:
- `sides`: Number of sides on the dice (default: 6).
- `current_value`: The value of the dice after rolling.

#### Actions:
- `roll()`: Simulates rolling the dice and sets `current_value` to a random number between 1 and `sides`.
- `get_value()`: Returns the `current_value` of the dice.

#### Relationships:
- The `Dice` class is used by the `Player` class for rolling during the game (Composition).

---

### Player Class
#### Data:
- `name`: The name of the player.
- `score`: The player's current score.
- `grid`: A 3x3 matrix representing the player's game board.
- `dice`: A `Dice` object used for rolling.
- `player_stats`: Additional statistics like games played, games won, etc. (Optional).

#### Actions:
- `roll_dice()`: Rolls the dice using the `Dice` object.
- `place_die(column, value)`: Places a die with the given `value` in the specified column of the grid.
- `calculate_score()`: Computes the player's score based on their grid and scoring rules.
- `remove_matching_die(column, value)`: Removes a die with the specified `value` from the opponent's column if it exists.
- `get_score()`: Returns the player's score.

#### Relationships:
- A `Player` HAS-A `Dice` object (Composition).
- A `Player` participates in the `Knucklebones` game (Association).

---

### Game Class
#### Data:
- `players`: A list of `Player` objects.
- `current_round`: The current round number.
- `rules`: General game rules (e.g., max rounds, tie-breaking rules).

#### Actions:
- `start_game()`: Initializes the game and sets up players.
- `end_game()`: Ends the game and declares the winner.
- `get_winner()`: Determines the player with the highest score.
- `next_round()`: Advances to the next round and handles turn logic.

#### Relationships:
- The `Game` class controls the `Player` objects and their interactions (Composition).

---

### Knucklebones Class (Inherits from Game)
#### Data:
- `board_size`: Dimensions of the grid (default: 3x3).
- `specific_rules`: Rules unique to Knucklebones, such as the multiplication bonus and opponent dice removal.

#### Actions:
- `start_round()`: Begins a round of Knucklebones with player turns.
- `end_round()`: Ends the round and calculates scores.
- `apply_knucklebones_rules()`: Applies unique rules like opponent dice removal and scoring bonuses.
- `calculate_winner()`: Determines the winner after all rounds are complete.

#### Relationships:
- The `Knucklebones` class IS-A `Game` (Inheritance).
- The `Knucklebones` game HAS players, a grid, and dice (Composition).

---

## Keywords and Feature List
### Necessary:
- `score`
- `winner`
- `player stats`
- `first name`
- `dice`
- `grid`

### Possible:
- `leaderboard`
- `team stats`
- `userid`
- `levels`
- `streak`

### Wishful:
- `coins`
- `messaging`
- `teams`
- `high score`
- `chat`

---

## Inheritance and Composition

### Inheritance
- **Knucklebones IS-A Game**: The `Knucklebones` class inherits from the `Game` class because it extends general game behavior with specific rules and logic.

### Composition
- **Player HAS-A Dice**: Each `Player` object contains a `Dice` object for rolling.
- **Game HAS Players**: The `Game` class aggregates `Player` objects to manage their interactions.
- **Knucklebones HAS-A Board**: The grid structure for each player is an attribute of the `Knucklebones` class.
