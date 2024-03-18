//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//           INSTITUTO POLIT�CNICO DO C�VADO E DO AVE
//                          2022/2023
//             ENGENHARIA DE SISTEMAS INFORM�TICOS
//                    VIS�O POR COMPUTADOR
//
//             [  DUARTE DUQUE - dduque@ipca.pt  ]
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Desabilita (no MSVC++) warnings de fun��es n�o seguras (fopen, sscanf, etc...)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "vc.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            FUNÇÕES: ALOCAR E LIBERTAR UMA IMAGEM
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// Alocar mem�ria para uma imagem
IVC *vc_image_new(int width, int height, int channels, int levels)
{
	IVC *image = (IVC *) malloc(sizeof(IVC));

	if(image == NULL) return NULL;
	if((levels <= 0) || (levels > 255)) return NULL;

	image->width = width;
	image->height = height;
	image->channels = channels;
	image->levels = levels;
	image->bytesperline = image->width * image->channels;
	image->data = (unsigned char *) malloc(image->width * image->height * image->channels * sizeof(char));

	if(image->data == NULL)
	{
		return vc_image_free(image);
	}

	return image;
}


// Libertar mem�ria de uma imagem
IVC *vc_image_free(IVC *image)
{
	if(image != NULL)
	{
		if(image->data != NULL)
		{
			free(image->data);
			image->data = NULL;
		}

		free(image);
		image = NULL;
	}

	return image;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    FUN��ES: LEITURA E ESCRITA DE IMAGENS (PBM, PGM E PPM)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


char *netpbm_get_token(FILE *file, char *tok, int len)
{
	char *t;
	int c;
	
	for(;;)
	{
		while(isspace(c = getc(file)));
		if(c != '#') break;
		do c = getc(file);
		while((c != '\n') && (c != EOF));
		if(c == EOF) break;
	}
	
	t = tok;
	
	if(c != EOF)
	{
		do
		{
			*t++ = c;
			c = getc(file);
		} while((!isspace(c)) && (c != '#') && (c != EOF) && (t - tok < len - 1));
		
		if(c == '#') ungetc(c, file);
	}
	
	*t = 0;
	
	return tok;
}


long int unsigned_char_to_bit(unsigned char *datauchar, unsigned char *databit, int width, int height)
{
	int x, y;
	int countbits;
	long int pos, counttotalbytes;
	unsigned char *p = databit;

	*p = 0;
	countbits = 1;
	counttotalbytes = 0;

	for(y=0; y<height; y++)
	{
		for(x=0; x<width; x++)
		{
			pos = width * y + x;

			if(countbits <= 8)
			{
				// Numa imagem PBM:
				// 1 = Preto
				// 0 = Branco
				//*p |= (datauchar[pos] != 0) << (8 - countbits);
				
				// Na nossa imagem:
				// 1 = Branco
				// 0 = Preto
				*p |= (datauchar[pos] == 0) << (8 - countbits);

				countbits++;
			}
			if((countbits > 8) || (x == width - 1))
			{
				p++;
				*p = 0;
				countbits = 1;
				counttotalbytes++;
			}
		}
	}

	return counttotalbytes;
}


void bit_to_unsigned_char(unsigned char *databit, unsigned char *datauchar, int width, int height)
{
	int x, y;
	int countbits;
	long int pos;
	unsigned char *p = databit;

	countbits = 1;

	for(y=0; y<height; y++)
	{
		for(x=0; x<width; x++)
		{
			pos = width * y + x;

			if(countbits <= 8)
			{
				// Numa imagem PBM:
				// 1 = Preto
				// 0 = Branco
				//datauchar[pos] = (*p & (1 << (8 - countbits))) ? 1 : 0;

				// Na nossa imagem:
				// 1 = Branco
				// 0 = Preto
				datauchar[pos] = (*p & (1 << (8 - countbits))) ? 0 : 1;
				
				countbits++;
			}
			if((countbits > 8) || (x == width - 1))
			{
				p++;
				countbits = 1;
			}
		}
	}
}


IVC *vc_read_image(char *filename)
{
	FILE *file = NULL;
	IVC *image = NULL;
	unsigned char *tmp;
	char tok[20];
	long int size, sizeofbinarydata;
	int width, height, channels;
	int levels = 255;
	int v;
	
	// Abre o ficheiro
	if((file = fopen(filename, "rb")) != NULL)
	{
		// Efectua a leitura do header
		netpbm_get_token(file, tok, sizeof(tok));

		if(strcmp(tok, "P4") == 0) { channels = 1; levels = 1; }	// Se PBM (Binary [0,1])
		else if(strcmp(tok, "P5") == 0) channels = 1;				// Se PGM (Gray [0,MAX(level,255)])
		else if(strcmp(tok, "P6") == 0) channels = 3;				// Se PPM (RGB [0,MAX(level,255)])
		else
		{
			#ifdef VC_DEBUG
			printf("ERROR -> vc_read_image():\n\tFile is not a valid PBM, PGM or PPM file.\n\tBad magic number!\n");
			#endif

			fclose(file);
			return NULL;
		}
		
		if(levels == 1) // PBM
		{
			if(sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 || 
			   sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1)
			{
				#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tFile is not a valid PBM file.\n\tBad size!\n");
				#endif

				fclose(file);
				return NULL;
			}

			// Aloca mem�ria para imagem
			image = vc_image_new(width, height, channels, levels);
			if(image == NULL) return NULL;

			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height;
			tmp = (unsigned char *) malloc(sizeofbinarydata);
			if(tmp == NULL) return 0;

			#ifdef VC_DEBUG
			printf("\nchannels=%d w=%d h=%d levels=%d\n", image->channels, image->width, image->height, levels);
			#endif

			if((v = fread(tmp, sizeof(unsigned char), sizeofbinarydata, file)) != sizeofbinarydata)
			{
				#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tPremature EOF on file.\n");
				#endif

				vc_image_free(image);
				fclose(file);
				free(tmp);
				return NULL;
			}

			bit_to_unsigned_char(tmp, image->data, image->width, image->height);

			free(tmp);
		}
		else // PGM ou PPM
		{
			if(sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 || 
			   sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1 || 
			   sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &levels) != 1 || levels <= 0 || levels > 255)
			{
				#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tFile is not a valid PGM or PPM file.\n\tBad size!\n");
				#endif

				fclose(file);
				return NULL;
			}

			// Aloca mem�ria para imagem
			image = vc_image_new(width, height, channels, levels);
			if(image == NULL) return NULL;

			#ifdef VC_DEBUG
			printf("\nchannels=%d w=%d h=%d levels=%d\n", image->channels, image->width, image->height, levels);
			#endif

			size = image->width * image->height * image->channels;

			if((v = fread(image->data, sizeof(unsigned char), size, file)) != size)
			{
				#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tPremature EOF on file.\n");
				#endif

				vc_image_free(image);
				fclose(file);
				return NULL;
			}
		}
		
		fclose(file);
	}
	else
	{
		#ifdef VC_DEBUG
		printf("ERROR -> vc_read_image():\n\tFile not found.\n");
		#endif
	}
	
	return image;
}


