#ifndef _INC_PBasic_H
#define _INC_PBasic_H
#if defined(PHREEQCI_GUI)
#include <windows.h>
#endif
#include <map>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <setjmp.h>
#include "phrqtype.h"
#include "PHRQ_base.h"
#include "global_structures.h"
class Phreeqc;

class PBasicStop : public std::exception
{
};

#define forloop         0
#define whileloop       1
#define gosubloop       2
#define checking	true
#define varnamelen      20
#define maxdims	 4
#define MAX_LINE 4096
#define FileNotFound     10
#define FileNotOpen      13
#define FileWriteError   38
#define BadInputFormat   14
#define EndOfFile        30
#define SETBITS  32
#define Const

typedef char varnamestring[varnamelen + 1];

/* Header file for code generated by "p2c", the Pascal-to-C translator */

/* "p2c"  Copyright (C) 1989, 1990, 1991 Free Software Foundation.
 * By Dave Gillespie, daveg@csvax.cs.caltech.edu.  Version 1.20.
 * This file may be copied, modified, etc. in any way.  It is not restricted
 * by the licence agreement accompanying p2c itself.
 */

typedef struct varrec
{
	varnamestring name;
	struct varrec *next;
	long dims[maxdims];
	char numdims;
	bool stringvar;
	union
	{
		struct
		{
			LDBLE *arr;
			LDBLE *val, rv;
		} U0;
		struct
		{
			char **sarr;
			char **sval, *sv;
		} U1;
	} UU;
} varrec;

typedef struct tokenrec
{
	struct tokenrec *next;
	int kind;
	union
	{
		struct varrec *vp;
		LDBLE num;
		char *sp;
		char snch;
	} UU;
//#ifdef PHREEQCI_GUI
	size_t n_sz;
	char *sz_num;
//#endif
} tokenrec;

typedef struct linerec
{
	long num, num2;
	tokenrec *txt;
	char inbuf[MAX_LINE];
	struct linerec *next;
} linerec;

class valrec
{
public:
	valrec()
	{
		stringval = false;
		UU.val = 0;
	}
	~valrec() {}
	bool stringval;
	union
	{
		LDBLE val;
		char *sval;
	} UU;
};

typedef struct looprec
{
	struct looprec *next;
	linerec *homeline;
	tokenrec *hometok;
	int kind;
	union
	{
		struct
		{
			varrec *vp;
			LDBLE max, step;
		} U0;
	} UU;
} looprec;

/*  variables for exec: */
struct LOC_exec
{
	bool gotoflag, elseflag;
	tokenrec *t;
};

class PBasic: public PHRQ_base
{
public:
	PBasic(Phreeqc *ptr, PHRQ_io *phrq_io=NULL);
	virtual ~PBasic();

