#include "hiscore.h"

char init_hiscore(void)
{
    char buffer[255] = {0};
    char tmp[16] = {0};
    int i = 0;
    int j = 0;

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

        for (i = 0; i < strlen((char*)buffer); i++)
        {
            tmp[j++] = buffer[i];
            if (j == 16)
            {
                printf("%s\n", unscramble(tmp));
                j = 0;
            }
        }

        return TRUE;
    }
    else
    {
        // file does not exist
        // lets create it
        file = fopen("hiscore", "w");
        if (file == NULL)
            return FALSE;

        fprintf(file, "%s", scramble("Jocke"));
        fprintf(file, "%s", scramble("10"));
        fprintf(file, "%s", scramble("Jocke"));
        fprintf(file, "%s", scramble("30"));
        fprintf(file, "%s", scramble("Jocke"));
        fprintf(file, "%s", scramble("50"));
        fprintf(file, "%s", scramble("Jocke"));
        fprintf(file, "%s", scramble("80"));
        fprintf(file, "%s", scramble("Jocke"));
        fprintf(file, "%s", scramble("100"));

        fclose(file);
    }

    return TRUE;
}

char* scramble(char* str)
{
    int len = 0;
    char key[] = "This is a secret key that will be used to chypher the text";

    len = strlen(str);
    for(int i = 0; i < 16; i++)
    {
        if (i >= len)
            ret[i] = 0x16 ^ key[i];
        else
            ret[i] = *(str+i) ^ key[i];
    }
    ret[16] = '\0';

    return ret;
}

char* unscramble(char* str)
{
    char c;
    char key[] = "This is a secret key that will be used to chypher the text";

    for (int i = 0; i < 16; i++)
    {
        c = *(str+i) ^ key[i];
        if (c != 0x16)
            ret[i] = c;
        else
            ret[i] = 0x20;
    }
    ret[16] = '\0';

    return ret;
}
