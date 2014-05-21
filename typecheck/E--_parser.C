/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "E--_parser.y++"


#include "Ast.h"
#include "ParserUtil.h"
#include "Error.h"

using namespace std;

extern int verbosity;
extern int yylex();
extern void yyerror(const char *s);
int offSet;
extern const OpNode::OpInfo opInfo[];



/* Line 268 of yacc.c  */
#line 88 "E--_parser.C"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_LEX_ERROR = 258,
     TOK_PAT_STAR = 259,
     TOK_PAT_OR = 260,
     TOK_PAT_NOT = 261,
     TOK_PLUS = 262,
     TOK_MINUS = 263,
     TOK_UMINUS = 264,
     TOK_MULT = 265,
     TOK_DIV = 266,
     TOK_MOD = 267,
     TOK_BITAND = 268,
     TOK_BITOR = 269,
     TOK_BITNOT = 270,
     TOK_BITXOR = 271,
     TOK_SHL = 272,
     TOK_SHR = 273,
     TOK_GT = 274,
     TOK_LT = 275,
     TOK_GE = 276,
     TOK_LE = 277,
     TOK_EQ = 278,
     TOK_NE = 279,
     TOK_AND = 280,
     TOK_OR = 281,
     TOK_NOT = 282,
     TOK_COMMA = 283,
     TOK_ASSIGN = 284,
     TOK_SEMICOLON = 285,
     TOK_COLON = 286,
     TOK_ARROW = 287,
     TOK_LBRACE = 288,
     TOK_RBRACE = 289,
     TOK_LPAREN = 290,
     TOK_RPAREN = 291,
     TOK_LBRACK = 292,
     TOK_RBRACK = 293,
     TOK_QMARK = 294,
     TOK_IF = 295,
     TOK_ELSE = 296,
     TOK_CLASS = 297,
     TOK_RETURN = 298,
     TOK_EVENT = 299,
     TOK_ANY = 300,
     TOK_PRINT = 301,
     TOK_WHILE = 302,
     TOK_BREAK = 303,
     TOK_UINTNUM = 304,
     TOK_DOUBLENUM = 305,
     TOK_VOID = 306,
     TOK_STRING = 307,
     TOK_STRCONST = 308,
     TOK_BIT = 309,
     TOK_ENUM = 310,
     TOK_LONG = 311,
     TOK_INT = 312,
     TOK_UNSIGNED = 313,
     TOK_BOOL = 314,
     TOK_BYTE = 315,
     TOK_DOUBLE = 316,
     TOK_SHORT = 317,
     TOK_TRUE = 318,
     TOK_FALSE = 319,
     TOK_IDENT = 320,
     TOK_DOUBLE_COLON = 321,
     TOK_DOT = 322
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 17 "E--_parser.y++"

  unsigned int 		 uVal;
  double             dVal;
  char*              cVal;
  vector<string>*    strVector;
  Value*             valVal;

  ExprNode*          exprVal;
  vector<ExprNode*>* exprList;
  RefExprNode*       refexpVal;

  ClassEntry*        classEntry;
  Type*              typeVal;
  vector<Type*>*     typeList; 

  EventEntry*        eventEntry;                        
  VariableEntry*     variableEntry;
  FunctionEntry*     functionEntry;

  BasePatNode*       patVal;
  PrimitivePatNode*  primPatVal;
  StmtNode*          stmtVal;
  list<StmtNode*>*   stmtList;
  IfNode*            ifVal;
  CompoundStmtNode*  compoundStmtVal;
  RuleNode*          ruleNode;

  vector<RuleNode*>* transList;
  
  vector<Type*>*     formalTypeVal;
  const OpNode::OpInfo*    funIval;

// below is what I add

  vector<VariableEntry*>*   variableList;



