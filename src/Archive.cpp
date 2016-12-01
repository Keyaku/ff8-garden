// Archive.cpp: implementation of the CArchive class.
//
//////////////////////////////////////////////////////////////////////

#include "ui_win32/StdAfx.h"
#include "Garden.h"
#include "Archive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif








#define UBYTE unsigned char /* Unsigned     byte (1 byte )        */
#define UWORD unsigned int  /* Unsigned     word (2 bytes)        */
#define ULONG unsigned long /* Unsigned longword (4 bytes)        */
#define FLAG_BYTES    4     /* Number of bytes used by copy flag. */
#define FLAG_COMPRESS 0     /* Signals that compression occurred. */
#define FLAG_COPY     1     /* Signals that a copyover occurred.  */
void fast_copy(UBYTE *p_src, UBYTE*p_dst,ULONG len) /* Fast copy routine.             */
{while (len--) *p_dst++=*p_src++;}


#define PS *p++!=*s++  /* Body of inner unrolled matching loop.         */
#define ITEMMAX 16     /* Maximum number of bytes in an expanded item.  */

BOOL lzs_compress(UBYTE *p_src_first,ULONG src_len,UBYTE *p_dst_first,ULONG *p_dst_len)
/* Input  : Specify input block using p_src_first and src_len.          */
/* Input  : Point p_dst_first to the start of the output zone (OZ).     */
/* Input  : Point p_dst_len to a ULONG to receive the output length.    */
/* Input  : Input block and output zone must not overlap.               */
/* Output : Length of output block written to *p_dst_len.               */
/* Output : Output block in Mem[p_dst_first..p_dst_first+*p_dst_len-1]. */
/* Output : May write in OZ=Mem[p_dst_first..p_dst_first+src_len+256-1].*/
/* Output : Upon completion guaranteed *p_dst_len<=src_len+FLAG_BYTES.  */
{
	UBYTE *p_src=p_src_first,*p_dst=p_dst_first;
	UBYTE *p_src_post=p_src_first+src_len,*p_dst_post=p_dst_first+src_len;
	UBYTE *p_src_max1=p_src_post-ITEMMAX,*p_src_max16=p_src_post-8*ITEMMAX;
	UBYTE *hash[4096], *p_control;
	UWORD control=0,control_bits=0;

	*p_dst=FLAG_COMPRESS; p_dst+=FLAG_BYTES; p_control=p_dst; p_dst++;

	while (TRUE) {
		UBYTE *p,*s;
		UWORD unroll=8,len,index;
		ULONG offset;
//		if (p_dst > p_dst_post) goto overrun;	// NEVER direct copy at this level
		if (p_src > p_src_max16) {
			unroll = 1;
			if (p_src > p_src_max1) {
				if (p_src == p_src_post) break;
				goto literal;
			}
		}

begin_unrolled_loop:

		index = ((40543 * ((((p_src[0] << 4) ^ p_src[1]) << 4) ^ p_src[2])) >> 4) & 0xFFF;
		p = hash[index];
		hash[index] = s = p_src;
		offset = s-p;
		if (offset>4095 || p<p_src_first || offset==0 || PS || PS || PS) {
literal:
			*p_dst++ = *p_src++;
			control >>= 1;
			control_bits++;
		}
		else {
			PS || PS || PS || PS || PS || PS || PS ||
			PS || PS || PS || PS || PS || PS || s++;
			len = s-p_src-1;

			// Change offset here...
			offset = ((p_src - p_src_first) - offset - 18) & 0xFFF;

			*p_dst++ = (BYTE)offset;
			*p_dst++ = (BYTE)(((offset & 0xF00) >> 4) + (len - 3));
			p_src += len;
			control = (control >> 1) | 0x80;
			control_bits++;
		}

//end_unrolled_loop:

		if (--unroll) goto begin_unrolled_loop;

		if (control_bits==8) {
			*p_control = control ^ 0xFF;

			p_control = p_dst;
			p_dst++;
			control = control_bits = 0;
		}
	}
	
	control >>= 8-control_bits;
	*p_control++ = control ^ 0xFF;
	//*p_control++ = control >> 8;

	if (p_control == p_dst) p_dst--;
	*p_dst_len = p_dst - p_dst_first;
	*(int*)p_dst_first = *p_dst_len - 4;
	return 1;

//overrun:
	fast_copy(p_src_first,p_dst_first,src_len);
	*p_dst_first = FLAG_COPY;
	*p_dst_len = src_len;

	return 0;

}

