/*-------------------------------------------------------------------------
 *
 * hello_fdw.c
 *     example foreign data wrapper for PostgreSQL
 *
 * Copyright (c) 2015: Your Name Here <youaresocool@domain.tld>
 * Copyright (c) 2015, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *		hello_fdw/hello_fdw.c
 *
 *-------------------------------------------------------------------------
 */


#include "postgres.h"

#include "foreign/fdwapi.h"
#include "foreign/foreign.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(hello_fdw_handler);
PG_FUNCTION_INFO_V1(hello_fdw_validator);

Datum
hello_fdw_handler(PG_FUNCTION_ARGS)
{
	FdwRoutine *fdwroutine = makeNode(FdwRoutine);

	PG_RETURN_POINTER(fdwroutine);
}

Datum
hello_fdw_validator(PG_FUNCTION_ARGS)
{
	PG_RETURN_VOID();
}
