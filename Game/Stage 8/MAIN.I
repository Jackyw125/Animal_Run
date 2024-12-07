# 1 "main.c" 1
# 1 "./MODEL.H" 1
# 1 "./TYPES.H" 1
# 18 "./TYPES.H"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef unsigned char bool;
# 12 "./MODEL.H" 2
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
# 13 "./MODEL.H" 2
# 27 "./MODEL.H"
typedef struct
{
    int x, y;
    int prev_x, prev_y;
    int velocity;
    int velocity_y;
    int state;
    bool isFalling;
    bool dead;
} Animal;

typedef struct
{
    int x, y;
    int prev_x, prev_y;
    bool off_screen;
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
bool has_animal_moved(Animal *chicken);
bool check_object_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2);
# 10 "main.c" 2
# 1 "./RENDER.H" 1
# 1 "./MODEL.H" 1
# 12 "./RENDER.H" 2
# 1 "./EVENTS.H" 1
# 1 "./MODEL.H" 1
# 12 "./EVENTS.H" 2
# 1 "./TYPES.H" 1
# 13 "./EVENTS.H" 2
# 1 "./BITMAP.H" 1
# 1 "./types.h" 1
# 4 "./BITMAP.H" 2
# 1 "./font.h" 1
# 1 "./types.h" 1
# 5 "./font.h" 2


extern const UINT8 font[];
extern const UINT8 char_delete[];
# 5 "./BITMAP.H" 2
# 16 "./BITMAP.H"
extern const UINT32 chicken_bitmap [];
extern const UINT32 monster_bitmap [];
extern const UINT16 coin_bitmap[];
extern const UINT32 clear_bitmap[];
# 14 "./EVENTS.H" 2


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
# 13 "./RENDER.H" 2
# 1 "./RASTER.H" 1
# 1 "./types.h" 1
# 14 "./RASTER.H" 2


void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_horizontal_line(UINT8 *base, int y);
void clear_screen(UINT8 *base);
void clear_horizontal_line_8(UINT8* base, int x, int y, int length);
void clear_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
UINT32 *get_video_base();
void set_video_base(UINT32 *);
void super_mode();
void user_mode();
# 14 "./RENDER.H" 2
# 1 "./BITMAP.H" 1
# 15 "./RENDER.H" 2
# 1 "./FONT.H" 1
# 16 "./RENDER.H" 2


void render(Model *model, UINT32 *base);
void double_buffer_render(Model *model, UINT32 *base);
void render_animal(const Animal *chicken, UINT32 *base);
void render_monster(const Monster *monster, UINT32 *base);
void render_score(Score *score, UINT32 *base);
void render_coin(Coin *coin, UINT16 *base);
void render_ground(Ground *ground, UINT8 *base);
void respawn_render(Model *model, UINT32 *base);
# 11 "main.c" 2
# 1 "./EVENTS.H" 1
# 12 "main.c" 2
# 1 "./RASTER.H" 1
# 13 "main.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 14 "main.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 15 "main.c" 2


UINT8 double_buffer[35840] = {0};

UINT32 get_time();
void main_game_loop();
void input(Model *model, char *pressedKey);
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer);

int main() {
    UINT8 *current_buffer = (UINT8 *)get_video_base();

    main_game_loop();

    return 0;
}

void main_game_loop()
{
    UINT32 *back_buffer, *front_buffer, *current_buffer;

    bool endGame = 0 ;

    UINT32 time_then, time_now, time_elapsed;

    Model model;
    char pressedKey = 0;

    initialize_model(&model);
    render(&model, (UINT32*)current_buffer);



    time_then = get_time();
    set_buffers(&back_buffer, &front_buffer, double_buffer);
    clear_screen((UINT8 *)front_buffer);
    clear_screen((UINT8 *)back_buffer);

    current_buffer = back_buffer;
    while (pressedKey != 'q' && !endGame) {
            input(&model, &pressedKey);
            if(pressedKey == ' ' || 'w' || 'W')
            {
                process_asynchronous_events(&model,&pressedKey);
            }
            time_now = get_time();
	        time_elapsed = time_now - time_then;

            if (time_elapsed > 0) {
                process_synchronous_events(&model,&endGame);
                double_buffer_render(&model, current_buffer);
                set_video_base(current_buffer);
                (void)_trap_14_w((short)0x25) ;
                switch_buffers(&current_buffer, front_buffer, back_buffer);
            }
    }
    set_video_base(front_buffer);
    clear_screen((UINT8 *)front_buffer);
}
# 91 "main.c"
void input(Model *model, char *pressedKey)
{
    if ((short)_trap_1_w((short)0x0B) )
    {
        char key = (char)_trap_1_w((short)0x08) ;
        if (key == ' ' || key == 'q' || key == 'W' || key == 'w') {
            *pressedKey = key;
        }
    }
    else {
        *pressedKey = 0;
    }
}

void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]) {

    UINT8 *temp = back_buffer_array;

    while( ((UINT32) temp) & 0xFF) {
        temp++;
    }

    *back_buffer =	(UINT32*) temp;
    *front_buffer =  get_video_base();
}

void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer) {

    if(*current_buffer == front_buffer) {
        *current_buffer = back_buffer;
    } else {
        *current_buffer = front_buffer;
    }
}
# 136 "main.c"
UINT32 get_time() {
    UINT32 time;
    long old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
    time = *((UINT32 *)0x462);
    _trap_1_wl((short)0x20,(long)(old_ssp)) ;
    return time;
}