/******************************************************************************/

void lzs_decompress(UBYTE *p_src_first,ULONG src_len, UBYTE *p_dst_first,ULONG *p_dst_len)
/* Input  : Specify input block using p_src_first and src_len.          */
/* Input  : Point p_dst_first to the start of the output zone.          */
/* Input  : Point p_dst_len to a ULONG to receive the output length.    */
/* Input  : Input block and output zone must not overlap. User knows    */
/* Input  : upperbound on output block length from earlier compression. */
/* Input  : In any case, maximum expansion possible is eight times.     */
/* Output : Length of output block written to *p_dst_len.               */
/* Output : Output block in Mem[p_dst_first..p_dst_first+*p_dst_len-1]. */
/* Output : Writes only  in Mem[p_dst_first..p_dst_first+*p_dst_len-1]. */
{
	UWORD controlbits = 0, control;
	UBYTE *p_src = p_src_first,
		*p_dst = p_dst_first,
		*p_src_post = p_src_first+src_len;

	while (p_src != p_src_post) {
		if (controlbits == 0) {
			control = *p_src++;
			controlbits = 8;
		}
		if (!(control & 1)) {
			UWORD offset,len; UBYTE *p;
			offset = *p_src++ & 0xFF;
			offset += (*p_src & 0xF0) << 4;
			len = 3 + (*p_src++ & 0xF);

			p = p_dst - (((p_dst - p_dst_first) - (offset + 18)) & 0xFFF);

			while (len--) {
				if (p < p_dst_first) {
					*p_dst++ = 0;
					p++;
				}
				else
					*p_dst++ = *p++;
			}
		}
		else
			*p_dst++ = *p_src++;
		
		control >>= 1;
		controlbits--;
	}

	*p_dst_len = p_dst - p_dst_first;
}










//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFF8Archive::CFF8Archive()
{
	headers = NULL;
	nFiles = 0;
	nFilled = 0;
	strArchive = "";
}

CFF8Archive::~CFF8Archive()
{
	if (headers) delete[] headers;
}

int CFF8Archive::AddFile(CString strFilename, CString strTag, BOOL compress)
{
	if (nFilled == nFiles) return 0;
	
	CFile temp;
	if (!temp.Open(strFilename,CFile::modeRead)) return 0;
	headers[nFilled].uSize = temp.GetLength();
	temp.Close();
	strncpy(headers[nFilled].szName,strTag,64);
	headers[nFilled].bCompressed = compress;

	nFilled++;
	return nFilled;
}


// Open an existing archive
int CFF8Archive::Load(LPCTSTR szArchive)
{
	if (!szArchive) return 0;

	if ((HFILE)fi != (UINT)-1) fi.Close();
	if ((HFILE)fi != (UINT)-1) fl.Close();
	if ((HFILE)fi != (UINT)-1) fs.Close();

	strArchive = szArchive;
//	CString filename = szArchive;

//	filename = strArchive + ".fi";
	if (!fi.Open(strArchive + ".fi",CFile::modeRead)) return 0;
	fi.Close();
//	filename = strArchive + ".fl";
	if (!fl.Open(strArchive + ".fl",CFile::modeRead)) return 0;
	fl.Close();
//	filename = strArchive + ".fs";
	if (!fs.Open(strArchive + ".fs",CFile::modeRead)) return 0;
	fs.Close();

	fi.Open(strArchive + ".fi",CFile::modeRead);
	fl.Open(strArchive + ".fl",CFile::modeRead);
	fs.Open(strArchive + ".fs",CFile::modeRead);

	nFiles = fi.GetLength() / 12;
	if (headers) delete[] headers;
	headers = new FF8FILEHEADER[nFiles];

	for (int i=0;i<nFiles;i++) {
		fi.Read(&headers[i].uSize,12);
	}

	int p;
	for (i=0;i<nFiles;i++) {
		p = 0;
		while (1) {
			fl.Read(&headers[i].szName[p],1);
			if (headers[i].szName[p-1] == 0x0D && headers[i].szName[p] == 0x0A) break;
			p++;
		}
		headers[i].szName[p-1] = 0x00;
	}

	return nFiles;
}


