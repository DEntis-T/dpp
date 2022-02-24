/*
*
* D++ Language
*
* (c) Copyright - 2022, DEntisT.
*
* Core functions.
*
*/

#define dpp_%0\32; dpp_
#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif
#define dppfunc::%0(%1) stock dpp_%0(%1)

static dpp_split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i]==delimiter || i==strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

stock dpp_loadconfig(id)
{
    new d_ArrayCoordinates[19][32],file_name[100];
    format(file_name, sizeof file_name,
        dpp_configfile, id);
    new strFromFile2[128];
    if(!fexist(file_name)) return 0;
    new File: file = fopen(file_name, io_read);
    if (file)
    {
        fread(file, strFromFile2);
        d_me_SplitString(strFromFile2, d_ArrayCoordinates, ',');
        strmid(g_Config[file], d_ArrayCoordinates[0], 0, strlen(d_ArrayCoordinates[0]));
        
        fclose(file);
    }
    return 1;
}

stock dpp_saveconfig(loopid)
{
    new string[228], file_name[100];
    format(file_name, sizeof file_name,
        dpp_configfile, loopid);
    new id = loopid;
    format(string, sizeof(string), 
        "%f,%f,%f,%f,%f,%f,%i");
    new File: file2 = fopen(file_name, io_write);
    fwrite(file2, string);
    fclose(file2);
    return 1;
}

dppfunc::init()
{
    print("                                        ");
    print("|======================================|");
    print("                                        ");
    print("            The D++ Language            ");
    print("          System is loading...          ");
    print("                                        ");
    print("               By: DEntisT              ");
    print("                                        ");
    print("|======================================|");
    print("                                        ");
    print("                                        ");
    print("                                        ");
}
/*
dppfunc::error(const str[])
{
    new output[256];
    format(output, sizeof output, "D++ | Error: %s",str);
    printf(output);    
    return 1;
}

dppfunc::debug(const str[])
{
    new output[256];
    format(output, sizeof output, "D++ | Debug: %s",str);
    printf(output);    
    return 1;
}

dppfunc::print(const str[])
{
    new output[256];
    format(output, sizeof output, "[D++]: (info) - %s",str);
    printf(output);    
    return 1;
}
*/

#define dpp_error(%1) printf("D++ | Error: "%1)
#define dpp_debug(%1) printf("D++ | Debug: "%1)
#define dpp_print(%1) printf("[D++]: (info) - "%1)

dppfunc::process(const line[])
{
    if(isnull(line))
        return 0;
    if(g_Config[execdebug] == 1) printf("[D++]: (info) - Processing: '%s'", line);
    new args[10][100], funcgroup[2][20];
    dpp_split(line, args, ',');
    dpp_split(args[0], funcgroup, '.')
    for(new i; i < strlen(funcgroup[0]); i++)
    {
        if(funcgroup[0][i] == ' ') strdel(funcgroup[0], i, i+1);
    }
    for(new i; i < strlen(funcgroup[0]); i++)
    {
        if(funcgroup[0][i] == '\10') strdel(funcgroup[0], i, i+1);
    }

    // Functions etc
    if(g_Config[execdebug] == 1) printf("[D++]: (info) - funcgrp: '%s %s'", funcgroup[0],funcgroup[1]);
    if(!strcmp(funcgroup[0], "option::debug"))
    {
        g_Config[execdebug] = strval(args[1]);
        return 1;
    }
    if(!strcmp(funcgroup[0], "import::file"))
    {
        for(new i; i < strlen(args[1]); i++)
        {
            if(args[1][i] == '\"') strdel(args[1], i, i+1);
        }
        new dpp_include[32];
        format(dpp_include, 32, "%s.dpp", args[1]);
        /*if(!fexist(dpp_include))
        {
            dpp_error("Cannot read from file: '%s'",funcgroup[1]);
            return 0;
        }*/
        dpp_subexecute(dpp_include);
        return 1;
    }
    if(!strcmp(funcgroup[0], "using::console"))
    {
        // If the function used it "Print"
        if(!strcmp(funcgroup[1], "Print"))
        {
            new mul, str[100];
            strmid(str, args[1], 0, 100);
            for(new i; i < strlen(args[1]); i++)
            {
                if(args[1][i] == '\"') mul++, strdel(args[1], i, i+1);
            }
            if(mul == 0)
            {
                dpp_error("You need to use '\"' to start a string.");
                return 0;
            }
            print(args[1]);
            return 1;
        }
        else
        {
            dpp_error("Unknown function.");
            return 0;
        }
    }
    else
    {
        dpp_error("Unknown directive.");
    }
    return 0;
}

