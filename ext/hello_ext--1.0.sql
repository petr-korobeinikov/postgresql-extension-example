-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION hello_world" to load this file. \quit

CREATE FUNCTION hello_world()
    RETURNS text
    AS 'MODULE_PATHNAME'
    LANGUAGE C;

CREATE FUNCTION hello_text_arg(text)
    RETURNS text
    AS 'MODULE_PATHNAME'
    LANGUAGE C;

CREATE FUNCTION hello_ereport()
    RETURNS void
    AS 'MODULE_PATHNAME'
    LANGUAGE C;