int CFF8Archive::GetCount()
{
	return nFiles;
}

int CFF8Archive::Save(CString strRelDir, CProgressDlg *dlg)
{
	if (nFiles != nFilled) return 0;	// Archive must be filled before saving
	
	if ((HFILE)fi != (UINT)-1) fi.Close();
	if ((HFILE)fi != (UINT)-1) fl.Close();
	if ((HFILE)fi != (UINT)-1) fs.Close();
	
	fi.Open(strArchive + ".fi",CFile::modeWrite | CFile::modeCreate);
	fl.Open(strArchive + ".fl",CFile::modeWrite | CFile::modeCreate);
	fs.Open(strArchive + ".fs",CFile::modeWrite | CFile::modeCreate);

	if (dlg) dlg->SetRange(0,nFiles);
	if (dlg) dlg->SetPos(0);

	CString line;
	CFile temp;
	char buf[0x4000];
	UINT offset=0;
	int q;
	for (int i=0;i<nFiles;i++) {
		line = strRelDir;
		line += (headers[i].szName + 3);
		headers[i].uOffset = offset;
		fi.Write(&headers[i].uSize,12);

		if (!temp.Open(line,CFile::modeRead)) return 0;

		if (headers[i].bCompressed) {
			offset += DeflateFile(&fs,&temp);
		}
		else {
			for (UINT j=0;j<headers[i].uSize;j+=0x4000) {
				if ((j+0x4000)>headers[i].uSize) {		// Last write
					temp.Read(buf,headers[i].uSize % 0x4000);
					fs.Write(buf,headers[i].uSize % 0x4000);
				} else {
					temp.Read(buf,0x4000);
					fs.Write(buf,0x4000);
				}
			}
			offset += headers[i].uSize;
		}

		temp.Close();

		line = headers[i].szName;
		line += "\r\n";
		q = strlen(line);
		fl.Write(line,strlen(line));

		dlg->SetPos(i+1);
	}

	fi.Close();
	fl.Close();
	fs.Close();


	return nFiles;

}

int CFF8Archive::ExtractFile(int index, LPCTSTR szFilename, CProgressDlg *dlg)
{

	int r = 0;
	fs.Seek(headers[index].uOffset,CFile::begin);

	CFile dest;

tryagain:

	if (!dest.Open(szFilename,CFile::modeWrite | CFile::modeCreate)) {
		if (ERROR_PATH_NOT_FOUND == GetLastError()) {
			CreateDir(szFilename);
			goto tryagain;
		}
		return 0;
	}

	if (headers[index].bCompressed) {
		r = InflateFile(&dest,&fs,headers[index].uSize);

	} else {
		if (dlg) dlg->SetRange(0,headers[index].uSize);
		if (dlg) dlg->SetPos(0);
		char *buf = new char[headers[index].uSize]; //(char*)malloc(slots[index].size);
		if (!buf) return FALSE;
		fs.Read(buf,headers[index].uSize);
		dest.Write(buf,headers[index].uSize);
		r = headers[index].uSize;
		delete[] buf; //free(buf);
		if (dlg) dlg->SetPos(headers[index].uSize);

	}

	dest.Close();
	
	return r;
}

