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

int ex_vc4_img_gray() {
    IVC *image;

    image = vc_read_image("../Images/FLIR/flir-01.pgm");
    if (image == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    if (vc_gray_negative(image) == 0) {
        vc_image_free(image);
        printf("ERROR -> vc_gray_negative():\n\tInvalid gray file!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_img_gray.pbm", image);
    vc_image_free(image);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_img_rgb() {
    IVC *image;

    image = vc_read_image("../Images/Classic/Boats.ppm");
    if (image == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    if (vc_rgb_negative(image) == 0) {
        vc_image_free(image);
        printf("ERROR -> vc_rgb_negative():\n\tInvalid rgb file!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_img_rgb.ppm", image);
    vc_image_free(image);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_img_red() {
    IVC *image;

    image = vc_read_image("../Images/Classic/pepper.ppm");
    if (image == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    if (vc_rgb_get_red_gray(image) == 0) {
        vc_image_free(image);
        printf("ERROR -> vc_rgb_get_red_gray():\n\tInvalid rgb file!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_img_red.ppm", image);
    vc_image_free(image);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_img_green() {
    IVC *image;

    image = vc_read_image("../Images/Classic/pepper.ppm");
    if (image == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    if (vc_rgb_get_green_gray(image) == 0) {
        vc_image_free(image);
        printf("ERROR -> vc_rgb_get_green_gray():\n\tInvalid rgb file!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_img_green.ppm", image);
    vc_image_free(image);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_img_blue() {
    IVC *image;

    image = vc_read_image("../Images/Classic/pepper.ppm");
    if (image == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    if (vc_rgb_get_blue_gray(image) == 0) {
        vc_image_free(image);
        printf("ERROR -> vc_rgb_get_blue_gray():\n\tInvalid rgb file!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_img_blue.ppm", image);
    vc_image_free(image);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_rbg_to_gray() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/Additional/cablecar.ppm");
    if (image_src == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image_dst = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_dst == NULL) {
        vc_image_free(image_src);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    if (vc_rgb_to_gray(image_src, image_dst) == 0) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_rgb_to_gray():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_img_rgb_to_gray.pbm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_rgb_to_hsv() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/HSV/HSVTestImage01.ppm");
    if (image_src == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image_dst = vc_image_new(image_src->width, image_src->height, 3, 255);
    if (image_dst == NULL) {
        vc_image_free(image_src);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    if (vc_rgb_to_hsv(image_src, image_dst) == 0) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_rgb_to_hsv():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_rgb_to_hsv.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_hsv_segmentation() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/HSV/HSVTestImage01.ppm");
    if (image_src == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image_dst = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_dst == NULL) {
        vc_image_free(image_src);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    if (vc_hsv_segmentation(image_src, image_dst, 30, 70, 50, 100, 60, 100) == 0) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_hsv_segmentation():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_hsv_segmentation.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc4_gray_to_rgb() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/OldClassic/bridge.pgm");
    if (image_src == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image_dst = vc_image_new(image_src->width, image_src->height, 3, 255);
    if (image_dst == NULL) {
        vc_image_free(image_src);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    if (vc_scale_gray_to_color_palette(image_src, image_dst) == 0) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_scale_gray_to_color_palette():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc4_gray_to_rgb.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_1() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/EX1/PET-Normal.ppm");
    if (image_src == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image_dst = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_dst == NULL) {
        vc_image_free(image_src);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    if (vc_hsv_segmentation(image_src, image_dst, 291 , 45, 50, 100, 60, 100) == 0) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_hsv_segmentation():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    printf("%d pixeis com 100%% de atividade.\n", vc_image_white_pixel_count(image_dst));

    vc_write_image("../output/vc_ex1.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int main() {
    //ex_vc3_1();
    //ex_vc3_2();
    //ex_vc3_3();

    //ex_vc4_img_gray();
    //ex_vc4_img_rgb();
    //ex_vc4_img_red();
    //ex_vc4_img_green();
    //ex_vc4_img_blue();
    //ex_vc4_rbg_to_gray();

    //ex_vc4_rgb_to_hsv();

    //ex_vc4_hsv_segmentation();

    //ex_vc4_gray_to_rgb();

    ex_1();
}