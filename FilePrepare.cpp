// FilePrepare.cpp: implementation of the FilePrepare class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FilePrepare.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilePrepare::CFilePrepare()
{
	nFileLength = 0;
	nTokensCount = 0;
	pFileContent = NULL;
	token = NULL;
	SeparatorCoding();
}

CFilePrepare::~CFilePrepare()
{

}

BOOL CFilePrepare::OpenFile(LPCTSTR lpszPathName)
{
	CStdioFile	file(lpszPathName, CFile::modeRead | CFile::typeBinary);
	nFileLength = file.GetLength() ;
	if (pFileContent != NULL)
	{
		delete pFileContent;
		pFileContent = NULL;
	}
	if(nFileLength == 0 || nFileLength < 5)
	{
		AfxMessageBox("Empty file OR The file is semi-Empty(less than 10 chars)!!!");
		return FALSE;
	}
	if((pFileContent = new char[nFileLength+1]) == NULL)
	{
		AfxMessageBox("Couldn't allocate memory for file!!! ");
		return FALSE;
	}	
	if(file.Read(pFileContent, nFileLength) == NULL)
	{
		AfxMessageBox("Empty file ");
		return FALSE;
	}
	pFileContent[nFileLength] = NULL;
	file.Close();
	return TRUE;
}

void CFilePrepare::FileDraw(CDC *pDC)
{
	pDC->GetTextMetrics(&tm);
	pDC->TabbedTextOut(10, 10, pFileContent,0,NULL,0);

}

void CFilePrepare::PrepareTotSize(CSize *sizeTotal)
{
	sizeTotal->cx = (LONG)((tm.tmMaxCharWidth - 9) * nFileLength) ;
	sizeTotal->cy = 100;

}

void CFilePrepare::FileTokens()
{
/*	//// not needed for now in this application
	int nEstimatedTokenCount;
	nTokensCount = 0;
//////counting # of \n //////////////////////////////////////////////
	int i=0, nEnterCount = 0;
	while(pFileContent[i])
	{
		if(pFileContent[i] == '\n')
			nEnterCount++;
		i++;
	}
	pFileContent[nFileLength - nEnterCount] = '\0';
/////////////////////////////////////////////////////////////////////
	// estimated rule based on the results of common words frequencies
	// could be refined based on further resluts of the incoming inputs...
	// %40 common words with length 3 or 4 and %60 regular words of length 10
	//////////////////////////////////////////////////////////////////////////
	nEstimatedTokenCount = (int)((0.4 * nFileLength)/3) + ((0.6 * nFileLength)/10);

/////////////////////////////////////////////////////////

	WORDINFO tempWawoo;
	BOOL bWawoo = FALSE;
	token = new WORDINFO [nEstimatedTokenCount + 1];
	token[nTokensCount] = strtok( (unsigned char *)pFileContent);
	while( token[nTokensCount].cWord[0] != NULL )
	{
		if (!strcmp((char *)token[nTokensCount].cWord, "æ"))
			bWawoo = TRUE;
		nTokensCount++;
		if(nTokensCount > nEstimatedTokenCount)
		{
			NeedExtraMem(token, 25 + nTokensCount);
			nEstimatedTokenCount += 26;
		}
		token[nTokensCount] = strtok( NULL);
		if( bWawoo && (!token[nTokensCount - 1].bDominantSeparator) ) 
		{   // it works in 2 cases in case of æ  and Initiales
			bWawoo = FALSE;
			//tempWawoo = token[nTokensCount];
			strcat((char *)token[nTokensCount - 1].cWord, (char *)token[nTokensCount].cWord);
			token[nTokensCount - 1].bDominantSeparator = token[nTokensCount].bDominantSeparator;
			nTokensCount--;
		}
		else
			bWawoo = FALSE;
	}
	token[nTokensCount - 1].bDominantSeparator = 1;
	//nTokensCount++; // for processing requirements
/////////////////////////////////////////////////////////
*/
}

WORDINFO CFilePrepare::strtok(unsigned char *string)
{
    static unsigned char *nextoken;
    unsigned char *str;//, sepInit[2];
	BOOL bReject, bWawooFlag, bInitiales;
	WORDINFO tempTI;
	::strtok( (char*)string, ".:");
    if (string)
		str = string;
    else
	{
		if (nextoken)
			str = nextoken;
		else
			AfxMessageBox("you called the strtok by a null pointer as a start!!!");
	}

	do
	{
		bReject = FALSE;
		bWawooFlag = FALSE;
		bInitiales = FALSE;
		/* Find beginning of token (skip over leading delimiters). Note that
		 * there is no token iff this loop sets str to point to the terminal
		 * null (*str == '\0') */
		while ( (map[*str >> 3] & (1 << (*str & 7))) && *str )
			str++;
		string = str;
		/* Find the end of the token. If it is not the end of the string,
		 * put a null there. */
		for ( ; *str ; str++ )
		{
/* //Commented because i handle it in the separator array...
			if ( (*str > 64 && *str < 91)||(*str > 96 && *str < 123) )// latin chars;;;
				bReject = TRUE;
*/
			if ( map[*str >> 3] & (1 << (*str & 7)) ) 
			{
/*				
				switch (*str)
				{
				case  '\n' :
				case  ' '  :
				case  254  :
				case  '\t' :
					// dominant_separator field of the current token = FALSE;
					tempTI.bDominantSeparator = FALSE;
					break;
				default:
					// dominant_separator field of the current token = TRUE;
					tempTI.bDominantSeparator = TRUE;
				}
*/
/*    //// not needed because i disabled the detecting initiales method ...
				if(*str == '.' || *str == '/')
				{
					//strcpy((char *)sepInit, (char *)*str);
					sepInit[0] = *str;
					sepInit[1] = NULL;
					bInitiales = TRUE;
				}
*/
				*str++ = '\0';
/*   //// not needed for now because i added the single chars that will appear in stoplist ...
				if(bInitiales && strlen((char *)string) == 1)
				{
					strcat((char *)string, (char *)sepInit);
					DetectInitiales(str);
				}
*/
/*    //// not needed for now because i added WAWOO to stop list ...
				if(!strcmp((char *)string, "æ"))
					bWawooFlag = TRUE;
*/
				break;
			}
		}
	}while(bReject);
/*
///////for multiple separator after finding the token /////////////////
		while( map[*str >> 3] & (1 << (*str & 7)) && *str) 
		{

			switch (*str)
			{
			case  ' '  :
			case  254  :
			case  '\t' :
			case  '\n' :
				// dominant_separator feild of the current token = FALSE;
				if(tempTI.bDominantSeparator == FALSE)
					tempTI.bDominantSeparator = FALSE;
				break;
			default:
				// dominant_separator feild of the current token = TRUE;
				tempTI.bDominantSeparator = TRUE;
			}
			str++;
		}

/////////////////////////////////////////////////////////////////////
*/
  nextoken = str;
    /* Determine if a token has been found. */
    if ( string == str )
	{
		nextoken = NULL;
		strcpy((char*)tempTI.cWord, "\0");
		//tempTI.cWord[0] = NULL;
		return tempTI;
	}
    else
	{
		strcpy((char *)tempTI.cWord, (char *)string);
		return tempTI;
	}
	
}