int CFF8Archive::InflateFile(CFile *dest, CFile *src, DWORD dwSize)
{
	if (!src || !dest) return NULL;

//	theProgress.Create();


	BYTE *_src = NULL;
	BYTE *_dest = NULL;

	ULONG srclen=0, destlen=0;
	src->Read(&srclen,4);

	_src = (BYTE*)malloc(srclen);
	_dest = (BYTE*)malloc(dwSize);

	src->Read(_src,srclen);

	lzs_decompress(_src,srclen,_dest,&destlen);

	dest->Write(_dest,destlen);

	free(_src);
	free(_dest);

	return destlen;

/*	UINT byte = 0, size = 0, wbytes = 0;
	int roffs = 0, rsize = 0;
	USHORT pointer = 0;
	BYTE byPeriod = 0, byFlags = 0;
	char chCopy = 0;

	src->Read(&size,4);

	char ref[0x1000];
	memset(ref,0,0x1000);
	int iRef = 0x0FEE;

	BYTE status = 0;
	if (dlg) dlg->SetRange(0,size);
	if (dlg) dlg->SetPos(0);

	while (byte<size) {
		if (byPeriod == 0) {
			src->Read(&byFlags,1);
			byte++;
		}
		else {
			if ((1 << (byPeriod - 1)) & byFlags) {		// Raw byte
				src->Read(&chCopy,1);
				ref[iRef++] = chCopy;
				if (iRef == 0x1000) iRef = 0;
				dest->Write(&chCopy,1);
				wbytes++;
				byte++;
			}
			else {							// Offset-length pair
					
				src->Read(&pointer,2);
				rsize = ((pointer & 0x0F00) >> 8) + 3;

				roffs = pointer & 0xFF;
				roffs |= ((pointer & 0xF000) >> 4);
				if (roffs == 0x1000) roffs = 0;

				wbytes += rsize;

				while (rsize--) {
					ref[iRef++] = ref[roffs];
					iRef &= 0xFFF;
					dest->Write(&ref[roffs],1);
					roffs++;
					if (roffs == 0x1000) roffs = 0;
				}
	
				byte += 2;
			}
		}

		byPeriod++;
		if (byPeriod > 8) {
			byPeriod = 0;		
			if (status == 0) if (dlg) dlg->SetPos(byte);
			status++;
		}

	}

	return wbytes;
*/
}

LPSTR CFF8Archive::GetFileName(LPSTR buf, int index)
{
	if (!buf) return NULL;
	strncpy(buf,headers[index].szName,64);
	return buf;
}

int CFF8Archive::CreateDir(LPCTSTR dir)
{
	char buf[MAX_PATH];

	UINT i = 0, r = 0;
	while (i < strlen(dir)) {
		if (dir[i] == '\\') {
			memset(buf,0,MAX_PATH);
			strncpy(buf,dir,i+1);
			r = CreateDirectory(buf,NULL);
		}
		i++;
	}
	return r;

}

BOOL CFF8Archive::IsCompressed(int index)
{
	return headers[index].bCompressed;
}




int CFF8Archive::DeflateFile(CFile *dest, CFile *src)
{
//	if (!src || !dest) return NULL;

//	ASSERT(FALSE);		// This function should not be used yet
//	return NULL;
	BYTE *_src = NULL;
	BYTE *_dest = NULL;

	ULONG srclen=src->GetLength(), destlen=0;

	_src = (BYTE*)malloc(srclen);
	_dest = (BYTE*)malloc(10+srclen*9/8);

	src->Read(_src,srclen);

	lzs_compress(_src,srclen,_dest,&destlen);

	dest->Write(_dest,destlen);

	free(_src);
	free(_dest);

	return destlen;

}

int CFF8Archive::SetFileCount(int files)
{
	if (headers) delete[] headers;

	headers = new FF8FILEHEADER[files];
	nFilled = 0;
	nFiles = files;

	return nFiles;
}

int CFF8Archive::SetFileName(LPCTSTR szName)
{
	strArchive = szName;
	return 1;
}

int CFF8Archive::Clear()
{
	nFiles = 0;
	nFilled = 0;
	if ((HFILE)fi != (UINT)-1) fi.Close();
	if ((HFILE)fl != (UINT)-1) fl.Close();
	if ((HFILE)fs != (UINT)-1) fs.Close();
	strArchive = "";
	return 1;
}



