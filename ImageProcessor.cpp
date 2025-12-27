#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char* argv[])
{

	if (argc < 3) {
		std::cout << "Usage: ImageProcessor <input_file> <output_file>" << std::endl;
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

	std::cout << "Success!" << std::endl;
	std::cout << "Width: " << width << " Height: " << height << " Channels: " << channels << std::endl;


	const int pixel_width = 4;

	size_t img_size = width * height * pixel_width;

	// channels go in this order [r,g,b,a] *p -> r so to to change g,b or a *(p + index)

	// grayscale = (red * 0.3) + (green * 0.59) + (blue * 0.11)

	for (unsigned char* p = image_data; p != image_data + img_size; p += pixel_width) {

		float red =(float) *p;
		float green = (float) *(p + 1);
		float blue = (float) *(p + 2);

		float grayValue = (red * 0.3f) + (green * 0.59f) + (blue * 0.11f);

		unsigned char grayscale = (unsigned char)grayValue;

		*p = grayscale;
		*(p + 1) = grayscale;
		*(p + 2) = grayscale;

	}

	stbi_write_png(argv[2], width, height, pixel_width, image_data, width * pixel_width);

	stbi_image_free(image_data);


	return 0;
}