	enum BASIC_TOKEN
	{
		tokvar,
		toknum,
		tokstr,
		toksnerr,
		tokplus,
		tokminus,
		toktimes,
		tokdiv,
		tokup,
		toklp,
		tokrp,
		tokcomma,
		toksemi,
		tokcolon,
		tokeq,
		toklt,
		tokgt,
		tokle,
		tokge,
		tokne,
		tokand,
		tokor,
		tokxor,
		tokmod,
		toknot,
		toksqr,
		toksqrt,
		toksin,
		tokcos,
		toktan,
		tokarctan,
		toklog,
		tokexp,
		tokabs,
		toksgn,
		tokstr_,
		tokval,
		tokchr_,
		tokasc,
		toklen,
		tokmid_,
		tokpeek,
		tokrem,
		toklet,
		tokprint,
		tokinput,
		tokgoto,
		tokif,
		tokend,
		tokstop,
		tokfor,
		toknext,
		tokwhile,
		tokwend,
		tokgosub,
		tokreturn,
		tokread,
		tokdata,
		tokrestore,
		tokgotoxy,
		tokon,
		tokdim,
		tokpoke,
		toklist,
		tokrun,
		toknew,
		tokload,
		tokmerge,
		toksave,
		tokbye,
		tokdel,
		tokrenum,
		tokthen,
		tokelse,
		tokto,
		tokstep,
		toktc,
		tokm0,
		tokm,
		tokparm,
		tokact,
		tokmol,
		tokla,
		toklm,
		toksr,
		toksi,
		toktot,
		toktk,
		toktime,
		toklog10,
		toksim_time,
		tokequi,
		tokgas,
		tokpunch,
		tokkin,
		toks_s,
		tokmu,
		tokalk,
		tokrxn,
		tokdist,
		tokmisc1,
		tokmisc2,
		tokedl,
		tokstep_no,
		toksim_no,
		toktotal_time,
		tokput,
		tokget,
		tokcharge_balance,
		tokpercent_error,
#if defined (PHREEQ98) || defined (MULTICHART)
		tokgraph_x,
		tokgraph_y,
		tokgraph_sy,
#endif
		tokcell_no,
		tokexists,
		toksurf,
		toklk_species,
		toklk_named,
		toklk_phase,
		toksum_species,
		toksum_gas,
		toksum_s_s,
		tokcalc_value,
		tokdescription,
		toksys,
		tokinstr,
		tokltrim,
		tokrtrim,
		toktrim,
		tokpad,
		tokchange_por,
		tokget_por,
		tokosmotic,
		tokchange_surf,
		tokporevolume,
		toksc,
		tokgamma,
		toklg,
		tokrho,
		tokcell_volume,
		tokcell_pore_volume,
		tokcell_porosity,
		tokcell_saturation,
#if defined MULTICHART
		tokplot_xy,
#endif
		toktotmole,
		tokiso,
		tokiso_unit,
		toktotmol,
		toktotmoles,
		tokeol_,
		tokceil,
		tokfloor,
		tokphase_formula,
		toklist_s_s,
		tokpr_p,
		tokpr_phi,
		tokgas_p,
		tokgas_vm,
		tokpressure,
		tokerase,
		tokeps_r,
		tokvm,
		tokdh_a,
		tokdh_b,
		tokdh_av,
		tokqbrn,
		tokkappa,
		tokgfw,
		toksoln_vol,
		tokequi_delta,
		tokkin_delta,
		tokkin_time,
		tokstr_f_
	};

#if !defined(PHREEQCI_GUI)
	enum IDErr
	{
		IDS_ERR_ARRAY_ALREADY,
		IDS_ERR_BAD_SUBSCRIPT,
		IDS_ERR_EXTRA,
		IDS_ERR_FOR_WO_NEXT,
		IDS_ERR_ILLEGAL,
		IDS_ERR_INFINITE_LOOP,
		IDS_ERR_INPUT_NOTLEGAL,
		IDS_ERR_MISMATCH,
		IDS_ERR_MISSING_Q,
		IDS_ERR_MISSING_RP,
		IDS_ERR_NEXT_WO_FOR,
		IDS_ERR_OUT_OF_DATA,
		IDS_ERR_RETURN_WO_GOSUB,
		IDS_ERR_SYNTAX,
		IDS_ERR_UNDEF_LINE,
		IDS_ERR_WEND_WO_WHILE,
		IDS_ERR_WHILE_WO_WEND
	};
#endif

	// Methods
	bool Get_phreeqci_gui(void) const {return phreeqci_gui;};
	void Set_phreeqci_gui(bool tf) {phreeqci_gui = tf;};
	bool Get_parse_all(void) const {return parse_all;};
	void Set_parse_all(bool tf) {parse_all = tf;};
	bool Get_parse_whole_program(void) const {return parse_whole_program;};
	void Set_parse_whole_program(bool tf) {parse_whole_program = tf;};
	int Get_nErrLineNumber(void) const {return nErrLineNumber;};
	void Set_nErrLineNumber(int i) {nErrLineNumber = i;};
#if defined(PHREEQCI_GUI)
	UINT Get_nIDErrPrompt(void)const {return nIDErrPrompt;};
	void Set_nIDErrPrompt(UINT u) {nIDErrPrompt = u;};
	int Get_P_escapecode(void)const {return P_escapecode;};
	void Set_P_escapecode(int code) {P_escapecode = code;};
	HANDLE Get_hInfiniteLoop(void) const {return hInfiniteLoop;};
	void Set_hInfiniteLoop(HANDLE h) {hInfiniteLoop = h;};
#endif
	int free_dim_stringvar(varrec *varbase);

