# Seam_Carving_Image_C++

Seam Carving is a content aware image-resizing algorithm where the image is reduced in size by one pixel of height (or width) at a time.

A vertical seam in an image is a path of pixels connected from the top to the bottom with one pixel in each row.
A horizontal seam is a path of pixels connected from the left to the right with one pixel in each column.

Steps:
○ Energy Calculation: Each pixel has some RGB values. Calculate energy for each pixel.
For ex.- You can use dual-gradient energy function. You can refer to this link for details
"https://www.cs.princeton.edu/courses/archive/fall17/cos226/assignments/seam/index.html".

○ Seam Identification: Identify the lowest energy seam.

○ Seam Removal: Remove the lowest energy seam.

Python Script extracts the individual pixel’s RGB values from the image, writes them to rgb_in.txt file and loads them in a 3D Matrix "rgb". Also, it will write RGB values into rgb_out.txt file after successfully applying Seam Carving algorithm from main.cpp file and generate image from the rgb_out.txt file.

Dependencies:
Pillow - Python Image Library

Note: Python script is only compatible with Linux Operating System.

How to Run:
python3 ./src/driver.py sample1.jpeg

Sample Input (366 x 605):

![sample4](https://user-images.githubusercontent.com/58835108/188721548-3025e18d-177d-4a06-9412-6b737b2f5906.jpeg)

Sample Output (300 x 400):

![sample_out_4](https://user-images.githubusercontent.com/58835108/188721518-6d3fd83f-47d0-4083-9d39-2470ae42df54.jpeg)
