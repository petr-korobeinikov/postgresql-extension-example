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
PG_FUNCTION_INFO_V1(hello_text_arg);
PG_FUNCTION_INFO_V1(hello_ereport);

Datum
hello_world(PG_FUNCTION_ARGS)
{
	PG_RETURN_TEXT_P(cstring_to_text("Hello, World!"));
}

Datum
hello_text_arg(PG_FUNCTION_ARGS)
{
	text *hello		= cstring_to_text("Hello, ");
	int32 hello_sz	= VARSIZE(hello) - VARHDRSZ;

	text *name		= PG_GETARG_TEXT_P(0);
	int32 name_sz	= VARSIZE(name) - VARHDRSZ;

	text *tail		= cstring_to_text("!");
	int32 tail_sz	= VARSIZE(tail) - VARHDRSZ;

	int32 out_sz	= hello_sz + name_sz + tail_sz + VARHDRSZ;
	text *out		= (text *) palloc(out_sz);

	SET_VARSIZE(out, out_sz);

	memcpy(VARDATA(out), VARDATA(hello), hello_sz);
	memcpy(VARDATA(out) + hello_sz, VARDATA(name), name_sz);
	memcpy(VARDATA(out) + hello_sz + name_sz, VARDATA(tail), tail_sz);

	PG_RETURN_TEXT_P(out);
}

Datum
hello_ereport(PG_FUNCTION_ARGS)
{
	ereport(ERROR,
			(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
			errmsg("null value not allowed")));

	PG_RETURN_VOID();
}
