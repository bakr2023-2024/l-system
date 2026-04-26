# L-System Visualizer

A turtle graphics L-system visualizer built with [Raylib](https://www.raylib.com/). Configure and switch between L-systems without touching the code — just pass a text file as an argument.

## Building

```
make main
```

## Usage

```
./lsystem.exe <file.txt>
```

Press **Enter** to advance to the next generation.

## File Format

Configuration files use an INI-like format with four sections: `[variables]`, `[rules]`, `[parameters]`, and `[misc]`. Sections must appear in the previous order, and the contents of each section must be followed by a blank line.

```ini
[variables]
F=DRAW
X=STAY

[rules]
F=FF
X=F+[[X]-X]-F[-FX]+X

[parameters]
axiom=-X
turn=25
start_x=96
start_y=720
start_angle=0

[misc]
length=15
scale=0.67
background=0x000000ff
foreground=0xffffffff
```

---

### [variables]

Maps a character to an action. Available actions:

| Action    | Description                                      |
|-----------|--------------------------------------------------|
| `DRAW`    | Move forward and draw a line                     |
| `MOVE`    | Move forward without drawing                     |
| `STAY`    | Do nothing (placeholder character)               |
| `CW`      | Rotate clockwise by the turn angle               |
| `ACW`     | Rotate counter-clockwise by the turn angle       |
| `SAVE`    | Push current position and angle onto the stack   |
| `RESTORE` | Pop position and angle from the stack            |

The characters `+`, `-`, `[`, `]` are mapped by default as follows:

| Character | Default action |
|-----------|----------------|
| `+`       | `CW`           |
| `-`       | `ACW`          |
| `[`       | `SAVE`         |
| `]`       | `RESTORE`      |

These defaults can be overridden by assigning them in `[variables]`, e.g. `+=ACW`.

---

### [rules]

Production rules of the form `A=...`. Each character on the left is replaced by the string on the right on every generation advance. Characters with no rule are kept as-is.

---

### [parameters]

| Key           | Description                                                                 |
|---------------|-----------------------------------------------------------------------------|
| `axiom`       | The starting string for the L-system                                        |
| `turn`        | Rotation amount in degrees applied by `CW`/`ACW`                            |
| `start_x`     | Starting X position of the turtle in pixels (max 960px)                     |
| `start_y`     | Starting Y position of the turtle in pixels (origin is top-left) (max 720px)|
| `start_angle` | Initial angle of the turtle in degrees. 0° points up, 90° points right      |

---

### [misc]

| Key          | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `length`     | Initial line length in pixels                                               |
| `scale`      | Multiplier applied to the line length on each generation advance            |
| `background` | Background color as a hex RGBA value (e.g. `0x000000ff` for black)         |
| `foreground` | Line color as a hex RGBA value (e.g. `0xffffffff` for white)               |

---

## Examples

Several pre-configured L-systems are included in the `examples/` folder, taken from the [Wikipedia article on L-systems](https://en.wikipedia.org/wiki/L-system#Examples_of_L-systems):

```
./lsystem.exe ./examples/fern.txt
./lsystem.exe ./examples/koch.txt
./lsystem.exe ./examples/sierpinski.txt
./lsystem.exe ./examples/dragon.txt
./lsystem.exe ./examples/binary.txt
```