dppfunc::subprocess(const line[])
{
    if(isnull(line))
        return 0;
    if(g_Config[execdebug] == 1) printf("[D++]: (info) - Processing: '%s'", line);
    new args[10][100], funcgroup[2][20];
    dpp_split(line, args, ',');
    dpp_split(args[0], funcgroup, '.')
    for(new i; i < strlen(funcgroup[0]); i++)
    {
        if(funcgroup[0][i] == ' ') strdel(funcgroup[0], i, i+1);
    }
    for(new i; i < strlen(funcgroup[0]); i++)
    {
        if(funcgroup[0][i] == '\10') strdel(funcgroup[0], i, i+1);
    }
    // Functions etc
    if(!strcmp(funcgroup[0], "option::debug"))
    {
        g_Config[execdebug] = strval(funcgroup[1]);
        return 1;
    }
    if(!strcmp(funcgroup[0], "import::file"))
    {
        new dpp_include[32];
        format(dpp_include, 32, "%s.dpp", funcgroup[1]);
        /*if(!fexist(dpp_include))
        {
            dpp_error("Cannot read from file: '%s'",funcgroup[1]);
            return 0;
        }*/
        dpp_subexecute(dpp_include);
        return 1;
    }
    if(!strcmp(funcgroup[0], "using::console"))
    {
        // If the function used it "Print"
        if(!strcmp(funcgroup[1], "Print"))
        {
            new mul, str[100];
            strmid(str, args[1], 0, 100);
            for(new i; i < strlen(args[1]); i++)
            {
                if(args[1][i] == '\"') mul++, strdel(args[1], i, i+1);
            }
            if(mul == 0)
            {
                dpp_error("You need to use '\"' to start a string.");
                return 0;
            }
            print(args[1]);
            return 1;
        }
        else
        {
            dpp_error("Unknown function.");
            return 0;
        }
    }
    else
    {
        dpp_error("Unknown directive.");
    }
    return 0;
}

#define MAX_CODE_LINES 100
#define MAX_LN_CHARS 300

dppfunc::execute(const dirbose[])
{
    printf("=====================[%s]=====================", dirbose);
    new content[16000], address[MAX_CODE_LINES][MAX_LN_CHARS];
    new File:file = fopen(dirbose, io_read);
    if(file)
    {
        fread(file, content);
        for(new i; i < strlen(content); i++)
        {
            if(content[i] == '\10') strdel(content, i, i+1);
        }
        dpp_split(content, address, ';');
        for(new i; i < MAX_CODE_LINES; i++)
        {
            dpp_process(address[i]);
        }
        fclose(file);
    }
    printf("=====================[EOS]=====================", dirbose);
    return 1;
}

dppfunc::subexecute(const dirbose[])
{
    //printf("=====================[%s]=====================", dirbose);
    new content[16000], address[MAX_CODE_LINES][MAX_LN_CHARS];
    new File:file = fopen(dirbose, io_read);
    if(file)
    {
        fread(file, content);
        for(new i; i < strlen(content); i++)
        {
            if(content[i] == '\10') strdel(content, i, i+1);
        }
        dpp_split(content, address, ';');
        for(new i; i < MAX_CODE_LINES; i++)
        {
            dpp_subprocess(address[i]);
        }
        fclose(file);
    }
    //printf("=====================[EOS]=====================", dirbose);
    return 1;
}