int vc_write_image(char *filename, IVC *image)
{
	FILE *file = NULL;
	unsigned char *tmp;
	long int totalbytes, sizeofbinarydata;
	
	if(image == NULL) return 0;

	if((file = fopen(filename, "wb")) != NULL)
	{
		if(image->levels == 1)
		{
			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height + 1;
			tmp = (unsigned char *) malloc(sizeofbinarydata);
			if(tmp == NULL) return 0;
			
			fprintf(file, "%s %d %d\n", "P4", image->width, image->height);
			
			totalbytes = unsigned_char_to_bit(image->data, tmp, image->width, image->height);
			printf("Total = %ld\n", totalbytes);
			if(fwrite(tmp, sizeof(unsigned char), totalbytes, file) != totalbytes)
			{
				#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
				#endif

				fclose(file);
				free(tmp);
				return 0;
			}

			free(tmp);
		}
		else
		{
			fprintf(file, "%s %d %d 255\n", (image->channels == 1) ? "P5" : "P6", image->width, image->height);
		
			if(fwrite(image->data, image->bytesperline, image->height, file) != image->height)
			{
				#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
				#endif

				fclose(file);
				return 0;
			}
		}
		
		fclose(file);

		return 1;
	}
	
	return 0;
}

//Gerar negativo da imagem gray
int vc_gray_negative(IVC* srcdst) {
	unsigned char *data = (unsigned char *)srcdst->data;
	int width = srcdst->width;
	int height = srcdst->height;
	int bytesperline = srcdst->bytesperline;
	int channels = srcdst->channels;
	int x, y;
	long int pos;

	//Verificação de erros
	if ((srcdst->width <= 0) || (srcdst->height <= 0) || (srcdst->data == NULL)) return 0;
	if (channels != 1) return 0;

	//Investe a imagem gray
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			pos = y * bytesperline + x * channels;

			data[pos] = 255 - data[pos];
		}
	}

	return 1;
}