	void exec(void);
	int basic_renumber(char *commands, void **lnbase, void **vbase, void **lpbase);
	void restoredata(void);
	void clearloops(void);
	void clearvar(varrec * v);
	void clearvars(void);
	char * numtostr(char * Result, LDBLE n);
	void parse(char * inbuf, tokenrec ** buf);
	void listtokens(FILE * f, tokenrec * buf);
	void disposetokens(tokenrec ** tok);
	void parseinput(tokenrec ** buf);
	void errormsg(const char * s);
	void snerr(const char * s);
	void tmerr(const char * s);
	void badsubscr(void);
	LDBLE realfactor(struct LOC_exec *LINK);
	char * strfactor(struct LOC_exec * LINK);
	char *stringfactor(char * Result, struct LOC_exec *LINK);
	const char *stringfactor(std::string & Result, struct LOC_exec * LINK);
	long intfactor(struct LOC_exec *LINK);
	LDBLE realexpr(struct LOC_exec *LINK);
	char * strexpr(struct LOC_exec * LINK);
	char * stringexpr(char * Result, struct LOC_exec * LINK);
	long intexpr(struct LOC_exec *LINK);
	void require(int k, struct LOC_exec *LINK);
	void skipparen(struct LOC_exec *LINK);
	varrec * findvar(struct LOC_exec *LINK);
	valrec factor(struct LOC_exec *LINK);
	valrec upexpr(struct LOC_exec * LINK);
	valrec term(struct LOC_exec * LINK);
	valrec sexpr(struct LOC_exec * LINK);
	valrec relexpr(struct LOC_exec * LINK);
	valrec andexpr(struct LOC_exec * LINK);
	valrec expr(struct LOC_exec *LINK);
	void checkextra(struct LOC_exec *LINK);
	bool iseos(struct LOC_exec *LINK);
	void skiptoeos(struct LOC_exec *LINK);
	linerec * findline(long n);
	linerec * mustfindline(long n);
	void cmdend(struct LOC_exec *LINK);
	void cmdnew(struct LOC_exec *LINK);
	void cmdlist(struct LOC_exec *LINK);
	void cmdload(bool merging, char * name, struct LOC_exec *LINK);
	void cmdrun(struct LOC_exec *LINK);
	void cmdsave(struct LOC_exec *LINK);
	void cmdput(struct LOC_exec *LINK);
	void cmdchange_por(struct LOC_exec *LINK);
	void cmdchange_surf(struct LOC_exec *LINK);
	void cmdbye(void);
	void cmddel(struct LOC_exec *LINK);
	void cmdrenum(struct LOC_exec *LINK);
	void cmdprint(struct LOC_exec *LINK);
	void cmdpunch(struct LOC_exec *LINK);
#if defined PHREEQ98 || defined MULTICHART
	void cmdgraph_x(struct LOC_exec *LINK);
	void cmdgraph_y(struct LOC_exec *LINK);
	void cmdgraph_sy(struct LOC_exec *LINK);
#endif
#if defined MULTICHART
	void cmdplot_xy(struct LOC_exec *LINK);
#endif
	void cmdlet(bool implied, struct LOC_exec *LINK);
	void cmdgoto(struct LOC_exec *LINK);
	void cmdif(struct LOC_exec *LINK);
	void cmdelse(struct LOC_exec *LINK);
	bool skiploop(int up, int dn, struct LOC_exec *LINK);
	void cmdfor(struct LOC_exec *LINK);
	void cmdnext(struct LOC_exec *LINK);
	void cmdwhile(struct LOC_exec *LINK);
	void cmdwend(struct LOC_exec *LINK);
	void cmdgosub(struct LOC_exec *LINK);
	void cmdreturn(struct LOC_exec *LINK);
	void cmdread(struct LOC_exec *LINK);
	void cmddata(struct LOC_exec *LINK);
	void cmdrestore(struct LOC_exec *LINK);
	void cmdgotoxy(struct LOC_exec *LINK);
	void cmdon(struct LOC_exec *LINK);
	void cmddim(struct LOC_exec *LINK);
	void cmderase(struct LOC_exec *LINK);
	void cmdpoke(struct LOC_exec *LINK);
	int basic_main(char *commands);
	int basic_compile(char *commands, void **lnbase, void **vbase, void **lpbase);
	int basic_run(char *commands, void *lnbase, void *vbase, void *lpbase);
	int basic_init(void);
#ifdef PHREEQ98
	void GridChar(char *s, char *a);
#endif
	int sget_logical_line(char **ptr, int *l, char *return_line);
	long my_labs(long x);
	void * my_memmove(void * d, Const void * s, size_t n);
	void * my_memcpy(void * d, Const void * s, size_t n);
	int my_memcmp(Const void * s1, Const void * s2, size_t n);
	void * my_memset(void * d, int c, size_t n);
	int my_toupper(int c);
	int my_tolower(int c);
	long ipow(long a, long b);
	char * strsub(register char *ret, register char *s, register int pos,
		register int len);
	int strpos2(char *s, register char *pat, register int pos);
	int strcicmp(register char *s1, register char *s2);
	char * strltrim(register char *s);
	char * strrtrim(register char *s);
	void strmove(register int len, register char *s, register int spos,
		register char *d, register int dpos);
	void strinsert(register char *src, register char *dst, register int pos);
	int P_peek(FILE * f);
	int P_eof(void);
	int P_eoln(FILE * f);
	void P_readpaoc(FILE * f, char *s, int len);
	void P_readlnpaoc(FILE * f, char *s, int len);
	long P_maxpos(FILE * f);
	char * P_trimname(register char * fn, register int len);
	long memavail(void);
	long maxavail(void);
	long * P_setunion(register long *d, register long *s1, register long *s2);
	long * P_setint(register long *d, register long *s1, register long *s2);
	long * P_setdiff(register long *d, register long *s1, register long *s2);
	long * P_setxor(register long *d, register long *s1, register long *s2);
	long * P_addset(register long *s, register unsigned val);
	long * P_addsetr(register long *s, register unsigned v1, register unsigned v2);
	long * P_remset(register long *s, register unsigned val);
	int P_setequal(register long *s1, register long *s2);
	int P_subset(register long *s1, register long *s2);
	long * P_setcpy(register long *d, register long *s);
	long * P_expset(register long *d, register long s);
	long P_packset(register long *s);	
	int _OutMem(void);
	int _CaseCheck(void);
	int _NilCheck(void);
	static char * _ShowEscape(char *buf, int code, int ior, char *prefix);
	int _Escape(int code);
	int _EscIO(int code);

	// data members
protected:
	Phreeqc * PhreeqcPtr;
	char *inbuf;
	linerec *linebase;
	varrec *varbase;
	looprec *loopbase;
	long curline;
	linerec *stmtline, *dataline;
	tokenrec *stmttok, *datatok, *buf;
	bool exitflag;
	long EXCP_LINE;
	static std::map<const std::string, BASIC_TOKEN> command_tokens;
	int P_escapecode;
	int P_ioresult;

	bool phreeqci_gui;
	bool parse_all;    /* true, most function values set to 1 for testing compilation */
	bool parse_whole_program;
	char fnbuf[256];
#if defined(PHREEQCI_GUI)
	HANDLE hInfiniteLoop;
	UINT nIDErrPrompt;
#else
	IDErr nIDErrPrompt;
#endif
	int nErrLineNumber;
};

#endif /* _INC_PBasic_H */
