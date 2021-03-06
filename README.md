stl_cmd
=======

The goal of each stl_cmd is to provide a simple command line interface for manipulating binary STL files. stl_cmd aims to be easy to set up, and is geared towards teaching basic terminal usage and programming skills in the 3D printing space.   
If you have ASCII stl, you can use this repo: https://github.com/Carlopasquinucci/stlconvert

Getting started
---------------

    git clone https://github.com/AllwineDesigns/stl_cmd.git
    cd stl_cmd
    make
    make install # will install to /usr/local/bin by default
    
    make prefix=/some/other/path install # will install to /some/other/path/bin
    make DESTDIR=/some/other/path install # will install to /some/other/path/usr/local/bin
    make DESTDIR=/some/other/path prefix=/usr # will install to /some/other/path/usr/bin

The stl_cmds will be compiled and placed in the bin/ directory in the root of the stl_cmd repo. Add it to your path and you can perform the following commands.

stl_cmd releases are now a part of Debian! You can install them using apt-get.

    # on Debian unstable or Ubuntu bionic
    sudo apt-get install stlcmd

Examples
--------

You have an STL file specified in inches and you want to convert it to mm.

    stl_transform -s 25.4 my_file_inches.stl my_file_mm.stl

Discard stored normals and calculate them based on vertex ordering (can fix some broken stl files).

    stl_normals -c my_file.stl my_fixed_file.stl

Count the number of triangles in an STL file.

    stl_count my_file.stl

Set the header of your STL file to contain copyright information.

    stl_header -s "My File. Copyright <Your name> 2014." my_file.stl

STL Commands
------------

## Geometry Generators 

The following commands create STL files.

### stl_empty

    stl_empty <output file>

Outputs an empty binary STL file. Can be useful to initialize an empty STL file when merging several files together.

### stl_cube

    stl_cube [ -w <width> ] [ <output file> ]

Outputs a binary STL file of a cube with the provided width. If no output file is provided, data is sent to stdout.

### stl_sphere 

    stl_sphere [-r <radius> ] [ -s <longitudinal segments> ] [ -t <latitudinal segments> ] [ <output file> ]

Outputs an stl file of a sphere with the provided radius and number of segments.
If the radius is omitted, it defaults to 1. If longitudinal segments is omitted, it defaults to 32. If latitudinal segments is omitted, it defaults to half the longitudinal segments. If no output file is provided, data is sent to stdout.

### stl_cylinder 

    stl_cylinder [-r <radius> ] [-h <height>] [ -s <segments> ] [ <output file> ]

Outputs an stl file of a cylinder with the provided radius, height and number of segments.
If the radius or height are omitted, they default to 1. If segments is omitted, it defaults to 32. If no output file is provided, data is sent to stdout.

### stl_cone 

    stl_cone [-r <radius> ] [-t <top radius>] [-h <height>] [ -s <segments> ] [ <output file> ]

Outputs an stl file of a cone with the provided radius, top radius, height and number of segments.
If the radius or height are omitted, they default to 1. If top radius is omittted, it defaults to 0. If top radius is greater than 0, it outputs a truncated cone. If segments is omitted, it defaults to 32. If no output file is provided, data is sent to stdout.

### stl_torus 

    stl_torus [-o <outer radius> ] [-i <inner radius>] [ -s <segments> ] [ -c <cross sectional segments> ] [ <output file> ]

Outputs an stl file of a torus with the provided inner radius, outter radius, and number of segments.
If the inner radius is omitted, it defaults to .5. If outer radius is omittted, it defaults to 1. If segments is omitted, it defaults to 32. If cross sectional segments is omitted, it defaults to half the segments. If no output file is provided, data is sent to stdout.

### stl_threads

    stl_threads [ -f ] [ -D <diameter> ] [ -P <pitch> ] [ -a <angle> ] 
                [ -h <height> ] [ -s <segments> ] <output file>