//Gerar negativo da imagem RGB
int vc_rgb_negative(IVC* srcdst) {
    unsigned char *data = (unsigned char *) srcdst->data;
    int width = srcdst->width;
    int height = srcdst->height;
    int bytesperline = srcdst->bytesperline;
    int channels = srcdst->channels;
    int x, y;
    long int pos;

    //Verificação de erros
    if ((srcdst->width <= 0) || (srcdst->height <= 0) || (srcdst->data == NULL)) return 0;
    if (channels != 3) return 0;

    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            pos = y * bytesperline + x * channels;

            data[pos] = 255 - data[pos];
            data[pos + 1] = 255 - data[pos + 1];
            data[pos + 2] = 255 - data[pos + 2];
        }
    }

    return 1;
}

//Extrair componente RED da imagem RGB para gray
int vc_rgb_get_red_gray(IVC *srcdst) {
    unsigned char *data = (unsigned char *) srcdst->data;
    int width = srcdst->width;
    int height = srcdst->height;
    int bytesperline = srcdst->bytesperline;
    int channels = srcdst->channels;
    int x, y;
    long int pos;

    //Verificação de erros
    if ((srcdst->width <= 0) || (srcdst->height <= 0) || (srcdst->data == NULL)) return 0;
    if (channels != 3) return 0;

    //Extrai a componente RED
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            pos = y * bytesperline + x * channels;

            data[pos + 1] = data[pos]; //Green
            data[pos + 2] = data[pos]; //Blue
        }
    }

    return 1;
}

//Extrair componente GREEN da imagem RGB para gray
int vc_rgb_get_green_gray(IVC *srcdst) {
    unsigned char *data = (unsigned char *) srcdst->data;
    int width = srcdst->width;
    int height = srcdst->height;
    int bytesperline = srcdst->bytesperline;
    int channels = srcdst->channels;
    int x, y;
    long int pos;

    //Verificação de erros
    if ((srcdst->width <= 0) || (srcdst->height <= 0) || (srcdst->data == NULL)) return 0;
    if (channels != 3) return 0;

    //Extrai a componente RED
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            pos = y * bytesperline + x * channels;

            data[pos] = data[pos + 1]; //RED
            data[pos + 2] = data[pos + 1]; //BLUE
        }
    }

    return 1;
}

//Extrair componente BLUE da imagem RGB para gray
int vc_rgb_get_blue_gray(IVC *srcdst) {
    unsigned char *data = (unsigned char *) srcdst->data;
    int width = srcdst->width;
    int height = srcdst->height;
    int bytesperline = srcdst->bytesperline;
    int channels = srcdst->channels;
    int x, y;
    long int pos;

    //Verificação de erros
    if ((srcdst->width <= 0) || (srcdst->height <= 0) || (srcdst->data == NULL)) return 0;
    if (channels != 3) return 0;

    //Extrai a componente RED
    for(y = 0; y < height; y++) {
        for(x = 0; x < width; x++) {
            pos = y * bytesperline + x * channels;

            data[pos] = data[pos + 2]; //RED
            data[pos + 1] = data[pos + 2]; //GREEN
        }
    }

    return 1;
}

