# Brut voronoi example

This example shows the brut voronoi generation's result.

## Execution

Those commands are executed from the project root.
This script should be used with small dimensions
since it is really expensive.

```shell script
# Create the dist folder
make

# Generate an image of 250 x 250 (w * h) with 250 germs (-g).
# The -p flags allows you to preview the resulting image.
# You can use the -d flag to specify which method must
# be used to perform distance calculation.
# Use `./dist/BrutVoronoi --help` to see the other distances. 
./dist/BrutVoronoi -w 250 -h 250 -g 250 -p -d D1 -o execution-example/brut-voronoi-example/command-result.jpg

Command output -> 15625000 iterations in 1s%
```


## Command result

![result](command-result.jpg)