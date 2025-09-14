#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define BUFFER 16384

int unzip(FILE *source, FILE *dest) {
    z_stream strm;
    int ret;
    unsigned int have;
    unsigned char in[BUFFER];
    unsigned char out[BUFFER];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK) {
        return ret;
    }

    do {
        strm.avail_in = fread(in, 1, BUFFER, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;

        strm.next_in = in;

        do {
            strm.avail_out = BUFFER;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);

            if (ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_NEED_DICT) {
                (void)inflateEnd(&strm);
                printf("Erro de dados na descompressao: %s\n", strm.msg);
                return ret;
            }

            have = BUFFER - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

    } while (ret != Z_STREAM_END);

    (void)inflateEnd(&strm);

    if (ret == Z_STREAM_END) {
        return Z_OK;
    } else {
        return ret;
    }
}

int main(int argc, char *argv[]) {
    FILE *source, *dest;
    int ret;

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_compactado> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    source = fopen(argv[1], "rb");
    if (!source) {
        printf("Erro ao abrir arquivo de entrada");
        return 1;
    }

    dest = fopen(argv[2], "wb");
    if (!dest) {
        printf("Erro ao abrir arquivo de saida");
        fclose(source);
        return 1;
    }

    ret = unzip(source, dest);
    fclose(source);
    fclose(dest);

    if (ret == Z_OK) {
        printf("Arquivo descompactado com sucesso.\n");
    } else {
        printf("Ocorreu um erro durante a descompactacao: %d\n", ret);
        return 1;
    }

    return 0;
}