//Converter de RGB para Gray
int vc_rgb_to_gray(IVC *src, IVC *dst) {
    unsigned char *datasrc = (unsigned char*) src->data;
    int bytesperline_src = src->width * src->channels;
    int channels_src = src->channels;
    unsigned char *datadst = (unsigned  char*) dst->data;
    int bytesperline_dst = dst->width * dst->channels;
    int channels_dst = dst->channels;
    int width = src->width;
    int height = src->height;
    int x, y;
    long int pos_src, pos_dst;
    float rf, gf, bf;

    //Verificação de erros
    if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL)) return 0;
    if ((src->width != dst->width) || (src->height != dst->height)) return 0;
    if ((src->channels != 3) || (dst->channels != 1)) return 0;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            pos_src = y * bytesperline_src + x * channels_src;
            pos_dst = y * bytesperline_dst + x * channels_dst;

            rf = (float) datasrc[pos_src];
            gf = (float) datasrc[pos_src + 1];
            bf = (float) datasrc[pos_src + 2];

            datadst[pos_dst] = (unsigned char) ((rf * 0.299) + (gf * 0.587) + (bf * 0.114));
        }
    }

    return 1;
}

//Converter rgb para hsv
int vc_rgb_to_hsv(IVC *src, IVC *dst) {
    unsigned char *datasrc = (unsigned char*) src->data;
    int channels_src = src->channels;
    unsigned char *datadst = (unsigned  char*) dst->data;
    int width = src->width;
    int height = src->height;
    int x;
    float rf, gf, bf;
    float max, min, delta;
    float h, s, v;

    //Verificação de erros
    if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL)) return 0;
    if ((src->width != dst->width) || (src->height != dst->height)) return 0;
    if ((src->channels != 3) || (dst->channels != 3)) return 0;

    float size = width * height * channels_src;

    for (x = 0; x < size; x += channels_src) {
        rf = (float)datasrc[x];
        gf = (float)datasrc[x + 1];
        bf = (float)datasrc[x + 2];

        max = (rf > gf ? (rf > bf ? rf : bf) : (gf > bf ? gf : bf));
        min = (rf < gf ? (rf < bf ? rf : bf) : (gf < bf ? gf : bf));
        delta = max - min;

        v = max;
        if (v == 0.0f) {
            h = 0.0f;
            s = 0.0f;
        } else {
            // Saturation toma valores entre [0,255]
            s = (delta / max) * 255.0f;

            if (s == 0.0f) {
                h = 0.0f;
            } else {
                // Hue toma valores entre [0,360]
                if ((max == rf) && (gf >= bf)) {
                    h = 60.0f * (gf - bf) / delta;
                } else if ((max == rf) && (bf > gf)) {
                    h = 360.0f + 60.0f * (gf - bf) / delta;
                } else if (max == gf) {
                    h = 120.0f + 60.0f * (bf - rf) / delta;
                } else {
                    h = 240.0f + 60.0f * (rf - gf) / delta;
                }
            }
        }

        datadst[x] = (unsigned char) ((h / 360.0f) * 255.0f);
        datadst[x + 1] = (unsigned char) (s);
        datadst[x + 2] = (unsigned char) (v);
    }

    return 1;
}

