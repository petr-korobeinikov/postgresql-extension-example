MODULES = hello_ext

EXTENSION = hello_ext
DATA = hello_ext--1.0.sql
PGFILEDESC = "hello_ext - example extension for postgresql"

REGRESS = hello_ext

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
