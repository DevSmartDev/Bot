#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include    <getopt.h>
#include "main.h"
unsigned int getUIntValueOfText(gchar* a, unsigned int l, int base);


/*==============================================================================================*/
/*! Function    : getByteOfDigit
    Description : calculate the value of digit
                    '0'=>0..'9'=>9 and 'A'/'a'=>10.. 'H'/'h'=>15
    Input       : ascii char
    Output      : value
*/
unsigned char getByteOfDigit(char c)
{
    /*! when the character > 'a' return 10->15  */
    if(c>=CHR_LOWER)
        return (unsigned char)(c-87);

    /*! when the character > 'A' return 10->15  */
    else if(c>=CHR_UPPER)
        return (unsigned char)(c-55);

    /*! when the character > '0' return 0->9  */
    else
        return (unsigned char)((0xFF)&(c-CHR_ZEROS));
}

/*==============================================================================================*/
/*! Function    :   isUIntValueBase
    Description :   check a char array is an integer and overflow
    Input       :   chars and count of chars
    Output      :   1 if is a unsigned integer and not overflow
                    0 if else
*/
int isUIntValueBase(char* a, unsigned int l)
{
    const char*     overuint = "4294967296";
    char*           noblank = a;
    unsigned int    len      = strlen(a);
    unsigned int    i        = 0;
    if(len>l)
        len = l;
    while(noblank[0]=='0')
    {
        ++noblank;
        --len;
    }
    if(len==0)
        return 0;

    if(len>10)
        len=10;
    if (len==10)
    {
        if(noblank[0]<'4')
            return 1;
        else if(noblank[0]>'4')
            return 0;
        else
        {
            for(i=0; i<10; ++i)
            {
                if(noblank[i]==overuint[i])
                    continue;
                else if((noblank[i]<overuint[i]))
                    return 1;
                else
                    return 0;
            }
            return 0;

        }

    }
    else
    {
        return 1;
    }


}
/*==============================================================================================*/
/*! Function    : getValueBaseOfText
    Description : return the value base of ascii array
    Input       : ascii array, ascii l
    Output      : BASE: NON/DEC/HEX/BIN
                    NONE: define the type is not number
                    DEC: define decimal number
                    HEX: define hexa number
                    BIN: define binary number

*/
int getValueBaseOfText(char* a,unsigned int leng)
{

    /*! Declare and initialize variables*/
    int i=0;
    unsigned int tail=0;

    /*! Check all arguments */
    if(!a)
        return 0;

    /*------------------------------------------------*/
    tail=strlen(a);
    if(tail>leng)
        tail=leng;

    if(!tail)
        return 0;

    --tail;


    /*!Ex: 0x00FA is hex number */
    if(a[0]=='0'&&(a[1]=='X'||a[1]=='x'))
    {
        for(i=tail; i>=2; --i)
            if(!isxdigit(a[i]))
                return 0;
        return 16; /*HEX*/
    }

    /*------------------------------------------------*/
    if(a[tail]=='b'||a[tail]=='B')
    {

        for(i=tail; i>=0; --i)
            if(!isxdigit(a[i]))
                return 0;

        /*!Ex: 00FB is hex number */
        for(i=tail; i>=0; --i)
            if(a[i]!='0'&&a[i]!='1')
                return 16; /*HEX*/

        /*!Ex: 101B is bin number */
        return 2; /*HEX*/
    }
    /*------------------------------------------------*/
    for(i=tail; i>=0; --i)
        if(!isxdigit(a[i]))
            return 0;
    /*------------------------------------------------*/
    for(i=tail; i>=0; --i)
        if(!isdigit(a[i]))
            return 16; /*HEX*/
    return 10; /*DEC*/

}

/*==============================================================================================*/
/*! Function    : getUIntValueOfText
    Description : convert the ascii array to value
    Input       : char array, number of char in array, base of value
    Output      : value (4 bytes)
*/

