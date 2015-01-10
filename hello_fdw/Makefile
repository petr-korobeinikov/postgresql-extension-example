MODULES = hello_fdw

EXTENSION = hello_fdw
DATA = hello_fdw--1.0.sql
PGFILEDESC = "hello_fdw - example foreign data wrapper for postgresql"

#REGRESS = hello_fdw

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
