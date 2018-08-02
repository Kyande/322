struct do_circulant
{
    int size;
    int matrix[200];

};

program Do_Circulant{
    version Do_VERS{
        struct do_circulant circulant(do_circulant) = 1;
    } = 1;
} = 0x23451111;
