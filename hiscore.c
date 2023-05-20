#include "hiscore.h"

char init_hiscore(void)
{
    char buffer[16] = {0};
    int i = 0;

    if ((file = fopen("hiscore", "r")))
    {
        // file exists
        // lets read it in
        while(!feof(file))
        {
            buffer[i++] = (char)fgetc(file);
        }
        fclose(file);

        buffer[i - 1] = '\0';

        printf("Hiscore: %s\n", unscramble(buffer));

        return TRUE;
    }
    else
    {
        // file does not exist
        // lets create it and add a small hiscore.
        file = fopen("hiscore", "w");
        if (file == NULL)
            return FALSE;

        fprintf(file, "%s", scramble("50"));

        fclose(file);
    }

    return TRUE;
}

int get_hiscore(void)
{

    int i = 0;

    if ((file = fopen("hiscore", "r")))
    {
        while(!feof(file))
        {
            ret[i++] = (char)fgetc(file);
        }
        fclose(file);

        ret[i - 1] = '\0';
    }
    return atoi(unscramble(ret));
}

char save_hiscore(int score)
{
    char buf[16];

    file = fopen("hiscore", "w");
    if (file == NULL)
        return FALSE;

    fprintf(file, "%s", scramble(itoa(score, buf, 10)));

    fclose(file);
    return TRUE;
}

char* scramble(char* str)
{
    char key = 0x16;

    for(int i = 0; i < strlen(str); i++)
    {
        ret[i] = *(str+i) ^ key;
    }

    ret[strlen(str)] = '\0';

    return ret;
}

char* unscramble(char* str)
{
    char key = 0x16;

    for (int i = 0; i < strlen(str); i++)
    {
        ret[i] = *(str+i) ^ key;
    }

    ret[strlen(str)] = '\0';

    return ret;
}