Outputs an stl file with male or female screw threads per the [ISO metric
screw thread standard](http://en.wikipedia.org/wiki/ISO_metric_screw_thread).

    -f            - Outputs female threads (defaults to male).
    -D <diameter> - Changes to major diameter of the threads.
    -P <pitch>    - Changes the height of a single thread, aka the pitch per 
                    the ISO metric standard.
    -h <height>   - Changes the total height of the threads.
    -a <angle>    - Changes the thread angle (degrees). The standard (and 
                    default) is 60 degrees. For 3D printing this can cause 
                    overhang issues as 60 degrees results in a 30 degree 
                    angle with the ground plane. Setting to 90 degrees 
                    results in a 45 degree angle with the ground plane.
    -s <segments> - Changes the resolution of the generated STL file. More 
                    segments yields finer resolution. <segments> is the 
                    number of segments to approximate a circle. Defaults to 
                    72 (every 5 degrees).

## Informational

The following commands display information about STL files. In some cases, they
make modifications to the STL files related to that information.

### stl_header

    stl_header [-s <header>] [-o <output file>] <input file>

Prints or sets the data in the header section of a binary STL file. The header section is rarely used, but can store a small amount of data (80 characters). Copyright info or a very brief description are some possibilities.

### stl_count

    stl_count [ <input file> ]

Prints the number of triangles in the provided binary STL file. If no input file is provided, data is read from stdin.

### stl_normals

    stl_normals [ -v ] [ -c ] [ -r ] [ <input file> ] [ <out file> ]

Compares normals stored in input file with normals calculated from the vertex ordering. Provided flags can tell stl_normals to fix the normals or reverse the point ordering.

### stl_bbox

    stl_bbox <input file>

Prints bounding box information about the provided binary STL file.

### stl_convex 

    stl_convex [ -v ] <input file>

Determines whether an STL file is a convex polyheda by calculating Euler's characteristic.
Prints convex if the STL file is convex, or not convex otherwise. If the -v flag is used
a verbose message is printed that shows the calculation.

### stl_borders 

    stl_borders <input file>

Outputs the number of border edges in the STL files. This should be 0 for manifold meshes. If the output is greater than 0, the mesh has holes in it or has non-manifold edges.

### stl_spreadsheet

    stl_spreadsheet <input file>

Outputs normal and position data for every triangle (normal, point1, point2 and point3 specified per row) in a tab delimited format that can be opened as a spreadsheet.   

### stl_volume  

    stl_cone [file.stl]   
    
Calculate the volume of STL files (could used for price or print time approximations)      

## Modifiers

These commands modify existing STL files.

### stl_merge

    stl_merge [ -o <output file> ] [ <input file> ... ]

Combines binary STL files into a single one. If no output file is provided, data is written to stdout.

### stl_transform

    stl_transform [[ <transformation> ] ...] <input file> <output file>

Performs any number of transformations in the order listed on the command line. Transformations include:

    -rx <angle> - rotates <angle> degrees about the x-axis
    -ry <angle> - rotates <angle> degrees about the y-axis
    -rz <angle> - rotates <angle> degrees about the z-axis
    -s <s> - uniformly scales x, y and z by <s> (cannot be 0)
    -sx <x> - scales by <x> in x (cannot be 0)
    -sy <y> - scales by <y> in y (cannot be 0)
    -sz <z> - scales by <z> in z (cannot be 0)
    -tx <x> - translates <x> units in x
    -ty <y> - translates <y> units in y
    -tz <z> - translates <z> units in z

### stl_boolean 

    stl_boolean -a <STL file A> -b <STL file B> [ -i ] [ -u ] [ -d ] <out file>

Performs a CSG boolean operation on STL files A and B using BSP trees. -i will perform the intersection of A and B. -u will 
perform the union of A and B. -d will perform the difference of A and B.

Future commands
---------------

These are ideas for future commands that may make it into the stl_cmd suite.

### stl_hull

Compute the convex hull of the input STL files.

### stl_area

Calculate the surface area of STL files (could be used for price or print time approximations)

### stl_layout

Layout a number of stl files on the Z = 0 plane, possibly even attempting to find the flattest side to place each file on.

### stl_zero or stl_center

Centers the STL file, with options to put the bottom of the model on the Z = 0 plane.

### stl_segments 

Extrude a circle or sweep a sphere along a piecewise linear curve.

### stl_bezier

Extrude a circle or sweep a sphere along a Bezier curve (would probably approximate the Bezier with some number of linear segments and use the same algorithm as stl_segments).

### stl_decimate 

Simplify an STL file while preserving its shape.

### stl_twist

Deform an STL file by twisting it.

### stl_bend

Deform an STL file by bending it.

### stl_noise

Deform an STL file by displacing vertices using noise.

Teaching
--------

The goal of this project is to be a resource for teaching terminal usage and some basic programming concepts in the 3D printing space. Imagine an assignment which involves building a brick wall. Students would need to use a combination of stl_cube, stl_transform and stl_merge. The commands could be combined in a bash or &lt;insert favorite scripting language&gt; script with for and while loops, could accept input and use conditionals to affect the attributes of the wall. 

The terminal is an important tool to learn when programming, but can be boring to learn when just making text based programs. stl_cmd aims to make the intro level terminal usage and programming more interesting by creating 3D printable models. As more commands are added more creative assignments are possible. I hope to grow the suite of commands included in stl_cmd with that goal in mind. 

Copyright 2014 Freakin' Sweet Apps, LLC (stl_cmd@freakinsweetapps.com)
