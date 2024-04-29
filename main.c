#include <stdio.h>
#include <malloc.h>
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
    float count100, count75, count50, count25, totalPixels;

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

    // Obter cor vermelha
    vc_hsv_segmentation(image_src, image_dst, 291 , 45, 50, 100, 60, 100);
    count100 = vc_image_white_pixel_count(image_dst);

    // Obter cor amarela
    vc_hsv_segmentation(image_src, image_dst, 46 , 70, 50, 100, 60, 100);
    count75 = vc_image_white_pixel_count(image_dst);

    // Obter cor verde
    vc_hsv_segmentation(image_src, image_dst, 71 , 160, 50, 100, 60, 100);
    count50 = vc_image_white_pixel_count(image_dst);

    // Obter cor azul
    vc_hsv_segmentation(image_src, image_dst, 161 , 290, 50, 100, 60, 100);
    count25 = vc_image_white_pixel_count(image_dst);

    // Obter pixeis pretos e depois fazer o negativo deles
    vc_hsv_segmentation(image_src, image_dst, 0, 360, 0, 50, 0, 30);
    vc_gray_negative(image_dst);
    totalPixels = vc_image_white_pixel_count(image_dst);

    printf("Percentagem de atividade ate 25: %.2f\n", (count25 + (totalPixels - count100 - count75 - count50 - count25)) / totalPixels * 100);
    printf("Percentagem de atividade ate 50: %.2f\n", count50 / totalPixels * 100);
    printf("Percentagem de atividade ate 75: %.2f\n", count75 / totalPixels * 100);
    printf("Percentagem de atividade ate 100: %.2f\n", count100 / totalPixels * 100);

    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc5_gray_to_binary() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/Other/gray-01.pgm");
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

    if (vc_gray_to_binary(image_src, image_dst, 10) != 1) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_gray_to_binary():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc5_gray_to_binary.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc5_gray_to_binary_global_mean() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/Other/gray-01.pgm");
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

    if (vc_gray_to_binary_global_mean(image_src, image_dst) != 1) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_gray_to_binary_global_mean():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc5_gray_to_binary_global_mean.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc5_gray_to_binary_midpoint() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/Other/gray-01.pgm");
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

    if (vc_gray_to_binary_midpoint(image_src, image_dst, 25) != 1) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_gray_to_binary_midpoint():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc5_gray_to_binary_midpoint.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc5_gray_to_binary_niblac() {
    IVC *image_src, *image_dst;

    image_src = vc_read_image("../Images/Other/gray-01.pgm");
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

    if (vc_gray_to_binary_niblac(image_src, image_dst, 25, -0.2) != 1) {
        vc_image_free(image_src);
        vc_image_free(image_dst);
        printf("ERROR -> vc_gray_to_binary_niblac():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc5_gray_to_binary_niblac.ppm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc5_binary_dilate() {
    IVC *image_src, *image_gray, *image_dst;

    image_src = vc_read_image("../Images/operadores_morfologicos/flir-01.pgm");
    if (image_src == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image_gray = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_gray == NULL) {
        vc_image_free(image_src);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    if (vc_gray_to_binary(image_src, image_gray, 210) != 1) {
        vc_image_free(image_src);
        vc_image_free(image_gray);
        printf("ERROR -> vc_gray_to_binary():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    image_dst = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_dst == NULL) {
        vc_image_free(image_src);
        vc_image_free(image_gray);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    if (vc_binary_dilate(image_gray, image_dst, 7) != 1) {
        vc_image_free(image_src);
        vc_image_free(image_gray);
        vc_image_free(image_dst);
        printf("ERROR -> vc_binary_dilate():\n\tCan't convert the image!\n");
        getchar();
        return 0;
    }

    vc_write_image("../output/vc5_binary_dilate.pgm", image_dst);
    vc_image_free(image_src);
    vc_image_free(image_gray);
    vc_image_free(image_dst);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_2() {
    IVC *image_src, *image_gray, *image_cranio, *image_brain, *image_brain2;

    image_src = vc_read_image("../Images/EX2/brain.pgm");
    if (image_src == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image_gray = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_gray == NULL) {
        vc_image_free(image_src);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    image_cranio = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_cranio == NULL) {
        vc_image_free(image_src);
        vc_image_free(image_gray);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    image_brain = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_brain == NULL) {
        vc_image_free(image_src);
        vc_image_free(image_gray);
        vc_image_free(image_cranio);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    image_brain2 = vc_image_new(image_src->width, image_src->height, 1, 255);
    if (image_brain2 == NULL) {
        vc_image_free(image_src);
        vc_image_free(image_gray);
        vc_image_free(image_cranio);
        vc_image_free(image_brain);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    vc_gray_to_binary(image_src, image_gray, 205);
    vc_binary_dilate(image_gray, image_cranio, 5);

    vc_gray_to_binary(image_src, image_gray, 60);
    vc_binary_erode(image_gray, image_brain, 5);

    for (int i = 0; i < image_cranio->height * image_cranio->width; i++) {
        if (image_cranio->data[i] == 255) {
            image_brain->data[i] = 0;
        }
    }

    vc_binary_open(image_brain, image_brain2, 5, 13);

    for (int i = 0; i < image_brain2->height * image_brain2->width; i++) {
        if (image_brain2->data[i] != 255) {
            image_src->data[i] = 0;
        }
    }

    vc_write_image("../output/brain.pgm", image_src);
    vc_image_free(image_src);
    vc_image_free(image_gray);
    vc_image_free(image_cranio);
    vc_image_free(image_brain);
    vc_image_free(image_brain2);

    printf("Press any key to exit...\n");
    getchar();

    return 0;
}

int ex_vc7_labeling() {
    IVC *image[4];
    int i;

    image[0] = vc_read_image("../Images/Labelling/labelling-2.pgm");
    if (image[0] == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image[1] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if (image[1] == NULL) {
        vc_image_free(image[0]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    int nblobs;
    OVC *blobs;
    blobs = vc_binary_blob_labelling(image[0], image[1], &nblobs);

    if (blobs != NULL) {
        printf("\nNumber of labels: %d\n", nblobs);
        for (i = 0; i<nblobs; i++) {
            printf("-> Label %d\n", blobs[i].label);
        }

        free(blobs);
    }

    image[2] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if (image[2] == NULL) {
        vc_image_free(image[0]);
        vc_image_free(image[1]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }
    image[3] = vc_image_new(image[0]->width, image[0]->height, 3, 255);
    if (image[3] == NULL) {
        vc_image_free(image[0]);
        vc_image_free(image[1]);
        vc_image_free(image[2]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    vc_blob_to_gray_scale(image[1], image[2], nblobs);
    vc_blob_to_gray_rgb(image[1], image[3], nblobs);

    vc_write_image("../output/vc7_labeling.pgm", image[1]);
    vc_write_image("../output/vc7_labeling_gray.pgm", image[2]);
    vc_write_image("../output/vc7_labeling_rgb.ppm", image[3]);

    vc_image_free(image[0]);
    vc_image_free(image[1]);
    vc_image_free(image[2]);
    vc_image_free(image[3]);

    return 0;
}

int ex_vc7_labelling2() {
    IVC *image[4];

    image[0] = vc_read_image("../Images/Labelling2/input.ppm");
    if (image[0] == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image[1] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if (image[1] == NULL) {
        vc_image_free(image[0]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    image[2] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if (image[2] == NULL) {
        vc_image_free(image[0]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    image[3] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if (image[3] == NULL) {
        vc_image_free(image[0]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    //Obter apenas bonecos azuis
    vc_hsv_segmentation(image[0], image[1], 190, 250, 50, 100, 30, 100);

    //Dilatar a imagem para juntar a cabeça ao corpo
    vc_binary_dilate(image[1], image[2], 3);

    //Obter os blobs da imagem (o lugar de cada boneco)
    int nblobs;
    OVC *blobs;
    blobs = vc_binary_blob_labelling(image[2], image[3], &nblobs);

    if (blobs != NULL) {
        printf("\nNumber of labels: %d\n", nblobs);

        //Obter as informações do blob
        vc_binary_blob_info(image[3], blobs, nblobs);

        for (int i = 0; i < nblobs; i++) {
            vc_draw_center_of_gravity(image[1], &blobs[i], 5);
            vc_draw_bounding_box(image[1], &blobs[i]);
        }

        free(blobs);
    }

    vc_write_image("../output/vc7_labeling2.ppm", image[1]);
    vc_image_free(image[0]);
    vc_image_free(image[1]);
    vc_image_free(image[2]);
    vc_image_free(image[3]);

    return 0;
}

int ex_vc8_histogram_show() {
    IVC *image[2];

    image[0] = vc_read_image("../Images/Histograma/barbara.pgm");
    if (image[0] == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image[1] = vc_image_new(256, 256, 1, 255);
    if (image[1] == NULL) {
        vc_image_free(image[0]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    vc_gray_histogram_show(image[0], image[1]);

    vc_write_image("../output/vc8_histogram_show.ppm", image[1]);
    vc_image_free(image[0]);
    vc_image_free(image[1]);

    return 0;
}

int ex_vc8_gray_histogram_equalization() {
    IVC *image[3];

    image[0] = vc_read_image("../Images/Histograma/barbara.pgm");
    if (image[0] == NULL) {
        printf("ERROR -> vc_read_image():\n\tFile not found!\n");
        getchar();
        return 0;
    }

    image[1] = vc_image_new(image[0]->width, image[0]->height, 1, 255);
    if (image[1] == NULL) {
        vc_image_free(image[0]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    image[2] = vc_image_new(256, 256, 1, 255);
    if (image[2] == NULL) {
        vc_image_free(image[0]);
        vc_image_free(image[1]);
        printf("ERROR -> vc_image_new():\n\tOut of memory!\n");
        getchar();
        return 0;
    }

    vc_gray_histogram_equalization(image[0], image[1]);
    vc_gray_histogram_show(image[1], image[2]);

    vc_write_image("../output/vc8_gray_histogram_equalization.ppm", image[1]);
    vc_write_image("../output/vc8_gray_histogram_equalization_histo.ppm", image[2]);
    vc_image_free(image[0]);
    vc_image_free(image[1]);
    vc_image_free(image[2]);

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

    //ex_1();

    //ex_vc5_gray_to_binary();
    //ex_vc5_gray_to_binary_global_mean();
    //ex_vc5_gray_to_binary_midpoint();

    //ex_vc5_gray_to_binary_niblac();
    //ex_vc5_binary_dilate();

    //ex_2();

    //ex_vc7_labeling();

    //ex_vc7_labelling2();

    ex_vc8_histogram_show();

    ex_vc8_gray_histogram_equalization();
}