void CFilePrepare::SeparatorCoding()
{
	unsigned char seps1[] = "~!@#$%^&*()-+=_<>[]{}:¡,/\\'\".?|0123456789\t\n\r;º¿ ÜabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const unsigned char *ctrl = seps;
	unsigned char cX[76];

	cX[0] = 254; // 
	cX[1] = 133;    cX[20] = 128;	cX[39] = 169;	cX[58] = 215;
	cX[2] = 127;	cX[21] = 131;	cX[40] = 171;	cX[59] = 224;
	cX[3] = 138;	cX[22] = 134;	cX[41] = 172;	cX[60] = 226;
	cX[4] = 143;	cX[23] = 135;	cX[42] = 173;	cX[61] = 231;
	cX[5] = 154;	cX[24] = 137;	cX[43] = 174;	cX[62] = 232;
	cX[6] = 157;	cX[25] = 140;	cX[44] = 175;	cX[63] = 233;
	cX[7] = 158;	cX[26] = 149;	cX[45] = 176;	cX[64] = 234;
	cX[8] = 159;	cX[27] = 150;	cX[46] = 177;	cX[65] = 235;
	cX[9] = 160;	cX[28] = 151;	cX[47] = 178;	cX[66] = 238;
	cX[10] = 132;	cX[29] = 153;	cX[48] = 179;	cX[67] = 239;
	cX[11] = 170;	cX[30] = 155;	cX[49] = 181;	cX[68] = 244;
	cX[12] = 147;	cX[31] = 156;	cX[50] = 182;	cX[69] = 247;
	cX[13] = 148;	cX[32] = 162;	cX[51] = 183;	cX[70] = 249;
	cX[14] = 192;	cX[33] = 163;	cX[52] = 184;	cX[71] = 251;
	cX[15] = 215;	cX[34] = 164;	cX[53] = 185;	cX[72] = 252;
	cX[16] = 224;	cX[35] = 165;	cX[54] = 187;	cX[73] = NULL;
	cX[17] = 226;	cX[36] = 166;	cX[55] = 188;	cX[74] = 13;
	cX[18] = 253;	cX[37] = 167;	cX[56] = 189;	cX[75] = 10;
	cX[19] = 255;	cX[38] = 168;	cX[57] = 190;
	///////////////cX[39] = 169;///ocX[58] = 215;other special characters 
	//int x = strlen((char*)seps);
	strcpy((char*)seps, (char*)seps1);
	strcat((char*)seps, (char*)cX);
	/* Clear control map */
    for (int count = 0; count < 32; count++)
            map[count] = 0;
    /* Set bits in delimiter table */
    do {
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
    } while (*ctrl++);

}

void CFilePrepare::NeedExtraMem(WORDINFO *token, int newCount)
{
	WORDINFO *tempWI = new WORDINFO [newCount];
	memcpy(tempWI, token, (sizeof(WORDINFO)) * nTokensCount);
	delete token;
	token = tempWI;
}

void CFilePrepare::DetectInitiales(unsigned char *str, unsigned char *string)
{
/*
	unsigned char * Initstr = str;

	for ( ; *str ; str++ )
		{
		if ( map[*str >> 3] & (1 << (*str & 7)) ) 
		{
			switch (*str)
			{
			case  '.' :
			case  ' '  :
			case  254  :
			case  '\t' :
				// dominant_separator feild of the current token = FALSE;
				tempTI.bDominantSeparator = FALSE;
				break;
			default:
				// dominant_separator field of the current token = TRUE;
				tempTI.bDominantSeparator = TRUE;
			}
			if(*str == '.' || *str == '/')
			{
				//strcpy((char *)sepInit, (char *)*str);
				sepInit[0] = *str;
				sepInit[1] = NULL;
				bInitiales = TRUE;
			}
			*str++ = '\0';
			if(bInitiales && strlen((char *)string) == 1)
			{
				strcat((char *)string, (char *)sepInit);
				DetectInitiales(str);
			}
			if(!strcmp((char *)string, "æ"))
				bWawooFlag = TRUE;
			break;
		}
	}
*/
}
