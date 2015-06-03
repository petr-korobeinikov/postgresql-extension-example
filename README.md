## Структура расширения

    expected/
        ext_name.out        # Ожидаемые результаты запуска тестов
    results/
        ext_name.out        # Результаты запуска тестов
    sql/
        ext_name.sql        # SQL-команды тестов (создание расширения, вызовы функций),
                            # выполняемые при вызове make installcheck
    ext_name.c              # Код расширения (может быть разнесен на несколько файлов)
    ext_name--version.sql   # SQL-команды установки расширения (создание функций, типов данных и пр.)
    ext_name.control        # Файл с описанием расширения
    Makefile

### Тесты

https://wiki.postgresql.org/wiki/Regression_test_authoring &mdash; создание регрессионных тестов

### Исходный код

http://www.postgresql.org/docs/devel/static/xfunc-c.html &mdash; примеры функций на C

### Makefile

http://www.postgresql.org/docs/devel/static/extend-pgxs.html

### control- и sql-файлы установки [и обновления] расширения

http://www.postgresql.org/docs/devel/static/extend-extensions.html

## hello_ext &mdash; пример расширения

    make
    make install
    make installcheck                       # прогон тестов
    psql -c 'create extension hello_ext'
    psql -c 'select hello_world()'

## hello_bgw &mdash; пример background worker'а

    make
    make install

    $EDITOR path/to/postgresql.conf
    --- shared_preload_libraries = ''
    +++ shared_preload_libraries = 'hello_bgw'

    pg_ctl -D path/to/datadir restart

## hello_fdw &mdash; пример foreign data wrapper'а

    todo

http://www.postgresql.org/docs/devel/static/fdwhandler.html

## hello_spi &mdash; пример server programming interface'а

    todo

## hello_plh &mdash; пример procedural language handler'а

    todo

## Другие примеры

* https://bitbucket.org/adunstan/blackhole_fdw
* https://github.com/michaelpq/pg_plugins
    * http://michael.otacoo.com/postgresql-2/blackhole-extension/
    * http://michael.otacoo.com/postgresql-2/postgres-9-3-feature-highlight-hello-world-with-custom-bgworkers/
