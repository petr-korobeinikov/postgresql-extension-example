-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION hello_fdw" to load this file. \quit

CREATE FUNCTION hello_fdw_handler()
    RETURNS fdw_handler
    AS 'MODULE_PATHNAME'
    LANGUAGE C STRICT;

CREATE FUNCTION hello_fdw_validator(text[], oid)
    RETURNS void
    AS 'MODULE_PATHNAME'
    LANGUAGE C STRICT;

CREATE FOREIGN DATA WRAPPER hello_fdw
    HANDLER hello_fdw_handler
    VALIDATOR hello_fdw_validator;
