#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>


#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../vendor/stb_image_write.h"

void filter_grayscale(unsigned char* image, int width, int height, int channels) {
	size_t img_size = width * height * channels;

	// channels go in this order [r,g,b,a] *p -> r so to to change g,b or a *(p + index)

	// grayscale = (red * 0.3) + (green * 0.59) + (blue * 0.11)

	for (unsigned char* p = image; p != image + img_size; p += channels) {

		float red = (float)*p;
		float green = (float)*(p + 1);
		float blue = (float)*(p + 2);

		float grayValue = (red * 0.3f) + (green * 0.59f) + (blue * 0.11f);

		unsigned char grayscale = (unsigned char)grayValue;

		*p = grayscale;
		*(p + 1) = grayscale;
		*(p + 2) = grayscale;

	}
}

void filter_invert(unsigned char* image, int width, int height, int channels) {
	size_t img_size = width * height * channels;

	// channels go in this order [r,g,b,a] *p -> r so to to change g,b or a *(p + index)
	// to invert a color new_color = 255 - old_color
	for (unsigned char* p = image; p != image + img_size; p += channels) {
		*p = 255 - *p;
		*(p + 1) = 255 - *(p + 1);
		*(p + 2) = 255 - *(p + 2);
	}

}

void filter_blur(unsigned char* image, int width, int height, int channels) {
	// create a copy of the image so we don't read "changed" pixels
	unsigned char* copy = new unsigned char[width * height * channels];

	// copy the actual data bytes
	memcpy(copy, image, width * height * channels);

	// loop through every pixel (skipping the 1-pixel border)
	// x and y coordinates cause its easier to find neighbors than using pointers
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {

			// hold the sum of colors
			int sum_r = 0;
			int sum_g = 0;
			int sum_b = 0;

			// loop through the 3x3 grid around the current pixel (x, y).
			// The grid goes from (x-1, y-1) to (x+1, y+1).

			for (int ky = -1; ky <= 1; ky++) {
				for (int kx = -1; kx <= 1; kx++) {
					int neightbor_index = ((y + ky) * width + (x + kx)) * channels;

					// channels go in this order [r,g,b,a] *p -> r so to to change g,b or a *(p + index)

					sum_r += copy[neightbor_index];
					sum_g += copy[neightbor_index + 1];
					sum_b += copy[neightbor_index + 2];

				}
			}


			// average the sums
			unsigned char avg_r = sum_r / 9;
			unsigned char avg_g = sum_g / 9;
			unsigned char avg_b = sum_b / 9;

			// new values to the ORIGINAL image
			int current_pixel_index = (y * width + x) * channels;
			image[current_pixel_index] = avg_r;
			image[current_pixel_index + 1] = avg_g;
			image[current_pixel_index + 2] = avg_b;
		}
	}

	// clean up
	delete[] copy;
}

int main(int argc, char* argv[])
{

	if (argc < 4) {
		std::cout << "Usage: ImageProcessor <input_file> <output_file> <FLAG>" << std::endl;
		return -1;
	}

	// hold image data
	int width, height, channels;

	// load image
	unsigned char* image_data = stbi_load(argv[1], &width, &height, &channels, 4);

	// checking if it worked
	if (image_data == nullptr) {
		std::cout << "Error: Could not load image!" << std::endl;
		return 1;
	}

	if (strcmp(argv[3], "--gray") == 0) {
		filter_grayscale(image_data, width, height, 4);
	}
	else if (strcmp(argv[3], "--invert") == 0) {
		filter_invert(image_data, width, height, 4);
	}
	else if (strcmp(argv[3], "--blur") == 0) {
		std::cout << "Blurring 50 times..." << std::endl;
		for (int i = 0; i < 50; i++) {
			filter_blur(image_data, width, height, 4);
		}
	}
	else {
		std::cout << "Uknown Filter" << std::endl;
		std::cout << "Available filters: --gray, --invert, --blur" << std::endl;
		return -1;
	}


	stbi_write_png(argv[2], width, height, 4, image_data, width * 4);
	std::cout << "IMAGE PROCESSED";


	stbi_image_free(image_data);


	return 0;
}
