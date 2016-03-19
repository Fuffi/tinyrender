#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
		int dx = x1-x0;
		int dy = y1-y0;

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

		const bool steep = (std::abs(dx) < std::abs(dy));
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
				std::swap(dx, dy);
    }

		const bool ascending = (y1 > y0);

    const int derror2 = std::abs(dy) * 2;
		int error2 = 0;

    int y = y0;

    for (int x = x0; x <= x1; ++x) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (ascending ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

int main(int argc, char** argv) {
	TGAImage image(500, 500, TGAImage::RGB);

	line(100, 100, 250, 130, image, red);
	line(100, 100, 250, 70, image, red);
	line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(80, 40, 13, 20, image, red);
	image.set(99, 100, white);
	image.set(251, 130, white);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
