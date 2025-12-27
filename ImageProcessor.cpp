#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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
	else {
		std::cout << "Uknown Filter" << std::endl;
		std::cout << "Available filters: --grayscale, --invert" << std::endl;
		return -1;
	}


	stbi_write_png(argv[2], width, height, 4, image_data, width * 4);
	std::cout << "IMAGE PROCESSED";


	stbi_image_free(image_data);


	return 0;
}
