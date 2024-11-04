#include "bitmap.h"

const UINT32 chicken_bitmap[] =     
{   
        0x00000000, 0x00000000, 0x00000000, 0x00000e00, 0x00000000, 0x00001fc0, 0x00000000, 0x00001fc0, 0x00000000, 0x00007fe0,
        0x00000000, 0x0000fff0, 0x00000000, 0x0000fff8, 0x00000000, 0x0001fff8, 0x00000000, 0x0001fffc, 0x00000000, 0x0003fffc,
        0x00000000, 0x0007fffe, 0x00000000, 0x0007ffff, 0x00000000, 0x000fffff, 0x1f000000, 0x001fffc0, 0x3fc00000, 0x007fff80,
        0x3fe00000, 0x00ffff00, 0x3fe80000, 0x0fffff00, 0x3fcc001f, 0xfffffe00, 0x3fcfffff, 0xfffffe00, 0x3fcfffff, 0xfffffe00,
        0x1fcfffff, 0xfffffe00, 0x1fefffff, 0xfffffe00, 0x1fe7ffff, 0xfffffe00, 0x1ff3ffff, 0xfffffe00, 0x0ff9ffff, 0xfffffe00,
        0x0ffcffff, 0xfffffe00, 0x07fe7fff, 0xfffffe00, 0x07ff3fff, 0xfffffe00, 0x03ff9fff, 0xfffffe00, 0x01ff9fff, 0xfffffe00,
        0x01ffcfff, 0xffdffe00, 0x00ffe7ff, 0xffbffc00, 0x007ff3ff, 0xff3ffc00, 0x003ff9ff, 0xfefffc00, 0x001ffcff, 0xf9fff800,
        0x000ffe1f, 0x87fff800, 0x0007ff80, 0x3ffff000, 0x0007ffff, 0xfffff000, 0x0003ffff, 0xffffe000, 0x0003ffff, 0xffffc000,
        0x0001ffff, 0xffff8000, 0x0001ffff, 0xffff0000, 0x0000ffff, 0xfffe0000, 0x0000ffff, 0xfffc0000, 0x00007fff, 0xfff00000,
        0x00003fff, 0xffc00000, 0x00001fff, 0xff000000, 0x000007ff, 0xfe000000, 0x000000ff, 0xfc000000, 0x0000003f, 0xf0000000,
        0x0000001f, 0xe0000000, 0x0000001f, 0xc0000000, 0x0000000f, 0xc0000000, 0x0000000f, 0xc0000000, 0x0000000d, 0xc0000000,
        0x0000000c, 0xc0000000, 0x0000000c, 0xc0000000, 0x0000000c, 0xc0000000, 0x0000000d, 0xc0000000, 0x0000000d, 0xc0000000,
        0x0000000f, 0xff000000, 0x0000003f, 0xfc000000, 0x00000003, 0xe0000000, 0x00000000, 0x00000000

};

const UINT32 monster_bitmap [] =     
{   
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000f, 0xff800000, 0x0001f078, 0x00f00000, 0x0003dcc0, 0x001c7c00,
        0x0007fe00, 0x00038700, 0x00060900, 0x00007f00, 0x00001d00, 0x0001c380, 0x00003380, 0x000060c0, 0x000061c0, 0x00203000,
        0x0000c0c0, 0x00401000, 0x00008360, 0x00c00800, 0x00010c30, 0x01b00c00, 0x00031818, 0x07080400, 0x00061006, 0x78040600,
        0x00042001, 0x80020200, 0x00086074, 0x26020300, 0x001840dc, 0x1b010100, 0x003040fc, 0x5f010080, 0x006040d4, 0x530100c0,
        0x00c040e4, 0x5e010040, 0x01804008, 0x4e010060, 0x03004018, 0x20030030, 0x02006030, 0x20020018, 0x04002060, 0x10060008,
        0x0c061980, 0x0808000c, 0x08090000, 0x07700006, 0x18198000, 0x0000c002, 0x10108000, 0x00032002, 0x1030ffff, 0xe0022003,
        0x10200000, 0x0f861001, 0x18060000, 0x000c1801, 0x08000000, 0x00041801, 0x0c000000, 0x00030801, 0x04000000, 0x00000003,
        0x03000000, 0x00000002, 0x01800000, 0x00000006, 0x00e00000, 0x0000000c, 0x001f8000, 0x00000030, 0x0001fc00, 0x000001c0,
        0x00000403, 0xf0001f00, 0x003f8800, 0x007fc000, 0x00c0f800, 0x00000000, 0x01000000, 0x00200000, 0x02000000, 0x00200000,
        0x06000180, 0x00200000, 0x06000060, 0x00200000, 0x06000010, 0x00100000, 0x02020000, 0x003c0000, 0x02000000, 0x00460000,
        0x01800058, 0x02018000, 0x00c00044, 0x0c00c000, 0x007000c6, 0x00006000, 0x001c00c6, 0x00006000, 0x00078183, 0x80002000,
        0x0000ff00, 0xe0002000, 0x00000000, 0x38006000, 0x00000000, 0x0f00c000, 0x00000000, 0x03ff8000, 0x00000000, 0x00080000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

};

const UINT16 coin_bitmap [] = 
{
        0x0000, 0x7FFE, 0x4002, 0x87E2, 0x4DB2, 0x5DBA, 
        0x29E5, 0x5E7A, 0x5E7A, 0x29E5, 0x5DBA, 0x4DB2, 
        0x87E2, 0x4002, 0x7FFE, 0x0000
};
