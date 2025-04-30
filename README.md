# fourier-series

<img width="1469" alt="fourier" src="https://github.com/gyanantaran/fourier-series/assets/95016059/b495bf30-01a0-4fec-a257-942830ec513d">

<img width="1469" alt="zoomed-fourier" src="https://github.com/gyanantaran/fourier-series/assets/95016059/1f9a1961-4517-4607-b35d-7d241ea2ba20">


## Contributing

Contributions are welcome! Feel free to open a pull request or submit an issue if you find any bugs or have any suggestions for new features.


## Introduction

Fourier Series is a fascinating mathematical concept that can be used to break down signals into their component harmonics, in a variety of complex situations -- in our case 2D drawings. By simulating these systems, we can gain a better understanding of how the calculation for fourier-series works and how order (drawings) emerge from clockwork chaos (precise cycloids).

This project is a simulation of fourier-series approximation of arbritrary 2D drawings, with cycloids that combined with each other, trace out the approximation to a given drawing. In this simulation, one can start off with a low number of harmonics and a simple drawn images (svgs) that are nice and easy to approximate (infinity sign, twitter logo). Then one after the other one may start adding more harmonics and see the approximations get better drawn, reactively. At the end we find that even with an extremely small number of harmonics (50 for example), the approximation are good enough and that the motion of the tip of cycloids (the very last cycloid) is seeming chaotic but exactly, scriplty organised.


## Some example demos

https://github.com/gyanantaran/fourier-series/assets/95016059/26279f60-5b23-4220-b8c5-61a4fe31d6ae

https://github.com/gyanantaran/fourier-series/assets/95016059/68d1814a-8531-4eca-a2db-c6e7b3e47850

https://github.com/gyanantaran/fourier-series/assets/95016059/6f9a225e-e1a2-41cf-9b52-4291721348ef



## Instruction to build the project

### Desktop

Here are the instructions to build and run the project:

Note: this project uses `cmake`, make sure that is installed, the minimum version for `cmake` is specified inside the CMakeLists.txt

```bash
cd fourier-series
cmake -DCMAKE_BUILD_TYPE=Release -S . -B ./build/
cd ./build/
make
cd ..
./build/fourier_series
```

### Web

Compiling for the web requires the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html):

```bash
mkdir build
cd build
emcmake cmake .. -DPLATFORM=Web -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXECUTABLE_SUFFIX=".html"
emmake make
python -m http.server 8080
```

Then, go to the URL `http://localhost:8080/fourier_series.html`.


## Logs and Bugs

The following registers the interesting bugs and milestones I came over the way.

### sampling bug - sample are very unevenly distributed in commit `#607989e`

![fourier-crudesampling-1](https://github.com/gyanantaran/fourier-series/assets/95016059/fa37a578-1b1f-45a9-aed6-431ddc4cad00)
![fourier-crudesampling-2](https://github.com/gyanantaran/fourier-series/assets/95016059/35dd0d5b-721b-4b56-98ef-f5012f546c40)

### weird bug - cycloids follow the cursor lazily in commit `#8dae5c9`

![weirdbug-laggingcycloid2](https://github.com/gyanantaran/fourier-series/assets/95016059/bdfebb0c-35d1-47d3-b874-032845a30ce3)

![weirdbug-laggingcycloid1](https://github.com/gyanantaran/fourier-series/assets/95016059/4ccad0a7-823b-4c68-9425-eb4f372669af)

### plotting and first tries at the analysis equation and final synthesis in commits before 872ba9f

![Screenshot 2024-04-06 at 11 12 53 PM](https://github.com/gyanantaran/fourier-series/assets/95016059/a6dfd1aa-0da3-49a8-ba19-c823e1ce5704)

![Screenshot 2024-04-06 at 11 14 36 PM](https://github.com/gyanantaran/fourier-series/assets/95016059/39a55aca-ad8d-4af7-b1aa-3e28ebe769df)

### cycloids and user input added in commit `#c429433`

![cycloids-added](https://github.com/gyanantaran/fourier-series/assets/95016059/bfb33e67-1946-471a-8711-d8af4a072a0f)

![sketch-added](https://github.com/gyanantaran/fourier-series/assets/95016059/6ae25c6d-8180-472c-b2e0-98f05608e7e3)


# Additional explorations for autodidacts and builders

If you want to further study and understand fourier-series and fourier transform, here are the resources I used:

1. [But what is a Fourier series? - 3b1b](https://www.youtube.com/embed/r6sGWTCMz2k?si=qhbYiE5w86cLLsef)
2. [2D Signal approximation ... - Pezzza's Work](https://www.youtube.com/embed/dRgFjYEURg8?si=I5HEyx18BxcU4hxI)
3. [But what is the Fourier Transform? - 3b1b](https://www.youtube.com/embed/spUNpyF58BY?si=b3UbnPR6uXIgkl5D)
4. [The more general uncertainty principle ... - 3b1b](https://www.youtube.com/embed/MBnnXbOM5S4?si=2NRGkbRGAD169CYX)


# Licence

This project is licensed under the Creative Commons License. <!-- See the `LICENSE` file for more information. -->

<img width="1469" alt="zoomed-fourier" src="https://github.com/gyanantaran/fourier-series/assets/95016059/1f9a1961-4517-4607-b35d-7d241ea2ba20">

<img width="1469" alt="fourier" src="https://github.com/gyanantaran/fourier-series/assets/95016059/b495bf30-01a0-4fec-a257-942830ec513d">
