# Higher or Lower
<img width="430" height="600" alt="image" src="https://github.com/user-attachments/assets/29ffadb1-56bf-46e6-9b52-17456bc3dde0" />
<img width="375" height="450" alt="image" src="https://github.com/user-attachments/assets/7f12272b-9d79-4ca5-badb-fc90eb02c6e9" />

# Building and Running

```bash
    git clone https://github.com/KareemOtoum/card-game.git
    cd card-game
    cmake -S. -Bbuild
    cd build
    make
    ./game
```
# Design Decisions
## Centralised Game State (GameState class)

I used a ```GameState``` class to store score, streak, and play-state through an entirely static interface.
The reason is simple: the game has one global state, and making a full object for it is pointless.
Static members avoid passing state everywhere and keep the code focused on gameplay instead of boilerplate.

I also prevented construction ```GameState() = delete;``` because creating multiple states would break the logic.

# Terminal Rendering (terminal namespace)

All terminal logic is kept in a dedicated namespace.
That keeps the main game loop tidy.

I created a ```void print_cards(const std::vector<Card>& cards);``` function to deal with the complexity 
of rendering multiple cards on the same row inside the terminal. The downside of this is that it forces users to
create a copy of the cards into a vector however considering the small size of the ```Card``` class being ~8 bytes 
this is not an issue and a copy is very fast. And input sizes will most likely remain under 52 

I used ANSI escape codes because they work on Linux/macOS and most Windows terminals.
The card rendering uses Unicode for suits because it looks much better and still fits in fixed-width layout.

# Card Representation (Card class)

Cards are classes with strings for value ("A", "1", "2") and an enum for the suit.
This keeps the code simple and avoids needing conversion functions as the scope of the game is small.

Value parsing happens in get_value_int().
Invalid cards return -1 so the game can detect broken deck logic.

# Deck Shuffle (Fisher–Yates)

The deck uses the Fisher–Yates shuffle for equally probable permutations

I store the ```std::mt19937``` engine inside the Deck so the shuffle doesn’t create RNGs every time.
std::random_device only seeds it once in the constructor.

5. Game Loop Structure

The main game loop is intentionally simple:

 - Clear screen
 - Show score
 - Show current + mystery card
 - Get input
 - Reveal next card and evaluate guess
 - Pause briefly

# Handling Mistakes and Unknown Input

If the player enters anything except h / l / q, the game prints a warning.
Breaking the flow for garbage input would make the game annoying.
