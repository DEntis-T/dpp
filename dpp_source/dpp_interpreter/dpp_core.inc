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

dppfunc::execute()
{
	return 1;
}