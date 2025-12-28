# 🎨 CLI Image Processor

A high-performance C++ command-line tool for manipulating raw pixel data. Built from scratch to understand memory management, pointer arithmetic, and image convolution algorithms.

## 🚀 Features

* **Zero-Dependency Core:** Uses direct memory manipulation for all image processing logic.
* **Custom Convolution Engine:** Implements a kernel-based 3x3 box blur algorithm.
* **Memory Safe:** Robust memory management preventing leaks and "Use-After-Free" errors.
* **Cross-Format Support:** Reads/Writes JPG, PNG, BMP, and TGA (via `stb_image`).

## 🛠️ How It Works

The tool loads an image into a 1D array of `unsigned char` bytes, manipulates the RGB channels directly via pointer arithmetic, and saves the result.

### Implemented Algorithms:
1.  **Grayscale:** Uses the Luminance formula `(0.3R + 0.59G + 0.11B)` to match human color perception, rather than a simple average.
2.  **Invert:** Bitwise negation of color channels `(255 - value)`.
3.  **Gaussian Blur:** Applies a 3x3 convolution kernel. For stronger effects, the kernel pass is iterated 50x.

## 🛠️ Build Instructions

### Prerequisites
* **Visual Studio 2022 (or any C++ compiler).

1. Clone the repo
	```bash
    git clone [https://github.com/Dronquavious/ImageProcessor.git](https://github.com/Dronquavious/ImageProcessor.git)
    ```
2. Open Project: Open ImageProcessor.slnx in Visual Studio.
3. Build: Press Ctrl + Shift + B or click Build Solution

## 💻 Usage

Run the tool from the command line:

```bash
./ImageProcessor <input_file> <output_file> <flag>
```

Examples:

# Convert to Grayscale
./ImageProcessor input.jpg output.png --grayscale

# Invert Colors (Negative)
./ImageProcessor input.jpg output.png --invert

# Apply Blur
./ImageProcessor input.jpg output.png --blur

## 📂 Project Structure

* `src/`: Main application source code
* `vendor/`: Third-party header-only libraries (stb_image).

## Dependencies
    // add


## 📄 License
This project is open source and under the MIT License. Feel free to use it for learning or as a base for your own ImageProcessor!

## Contact

If you have questions, feedback, or want to discuss the project, you can reach me at:

- GitHub: @Dronquavious
- Email: tambweamani@gmail.com

Feel free to reach out — I’m happy to talk about the project or help you get started.