/* Line 293 of yacc.c  */
#line 230 "E--_parser.C"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 242 "E--_parser.C"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   597

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  127
/* YYNRULES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    16,    18,    21,
      25,    29,    34,    38,    40,    42,    44,    46,    48,    51,
      55,    57,    61,    65,    69,    72,    75,    77,    81,    85,
      89,    94,    99,   103,   107,   109,   113,   115,   119,   122,
     125,   127,   131,   133,   136,   140,   141,   143,   147,   149,
     151,   153,   157,   159,   161,   165,   168,   171,   173,   176,
     180,   186,   190,   194,   199,   206,   210,   215,   217,   220,
     224,   225,   227,   229,   233,   236,   240,   241,   245,   247,
     250,   253,   255,   257,   259,   261,   263,   266,   269,   273,
     276,   280,   284,   288,   292,   296,   300,   304,   308,   312,
     316,   320,   324,   328,   332,   336,   340,   344,   348,   351,
     353,   355,   357,   359,   361,   362,   364,   366,   370,   373,
     375,   378,   380,   382,   384,   386,   388,   390
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    70,    -1,    70,    71,    -1,    -1,    70,
      73,    -1,    70,     1,    30,    -1,    72,    -1,    71,    72,
      -1,    71,     1,    30,    -1,    75,    32,    76,    -1,    75,
      32,    76,    30,    -1,    75,     1,    76,    -1,    30,    -1,
      77,    -1,    78,    -1,    81,    -1,    74,    -1,    42,    65,
      -1,    42,     1,    30,    -1,    83,    -1,    35,    75,    36,
      -1,    75,    31,    75,    -1,    75,     5,    75,    -1,    75,
       4,    -1,    27,    75,    -1,    87,    -1,    97,    98,    99,
      -1,    97,     1,    30,    -1,   107,    79,    30,    -1,   107,
      79,     1,    30,    -1,   107,    79,    28,     1,    -1,   107,
       1,    30,    -1,    65,     1,    30,    -1,    80,    -1,    79,
      28,    80,    -1,    65,    -1,    65,    29,   101,    -1,    82,
      98,    -1,    44,    65,    -1,    84,    -1,    84,    14,   101,
      -1,    45,    -1,    65,    85,    -1,    35,    86,    36,    -1,
      -1,    65,    -1,    86,    28,    65,    -1,    30,    -1,    93,
      -1,    91,    -1,    33,    89,    34,    -1,    90,    -1,    88,
      -1,    47,   101,    87,    -1,   102,    30,    -1,    43,   101,
      -1,    87,    -1,    89,    87,    -1,    89,     1,    87,    -1,
      40,   101,    87,    41,    87,    -1,    40,   101,    87,    -1,
      40,     1,    87,    -1,    40,   101,     1,    87,    -1,    40,
     101,    87,    41,     1,    30,    -1,    92,    29,   101,    -1,
      92,    29,     1,    30,    -1,    65,    -1,    65,    94,    -1,
      35,    95,    36,    -1,    -1,    96,    -1,   101,    -1,    96,
      28,   101,    -1,   107,    65,    -1,    35,   104,    36,    -1,
      -1,    33,   100,    34,    -1,    89,    -1,    78,    89,    -1,
      78,     1,    -1,   103,    -1,   102,    -1,    92,    -1,    91,
      -1,    93,    -1,    15,   101,    -1,     8,   101,    -1,    35,
     101,    36,    -1,    27,   101,    -1,   101,    16,   101,    -1,
     101,    17,   101,    -1,   101,    22,   101,    -1,   101,    20,
     101,    -1,   101,    23,   101,    -1,   101,    21,   101,    -1,
     101,    18,   101,    -1,   101,    19,   101,    -1,   101,    26,
     101,    -1,   101,    14,   101,    -1,   101,     8,   101,    -1,
     101,    24,   101,    -1,   101,    11,   101,    -1,   101,    10,
     101,    -1,   101,    13,   101,    -1,   101,    25,   101,    -1,
     101,    12,   101,    -1,   101,     7,   101,    -1,    46,   101,
      -1,    49,    -1,    50,    -1,    53,    -1,    63,    -1,    64,
      -1,    -1,   105,    -1,   106,    -1,   105,    28,   106,    -1,
     107,    65,    -1,   108,    -1,    58,   108,    -1,    65,    -1,
      57,    -1,    59,    -1,    61,    -1,    51,    -1,    52,    -1,
      60,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   143,   151,   154,   158,   165,   169,   173,
     180,   199,   218,   225,   229,   233,   237,   241,   248,   254,
     261,   265,   269,   273,   277,   281,   288,   295,   307,   314,
     325,   329,   333,   337,   344,   349,   357,   361,   368,   379,
     387,   391,   399,   404,   417,   425,   428,   433,   441,   445,
     449,   453,   457,   461,   465,   477,   487,   494,   500,   505,
     512,   516,   520,   524,   528,   535,   539,   546,   554,   562,
     570,   573,   580,   585,   593,   602,   610,   613,   620,   624,
     628,   635,   639,   643,   647,   651,   655,   659,   663,   667,
     671,   675,   679,   683,   687,   691,   695,   699,   703,   707,
     711,   715,   720,   725,   730,   735,   740,   745,   752,   759,
     763,   767,   771,   775,   783,   786,   793,   798,   806,   814,
     818,   823,   831,   835,   839,   843,   847,   851
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_LEX_ERROR", "TOK_PAT_STAR",
  "TOK_PAT_OR", "TOK_PAT_NOT", "TOK_PLUS", "TOK_MINUS", "TOK_UMINUS",
  "TOK_MULT", "TOK_DIV", "TOK_MOD", "TOK_BITAND", "TOK_BITOR",
  "TOK_BITNOT", "TOK_BITXOR", "TOK_SHL", "TOK_SHR", "TOK_GT", "TOK_LT",
  "TOK_GE", "TOK_LE", "TOK_EQ", "TOK_NE", "TOK_AND", "TOK_OR", "TOK_NOT",
  "TOK_COMMA", "TOK_ASSIGN", "TOK_SEMICOLON", "TOK_COLON", "TOK_ARROW",
  "TOK_LBRACE", "TOK_RBRACE", "TOK_LPAREN", "TOK_RPAREN", "TOK_LBRACK",
  "TOK_RBRACK", "TOK_QMARK", "TOK_IF", "TOK_ELSE", "TOK_CLASS",
  "TOK_RETURN", "TOK_EVENT", "TOK_ANY", "TOK_PRINT", "TOK_WHILE",
  "TOK_BREAK", "TOK_UINTNUM", "TOK_DOUBLENUM", "TOK_VOID", "TOK_STRING",
  "TOK_STRCONST", "TOK_BIT", "TOK_ENUM", "TOK_LONG", "TOK_INT",
  "TOK_UNSIGNED", "TOK_BOOL", "TOK_BYTE", "TOK_DOUBLE", "TOK_SHORT",
  "TOK_TRUE", "TOK_FALSE", "TOK_IDENT", "TOK_DOUBLE_COLON", "TOK_DOT",
  "$accept", "specification", "ifc_decl_star", "rule_list", "rule",
  "ifc_decl", "class_decl", "event_pattern", "rule_body1", "function_decl",
  "variable_decl", "vlist", "vname", "event_decl", "event_decl_hdr",
  "primitive_pat", "event", "evenparamlistpp", "evenparamlist", "stmt",
  "ret_stmt", "stmt_plus", "if_then_else_stmt", "asg_stmt", "ref_expr",
  "function_invocation", "funcinvolistpp", "expr_list", "expr_plus",
  "function_header", "formalparamlistpp", "funcbody", "fun_rest", "expr",
  "prt_expr", "literal", "formal_param_list", "formal_param_plus",
  "formal_param", "type", "baseType", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    69,    70,    70,    70,    71,    71,    71,
      72,    72,    72,    73,    73,    73,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    76,    77,    77,    78,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    82,
      83,    83,    84,    84,    85,    86,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    88,    89,    89,    89,
      90,    90,    90,    90,    90,    91,    91,    92,    93,    94,
      95,    95,    96,    96,    97,    98,    99,    99,   100,   100,
     100,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   102,   103,
     103,   103,   103,   103,   104,   104,   105,   105,   106,   107,
     107,   107,   108,   108,   108,   108,   108,   108
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     3,     1,     2,     3,
       3,     4,     3,     1,     1,     1,     1,     1,     2,     3,
       1,     3,     3,     3,     2,     2,     1,     3,     3,     3,
       4,     4,     3,     3,     1,     3,     1,     3,     2,     2,
       1,     3,     1,     2,     3,     0,     1,     3,     1,     1,
       1,     3,     1,     1,     3,     2,     2,     1,     2,     3,
       5,     3,     3,     4,     6,     3,     4,     1,     2,     3,
       0,     1,     1,     3,     2,     3,     0,     3,     1,     2,
       2,     1,     1,     1,     1,     1,     2,     2,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     1,     0,     1,     1,     3,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,    13,     0,     0,     0,
      42,   125,   126,   122,     0,   123,   127,   124,     0,     0,
       7,     5,    17,     0,    14,    15,    16,     0,    20,    40,
       0,     0,   119,     6,     0,    25,     0,     0,    18,    39,
     120,     0,    45,    43,     0,     8,     0,    24,     0,     0,
       0,   114,    38,     0,     0,    76,     0,    36,     0,    34,
      21,    19,    33,    46,     0,     9,    48,     0,     0,     0,
       0,     0,    67,    12,    26,    53,    52,    50,     0,    49,
       0,    23,    22,    10,   121,     0,   115,   116,     0,     0,
       0,     0,     0,   109,   110,   111,   112,   113,    84,    83,
      85,    41,    82,    81,    28,     0,    27,    32,     0,     0,
       0,    29,     0,    44,    57,     0,     0,     0,    56,   108,
       0,    70,    68,     0,    55,    11,    75,     0,   118,    87,
      86,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,    30,    31,    36,
      35,    47,     0,    51,    58,    62,     0,    61,    54,     0,
      71,    72,     0,    65,   117,    88,   107,   100,   103,   102,
     106,   104,    99,    90,    91,    96,    97,    93,    95,    92,
      94,   101,   105,    98,    80,     0,    77,    59,    63,     0,
      69,     0,    66,     0,    60,    73,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    19,    20,    21,    22,    23,    73,    24,
      25,    58,    59,    26,    27,    28,    29,    43,    64,   114,
      75,   115,    76,    98,    99,   100,   122,   169,   170,    30,
      52,   106,   154,   101,   102,   103,    85,    86,    87,    88,
      32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -101
static const yytype_int16 yypact[] =
{
    -101,    40,   223,  -101,   -14,   -15,  -101,   -15,     8,    -8,
    -101,  -101,  -101,  -101,   282,  -101,  -101,  -101,    13,     2,
    -101,  -101,  -101,    57,  -101,  -101,  -101,    28,  -101,    27,
       0,    14,  -101,  -101,    31,  -101,    20,    23,  -101,  -101,
    -101,    34,     3,  -101,    60,  -101,   166,  -101,   -15,   -15,
     166,   340,  -101,   424,    64,    62,    70,    10,    16,  -101,
    -101,  -101,  -101,  -101,    -5,  -101,  -101,   166,   165,   424,
     424,   424,    76,  -101,  -101,  -101,  -101,  -101,    80,  -101,
      91,    29,   119,    97,  -101,    95,   104,  -101,    71,   424,
     424,   424,   424,  -101,  -101,  -101,  -101,  -101,  -101,    80,
    -101,   516,  -101,  -101,  -101,   439,  -101,  -101,   424,   109,
      17,  -101,    72,  -101,  -101,   226,   166,   285,   516,   516,
     403,   424,  -101,   311,  -101,  -101,  -101,   340,  -101,    74,
     107,   555,   495,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     424,     7,   100,   319,   111,    18,   516,  -101,  -101,   122,
    -101,  -101,   166,  -101,  -101,  -101,   166,   115,  -101,   116,
     135,   516,   134,   516,  -101,  -101,    74,    74,  -101,  -101,
    -101,   107,   445,   445,   150,   150,   573,   573,   573,   573,
     573,   573,   555,   536,  -101,   339,  -101,  -101,  -101,   347,
    -101,   424,  -101,   142,  -101,   516,  -101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,  -101,  -101,   155,  -101,  -101,     6,   126,  -101,
      73,  -101,    69,  -101,  -101,  -101,  -101,  -101,  -101,   -12,
    -101,  -100,  -101,   -46,   -40,   -24,  -101,  -101,  -101,  -101,
     152,  -101,  -101,    99,   -18,  -101,  -101,  -101,    58,     5,
     170
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -122
static const yytype_int16 yytable[] =
{
      77,    54,    -3,    44,    77,   153,    78,    31,    41,    37,
      78,    35,     5,    36,    41,    56,    33,   109,   158,    56,
       7,    77,    79,   112,    47,    48,    79,    78,    80,     5,
      10,   113,    80,    47,    74,    51,   -67,     7,    74,   108,
       3,    53,   121,    79,   110,   -74,   111,    10,    42,    80,
      34,    49,   195,    61,    81,    82,    60,    39,    46,    77,
      49,    47,    48,    51,    62,    78,    42,    34,    63,    77,
      77,    77,  -121,    38,    77,    78,    78,    78,  -121,    57,
      78,    79,   159,   159,   135,   136,   137,    80,    49,    50,
      65,    79,    79,    79,   104,   105,    79,    80,    80,    80,
     107,   194,    80,   164,   165,   167,    77,    77,   168,   123,
     155,   121,    78,    78,   133,   134,    77,   135,   136,   137,
      77,   124,    78,    47,   141,   142,    78,   125,    79,    79,
      66,   126,   127,    67,    80,    80,   128,   161,    79,   157,
      68,   164,    79,    69,    80,   196,    70,    71,    80,    77,
     197,   108,   200,    77,   198,    78,   199,   133,   134,    78,
     135,   136,   137,   201,   202,    72,   116,   117,   118,   119,
     120,    79,   206,    89,    45,    79,    83,    80,   152,   160,
      90,    80,    55,   164,    40,   174,     0,   204,   129,   130,
     131,   132,    91,     0,     0,     0,    66,     0,     0,    67,
      92,     0,     0,     0,     0,     0,    68,   156,     0,    69,
       0,    70,    70,    71,    93,    94,     0,     0,    95,     0,
     171,     0,   173,    -2,     4,     0,     0,   162,    96,    97,
      72,    72,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
       5,     0,     0,     6,     0,     0,    66,     0,     7,    67,
     163,     0,     0,     0,     0,     8,    68,     9,    10,    69,
       0,     0,    70,    71,    11,    12,     0,     0,     0,     0,
      13,    14,    15,    16,    17,     0,   166,     0,    18,     0,
       0,    72,   133,   134,     0,   135,   136,   137,   138,   139,
     205,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   172,     0,     0,    66,     0,     0,    67,    89,
     162,     0,     0,     0,     0,    68,    90,     0,    69,     0,
       0,    70,    71,    11,    12,     0,     0,     0,    91,    13,
     162,    15,    16,    17,     0,     0,    92,     0,   203,    66,
      72,     0,    67,   -78,     0,     0,     0,    70,     0,    68,
      93,    94,    69,     0,    95,    70,    71,     0,     0,    66,
       0,     0,    67,   -79,    96,    97,    72,    66,     0,    68,
      67,     0,    69,     0,    72,    70,    71,    68,     0,     0,
      69,    11,    12,    70,    71,     0,     0,    13,    14,    15,
      16,    17,     0,     0,    72,    84,     0,     0,     0,     0,
     133,   134,    72,   135,   136,   137,   138,   139,     0,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
       0,     0,    89,    66,     0,     0,    67,     0,     0,    90,
       0,     0,     0,    68,     0,     0,    69,     0,     0,    70,
      71,    91,   133,   134,     0,   135,   136,   137,   138,    92,
       0,     0,   141,   142,     0,     0,     0,     0,    72,    66,
      70,     0,    67,    93,    94,     0,     0,    95,     0,    68,
       0,     0,    69,     0,     0,    70,    71,    96,    97,    72,
      11,    12,     0,     0,     0,     0,    13,    14,    15,    16,
      17,     0,   133,   134,   151,   135,   136,   137,   138,   139,
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,     0,   133,   134,     0,   135,   136,   137,   138,
     139,   175,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   133,   134,     0,   135,   136,   137,   138,
     139,     0,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   133,   134,     0,   135,   136,   137,   138,   139,
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     133,   134,     0,   135,   136,   137,   138,   139,     0,   140,
     141,   142,  -122,  -122,  -122,  -122,  -122,  -122
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-101))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-122))

static const yytype_int16 yycheck[] =
{
      46,     1,     0,     1,    50,   105,    46,     2,     1,     1,
      50,     5,    27,     7,     1,     1,    30,     1,     1,     1,
      35,    67,    46,    28,     4,     5,    50,    67,    46,    27,
      45,    36,    50,     4,    46,    35,    29,    35,    50,    29,
       0,    14,    35,    67,    28,    35,    30,    45,    35,    67,
      65,    31,   152,    30,    48,    49,    36,    65,     1,   105,
      31,     4,     5,    35,    30,   105,    35,    65,    65,   115,
     116,   117,    65,    65,   120,   115,   116,   117,    65,    65,
     120,   105,    65,    65,    10,    11,    12,   105,    31,    32,
      30,   115,   116,   117,    30,    33,   120,   115,   116,   117,
      30,     1,   120,   115,   116,   117,   152,   153,   120,    29,
     105,    35,   152,   153,     7,     8,   162,    10,    11,    12,
     166,    30,   162,     4,    17,    18,   166,    30,   152,   153,
      30,    36,    28,    33,   152,   153,    65,    65,   162,    30,
      40,   153,   166,    43,   162,    34,    46,    47,   166,   195,
     162,    29,    36,   199,   166,   195,    41,     7,     8,   199,
      10,    11,    12,    28,    30,    65,     1,    68,    69,    70,
      71,   195,    30,     8,    19,   199,    50,   195,   105,   110,
      15,   199,    30,   195,    14,   127,    -1,   199,    89,    90,
      91,    92,    27,    -1,    -1,    -1,    30,    -1,    -1,    33,
      35,    -1,    -1,    -1,    -1,    -1,    40,   108,    -1,    43,
      -1,    46,    46,    47,    49,    50,    -1,    -1,    53,    -1,
     121,    -1,   123,     0,     1,    -1,    -1,     1,    63,    64,
      65,    65,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
      27,    -1,    -1,    30,    -1,    -1,    30,    -1,    35,    33,
      34,    -1,    -1,    -1,    -1,    42,    40,    44,    45,    43,
      -1,    -1,    46,    47,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    -1,     1,    -1,    65,    -1,
      -1,    65,     7,     8,    -1,    10,    11,    12,    13,    14,
     201,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,     1,    -1,    -1,    30,    -1,    -1,    33,     8,
       1,    -1,    -1,    -1,    -1,    40,    15,    -1,    43,    -1,
      -1,    46,    47,    51,    52,    -1,    -1,    -1,    27,    57,
       1,    59,    60,    61,    -1,    -1,    35,    -1,     1,    30,
      65,    -1,    33,    34,    -1,    -1,    -1,    46,    -1,    40,
      49,    50,    43,    -1,    53,    46,    47,    -1,    -1,    30,
      -1,    -1,    33,    34,    63,    64,    65,    30,    -1,    40,
      33,    -1,    43,    -1,    65,    46,    47,    40,    -1,    -1,
      43,    51,    52,    46,    47,    -1,    -1,    57,    58,    59,
      60,    61,    -1,    -1,    65,    65,    -1,    -1,    -1,    -1,
       7,     8,    65,    10,    11,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,     8,    30,    -1,    -1,    33,    -1,    -1,    15,
      -1,    -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    46,
      47,    27,     7,     8,    -1,    10,    11,    12,    13,    35,
      -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    65,    30,
      46,    -1,    33,    49,    50,    -1,    -1,    53,    -1,    40,
      -1,    -1,    43,    -1,    -1,    46,    47,    63,    64,    65,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    59,    60,
      61,    -1,     7,     8,    65,    10,    11,    12,    13,    14,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,     7,     8,    -1,    10,    11,    12,    13,
      14,    36,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,     7,     8,    -1,    10,    11,    12,    13,
      14,    -1,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,     7,     8,    -1,    10,    11,    12,    13,    14,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       7,     8,    -1,    10,    11,    12,    13,    14,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    69,    70,     0,     1,    27,    30,    35,    42,    44,
      45,    51,    52,    57,    58,    59,    60,    61,    65,    71,
      72,    73,    74,    75,    77,    78,    81,    82,    83,    84,
      97,   107,   108,    30,    65,    75,    75,     1,    65,    65,
     108,     1,    35,    85,     1,    72,     1,     4,     5,    31,
      32,    35,    98,    14,     1,    98,     1,    65,    79,    80,
      36,    30,    30,    65,    86,    30,    30,    33,    40,    43,
      46,    47,    65,    76,    87,    88,    90,    91,    92,    93,
     102,    75,    75,    76,    65,   104,   105,   106,   107,     8,
      15,    27,    35,    49,    50,    53,    63,    64,    91,    92,
      93,   101,   102,   103,    30,    33,    99,    30,    29,     1,
      28,    30,    28,    36,    87,    89,     1,   101,   101,   101,
     101,    35,    94,    29,    30,    30,    36,    28,    65,   101,
     101,   101,   101,     7,     8,    10,    11,    12,    13,    14,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    65,    78,    89,   100,   107,   101,    30,     1,    65,
      80,    65,     1,    34,    87,    87,     1,    87,    87,    95,
      96,   101,     1,   101,   106,    36,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,     1,    89,    34,    87,    87,    41,
      36,    28,    30,     1,    87,   101,    30
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 140 "E--_parser.y++"
    { 
    errMsg("Must contain at least one rule"); 
}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 144 "E--_parser.y++"
    {
    
}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 151 "E--_parser.y++"
    {
  
}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 155 "E--_parser.y++"
    {
    
}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 159 "E--_parser.y++"
    {
    errMsg("Syntax error, expecting a declaration");  
}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 166 "E--_parser.y++"
    {
  
}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 170 "E--_parser.y++"
    {
  
}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 174 "E--_parser.y++"
    {
    errMsg("Error, expecting a rule");
}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 181 "E--_parser.y++"
    {
    if ((yyvsp[(1) - (3)].patVal)) {
        stm.leaveScope();   // Leave BlockEntry (event)
        if ((yyvsp[(3) - (3)].stmtVal)) {
            (yyval.ruleNode) = new RuleNode(new BlockEntry(" ", yylinenum, yycolumnno, yyfilename), (yyvsp[(1) - (3)].patVal), (yyvsp[(3) - (3)].stmtVal), yylinenum, yycolumnno, yyfilename);
            if ( stm.currentScope() && stm.currentScope()->kind() == SymTabEntry::Kind::GLOBAL_KIND) {
                GlobalEntry* ge = (GlobalEntry*)stm.currentScope();
                ge->addRule((yyval.ruleNode));
            }
        }
    } else
        (yyval.ruleNode) = NULL;
    /*stm.leaveScope();
    GlobalEntry* gloen = (GlobalEntry*)stm.currentScope();
    BlockEntry *t = new BlockEntry("Block", yylinenum, yycolumnno, yyfilename);
    $$ = new RuleNode(t, $1, $3, yylinenum, yycolumnno, yyfilename);  
    gloen->addRule($$);*/
}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 200 "E--_parser.y++"
    {
    if ((yyvsp[(1) - (4)].patVal)) {
        stm.leaveScope();   // Leave BlockEntry (event)
        if ((yyvsp[(3) - (4)].stmtVal)) {
            (yyval.ruleNode) = new RuleNode(new BlockEntry(" ", yylinenum, yycolumnno, yyfilename), (yyvsp[(1) - (4)].patVal), (yyvsp[(3) - (4)].stmtVal), yylinenum, yycolumnno, yyfilename);
            if ( stm.currentScope() && stm.currentScope()->kind() == SymTabEntry::Kind::GLOBAL_KIND) {
                GlobalEntry* ge = (GlobalEntry*)stm.currentScope();
                ge->addRule((yyval.ruleNode));
            }
        }
    } else
        (yyval.ruleNode) = NULL;
    /*stm.leaveScope();
    GlobalEntry* gloen = (GlobalEntry*)stm.currentScope();
    BlockEntry *t = new BlockEntry("Block", yylinenum, yycolumnno, yyfilename);
    $$ = new RuleNode(t, $1, $3, yylinenum, yycolumnno, yyfilename); 
    gloen->addRule($$);*/
}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 219 "E--_parser.y++"
    {
    errMsg("Syntax error, skipping event pattern");
}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 226 "E--_parser.y++"
    {
  
}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 230 "E--_parser.y++"
    {
  
}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 234 "E--_parser.y++"
    {
  
}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 238 "E--_parser.y++"
    {
  
}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 242 "E--_parser.y++"
    {
    
}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 249 "E--_parser.y++"
    { 
    (yyval.classEntry) = new ClassEntry((yyvsp[(2) - (2)].cVal), yylinenum, yycolumnno, yyfilename); 
    stm.insert((yyval.classEntry));
}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 255 "E--_parser.y++"
    {
    errMsg("Syntax error in class declaration: expecting class name");
}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 262 "E--_parser.y++"
    {
    (yyval.patVal) = (yyvsp[(1) - (1)].primPatVal);
}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 266 "E--_parser.y++"
    {
    (yyval.patVal) = (yyvsp[(2) - (3)].patVal);
}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 270 "E--_parser.y++"
    {
    (yyval.patVal) = new PatNode(BasePatNode::PatNodeKind::SEQ, (yyvsp[(1) - (3)].patVal), (yyvsp[(3) - (3)].patVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 274 "E--_parser.y++"
    {
    (yyval.patVal) = new PatNode(BasePatNode::PatNodeKind::OR, (yyvsp[(1) - (3)].patVal), (yyvsp[(3) - (3)].patVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 278 "E--_parser.y++"
    {
    (yyval.patVal) = new PatNode(BasePatNode::PatNodeKind::STAR, (yyvsp[(1) - (2)].patVal), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 282 "E--_parser.y++"
    {
    (yyval.patVal) = new PatNode(BasePatNode::PatNodeKind::NEG, (yyvsp[(2) - (2)].patVal), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 289 "E--_parser.y++"
    {
    (yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);
}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 296 "E--_parser.y++"
    {
    (yyval.functionEntry) = (yyvsp[(1) - (3)].functionEntry);
    stm.leaveScope();
    Type* func_Type = new Type((yyvsp[(2) - (3)].typeList), (yyval.functionEntry)->type());
    (yyval.functionEntry)->type(func_Type);
    if ((yyvsp[(3) - (3)].compoundStmtVal) != NULL)
    {
        (yyval.functionEntry)->body((yyvsp[(3) - (3)].compoundStmtVal));
    }
    stm.insert((yyval.functionEntry));
}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 308 "E--_parser.y++"
    {
    errMsg("Syntax error in formal parameter declaration");
}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 315 "E--_parser.y++"
    {
    VariableEntry *t;
    int x = (yyvsp[(2) - (3)].variableList)->size();
    for (int i = 0; i < x; i++)
    {
        t = (yyvsp[(2) - (3)].variableList)->at(i);
        t->type((yyvsp[(1) - (3)].typeVal));
        stm.insert(t);
    }
}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 326 "E--_parser.y++"
    {
    errMsg("Error in variable declaration, may be a missing \",\" or identifier");
}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 330 "E--_parser.y++"
    {
    errMsg("Error in variable declaration, may be a missing \",\" or identifier");
}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 334 "E--_parser.y++"
    {
    errMsg("Error in variable declaration, may be a missing identifier");
}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 338 "E--_parser.y++"
    {
    errMsg("Error in variable declaration, may be a missing type name or identifier");
}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 345 "E--_parser.y++"
    {
    (yyval.variableList) = new vector<VariableEntry*>;
    (yyval.variableList)->push_back((yyvsp[(1) - (1)].variableEntry));
}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 350 "E--_parser.y++"
    {
    //$$ = $1;                                //should be like this
    (yyval.variableList)->push_back((yyvsp[(3) - (3)].variableEntry));
}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 358 "E--_parser.y++"
    {
    (yyval.variableEntry) = new VariableEntry((yyvsp[(1) - (1)].cVal), VariableEntry::VarKind::GLOBAL_VAR, NULL, NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 362 "E--_parser.y++"
    {
    (yyval.variableEntry) = new VariableEntry((yyvsp[(1) - (3)].cVal), VariableEntry::VarKind::GLOBAL_VAR, NULL, (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 369 "E--_parser.y++"
    {
    (yyval.eventEntry) = (yyvsp[(1) - (2)].eventEntry);
    Type* event_type = new Type((yyvsp[(2) - (2)].typeList), Type::EVENT);
    stm.leaveScope();
    (yyval.eventEntry)->type(event_type);
    stm.insert((yyval.eventEntry));
}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 380 "E--_parser.y++"
    {
    (yyval.eventEntry) = new EventEntry((yyvsp[(2) - (2)].cVal), yylinenum, yycolumnno, yyfilename);
    stm.enterScope((yyval.eventEntry));
}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 388 "E--_parser.y++"
    {
    (yyval.primPatVal) = (yyvsp[(1) - (1)].primPatVal);
}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 392 "E--_parser.y++"
    {
    (yyval.primPatVal) = (yyvsp[(1) - (3)].primPatVal);
    (yyval.primPatVal)->cond((yyvsp[(3) - (3)].exprVal));
}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 400 "E--_parser.y++"
    {
    EventEntry* e = (EventEntry*)stm.lookUp((yyvsp[(1) - (1)].cVal));
    (yyval.primPatVal) = new PrimitivePatNode(e, NULL, NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 405 "E--_parser.y++"
    {
    EventEntry* e = (EventEntry*)stm.lookUpInScope((yyvsp[(1) - (2)].cVal), SymTabEntry::Kind::GLOBAL_KIND);
    if (stm.currentScope()->kind() != SymTabEntry::Kind::BLOCK_KIND) 
    {
        stm.enterScope(new BlockEntry((yyvsp[(1) - (2)].cVal), yylinenum, yycolumnno, yyfilename));
    }
    //stm.enterScope(b);
    (yyval.primPatVal) = new PrimitivePatNode(e, (yyvsp[(2) - (2)].variableList), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 418 "E--_parser.y++"
    {
    (yyval.variableList) = (yyvsp[(2) - (3)].variableList);
}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 425 "E--_parser.y++"
    { 
    (yyval.variableList) = NULL;
}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 429 "E--_parser.y++"
    {
    (yyval.variableList) = new vector<VariableEntry*>;
    (yyval.variableList)->push_back(new VariableEntry((yyvsp[(1) - (1)].cVal), VariableEntry::VarKind::PARAM_VAR, NULL, NULL, yylinenum, yycolumnno, yyfilename));
}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 434 "E--_parser.y++"
    {
    //$$ = $1;
    (yyval.variableList)->push_back(new VariableEntry((yyvsp[(3) - (3)].cVal), VariableEntry::VarKind::PARAM_VAR, NULL, NULL, yylinenum, yycolumnno, yyfilename));
}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 442 "E--_parser.y++"
    {
    (yyval.stmtVal) = NULL;
}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 446 "E--_parser.y++"
    {
    (yyval.stmtVal) = new ExprStmtNode((yyvsp[(1) - (1)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 450 "E--_parser.y++"
    {
    (yyval.stmtVal) = new ExprStmtNode((yyvsp[(1) - (1)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 454 "E--_parser.y++"
    {
    (yyval.stmtVal) = new CompoundStmtNode((yyvsp[(2) - (3)].stmtList), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 458 "E--_parser.y++"
    {
    (yyval.stmtVal) = (yyvsp[(1) - (1)].ifVal);
}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 462 "E--_parser.y++"
    {
    (yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);
}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 466 "E--_parser.y++"
    {
    if((yyvsp[(2) - (3)].exprVal) && (yyvsp[(3) - (3)].stmtVal)) 
    {
        //cout << "this is while!" << endl;
        (yyval.stmtVal) = new WhileNode((yyvsp[(2) - (3)].exprVal), (yyvsp[(3) - (3)].stmtVal), yylinenum, yycolumnno, yyfilename);
        //stm.leaveScope();
        //stm.insert($$);
    }
    else
        (yyval.stmtVal) = NULL;
}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 478 "E--_parser.y++"
    {
        if((yyvsp[(1) - (2)].exprVal))
            (yyval.stmtVal) = new ExprStmtNode((yyvsp[(1) - (2)].exprVal), yylinenum, yycolumnno, yyfilename);
        else
            (yyval.stmtVal) = NULL;   
}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 488 "E--_parser.y++"
    {
    (yyval.stmtVal) = new ReturnStmtNode((yyvsp[(2) - (2)].exprVal), (FunctionEntry*)stm.currentScope(), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 495 "E--_parser.y++"
    {
    
    (yyval.stmtList) = new list<StmtNode*>;
    if ((yyvsp[(1) - (1)].stmtVal) != NULL)(yyval.stmtList)->push_back((yyvsp[(1) - (1)].stmtVal));
}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 501 "E--_parser.y++"
    {
    (yyval.stmtList) = (yyvsp[(1) - (2)].stmtList);
    if ((yyvsp[(2) - (2)].stmtVal) != NULL) (yyval.stmtList)->push_back((yyvsp[(2) - (2)].stmtVal));
}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 506 "E--_parser.y++"
    {
    errMsg("Syntax error while parsing a statement");
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 513 "E--_parser.y++"
    {
    (yyval.ifVal) = new IfNode((yyvsp[(2) - (5)].exprVal), (yyvsp[(3) - (5)].stmtVal), (yyvsp[(5) - (5)].stmtVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 517 "E--_parser.y++"
    {
    (yyval.ifVal) = new IfNode((yyvsp[(2) - (3)].exprVal), (yyvsp[(3) - (3)].stmtVal), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 521 "E--_parser.y++"
    {
    errMsg("Syntax error while parsing a statement");
}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 525 "E--_parser.y++"
    {
    errMsg("Syntax error while parsing a statement");
}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 529 "E--_parser.y++"
    {
    errMsg("Syntax error in else statement");
}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 536 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::ASSIGN, (yyvsp[(1) - (3)].refexpVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 540 "E--_parser.y++"
    {
    errMsg("Syntax error in assignment");
}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 547 "E--_parser.y++"
    {
    SymTabEntry* e = stm.lookUp((yyvsp[(1) - (1)].cVal));
    (yyval.refexpVal) = new RefExprNode((yyvsp[(1) - (1)].cVal), e, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 555 "E--_parser.y++"
    {
    SymTabEntry* fEntry = stm.lookUpInScope((yyvsp[(1) - (2)].cVal), SymTabEntry::Kind::GLOBAL_KIND);
    (yyval.exprVal) = new InvocationNode((const SymTabEntry*)fEntry, (yyvsp[(2) - (2)].exprList), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 563 "E--_parser.y++"
    {
    (yyval.exprList) = (yyvsp[(2) - (3)].exprList);
}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 570 "E--_parser.y++"
    {
    (yyval.exprList) = NULL; 
}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 574 "E--_parser.y++"
    {
    (yyval.exprList) = (yyvsp[(1) - (1)].exprList);
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 581 "E--_parser.y++"
    {
    (yyval.exprList) = new vector<ExprNode*>;
    (yyval.exprList)->push_back((yyvsp[(1) - (1)].exprVal));
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 586 "E--_parser.y++"
    {
    //$$ = $1;
    (yyval.exprList)->push_back((yyvsp[(3) - (3)].exprVal));
}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 594 "E--_parser.y++"
    {

    (yyval.functionEntry) = new FunctionEntry((yyvsp[(2) - (2)].cVal), (yyvsp[(1) - (2)].typeVal), yylinenum, yycolumnno, yyfilename);
    stm.enterScope((yyval.functionEntry));
}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 603 "E--_parser.y++"
    { 
    (yyval.typeList) = (yyvsp[(2) - (3)].typeList);
}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 610 "E--_parser.y++"
    {
    (yyval.compoundStmtVal) = NULL;
}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 614 "E--_parser.y++"
    {
    (yyval.compoundStmtVal) = (yyvsp[(2) - (3)].compoundStmtVal);
}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 621 "E--_parser.y++"
    {
    (yyval.compoundStmtVal) = new CompoundStmtNode((yyvsp[(1) - (1)].stmtList), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 625 "E--_parser.y++"
    {
    (yyval.compoundStmtVal) = new CompoundStmtNode((yyvsp[(2) - (2)].stmtList), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 629 "E--_parser.y++"
    {
    errMsg("Syntax error, expecting a declaration");
}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 636 "E--_parser.y++"
    {
    (yyval.exprVal) = new ValueNode((yyvsp[(1) - (1)].valVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 640 "E--_parser.y++"
    {
    (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);
}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 644 "E--_parser.y++"
    {
    (yyval.exprVal) = (yyvsp[(1) - (1)].refexpVal);
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 648 "E--_parser.y++"
    {
    (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);
}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 652 "E--_parser.y++"
    {
    (yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);
}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 656 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::BITNOT, (yyvsp[(2) - (2)].exprVal), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 660 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::UMINUS, (yyvsp[(2) - (2)].exprVal), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 664 "E--_parser.y++"
    {
    (yyval.exprVal) = (yyvsp[(2) - (3)].exprVal);
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 668 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::NOT, (yyvsp[(2) - (2)].exprVal), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 672 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::BITXOR, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 676 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::SHL, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 680 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::LE, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 684 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::LT, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 688 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::EQ, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 692 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::GE, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 696 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::SHR, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 700 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::GT, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 704 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::OR, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 708 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::BITOR, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 712 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::MINUS, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 716 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::NE, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
  
}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 721 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::DIV, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);

}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 726 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::MULT, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);

}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 731 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::BITAND, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);

}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 736 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::AND, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);

}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 741 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::MOD, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);

}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 746 "E--_parser.y++"
    {
    (yyval.exprVal) = new OpNode(OpNode::OpCode::PLUS, (yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal), yylinenum, yycolumnno, yyfilename);
}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 753 "E--_parser.y++"
    { 
    (yyval.exprVal) = new OpNode(OpNode::OpCode::PRINT, (yyvsp[(2) - (2)].exprVal), NULL, yylinenum, yycolumnno, yyfilename);
}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 760 "E--_parser.y++"
    { 
    (yyval.valVal) = new Value((yyvsp[(1) - (1)].uVal), Type::UINT); 
}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 764 "E--_parser.y++"
    { 
    (yyval.valVal) = new Value((yyvsp[(1) - (1)].dVal));             
}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 768 "E--_parser.y++"
    {   
    (yyval.valVal) = new Value((yyvsp[(1) - (1)].cVal));             
}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 772 "E--_parser.y++"
    {   
    (yyval.valVal) = new Value(true);           
}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 776 "E--_parser.y++"
    { 
    (yyval.valVal) = new Value(false);          
}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 783 "E--_parser.y++"
    {
    (yyval.typeList) = NULL;
}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 787 "E--_parser.y++"
    {
    (yyval.typeList) = (yyvsp[(1) - (1)].typeList);
}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 794 "E--_parser.y++"
    {
    (yyval.typeList) = new vector<Type*>;
    (yyval.typeList)->push_back((yyvsp[(1) - (1)].variableEntry)->type());
}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 799 "E--_parser.y++"
    {
    //$$ = $1;
    (yyval.typeList)->push_back((yyvsp[(3) - (3)].variableEntry)->type());
}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 807 "E--_parser.y++"
    {
    (yyval.variableEntry) = new VariableEntry((yyvsp[(2) - (2)].cVal), VariableEntry::VarKind::PARAM_VAR, (yyvsp[(1) - (2)].typeVal), NULL, yylinenum, yycolumnno, yyfilename);
    stm.insert((yyval.variableEntry));
}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 815 "E--_parser.y++"
    {
    (yyval.typeVal) = (yyvsp[(1) - (1)].typeVal); 
}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 819 "E--_parser.y++"
    { 
    if(((yyvsp[(2) - (2)].typeVal))->tag() == Type::INT)
    (yyval.typeVal) = new Type(Type::UINT);
}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 824 "E--_parser.y++"
    {
    SymTabEntry* e = stm.lookUp((yyvsp[(1) - (1)].cVal));
    (yyval.typeVal) = new Type(e, Type::TypeTag::CLASS);
}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 832 "E--_parser.y++"
    { 
    (yyval.typeVal) = new Type(Type::INT);     
}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 836 "E--_parser.y++"
    {   
    (yyval.typeVal) = new Type(Type::BOOL);    
}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 840 "E--_parser.y++"
    {   
    (yyval.typeVal) = new Type(Type::DOUBLE);  
}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 844 "E--_parser.y++"
    { 
    (yyval.typeVal) = new Type(Type::VOID);    
}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 848 "E--_parser.y++"
    { 
    (yyval.typeVal) = new Type(Type::STRING); 
}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 852 "E--_parser.y++"
    {   
    (yyval.typeVal) = new Type(Type::BYTE);    
}
    break;



/* Line 1806 of yacc.c  */
#line 2985 "E--_parser.C"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 856 "E--_parser.y++"


