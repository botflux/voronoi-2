# Voronoi

## Execution examples

You can find execution examples [here](./execution-example).

## Compile project

```shell script
# It uses cmake
make build
```

## Usage

### Voronoi diagram generations

#### Brut approach

```shell script
# Generate an image of 250 x 250 (w * h) with 250 germs (-g).
# The -p flags allows you to preview the resulting image.
# You can use the -d flag to specify which method must
# be used to perform distance calculation.
# Use `./dist/BrutVoronoi --help` to see the other distances. 
./dist/BrutVoronoi -w 250 -h 250 -g 250 -p -d D1
```

##### Save the result

```shell script
# Use the -o flag to save the resulting diagram.
./dist/BrutVoronoi -w 300 -h 300 -g 250 -o hello.png -d DE
```

#### Sequential approach

```shell script
# Parameters have the same meaning as with BrutVoronoi
./dist/SequentialVoronoi -w 600 -h 600 -g 250 -p
# You can also save the result using the -o flag
./dist/SequentialVoronoi -w 600 -h 600 -g 250 -o result.jpg
```

### Image approximation

#### Brut approach

```shell script
# Generate a approximation of the given image.
./dist/BrutVoronoiApproximation -i ../image-example/example-0.png -g 3000 -p
```