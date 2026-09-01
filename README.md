# PONG

A simple two-player Pong game written in **C** using **raylib**.

This project is a rewrite of my original Pygame Squash/Pong project in C. The goal is to recreate the core gameplay while learning C and working directly with a lightweight native game library.

## Features

- Two-player local multiplayer
- Player A controlled with `W` / `S`
- Player B controlled with `↑` / `↓`
- Frame-rate-independent movement
- Ball physics using velocity and delta time
- Paddle collision detection using raylib hitboxes
- Three paddle collision zones:
  - Top → ball bounces upward
  - Middle → ball continues horizontally
  - Bottom → ball bounces downward
- Automatic ball reset after a player misses
- Score tracking
- Center dividing line
- High-DPI support
- Undecorated game window

## Controls

| Player | Up | Down |
|---|---|---|
| Player A | `W` | `S` |
| Player B | `↑` | `↓` |

Close the game using the window manager or the normal window-close action.

---

## Dependencies

The project requires:

- C compiler (`clang` or `gcc`)

