# 1 "vbl.c" 1
# 1 "./VBL.H" 1
# 1 "./GLOBAL.H" 1
# 1 "./model.h" 1
# 1 "./TYPES.H" 1
# 18 "./TYPES.H"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef unsigned char bool;
# 12 "./model.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 13 "./model.h" 2
# 27 "./model.h"
typedef struct
{
    int x, y;
    int prev_x, prev_y;
    int velocity;
    int velocity_y;
    int state;
    bool dead;
} Animal;

typedef struct
{
    int x, y;
    int prev_x, prev_y;
} Monster;

typedef struct
{
    int x, y;
    int prev_x, prev_y;
    bool active;
} Coin;

typedef struct
{
  int total;
  int digits;
  int prev_total;
} Score;

typedef struct
{
	int y;
} Ground;

typedef struct {
    Animal chicken;
    Monster monster;
    Score score;
    Coin coins[5 ];
    Ground ground;
} Model;

void initialize_model(Model *model);
void initialize_animal(Animal *chicken);
void initialize_score (Score *score);
void initialize_monster(Monster *monster, Coin *coins);
void initialize_coins(Coin *coins, Monster *monster);
void initialize_ground(Ground *ground, int y);
void animal_horizontal_movement(Animal *chicken);
void move_animal(Animal *chicken, int displacement_x, int displacement_y);
bool check_object_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2);
# 3 "./GLOBAL.H" 2
# 1 "./types.h" 1
# 4 "./GLOBAL.H" 2



extern Model model;
extern bool endGame;
extern int render_request;
extern UINT32 music_time;

extern bool game_on;
# 4 "./VBL.H" 2
# 1 "./EVENTS.H" 1
# 1 "./MODEL.H" 1
# 12 "./EVENTS.H" 2
# 1 "./TYPES.H" 1
# 13 "./EVENTS.H" 2


void check_animal_death(Model *model, bool *endGame);
void animal_input(Animal *chicken, char key);
bool check_collision_coin(Animal *chicken, Coin *coin, int index);
bool check_collision_monster(Animal *chicken, Monster *monster);
bool check_ground_collision(Animal *chicken, Ground* ground);
void animal_vertical_movement(Animal *chicken);
void animal_jump(Animal *chicken);
void animal_fly(Animal *chicken);
void update_score(Model *model);
bool respawn_event(Model *model);
void process_synchronous_events(Model *model, bool *endGame);
void process_asynchronous_events(Model *model, char *pressedKey);
# 5 "./VBL.H" 2
# 1 "./MODEL.H" 1
# 6 "./VBL.H" 2
# 1 "C:/c68/include/osbind.h" 1
# 7 "./VBL.H" 2


void do_vbl_isr();
void main_vbl_isr();
# 1 "vbl.c" 2


int main_game_timer = 0;
int render_request = 0;
bool game_on = 1 ;
UINT32 music_time = 0;

void do_vbl_isr()
{
    if(game_on == 1 ) {
        main_game_timer++;
        if(main_game_timer == 1){
            process_synchronous_events(&model, &endGame);
            music_time++;
            render_request = 1;
            main_game_timer = 0;
        }
    }
}
