#include <stdio.h>
#include "vc.h"

int ex_vc3_1() {
	IVC *image;
	int x, y;
	long int pos;
	
	image = vc_image_new(256, 256, 1, 255);
	if (image == NULL) {
		printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
		getchar();
		return 0;
	}

	for (x = 0; x < image->width; x++) {
		for (y = 0; y < image->height; y++) {
			pos = y * image->bytesperline + x * image->channels;

			image->data[pos] = x;
		}
	}

	vc_write_image("../output/image_vc3_1.pbm", image);
	vc_image_free(image);

	printf("Press any key to exit...\n");
	getchar();

	return 0;
}

int ex_vc3_2() {
	IVC* image;
	int x, y;
	long int pos;

	image = vc_image_new(256, 256, 1, 255);
	if (image == NULL) {
		printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
		getchar();
		return 0;
	}

	for (x = 0; x < image->width; x++) {
		for (y = 0; y < image->height; y++) {
			pos = y * image->bytesperline + x * image->channels;

			image->data[pos] = y;
		}
	}

	vc_write_image("../output/image_vc3_2.pbm", image);
	vc_image_free(image);

	printf("Press any key to exit...\n");
	getchar();

	return 0;
}

int ex_vc3_3() {
	IVC* image;
	int x, y;
	long int pos;

	image = vc_image_new(256, 256, 1, 255);
	if (image == NULL) {
		printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
		getchar();
		return 0;
	}

	for (x = 0; x < image->width; x++) {
		for (y = 0; y < image->height; y++) {
			pos = y * image->bytesperline + x * image->channels;

			image->data[pos] = (unsigned char) ((x + y) / 2);
		}
	}
	 
	vc_write_image("../output/image_vc3_e.pbm", image);
	vc_image_free(image);
	
	printf("Press any key to exit...\n");
	getchar();

	return 0;
}

int main() {
    ex_vc3_1();
    ex_vc3_2();
    ex_vc3_3();
}