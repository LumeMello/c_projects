#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define BUFFER 16384

int zip(FILE *source, FILE *dest) {
    z_stream strm;
    int ret, flush;
    unsigned int have;
    unsigned char in[BUFFER];
    unsigned char out[BUFFER];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        return ret;
    }

    do {
        strm.avail_in = fread(in, 1, BUFFER, source);
        if (ferror(source)) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }

        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        do {
            strm.avail_out = BUFFER;
            strm.next_out = out;
            ret = deflate(&strm, flush);
            
            if (ret == Z_STREAM_ERROR) {
                (void)deflateEnd(&strm);
                return ret;
            }

            have = BUFFER- strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

    } while (flush != Z_FINISH);

    (void)deflateEnd(&strm);
    return Z_OK;
}

int main(int argc, char *argv[]) {
    FILE *source, *dest;
    int ret;

    if (argc != 3) {
        printf("Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
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

    ret = zip(source, dest);

    fclose(source);
    fclose(dest);

    if (ret == Z_OK) {
        printf("Arquivo compactado com sucesso.\n");
    } else {
        printf("Ocorreu um erro durante a compactacao: %d\n", ret);
        return 1;
    }

    return 0;
}
