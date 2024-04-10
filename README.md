# fourier-series

A graphical visualiser and a browser for Fourier series expansion of arbitrary 2D Signals or Drawings!

# TODO

* Menu system (with blinking rectangle):
A : Adds a new harmonic
E : Removes the harmonic with highest frequency
R : Reset the input signal
Q : [Toggle] Render all harmonics
S : [Toggle] Render input signal
D : [Toggle] Render cycoids
Space : [Toogle] Slow motion close up

* SVG Input

## Instruction to build the project

Hi! First of all, thank you for somehow landing on this page.

The following pictures and videos should be enough for most people, but in the case it is not enough to quench you, my autodidact friend, here are the instructions to build and run the project:

Note: this project uses `cmake`, make sure that is installed, the minimum version for `cmake` is specified inside the CMakeLists.txt

```bash
cd fourier-series
mkdir build
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release #(or Debug)
./build/fourier_series
```

Something like the above should work, I've not tried it (yet) as I use Clion's UI.


## sampling bug - sample are very unevenly distributed in commit 607989e

![fourier-crudesampling-1](https://github.com/gyanantaran/fourier-series/assets/95016059/fa37a578-1b1f-45a9-aed6-431ddc4cad00)
![fourier-crudesampling-2](https://github.com/gyanantaran/fourier-series/assets/95016059/35dd0d5b-721b-4b56-98ef-f5012f546c40)

## weird bug - cycloids follow the cursor lazily in commit 8dae5c9

![weirdbug-laggingcycloid2](https://github.com/gyanantaran/fourier-series/assets/95016059/bdfebb0c-35d1-47d3-b874-032845a30ce3)

![weirdbug-laggingcycloid1](https://github.com/gyanantaran/fourier-series/assets/95016059/4ccad0a7-823b-4c68-9425-eb4f372669af)

## plotting and first tries at the analysis equation and final synthesis in commits before 872ba9f

![Screenshot 2024-04-06 at 11 12 53 PM](https://github.com/gyanantaran/fourier-series/assets/95016059/a6dfd1aa-0da3-49a8-ba19-c823e1ce5704)

![Screenshot 2024-04-06 at 11 14 36 PM](https://github.com/gyanantaran/fourier-series/assets/95016059/39a55aca-ad8d-4af7-b1aa-3e28ebe769df)

## cycloids and user input added in commit c429433

![cycloids-added](https://github.com/gyanantaran/fourier-series/assets/95016059/bfb33e67-1946-471a-8711-d8af4a072a0f)

![sketch-added](https://github.com/gyanantaran/fourier-series/assets/95016059/6ae25c6d-8180-472c-b2e0-98f05608e7e3)