unsigned int getUIntValueOfText(gchar* a, unsigned int l, int base)
{
    /*! Declare and initialize variables*/
    unsigned int    value   = 0;
    unsigned int len= 0;
    unsigned int i           = 0;
    /*------------------------------------------------*/
    /*! Check all arguments */
    if(!a)
        return 0;
    len=strlen(a);
    if(len>l)
        len=l;

    if(!len)
        return 0;
    /*------------------------------------------------*/
    /*! determine the value base of string */
    if(!getValueBaseOfText(a,l))
        return 0;
    /*------------------------------------------------*/
    /*! calculate the value of string with base */


    switch(base)
    {
    case 0: /*BIN*/

        /*! Remove the character 'b' or 'B' at tail string */
        if(a[len-1]=='b'||a[len-1]=='B')
            --len;

        /*! Remove all '0' before value */
        while((*a)=='0'&&len>0)
        {
            ++a;
            --len;
        }

        /*! Maximum digits of binary number is 32*/
        if(len>32)
            len=32;

        /*! get binary value of string */
        for(i=0; i<len; ++i)
            value=(value<<1)|(a[i]!='0');

        break;

    case 10: /*DEC*/

        /*! Remove all '0' before value */
        while((*a)=='0'&&len>0)
        {
            ++a;
            --len;
        }

        /*! Maximum digits of decimal number is 10 */
        if(len>=10&&!isUIntValueBase(a,len))
            len=9;

        /*! get decimal value of string */
        for(i=0; i<len; ++i)
            value=value*10+getByteOfDigit(a[i]);
        break;


    case 16:/*HEX*/

        /*! Get string after "0x" */
        if(a[1]=='x'||a[1]=='X')
        {
            a=a+2;
            len-=2;
        }

        /*! Remove all '0' before value */
        while((*a)=='0'&&len>0)
        {
            a++;
            len--;
        }

        /*! Maximum digits of decimal number is 8 */
        if(len>8)
            len=8;


        /*! get hexa value of string */
        for(i=0; i<len; i++)
        {
            value=(value<<4)|getByteOfDigit(a[i]);
        }


        break;


    default:
        value=0;
        break;

    }
    /*------------------------------------------------*/
    /*! return unsigned int output */
    value=value&0xFFFFFFFF;
    return value;
}


void spl_chart_help(const gchar* programName) {
	printf("Usage: %s -a <account> -d <id> -u <ddress:port> -l <lcuid> -b <begin time> -e <end time>\n", programName);
    printf("OPTION:\n");
    printf("\t -b, --begin_time  <time>\t: begin time in order to draw chart. Format of time is YYYY-mm-dd HH:MM:SS\n");
    printf("\t -e, --end_time  <time>\t\t: begin time in order to draw chart. Format of time is YYYY-mm-dd HH:MM:SS\n");
    printf("\t -a, --account  <account>\t: user name get data for chart\n");
    printf("\t -d, --user_id <User Id>\t: user id get data for chart\n");
    printf("\t -u, --url  <address:port>\t: address of server\n");
    printf("\t -l, --lcuid  <lcuid>\t\t: id of lcu\n");
}

gboolean getOptCommandLine(int argc, char **argv, struct PROGRAM_OPTION* option_t)
{


    struct option longOption[] = {
            {"begin_time", required_argument,   0, 'b'},
            {"end_time", required_argument,   0, 'e'},
            {"account", required_argument,   0, 'a'},
            {"user_id", required_argument,   0, 'd'},
            {"url", required_argument,   0, 'u'},
            {"lcuid", required_argument,   0, 'l'},
            {0,0,0,0}
	};
   gint c;
   while (1) {

            /*! getopt_long stores the option index here.*/
            int option_index = 0;
            c = getopt_long (argc, argv, "b:e:a:d:u:l:l", longOption, &option_index);
            /*! Detect the end of the options.*/

            if (c == -1)
                break;
            switch (c) {
            case 'b':
                option_t->begin_time = g_strdup(optarg);
                //DEBUG("option_t->begin_time: %s\n",option_t->begin_time);
                break;
            case 'e':
                option_t->end_time = g_strdup(optarg);
                // DEBUG("option_t->end_time: %s\n",option_t->end_time);
                break;
            case 'a':
                option_t->account = g_strdup(optarg);
                 //DEBUG("option_t->account: %s\n",option_t->account);
                break;
            case 'd':
                option_t->account_id = getUIntValueOfText(optarg,strlen(optarg),10);
                // DEBUG("option_t->account_id: %d\n",option_t->account_id);
                break;
            case 'u':
                option_t->url = g_strdup(optarg);
                 DEBUG("option_t->url: %s\n",option_t->url);
                break;
            case 'l':
                option_t->lcu_id = g_strdup(optarg);
                // DEBUG("option_t->lcu_id: %s\n",option_t->lcu_id);
                break;
            default:
                break;
            }
    }
    if (option_t->begin_time == NULL ||
        option_t->end_time ==NULL ||
        option_t->account == NULL ||
        option_t->url == NULL ||
        option_t->lcu_id == NULL ||
        option_t->account_id ==0 )
            return FALSE;
    return TRUE;

}