// hmin,hmax = [0, 360]; smin,smax = [0, 100]; vmin,vmax = [0, 100]
int vc_hsv_segmentation(IVC *src, IVC *dst, int hmin, int hmax, int smin,
                        int smax, int vmin, int vmax) {
    unsigned char *datasrc = (unsigned char * ) src->data;
    int bytesperline_src = src->width * src->channels;
    int channels_src = src->channels;
    unsigned char *datadst = (unsigned char * ) dst->data;
    int bytesperline_dst = dst->width * dst->channels;
    int channels_dst = dst->channels;
    int width = src->width;
    int height = src->height;
    int x, y;
    float max, min, hue, sat, valor, delta;
    long int pos_src, pos_dst;
    float rf, gf, bf;

    //verificalão de errors
    if((src->width <= 0 ) || (src->height <= 0) || (src->data == NULL)) return 0;
    if((src->width != dst->width) || (src->height != dst->height)) return 0;
    if((src->channels != 3 ) || (dst->channels != 1))return 0 ;

    // meter em hsv
    for(y=0; y<height ; y++){
        for(x=0; x<width ; x++){
            pos_src = y * bytesperline_src + x * channels_src;
            pos_dst = y * bytesperline_dst + x * channels_dst;

            rf = (float) datasrc[pos_src];
            gf = (float) datasrc[pos_src + 1];
            bf = (float) datasrc[pos_src + 2];

            max = (rf > gf ? (rf > bf ? rf : bf) : (gf > bf ? gf : bf));
            min = (rf < gf ? (rf < bf ? rf : bf) : (gf < bf ? gf : bf));
            delta = max - min;

            //calcular value
            valor = max;

            //calcular saturação
            if (max==0 || max == min) {
                sat=0;
                hue=0;
            } else {
                sat= delta  * 100.0f / valor;
                //calcular hue
                // Quando o vermelho é o maior, Hue será um ângulo entre 300 e 360 ou entre 0 e 60
                if (rf==max && gf>=bf ) {
                    hue = 60.0f * (gf - bf) / delta ;
                } else if (rf==max && bf>gf ) {
                    hue = 360 + 60.0f * (gf - bf) / delta ;
                } else if(gf==max) {
                    hue = 120 + 60.0f * (bf - rf) / delta;
                } else if (max==bf) {
                    hue = 240 + 60.0f * (rf - gf) / delta ;
                }
            }

            //se o hmin for maior que o hmax  entao hmin ate 360 e de 0 ate hmax
            if (hmin > hmax ) {
                if ((hue >= 0 && hue <= hmax || hue <= 360 && hue >= hmin) && sat <= smax && sat  >= smin && valor <= vmax / 100.0f * 255 && valor >= vmin / 100.0f * 255)
                    datadst[pos_dst] = 255;
                else
                    datadst[pos_dst] = 0;
            } else {
                if (hue <= hmax && hue >= hmin && sat <= smax && sat  >= smin && valor <= vmax / 100.0f * 255 && valor >= vmin / 100.0f * 255)
                    datadst[pos_dst] = 255;
                else
                    datadst[pos_dst] = 0;
            }
        }
    }

    return 1;
}

int vc_scale_gray_to_color_palette(IVC *src, IVC *dst) {
    unsigned char* datasrc = (unsigned char*)src->data;
    int bytesperline_src = src->channels * src->width;
    int channels_src = src->channels;
    unsigned char* datadst = (unsigned char*)dst->data;
    int bytesperline_dst = dst->channels * dst->width;
    int channels_dst = dst->channels;
    int width = src->width;
    int height = src->height;
    int x, y;
    long int pos_src, pos_dst;

    if ((src->width <= 0) || (src->height <= 0) || (src->data == NULL)) return 0;
    if ((src->width != dst->width) || (src->height != dst->height)) return 0;
    if ((src->channels != 1) || (dst->channels != 3)) return 0;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            pos_src = y * bytesperline_src + x * channels_src;
            pos_dst = y * bytesperline_dst + x * channels_dst;

            if (datasrc[pos_src] < 64) { // Primeiro quarteto -> cores verdes
                datadst[pos_dst] = 0;
                datadst[pos_dst + 1] = datasrc[pos_src] * 4;
                datadst[pos_dst + 2] = 255;
            } else if (datasrc[pos_src] < 128) { // Segundo quarteto -> verde a azul
                datadst[pos_dst] = 0;
                datadst[pos_dst + 1] = 255;
                datadst[pos_dst + 2] = 255 - ((datasrc[pos_src] - 64) * 4);
            } else if (datasrc[pos_src] < 192) { // Terceiro quarteto -> azul a vermelho
                datadst[pos_dst] = (datasrc[pos_src] - 128) * 4;
                datadst[pos_dst + 1] = 255;
                datadst[pos_dst + 2] = 0;
            } else { // Quarto quarteto -> vermelho para verde
                datadst[pos_dst] = 255;
                datadst[pos_dst + 1] = 255 - ((datasrc[pos_src] - 192) * 4);;
                datadst[pos_dst + 2] = 0;
            }
        }
    }

    return 1;
}

int vc_image_white_pixel_count(IVC *src) {
    int x, y, count = 0;
    long int pos;

    for (y = 0; y < src->height; y++) {
        for (x = 0; x < src->width; x++) {
            pos = y * src->bytesperline + x * src->channels;

            if (src->data[pos] == 255) {
                count++;
            }
        }
    }

    return count;
}
