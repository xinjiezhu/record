/*
 * key codes 2014-3-17
 */
#define u8 unsigned char 
#define KEY_NUM 3

#define KEY_0 0x31
#define KEY_1 0x32
#define KEY_2 0x33


static const u8 KeyCodes[KEY_NUM] =
{
    KEY_0,
    KEY_1,
    KEY_2
};

enum _key_code
{
    IS_KEY_0,
    IS_KEY_1,
    IS_KEY_2
};

/*explain*/
if key 0 is pressed, send KeyCodes[IS_KEY_0];
if key 1 is pressed, send KeyCodes[IS_KEY_1];
if key 2 is pressed, send KeyCodes[IS_KEY_2];