# fdf
FDF, an abbreviation for fil de fer, which in French means wireframe model.

<br/>

**This project is compilable on both Linux and MacOS.**

<br/>

## 1. Usage

- Use `--recurse-submodule` when cloning the repository.
- Run `make` in terminal to compile the program.
- Run `./fdf test_map_file`, in which `test_map_file` contains coordinates of the landscape as shown, where the horizontal and vertical positions
correspond to the abscissa and ordinate, and the values correspond to its altitude:
<p align="center">
<img 
    width="400" 
    alt="Screenshot 2023-01-08 at 16 17 11" 
    src="https://user-images.githubusercontent.com/99158692/211186872-ac6b6a3f-33a8-4ba5-be39-2a9585b8f2a1.png"
  >
</p>
  
<br/>

## 2. Approach

<p align="center">
<img 
    width="800" 
    alt="Screenshot 2023-01-08 at 15 56 43" 
    src="https://user-images.githubusercontent.com/99158692/211186535-97e197df-6554-4c02-823d-5665805c83dd.jpg"
  >
</p>

A wireframe is initially assumed to be a cuboid (see white outline), in which its length and width of the cuboid equate to the rows and columns
defined in the map_file, and the height can be defined by the altitude. By calculating the apparent height and width of the cuboid when projected to
2D space, specific value for the pixel distance between points can be obtained while attempting to fit the model as much onto the screen as possible.
