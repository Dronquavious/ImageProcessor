#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main()
{
	// hold image data
	int width, height, channels;

	// load image
	unsigned char* image_data = stbi_load("test.jpg", &width, &height, &channels, 4);

	// checking if it worked
	if (image_data == nullptr) {
		std::cout << "Error: Could not load image!" << std::endl;
		return 1;
	}

	std::cout << "Success!" << std::endl;
	std::cout << "Width: " << width << " Height: " << height << " Channels: " << channels << std::endl;


	const int pixel_width = 4;

	size_t img_size = width * height * pixel_width;

	for (unsigned char* p = image_data; p != image_data + img_size; p += pixel_width) {

		*(p + 1) = 0;
		*(p + 2) = 0;
	}

	// save the image to a new file called "red_only.jpeg"
	stbi_write_png("red_only.jpeg", width, height, pixel_width, image_data, width * pixel_width);

	stbi_image_free(image_data);


	return 0;
}
