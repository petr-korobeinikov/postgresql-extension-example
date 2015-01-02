/*-------------------------------------------------------------------------
 *
 * hello_ext.c
 *     example extenstion for PostgreSQL
 *
 * Copyright (c) 2014-2015: Your Name Here <youaresocool@domain.tld>
 * Copyright (c) 2014-2015, PostgreSQL Global Development Group
 *
 *-------------------------------------------------------------------------
 */


#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(hello_world);
PG_FUNCTION_INFO_V1(greet);

Datum
hello_world(PG_FUNCTION_ARGS)
{
	PG_RETURN_TEXT_P(cstring_to_text("Hello, world!"));
}

Datum
greet(PG_FUNCTION_ARGS)
{

	text *hello	= cstring_to_text("hello, ");
	text *name	= PG_GETARG_TEXT_P(0);

	int32 hello_name_sz = VARSIZE(hello) + VARSIZE(name) - VARHDRSZ;
	text *hello_name = (text *) palloc(hello_name_sz);

	SET_VARSIZE(hello_name, hello_name_sz);
	memcpy(VARDATA(hello_name), VARDATA(hello), VARSIZE(hello) - VARHDRSZ);
	memcpy(VARDATA(hello_name) + (VARSIZE(hello) - VARHDRSZ),
		   VARDATA(name),
		   VARSIZE(name) - VARHDRSZ);

	PG_RETURN_TEXT_P(hello_name);
}
