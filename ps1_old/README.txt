computing-4_ps1

Use GNU Make to build. (i.e. make)

Dependencies: SFML

Binary usage:

sierpinski <unsigned-int-recursion_depth> <unsigned-int-square_window_side_length>

original <unsigned-int-initial-recursion_depth> <unsigned-int-square_window_side_length>

Parameter defaults:

Base radial spokes per iteration: 0
Ratio between parent and child lines: 0.8
Relationship between radial spokes per iteration and recursion depth: FIXED (key M)

Keybindings for original (fractal generator)

Q: Quit

I: Increase recursion depth by 1
U: Decrease recursion depth by 1

E: Increase base number of radial spokes per iteration by 1
W: Decrease base number of radial spokes per iteration by 1

R: Increase ratio between parent and child lines by 0.05
T: Decrease ratio between parent and child lines by 0.05

M: Calculate number of radial spokes as fixed to the base value (This is the only true fractal mode)
N: Calculate number of radial spokes as increasing arithmetically with recursion depth
B: Calculate number of radial spokes as increasing geometrically with recursion depth


TODO: Add a keybind to modify initial window length to first line ratio