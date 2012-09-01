
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "amessage.pb-c.h"

void print_content(int len, uint8_t *buf)
{
    int i;
    for (i = 0; i < len; i++) {
        if (i != 0 && i % 16 == 0)
            printf("\n");
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

int example1(int argc, char **argv)
{
    uint8_t *buf = NULL;
    unsigned len;
    AMessage msg;
    AMessage *recv_msg = NULL;

    amessage__init(&msg);

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "usage: pack_unpack a [b]\n");
        return 1;
    }
    msg.a = atoi(argv[1]);
    if (argc == 3) {
        msg.has_b = 1;
        msg.b = atoi(argv[2]);
    }
    len = amessage__get_packed_size(&msg);
    buf = malloc(len);
    if (buf == NULL) {
        fprintf(stdout, "malloc error\n");
        return 1;
    }
    amessage__pack(&msg, buf);

    recv_msg = amessage__unpack(NULL, len, buf);
    if (recv_msg == NULL) {
        fprintf(stdout, "error unpacking message\n");
        return 1;
    }

    printf("-----------%s------------\n", __func__);
    printf("a=%d", recv_msg->a);
    if (recv_msg->has_b)
        printf("; b=%d", recv_msg->b);
    printf("\n");
    free(buf);
    amessage__free_unpacked(recv_msg, NULL);

    return 0;
}

int example2()
{
    StructTest str_test = STRUCT_TEST__INIT;
    StructTest__Nested2 **nest_m = NULL;
    StructTest__Nested2 nest[2];
    StructTest *rcv = NULL;
    StructTest__Nested2 *result;
    uint8_t *buf = NULL;
    int len;

    struct_test__init(&str_test);
    struct_test__nested2__init(&nest[0]);
    struct_test__nested2__init(&nest[1]);

    nest[0].a = 3;
    nest[0].b = 4;
    nest[1].a = 5;
    nest[1].b = 6;
    str_test.n_nested2 = 2;
    nest_m = malloc(sizeof(StructTest__Nested2 *) * 2);
    if (nest_m == NULL) {
        fprintf(stdout, "error malloc\n");
        return 1;
    }
    *nest_m = &nest[0];
    *(nest_m + 1) = &nest[1];
    str_test.nested2 = nest_m;

    len = struct_test__get_packed_size(&str_test);

    buf = malloc(len);
    if (buf == NULL) {
        fprintf(stdout, "malloc error\n");
        return 1;
    }
    struct_test__pack(&str_test, buf);

    rcv = struct_test__unpack(NULL, len, buf);

    if (rcv == NULL) {
        fprintf(stdout, "error unpacking message\n");
        return 1;
    }

    printf("-----------%s------------\n", __func__);
    printf("num: %d.\n", rcv->n_nested2);
    result = *(rcv->nested2);
    printf("1.a: %d.\n", result->a);
    printf("1.b: %d.\n", result->b);
    result = *(rcv->nested2 + 1);
    printf("2.a: %d.\n", result->a);
    printf("2.b: %d.\n", result->b);
    struct_test__free_unpacked(rcv, NULL);
    free(buf);
    free(nest_m);
    return 0;
}

#define TIMES    1
int example3()
{
    long int r_num = 0;
    unsigned len;
    int times;
    CMessage msg;

    for (times = 0; times < TIMES; times++) {
        cmessage__init(&msg);
        r_num = random();
        msg.a = 0;//r_num;
        r_num = random();
        msg.b = 0;//r_num;
        r_num = random();
        msg.c = 0;//r_num;
        r_num = random();
        msg.d = 0;//r_num;
        len = cmessage__get_packed_size(&msg);
        printf("r_num: %ld, len: %u.\n", r_num, len);
    }
    return 0;
}

int main(int argc, char **argv)
{
#if 0
    example1(argc, argv);
#endif
#if 0
    example2();
#endif
#if 1
    example3();
#endif
    return 0;
}
