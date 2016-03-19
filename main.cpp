#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(const int x0, const int y0, const int x1, const int y1, TGAImage& image, const TGAColor& color) {
	int dx = x1 - x0;
	int dy = y1 - y0;
	int d_error = (2 * dy) - dx;

	int y = y0;

	for (int x = x0; x <= x1; ++x) {
		image.set(x, y, color);
		d_error += 2 * dy;
		if (d_error > 0) {
			y += 1;
			d_error -= 2 * dx;
		}
	}
}

int main(int argc, char** argv) {
	TGAImage image(500, 500, TGAImage::RGB);

	line(100, 100, 250, 130, image, red);
	image.set(99, 100, white);
	image.set(251, 130, white);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
